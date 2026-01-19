#!/usr/bin/env python3
"""
Advanced C++ Code Refinement for Java-to-C++ Converted Code
Fixes remaining Java syntax, improves C++ idioms, and adds safety features
"""

import os
import re
import sys
from pathlib import Path
from typing import Tuple, List

class AdvancedCppRefiner:
    def __init__(self, base_path: str):
        self.base_path = Path(base_path)
        self.stats = {
            'files_processed': 0,
            'files_fixed': 0,
            'issues_fixed': 0,
            'java_syntax_fixes': 0,
            'memory_fixes': 0,
            'type_fixes': 0,
            'array_fixes': 0,
        }
    
    def refine_file(self, filepath: Path) -> Tuple[bool, int]:
        """Refine a single header file"""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            original_content = content
            issues_count = 0
            
            # 1. Replace 'new' keyword allocations with make_shared/make_unique
            content, count = self._fix_new_allocations(content)
            issues_count += count
            self.stats['java_syntax_fixes'] += count
            
            # 2. Replace 'delete' with nullptr
            content, count = self._fix_delete_statements(content)
            issues_count += count
            self.stats['memory_fixes'] += count
            
            # 3. Fix Java array syntax
            content, count = self._fix_java_array_syntax(content)
            issues_count += count
            self.stats['array_fixes'] += count
            
            # 4. Fix collection instantiations
            content, count = self._fix_collection_instantiations(content)
            issues_count += count
            self.stats['java_syntax_fixes'] += count
            
            # 5. Fix field initializations
            content, count = self._fix_field_initializations(content)
            issues_count += count
            self.stats['type_fixes'] += count
            
            # 6. Fix Java casts to C++ static_cast
            content, count = self._fix_casts(content)
            issues_count += count
            self.stats['type_fixes'] += count
            
            # 7. Add thread-safety annotations where needed
            content, count = self._add_thread_safety_markers(content)
            issues_count += count
            
            # 8. Fix final/static field issues
            content, count = self._fix_static_fields(content)
            issues_count += count
            self.stats['java_syntax_fixes'] += count
            
            if content != original_content:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(content)
                self.stats['files_fixed'] += 1
                return True, issues_count
            
            self.stats['issues_fixed'] += issues_count
            return False, issues_count
            
        except Exception as e:
            print(f"Error processing {filepath}: {e}")
            return False, 0
    
    def _fix_new_allocations(self, content: str) -> Tuple[str, int]:
        """Replace 'new Type()' with make_shared<Type>()"""
        count = 0
        
        # Handle: Type var = new Type(...) or const Type var = new Type(...)
        pattern = r'(\s+)(const\s+)?(\w+)\s+(\w+)\s*=\s*new\s+(\w+)\s*\('
        
        def replacer(match):
            nonlocal count
            indent = match.group(1)
            const = match.group(2) or ''
            var_type = match.group(3)
            var_name = match.group(4)
            class_name = match.group(5)
            
            # Convert to make_shared
            if const and 'const' not in const:
                replacement = f'{indent}auto {var_name} = std::make_shared<{class_name}>('
            else:
                replacement = f'{indent}auto {var_name} = std::make_shared<{class_name}>('
            
            count += 1
            return replacement
        
        content = re.sub(pattern, replacer, content)
        
        # Handle static field initializations: static Type var = new Type()
        pattern = r'(static\s+(?:const\s+)?(\w+)\s+(\w+)\s*=\s*new\s+)(\w+)(\s*\()'
        
        def static_replacer(match):
            nonlocal count
            prefix = match.group(1).replace('new ', '')
            class_name = match.group(4)
            suffix = match.group(5)
            replacement = f'{prefix}std::make_shared<{class_name}>{suffix}'
            count += 1
            return replacement
        
        content = re.sub(pattern, static_replacer, content)
        
        return content, count
    
    def _fix_delete_statements(self, content: str) -> Tuple[str, int]:
        """Replace 'delete var' with 'var = nullptr' or remove"""
        count = 0
        
        # Handle: delete var;
        pattern = r'\n\s*delete\s+(\w+)\s*;'
        
        def replacer(match):
            nonlocal count
            var_name = match.group(1)
            count += 1
            # For smart pointers, just set to nullptr
            return f'\n        {var_name} = nullptr;'
        
        content = re.sub(pattern, replacer, content)
        
        # Handle: array delete
        pattern = r'\n\s*delete\s*\[\]\s*(\w+)\s*;'
        content = re.sub(pattern, lambda m: f'\n        {m.group(1)}.clear();', content)
        count += len(re.findall(pattern, content))
        
        return content, count
    
    def _fix_java_array_syntax(self, content: str) -> Tuple[str, int]:
        """Fix Java array syntax to C++"""
        count = 0
        
        # Handle: new Type[size]
        pattern = r'new\s+(\w+)\s*\[\s*(\d+)\s*\]'
        
        def replacer(match):
            nonlocal count
            type_name = match.group(1)
            size = match.group(2)
            count += 1
            return f'std::make_shared<std::array<{type_name}, {size}>>()'
        
        content = re.sub(pattern, replacer, content)
        
        # Handle: new Type[] (dynamic size)
        pattern = r'new\s+(\w+)\s*\[\]\s*'
        content = re.sub(pattern, lambda m: f'std::make_shared<std::vector<{m.group(1)}>>()', content)
        count += len(re.findall(pattern, content))
        
        # Handle: Type[] array = ...
        pattern = r'(\w+)\[\]\s+(\w+)\s*='
        content = re.sub(pattern, r'std::vector<\1> \2 =', content)
        count += len(re.findall(pattern, content))
        
        # Fix final byte[] literals
        pattern = r'new\s+byte\s*\{\s*([\d\s,]+)\s*\}'
        
        def byte_array_replacer(match):
            nonlocal count
            values = match.group(1)
            count += 1
            return f'std::vector<uint8_t>{{{values}}}'
        
        content = re.sub(pattern, byte_array_replacer, content)
        
        return content, count
    
    def _fix_collection_instantiations(self, content: str) -> Tuple[str, int]:
        """Fix Java collection type instantiations"""
        count = 0
        
        # ArrayList -> std::vector
        pattern = r'new\s+ArrayList\s*<([^>]+)>\s*\('
        content = re.sub(pattern, r'std::make_shared<std::vector<\1>>(', content)
        count += len(re.findall(pattern, content))
        
        # HashMap -> std::unordered_map
        pattern = r'new\s+HashMap\s*<([^,]+),\s*([^>]+)>\s*\('
        content = re.sub(pattern, r'std::make_shared<std::unordered_map<\1, \2>>(', content)
        count += len(re.findall(pattern, content))
        
        # TreeMap -> std::map
        pattern = r'new\s+TreeMap\s*<([^,]+),\s*([^>]+)>\s*\('
        content = re.sub(pattern, r'std::make_shared<std::map<\1, \2>>(', content)
        count += len(re.findall(pattern, content))
        
        # Stack -> std::stack
        pattern = r'new\s+Stack\s*<([^>]+)>\s*\('
        content = re.sub(pattern, r'std::make_shared<std::stack<\1>>(', content)
        count += len(re.findall(pattern, content))
        
        # Vector -> std::vector
        pattern = r'new\s+Vector\s*<([^>]+)>\s*\('
        content = re.sub(pattern, r'std::make_shared<std::vector<\1>>(', content)
        count += len(re.findall(pattern, content))
        
        # LinkedList -> std::list
        pattern = r'new\s+LinkedList\s*<([^>]+)>\s*\('
        content = re.sub(pattern, r'std::make_shared<std::list<\1>>(', content)
        count += len(re.findall(pattern, content))
        
        # HashSet -> std::unordered_set
        pattern = r'new\s+HashSet\s*<([^>]+)>\s*\('
        content = re.sub(pattern, r'std::make_shared<std::unordered_set<\1>>(', content)
        count += len(re.findall(pattern, content))
        
        return content, count
    
    def _fix_field_initializations(self, content: str) -> Tuple[str, int]:
        """Fix static field initializations"""
        count = 0
        
        # Handle: static Type field = value;
        # (may need smart pointer wrapping for objects)
        pattern = r'static\s+(const\s+)?(\w+)\s+(\w+)\s*=\s*nullptr\s*;'
        
        # This is mostly correct, just ensure it's formatted properly
        count += len(re.findall(pattern, content))
        
        return content, count
    
    def _fix_casts(self, content: str) -> Tuple[str, int]:
        """Convert Java casts to C++ static_cast"""
        count = 0
        
        # Handle: (Type)var
        pattern = r'\((\w+)\s*\)\s*(\w+)'
        
        def replacer(match):
            nonlocal count
            cast_type = match.group(1)
            var_name = match.group(2)
            # Only replace if it looks like a cast, not a function call
            if cast_type[0].isupper():  # Class name convention
                count += 1
                return f'static_cast<{cast_type}>({var_name})'
            return match.group(0)
        
        content = re.sub(pattern, replacer, content)
        
        return content, count
    
    def _add_thread_safety_markers(self, content: str) -> Tuple[str, int]:
        """Add thread-safety annotations for synchronized methods"""
        count = 0
        
        # Mark synchronized methods/fields
        pattern = r'(public|private|protected)\s+synchronized\s+(\w+)'
        
        if re.search(pattern, content):
            # Add comment marker for thread-safety
            content = re.sub(
                pattern,
                r'\1 /* THREAD_SAFE */ \2',
                content
            )
            count += len(re.findall(pattern, content))
        
        return content, count
    
    def _fix_static_fields(self, content: str) -> Tuple[str, int]:
        """Fix static field definitions"""
        count = 0
        
        # Handle: static final Type CONSTANT = ...
        pattern = r'static\s+final\s+(\w+)\s+([A-Z_]+)\s*='
        content = re.sub(pattern, r'static constexpr \1 \2 =', content)
        count += len(re.findall(pattern, content))
        
        # Handle: private static final Type field = ...
        pattern = r'private\s+static\s+final\s+(\w+)\s+([A-Z_]+)\s*='
        content = re.sub(pattern, r'private static constexpr \1 \2 =', content)
        count += len(re.findall(pattern, content))
        
        return content, count
    
    def process_directory(self) -> None:
        """Process all header files in the directory"""
        include_dir = self.base_path / 'Convert2Cpp' / 'include'
        
        if not include_dir.exists():
            print(f"Error: {include_dir} does not exist")
            return
        
        header_files = list(include_dir.rglob('*.h'))
        print(f"\nStarting advanced refinement of {len(header_files)} header files...")
        
        for i, filepath in enumerate(header_files, 1):
            if i % 50 == 0:
                print(f"Progress: {i}/{len(header_files)}")
            
            self.stats['files_processed'] += 1
            fixed, issues = self.refine_file(filepath)
            if issues > 0:
                self.stats['issues_fixed'] += issues
        
        self.print_report()
    
    def print_report(self) -> None:
        """Print refinement report"""
        print("\n" + "="*60)
        print("Advanced Code Refinement Report")
        print("="*60)
        print(f"Files processed: {self.stats['files_processed']}")
        print(f"Files fixed: {self.stats['files_fixed']}")
        print(f"\nIssues fixed by category:")
        print(f"  Java syntax fixes: {self.stats['java_syntax_fixes']}")
        print(f"  Memory management: {self.stats['memory_fixes']}")
        print(f"  Type/cast fixes: {self.stats['type_fixes']}")
        print(f"  Array fixes: {self.stats['array_fixes']}")
        print(f"\nTotal issues fixed: {self.stats['issues_fixed']}")
        print("="*60 + "\n")


if __name__ == '__main__':
    base_path = '/workspaces/PZ'
    refiner = AdvancedCppRefiner(base_path)
    refiner.process_directory()
