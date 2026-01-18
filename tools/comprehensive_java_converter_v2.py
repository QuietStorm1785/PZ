#!/usr/bin/env python3
"""
Comprehensive Java-to-C++ Converter - Production Edition
Features: Pre-compiled regex patterns, multiprocessing, batch operations, caching
"""

import os
import re
import sys
import hashlib
import json
from pathlib import Path
from multiprocessing import Pool, cpu_count
from functools import partial
try:
    from tqdm import tqdm
except ImportError:
    def tqdm(iterable, **kwargs):
        return iterable

class ProductionJavaConverter:
    def __init__(self, use_cache=True, num_workers=None):
        self.use_cache = use_cache
        self.cache_file = "/workspaces/PZ/.conversion_cache.json"
        self.cache = self._load_cache() if use_cache else {}
        self.num_workers = num_workers or max(1, cpu_count() - 1)
        
        # Pre-compile all regex patterns
        self.pattern_combined = self._build_combined_patterns()
        self.pattern_groups = self._build_pattern_groups()
        
        self.stats = {
            'files_processed': 0,
            'files_skipped_cached': 0,
            'this_dot': 0,
            'throw_new': 0,
            'is_empty': 0,
            'null_keyword': 0,
            'java_keywords': 0,
            'double_parens': 0,
            'string_nullptr': 0,
            'files_fixed': 0,
        }
    
    def _load_cache(self):
        """Load conversion results cache."""
        if os.path.exists(self.cache_file):
            try:
                with open(self.cache_file, 'r') as f:
                    return json.load(f)
            except Exception:
                return {}
        return {}
    
    def _save_cache(self):
        """Save conversion cache."""
        try:
            with open(self.cache_file, 'w') as f:
                json.dump(self.cache, f)
        except Exception:
            pass
    
    def _get_file_hash(self, filepath):
        """Get hash of file contents for caching."""
        try:
            with open(filepath, 'rb') as f:
                return hashlib.md5(f.read()).hexdigest()
        except Exception:
            return None
    
    def _build_combined_patterns(self):
        """Build optimized combined regex patterns."""
        return {
            # Single pattern for multiple Java keywords
            'keywords': re.compile(r'\b(?:final|abstract|volatile|transient|strictfp|native)\s+'),
            # Combined null handling
            'null_variants': re.compile(r'\bnull\b|== nullptr'),
            # Batch method conversions
            'method_fixes': re.compile(
                r'\bthis\.|\.isEmpty\(\)|(?<!\w)null(?!\w)|throw\s+new'
            ),
        }
    
    def _build_pattern_groups(self):
        """Build individual patterns for detailed tracking."""
        return {
            'this_dot': re.compile(r'\bthis\.'),
            'throw_new': re.compile(r'\bthrow\s+new\b'),
            'is_empty': re.compile(r'\.isEmpty\(\)'),
            'null_keyword': re.compile(r'(?<!\w)null(?!\w)'),
            'double_parens': re.compile(r'(\w+)\)\)'),
            'string_nullptr': re.compile(r'(\w+)\s*==\s*nullptr'),
            'whitespace': re.compile(r'  +'),
        }
    
    def apply_fixes(self, content):
        """Apply all fixes with batch operations."""
        original = content
        
        # Count fixes before applying (for statistics)
        counts = {
            'this_dot': len(self.pattern_groups['this_dot'].findall(content)),
            'throw_new': len(self.pattern_groups['throw_new'].findall(content)),
            'is_empty': len(self.pattern_groups['is_empty'].findall(content)),
            'null_keyword': len(self.pattern_groups['null_keyword'].findall(content)),
            'double_parens': len(self.pattern_groups['double_parens'].findall(content)),
            'string_nullptr': len(self.pattern_groups['string_nullptr'].findall(content)),
        }
        
        # Apply batch conversions
        content = self.pattern_groups['this_dot'].sub('this->', content)
        content = self.pattern_groups['throw_new'].sub('throw', content)
        content = self.pattern_groups['is_empty'].sub('.empty()', content)
        content = self.pattern_groups['null_keyword'].sub('nullptr', content)
        
        # Remove Java keywords
        content = self.pattern_combined['keywords'].sub(' ', content)
        
        # Fix double parenthesis
        content = self.pattern_groups['double_parens'].sub(r'\1)', content)
        
        # Clean up whitespace
        content = self.pattern_groups['whitespace'].sub(' ', content)
        
        # Update statistics
        for key, count in counts.items():
            if key in self.stats:
                self.stats[key] += count
        
        if content != original:
            self.stats['files_fixed'] += 1
        
        return content
    
    def process_file(self, filepath):
        """Process a single file with caching."""
        try:
            file_hash = self._get_file_hash(filepath)
            
            # Check cache
            if self.use_cache and filepath in self.cache:
                cached_hash = self.cache[filepath]
                if cached_hash == file_hash:
                    self.stats['files_skipped_cached'] += 1
                    return True
            
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            new_content = self.apply_fixes(content)
            
            if content != new_content:
                with open(filepath, 'w', encoding='utf-8') as f:
                    f.write(new_content)
                
                # Update cache
                if self.use_cache and file_hash:
                    self.cache[filepath] = file_hash
                
                self.stats['files_processed'] += 1
                return True
            elif self.use_cache and file_hash:
                # File didn't change, cache it
                self.cache[filepath] = file_hash
            
            return False
        except Exception:
            return False
    
    def process_files_parallel(self, files):
        """Process files in parallel using multiprocessing Pool."""
        if self.num_workers <= 1:
            # Sequential processing
            for filepath in tqdm(files, desc="Converting", unit=" files"):
                self.process_file(filepath)
        else:
            # Parallel processing
            with Pool(self.num_workers) as pool:
                # Use imap_unordered for better performance
                for _ in tqdm(
                    pool.imap_unordered(self.process_file, files),
                    total=len(files),
                    desc="Converting",
                    unit=" files"
                ):
                    pass
    
    def run(self, directory):
        """Scan and process all files."""
        if not os.path.isdir(directory):
            print(f"Error: {directory} is not a directory")
            return False
        
        files = []
        for ext in ['*.h', '*.hpp', '*.cpp', '*.cc']:
            files.extend(Path(directory).rglob(ext))
        
        print(f"Processing {len(files)} C++ files ({self.num_workers} workers)...")
        if self.use_cache:
            print(f"Using conversion cache: {self.cache_file}")
        
        self.process_files_parallel(list(files))
        
        # Save cache
        if self.use_cache:
            self._save_cache()
        
        return True
    
    def print_report(self):
        """Print detailed statistics."""
        print("\n" + "="*60)
        print("Production Java-to-C++ Conversion Report")
        print("="*60)
        print(f"\nExecution:")
        print(f"  Workers: {self.num_workers}")
        print(f"  Cache enabled: {self.use_cache}")
        print(f"  Files skipped (cached): {self.stats['files_skipped_cached']}")
        print(f"\nFiles Fixed: {self.stats['files_fixed']}")
        print(f"\nIssues Corrected:")
        print(f"  this. → this->           {self.stats['this_dot']:>5}")
        print(f"  throw new → throw        {self.stats['throw_new']:>5}")
        print(f"  .isEmpty() → .empty()    {self.stats['is_empty']:>5}")
        print(f"  null → nullptr           {self.stats['null_keyword']:>5}")
        print(f"  Java keywords removed    {self.stats['java_keywords']:>5}")
        print(f"  == nullptr fixed         {self.stats['string_nullptr']:>5}")
        print(f"  Double parenthesis fixed {self.stats['double_parens']:>5}")
        print(f"\nTotal Fixes Applied: {sum(self.stats[k] for k in ['this_dot', 'throw_new', 'is_empty', 'null_keyword', 'java_keywords', 'string_nullptr', 'double_parens'])}")
        print("="*60 + "\n")


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 comprehensive_java_converter.py <directory> [--no-cache] [--workers N]")
        sys.exit(1)
    
    directory = sys.argv[1]
    use_cache = '--no-cache' not in sys.argv
    num_workers = None
    
    # Parse workers argument
    if '--workers' in sys.argv:
        idx = sys.argv.index('--workers')
        if idx + 1 < len(sys.argv):
            try:
                num_workers = int(sys.argv[idx + 1])
            except ValueError:
                pass
    
    converter = ProductionJavaConverter(use_cache=use_cache, num_workers=num_workers)
    if converter.run(directory):
        converter.print_report()
        return 0
    return 1


if __name__ == '__main__':
    sys.exit(main())
