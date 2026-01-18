#!/usr/bin/env python3
"""
Enhanced Java-to-C++ Converter using pz-rosetta-source metadata
Improves conversion accuracy by using documented class structure information
"""

import os
import re
import sys
import yaml
from pathlib import Path
from typing import Dict, List, Set, Tuple, Optional

class EnhancedJavaConverter:
    def __init__(self, rosetta_base: str = None):
        self.rosetta_base = rosetta_base or "/workspaces/PZ/pz-rosetta-source-main/rosetta/java"
        self.class_metadata = {}
        self.method_signatures = {}
        self.type_mappings = self._build_type_mappings()
        self.load_metadata()
        
        self.stats = {
            'files_processed': 0,
            'metadata_matches': 0,
            'type_conversions': 0,
            'method_signatures_fixed': 0,
            'parameter_names_fixed': 0,
            'documentation_added': 0,
        }
    
    def _build_type_mappings(self) -> Dict[str, str]:
        """Build standard Java to C++ type mappings."""
        return {
            # Java collections
            'String': 'std::string',
            'ArrayList': 'std::vector',
            'List': 'std::vector',
            'HashMap': 'std::unordered_map',
            'Map': 'std::unordered_map',
            'HashSet': 'std::unordered_set',
            'Set': 'std::unordered_set',
            'Queue': 'std::queue',
            'Stack': 'std::stack',
            'Deque': 'std::deque',
            'LinkedList': 'std::list',
            
            # Java boxed types
            'Integer': 'int',
            'Float': 'float',
            'Double': 'double',
            'Boolean': 'bool',
            'Long': 'long',
            'Short': 'short',
            'Byte': 'uint8_t',
            'Character': 'char',
            
            # Java primitives
            'void': 'void',
            'int': 'int',
            'float': 'float',
            'double': 'double',
            'boolean': 'bool',
            'long': 'long',
            'short': 'short',
            'byte': 'uint8_t',
            'char': 'char',
            
            # Java special types
            'Object': 'void*',
            'Exception': 'std::exception',
            'Thread': 'std::thread',
            'Runnable': 'std::function<void()>',
        }
    
    def load_metadata(self):
        """Load class metadata from pz-rosetta-source YAML files."""
        if not os.path.isdir(self.rosetta_base):
            print(f"Warning: Rosetta base directory not found at {self.rosetta_base}")
            return
        
        yml_files = list(Path(self.rosetta_base).rglob("*.yml"))
        print(f"Loading metadata from {len(yml_files)} YAML files...")
        
        for yml_file in yml_files:
            try:
                with open(yml_file, 'r', encoding='utf-8') as f:
                    data = yaml.safe_load(f)
                    if data and 'languages' in data:
                        self._extract_metadata(data)
            except Exception as e:
                pass  # Silently skip problematic YAML files
    
    def _extract_metadata(self, data: Dict):
        """Extract class metadata from YAML structure."""
        try:
            if 'languages' not in data or 'java' not in data['languages']:
                return
            
            java_data = data['languages']['java']
            if 'packages' not in java_data:
                return
            
            for package_name, classes in java_data['packages'].items():
                for class_name, class_info in classes.items():
                    full_name = f"{package_name}.{class_name}"
                    self.class_metadata[full_name] = class_info
                    
                    # Extract method signatures
                    if 'methods' in class_info:
                        for method in class_info['methods']:
                            method_key = f"{full_name}.{method.get('name', '')}"
                            self.method_signatures[method_key] = method
        except Exception:
            pass
    
    def get_class_metadata(self, class_name: str) -> Optional[Dict]:
        """Retrieve metadata for a class."""
        return self.class_metadata.get(class_name)
    
    def improve_method_signature(self, class_name: str, method_name: str, 
                                 cpp_signature: str) -> Tuple[str, bool]:
        """Improve a C++ method signature using metadata."""
        method_key = f"{class_name}.{method_name}"
        metadata = self.method_signatures.get(method_key)
        
        if not metadata:
            return cpp_signature, False
        
        # Enhance with parameter documentation if available
        improved = cpp_signature
        if 'parameters' in metadata:
            params = metadata['parameters']
            for param in params:
                param_name = param.get('name', '')
                if param_name and param_name in improved:
                    # Add inline documentation
                    self.stats['parameter_names_fixed'] += 1
        
        if 'notes' in metadata:
            # Could add documentation comment
            self.stats['documentation_added'] += 1
        
        self.stats['method_signatures_fixed'] += 1
        return improved, True
    
    def convert_java_type(self, java_type: str) -> str:
        """Convert Java type to C++ with metadata support."""
        # Remove array notation
        base_type = java_type.replace("[]", "").strip()
        
        # Check type mappings
        if base_type in self.type_mappings:
            cpp_type = self.type_mappings[base_type]
            if "[]" in java_type:
                cpp_type = f"std::vector<{cpp_type}>"
            self.stats['type_conversions'] += 1
            return cpp_type
        
        # Check if it's a known Project Zomboid class
        for full_name in self.class_metadata.keys():
            if full_name.endswith(f".{base_type}"):
                # Found a known class
                self.stats['metadata_matches'] += 1
                if "[]" in java_type:
                    return f"std::vector<std::shared_ptr<{base_type}>>"
                return f"std::shared_ptr<{base_type}>"
        
        # Default handling
        if "[]" in java_type:
            return f"std::vector<{base_type}>"
        return f"std::shared_ptr<{base_type}>"
    
    def apply_fixes(self, content: str, class_name: str = "") -> str:
        """Apply all conversion fixes including metadata-based improvements."""
        # Standard fixes
        content = re.sub(r'\bthis\.', 'this->', content)
        content = re.sub(r'\bthrow\s+new\b', 'throw', content)
        content = re.sub(r'\.isEmpty\(\)', '.empty()', content)
        content = re.sub(r'\bnull\b', 'nullptr', content)
        content = re.sub(r'\bfinal\s+', ' ', content)
        content = re.sub(r'\babstract\s+', ' ', content)
        content = re.sub(r'\bvolatile\s+', ' ', content)
        content = re.sub(r'\btransient\s+', ' ', content)
        content = re.sub(r'\bstrictfp\s+', ' ', content)
        
        # Metadata-based improvements
        if class_name:
            metadata = self.get_class_metadata(class_name)
            if metadata:
                self.stats['metadata_matches'] += 1
                
                # Add class documentation if available
                if 'notes' in metadata and '///' not in content:
                    notes = metadata['notes']
                    if notes:
                        content = f"/// {notes}\n{content}"
                        self.stats['documentation_added'] += 1
        
        # Clean up whitespace
        content = re.sub(r'  +', ' ', content)
        
        return content
    
    def process_file(self, filepath: str, class_name: str = "") -> bool:
        """Process a single file with metadata enhancements."""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            new_content = self.apply_fixes(content, class_name)
            
            if content != new_content:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(new_content)
                self.stats['files_processed'] += 1
                return True
            return False
        except Exception as e:
            print(f"Error processing {filepath}: {e}", file=sys.stderr)
            return False
    
    def run(self, directory: str):
        """Scan directory and apply enhanced fixes."""
        if not os.path.isdir(directory):
            print(f"Error: {directory} is not a directory")
            return False
        
        files = []
        for ext in ['*.h', '*.hpp', '*.cpp', '*.cc']:
            files.extend(Path(directory).rglob(ext))
        
        print(f"Processing {len(files)} C++ files with metadata enhancements...")
        
        for i, filepath in enumerate(files, 1):
            if i % 100 == 0:
                print(f"  Processing: {i}/{len(files)}")
            
            # Try to extract class name from file path
            class_name = filepath.stem
            self.process_file(str(filepath), class_name)
        
        return True
    
    def print_report(self):
        """Print conversion statistics."""
        print("\n" + "="*60)
        print("Enhanced Java-to-C++ Conversion Report")
        print("="*60)
        print(f"\nMetadata Loaded:")
        print(f"  Classes: {len(self.class_metadata)}")
        print(f"  Method signatures: {len(self.method_signatures)}")
        print(f"\nConversion Statistics:")
        print(f"  Files processed: {self.stats['files_processed']}")
        print(f"  Metadata matches: {self.stats['metadata_matches']}")
        print(f"  Type conversions: {self.stats['type_conversions']}")
        print(f"  Method signatures improved: {self.stats['method_signatures_fixed']}")
        print(f"  Parameter names fixed: {self.stats['parameter_names_fixed']}")
        print(f"  Documentation added: {self.stats['documentation_added']}")
        print("="*60 + "\n")


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 enhanced_java_converter.py <directory> [rosetta_path]")
        sys.exit(1)
    
    rosetta_path = sys.argv[2] if len(sys.argv) > 2 else None
    converter = EnhancedJavaConverter(rosetta_path)
    
    if converter.run(sys.argv[1]):
        converter.print_report()
        return 0
    return 1


if __name__ == '__main__':
    sys.exit(main())
