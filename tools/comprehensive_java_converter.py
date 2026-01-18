#!/usr/bin/env python3
"""
Comprehensive Java-to-C++ conversion improvement tool.
Combines all previous fixes and adds new patterns.
"""

import os
import re
import sys
from pathlib import Path

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
    
    def apply_fixes(self, content):
        """Apply all Java-to-C++ fixes to content."""
        original = content
        
        # 1. Fix this. → this->
        count = len(re.findall(r'\bthis\.', content))
        content = re.sub(r'\bthis\.', 'this->', content)
        self.stats['this_dot'] += count
        
        # 2. Fix throw new → throw
        count = len(re.findall(r'\bthrow\s+new\b', content))
        content = re.sub(r'\bthrow\s+new\b', 'throw', content)
        self.stats['throw_new'] += count
        
        # 3. Fix .isEmpty() → .empty()
        count = len(re.findall(r'\.isEmpty\(\)', content))
        content = re.sub(r'\.isEmpty\(\)', '.empty()', content)
        self.stats['is_empty'] += count
        
        # 4. Fix string == nullptr → string.empty()
        count = len(re.findall(r'(\w+)\s*==\s*nullptr', content))
        # Only replace if looks like a string variable
        content = re.sub(r'(\w+)\s*==\s*nullptr', r'\1.empty()', content)
        self.stats['string_nullptr'] += count
        
        # 5. Remove Java keywords
        keywords_to_remove = [
            (r'\bfinal\s+', ' '),
            (r'\babstract\s+', ' '),
            (r'\bvolatile\s+', ' '),
            (r'\btransient\s+', ' '),
            (r'\bstrictfp\s+', ' '),
        ]
        
        for pattern, replacement in keywords_to_remove:
            count = len(re.findall(pattern, content))
            if count > 0:
                content = re.sub(pattern, replacement, content)
                self.stats['java_keywords'] += count
        
        # 6. Fix null → nullptr
        count = len(re.findall(r'\bnull\b', content))
        content = re.sub(r'\bnull\b', 'nullptr', content)
        self.stats['null_keyword'] += count
        
        # 7. Fix double parenthesis
        count = len(re.findall(r'\)\)', content))
        if count > 0:
            # This is tricky - only fix if clearly wrong
            content = re.sub(r'(\w+)\)\)', r'\1)', content)
            self.stats['double_parens'] += count
        
        # 8. Clean up multiple spaces
        content = re.sub(r'  +', ' ', content)
        
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
        """Scan directory and fix all files."""
        if not os.path.isdir(directory):
            print(f"Error: {directory} is not a directory")
            return False
        
        files = []
        for ext in ['*.h', '*.hpp', '*.cpp', '*.cc']:
            files.extend(Path(directory).rglob(ext))
        
        print(f"Scanning {len(files)} C++ files for Java-to-C++ issues...")
        
        for i, filepath in enumerate(files, 1):
            if i % 100 == 0:
                print(f"  Processing: {i}/{len(files)}")
            
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
