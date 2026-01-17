#!/usr/bin/env python3
"""
Batch syntax normalizer for converted2 Java→C++ output.

Usage:
    python tools/fix_converted2.py --apply      # modify files in-place
    python tools/fix_converted2.py --dry-run     # default: show counts only
"""
from __future__ import annotations
import argparse
import pathlib
import re
import sys
from typing import List, Tuple

ROOT = pathlib.Path(__file__).resolve().parents[1]
TARGET = ROOT / "converted2"

REPLACEMENTS: List[Tuple[str, re.Pattern[str], str]] = [
    ("implements -> : public", re.compile(r"(class\s+\w+)\s+implements\s+"), r"\1 : public "),
    ("extends -> : public", re.compile(r"(class\s+\w+)\s+extends\s+"), r"\1 : public "),
    ("ArrayList -> std::vector", re.compile(r"\bArrayList<"), "std::vector<"),
    ("HashMap -> std::unordered_map", re.compile(r"\bHashMap<"), "std::unordered_map<"),
    ("String -> std::string", re.compile(r"\bString\b"), "std::string"),
    ("boolean -> bool", re.compile(r"\bboolean\b"), "bool"),
    ("@Override removal", re.compile(r"@Override\s*\n"), ""),
    ("public class -> class", re.compile(r"public\s+class\s+"), "class "),
]

SUFFIXES = {".h", ".hpp", ".cpp", ".cc"}

def process_file(path: pathlib.Path, apply: bool) -> int:
    text = path.read_text(encoding="utf-8", errors="ignore")
    original = text
    for _, pattern, replacement in REPLACEMENTS:
        text = pattern.sub(replacement, text)
    if text != original and apply:
        path.write_text(text, encoding="utf-8")
    return 0 if text == original else 1

def main() -> int:
    parser = argparse.ArgumentParser(description="Normalize converted2 syntax")
    parser.add_argument("--apply", action="store_true", help="write changes to files")
    parser.add_argument("--dry-run", action="store_true", help="report only")
    args = parser.parse_args()

    apply = args.apply and not args.dry_run

    if not TARGET.exists():
        print(f"Target folder not found: {TARGET}", file=sys.stderr)
        return 1

    changed = 0
    scanned = 0
    for path in TARGET.rglob("*"):
        if path.suffix in SUFFIXES and path.is_file():
            scanned += 1
            changed += process_file(path, apply)

    mode = "APPLIED" if apply else "DRY-RUN"
    print(f"[{mode}] scanned={scanned} potential_changes={changed}")
    if not apply:
        print("Re-run with --apply to write modifications.")
    return 0

if __name__ == "__main__":
    sys.exit(main())
