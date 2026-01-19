#!/usr/bin/env python3
"""
Decompile Java .class files using Vineflower with Rosetta metadata enhancement
Integrates PZ-Rosetta documentation into decompiled source code
"""

import os
import subprocess
import sys
import yaml
import re
import zipfile
import shutil
import time
import mmap
import functools
import json
from pathlib import Path
from multiprocessing import Pool, cpu_count, set_start_method
from concurrent.futures import ThreadPoolExecutor, as_completed
from typing import Dict, Optional, List, Tuple, Set
from collections import defaultdict

# Ensure fork is used (more reliable on Linux)
try:
    set_start_method('fork')
except RuntimeError:
    pass  # Already set

try:
    from tqdm import tqdm
    HAS_TQDM = True
except ImportError:
    HAS_TQDM = False
    def tqdm(iterable, **kwargs):
        return iterable

class RosettaDocumentation:
    """Load and provide access to Rosetta documentation"""
    def __init__(self, rosetta_base: str = None, cache_path: Optional[str] = None):
        self.rosetta_base = rosetta_base or "/workspaces/PZ/tools/pz-rosetta-source-main/rosetta/java"
        self.class_docs = {}
        self.methods_docs = defaultdict(dict)
        self.fields_docs = defaultdict(dict)
        self.loaded = False
        self._target_classes: Optional[Set[str]] = None
        # Default cache location under workspace .cache
        default_cache = os.path.join(Path.cwd(), ".cache", "rosetta_java_class_docs.json")
        self.cache_path = cache_path or default_cache
        # Injection toggles (default: class docs on, method/field off to minimize overhead)
        self.inject_class_docs: bool = True
        self.inject_method_docs: bool = False
        self.inject_field_docs: bool = False
    
    def load(self, workers: Optional[int] = None, target_classes: Optional[Set[str]] = None, use_cache: bool = True):
        """Load Rosetta documentation in parallel for speed.
        If target_classes is provided, only documentation for those classes will be stored.
        """
        if not os.path.isdir(self.rosetta_base):
            print(f"Rosetta base not found: {self.rosetta_base}")
            return False
        
        yml_files = list(Path(self.rosetta_base).rglob("*.yml"))
        print(f"Loading Rosetta documentation from {len(yml_files)} files...")
        if not yml_files:
            return False

        # Apply target class filter if provided
        self._target_classes = target_classes

        # Attempt cache load when enabled and fresh
        if use_cache and self._try_load_from_cache(yml_files):
            return True
        
        # Choose sensible default worker count
        if workers is None:
            try:
                from multiprocessing import cpu_count
                workers = max(1, min(8, cpu_count() - 1))
            except Exception:
                workers = 4
        
        # Parse YAML files in parallel threads (I/O bound)
        # Use the fastest available YAML loader
        try:
            from yaml import CSafeLoader as YAMLLoader
        except Exception:
            try:
                from yaml import CLoader as YAMLLoader
            except Exception:
                from yaml import SafeLoader as YAMLLoader

        def _parse_file(path: Path):
            try:
                with open(path, 'r', encoding='utf-8') as f:
                    data = yaml.load(f, Loader=YAMLLoader)
                if data and 'languages' in data and 'java' in data['languages']:
                    return data['languages']['java']
            except Exception:
                return None
            return None
        
        parsed_count = 0
        from concurrent.futures import ThreadPoolExecutor, as_completed
        with ThreadPoolExecutor(max_workers=workers) as ex:
            futures = [ex.submit(_parse_file, p) for p in yml_files]
            for fut in tqdm(as_completed(futures), total=len(futures), desc="Loading docs", disable=not HAS_TQDM):
                java_data = None
                try:
                    java_data = fut.result()
                except Exception:
                    java_data = None
                if java_data:
                    self._extract_docs(java_data)
                    parsed_count += 1
        
        self.loaded = True
        # Write cache (class docs only) for future fast loads
        try:
            os.makedirs(os.path.dirname(self.cache_path), exist_ok=True)
            # Prefer ultra-fast json if available
            try:
                import orjson  # type: ignore
                with open(self.cache_path, 'wb') as f:
                    f.write(orjson.dumps({
                        'class_docs': self.class_docs,
                        'methods_docs': {k: v for k, v in self.methods_docs.items()},
                        'fields_docs': {k: v for k, v in self.fields_docs.items()},
                    }))
            except Exception:
                with open(self.cache_path, 'w', encoding='utf-8') as f:
                    json.dump({
                        'class_docs': self.class_docs,
                        'methods_docs': {k: v for k, v in self.methods_docs.items()},
                        'fields_docs': {k: v for k, v in self.fields_docs.items()},
                    }, f)
        except Exception:
            pass
        print(f"✓ Loaded documentation for {len(self.class_docs)} classes from {parsed_count} files")
        return True
        def _try_load_from_cache(self, yml_files: List[Path]) -> bool:
            """Load class docs from cache if cache is newer than any YAML file. Apply target filter if set."""
            try:
                if not os.path.isfile(self.cache_path):
                    return False
                cache_mtime = os.path.getmtime(self.cache_path)
                latest_yaml_mtime = max((f.stat().st_mtime for f in yml_files), default=0)
                if cache_mtime < latest_yaml_mtime:
                    return False
                # Load cache
                try:
                    import orjson  # type: ignore
                    with open(self.cache_path, 'rb') as f:
                        data = orjson.loads(f.read())
                except Exception:
                    with open(self.cache_path, 'r', encoding='utf-8') as f:
                        data = json.load(f)
                class_docs = data.get('class_docs', {})
                methods_docs = data.get('methods_docs', {})
                fields_docs = data.get('fields_docs', {})
                if self._target_classes is not None:
                    # Filter down to target classes only
                    self.class_docs = {k: v for k, v in class_docs.items() if k in self._target_classes}
                    self.methods_docs = defaultdict(dict, {k: v for k, v in methods_docs.items() if k in self._target_classes})
                    self.fields_docs = defaultdict(dict, {k: v for k, v in fields_docs.items() if k in self._target_classes})
                else:
                    self.class_docs = class_docs
                    self.methods_docs = defaultdict(dict, methods_docs)
                    self.fields_docs = defaultdict(dict, fields_docs)
                self.loaded = True
                print(f"✓ Loaded documentation from cache ({len(self.class_docs)} classes)")
                return True
            except Exception:
                return False
    
    def _extract_docs(self, java_data: Dict):
        """Extract documentation from Java language data"""
        if 'packages' not in java_data:
            return
        
        for package_name, classes_dict in java_data['packages'].items():
            if not isinstance(classes_dict, dict):
                continue
            for class_name, class_info in classes_dict.items():
                if not isinstance(class_info, dict):
                    continue
                
                full_name = f"{package_name}.{class_name}"

                # If filtering to target classes, skip others early
                if self._target_classes is not None and full_name not in self._target_classes:
                    continue
                
                # Store class documentation
                self.class_docs[full_name] = {
                    'notes': class_info.get('notes', ''),
                    'modifiers': class_info.get('modifiers', []),
                }
                
                # Store field documentation
                for field_name, field_info in class_info.get('fields', {}).items():
                    if isinstance(field_info, dict):
                        self.fields_docs[full_name][field_name] = field_info.get('notes', '')
                
                # Store method documentation
                for method_info in class_info.get('methods', []):
                    if isinstance(method_info, dict):
                        method_name = method_info.get('name', '')
                        params = self._extract_params_doc(method_info.get('parameters', []))
                        self.methods_docs[full_name][method_name] = {
                            'notes': method_info.get('notes', ''),
                            'parameters': params,
                            'return_notes': method_info.get('return_notes', ''),
                        }
    
    def _extract_params_doc(self, params: list) -> Dict:
        """Extract parameter documentation"""
        result = {}
        for param in params:
            if isinstance(param, dict):
                param_name = param.get('name', '')
                result[param_name] = param.get('notes', '')
        return result
    
    def get_class_doc(self, class_name: str) -> Optional[str]:
        """Get class documentation"""
        doc = self.class_docs.get(class_name, {})
        return doc.get('notes', '')
    
    def get_method_doc(self, class_name: str, method_name: str) -> Optional[Dict]:
        """Get method documentation"""
        return self.methods_docs.get(class_name, {}).get(method_name, {})
    
    def get_field_doc(self, class_name: str, field_name: str) -> Optional[str]:
        """Get field documentation"""
        return self.fields_docs.get(class_name, {}).get(field_name, '')

# Cache Java path to avoid repeated lookups
_JAVA_PATH_CACHE = None
_VINEFLOWER_JAR_PATH = '/workspaces/PZ/ZomboidDecompiler/lib/vineflower-1.11.2-module.jar'

def _get_java_cmd(java_home: str) -> str:
    """Get full path to Java executable, cached. Prefers system java 17+ over JAVA_HOME."""
    global _JAVA_PATH_CACHE
    if _JAVA_PATH_CACHE is None:
        # Try system java first (more likely to be correct version for Vineflower)
        import shutil
        system_java = shutil.which('java')
        if system_java:
            try:
                # Check if it's Java 17+ (required for Vineflower JAR)
                result = subprocess.run([system_java, '-version'], capture_output=True, text=True, timeout=5)
                version_output = result.stderr if result.stderr else result.stdout
                # Look for version number (e.g., "21.0.9" or "17.0.1")
                version_match = re.search(r'version "(\d+)\.', version_output)
                if version_match:
                    major_version = int(version_match.group(1))
                    if major_version >= 17:
                        _JAVA_PATH_CACHE = system_java
                        return _JAVA_PATH_CACHE
            except Exception:
                pass
        
        # Fall back to JAVA_HOME
        _JAVA_PATH_CACHE = os.path.join(java_home, 'bin', 'java')
    return _JAVA_PATH_CACHE

def decompile_file(args: Tuple) -> Tuple[bool, str]:
    """Decompile a single .class file using Vineflower (optimized for multiprocessing)"""
    class_file, output_dir, java_home, rosetta_docs = args
    try:
        # Create relative path structure
        rel_path = os.path.relpath(class_file)
        output_file = os.path.join(output_dir, rel_path.replace('.class', '.java'))
        output_file_dir = os.path.dirname(output_file)
        
        # Ensure output directory exists
        os.makedirs(output_file_dir, exist_ok=True)
        
        # Run Vineflower with optimization flags
        # These flags skip expensive operations while maintaining quality output
        cmd = [
            _get_java_cmd(java_home),
            '-jar',
            _VINEFLOWER_JAR_PATH,
            '--silent',  # Suppress verbose output
            '--decompiler-comments=false',  # Skip adding decompiler comments (speeds up processing)
            '--bytecode-source-mapping=false',  # Skip bytecode mapping (not needed for our use case)
            '--dump-code-lines=false',  # Skip line mapping dumps
            class_file,
            output_file_dir
        ]
        
        result = subprocess.run(cmd, capture_output=True, timeout=60)
        
        if result.returncode == 0:
            # Try to enhance with Rosetta documentation
            if rosetta_docs and rosetta_docs.loaded and os.path.exists(output_file):
                _enhance_with_rosetta(output_file, rosetta_docs)
            return (True, class_file)
        else:
            return (False, f"{class_file}: {result.stderr.decode()[:100]}")
    
    except subprocess.TimeoutExpired:
        return (False, f"{class_file}: Timeout")
    except Exception as e:
        return (False, f"{class_file}: {str(e)[:100]}")

def decompile_batch(args: Tuple[List[str], str, str, Optional[RosettaDocumentation]]) -> Tuple[int, int]:
    """Decompile a batch of class files in one worker. Returns (success_count, failed_count)."""
    files, output_dir, java_home, rosetta_docs = args
    success = 0
    failed = 0
    print(f"[Worker] Starting batch of {len(files)} files...", flush=True)
    for i, cf in enumerate(files):
        try:
            if i % 20 == 0:
                print(f"[Worker] Processing file {i+1}/{len(files)}", flush=True)
            ok, _msg = decompile_file((cf, output_dir, java_home, rosetta_docs))
            if ok:
                success += 1
            else:
                failed += 1
                print(f"[Worker] Failed: {_msg[:100]}", flush=True)
        except Exception as e:
            failed += 1
            print(f"[Worker] Exception: {str(e)[:100]}", flush=True)
    print(f"[Worker] Batch complete: {success} success, {failed} failed", flush=True)
    return (success, failed)

def _enhance_with_rosetta(java_file: str, rosetta_docs: RosettaDocumentation):
    """Enhance decompiled Java file with Rosetta documentation"""
    try:
        with open(java_file, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # Extract class name from file path
        class_name = _extract_class_name_from_path(java_file)
        if not class_name:
            return
        
        # Get class documentation
        class_doc = rosetta_docs.get_class_doc(class_name)
        
        # Add class documentation if available and enabled
        if rosetta_docs.inject_class_docs and class_doc:
            class_match = CLASS_DECL_RE.search(content)
            if class_match:
                insert_pos = class_match.start()
                if insert_pos >= 3 and content[insert_pos-3:insert_pos] == '/**':
                    pass
                else:
                    doc_comment = f"/**\n * {class_doc}\n */\n"
                    content = content[:insert_pos] + doc_comment + content[insert_pos:]

        # Inject method-level docs if enabled
        if rosetta_docs.inject_method_docs:
            methods = rosetta_docs.get_method_doc(class_name, '')  # placeholder; we will use dict directly
            methods = rosetta_docs.methods_docs.get(class_name, {})
            for mname, minfo in methods.items():
                notes = (minfo or {}).get('notes', '')
                params = (minfo or {}).get('parameters', {})
                if not notes and not params:
                    continue
                # Build doc comment
                doc_lines = ["/**"]
                if notes:
                    doc_lines.append(f" * {notes}")
                if params:
                    for pname, pnote in params.items():
                        doc_lines.append(f" * @param {pname} {pnote}")
                doc_lines.append(" */\n")
                doc_comment = "\n".join(doc_lines)
                # Search for method declaration and inject above
                method_re = re.compile(rf"(^|\n)([ \t]*(public|private|protected|static|final|synchronized|native|abstract|strictfp)[^;{{]*\b{re.escape(mname)}\s*\()", re.MULTILINE)
                mm = method_re.search(content)
                if mm:
                    insert_pos = mm.start(2)
                    # Avoid duplicate immediate doc blocks
                    prev_chunk = content[max(0, insert_pos-4):insert_pos]
                    if '/**' not in prev_chunk:
                        content = content[:insert_pos] + doc_comment + content[insert_pos:]

        # Inject field-level docs if enabled
        if rosetta_docs.inject_field_docs:
            fields = rosetta_docs.fields_docs.get(class_name, {})
            for fname, fnotes in fields.items():
                if not fnotes:
                    continue
                doc_comment = f"/**\n * {fnotes}\n */\n"
                field_re = re.compile(rf"(^|\n)([ \t]*(public|private|protected|static|final|transient|volatile)[^;{{]*\b{re.escape(fname)}\b[^;(]*;)", re.MULTILINE)
                fm = field_re.search(content)
                if fm:
                    insert_pos = fm.start(2)
                    prev_chunk = content[max(0, insert_pos-4):insert_pos]
                    if '/**' not in prev_chunk:
                        content = content[:insert_pos] + doc_comment + content[insert_pos:]
        
        # Write enhanced content back
        with open(java_file, 'w', encoding='utf-8') as f:
            f.write(content)
    
    except Exception as e:
        pass  # Silently fail, don't block decompilation

@functools.lru_cache(maxsize=10000)
def _extract_class_name_from_path(java_file: str) -> Optional[str]:
    """Extract full class name from Java file path"""
    try:
        # Remove .java extension and split by directory separator
        parts = java_file.replace('.java', '').split(os.sep)
        
        # Find the package starting point (usually after 'converted' or 'classes_only')
        if 'converted' in parts:
            start_idx = parts.index('converted') + 1
        elif 'classes_only' in parts:
            start_idx = parts.index('classes_only') + 1
        else:
            start_idx = 0
        
        # Join remaining parts with dots to form full class name
        class_path = '.'.join(parts[start_idx:])
        return class_path if class_path else None
    except Exception:
        return None

# Precompile class declaration regex for faster matching across many files
CLASS_DECL_RE = re.compile(r'(public |private |protected |static )*class ')

def _class_name_from_classfile(input_dir: str, class_file: Path) -> Optional[str]:
    """Derive fully qualified class name from a .class file path relative to input_dir."""
    try:
        rel = os.path.relpath(str(class_file), start=input_dir)
        if rel.startswith('..'):
            # class_file not under input_dir
            rel = os.path.basename(str(class_file))
        # If the path contains a leading jar subdir, drop it to align with package roots
        parts = rel.replace('.class', '').split(os.sep)
        if len(parts) > 1:
            parts = parts[1:]
        name = '.'.join(parts)
        return name if name else None
    except Exception:
        return None

def extract_jars_to_classes(input_dir: str, output_dir: str) -> Tuple[int, int]:
    """Extract all .class files from JAR files in input directory
    
    Optimized to use extractall() for better performance
    Returns tuple of (jar_count, class_count)
    """
    jar_files = list(Path(input_dir).rglob('*.jar'))
    
    if not jar_files:
        return (0, 0)
    
    print(f"\nFound {len(jar_files)} JAR files to extract")
    extracted_count = 0
    class_count = 0
    
    for jar_file in tqdm(jar_files, desc="Extracting JARs", disable=not HAS_TQDM):
        try:
            with zipfile.ZipFile(jar_file, 'r') as zip_ref:
                # Get list of class files (more efficient than extracting all)
                class_files = [f for f in zip_ref.namelist() if f.endswith('.class')]
                
                if class_files:
                    jar_name = jar_file.stem
                    jar_output = os.path.join(output_dir, jar_name)
                    
                    # Use extract for each class file
                    for class_file in class_files:
                        try:
                            zip_ref.extract(class_file, jar_output)
                        except KeyError:
                            pass
                    
                    extracted_count += 1
                    class_count += len(class_files)
        
        except zipfile.BadZipFile:
            pass  # Skip invalid ZIP files
        except Exception as e:
            pass  # Silently skip problematic JARs
    
    if extracted_count > 0:
        print(f"✓ Extracted {class_count} class files from {extracted_count} JAR files")
    
    return (extracted_count, class_count)

def flatten_extracted_jars(classes_dir: str) -> int:
    """Flatten directory structure to prepare for decompilation
    
    Moves all .class files from JAR subdirectories to flat structure
    Optimized for speed with batch operations
    Returns the number of .class files moved
    """
    moved_count = 0
    
    try:
        # Get all class files in one pass (more efficient)
        all_class_files = list(Path(classes_dir).rglob('*.class'))
        
        if not all_class_files:
            return 0
        
        # Identify JAR subdirectories
        jar_subdirs = set()
        for class_file in all_class_files:
            rel_parts = class_file.relative_to(classes_dir).parts
            if len(rel_parts) > 1:
                jar_subdirs.add(rel_parts[0])
        
        if jar_subdirs:
            print(f"\nFlattening {len(jar_subdirs)} JAR extraction directories...")
            
            for subdir_name in tqdm(jar_subdirs, desc="Flattening structure", disable=not HAS_TQDM):
                jar_dir = Path(classes_dir) / subdir_name
                try:
                    class_files = list(jar_dir.rglob('*.class'))
                    for class_file in class_files:
                        rel_path = class_file.relative_to(jar_dir)
                        target_path = Path(classes_dir) / rel_path
                        
                        # Create parent directories
                        target_path.parent.mkdir(parents=True, exist_ok=True)
                        
                        # Move file (shutil.move for efficiency)
                        if not target_path.exists():
                            shutil.move(str(class_file), str(target_path))
                            moved_count += 1
                    
                    # Remove empty JAR subdirectory
                    shutil.rmtree(jar_dir, ignore_errors=True)
                
                except Exception:
                    pass  # Skip problematic directories
            
            if moved_count > 0:
                print(f"✓ Flattened {moved_count} class files from JAR directories")
        
    except Exception:
        pass  # Silently handle any errors
    
    return moved_count

def main():
    if len(sys.argv) < 3:
        print("Usage: python3 decompile_vineflower.py <input_dir> <output_dir> [options]")
        print("\nOptions:")
        print("  --skip-rosetta          Skip Rosetta documentation enhancement")
        print("  --extract-jars-only     Only extract JARs, don't decompile")
        print("  --workers N             Use N parallel workers (default: auto)")
        print("  --filter-rosetta        Only load docs for target classes (default: on)")
        print("  --no-filter-rosetta     Disable target-class filtering")
        print("  --rosetta-cache PATH    Path to Rosetta JSON cache (default: .cache/rosetta_java_class_docs.json)")
        print("  --no-inject-class-docs  Disable class-level doc injection")
        print("  --inject-method-docs    Enable method-level doc injection")
        print("  --inject-field-docs     Enable field-level doc injection")
        print("  --build-rosetta-cache-only  Build Rosetta cache and exit (no decompilation)")
        print("  --progress-interval N   Print progress every N files (default: auto)")
        sys.exit(1)
    
    input_dir = sys.argv[1]
    output_dir = sys.argv[2]
    java_home = '/usr/lib/jvm/java-21-openjdk-amd64'
    skip_rosetta = '--skip-rosetta' in sys.argv
    extract_only = '--extract-jars-only' in sys.argv
    build_cache_only = '--build-rosetta-cache-only' in sys.argv
    filter_rosetta = True
    if '--no-filter-rosetta' in sys.argv:
        filter_rosetta = False
    elif '--filter-rosetta' in sys.argv:
        filter_rosetta = True
    # Rosetta cache path
    cache_path = None
    if '--rosetta-cache' in sys.argv:
        try:
            idx = sys.argv.index('--rosetta-cache')
            cache_path = sys.argv[idx + 1]
        except Exception:
            cache_path = None
    # Progress interval (files)
    progress_interval: Optional[int] = None
    if '--progress-interval' in sys.argv:
        try:
            idx = sys.argv.index('--progress-interval')
            progress_interval = int(sys.argv[idx + 1])
        except Exception:
            progress_interval = None
    # Injection toggles
    inject_class_docs = True
    if '--no-inject-class-docs' in sys.argv:
        inject_class_docs = False
    inject_method_docs = '--inject-method-docs' in sys.argv
    inject_field_docs = '--inject-field-docs' in sys.argv
    
    # Parse worker count - use all CPUs for subprocess work (they release GIL)
    # For threading with subprocess calls, we can use more workers than CPU count
    workers = min(cpu_count() * 2, 8)  # Use 2x CPU count but cap at 8
    if '--workers' in sys.argv:
        try:
            idx = sys.argv.index('--workers')
            workers = int(sys.argv[idx + 1])
        except (IndexError, ValueError):
            pass
    
    start_time = time.time()
    classes_temp_dir = os.path.join(input_dir, '.extracted_classes')

    # Enable line-buffered stdout so progress shows even when piped/tee'd
    try:
        sys.stdout.reconfigure(line_buffering=True)
    except Exception:
        pass

    # If we only want to build Rosetta cache, do it early and exit
    if build_cache_only:
        print("\nBuilding Rosetta documentation cache...")
        try:
            rosetta_docs = RosettaDocumentation(cache_path=cache_path)
            # Always full load for cache; ignore filtering and existing cache freshness
            if rosetta_docs.load(workers=workers, target_classes=None, use_cache=False):
                print(f"✓ Rosetta cache built with {len(rosetta_docs.class_docs)} classes")
                if rosetta_docs.cache_path:
                    print(f"Cache: {rosetta_docs.cache_path}")
            else:
                print("⚠ Failed to build Rosetta cache")
        except Exception:
            print("⚠ Exception while building Rosetta cache")
        return
    
    # Extract JARs and get counts
    jar_count, extracted_class_count = extract_jars_to_classes(input_dir, classes_temp_dir)
    
    # If JARs were extracted, flatten the directory structure
    if jar_count > 0:
        flatten_extracted_jars(classes_temp_dir)
    
    # If extract-only flag is set, stop here
    if extract_only:
        elapsed = time.time() - start_time
        print(f"\n✓ JAR extraction complete in {elapsed:.1f}s")
        if jar_count > 0:
            print(f"Extracted classes in: {classes_temp_dir}")
        return
    
    # Find all .class files (optimized single pass)
    class_files = list(Path(input_dir).rglob('*.class'))
    
    if not class_files:
        print("No .class files found!")
        return
    
    print(f"\nFound {len(class_files)} total .class files to decompile")
    if jar_count > 0:
        print(f"  ├─ {len(class_files) - extracted_class_count} loose .class files")
        print(f"  └─ {extracted_class_count} extracted from {jar_count} JAR files")
    
    # Create output directory
    os.makedirs(output_dir, exist_ok=True)
    
    # Load Rosetta documentation if available
    rosetta_docs = None
    if not skip_rosetta:
        try:
            rosetta_docs = RosettaDocumentation(cache_path=cache_path)
            print("\nLoading Rosetta documentation...")
            # Build target class set to filter Rosetta load to only classes being decompiled
            target_classes: Optional[Set[str]] = None
            if filter_rosetta:
                target_classes = set()
                for cf in class_files:
                    cn = _class_name_from_classfile(input_dir, cf)
                    if cn:
                        target_classes.add(cn)
            if rosetta_docs.load(workers=workers, target_classes=target_classes, use_cache=True):
                # If filtering resulted in zero matches and filtering is enabled, fall back to full load
                if filter_rosetta and len(rosetta_docs.class_docs) == 0:
                    rosetta_docs = RosettaDocumentation(cache_path=cache_path)
                    rosetta_docs.load(workers=workers, use_cache=True)
                # Set injection toggles
                rosetta_docs.inject_class_docs = inject_class_docs
                rosetta_docs.inject_method_docs = inject_method_docs
                rosetta_docs.inject_field_docs = inject_field_docs
                print(f"✓ Rosetta documentation loaded ({len(rosetta_docs.class_docs)} classes)")
            else:
                rosetta_docs = None
        except Exception:
            rosetta_docs = None
    
    # Prepare decompilation jobs
    decompile_jobs = [(str(cf), output_dir, java_home, rosetta_docs) for cf in class_files]
    
    # Decompile using multiprocessing for better parallelism
    success_count = 0
    failed_count = 0
    
    print(f"\nDecompiling with {workers} workers...", flush=True)
    decompile_start = time.time()
    
    try:
        # Determine batch size if not provided earlier
        total_files = len(class_files)
        if progress_interval is None:
            # Default: about 20 updates across the run
            progress_interval = max(50, total_files // 20)
        if '--batch-size' in sys.argv:
            try:
                idx = sys.argv.index('--batch-size')
                batch_size = int(sys.argv[idx + 1])
            except Exception:
                # Optimize batch size: smaller batches = better parallelism, but not too small
                # For threading with subprocess work, we want more batches than workers
                batch_size = max(5, total_files // (workers * 16))
        else:
            # Optimize batch size: smaller batches = better parallelism, but not too small
            # For threading with subprocess work, we want more batches than workers
            batch_size = max(5, total_files // (workers * 16))

        # Build batches
        batches: List[List[str]] = []
        current: List[str] = []
        for cf in class_files:
            current.append(str(cf))
            if len(current) >= batch_size:
                batches.append(current)
                current = []
        if current:
            batches.append(current)

        print(f"\nUsing batch size {batch_size} across {len(batches)} batches", flush=True)
        print(f"Starting decompilation...", flush=True)
        
        jobs = [(batch, output_dir, java_home, rosetta_docs) for batch in batches]
        
        # Use ThreadPoolExecutor as fallback - more reliable than multiprocessing Pool
        # For CPU-bound subprocess work, threading works fine since subprocesses release GIL
        with ThreadPoolExecutor(max_workers=workers) as executor:
            print(f"Submitting {len(jobs)} batch jobs to {workers} workers...", flush=True)
            futures = {}
            for i, job in enumerate(jobs):
                future = executor.submit(decompile_batch, job)
                futures[future] = i
            
            print(f"Submitted all jobs, waiting for completion...", flush=True)
            processed = 0
            batch_num = 0
            
            for future in as_completed(futures):
                batch_num += 1
                batch_id = futures[future]
                try:
                    s, f = future.result(timeout=300)  # 5 minute timeout per batch
                    success_count += s
                    failed_count += f
                    processed += (s + f)
                    
                    # Show progress
                    elapsed = time.time() - decompile_start
                    rate = processed / elapsed if elapsed > 0 else 0
                    remaining = (total_files - processed) / rate if rate > 0 else 0
                    print(f"  Batch {batch_num}/{len(batches)} (ID: {batch_id}) | [{processed}/{total_files}] | {rate:.1f} files/sec | ETA: {remaining:.0f}s", flush=True)
                except Exception as e:
                    print(f"  Batch {batch_id} error: {e}", flush=True)
                    failed_count += len(jobs[batch_id][0])  # Count all files in failed batch
            
            print(f"\nAll batches completed!", flush=True)
    
    except KeyboardInterrupt:
        print("\n⚠ Decompilation interrupted")
    
    # Cleanup temporary extraction directory
    if jar_count > 0 and os.path.exists(classes_temp_dir):
        try:
            shutil.rmtree(classes_temp_dir)
        except Exception:
            pass
    
    # Final statistics
    total_time = time.time() - start_time
    decompile_time = time.time() - decompile_start
    
    print(f"\n{'='*60}")
    print(f"Decompilation Complete")
    print(f"{'='*60}")
    print(f"Files decompiled: {success_count}/{len(class_files)}")
    print(f"Success rate: {success_count/len(class_files)*100:.1f}%")
    if failed_count > 0:
        print(f"Failed: {failed_count}")
    if jar_count > 0:
        print(f"JAR files processed: {jar_count}")
    print(f"\nTiming:")
    print(f"  Decompilation: {decompile_time:.1f}s ({len(class_files)/decompile_time:.1f} files/sec)")
    print(f"  Total time: {total_time:.1f}s")
    print(f"  Workers used: {workers}")
    if rosetta_docs and rosetta_docs.loaded:
        print(f"  Rosetta enhancement: {len(rosetta_docs.class_docs)} classes")
    print(f"\nOutput: {output_dir}")
    print(f"{'='*60}\n")

if __name__ == '__main__':
    main()
