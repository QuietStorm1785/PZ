#!/usr/bin/env python3
"""
AttachedItems-specific fixes for structural issues.
Handles member variables, Java keywords, and type mismatches.
"""

import os
import re
import sys
from pathlib import Path

class AttachedItemsFixer:
    def __init__(self):
        self.issues_fixed = {
            'missing_members': 0,
            'java_keywords': 0,
            'null_to_nullptr': 0,
            'access_specifiers': 0,
            'missing_semicolons': 0,
        }
    
    def fix_attached_location_group(self, content):
        """Fix AttachedLocationGroup class specifically."""
        lines = content.split('\n')
        fixed_lines = []
        in_class = False
        class_start_idx = -1
        members_added = False
        
        for i, line in enumerate(lines):
            # Detect class declaration
            if 'class AttachedLocationGroup' in line:
                in_class = True
                class_start_idx = len(fixed_lines)
                fixed_lines.append(line)
                continue
            
            # Fix access specifiers (remove standalone protected/public)
            if in_class and line.strip() in ['protected', 'public', 'private']:
                if not members_added and 'protected' in line:
                    # Add members before first access specifier
                    fixed_lines.append('private:')
                    fixed_lines.append('  std::vector<std::shared_ptr<AttachedLocation>> locations;')
                    fixed_lines.append('')
                    members_added = True
                    self.issues_fixed['missing_members'] += 1
                # Replace standalone access specifier with proper one
                fixed_lines.append('public:')
                continue
            
            # Fix 'final' keyword
            if ' final ' in line:
                line = re.sub(r'\s*final\s+', ' ', line)
                self.issues_fixed['java_keywords'] += 1
            
            # Remove 'final' at line end
            if line.rstrip().endswith(' final'):
                line = line.rstrip()[:-6]
                self.issues_fixed['java_keywords'] += 1
            
            # Fix ArrayList reference to std::vector
            if 'ArrayList<AttachedLocation>' in line:
                line = line.replace('ArrayList<AttachedLocation>', 'std::vector<std::shared_ptr<AttachedLocation>>')
                self.issues_fixed['java_keywords'] += 1
            
            # Fix std::make_unique<ArrayList> → proper initialization
            if 'std::make_unique<ArrayList>' in line:
                # This line should be removed since we declare member properly
                continue
            
            # Fix 'null' to 'nullptr'
            if ' null' in line or ' null;' in line:
                line = re.sub(r'\bnull\b', 'nullptr', line)
                self.issues_fixed['null_to_nullptr'] += 1
            
            # Fix .empty() calls on non-string types
            if '.empty()' in line and ('attachedLocation' in line or 'this->locations' in line):
                # .empty() on AttachedLocation is wrong, should check if null
                line = line.replace('.empty()', ' == nullptr')
            
            # Add missing semicolons after class members
            if in_class and '=' in line and not line.rstrip().endswith((';', ',')):
                # This is likely a member initialization, but it's malformed
                # Check context
                pass
            
            # Fix method return type (AttachedLocation should have *)
            if 'AttachedLocation getLocation' in line or 'AttachedLocation getOrCreateLocation' in line:
                line = line.replace('AttachedLocation getLocation', 'std::shared_ptr<AttachedLocation> getLocation')
                line = line.replace('AttachedLocation getOrCreateLocation', 'std::shared_ptr<AttachedLocation> getOrCreateLocation')
                self.issues_fixed['access_specifiers'] += 1
            
            fixed_lines.append(line)
        
        return '\n'.join(fixed_lines)
    
    def process_file(self, filepath):
        """Process AttachedItems files."""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            # Determine which fixer to use based on filename
            if 'AttachedLocationGroup' in filepath:
                new_content = self.fix_attached_location_group(content)
            else:
                # Apply standard fixes
                new_content = content
                # Fix null → nullptr
                new_content = re.sub(r'\bnull\b', 'nullptr', new_content)
                # Fix final keyword
                new_content = re.sub(r'\s+final\s+', ' ', new_content)
            
            if content != new_content:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(new_content)
                return True
            return False
        except Exception as e:
            print(f"Error processing {filepath}: {e}", file=sys.stderr)
            return False
    
    def run(self, directory):
        """Scan and fix AttachedItems files."""
        if not os.path.isdir(directory):
            print(f"Error: {directory} is not a directory")
            return False
        
        # Target AttachedItems directory
        search_pattern = Path(directory).rglob('AttachedItems/*.h')
        files = list(search_pattern)
        
        print(f"Found {len(files)} AttachedItems files to fix...")
        
        fixed = 0
        for filepath in files:
            if self.process_file(str(filepath)):
                fixed += 1
                print(f"Fixed: {filepath.relative_to(directory) if directory != '.' else filepath.name}")
        
        return True
    
    def print_report(self):
        """Print statistics."""
        print("\nAttachedItems Fixer Report:")
        print(f"  Missing members added: {self.issues_fixed['missing_members']}")
        print(f"  Java keywords removed: {self.issues_fixed['java_keywords']}")
        print(f"  null → nullptr: {self.issues_fixed['null_to_nullptr']}")
        print(f"  Access specifiers fixed: {self.issues_fixed['access_specifiers']}")
        print(f"  Missing semicolons added: {self.issues_fixed['missing_semicolons']}")


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 fix_attached_items.py <directory>")
        sys.exit(1)
    
    fixer = AttachedItemsFixer()
    if fixer.run(sys.argv[1]):
        fixer.print_report()
        return 0
    return 1


if __name__ == '__main__':
    sys.exit(main())
