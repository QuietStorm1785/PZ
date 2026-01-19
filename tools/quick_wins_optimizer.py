#!/usr/bin/env python3
"""
Quick Wins Optimization Script
Implements high-impact, low-effort improvements:
1. Add const to getter methods
2. Add noexcept specifications
3. Adopt std::string_view for string parameters
"""

import os
import re
from pathlib import Path
from typing import Tuple, List

class QuickWinsOptimizer:
    def __init__(self):
        self.stats = {
            'const_added': 0,
            'noexcept_added': 0,
            'string_view_adopted': 0,
            'files_modified': 0,
        }
    
    def optimize_headers(self):
        """Apply quick wins optimizations to header files"""
        include_dirs = [
            'PZ-Switch/include',
            'PZ-Switch/include/jni',
        ]
        
        for include_dir in include_dirs:
            if not Path(include_dir).exists():
                continue
            
            for h_file in Path(include_dir).rglob('*.h'):
                self._optimize_file(h_file)
    
    def _optimize_file(self, filepath: Path) -> None:
        """Optimize a single header file"""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            original_content = content
            
            # 1. Add const to getter methods
            content, count = self._add_const_to_getters(content)
            self.stats['const_added'] += count
            
            # 2. Add noexcept to simple methods
            content, count = self._add_noexcept(content)
            self.stats['noexcept_added'] += count
            
            # 3. Replace std::string with std::string_view in parameters
            content, count = self._use_string_view(content)
            self.stats['string_view_adopted'] += count
            
            if content != original_content:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(content)
                self.stats['files_modified'] += 1
        
        except Exception as e:
            print(f"Warning: Could not process {filepath}: {e}")
    
    def _add_const_to_getters(self, content: str) -> Tuple[str, int]:
        """Add const qualifier to getter methods"""
        count = 0
        
        # Pattern: getter methods without const
        # Matches: Type getName() { return ... }
        pattern = r'(\s+(?:inline\s+)?)((?:std::\w+|bool|int|float|double|char|size_t|uint32_t|int32_t)\S*)\s+(\w+Get\w+)\s*\(\s*\)\s*(\{|;)'
        
        def replacer(match):
            nonlocal count
            indent = match.group(1)
            return_type = match.group(2)
            method_name = match.group(3)
            ending = match.group(4)
            
            # Check if already has const
            if 'const' not in return_type:
                count += 1
                return f'{indent}{return_type} {method_name}() const {ending}'
            return match.group(0)
        
        content = re.sub(pattern, replacer, content)
        
        return content, count
    
    def _add_noexcept(self, content: str) -> Tuple[str, int]:
        """Add noexcept to methods that won't throw"""
        count = 0
        
        # Simple getters and accessors
        pattern = r'(\s+(?:inline\s+)?(?:const\s+)?[^(]+)\s+(\w+(?:Get|get|Count|count|Size|size)\w*)\s*\(\s*\)\s*(const)?(\s*\{)'
        
        def replacer(match):
            nonlocal count
            prefix = match.group(1)
            method_name = match.group(2)
            is_const = match.group(3)
            opening = match.group(4)
            
            # Add noexcept if not already present and method is likely non-throwing
            if 'noexcept' not in prefix:
                count += 1
                if is_const:
                    return f'{prefix} {method_name}() const noexcept{opening}'
                else:
                    return f'{prefix} {method_name}() noexcept{opening}'
            return match.group(0)
        
        content = re.sub(pattern, replacer, content)
        
        return content, count
    
    def _use_string_view(self, content: str) -> Tuple[str, int]:
        """Replace const std::string& with std::string_view"""
        count = 0
        
        # Only replace in function parameters, not return types
        pattern = r'([\(\,]\s*)const\s+std::string\s*&\s*(\w+)'
        
        def replacer(match):
            nonlocal count
            prefix = match.group(1)
            param_name = match.group(2)
            count += 1
            return f'{prefix}std::string_view {param_name}'
        
        content = re.sub(pattern, replacer, content)
        
        # Also need to add the include if using string_view
        if count > 0 and '#include <string_view>' not in content:
            # Find the includes section and add it
            include_pattern = r'(#include <string>)'
            if re.search(include_pattern, content):
                content = re.sub(
                    include_pattern,
                    r'#include <string>\n#include <string_view>',
                    content
                )
                count += 1
        
        return content, count
    
    def print_report(self) -> None:
        """Print optimization report"""
        print("\n" + "="*70)
        print("QUICK WINS OPTIMIZATION REPORT")
        print("="*70)
        print(f"\nOptimizations Applied:")
        print(f"  const added to getters:        {self.stats['const_added']}")
        print(f"  noexcept specifications:       {self.stats['noexcept_added']}")
        print(f"  std::string_view adoptions:    {self.stats['string_view_adopted']}")
        print(f"  Files modified:                {self.stats['files_modified']}")
        print("\nPerformance Impact:")
        print(f"  - Const correctness:     Better compiler optimization")
        print(f"  - Noexcept:              Enables exception-free optimization")
        print(f"  - string_view:           Zero-copy string parameters")
        print("="*70 + "\n")


if __name__ == '__main__':
    optimizer = QuickWinsOptimizer()
    print("Starting quick wins optimization...")
    optimizer.optimize_headers()
    optimizer.print_report()
