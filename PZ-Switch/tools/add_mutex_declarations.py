#!/usr/bin/env python3
"""
Add mutex declarations to classes that use std::lock_guard.

This script scans header files for std::lock_guard usage and adds
the corresponding mutex member declarations.
"""

import re
import sys
from pathlib import Path
from typing import Set, Dict, List
from collections import defaultdict

def extract_mutex_names(content: str) -> Set[str]:
    """Extract all mutex names used in lock_guard statements."""
    mutexes = set()
    
    # Pattern: std::lock_guard<std::mutex> __sync_lock__(MUTEX_NAME);
    pattern = r'std::lock_guard<std::mutex>\s+\w+\((\w+)\);'
    
    for match in re.finditer(pattern, content):
        mutex_name = match.group(1)
        mutexes.add(mutex_name)
    
    return mutexes

def is_static_mutex(mutex_name: str, content: str) -> bool:
    """Determine if a mutex should be static based on naming convention."""
    # Class-level mutexes (ClassName_mutex or ClassName_class_mutex)
    if '_class_mutex' in mutex_name:
        return True
    
    # If used with static members/methods
    # Check if the lock is in a static context
    # For now, use heuristic: if it ends with _mutex but doesn't start with lowercase, likely static
    if mutex_name.endswith('_mutex'):
        base_name = mutex_name[:-6]  # Remove '_mutex'
        # Check if base name matches pattern for static (starts with uppercase or is a known static pattern)
        if base_name and base_name[0].isupper():
            return True
    
    return False

def find_class_declaration(content: str, search_from: int = 0) -> tuple:
    """Find the class declaration line and its name."""
    pattern = r'^\s*class\s+(\w+)\s*(?::\s*public)?.*?\{$'
    
    lines = content.split('\n')
    for i, line in enumerate(lines[search_from:], start=search_from):
        match = re.match(pattern, line)
        if match:
            class_name = match.group(1)
            return (i, class_name)
    
    return (None, None)

def add_mutex_declarations(file_path: Path) -> int:
    """Add mutex declarations to a file."""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # Extract mutex names
        mutexes = extract_mutex_names(content)
        if not mutexes:
            return 0
        
        # Check if mutexes are already declared
        already_declared = set()
        for mutex in mutexes:
            if re.search(rf'\bstd::mutex\s+{mutex}\b', content):
                already_declared.add(mutex)
        
        mutexes_to_add = mutexes - already_declared
        if not mutexes_to_add:
            return 0
        
        # Find where to insert mutex declarations
        # Look for "public:" section after class declaration
        lines = content.split('\n')
        
        # Find class declaration
        class_line = None
        class_name = None
        for i, line in enumerate(lines):
            if re.match(r'^\s*class\s+\w+', line):
                class_line = i
                match = re.match(r'^\s*class\s+(\w+)', line)
                if match:
                    class_name = match.group(1)
                break
        
        if class_line is None:
            print(f"Warning: Could not find class declaration in {file_path}")
            return 0
        
        # Find first public section or end of class opening
        insert_line = None
        for i in range(class_line + 1, len(lines)):
            line = lines[i].strip()
            if line == 'public:':
                insert_line = i + 1
                break
            elif line.startswith('private:') or line.startswith('protected:'):
                # Insert before private/protected
                insert_line = i
                break
        
        if insert_line is None:
            # No public section found, insert after class opening brace
            for i in range(class_line, min(class_line + 10, len(lines))):
                if '{' in lines[i]:
                    insert_line = i + 1
                    break
        
        if insert_line is None:
            print(f"Warning: Could not find insertion point in {file_path}")
            return 0
        
        # Categorize mutexes
        static_mutexes = []
        instance_mutexes = []
        
        for mutex in sorted(mutexes_to_add):
            if is_static_mutex(mutex, content):
                static_mutexes.append(mutex)
            else:
                instance_mutexes.append(mutex)
        
        # Build insertion text
        insertion_lines = []
        if static_mutexes or instance_mutexes:
            insertion_lines.append('')
            insertion_lines.append('  // Mutexes for synchronized blocks')
        
        if static_mutexes:
            for mutex in static_mutexes:
                insertion_lines.append(f'  static std::mutex {mutex};')
        
        if instance_mutexes:
            if static_mutexes:
                insertion_lines.append('')
            for mutex in instance_mutexes:
                insertion_lines.append(f'  std::mutex {mutex};')
        
        # Insert the mutex declarations
        lines[insert_line:insert_line] = insertion_lines
        
        # Write back
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(lines))
        
        count = len(mutexes_to_add)
        print(f'✓ {file_path}: Added {count} mutex declaration(s)')
        return count
        
    except Exception as e:
        print(f'✗ Error processing {file_path}: {e}', file=sys.stderr)
        return 0

def main():
    """Main entry point."""
    import argparse
    
    parser = argparse.ArgumentParser(description='Add mutex declarations to header files')
    parser.add_argument('paths', nargs='+', help='Files or directories to process')
    parser.add_argument('--dry-run', action='store_true', help='Show what would be changed')
    
    args = parser.parse_args()
    
    files_to_process: List[Path] = []
    
    for path_str in args.paths:
        path = Path(path_str)
        if path.is_file():
            if path.suffix == '.h':
                files_to_process.append(path)
        elif path.is_dir():
            files_to_process.extend(path.rglob('*.h'))
    
    # Filter to only files that use lock_guard
    files_with_locks = []
    for file_path in files_to_process:
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                if 'std::lock_guard' in f.read():
                    files_with_locks.append(file_path)
        except:
            pass
    
    total_files = len(files_with_locks)
    total_mutexes = 0
    files_changed = 0
    
    print(f'Processing {total_files} files with lock_guard...')
    
    for file_path in files_with_locks:
        if args.dry_run:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
            mutexes = extract_mutex_names(content)
            already_declared = set()
            for mutex in mutexes:
                if re.search(rf'\bstd::mutex\s+{mutex}\b', content):
                    already_declared.add(mutex)
            mutexes_to_add = mutexes - already_declared
            if mutexes_to_add:
                print(f'Would add to {file_path}: {", ".join(sorted(mutexes_to_add))}')
                total_mutexes += len(mutexes_to_add)
        else:
            count = add_mutex_declarations(file_path)
            if count > 0:
                files_changed += 1
                total_mutexes += count
    
    print(f'\n{"DRY RUN - " if args.dry_run else ""}Summary:')
    print(f'  Files with locks: {total_files}')
    print(f'  Files changed: {files_changed}')
    print(f'  Mutex declarations added: {total_mutexes}')
    
    return 0

if __name__ == '__main__':
    sys.exit(main())
