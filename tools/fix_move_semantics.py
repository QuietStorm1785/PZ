#!/usr/bin/env python3
"""
Fix common Java→C++ move semantics issues:
- Remove std::move() when applied to const std::string variables (illegal)
- Normalize `const std::string&&` → `const std::string&`
- Normalize `std::string&&` → `std::string` (value) for declarations/parameters

Heuristics:
- Detect const string identifiers in each file, then strip std::move(id)
- Apply safe textual replacements for && on string types

Usage:
    python3 fix_move_semantics.py <directory>
"""

import os
import re
import sys
from pathlib import Path

CONST_STRING_DECL = re.compile(r"\bconst\s+(?:std::)?string\s+([A-Za-z_][A-Za-z0-9_]*)\b")
MOVE_OF_ID = lambda ident: re.compile(rf"std::move\(\s*{re.escape(ident)}\s*\)")

# Patterns to normalize rvalue refs on strings
DECL_CONST_RR = re.compile(r"\bconst\s+(std::)?string\s*&&\s*")
DECL_RR = re.compile(r"\b(std::)?string\s*&&\s*")


def process_content(content: str) -> str:
    # Collect const string identifiers
    const_ids = set(CONST_STRING_DECL.findall(content))
    result = content

    # Remove std::move(constStringId)
    for ident in const_ids:
        result = MOVE_OF_ID(ident).sub(ident, result)

    # Normalize const string rvalue refs to lvalue refs
    result = DECL_CONST_RR.sub(lambda m: f"const {m.group(1) or ''}string& ", result)

    # Normalize plain string rvalue refs to value semantics
    # Prefer value to avoid accidental binding to const lvalues
    result = DECL_RR.sub(lambda m: f"{m.group(1) or ''}string ", result)

    return result


def process_file(filepath: str) -> bool:
    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
        new_content = process_content(content)
        if new_content != content:
            with open(filepath, 'w', encoding='utf-8') as f:
                f.write(new_content)
            return True
        return False
    except Exception as e:
        print(f"Error processing {filepath}: {e}", file=sys.stderr)
        return False


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 fix_move_semantics.py <directory>")
        sys.exit(1)
    root_dir = sys.argv[1]
    if not os.path.isdir(root_dir):
        print(f"Error: {root_dir} is not a directory")
        sys.exit(1)

    files = []
    for ext in ['*.h', '*.hpp', '*.cpp', '*.cc']:
        files.extend(Path(root_dir).rglob(ext))

    fixed = 0
    total = len(files)
    print(f"Scanning {total} files for move semantics fixes...")

    for i, path in enumerate(files, 1):
        if i % 200 == 0:
            print(f"  Processed {i}/{total}...")
        if process_file(str(path)):
            fixed += 1
            try:
                rel = Path(path).relative_to(root_dir)
            except Exception:
                rel = path
            print(f"Fixed: {rel}")

    print(f"\nFixed {fixed} files")


if __name__ == '__main__':
    sys.exit(main())
