#!/usr/bin/env python3
"""
Fix C++ Class Qualification in Implementation Files
Adds proper ClassName:: qualification to methods in .cpp files
"""

import os
import re
import sys
from pathlib import Path
from typing import Optional, List, Tuple

class CppQualificationFixer:
    def __init__(self):
        self.stats = {
            'files_processed': 0,
            'files_fixed': 0,
            'methods_qualified': 0,
            'errors': 0
        }
    
    def extract_class_name_from_header(self, header_path: Path) -> Optional[str]:
        """Extract class name from corresponding header file"""
        if not header_path.exists():
            return None
        
        try:
            with open(header_path, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            # Look for class definition
            match = re.search(r'class\s+(\w+)\s*[:{]', content)
            return match.group(1) if match else None
        except Exception:
            return None
    
    def extract_namespace(self, content: str) -> Optional[str]:
        """Extract namespace from cpp file"""
        match = re.search(r'namespace\s+(\w+)\s*{', content)
        return match.group(1) if match else None
    
    def find_function_definitions(self, content: str) -> List[Tuple[int, int, str, str]]:
        """Find all function definitions and their signatures"""
        functions = []
        lines = content.split('\n')
        
        in_namespace = False
        
        i = 0
        while i < len(lines):
            line = lines[i]
            stripped = line.strip()
            
            # Track namespace
            if re.match(r'namespace\s+\w+\s*{', stripped):
                in_namespace = True
                i += 1
                continue
            
            # Skip comments and empty lines
            if not stripped or stripped.startswith('//') or stripped.startswith('/*') or stripped.startswith('*'):
                i += 1
                continue
            
            # Skip #include and #pragma
            if stripped.startswith('#'):
                i += 1
                continue
            
            # Skip closing namespace
            if stripped.startswith('}'):
                i += 1
                continue
            
            # Look for function signature (return_type function_name(...))
            # More flexible pattern to catch various cases
            func_pattern = r'^(\w+(?:\s*[<>:,\*&\w\s]*)?)\s+(\w+)\s*\('
            match = re.match(func_pattern, stripped)
            
            if match:
                # Found potential function
                return_type = match.group(1).strip()
                func_name = match.group(2).strip()
                
                # Skip if already qualified (contains ::)
                if '::' in stripped:
                    i += 1
                    continue
                
                # Skip constructors/destructors (name matches return type or ~name)
                if func_name == return_type or stripped.startswith('~'):
                    i += 1
                    continue
                
                # Find the opening brace (might be on same line or next few lines)
                sig_lines = [line]
                j = i
                found_brace = '{' in line
                
                while not found_brace and j < min(i + 5, len(lines)):
                    j += 1
                    if j < len(lines):
                        sig_lines.append(lines[j])
                        if '{' in lines[j]:
                            found_brace = True
                
                # Only add if we found the opening brace (it's a definition, not declaration)
                if found_brace:
                    func_signature = '\n'.join(sig_lines)
                    functions.append((i, return_type, func_name, func_signature))
            
            i += 1
        
        return functions
    
    def qualify_method(self, signature: str, class_name: str, return_type: str, method_name: str) -> str:
        """Add class qualification to method signature"""
        # Pattern to match the method name in the signature
        # We want to replace "return_type method_name(" with "return_type ClassName::method_name("
        
        # Handle various cases:
        # 1. Simple: "void doSomething("
        # 2. With modifiers: "static void doSomething("
        # 3. Template: "std::vector<int> getValue("
        # 4. Pointer/reference: "void* getData("
        
        # Remove any 'static' keyword from implementation
        signature = re.sub(r'\bstatic\s+', '', signature)
        
        # Build the pattern to find method declaration
        # Escape special regex characters in return_type and method_name
        escaped_return = re.escape(return_type)
        escaped_method = re.escape(method_name)
        
        # Pattern: return_type followed by whitespace and method_name followed by (
        # But method_name should not already have :: before it
        pattern = rf'({escaped_return}\s+)({escaped_method}\s*\()'
        
        # Replace with qualified version
        replacement = rf'\1{class_name}::\2'
        
        qualified = re.sub(pattern, replacement, signature)
        
        return qualified
    
    def fix_cpp_file(self, cpp_path: Path, class_name: str) -> Tuple[bool, str]:
        """Fix class qualification in a cpp file"""
        try:
            with open(cpp_path, 'r', encoding='utf-8', errors='ignore') as f:
                original_content = f.read()
            
            # Find all function definitions
            functions = self.find_function_definitions(original_content)
            
            if not functions:
                return False, original_content
            
            # Work backwards to preserve line positions
            lines = original_content.split('\n')
            modified = False
            
            for line_num, return_type, method_name, signature in reversed(functions):
                # Get the lines for this function signature
                sig_lines = signature.split('\n')
                sig_line_count = len(sig_lines)
                
                # Qualify the signature
                qualified_sig = self.qualify_method(signature, class_name, return_type, method_name)
                
                if qualified_sig != signature:
                    # Replace the lines
                    qualified_lines = qualified_sig.split('\n')
                    lines[line_num:line_num + sig_line_count] = qualified_lines
                    modified = True
                    self.stats['methods_qualified'] += 1
            
            new_content = '\n'.join(lines)
            return modified, new_content
            
        except Exception as e:
            print(f"Error fixing {cpp_path}: {e}")
            self.stats['errors'] += 1
            return False, original_content
    
    def process_cpp_file(self, cpp_path: Path) -> bool:
        """Process a single cpp file"""
        # Find corresponding header
        header_path = cpp_path.with_suffix('.h')
        
        if not header_path.exists():
            return False
        
        # Extract class name from header
        class_name = self.extract_class_name_from_header(header_path)
        
        if not class_name:
            return False
        
        # Fix the cpp file
        modified, new_content = self.fix_cpp_file(cpp_path, class_name)
        
        if modified:
            # Write back
            with open(cpp_path, 'w', encoding='utf-8') as f:
                f.write(new_content)
            return True
        
        return False
    
    def process_directory(self, directory: str):
        """Process all cpp files in directory"""
        dir_path = Path(directory)
        
        print(f"Processing directory: {dir_path}")
        print()
        
        # Find all .cpp files
        cpp_files = list(dir_path.rglob('*.cpp'))
        print(f"Found {len(cpp_files)} cpp files")
        print()
        
        for i, cpp_file in enumerate(cpp_files, 1):
            if i % 100 == 0:
                print(f"Progress: {i}/{len(cpp_files)} files processed...")
            
            self.stats['files_processed'] += 1
            if self.process_cpp_file(cpp_file):
                self.stats['files_fixed'] += 1
        
        self.print_report()
    
    def print_report(self):
        """Print processing report"""
        print("\n" + "="*60)
        print("C++ Class Qualification Fix Report")
        print("="*60)
        print(f"Files processed: {self.stats['files_processed']}")
        print(f"Files fixed: {self.stats['files_fixed']}")
        print(f"Methods qualified: {self.stats['methods_qualified']}")
        if self.stats['errors'] > 0:
            print(f"Errors: {self.stats['errors']}")
        print("="*60 + "\n")


def main():
    if len(sys.argv) < 2:
        print("Usage: python fix_cpp_class_qualification.py <directory>")
        print("Example: python fix_cpp_class_qualification.py Convert2Cpp")
        sys.exit(1)
    
    directory = sys.argv[1]
    
    if not os.path.exists(directory):
        print(f"Error: Directory does not exist: {directory}")
        sys.exit(1)
    
    fixer = CppQualificationFixer()
    fixer.process_directory(directory)


if __name__ == '__main__':
    main()
