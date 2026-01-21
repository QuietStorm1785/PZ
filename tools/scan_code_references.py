#!/usr/bin/env python3
import os
import re
from collections import defaultdict

SRC_DIR = os.path.join(os.path.dirname(__file__), '../ProjectZomboidSwitch/src')

# Patterns for C++ symbols
FUNC_DEF = re.compile(r'([a-zA-Z_][a-zA-Z0-9_:<>]*)\s+([a-zA-Z_][a-zA-Z0-9_:<>]*)\s*\(([^)]*)\)\s*[{;]')
FUNC_CALL = re.compile(r'([a-zA-Z_][a-zA-Z0-9_:<>]*)\s*\(')
CLASS_DEF = re.compile(r'\b(class|struct|enum)\s+([a-zA-Z_][a-zA-Z0-9_]*)')
VAR_DEF = re.compile(r'([a-zA-Z_][a-zA-Z0-9_:<>]*)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*[;=]')

# Collect all definitions and usages
func_defs = set()
func_calls = set()
class_defs = set()
var_defs = set()
var_uses = set()

for root, dirs, files in os.walk(SRC_DIR):
    for f in files:
        if not f.endswith(('.cpp', '.h', '.hpp', '.cc', '.c')):
            continue
        path = os.path.join(root, f)
        with open(path, encoding='utf-8', errors='ignore') as file:
            for line in file:
                # Function definitions
                for m in FUNC_DEF.finditer(line):
                    func_defs.add(m.group(2))
                # Function calls
                for m in FUNC_CALL.finditer(line):
                    func_calls.add(m.group(1))
                # Class/struct/enum definitions
                for m in CLASS_DEF.finditer(line):
                    class_defs.add(m.group(2))
                # Variable definitions
                for m in VAR_DEF.finditer(line):
                    var_defs.add(m.group(2))
                # Variable usages (simple heuristic)
                for v in re.findall(r'\b([a-zA-Z_][a-zA-Z0-9_]*)\b', line):
                    var_uses.add(v)

# Find undefined function calls
undefined_funcs = sorted([f for f in func_calls if f not in func_defs and f not in class_defs])
# Find unused functions
unused_funcs = sorted([f for f in func_defs if f not in func_calls])
# Find unused classes
unused_classes = sorted([c for c in class_defs if c not in var_uses and c not in func_calls])
# Find undefined variables (used but not defined)
undefined_vars = sorted([v for v in var_uses if v not in var_defs and v not in func_defs and v not in class_defs])
# Find unused variables
unused_vars = sorted([v for v in var_defs if v not in var_uses])

print("==== Undefined Function Calls ====")
for f in undefined_funcs:
    print(f)
print("\n==== Unused Functions ====")
for f in unused_funcs:
    print(f)
print("\n==== Unused Classes ====")
for c in unused_classes:
    print(c)
print("\n==== Undefined Variables (used but not defined) ====")
for v in undefined_vars:
    print(v)
print("\n==== Unused Variables ====")
for v in unused_vars:
    print(v)
