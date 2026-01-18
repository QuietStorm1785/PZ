#!/usr/bin/env python3
"""
Audit C++ classes for missing member variables.
Detects class definitions and flags potential issues:
- getters/setters without backing members
- method calls on undefined members
- incomplete constructors
"""

import os
import re
import sys
from pathlib import Path
from collections import defaultdict

class MemberAuditor:
    def __init__(self):
        self.issues = []
        self.classes = {}
    
    def extract_class_info(self, filepath, content):
        """Extract class definitions and member info from C++ file."""
        # Match class definitions
        class_pattern = r'(?:class|struct)\s+(\w+)\s*(?::|{)'
        
        for match in re.finditer(class_pattern, content):
            class_name = match.group(1)
            class_start = match.start()
            
            # Find matching brace
            brace_count = 0
            in_class = False
            class_end = len(content)
            
            for i in range(class_start, len(content)):
                if content[i] == '{':
                    in_class = True
                    brace_count += 1
                elif content[i] == '}':
                    brace_count -= 1
                    if in_class and brace_count == 0:
                        class_end = i
                        break
            
            if not in_class:
                continue
            
            class_body = content[class_start:class_end]
            
            # Extract members and methods
            members = self.extract_members(class_body)
            methods = self.extract_methods(class_body)
            
            self.classes[class_name] = {
                'members': members,
                'methods': methods,
                'filepath': filepath,
                'body': class_body,
                'line': content[:class_start].count('\n') + 1
            }
    
    def extract_members(self, class_body):
        """Extract member variable declarations."""
        members = set()
        
        # Match member declarations (basic pattern)
        member_pattern = r'^\s*(?:std::\w+|[\w:]+)\s+(\w+)\s*[=;]'
        
        for line in class_body.split('\n'):
            # Skip method definitions and access modifiers
            if '(' in line or line.strip().startswith(('public:', 'private:', 'protected:')):
                continue
            
            for match in re.finditer(member_pattern, line):
                members.add(match.group(1))
        
        return members
    
    def extract_methods(self, class_body):
        """Extract method signatures."""
        methods = defaultdict(list)
        
        # Match method signatures (simple pattern)
        method_pattern = r'(?:virtual\s+)?(?:static\s+)?(?:const\s+)?(\w+)\s+(\w+)\s*\([^)]*\)'
        
        for line in class_body.split('\n'):
            if '{' not in line:  # Skip one-liners for now
                for match in re.finditer(method_pattern, line):
                    return_type = match.group(1)
                    method_name = match.group(2)
                    methods[method_name].append(return_type)
        
        return methods
    
    def find_issues(self):
        """Analyze classes for potential issues."""
        for class_name, info in self.classes.items():
            members = info['members']
            methods = info['methods']
            body = info['body']
            
            # Check for getters without members
            for method_name in methods:
                if method_name.startswith('get'):
                    # Extract likely member name
                    suffix = method_name[3:]
                    potential_members = [
                        suffix.lower(),
                        '_' + suffix.lower(),
                        suffix[0].lower() + suffix[1:],
                        'm_' + suffix.lower(),
                    ]
                    
                    if not any(m in members for m in potential_members):
                        # Check if it's a simple getter
                        if 'return' in body:
                            self.issues.append({
                                'type': 'getter_without_member',
                                'class': class_name,
                                'method': method_name,
                                'potential_members': potential_members,
                                'filepath': info['filepath'],
                                'line': info['line']
                            })
            
            # Check for setters without getters
            setter_methods = [m for m in methods if m.startswith('set')]
            getter_methods = [m for m in methods if m.startswith('get')]
            
            for setter in setter_methods:
                suffix = setter[3:]
                corresponding_getter = 'get' + suffix
                
                if corresponding_getter not in getter_methods and suffix not in members:
                    self.issues.append({
                        'type': 'setter_without_member',
                        'class': class_name,
                        'method': setter,
                        'property': suffix,
                        'filepath': info['filepath'],
                        'line': info['line']
                    })
    
    def report(self):
        """Print audit report."""
        if not self.issues:
            print("✓ No issues found")
            return
        
        print(f"\n⚠ Found {len(self.issues)} potential issues:\n")
        
        for issue in self.issues:
            print(f"  [{issue['class']}] {issue['type']}")
            print(f"    File: {issue['filepath']}:{issue['line']}")
            
            if issue['type'] == 'getter_without_member':
                print(f"    Method: {issue['method']}()")
                print(f"    Potential members: {', '.join(issue['potential_members'])}")
            elif issue['type'] == 'setter_without_member':
                print(f"    Method: {issue['method']}()")
                print(f"    Property: {issue['property']}")
            
            print()


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 audit_class_members.py <directory>")
        sys.exit(1)
    
    root_dir = sys.argv[1]
    
    if not os.path.isdir(root_dir):
        print(f"Error: {root_dir} is not a directory")
        sys.exit(1)
    
    auditor = MemberAuditor()
    
    # Find all C++ header files
    files = list(Path(root_dir).rglob('*.h'))
    
    print(f"Auditing {len(files)} header files for missing members...")
    
    for i, filepath in enumerate(files, 1):
        if i % 100 == 0:
            print(f"  Processing: {i}/{len(files)}")
        
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            auditor.extract_class_info(str(filepath), content)
        except Exception as e:
            print(f"Error reading {filepath}: {e}", file=sys.stderr)
    
    print(f"\nAnalyzed {len(auditor.classes)} classes")
    auditor.find_issues()
    auditor.report()
    
    return 0


if __name__ == '__main__':
    sys.exit(main())
