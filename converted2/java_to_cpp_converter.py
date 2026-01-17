#!/usr/bin/env python3
"""
Java to C++ Automated Converter for Project Zomboid
Converts Java source files to C++ with SDL2/modern C++ patterns
"""

import os
import re
import sys
from pathlib import Path
from typing import Dict, List, Tuple

class JavaToCppConverter:
    def __init__(self):
        self.type_mappings = {
            # Java collections
            'String': 'std::string',
            'ArrayList': 'std::vector',
            'List': 'std::vector',
            'HashMap': 'std::unordered_map',
            'Map': 'std::unordered_map',
            'HashSet': 'std::unordered_set',
            'Set': 'std::unordered_set',
            'Queue': 'std::queue',
            'Stack': 'std::stack',
            'Deque': 'std::deque',
            
            # Java boxed types -> C++ primitives
            'Integer': 'int',
            'Float': 'float',
            'Double': 'double',
            'Boolean': 'bool',
            'Long': 'long',
            'Short': 'short',
            'Byte': 'uint8_t',
            'Character': 'char',
            
            # Java primitives (already C++)
            'void': 'void',
            'int': 'int',
            'float': 'float',
            'double': 'double',
            'boolean': 'bool',
            'long': 'long',
            'short': 'short',
            'byte': 'uint8_t',
            'char': 'char',
            
            # Java special types
            'Object': 'void*',
            'Throwable': 'std::exception',
            'Exception': 'std::exception',
            'RuntimeException': 'std::runtime_error',
            'IOException': 'std::ios_base::failure',
        }
        
        # Types that should use smart pointers
        self.smart_ptr_types = {
            'String', 'ArrayList', 'List', 'HashMap', 'Map', 'HashSet', 'Set',
            'Queue', 'Stack', 'Deque', 'BufferedImage', 'BufferedReader',
            'FileReader', 'FileWriter', 'BufferedInputStream', 'BufferedOutputStream'
        }
        
        self.stats = {
            'files_processed': 0,
            'files_success': 0,
            'files_failed': 0,
            'lines_converted': 0,
        }

    def parse_package(self, line: str) -> List[str]:
        """Parse Java package declaration into namespace parts"""
        match = re.match(r'package\s+([\w.]+);', line)
        if match:
            package = match.group(1)
            return package.split('.')
        return []

    def convert_imports_to_includes(self, line: str) -> str:
        """Convert Java imports to C++ includes"""
        if not line.strip().startswith('import '):
            return ''

        wildcard = '.*' in line
        match = re.match(r'import\s+([\w.]+)(?:\.\*)?;', line)
        if not match:
            return ''

        import_path = match.group(1)
        class_name = import_path.split('.')[-1]

        if wildcard:
            # For wildcard imports, try to map common packages
            if import_path.endswith('.java.util'):
                return '#include <vector>\n#include <unordered_map>\n#include <unordered_set>\n#include <deque>\n#include <queue>\n#include <stack>\n'
            if import_path.endswith('.java.io'):
                return '#include <fstream>\n#include <iostream>\n#include <sstream>\n'
            if import_path.endswith('.java.nio'):
                return '#include <cstdint>\n'
            # For project packages, emit a TODO comment instead
            return f'// TODO: include all classes from {import_path}\n'

        # Standard library mappings
        if import_path.startswith('java.util'):
            if class_name in ['ArrayList', 'List', 'Vector', 'Collection', 'Collections']:
                return '#include <vector>\n'
            if class_name in ['HashMap', 'Map', 'TreeMap']:
                return '#include <unordered_map>\n'
            if class_name in ['HashSet', 'Set', 'TreeSet']:
                return '#include <unordered_set>\n'
            if class_name in ['Iterator', 'Enumeration']:
                return '#include <iterator>\n'
            return '#include <algorithm>\n'

        if import_path.startswith('java.io'):
            return '#include <fstream>\n#include <iostream>\n'

        if import_path.startswith('java.nio'):
            return '#include <filesystem>\n#include <cstdint>\n'

        if import_path.startswith('java.lang'):
            return ''  # java.lang is implicit

        # Project-local include: convert package path to header path
        path = import_path.replace('.', '/') + '.h'
        return f'#include "{path}"\n'

    def convert_class_declaration(self, line: str) -> str:
        """Convert Java class to C++ class"""
        # public class Foo extends Bar implements Baz
        match = re.match(r'(public\s+|private\s+|protected\s+)?(?:abstract\s+|final\s+)?(class|interface|enum)\s+(\w+)(?:\s+extends\s+(\w+))?(?:\s+implements\s+([\w,\s]+))?', line)
        if match:
            visibility = match.group(1) or ''
            class_type = match.group(2)
            class_name = match.group(3)
            extends = match.group(4)
            
            if class_type == 'interface':
                result = f'class {class_name} {{\npublic:\n    virtual ~{class_name}() = default;\n'
            elif class_type == 'enum':
                result = f'enum class {class_name} {{\n'
            else:
                inheritance = f' : public {extends}' if extends else ''
                result = f'class {class_name}{inheritance} {{\npublic:\n'
            return result
        return line

    def convert_method_declaration(self, line: str, store_methods: List[dict] = None) -> str:
        """Convert Java method to C++ method"""
        # public void doSomething(int x, String y) {
        match = re.match(r'\s*(public|private|protected)?\s*(static)?\s*(final)?\s*(\w+)\s+(\w+)\s*\((.*?)\)\s*\{?', line)
        if match:
            visibility = match.group(1) or 'public'
            is_static = match.group(2)
            return_type = match.group(4)
            method_name = match.group(5)
            params = match.group(6)
            
            # Convert return type
            cpp_return = self.type_mappings.get(return_type, return_type)
            
            # Convert parameters
            cpp_params = self.convert_parameters(params)
            
            # Add static if needed
            static_str = 'static ' if is_static else ''
            
            result = f'    {static_str}{cpp_return} {method_name}({cpp_params})'
            if line.rstrip().endswith('{'):
                result += ' {'
            else:
                result += ';'
            
            # Store for later .cpp generation if requested
            if store_methods is not None:
                store_methods.append({
                    'return_type': return_type,
                    'cpp_return': cpp_return,
                    'method_name': method_name,
                    'params': cpp_params,
                    'is_static': bool(is_static),
                })
            
            return result + '\n'
        return line

    def convert_parameters(self, params: str) -> str:
        """Convert Java parameters to C++ parameters"""
        if not params or params.strip() == '':
            return ''
        
        cpp_params = []
        for param in params.split(','):
            param = param.strip()
            if param:
                # Split type and name
                parts = param.split()
                if len(parts) >= 2:
                    param_type = parts[0]
                    param_name = parts[1]
                    cpp_type = self.type_mappings.get(param_type, param_type)
                    
                    # Add const& for string/vector types
                    if cpp_type in ['std::string', 'std::vector']:
                        cpp_type = f'const {cpp_type}&'
                    
                    cpp_params.append(f'{cpp_type} {param_name}')
        
        return ', '.join(cpp_params)

    def convert_field_declaration(self, line: str) -> str:
        """Convert Java field to C++ member variable"""
        # private int myField = 0;
        match = re.match(r'\s*(public|private|protected)?\s*(static)?\s*(final)?\s*(\w+)\s+(\w+)\s*(?:=\s*([^;]+))?\s*;', line)
        if match:
            visibility = match.group(1) or 'private'
            is_static = match.group(2)
            is_final = match.group(3)
            field_type = match.group(4)
            field_name = match.group(5)
            initializer = match.group(6)
            
            cpp_type = self.type_mappings.get(field_type, field_type)
            
            # Add const for final
            const_str = 'const ' if is_final else ''
            static_str = 'static ' if is_static else ''
            
            result = f'    {static_str}{const_str}{cpp_type} {field_name}'
            if initializer:
                result += f' = {initializer}'
            result += ';\n'
            return result
        return line

    def convert_new_keyword(self, line: str) -> str:
        """Convert Java new to C++ smart pointers or stack allocation"""
        # Handle generic collections first
        line = re.sub(r'new\s+ArrayList<(\w+)>\(\)', 
                     lambda m: f'std::make_unique<std::vector<{self.type_mappings.get(m.group(1), m.group(1))}>>()', 
                     line)
        line = re.sub(r'new\s+HashMap<(\w+),\s*(\w+)>\(\)', 
                     lambda m: f'std::make_unique<std::unordered_map<{self.type_mappings.get(m.group(1), m.group(1))}, {self.type_mappings.get(m.group(2), m.group(2))}>>()', 
                     line)
        line = re.sub(r'new\s+HashSet<(\w+)>\(\)', 
                     lambda m: f'std::make_unique<std::unordered_set<{self.type_mappings.get(m.group(1), m.group(1))}>>()', 
                     line)
        
        # Handle non-generic new: new ClassName() → std::make_unique<ClassName>()
        line = re.sub(r'\bnew\s+(\w+)\s*\(\)', r'std::make_unique<\1>()', line)
        
        # Handle generics without parameters: new ClassName<T>() → std::make_unique<ClassName<T>>()
        line = re.sub(r'\bnew\s+([\w<>]+)\s*\(\)', r'std::make_unique<\1>()', line)
        
        return line

    def convert_for_each_loop(self, line: str) -> str:
        """Convert Java for-each to C++ range-based for"""
        # for (String item : items) → for (auto& item : items)
        match = re.match(r'\s*for\s*\(\s*(\w+)\s+(\w+)\s*:\s*(\w+)\s*\)', line)
        if match:
            item_name = match.group(2)
            collection = match.group(3)
            return f'    for (auto& {item_name} : {collection})'
        return line

    def convert_null_to_nullptr(self, line: str) -> str:
        """Convert null to nullptr"""
        return re.sub(r'\bnull\b', 'nullptr', line)

    def convert_boolean_literals(self, line: str) -> str:
        """Convert true/false (already compatible)"""
        return line

    def convert_string_operations(self, line: str) -> str:
        """Convert Java String operations to C++ std::string"""
        # .length() is compatible
        # .equals() → ==
        line = re.sub(r'\.equals\(', ' == ', line)
        return line

    def get_default_return_value(self, return_type: str) -> str:
        """Get default return value for a C++ type"""
        cpp_type = self.type_mappings.get(return_type, return_type)
        if cpp_type == 'void':
            return ''
        if cpp_type in ['int', 'float', 'double', 'long', 'short', 'uint8_t', 'char']:
            return '0'
        if cpp_type == 'bool':
            return 'false'
        if cpp_type == 'std::string':
            return '""'
        if 'vector' in cpp_type or 'map' in cpp_type or 'set' in cpp_type:
            return '{}'
        # For pointers and objects, return nullptr or default construct
        return 'nullptr'

    def convert_line(self, line: str, collected_methods: List[dict] = None) -> str:
        """Apply all conversions to a single line"""
        original = line
        
        # Remove Java annotations (@Override, @Deprecated, etc.)
        if line.strip().startswith('@'):
            return ''
        
        # Package/imports
        if line.strip().startswith('package '):
            return self.convert_package_to_namespace(line)
        if line.strip().startswith('import '):
            return self.convert_imports_to_includes(line)
        
        # Comments (skip)
        if line.strip().startswith('//') or line.strip().startswith('/*') or line.strip().startswith('*'):
            return line
        
        # Class/interface declarations
        if re.search(r'\b(class|interface|enum)\s+\w+', line):
            return self.convert_class_declaration(line)

        # Field declarations
        field_converted = self.convert_field_declaration(line)
        if field_converted != line:
            return field_converted

        # Method declarations
        method_converted = self.convert_method_declaration(line, collected_methods)
        if method_converted != line:
            return method_converted
        
        # Apply transformations
        line = self.convert_null_to_nullptr(line)
        line = self.convert_new_keyword(line)
        line = self.convert_for_each_loop(line)
        line = self.convert_string_operations(line)
        
        return line

    def convert_file(self, java_file: Path, output_dir: Path) -> Tuple[bool, str]:
        """Convert a single Java file to C++"""
        try:
            with open(java_file, 'r', encoding='utf-8', errors='ignore') as f:
                java_code = f.readlines()

            # Basic metadata
            class_name = java_file.stem
            package_parts: List[str] = []
            include_set: Dict[str, None] = {}
            body_lines: List[str] = []
            collected_methods: List[dict] = []

            # First pass: collect package/imports
            for line in java_code:
                if not package_parts:
                    package_parts = self.parse_package(line)
                    if package_parts:
                        continue

                inc = self.convert_imports_to_includes(line)
                if inc:
                    for inc_line in inc.strip().split('\n'):
                        if inc_line:
                            include_set[inc_line + '\n'] = None
                    continue

                body_lines.append(line)

            # Determine output paths (mirror package folders)
            relative_dir = Path('/'.join(package_parts)) if package_parts else Path('')
            header_file = output_dir / 'include' / relative_dir / f'{class_name}.h'
            source_file = output_dir / 'src' / relative_dir / f'{class_name}.cpp'
            include_path_for_cpp = f"{relative_dir}/{class_name}.h" if relative_dir.as_posix() != '.' else f"{class_name}.h"

            # Header preamble
            header_lines: List[str] = [
                '#pragma once\n',
                '#include <string>\n',
                '#include <vector>\n',
                '#include <memory>\n',
                '#include <unordered_map>\n',
                '#include <unordered_set>\n',
                '#include <cstdint>\n',
            ]

            # Add converted includes (deduped)
            for inc_line in sorted(include_set.keys()):
                if inc_line not in header_lines:
                    header_lines.append(inc_line)
            header_lines.append('\n')

            # Namespace openings
            for part in package_parts:
                header_lines.append(f'namespace {part} {{\n')

            # Convert body lines and collect methods
            for line in body_lines:
                converted = self.convert_line(line, collected_methods)
                header_lines.append(converted)
                self.stats['lines_converted'] += 1

            # Close namespaces
            for part in reversed(package_parts):
                header_lines.append(f'}} // namespace {part}\n')

            # Write header file
            header_file.parent.mkdir(parents=True, exist_ok=True)
            with open(header_file, 'w', encoding='utf-8') as f:
                f.writelines(header_lines)

            # Write source file with method stubs
            source_lines = [f'#include "{include_path_for_cpp}"\n', '\n']
            
            # Add namespace openings
            for part in package_parts:
                source_lines.append(f'namespace {part} {{\n')
            source_lines.append('\n')
            
            # Add method implementations
            for method in collected_methods:
                default_return = self.get_default_return_value(method['return_type'])
                cpp_type = method['cpp_return']
                
                sig = f"{cpp_type} {class_name}::{method['method_name']}({method['params']})"
                if cpp_type == 'void':
                    source_lines.append(f'{sig} {{\n    // TODO: Implement {method["method_name"]}\n}}\n\n')
                else:
                    source_lines.append(f'{sig} {{\n    // TODO: Implement {method["method_name"]}\n    return {default_return};\n}}\n\n')
            
            # Close namespaces
            for part in reversed(package_parts):
                source_lines.append(f'}} // namespace {part}\n')
            
            source_file.parent.mkdir(parents=True, exist_ok=True)
            with open(source_file, 'w', encoding='utf-8') as f:
                f.writelines(source_lines)

            self.stats['files_success'] += 1
            return True, f'Converted: {java_file.name} → {header_file}'

        except Exception as e:
            self.stats['files_failed'] += 1
            return False, f'Failed: {java_file.name} - {str(e)}'

    def convert_directory(self, source_dir: Path, output_dir: Path, max_files: int = None):
        """Convert all Java files in a directory"""
        java_files = list(source_dir.rglob('*.java'))
        
        if max_files:
            java_files = java_files[:max_files]
        
        print(f'Found {len(java_files)} Java files to convert')
        print(f'Output directory: {output_dir}')
        print('=' * 60)
        
        for i, java_file in enumerate(java_files, 1):
            self.stats['files_processed'] += 1
            success, message = self.convert_file(java_file, output_dir)
            
            if success:
                print(f'[{i}/{len(java_files)}] ✓ {message}')
            else:
                print(f'[{i}/{len(java_files)}] ✗ {message}')
        
        print('=' * 60)
        print('Conversion Summary:')
        print(f'  Files Processed: {self.stats["files_processed"]}')
        print(f'  Files Success:   {self.stats["files_success"]}')
        print(f'  Files Failed:    {self.stats["files_failed"]}')
        print(f'  Lines Converted: {self.stats["lines_converted"]}')
        print(f'  Success Rate:    {self.stats["files_success"]/max(1, self.stats["files_processed"])*100:.1f}%')

def main():
    if len(sys.argv) < 3:
        print('Usage: python3 java_to_cpp_converter.py <source_dir> <output_dir> [max_files]')
        print('Example: python3 java_to_cpp_converter.py /workspaces/PZ/src/zombie /workspaces/PZ/converted2 50')
        sys.exit(1)
    
    source_dir = Path(sys.argv[1])
    output_dir = Path(sys.argv[2])
    max_files = int(sys.argv[3]) if len(sys.argv) > 3 else None
    
    if not source_dir.exists():
        print(f'Error: Source directory does not exist: {source_dir}')
        sys.exit(1)
    
    converter = JavaToCppConverter()
    converter.convert_directory(source_dir, output_dir, max_files)

if __name__ == '__main__':
    main()
