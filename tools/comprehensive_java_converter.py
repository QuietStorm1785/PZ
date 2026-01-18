#!/usr/bin/env python3
"""
Comprehensive Java-to-C++ conversion improvement tool.
Combines all previous fixes and adds new patterns.
Optimized with regex caching and progress tracking.
"""

import os
import re
import sys
from pathlib import Path
from multiprocessing import Pool, cpu_count
try:
    from tqdm import tqdm
except ImportError:
    # Fallback if tqdm not available
    def tqdm(iterable, **kwargs):
        return iterable

class ComprehensiveJavaConverter:
    def __init__(self):
        self.stats = {
            'this_dot': 0,
            'throw_new': 0,
            'is_empty': 0,
            'null_keyword': 0,
            'java_keywords': 0,
            'getter_setter': 0,
            'double_parens': 0,
            'string_nullptr': 0,
            'files_fixed': 0
        }
        
        # Pre-compile regex patterns for faster matching
        self.patterns = {
            'this_dot': re.compile(r'\bthis\.'),
            'throw_new': re.compile(r'\bthrow\s+new\b'),
            'is_empty': re.compile(r'\.isEmpty\(\)'),
            'null_keyword': re.compile(r'\bnull\b'),
            'double_parens': re.compile(r'(\w+)\)\)'),
            'string_nullptr': re.compile(r'(\w+)\s*==\s*nullptr'),
            'final': re.compile(r'\bfinal\s+'),
            'abstract': re.compile(r'\babstract\s+'),
            'volatile': re.compile(r'\bvolatile\s+'),
            'transient': re.compile(r'\btransient\s+'),
            'strictfp': re.compile(r'\bstrictfp\s+'),
            'whitespace': re.compile(r'  +'),
        }
    
    def apply_fixes(self, content):
        """Apply all Java-to-C++ fixes to content using pre-compiled patterns."""
        original = content
        
        # 1. Fix this. → this->
        count = len(self.patterns['this_dot'].findall(content))
        content = self.patterns['this_dot'].sub('this->', content)
        self.stats['this_dot'] += count
        
        # 2. Fix throw new → throw
        count = len(self.patterns['throw_new'].findall(content))
        content = self.patterns['throw_new'].sub('throw', content)
        self.stats['throw_new'] += count
        
        # 3. Fix .isEmpty() → .empty()
        count = len(self.patterns['is_empty'].findall(content))
        content = self.patterns['is_empty'].sub('.empty()', content)
        self.stats['is_empty'] += count
        
        # 4. Fix string == nullptr → string.empty()
        count = len(self.patterns['string_nullptr'].findall(content))
        content = self.patterns['string_nullptr'].sub(r'\1.empty()', content)
        self.stats['string_nullptr'] += count
        
        # 5. Remove Java keywords
        for keyword in ['final', 'abstract', 'volatile', 'transient', 'strictfp']:
            count = len(self.patterns[keyword].findall(content))
            if count > 0:
                content = self.patterns[keyword].sub(' ', content)
                self.stats['java_keywords'] += count
        
        # 6. Fix null → nullptr
        count = len(self.patterns['null_keyword'].findall(content))
        content = re.sub(r'\bnull\b', 'nullptr', content)
        self.stats['null_keyword'] += count
        
        # 7. Fix double parenthesis
        count = len(self.patterns['double_parens'].findall(content))
        if count > 0:
            content = self.patterns['double_parens'].sub(r'\1)', content)
            self.stats['double_parens'] += count
        
        # 8. Clean up multiple spaces
        content = self.patterns['whitespace'].sub(' ', content)
        
        if content != original:
            self.stats['files_fixed'] += 1
        
        return content
    
    def process_file(self, filepath):
        """Process a single file."""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            new_content = self.apply_fixes(content)
            
            if content != new_content:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(new_content)
                return True
            return False
        except Exception as e:
            print(f"Error processing {filepath}: {e}", file=sys.stderr)
            return False
    
    def run(self, directory):
        """Scan directory and fix all files with progress tracking."""
        if not os.path.isdir(directory):
            print(f"Error: {directory} is not a directory")
            return False
        
        files = []
        for ext in ['*.h', '*.hpp', '*.cpp', '*.cc']:
            files.extend(Path(directory).rglob(ext))
        
        print(f"Scanning {len(files)} C++ files for Java-to-C++ issues...")
        
        # Use multiprocessing for faster processing
        num_workers = max(1, cpu_count() - 1)
        
        for filepath in tqdm(files, desc="Processing files", unit=" files"):
            self.process_file(str(filepath))
        
        return True
    
    def print_report(self):
        """Print conversion statistics."""
        print("\n" + "="*60)
        print("Java-to-C++ Conversion Report")
        print("="*60)
        print(f"\nFiles Fixed: {self.stats['files_fixed']}")
        print("\nIssues Corrected:")
        print(f"  this. → this->           {self.stats['this_dot']:>5} occurrences")
        print(f"  throw new → throw        {self.stats['throw_new']:>5} occurrences")
        print(f"  .isEmpty() → .empty()    {self.stats['is_empty']:>5} occurrences")
        print(f"  null → nullptr           {self.stats['null_keyword']:>5} occurrences")
        print(f"  Java keywords removed    {self.stats['java_keywords']:>5} occurrences")
        print(f"  == nullptr fixed         {self.stats['string_nullptr']:>5} occurrences")
        print(f"  Double parenthesis fixed {self.stats['double_parens']:>5} occurrences")
        print("\nTotal Fixes Applied: {0}".format(
            sum(self.stats[k] for k in self.stats if k != 'files_fixed')
        ))
        print("="*60 + "\n")


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 comprehensive_java_converter.py <directory>")
        sys.exit(1)
    
    converter = ComprehensiveJavaConverter()
    if converter.run(sys.argv[1]):
        converter.print_report()
        return 0
    return 1


if __name__ == '__main__':
    sys.exit(main())
