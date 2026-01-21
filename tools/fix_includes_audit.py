import os
import re

# Configuration
SRC_ROOT = r"ProjectZomboidSwitch/src"
HEADER_EXTS = {'.h', '.hpp'}
SOURCE_EXTS = {'.cpp', '.c', '.cc'}

# Regex to match #include lines
INCLUDE_RE = re.compile(r'#include\s+["<]([^">]+)[">]')

# Collect all files in the source tree
all_files = set()
for root, dirs, files in os.walk(SRC_ROOT):
    for f in files:
        rel_path = os.path.relpath(os.path.join(root, f), SRC_ROOT)
        all_files.add(rel_path.replace('\\', '/'))

# Scan for includes and issues
def scan_includes():
    issues = {
        'inconsistent_slashes': [],
        'missing_files': [],
        'case_mismatches': [],
        'fixed': [],
        'scanned_files': 0,
        'total_includes': 0
    }
    for root, dirs, files in os.walk(SRC_ROOT):
        for fname in files:
            if not (fname.endswith(tuple(SOURCE_EXTS)) or fname.endswith(tuple(HEADER_EXTS))):
                continue
            fpath = os.path.join(root, fname)
            rel_fpath = os.path.relpath(fpath, SRC_ROOT)
            issues['scanned_files'] += 1
            print(f"Scanning: {rel_fpath}")
            with open(fpath, encoding='utf-8', errors='ignore') as f:
                lines = f.readlines()
            new_lines = []
            changed = False
            for line in lines:
                m = INCLUDE_RE.search(line)
                if m:
                    issues['total_includes'] += 1
                    inc = m.group(1)
                    # Check for inconsistent slashes
                    if '\\' in inc and '/' in inc:
                        issues['inconsistent_slashes'].append((rel_fpath, inc))
                        inc_fixed = inc.replace('\\', '/')
                        line = line.replace(inc, inc_fixed)
                        changed = True
                    # Check if file exists (case-sensitive)
                    inc_norm = inc.replace('\\', '/').replace('../', '')
                    if inc_norm not in all_files:
                        # Try case-insensitive match
                        matches = [f for f in all_files if f.lower() == inc_norm.lower()]
                        if matches:
                            issues['case_mismatches'].append((rel_fpath, inc, matches[0]))
                        else:
                            issues['missing_files'].append((rel_fpath, inc))
                new_lines.append(line)
            # Write back if changed
            if changed:
                with open(fpath, 'w', encoding='utf-8') as f:
                    f.writelines(new_lines)
                print(f"  Fixed slashes in: {rel_fpath}")
                issues['fixed'].append(rel_fpath)
    return issues

def main():
    issues = scan_includes()
    print("\n=== Include Fix Audit Report ===")
    print(f"Files scanned: {issues['scanned_files']}")
    print(f"Total #include statements: {issues['total_includes']}")
    print(f"Files auto-fixed (slashes): {len(issues['fixed'])}")
    print(f"Remaining inconsistent slashes: {len(issues['inconsistent_slashes'])}")
    print(f"Missing include files: {len(issues['missing_files'])}")
    print(f"Case/path mismatches: {len(issues['case_mismatches'])}")

    if issues['fixed']:
        print("\nFiles auto-fixed:")
        for f in issues['fixed']:
            print(f"  {f}")
    if issues['inconsistent_slashes']:
        print("\nRemaining includes with inconsistent slashes:")
        for f, inc in issues['inconsistent_slashes']:
            print(f"  {f}: {inc}")
    if issues['missing_files']:
        print("\nIncludes referencing missing files:")
        for f, inc in issues['missing_files']:
            print(f"  {f}: {inc}")
    if issues['case_mismatches']:
        print("\nIncludes with case/path mismatches:")
        for f, inc, match in issues['case_mismatches']:
            print(f"  {f}: {inc} (actual: {match})")

if __name__ == '__main__':
    main()
