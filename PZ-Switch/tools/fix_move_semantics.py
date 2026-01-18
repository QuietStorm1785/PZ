#!/usr/bin/env python3
"""
Fix common move semantics issues introduced by Java→C++ conversion.
- Convert 'std::string&&' function parameters to 'const std::string&'
- Replace 'std::move(var)' with 'var' when 'var' is a const std::string in scope

Usage:
  python3 tools/fix_move_semantics.py <root_dir>
"""
import os
import re
import sys

STR_RVALUE_PARAM = re.compile(r"\bstd::string\s*&&")
STR_RVALUE_PARAM_SHORT = re.compile(r"\bstring\s*&&")
MOVE_CALL = re.compile(r"std::move\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)")
CONST_STR_DECL = re.compile(r"\bconst\s+std::string\s+([A-Za-z_][A-Za-z0-9_]*)\b|\bconst\s+string\s+([A-Za-z_][A-Za-z0-9_]*)\b")


def fix_params(text: str) -> str:
    text = STR_RVALUE_PARAM.sub("const std::string&", text)
    text = STR_RVALUE_PARAM_SHORT.sub("const std::string&", text)
    return text


def fix_moves(text: str) -> str:
    # Gather const string variable names in file (simple heuristic)
    const_names = set()
    for m in CONST_STR_DECL.finditer(text):
        name = m.group(1) or m.group(2)
        if name:
            const_names.add(name)

    def repl(m):
        var = m.group(1)
        if var in const_names:
            return var
        return m.group(0)  # leave std::move if not const

    return MOVE_CALL.sub(repl, text)


def process_file(path: str) -> bool:
    try:
        with open(path, 'r', encoding='utf-8') as f:
            original = f.read()
        fixed = fix_params(original)
        fixed = fix_moves(fixed)
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
        print("Usage: python3 tools/fix_move_semantics.py <root_dir>")
        sys.exit(1)
    root = sys.argv[1]
    changed = walk_and_fix(root)
    print(f"[INFO] fix_move_semantics changed {changed} files under {root}")

if __name__ == '__main__':
    main()
