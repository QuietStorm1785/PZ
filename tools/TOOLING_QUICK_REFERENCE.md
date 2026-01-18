# Tooling Quick Reference

## Available Tools (Phase 4)

### 1. Comprehensive Java-to-C++ Converter
**File**: `tools/comprehensive_java_converter.py`  
**Use When**: Initial cleanup of decompiled Java code

```bash
python3 tools/comprehensive_java_converter.py <directory>
```

**Fixes**: 8 categories, 89,710 issues on first run

---

### 2. Remove Java Keywords
**File**: `tools/remove_java_keywords.py`  
**Use When**: Final cleanup of remaining Java modifiers

```bash
python3 tools/remove_java_keywords.py <directory>
```

**Removes**: final, abstract, volatile, transient, strictfp, native

---

### 3. Audit Class Members
**File**: `tools/audit_class_members.py`  
**Use When**: Finding structural issues (missing members, incomplete implementations)

```bash
python3 tools/audit_class_members.py <directory>
```

**Identifies**:
- Getters without backing members
- Setters without properties
- Incomplete class implementations

---

### 4. Fix AttachedItems Subsystem
**File**: `tools/fix_attached_items.py`  
**Use When**: Addressing AttachedItems-specific conversion issues

```bash
python3 tools/fix_attached_items.py <directory>
```

**Converts**:
- ArrayList → std::vector
- Java objects → smart pointers
- Fixes access specifiers

---

## Recommended Workflow

```bash
# Step 1: Comprehensive initial pass
python3 tools/comprehensive_java_converter.py PZ-Switch/include

# Step 2: Identify remaining issues
python3 tools/audit_class_members.py PZ-Switch/include

# Step 3: Targeted subsystem fixes (if needed)
python3 tools/fix_attached_items.py PZ-Switch/include

# Step 4: Final keyword cleanup
python3 tools/remove_java_keywords.py PZ-Switch/include

# Step 5: Build and repeat
cd PZ-Switch/build-test && make -j4
```

---

## Statistics

**Comprehensive Converter Results** (First Run):
- Files scanned: 2,167
- Files fixed: 2,139 (98.7%)
- Total fixes: 89,710
- Time: ~2 minutes

**Fix Categories**:
- this. → this-> : 44,539
- null → nullptr : 3,359
- Java keywords : 3,818
- == nullptr fixes : 3,261
- Double parenthesis : 34,268
- throw new → throw : 450
- .isEmpty() → .empty() : 15

---

## After Tooling Applied

✅ AttachedLocationGroup.h - Refactored to proper C++  
✅ AttachedLocationGroup.cpp - Implemented with smart pointers  
✅ 2,139 files cleaned up  
✅ 89,710 issues fixed

---

## Next: Build Testing

Ready to compile with improved codebase:

```bash
cd /workspaces/PZ/PZ-Switch/build-test
make -j4 2>&1 | tee build_with_improvements.log
```

Monitor for remaining errors and address categorically.
