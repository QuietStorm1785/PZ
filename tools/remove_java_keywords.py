#!/usr/bin/env python3
"""
Remove/translate Java keywords that don't map directly to C++.

Updates:
- Translate `static final` → `static const` (safe default across types)
- Translate standalone `final` modifiers on fields/locals → `const`
- Remove other Java-only modifiers: abstract, volatile, transient, strictfp, native

Note: We intentionally avoid mapping Java `final class Foo` to C++ `class Foo final`
because the decompiler output often places modifiers in non-standard positions.
This tool focuses on eliminating syntax errors and producing compilable C++.
"""

import os
import re
import sys
from pathlib import Path

# Java keywords to remove (don't translate to C++)
JAVA_KEYWORDS_TO_REMOVE = [
    # final handled separately (translate rather than remove)
    r'\babstract\b',        # abstract classes/methods → remove (pure virtual)
    r'\bvolatile\b',        # volatile variables → remove (use std::atomic if needed)
    r'\btransient\b',       # transient fields → remove
    r'\bstrictfp\b',        # strictfp classes/methods → remove
    r'\bnative\b',          # native methods → remove marker
]

# Java keywords that should be replaced
KEYWORD_REPLACEMENTS = {
    r'\bpublic\s+class\b': 'class',           # public class → class
    r'\bprotected\s+class\b': 'class',        # protected class → class
    r'\bprivate\s+class\b': 'class',          # private class → class (use namespace/detail)
}

def translate_final_modifiers(content: str) -> str:
    """Translate Java `final` to C++ const forms.

    Rules:
    - `static final` → `static const`
    - standalone `final` (field/local) → `const`
    The replacements are conservative to improve compilation without overfitting types.
    """
    result = content
    # Replace `static final` with `static const`
    result = re.sub(r'\bstatic\s+final\b', 'static const', result)
    # Replace standalone `final` with `const` when used as a modifier before a type/name
    # Avoid cases like `class Foo final {}` by only replacing `final` followed by space and a type-ish token
    result = re.sub(r'\bfinal\s+(?=[A-Za-z_])', 'const ', result)
    return result


def remove_java_keywords(content):
    """Remove Java keywords from C++ code, after translating `final`.
    """
    # First translate `final` occurrences
    result = translate_final_modifiers(content)

    # Remove other Java-only keywords
    for keyword in JAVA_KEYWORDS_TO_REMOVE:
        # Match keyword followed by whitespace
        result = re.sub(keyword + r'\s+', ' ', result)
        # Match keyword at end of line
        result = re.sub(keyword + r'$', '', result, flags=re.MULTILINE)

    # Replace public/protected/private class declarations
    for pattern, replacement in KEYWORD_REPLACEMENTS.items():
        result = re.sub(pattern, replacement, result)

    # Clean up multiple spaces
    result = re.sub(r'  +', ' ', result)

    return result


def process_file(filepath):
    """Process a single file to remove Java keywords."""
    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
        
        new_content = remove_java_keywords(content)
        
        if content != new_content:
            with open(filepath, 'w', encoding='utf-8') as f:
                f.write(new_content)
            return True
        return False
    except Exception as e:
        print(f"Error processing {filepath}: {e}", file=sys.stderr)
        return False


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 remove_java_keywords.py <directory>")
        sys.exit(1)
    
    root_dir = sys.argv[1]
    
    if not os.path.isdir(root_dir):
        print(f"Error: {root_dir} is not a directory")
        sys.exit(1)
    
    # Find all C++ files
    files = []
    for ext in ['*.h', '*.hpp', '*.cpp', '*.cc']:
        files.extend(Path(root_dir).rglob(ext))
    
    fixed_count = 0
    total_count = len(files)
    
    print(f"Scanning {total_count} C++ files for Java keywords...")
    
    for i, filepath in enumerate(files, 1):
        if i % 100 == 0:
            print(f"  Processing: {i}/{total_count}")
        
        if process_file(str(filepath)):
            fixed_count += 1
            print(f"Fixed: {filepath.relative_to(root_dir) if root_dir != '.' else filepath.name}")
    
    print(f"\nFixed {fixed_count} files")
    return 0


if __name__ == '__main__':
    sys.exit(main())
