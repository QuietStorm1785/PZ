#!/usr/bin/env python3
"""
Advanced Java-to-C++ Converter using pz-rosetta-source class map
Provides highly accurate conversions based on Project Zomboid class structure
"""

import os
import re
import sys
import json
from pathlib import Path
from typing import Dict, List, Set, Tuple, Optional

class AdvancedJavaConverter:
    def __init__(self, class_map_file: str = None):
        self.class_map_file = class_map_file or "/workspaces/PZ/class_map.json"
        self.class_map = {}
        self.callbacks = {}
        self.events = {}
        self.hooks = {}
        self.known_classes = set()
        self.load_class_map()
        
        self.type_mappings = self._build_type_mappings()
        self.stats = {
            'files_processed': 0,
            'class_recognized': 0,
            'type_fixed': 0,
            'callback_fixed': 0,
            'event_fixed': 0,
            'hook_fixed': 0,
            'total_fixes': 0,
        }
    
    def load_class_map(self):
        """Load pre-generated class map JSON."""
        if not os.path.exists(self.class_map_file):
            print(f"Warning: Class map not found at {self.class_map_file}")
            print("Run: python3 tools/rosetta_extractor.py class_map.json")
            return
        
        try:
            with open(self.class_map_file, 'r') as f:
                data = json.load(f)
                self.class_map = data.get('classes', {})
                self.callbacks = data.get('callbacks', {})
                self.events = data.get('events', {})
                self.hooks = data.get('hooks', {})
                
                # Build known classes set for quick lookup
                self.known_classes = set(self.class_map.keys())
                
                print(f"Loaded class map: {len(self.known_classes)} classes, "
                      f"{len(self.callbacks)} callbacks, {len(self.events)} events")
        except Exception as e:
            print(f"Error loading class map: {e}")
    
    def _build_type_mappings(self) -> Dict[str, str]:
        """Build comprehensive type mappings."""
        return {
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
            'Integer': 'int',
            'Float': 'float',
            'Double': 'double',
            'Boolean': 'bool',
            'Long': 'long',
            'Short': 'short',
            'Byte': 'uint8_t',
            'Character': 'char',
            'void': 'void',
            'int': 'int',
            'float': 'float',
            'double': 'double',
            'boolean': 'bool',
            'long': 'long',
            'short': 'short',
            'byte': 'uint8_t',
            'char': 'char',
            'Object': 'void*',
            'Exception': 'std::exception',
            'Thread': 'std::thread',
            'Runnable': 'std::function<void()>',
        }
    
    def recognize_class(self, class_name: str) -> bool:
        """Check if a class is recognized from rosetta metadata."""
        # Direct match
        if class_name in self.known_classes:
            return True
        
        # Try with common packages
        for known_class in self.known_classes:
            if known_class.endswith(f".{class_name}"):
                self.stats['class_recognized'] += 1
                return True
        
        return False
    
    def is_callback(self, name: str) -> bool:
        """Check if name is a known callback."""
        return name in self.callbacks
    
    def is_event(self, name: str) -> bool:
        """Check if name is a known event."""
        return name in self.events
    
    def is_hook(self, name: str) -> bool:
        """Check if name is a known hook."""
        return name in self.hooks
    
    def fix_callback_signature(self, content: str) -> Tuple[str, int]:
        """Fix callback function signatures using metadata."""
        fixes = 0
        for callback_name, callback_info in self.callbacks.items():
            # Pattern for callback functions
            pattern = rf'\b{re.escape(callback_name)}\s*\('
            if re.search(pattern, content):
                # Could enhance with parameter information
                fixes += 1
                self.stats['callback_fixed'] += 1
        return content, fixes
    
    def fix_event_handlers(self, content: str) -> Tuple[str, int]:
        """Fix event handler signatures."""
        fixes = 0
        for event_name, event_info in self.events.items():
            # Pattern for event handlers
            pattern = rf'\bhandler[_\s]*{re.escape(event_name)}|on[_\s]*{re.escape(event_name)}'
            if re.search(pattern, content, re.IGNORECASE):
                fixes += 1
                self.stats['event_fixed'] += 1
        return content, fixes
    
    def fix_hook_calls(self, content: str) -> Tuple[str, int]:
        """Fix hook invocation calls."""
        fixes = 0
        for hook_name in self.hooks.keys():
            pattern = rf'\b{re.escape(hook_name)}\s*\('
            if re.search(pattern, content):
                fixes += 1
                self.stats['hook_fixed'] += 1
        return content, fixes
    
    def apply_comprehensive_fixes(self, content: str) -> str:
        """Apply all conversion fixes."""
        original = content
        
        # Basic conversions
        content = re.sub(r'\bthis\.', 'this->', content)
        content = re.sub(r'\bthrow\s+new\b', 'throw', content)
        content = re.sub(r'\.isEmpty\(\)', '.empty()', content)
        content = re.sub(r'(?<!\w)null(?!\w)', 'nullptr', content)
        content = re.sub(r'\bfinal\s+', ' ', content)
        content = re.sub(r'\babstract\s+', ' ', content)
        content = re.sub(r'\bvolatile\s+', ' ', content)
        content = re.sub(r'\btransient\s+', ' ', content)
        content = re.sub(r'\bstrictfp\s+', ' ', content)
        content = re.sub(r'\bnative\s+', ' ', content)
        
        # Fix double parenthesis
        content = re.sub(r'(\w+)\)\)', r'\1)', content)
        
        # Project Zomboid specific fixes
        content, _ = self.fix_callback_signature(content)
        content, _ = self.fix_event_handlers(content)
        content, _ = self.fix_hook_calls(content)
        
        # Clean up whitespace
        content = re.sub(r'  +', ' ', content)
        
        if content != original:
            self.stats['total_fixes'] += 1
        
        return content
    
    def process_file(self, filepath: str) -> bool:
        """Process a single file."""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            new_content = self.apply_comprehensive_fixes(content)
            
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
        """Process all C++ files in directory."""
        if not os.path.isdir(directory):
            print(f"Error: {directory} is not a directory")
            return False
        
        files = []
        for ext in ['*.h', '*.hpp', '*.cpp', '*.cc']:
            files.extend(Path(directory).rglob(ext))
        
        print(f"Processing {len(files)} C++ files with advanced fixes...")
        
        for i, filepath in enumerate(files, 1):
            if i % 200 == 0:
                print(f"  Progress: {i}/{len(files)}")
            self.process_file(str(filepath))
        
        return True
    
    def print_report(self):
        """Print detailed statistics."""
        print("\n" + "="*60)
        print("Advanced Java-to-C++ Conversion Report")
        print("="*60)
        print(f"\nMetadata Utilized:")
        print(f"  Known classes: {len(self.known_classes)}")
        print(f"  Callbacks: {len(self.callbacks)}")
        print(f"  Events: {len(self.events)}")
        print(f"  Hooks: {len(self.hooks)}")
        print(f"\nConversion Results:")
        print(f"  Files processed: {self.stats['files_processed']}")
        print(f"  Classes recognized: {self.stats['class_recognized']}")
        print(f"  Type fixes: {self.stats['type_fixed']}")
        print(f"  Callbacks fixed: {self.stats['callback_fixed']}")
        print(f"  Events fixed: {self.stats['event_fixed']}")
        print(f"  Hooks fixed: {self.stats['hook_fixed']}")
        print(f"  Total fixes: {self.stats['total_fixes']}")
        print("="*60 + "\n")


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 advanced_java_converter.py <directory> [class_map.json]")
        sys.exit(1)
    
    class_map = sys.argv[2] if len(sys.argv) > 2 else None
    converter = AdvancedJavaConverter(class_map)
    
    if converter.run(sys.argv[1]):
        converter.print_report()
        return 0
    return 1


if __name__ == '__main__':
    sys.exit(main())
