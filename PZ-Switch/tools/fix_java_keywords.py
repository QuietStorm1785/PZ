#!/usr/bin/env python3
"""
Fix Java keyword artifacts in converted C++ code.
- Replace 'final' with 'const' for variable/parameter declarations
- Remove 'final' when used with class/interface declarations
- Remove 'abstract' keywords

Usage:
  python3 tools/fix_java_keywords.py <root_dir>
"""
import os
import re
import sys

FINAL_VAR_PATTERN = re.compile(r"\bfinal\s+")
FINAL_CLASS_PATTERN = re.compile(r"\bfinal\s+(class|struct)\b")
ABSTRACT_PATTERN = re.compile(r"\babstract\s+")

# Rough heuristic: if 'final' appears before class/struct, drop it; otherwise change to 'const '

def fix_content(path: str, text: str) -> str:
    # Remove 'abstract' everywhere it appears as a standalone keyword
    text = ABSTRACT_PATTERN.sub("", text)

    # Replace 'final' before class/struct with nothing
    text = FINAL_CLASS_PATTERN.sub(lambda m: m.group(1), text)

    # Replace remaining 'final' with 'const '
    text = FINAL_VAR_PATTERN.sub("const ", text)

    return text


def process_file(root: str, relpath: str) -> bool:
    full = os.path.join(root, relpath)
    try:
        with open(full, 'r', encoding='utf-8') as f:
            original = f.read()
        fixed = fix_content(full, original)
        if fixed != original:
            with open(full, 'w', encoding='utf-8') as f:
                f.write(fixed)
            return True
    except Exception as e:
        print(f"[WARN] Failed to process {full}: {e}")
    return False


def is_source_file(name: str) -> bool:
    return name.endswith(('.h', '.hpp', '.hh', '.cpp', '.cc', '.cxx'))


def walk_and_fix(root: str) -> int:
    changed = 0
    for dirpath, _, filenames in os.walk(root):
        for fn in filenames:
            if not is_source_file(fn):
                continue
            rel = os.path.relpath(os.path.join(dirpath, fn), root)
            changed += 1 if process_file(root, rel) else 0
    return changed


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 tools/fix_java_keywords.py <root_dir>")
        sys.exit(1)
    root = sys.argv[1]
    changed = walk_and_fix(root)
    print(f"[INFO] fix_java_keywords changed {changed} files under {root}")

if __name__ == '__main__':
    main()
