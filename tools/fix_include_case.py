import os
import re

SRC_ROOT = r"ProjectZomboidSwitch/src"
HEADER_EXTS = {'.h', '.hpp'}
SOURCE_EXTS = {'.cpp', '.c', '.cc'}
INCLUDE_RE = re.compile(r'#include\s+["<]([^">]+)[">]')

def build_file_index():
    """Build a dict mapping lowercase relative paths to actual paths (with correct case)."""
    file_index = {}
    for root, dirs, files in os.walk(SRC_ROOT):
        for f in files:
            rel_path = os.path.relpath(os.path.join(root, f), SRC_ROOT)
            rel_path_norm = rel_path.replace('\\', '/').replace('../', '')
            file_index[rel_path_norm.lower()] = rel_path_norm
    return file_index

def fix_case_includes():
    file_index = build_file_index()
    fixed = []
    unresolved = []
    scanned_files = 0
    total_includes = 0
    for root, dirs, files in os.walk(SRC_ROOT):
        for fname in files:
            if not (fname.endswith(tuple(SOURCE_EXTS)) or fname.endswith(tuple(HEADER_EXTS))):
                continue
            fpath = os.path.join(root, fname)
            rel_fpath = os.path.relpath(fpath, SRC_ROOT)
            scanned_files += 1
            print(f"Scanning: {rel_fpath}")
            with open(fpath, encoding='utf-8', errors='ignore') as f:
                lines = f.readlines()
            new_lines = []
            changed = False
            for line in lines:
                m = INCLUDE_RE.search(line)
                if m:
                    total_includes += 1
                    inc = m.group(1)
                    inc_norm = inc.replace('\\', '/').replace('../', '')
                    inc_key = inc_norm.lower()
                    if inc_key in file_index:
                        if inc_norm != file_index[inc_key]:
                            # Fix the include to match the actual file path
                            line = line.replace(inc, file_index[inc_key])
                            changed = True
                    else:
                        unresolved.append((rel_fpath, inc))
                new_lines.append(line)
            if changed:
                with open(fpath, 'w', encoding='utf-8') as f:
                    f.writelines(new_lines)
                print(f"  Fixed case in: {rel_fpath}")
                fixed.append(rel_fpath)
    return fixed, unresolved, scanned_files, total_includes

def main():
    fixed, unresolved, scanned_files, total_includes = fix_case_includes()
    print("\n=== Case Include Fix Report ===")
    print(f"Files scanned: {scanned_files}")
    print(f"Total #include statements: {total_includes}")
    print(f"Files auto-fixed (case): {len(fixed)}")
    print(f"Unresolved includes (no matching file): {len(unresolved)}")
    if fixed:
        print("\nFiles auto-fixed:")
        for f in fixed:
            print(f"  {f}")
    if unresolved:
        print("\nUnresolved includes:")
        for f, inc in unresolved:
            print(f"  {f}: {inc}")
    if not fixed and not unresolved:
        print("No case mismatches or unresolved includes found.")

if __name__ == '__main__':
    main()
