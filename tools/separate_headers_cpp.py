#!/usr/bin/env python3
"""
Separate C++ Header Files into .h (declarations) and .cpp (implementations)
Processes header files and extracts function/method implementations into separate .cpp files
"""

import os
import re
import sys
from pathlib import Path
from typing import List, Tuple, Optional

class HeaderSeparator:
    def __init__(self):
        self.stats = {
            'files_processed': 0,
            'files_separated': 0,
            'methods_extracted': 0,
            'errors': 0
        }
    
    def extract_namespace(self, content: str) -> Optional[str]:
        """Extract the namespace from the file"""
        match = re.search(r'namespace\s+(\w+)\s*{', content)
        return match.group(1) if match else None
    
    def extract_class_name(self, content: str) -> Optional[str]:
        """Extract the main class name from the file"""
        match = re.search(r'class\s+(\w+)\s*{', content)
        return match.group(1) if match else None
    
    def find_method_implementations(self, content: str) -> List[Tuple[int, int, str]]:
        """Find all method implementations in the file (inside class definition)"""
        implementations = []
        lines = content.split('\n')
        in_class = False
        brace_count = 0
        class_brace_level = 0
        method_start = -1
        method_lines = []
        
        for i, line in enumerate(lines):
            stripped = line.strip()
            
            # Track class definition
            if re.match(r'class\s+\w+', stripped):
                in_class = True
                class_brace_level = 0
            
            if in_class:
                # Count braces
                brace_count += line.count('{') - line.count('}')
                
                # Check if this is a method definition (has { and not just declaration)
                if '{' in line and method_start == -1:
                    # Check if it's a method (not class or namespace opening)
                    if not re.match(r'(class|struct|namespace|enum)\s+\w+', stripped):
                        # Look back to find the method signature
                        sig_start = i
                        for j in range(i-1, max(0, i-10), -1):
                            if lines[j].strip().startswith('//') or lines[j].strip().startswith('/*'):
                                continue
                            if re.search(r'(static\s+)?\w+[\w\s<>,:\*&]*\s+\w+\s*\([^)]*\)', lines[j]):
                                sig_start = j
                                break
                        method_start = sig_start
                        method_lines = []
                
                # Collect method lines
                if method_start != -1:
                    method_lines.append(line)
                    
                    # Check if method is complete
                    if brace_count == class_brace_level + 1 and '}' in line:
                        # Method implementation complete
                        impl = '\n'.join(method_lines)
                        implementations.append((method_start, i, impl))
                        method_start = -1
                        method_lines = []
                
                # Track when we exit the class
                if brace_count == 0 and in_class and i > 0:
                    in_class = False
        
        return implementations
    
    def create_header_file(self, content: str, implementations: List[Tuple[int, int, str]]) -> str:
        """Create header file with only declarations"""
        lines = content.split('\n')
        
        # Remove method implementations, keep only declarations
        result_lines = []
        skip_until = -1
        
        for i, line in enumerate(lines):
            if i < skip_until:
                continue
            
            # Check if this line is part of an implementation
            is_impl_line = False
            for start, end, impl in implementations:
                if start <= i <= end:
                    is_impl_line = True
                    skip_until = end + 1
                    
                    # Extract just the method signature and make it a declaration
                    sig_lines = []
                    for j in range(start, min(start + 10, end)):
                        sig_lines.append(lines[j])
                        if '{' in lines[j]:
                            break
                    
                    # Convert to declaration
                    signature = '\n'.join(sig_lines)
                    signature = re.sub(r'\s*{.*$', ';', signature, flags=re.DOTALL)
                    result_lines.append(signature.strip())
                    break
            
            if not is_impl_line:
                result_lines.append(line)
        
        return '\n'.join(result_lines)
    
    def create_cpp_file(self, header_path: str, namespace: str, class_name: str, 
                       implementations: List[Tuple[int, int, str]], header_content: str) -> str:
        """Create .cpp file with implementations"""
        cpp_content = []
        
        # Add include for the header
        rel_header = os.path.basename(header_path)
        cpp_content.append(f'#include "{rel_header}"')
        cpp_content.append('')
        
        # Extract includes from header that might be needed
        includes = re.findall(r'#include\s+[<"]([^>"]+)[>"]', header_content)
        
        # Add namespace if present
        if namespace:
            cpp_content.append(f'namespace {namespace} {{')
            cpp_content.append('')
        
        # Add each implementation
        for start, end, impl in implementations:
            # Extract method signature
            sig_match = re.search(r'(static\s+)?(\w+[\w\s<>,:\*&]*)\s+(\w+)\s*\([^)]*\)', impl)
            if sig_match:
                is_static = sig_match.group(1) is not None
                return_type = sig_match.group(2).strip()
                method_name = sig_match.group(3)
                
                # Create qualified method name
                if not is_static and class_name:
                    qualified_impl = impl.replace(f'{return_type} {method_name}', 
                                                 f'{return_type} {class_name}::{method_name}')
                else:
                    qualified_impl = impl
                
                # Remove 'static' keyword for implementation
                qualified_impl = re.sub(r'\bstatic\s+', '', qualified_impl)
                
                cpp_content.append(qualified_impl)
                cpp_content.append('')
        
        if namespace:
            cpp_content.append('}  // namespace ' + namespace)
        
        return '\n'.join(cpp_content)
    
    def process_file(self, filepath: Path, src_dir: Path, output_dir: Path) -> bool:
        """Process a single header file"""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            # Check if file has implementations
            implementations = self.find_method_implementations(content)
            
            if not implementations:
                # No implementations found, just copy as-is
                return False
            
            # Extract metadata
            namespace = self.extract_namespace(content)
            class_name = self.extract_class_name(content)
            
            # Create new header with declarations only
            new_header = self.create_header_file(content, implementations)
            
            # Create cpp file with implementations
            cpp_content = self.create_cpp_file(str(filepath), namespace, class_name, 
                                              implementations, content)
            
            # Determine output paths
            rel_path = filepath.relative_to(src_dir)
            header_out = output_dir / rel_path
            cpp_out = header_out.with_suffix('.cpp')
            
            # Create directories
            header_out.parent.mkdir(parents=True, exist_ok=True)
            cpp_out.parent.mkdir(parents=True, exist_ok=True)
            
            # Write files
            with open(header_out, 'w', encoding='utf-8') as f:
                f.write(new_header)
            
            with open(cpp_out, 'w', encoding='utf-8') as f:
                f.write(cpp_content)
            
            self.stats['methods_extracted'] += len(implementations)
            return True
            
        except Exception as e:
            print(f"Error processing {filepath}: {e}")
            self.stats['errors'] += 1
            return False
    
    def process_directory(self, src_dir: str, output_dir: str = None):
        """Process all header files in directory"""
        src_path = Path(src_dir)
        
        if output_dir is None:
            # Create output in parent directory
            output_path = src_path.parent / 'src_separated'
        else:
            output_path = Path(output_dir)
        
        print(f"Processing headers from: {src_path}")
        print(f"Output directory: {output_path}")
        print()
        
        # Find all .h files
        header_files = list(src_path.rglob('*.h'))
        print(f"Found {len(header_files)} header files")
        print()
        
        for i, filepath in enumerate(header_files, 1):
            if i % 100 == 0:
                print(f"Progress: {i}/{len(header_files)} files processed...")
            
            self.stats['files_processed'] += 1
            if self.process_file(filepath, src_path, output_path):
                self.stats['files_separated'] += 1
        
        self.print_report()
    
    def print_report(self):
        """Print processing report"""
        print("\n" + "="*60)
        print("Header Separation Report")
        print("="*60)
        print(f"Files processed: {self.stats['files_processed']}")
        print(f"Files separated: {self.stats['files_separated']}")
        print(f"Methods extracted: {self.stats['methods_extracted']}")
        if self.stats['errors'] > 0:
            print(f"Errors: {self.stats['errors']}")
        print("="*60 + "\n")


def main():
    if len(sys.argv) < 2:
        print("Usage: python separate_headers_cpp.py <include_directory> [output_directory]")
        print("Example: python separate_headers_cpp.py Convert2Cpp/src/include")
        sys.exit(1)
    
    src_dir = sys.argv[1]
    output_dir = sys.argv[2] if len(sys.argv) > 2 else None
    
    if not os.path.exists(src_dir):
        print(f"Error: Directory does not exist: {src_dir}")
        sys.exit(1)
    
    separator = HeaderSeparator()
    separator.process_directory(src_dir, output_dir)


if __name__ == '__main__':
    main()
