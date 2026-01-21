#!/usr/bin/env python3
import os
import re
import sys

SRC_DIR = os.path.join(os.path.dirname(__file__), '../ProjectZomboidSwitch/src')

INCLUDE_PATTERN = re.compile(r'#include\s+[<"]([^">]+)[">]')

# Build a set of all files in the src dir (relative, normalized, lowercased)
all_files = set()
for root, dirs, files in os.walk(SRC_DIR):
    for f in files:
        rel = os.path.relpath(os.path.join(root, f), SRC_DIR)
        all_files.add(rel.replace('\\', '/'))
        all_files.add(rel.replace('\\', '/').lower())

problems = []

for root, dirs, files in os.walk(SRC_DIR):
    for f in files:
        if not f.endswith(('.cpp', '.h', '.hpp', '.cc', '.c')):
            continue
        path = os.path.join(root, f)
        relpath = os.path.relpath(path, SRC_DIR)
        with open(path, encoding='utf-8', errors='ignore') as file:
            for i, line in enumerate(file, 1):
                m = INCLUDE_PATTERN.search(line)
                if m:
                    inc = m.group(1)
                    norm_inc = inc.replace('\\', '/').replace('//', '/')
                    if norm_inc not in all_files:
                        # Try case-insensitive
                        if norm_inc.lower() in all_files:
                            problems.append(f"{relpath}:{i}: Case mismatch: {inc}")
                        else:
                            problems.append(f"{relpath}:{i}: Missing include: {inc}")
                    if '\\' in inc:
                        problems.append(f"{relpath}:{i}: Backslash in include: {inc}")

if problems:
    print("Include check failed! Problems found:")
    for p in problems:
        print(p)
    sys.exit(1)
else:
    print("All includes are valid!")
    sys.exit(0)
