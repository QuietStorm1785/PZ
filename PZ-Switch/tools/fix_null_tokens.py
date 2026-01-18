#!/usr/bin/env python3
"""
Replace standalone Java 'null' tokens with C++ 'nullptr'.
Skips replacements inside obvious string literals.

Usage:
  python3 tools/fix_null_tokens.py <root_dir>
"""
import os
import re
import sys

# Word-boundary match for null not inside quotes (basic heuristic)
NULL_PATTERN = re.compile(r"\bnull\b")
STRING_LITERAL = re.compile(r'"([^"\\]|\\.)*"')


def replace_outside_strings(text: str) -> str:
    # Split by double-quote strings and only replace in non-string segments
    parts = []
    last = 0
    for m in STRING_LITERAL.finditer(text):
        segment = text[last:m.start()]
        segment = NULL_PATTERN.sub("nullptr", segment)
        parts.append(segment)
        parts.append(text[m.start():m.end()])  # original string literal
        last = m.end()
    tail = text[last:]
    tail = NULL_PATTERN.sub("nullptr", tail)
    parts.append(tail)
    return ''.join(parts)


def process_file(path: str) -> bool:
    try:
        with open(path, 'r', encoding='utf-8') as f:
            original = f.read()
        fixed = replace_outside_strings(original)
        if fixed != original:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(fixed)
            return True
    except Exception as e:
        print(f"[WARN] Failed to process {path}: {e}")
    return False


def is_source_file(name: str) -> bool:
    return name.endswith(('.h', '.hpp', '.hh', '.cpp', '.cc', '.cxx'))


def walk_and_fix(root: str) -> int:
    changed = 0
    for dirpath, _, filenames in os.walk(root):
        for fn in filenames:
            if not is_source_file(fn):
                continue
            full = os.path.join(dirpath, fn)
            changed += 1 if process_file(full) else 0
    return changed


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 tools/fix_null_tokens.py <root_dir>")
        sys.exit(1)
    root = sys.argv[1]
    changed = walk_and_fix(root)
    print(f"[INFO] fix_null_tokens changed {changed} files under {root}")

if __name__ == '__main__':
    main()
