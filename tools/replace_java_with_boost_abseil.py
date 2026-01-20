#!/usr/bin/env python3
"""
Replace Java implementations with Boost and Abseil C++ equivalents
Systematically converts Java patterns to modern C++ using STL, Boost, and Abseil
"""

import os
import re
import sys
from pathlib import Path
from typing import Tuple

class JavaToBoostAbseilConverter:
    def __init__(self):
        self.stats = {
            'files_processed': 0,
            'files_modified': 0,
            'type_replacements': 0,
            'method_replacements': 0,
            'pattern_replacements': 0,
            'includes_added': 0
        }
        
        # Type mappings to C++/Boost/Abseil
        self.type_mappings = {
            # Java primitive wrappers -> C++ primitives
            r'\bInteger\b': 'int',
            r'\bLong\b': 'int64_t',
            r'\bShort\b': 'int16_t',
            r'\bByte\b': 'uint8_t',
            r'\bFloat\b': 'float',
            r'\bDouble\b': 'double',
            r'\bBoolean\b': 'bool',
            r'\bCharacter\b': 'char',
            
            # Java collections -> STL
            r'\bArrayList\b': 'std::vector',
            r'\bLinkedList\b': 'std::list',
            r'\bHashMap\b': 'std::unordered_map',
            r'\bTreeMap\b': 'std::map',
            r'\bHashSet\b': 'std::unordered_set',
            r'\bTreeSet\b': 'std::set',
            r'\bStack\b': 'std::stack',
            r'\bQueue\b': 'std::queue',
            r'\bDeque\b': 'std::deque',
            r'\bPriorityQueue\b': 'std::priority_queue',
            
            # Java special types
            r'\bString\b': 'std::string',
            r'\bStringBuilder\b': 'std::stringstream',
            r'\bStringBuffer\b': 'std::stringstream',
        }
        
        # Method call replacements
        self.method_replacements = {
            # Collection methods
            r'\.add\(': '.push_back(',
            r'\.remove\(': '.erase(',
            r'\.size\(\)': '.size()',
            r'\.isEmpty\(\)': '.empty()',
            r'\.clear\(\)': '.clear()',
            r'\.get\(': '[',  # Will need special handling
            r'\.contains\(': '.find(',  # Will need special handling
            
            # String methods
            r'\.length\(\)': '.length()',
            r'\.substring\(': '.substr(',
            r'\.charAt\(': '[',
            r'\.indexOf\(': '.find(',
            r'\.lastIndexOf\(': '.rfind(',
            r'\.toLowerCase\(\)': '',  # Use std::transform with tolower
            r'\.toUpperCase\(\)': '',  # Use std::transform with toupper
            r'\.trim\(\)': '',  # Use boost::trim or custom
            r'\.equals\(': ' == ',
            r'\.equalsIgnoreCase\(': '',  # Use boost::iequals
            r'\.startsWith\(': '',  # Use string::starts_with (C++20) or boost
            r'\.endsWith\(': '',  # Use string::ends_with (C++20) or boost
            r'\.split\(': '',  # Use boost::split
            r'\.replace\(': '',  # Use boost::replace_all
            
            # Object methods
            r'\.toString\(\)': '',  # Remove or use stream operators
            r'\.hashCode\(\)': '.hash()',
        }
    
    def add_required_includes(self, content: str) -> Tuple[str, int]:
        """Add necessary C++ headers based on usage"""
        includes_to_add = set()
        count = 0
        
        # Check what's used in the file
        if 'std::vector' in content or 'ArrayList' in content:
            includes_to_add.add('#include <vector>')
        if 'std::list' in content or 'LinkedList' in content:
            includes_to_add.add('#include <list>')
        if 'std::map' in content or 'TreeMap' in content:
            includes_to_add.add('#include <map>')
        if 'std::unordered_map' in content or 'HashMap' in content:
            includes_to_add.add('#include <unordered_map>')
        if 'std::set' in content or 'TreeSet' in content:
            includes_to_add.add('#include <set>')
        if 'std::unordered_set' in content or 'HashSet' in content:
            includes_to_add.add('#include <unordered_set>')
        if 'std::stack' in content or 'Stack' in content:
            includes_to_add.add('#include <stack>')
        if 'std::queue' in content or 'Queue' in content:
            includes_to_add.add('#include <queue>')
        if 'std::string' in content or 'String' in content:
            includes_to_add.add('#include <string>')
        if 'std::stringstream' in content or 'StringBuilder' in content or 'StringBuffer' in content:
            includes_to_add.add('#include <sstream>')
        if 'std::shared_ptr' in content or 'std::make_shared' in content:
            includes_to_add.add('#include <memory>')
        if 'std::optional' in content:
            includes_to_add.add('#include <optional>')
        if 'int64_t' in content or 'int32_t' in content or 'uint8_t' in content:
            includes_to_add.add('#include <cstdint>')
        
        # Check for Boost usage
        if 'boost::' in content:
            if 'trim' in content or 'split' in content:
                includes_to_add.add('#include <boost/algorithm/string.hpp>')
            if 'boost::optional' in content:
                includes_to_add.add('#include <boost/optional.hpp>')
        
        # Check for Abseil usage
        if 'absl::' in content:
            if 'absl::string_view' in content:
                includes_to_add.add('#include "absl/strings/string_view.h"')
            if 'StrCat' in content or 'StrAppend' in content:
                includes_to_add.add('#include "absl/strings/str_cat.h"')
            if 'StrSplit' in content:
                includes_to_add.add('#include "absl/strings/str_split.h"')
        
        # Find where to insert includes (after #pragma once or first #include)
        lines = content.split('\n')
        insert_pos = 0
        
        for i, line in enumerate(lines):
            if line.strip().startswith('#pragma once'):
                insert_pos = i + 1
                break
            elif line.strip().startswith('#include'):
                insert_pos = i
                break
        
        # Add includes that don't already exist
        for include in sorted(includes_to_add):
            if include not in content:
                lines.insert(insert_pos, include)
                insert_pos += 1
                count += 1
        
        return '\n'.join(lines), count
    
    def replace_types(self, content: str) -> Tuple[str, int]:
        """Replace Java types with C++ equivalents"""
        count = 0
        modified = content
        
        for java_type, cpp_type in self.type_mappings.items():
            pattern = re.compile(java_type)
            matches = pattern.findall(modified)
            if matches:
                modified = pattern.sub(cpp_type, modified)
                count += len(matches)
        
        return modified, count
    
    def replace_null_with_nullptr(self, content: str) -> Tuple[str, int]:
        """Replace null with nullptr"""
        pattern = r'\bnull\b'
        matches = re.findall(pattern, content)
        modified = re.sub(pattern, 'nullptr', content)
        return modified, len(matches)
    
    def replace_instanceof(self, content: str) -> Tuple[str, int]:
        """Replace instanceof with dynamic_cast checks"""
        pattern = r'(\w+)\s+instanceof\s+(\w+)'
        matches = re.findall(pattern, content)
        # Replace with: dynamic_cast<Type*>(obj) != nullptr
        modified = re.sub(pattern, r'dynamic_cast<\2*>(\1) != nullptr', content)
        return modified, len(matches)
    
    def replace_throw_new(self, content: str) -> Tuple[str, int]:
        """Replace 'throw new Exception' with 'throw Exception'"""
        pattern = r'throw\s+new\s+'
        matches = re.findall(pattern, content)
        modified = re.sub(pattern, 'throw ', content)
        return modified, len(matches)
    
    def replace_new_with_make_shared(self, content: str) -> Tuple[str, int]:
        """Replace 'new ClassName()' with 'std::make_shared<ClassName>()'"""
        # Pattern: new ClassName(args)
        pattern = r'new\s+(\w+)\s*\('
        matches = re.findall(pattern, content)
        modified = re.sub(pattern, r'std::make_shared<\1>(', content)
        return modified, len(matches)
    
    def replace_final_with_const(self, content: str) -> Tuple[str, int]:
        """Replace 'final' keyword with 'const'"""
        pattern = r'\bfinal\s+'
        matches = re.findall(pattern, content)
        modified = re.sub(pattern, 'const ', content)
        return modified, len(matches)
    
    def replace_synchronized(self, content: str) -> Tuple[str, int]:
        """Replace synchronized with mutex (commented)"""
        pattern = r'\bsynchronized\b'
        matches = re.findall(pattern, content)
        modified = re.sub(pattern, '/* synchronized - TODO: add std::mutex */', content)
        return modified, len(matches)
    
    def replace_extends_implements(self, content: str) -> Tuple[str, int]:
        """Replace extends/implements with C++ inheritance"""
        count = 0
        
        # extends -> : public
        pattern = r'\bextends\s+'
        matches = re.findall(pattern, content)
        content = re.sub(pattern, ': public ', content)
        count += len(matches)
        
        # implements -> : public (multiple inheritance)
        pattern = r'\bimplements\s+'
        matches = re.findall(pattern, content)
        content = re.sub(pattern, ', public ', content)
        count += len(matches)
        
        return content, count
    
    def replace_collection_methods(self, content: str) -> Tuple[str, int]:
        """Replace Java collection methods with C++ equivalents"""
        count = 0
        
        # .add() -> .push_back()
        pattern = r'\.add\('
        matches = re.findall(pattern, content)
        content = re.sub(pattern, '.push_back(', content)
        count += len(matches)
        
        # .isEmpty() -> .empty()
        pattern = r'\.isEmpty\(\)'
        matches = re.findall(pattern, content)
        content = re.sub(pattern, '.empty()', content)
        count += len(matches)
        
        # .size() is same in C++, no change needed
        
        return content, count
    
    def replace_string_methods(self, content: str) -> Tuple[str, int]:
        """Replace Java String methods with C++ equivalents"""
        count = 0
        
        # .equals() -> ==
        pattern = r'\.equals\('
        matches = re.findall(pattern, content)
        content = re.sub(pattern, ' == ', content)
        count += len(matches)
        
        # .length() is same in C++
        
        # .substring() -> .substr()
        pattern = r'\.substring\('
        matches = re.findall(pattern, content)
        content = re.sub(pattern, '.substr(', content)
        count += len(matches)
        
        # Remove .toString() calls (not needed in C++)
        pattern = r'\.toString\(\)'
        matches = re.findall(pattern, content)
        content = re.sub(pattern, '', content)
        count += len(matches)
        
        return content, count
    
    def process_file(self, filepath: Path) -> bool:
        """Process a single file"""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            original_content = content
            total_replacements = 0
            
            # Apply all transformations
            content, count = self.replace_types(content)
            total_replacements += count
            self.stats['type_replacements'] += count
            
            content, count = self.replace_null_with_nullptr(content)
            total_replacements += count
            
            content, count = self.replace_instanceof(content)
            total_replacements += count
            
            content, count = self.replace_throw_new(content)
            total_replacements += count
            
            content, count = self.replace_new_with_make_shared(content)
            total_replacements += count
            self.stats['pattern_replacements'] += count
            
            content, count = self.replace_final_with_const(content)
            total_replacements += count
            
            content, count = self.replace_synchronized(content)
            total_replacements += count
            
            content, count = self.replace_extends_implements(content)
            total_replacements += count
            
            content, count = self.replace_collection_methods(content)
            total_replacements += count
            self.stats['method_replacements'] += count
            
            content, count = self.replace_string_methods(content)
            total_replacements += count
            self.stats['method_replacements'] += count
            
            # Add required includes
            content, count = self.add_required_includes(content)
            self.stats['includes_added'] += count
            
            # Write back if modified
            if content != original_content:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(content)
                return True
            
            return False
            
        except Exception as e:
            print(f"Error processing {filepath}: {e}")
            return False
    
    def process_directory(self, directory: str):
        """Process all C++ files in directory"""
        dir_path = Path(directory)
        
        print(f"Processing directory: {dir_path}")
        print()
        
        # Find all .h and .cpp files
        h_files = list(dir_path.rglob('*.h'))
        cpp_files = list(dir_path.rglob('*.cpp'))
        all_files = h_files + cpp_files
        
        print(f"Found {len(all_files)} files to process")
        print()
        
        for i, filepath in enumerate(all_files, 1):
            if i % 500 == 0:
                print(f"Progress: {i}/{len(all_files)} files processed...")
            
            self.stats['files_processed'] += 1
            if self.process_file(filepath):
                self.stats['files_modified'] += 1
        
        self.print_report()
    
    def print_report(self):
        """Print conversion report"""
        print("\n" + "="*60)
        print("Java to Boost/Abseil Conversion Report")
        print("="*60)
        print(f"Files processed: {self.stats['files_processed']}")
        print(f"Files modified: {self.stats['files_modified']}")
        print(f"\nReplacements made:")
        print(f"  Type replacements: {self.stats['type_replacements']}")
        print(f"  Method replacements: {self.stats['method_replacements']}")
        print(f"  Pattern replacements: {self.stats['pattern_replacements']}")
        print(f"  Includes added: {self.stats['includes_added']}")
        print("="*60 + "\n")


def main():
    if len(sys.argv) < 2:
        print("Usage: python replace_java_with_boost_abseil.py <directory>")
        print("Example: python replace_java_with_boost_abseil.py Convert2Cpp")
        sys.exit(1)
    
    directory = sys.argv[1]
    
    if not os.path.exists(directory):
        print(f"Error: Directory does not exist: {directory}")
        sys.exit(1)
    
    converter = JavaToBoostAbseilConverter()
    converter.process_directory(directory)


if __name__ == '__main__':
    main()
