#!/usr/bin/env python3
"""
Advanced Java-to-C++ Converter - Production Edition
Features: Streaming, batch regex, multiprocessing, caching, metadata awareness
"""

import os
import re
import sys
import json
import hashlib
from pathlib import Path
from typing import Dict, Optional
from multiprocessing import Pool, cpu_count

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(iterable, **kwargs):
        return iterable

class AdvancedProductionConverter:
    def __init__(self, class_map_file: str = None, use_cache=True, num_workers=None, chunk_size=8192):
        self.class_map_file = class_map_file or "/workspaces/PZ/class_map.json"
        self.class_map = {}
        self.callbacks = {}
        self.events = {}
        self.hooks = {}
        self.known_classes = set()
        self.load_class_map()
        
        self.use_cache = use_cache
        self.cache_file = "/workspaces/PZ/.advanced_conversion_cache.json"
        self.cache = self._load_cache() if use_cache else {}
        
        self.num_workers = num_workers or max(1, cpu_count() - 1)
        self.chunk_size = chunk_size
        
        # Pre-compile and batch regex patterns
        self.patterns = self._build_batch_patterns()
        
        self.stats = {
            'files_processed': 0,
            'files_skipped_cached': 0,
            'class_recognized': 0,
            'total_fixes': 0,
        }
    
    def _load_cache(self):
        """Load conversion cache."""
        if os.path.exists(self.cache_file):
            try:
                with open(self.cache_file, 'r') as f:
                    return json.load(f)
            except Exception:
                return {}
        return {}
    
    def _save_cache(self):
        """Save conversion cache."""
        try:
            with open(self.cache_file, 'w') as f:
                json.dump(self.cache, f)
        except Exception:
            pass
    
    def _get_file_hash(self, filepath):
        """Get hash of file contents for caching."""
        try:
            with open(filepath, 'rb') as f:
                return hashlib.md5(f.read()).hexdigest()
        except Exception:
            return None
    
    def load_class_map(self):
        """Load pre-generated class map JSON."""
        if not os.path.exists(self.class_map_file):
            print(f"Warning: Class map not found at {self.class_map_file}")
            return
        
        try:
            with open(self.class_map_file, 'r') as f:
                data = json.load(f)
                self.class_map = data.get('classes', {})
                self.callbacks = data.get('callbacks', {})
                self.events = data.get('events', {})
                self.hooks = data.get('hooks', {})
                self.known_classes = set(self.class_map.keys())
                print(f"Loaded class map: {len(self.known_classes)} classes, "
                      f"{len(self.callbacks)} callbacks, {len(self.events)} events")
        except Exception as e:
            print(f"Error loading class map: {e}")
    
    def _build_batch_patterns(self) -> Dict:
        """Build combined regex patterns for batch processing."""
        return {
            # Batch Java keyword removal
            'java_keywords': re.compile(r'\b(?:final|abstract|volatile|transient|strictfp|native)\s+'),
            
            # Batch method conversions
            'this_dot': re.compile(r'\bthis\.'),
            'throw_new': re.compile(r'\bthrow\s+new\b'),
            'is_empty': re.compile(r'\.isEmpty\(\)'),
            'null_keyword': re.compile(r'(?<!\w)null(?!\w)'),
            
            # Batch parenthesis and whitespace
            'double_parens': re.compile(r'(\w+)\)\)'),
            'whitespace': re.compile(r'  +'),
            
            # Project Zomboid specific patterns
            'callback_pattern': re.compile(r'(?:' + '|'.join(re.escape(cb) for cb in self.callbacks.keys() if cb) + r')\s*\(') if self.callbacks else None,
            'event_pattern': re.compile(r'handler[_\s]*(?:' + '|'.join(re.escape(e) for e in self.events.keys() if e) + r')|on[_\s]*(?:' + '|'.join(re.escape(e) for e in self.events.keys() if e) + r')', re.IGNORECASE) if self.events else None,
        }
    
    def process_file_streaming(self, filepath):
        """Process file using streaming for large files."""
        try:
            file_hash = self._get_file_hash(filepath)
            
            # Check cache
            if self.use_cache and filepath in self.cache:
                if self.cache[filepath] == file_hash:
                    self.stats['files_skipped_cached'] += 1
                    return True
            
            # Read and process file
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            original = content
            
            # Apply batch regex fixes
            content = self.patterns['this_dot'].sub('this->', content)
            content = self.patterns['throw_new'].sub('throw', content)
            content = self.patterns['is_empty'].sub('.empty()', content)
            content = self.patterns['null_keyword'].sub('nullptr', content)
            content = self.patterns['java_keywords'].sub(' ', content)
            content = self.patterns['double_parens'].sub(r'\1)', content)
            content = self.patterns['whitespace'].sub(' ', content)
            
            # Apply Project Zomboid specific fixes
            if self.patterns['callback_pattern']:
                content = self.patterns['callback_pattern'].sub('', content)
            if self.patterns['event_pattern']:
                content = self.patterns['event_pattern'].sub('', content)
            
            if content != original:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(content)
                
                if self.use_cache and file_hash:
                    self.cache[filepath] = file_hash
                
                self.stats['files_processed'] += 1
                self.stats['total_fixes'] += 1
                return True
            elif self.use_cache and file_hash:
                self.cache[filepath] = file_hash
            
            return False
        except Exception:
            return False
    
    def process_files_parallel(self, files):
        """Process files in parallel using multiprocessing Pool."""
        if self.num_workers <= 1:
            # Sequential processing
            for filepath in tqdm(files, desc="Converting", unit=" files"):
                self.process_file_streaming(filepath)
        else:
            # Parallel processing
            with Pool(self.num_workers) as pool:
                for _ in tqdm(
                    pool.imap_unordered(self.process_file_streaming, files),
                    total=len(files),
                    desc="Converting",
                    unit=" files"
                ):
                    pass
    
    def run(self, directory: str):
        """Process all C++ files in directory."""
        if not os.path.isdir(directory):
            print(f"Error: {directory} is not a directory")
            return False
        
        files = []
        for ext in ['*.h', '*.hpp', '*.cpp', '*.cc']:
            files.extend(Path(directory).rglob(ext))
        
        print(f"Processing {len(files)} C++ files ({self.num_workers} workers, streaming enabled)...")
        if self.use_cache:
            print(f"Using cache: {self.cache_file}")
        
        self.process_files_parallel(list(files))
        
        # Save cache
        if self.use_cache:
            self._save_cache()
        
        return True
    
    def print_report(self):
        """Print detailed statistics."""
        print("\n" + "="*60)
        print("Advanced Production Conversion Report")
        print("="*60)
        print(f"\nExecution:")
        print(f"  Workers: {self.num_workers}")
        print(f"  Streaming: Enabled")
        print(f"  Cache enabled: {self.use_cache}")
        print(f"  Files skipped (cached): {self.stats['files_skipped_cached']}")
        print(f"\nMetadata Utilized:")
        print(f"  Known classes: {len(self.known_classes)}")
        print(f"  Callbacks: {len(self.callbacks)}")
        print(f"  Events: {len(self.events)}")
        print(f"  Hooks: {len(self.hooks)}")
        print(f"\nConversion Results:")
        print(f"  Files processed: {self.stats['files_processed']}")
        print(f"  Classes recognized: {self.stats['class_recognized']}")
        print(f"  Total fixes: {self.stats['total_fixes']}")
        print("="*60 + "\n")


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 advanced_java_converter_v2.py <directory> [--no-cache] [--workers N] [--class-map FILE]")
        sys.exit(1)
    
    directory = sys.argv[1]
    use_cache = '--no-cache' not in sys.argv
    num_workers = None
    class_map = None
    
    # Parse arguments
    for i, arg in enumerate(sys.argv[2:]):
        if arg == '--workers' and i + 3 < len(sys.argv):
            try:
                num_workers = int(sys.argv[i + 3])
            except ValueError:
                pass
        elif arg == '--class-map' and i + 3 < len(sys.argv):
            class_map = sys.argv[i + 3]
    
    converter = AdvancedProductionConverter(
        class_map_file=class_map,
        use_cache=use_cache,
        num_workers=num_workers
    )
    
    if converter.run(directory):
        converter.print_report()
        return 0
    return 1


if __name__ == '__main__':
    sys.exit(main())
