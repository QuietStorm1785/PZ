#!/usr/bin/env python3
"""Test decompilation to identify the hang issue"""

import os
import subprocess
from pathlib import Path
import shutil

# Use system java (should be Java 21)
java_cmd = shutil.which('java')
jar_path = '/workspaces/PZ/ZomboidDecompiler/lib/vineflower-1.11.2-module.jar'

test_class = list(Path('/workspaces/PZ/classes_only').rglob('*.class'))[0]
output_dir = '/tmp/test_decompile_output'
os.makedirs(output_dir, exist_ok=True)

print(f"Testing decompilation of: {test_class}")
print(f"Java command: {java_cmd}")
print(f"JAR path: {jar_path}")
print(f"Output dir: {output_dir}")

cmd = [
    java_cmd,
    '-jar',
    jar_path,
    str(test_class),
    output_dir
]

print(f"\nRunning: {' '.join(cmd)}")
print("This may take 30-60 seconds due to module scanning...")

try:
    result = subprocess.run(cmd, capture_output=True, timeout=120, text=True)
    print(f"\nReturn code: {result.returncode}")
    if result.stdout:
        print(f"STDOUT:\n{result.stdout[:500]}")
    if result.stderr:
        print(f"STDERR:\n{result.stderr[:500]}")
    
    # Check if output file was created
    java_files = list(Path(output_dir).rglob('*.java'))
    print(f"\nCreated {len(java_files)} .java files")
    if java_files:
        print(f"Example: {java_files[0]}")
        
except subprocess.TimeoutExpired:
    print("TIMEOUT!")
except Exception as e:
    print(f"ERROR: {e}")
