#!/usr/bin/env python3
"""
Fix Java-to-C++ conversion issues in PZ-Switch codebase.

This script performs the following transformations:
1. instanceof operator → dynamic_cast
2. synchronized blocks → std::lock_guard
3. TypeK/TypeV → templates or void* (handled by includes)
"""

import re
import sys
from pathlib import Path
from typing import List, Tuple

def fix_instanceof_patterns(content: str) -> Tuple[str, int]:
    """
    Fix instanceof patterns in C++ code.
    
    Patterns:
    1. if (obj instanceof Type) → if (dynamic_cast<Type*>(obj) != nullptr)
    2. if (!(obj instanceof Type)) → if (dynamic_cast<Type*>(obj) == nullptr)
    3. if (obj instanceof Type var) → if (auto* var = dynamic_cast<Type*>(obj))
    4. obj instanceof Type && ... → (dynamic_cast<Type*>(obj) != nullptr) && ...
    """
    changes = 0
    
    # Pattern 1: Simple instanceof check (no pattern matching variable)
    # if (arg0 instanceof Matrix2f) → if (dynamic_cast<Matrix2f*>(arg0) != nullptr)
    pattern1 = r'\b(\w+)\s+instanceof\s+(\w+)(?!\s+\w+\s*[;,)])'
    def repl1(match):
        obj, typ = match.groups()
        return f'dynamic_cast<{typ}*>({obj}) != nullptr'
    new_content, count1 = re.subn(pattern1, repl1, content)
    changes += count1
    content = new_content
    
    # Pattern 2: instanceof with pattern matching variable
    # if (type instanceof TypeVariable typeVariable) →
    # if (auto* typeVariable = dynamic_cast<TypeVariable*>(type))
    pattern2 = r'\b(\w+)\s+instanceof\s+(\w+)\s+(\w+)'
    def repl2(match):
        obj, typ, var = match.groups()
        return f'auto* {var} = dynamic_cast<{typ}*>({obj})'
    new_content, count2 = re.subn(pattern2, repl2, content)
    changes += count2
    content = new_content
    
    # Pattern 3: Negated instanceof
    # !(obj instanceof Type) → dynamic_cast<Type*>(obj) == nullptr
    pattern3 = r'!\(([^)]+)\s+instanceof\s+(\w+)\)'
    def repl3(match):
        obj, typ = match.groups()
        obj = obj.strip()
        return f'dynamic_cast<{typ}*>({obj}) == nullptr'
    new_content, count3 = re.subn(pattern3, repl3, content)
    changes += count3
    content = new_content
    
    return content, changes


def fix_synchronized_blocks(content: str) -> Tuple[str, int]:
    """
    Fix synchronized blocks in C++ code.
    
    Patterns:
    1. synchronized(obj) { → { std::lock_guard<std::mutex> __lock__(obj##_mutex);
    2. synchronized void method() → void method() with lock_guard inside
    """
    changes = 0
    
    # Pattern 1: synchronized(object) block
    # synchronized(this.lock) → { std::lock_guard<std::mutex> __lock__(lock_mutex);
    pattern1 = r'synchronized\s*\(\s*([^)]+)\s*\)\s*\{'
    def repl1(match):
        obj = match.group(1).strip()
        # Handle this.field → field_mutex
        if obj.startswith('this.'):
            obj = obj[5:]  # Remove 'this.'
        # Handle ClassName.class → ClassName_class_mutex
        if obj.endswith('.class'):
            obj = obj[:-6] + '_class'
        mutex_name = f'{obj}_mutex'
        return f'{{ std::lock_guard<std::mutex> __sync_lock__({mutex_name});'
    new_content, count1 = re.subn(pattern1, repl1, content)
    changes += count1
    content = new_content
    
    # Pattern 2: synchronized method
    # synchronized void method() → void method() (requires manual lock_guard insertion)
    # This is more complex and requires context, so we'll flag it instead
    pattern2 = r'\bsynchronized\s+([\w<>]+\s+\w+\s*\([^)]*\))'
    def repl2(match):
        method_sig = match.group(1)
        return f'/* TODO: Add SYNCHRONIZED_METHOD() */ {method_sig}'
    new_content, count2 = re.subn(pattern2, repl2, content)
    changes += count2
    content = new_content
    
    return content, changes


def process_file(file_path: Path, fix_instanceof: bool = True, fix_synchronized: bool = True) -> int:
    """Process a single file and apply fixes."""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        original_content = content
        total_changes = 0
        
        if fix_instanceof:
            content, changes = fix_instanceof_patterns(content)
            total_changes += changes
            
        if fix_synchronized:
            content, changes = fix_synchronized_blocks(content)
            total_changes += changes
        
        if total_changes > 0:
            with open(file_path, 'w', encoding='utf-8') as f:
                f.write(content)
            print(f'✓ {file_path}: {total_changes} fixes applied')
        
        return total_changes
        
    except Exception as e:
        print(f'✗ Error processing {file_path}: {e}', file=sys.stderr)
        return 0


def main():
    """Main entry point."""
    import argparse
    
    parser = argparse.ArgumentParser(description='Fix Java-to-C++ conversion issues')
    parser.add_argument('paths', nargs='+', help='Files or directories to process')
    parser.add_argument('--instanceof', action='store_true', help='Fix instanceof only')
    parser.add_argument('--synchronized', action='store_true', help='Fix synchronized only')
    parser.add_argument('--dry-run', action='store_true', help='Show what would be changed without modifying files')
    
    args = parser.parse_args()
    
    # If no specific fix specified, do all
    fix_instanceof = args.instanceof or not args.synchronized
    fix_synchronized = args.synchronized or not args.instanceof
    
    files_to_process: List[Path] = []
    
    for path_str in args.paths:
        path = Path(path_str)
        if path.is_file():
            if path.suffix in ['.h', '.cpp']:
                files_to_process.append(path)
        elif path.is_dir():
            files_to_process.extend(path.rglob('*.h'))
            files_to_process.extend(path.rglob('*.cpp'))
        else:
            print(f'Warning: {path} does not exist', file=sys.stderr)
    
    total_files = len(files_to_process)
    total_changes = 0
    files_changed = 0
    
    print(f'Processing {total_files} files...')
    
    for file_path in files_to_process:
        if args.dry_run:
            # For dry run, just check what would change
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
            
            if fix_instanceof:
                _, changes = fix_instanceof_patterns(content)
                if changes > 0:
                    print(f'Would fix {file_path}: {changes} instanceof issues')
                    total_changes += changes
            
            if fix_synchronized:
                _, changes = fix_synchronized_blocks(content)
                if changes > 0:
                    print(f'Would fix {file_path}: {changes} synchronized issues')
                    total_changes += changes
        else:
            changes = process_file(file_path, fix_instanceof, fix_synchronized)
            if changes > 0:
                files_changed += 1
                total_changes += changes
    
    print(f'\n{"DRY RUN - " if args.dry_run else ""}Summary:')
    print(f'  Files processed: {total_files}')
    print(f'  Files changed: {files_changed}')
    print(f'  Total fixes: {total_changes}')
    
    return 0 if total_changes == 0 else 1


if __name__ == '__main__':
    sys.exit(main())
