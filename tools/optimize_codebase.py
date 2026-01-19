#!/usr/bin/env python3
"""
Comprehensive Codebase Optimization Script
Fixes missed optimizations and performance issues
"""

import os
import re
from pathlib import Path

class CodebaseOptimizer:
    def __init__(self):
        self.stats = {
            'std_endl_replaced': 0,
            'java_catch_fixed': 0,
            'missing_comments': 0,
        }
    
    def optimize_performance(self):
        """Replace std::endl with '\n' for better performance"""
        self.stats['std_endl_replaced'] = 0
        
        for cpp_file in Path('PZ-Switch/src').glob('*.cpp'):
            with open(cpp_file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            original = content
            # Replace std::endl with '\n' (much faster - doesn't flush)
            content = re.sub(r'std::endl', r"'\\n'", content)
            
            if content != original:
                self.stats['std_endl_replaced'] += len(re.findall(r"'\\n'", content)) - len(re.findall(r"std::endl", original))
                with open(cpp_file, 'w', encoding='utf-8') as f:
                    f.write(content)
    
    def fix_java_exceptions(self):
        """Convert Java exception patterns to C++"""
        self.stats['java_catch_fixed'] = 0
        
        for h_file in Path('Convert2Cpp/include').rglob('*.h'):
            with open(h_file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            original = content
            
            # Fix: catch (IOException var2) -> catch (const jni::JavaException& e)
            content = re.sub(
                r'catch\s*\(\s*IOException\s+(\w+)\s*\)',
                r'catch (const jni::JavaException& \1)',
                content
            )
            
            # Fix: catch (InterruptedException var2) -> catch (const std::exception& e)
            content = re.sub(
                r'catch\s*\(\s*InterruptedException\s+(\w+)\s*\)',
                r'catch (const std::exception& \1)',
                content
            )
            
            # Fix: catch (Exception var2) -> catch (const jni::JavaException& e)
            content = re.sub(
                r'catch\s*\(\s*Exception\s+(\w+)\s*\)',
                r'catch (const jni::JavaException& \1)',
                content
            )
            
            # Fix: catch (Throwable var2) -> catch (const std::exception& e)
            content = re.sub(
                r'catch\s*\(\s*Throwable\s+(\w+)\s*\)',
                r'catch (const std::exception& \1)',
                content
            )
            
            if content != original:
                self.stats['java_catch_fixed'] += 1
                with open(h_file, 'w', encoding='utf-8') as f:
                    f.write(content)
    
    def add_const_correctness(self):
        """Add const correctness to method signatures"""
        # This is more complex and would need custom logic per file
        pass
    
    def print_report(self):
        """Print optimization report"""
        print("\n" + "=" * 70)
        print("PERFORMANCE OPTIMIZATION REPORT")
        print("=" * 70)
        print(f"\nOptimizations Applied:")
        print(f"  std::endl → '\\n': {self.stats['std_endl_replaced']} replacements")
        print(f"  Java exceptions fixed: {self.stats['java_catch_fixed']} files")
        print("=" * 70 + "\n")


if __name__ == '__main__':
    optimizer = CodebaseOptimizer()
    print("Starting comprehensive optimization...")
    optimizer.optimize_performance()
    optimizer.fix_java_exceptions()
    optimizer.print_report()
