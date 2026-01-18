#!/usr/bin/env python3
"""
Fix string == nullptr comparisons (Java artifact)
Replace with .empty() checks
"""

import re
import sys
from pathlib import Path

def fix_string_nullptr(content):
    """Replace string == nullptr with .empty() """
    # Match: identifier == nullptr (where identifier is likely a string)
    # Replace with: identifier.empty()
    pattern = r'(\w+)\s*==\s*nullptr'
    
    def replacer(match):
        var = match.group(1)
        return f'{var}.empty()'
    
    return re.sub(pattern, replacer, content)

def fix_file(file_path):
    """Apply fix to a file"""
    try:
        with open(file_path, 'r') as f:
            content = f.read()
        
        original = content
        content = fix_string_nullptr(content)
        
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
        print("Usage: python3 fix_string_nullptr.py <directory>")
        sys.exit(1)
    
    root_dir = Path(sys.argv[1])
    if not root_dir.exists():
        print(f"Directory not found: {root_dir}")
        sys.exit(1)
    
    # Find all .h files
    h_files = list(root_dir.rglob("*.h"))
    
    print(f"Scanning {len(h_files)} files...")
    
    fixed_count = 0
    for file_path in h_files:
        if fix_file(file_path):
            fixed_count += 1
            print(f"Fixed: {file_path}")
    
    print(f"\nFixed {fixed_count} files")

if __name__ == "__main__":
    main()
