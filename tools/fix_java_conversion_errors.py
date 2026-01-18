#!/usr/bin/env python3
"""
Fix common Java-to-C++ conversion errors in converted files
- this. → this->
- throw new Exception → throw Exception
- .isEmpty() → .empty()
"""

import re
import sys
from pathlib import Path

def fix_this_dot(content):
    """Replace this. with this-> """
    # Match this.member but not this->member
    pattern = r'\bthis\.(\w+)'
    return re.sub(pattern, r'this->\1', content)

def fix_throw_new(content):
    """Replace 'throw new Exception' with 'throw Exception' """
    pattern = r'throw\s+new\s+(\w+)'
    return re.sub(pattern, r'throw \1', content)

def fix_is_empty(content):
    """Replace .isEmpty() with .empty() """
    return content.replace('.isEmpty()', '.empty()')

def fix_file(file_path):
    """Apply all fixes to a file"""
    try:
        with open(file_path, 'r') as f:
            content = f.read()
        
        original = content
        content = fix_this_dot(content)
        content = fix_throw_new(content)
        content = fix_is_empty(content)
        
        if content != original:
            with open(file_path, 'w') as f:
                f.write(content)
            return True
        return False
    except Exception as e:
        print(f"Error processing {file_path}: {e}", file=sys.stderr)
        return False

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 fix_java_conversion_errors.py <directory>")
        sys.exit(1)
    
    root_dir = Path(sys.argv[1])
    if not root_dir.exists():
        print(f"Directory not found: {root_dir}")
        sys.exit(1)
    
    # Find all .cpp and .h files
    cpp_files = list(root_dir.rglob("*.cpp"))
    h_files = list(root_dir.rglob("*.h"))
    all_files = cpp_files + h_files
    
    print(f"Scanning {len(all_files)} files...")
    
    fixed_count = 0
    for file_path in all_files:
        if fix_file(file_path):
            fixed_count += 1
            print(f"Fixed: {file_path}")
    
    print(f"\nFixed {fixed_count} files")

if __name__ == "__main__":
    main()
