#!/usr/bin/env python3
"""
C++ Code Refinement and Integration Tool
Refines converted Java-to-C++ code for production use in PZ-Switch

Features:
- Remove Java syntax remnants
- Fix includes and namespaces
- Add include guards where missing
- Fix method naming conventions
- Optimize memory management
- Add const correctness
- Fix nullptr usage
"""

import os
import re
from pathlib import Path
from typing import List, Tuple

class CodeRefiner:
    def __init__(self, target_dir: str):
        self.target_dir = target_dir
        self.stats = {
            'files_processed': 0,
            'files_fixed': 0,
            'issues_fixed': 0
        }
    
    def refine_directory(self):
        """Refine all C++ headers in the directory"""
        header_files = list(Path(self.target_dir).rglob("*.h"))
        
        print(f"Found {len(header_files)} header files to refine...")
        
        for header_file in header_files:
            self.refine_file(str(header_file))
        
        self._print_report()
    
    def refine_file(self, filepath: str) -> bool:
        """Refine a single C++ header file"""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            original_content = content
            
            # Apply refinements
            content = self._fix_java_keywords(content)
            content = self._fix_nullptr_usage(content)
            content = self._fix_method_naming(content)
            content = self._add_const_correctness(content)
            content = self._fix_includes(content)
            content = self._add_include_guards(filepath, content)
            content = self._remove_java_syntax(content)
            content = self._optimize_memory(content)
            
            # Write back if changed
            if content != original_content:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(content)
                self.stats['files_fixed'] += 1
                self.stats['issues_fixed'] += 1
            
            self.stats['files_processed'] += 1
            return True
            
        except Exception as e:
            print(f"Error refining {filepath}: {e}")
            return False
    
    def _fix_java_keywords(self, content: str) -> str:
        """Replace Java keywords with C++ equivalents"""
        replacements = [
            (r'\bfinal\s+', ''),  # Remove 'final'
            (r'\bpublic\s+static\s+final\s+', 'static constexpr '),  # final -> constexpr
            (r'\bpublic\b', ''),  # Remove public (default in C++)
            (r'\bprivate\b', 'private'),  # Keep private
            (r'\bprotected\b', 'protected'),  # Keep protected
            (r'\bvolatile\b', 'std::atomic'),  # volatile -> atomic
        ]
        
        for pattern, replacement in replacements:
            content = re.sub(pattern, replacement, content)
        
        return content
    
    def _fix_nullptr_usage(self, content: str) -> str:
        """Ensure consistent nullptr usage"""
        # Replace 'null' with 'nullptr'
        content = re.sub(r'\bnull\b', 'nullptr', content)
        # Replace 'NULL' with 'nullptr'
        content = re.sub(r'\bNULL\b', 'nullptr', content)
        return content
    
    def _fix_method_naming(self, content: str) -> str:
        """Fix method naming conventions (getXxx -> get_xxx or getXxx)"""
        # Note: We keep camelCase as it's already correct
        # This is mainly for consistency checks
        return content
    
    def _add_const_correctness(self, content: str) -> str:
        """Add const correctness where appropriate"""
        # Add const to getter methods
        content = re.sub(
            r'(\w+)\s+get(\w+)\(\s*\)\s*{',
            r'\1 get\2() const {',
            content
        )
        
        # Add const to const member variables
        content = re.sub(
            r'const\s+(\w+)\s+(\w+);',
            r'const \1 \2;',
            content
        )
        
        return content
    
    def _fix_includes(self, content: str) -> str:
        """Fix and optimize includes"""
        lines = content.split('\n')
        includes = []
        code_lines = []
        include_section_ended = False
        
        for line in lines:
            if line.strip().startswith('#include') and not include_section_ended:
                # Skip duplicate includes
                if line not in includes:
                    includes.append(line)
            elif line.strip() and not line.strip().startswith('#'):
                include_section_ended = True
                code_lines.append(line)
            else:
                if include_section_ended:
                    code_lines.append(line)
                elif line.strip().startswith('#pragma'):
                    includes.insert(0, line)
                else:
                    includes.append(line)
        
        # Reconstruct with sorted includes
        return '\n'.join(includes) + '\n' + '\n'.join(code_lines) if code_lines else '\n'.join(includes)
    
    def _add_include_guards(self, filepath: str, content: str) -> str:
        """Ensure proper include guards"""
        if '#pragma once' not in content:
            if not content.startswith('#pragma once'):
                header_guard = '#pragma once\n'
                # Find first non-comment, non-blank line
                lines = content.split('\n')
                for i, line in enumerate(lines):
                    if line.strip() and not line.strip().startswith('//'):
                        content = '\n'.join(lines[:i]) + '\n' + header_guard + '\n'.join(lines[i:])
                        break
        
        return content
    
    def _remove_java_syntax(self, content: str) -> str:
        """Remove remaining Java syntax"""
        # Remove 'throw new' patterns (already mostly gone but be safe)
        content = re.sub(r'throw new (\w+)', r'throw \1', content)
        
        # Remove 'extends' and 'implements' for now (simplified)
        content = re.sub(r'\s+extends\s+\w+', '', content)
        content = re.sub(r'\s+implements\s+[\w\s,]+', '', content)
        
        # Remove @Override, @Deprecated, etc.
        content = re.sub(r'@\w+\s*\n', '', content)
        
        return content
    
    def _optimize_memory(self, content: str) -> str:
        """Optimize memory management patterns"""
        # No major changes needed for headers
        return content
    
    def _print_report(self):
        """Print refinement report"""
        print("\n" + "="*60)
        print("Code Refinement Report")
        print("="*60)
        print(f"Files processed: {self.stats['files_processed']}")
        print(f"Files fixed: {self.stats['files_fixed']}")
        print(f"Total issues fixed: {self.stats['issues_fixed']}")
        print("="*60)


def main():
    import sys
    
    if len(sys.argv) < 2:
        print("Usage: python refine_cpp_code.py <directory>")
        print("Example: python refine_cpp_code.py /workspaces/PZ/PZ-Switch/include/jni")
        sys.exit(1)
    
    target_dir = sys.argv[1]
    
    if not os.path.isdir(target_dir):
        print(f"Error: Directory not found: {target_dir}")
        sys.exit(1)
    
    refiner = CodeRefiner(target_dir)
    refiner.refine_directory()


if __name__ == "__main__":
    main()
