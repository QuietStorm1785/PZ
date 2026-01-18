# Java-to-C++ Conversion Fixes Strategy

## Date: January 17, 2026

## Overview
This document outlines the systematic approach to fixing the remaining Java-to-C++ conversion issues in the PZ-Switch codebase.

## Issue Categories

### 1. Generic Type Parameters (TypeK, TypeV)

**Location**: Primarily in `zombie/core/Collections/NonBlockingIdentityHashMap.h`

**Problem**: Java's generic parameters `<K, V>` were converted to literal types `TypeK` and `TypeV`.

**Solutions**:
- **Option A** (Quick Fix): Define as `void*` aliases in JavaCompatMacros.h
- **Option B** (Proper Fix): Convert to C++ templates `template<typename K, typename V>`

**Chosen Solution**: Option A for now (already in JavaCompatMacros.h)
- Allows compilation to proceed
- Can be refactored to templates later if needed
- Most of this code is not performance-critical

**Files Affected**:
- `zombie/core/Collections/NonBlockingIdentityHashMap.h`

---

### 2. instanceof Operator

**Locations**: 
- Third-party libraries: `org/joml/*` (50+ occurrences)
- Lua integration: `se/krka/kahlua/*`
- Third-party libraries: `org/lwjglx/opengl/*`

**Problem**: Java's `instanceof` operator doesn't exist in C++.

**Patterns Found**:
```java
// Pattern 1: Type check without variable
if (arg0 instanceof Matrix2f) { ... }

// Pattern 2: Type check with pattern matching variable
if (type instanceof TypeVariable typeVariable) { ... }

// Pattern 3: Negated check
if (!(arg0 instanceof Matrix2f)) { ... }
```

**Solutions**:
```cpp
// Pattern 1: Use dynamic_cast directly
if (dynamic_cast<Matrix2f*>(arg0) != nullptr) { ... }

// Pattern 2: Use dynamic_cast with assignment
if (auto* typeVariable = dynamic_cast<TypeVariable*>(type)) { ... }

// Pattern 3: Negated
if (dynamic_cast<Matrix2f*>(arg0) == nullptr) { ... }
```

**Replacement Strategy**:
1. **JOML Classes** (`org/joml/*`): Direct `dynamic_cast` - these are performance-critical math operations
2. **Kahlua/Lua Classes**: Use macro helpers for readability
3. **Networking Classes**: Direct `dynamic_cast`

**Implementation**:
- Create regex-based replacements for each pattern
- Apply to all affected files in batch operations

---

### 3. synchronized Keyword

**Locations**:
- Networking: `zombie/network/*` (LoginQueue, MPStatisticClient, CoopSlave)
- Profilers: `se/krka/kahlua/profiler/*`
- Audio: `de/jarnbjo/ogg/*`, `de/jarnbjo/vorbis/*`
- Game state: `zombie/gameStates/GameLoadingState.h`
- Meta: `zombie/meta/Meta.h`
- Utilities: `org/joml/Random.h`, `se/krka/kahlua/test/UserdataArray.h`

**Patterns Found**:
```java
// Pattern 1: synchronized method
synchronized void method() { ... }

// Pattern 2: synchronized block on object
synchronized(this.lock) { ... }

// Pattern 3: synchronized on class
synchronized(ClassName.class) { ... }
```

**Solutions**:
```cpp
// Pattern 1: Add lock_guard at method start
void method() {
    std::lock_guard<std::mutex> lock(this_mutex);
    ...
}

// Pattern 2: Scoped lock_guard
{
    std::lock_guard<std::mutex> lock(lock_mutex);
    ...
}

// Pattern 3: Static mutex
{
    std::lock_guard<std::mutex> lock(ClassName_class_mutex);
    ...
}
```

**Implementation Steps**:
1. Add mutex member declarations to classes with synchronized methods
2. Add static mutex declarations for class-level synchronization
3. Replace `synchronized(obj)` blocks with `std::lock_guard` scoped blocks
4. Replace `synchronized void method()` with method-level `std::lock_guard`

---

### 4. Method Stubs (TODO)

**Status**: Widespread throughout converted code

**Priority Classification**:

**High Priority** (Needed for core functionality):
- Core game loop methods
- Player input/control
- World rendering
- Collision detection
- Save/load operations

**Medium Priority** (Enhances gameplay):
- AI decision making
- Crafting system
- Item interactions
- Weather/time systems

**Low Priority** (Can be stubbed):
- Statistics tracking
- Debug logging
- Profiling
- Some UI features

**Strategy**:
1. **Phase 1**: Identify critical path methods (Core, IsoPlayer, IsoWorld, IsoCell)
2. **Phase 2**: Implement rendering pipeline stubs (minimal return values)
3. **Phase 3**: Implement input handling and player control
4. **Phase 4**: Gradual implementation of game systems as needed

**Implementation**:
- Use `grep_search` to find TODO comments
- Categorize by namespace/subsystem
- Implement high-priority stubs first
- Leave low-priority as empty implementations for now

---

## Implementation Plan

### Phase 1: Quick Fixes (Enable Compilation) ✅
- [x] Create JavaCompatMacros.h with TypeK/TypeV aliases
- [ ] Apply instanceof fixes to JOML library (50+ files)
- [ ] Apply synchronized fixes to network/audio classes (30+ files)

### Phase 2: Critical Method Stubs
- [ ] Identify critical path (Core→IsoWorld→IsoCell→IsoPlayer)
- [ ] Implement minimal stubs for rendering pipeline
- [ ] Implement basic input handling
- [ ] Test .nro boots and displays something

### Phase 3: Functionality Implementation
- [ ] Implement game loop (Core.cpp)
- [ ] Implement player movement (IsoPlayer.cpp)
- [ ] Implement world rendering (IsoWorld.cpp, IsoCell.cpp)
- [ ] Test basic gameplay

### Phase 4: Polish & Optimization
- [ ] Convert TypeK/TypeV to proper templates (if needed)
- [ ] Optimize hot paths
- [ ] Implement remaining game systems
- [ ] Full testing

---

## Automated Replacement Scripts

### Script 1: Fix instanceof (JOML libraries)
```bash
# Pattern 1: Simple type check
find PZ-Switch/include/org/joml -name "*.h" -exec sed -i \\
  's/if (\([^)]*\) instanceof \([^)]*\))/if (dynamic_cast<\2*>(\1) != nullptr)/g' {} +

# Pattern 2: Negated type check  
find PZ-Switch/include/org/joml -name "*.h" -exec sed -i \\
  's/if (!(\([^)]*\) instanceof \([^)]*\)))/if (dynamic_cast<\2*>(\1) == nullptr)/g' {} +
```

### Script 2: Fix synchronized blocks
```bash
# Pattern 1: synchronized(object)
find PZ-Switch/include -name "*.h" -exec sed -i \\
  's/synchronized(\([^)]*\))/{ std::lock_guard<std::mutex> __sync_lock__(\1_mutex);/g' {} +

# Note: Requires manual addition of closing braces and mutex declarations
```

---

## Testing Strategy

### Compilation Test
```bash
cd PZ-Switch/build-test
cmake .. -DCMAKE_TOOLCHAIN_FILE=/opt/devkitpro/cmake/Switch.cmake \\
  -DNINTENDO_SWITCH=ON -DBUILD_MODDING=ON
make -j4
```

### Expected Outcomes:
1. **After instanceof fixes**: Reduction in "invalid use of incomplete type" errors
2. **After synchronized fixes**: Reduction in "expected ';'" errors  
3. **After TypeK/TypeV fixes**: Reduction in "unknown type" errors

### Success Criteria:
- ✅ Full codebase compiles (1,375 files)
- ✅ Generates .nro file
- ✅ .nro file loads on Switch/emulator
- ✅ Displays some output (even if just a blank screen)

---

## Notes

### Why Not Fix Everything At Once?
- **Incremental Progress**: Each fix category is independent
- **Testing**: Can verify each fix type separately
- **Reversible**: Easy to roll back specific changes
- **Learning**: Understand impact of each fix on compilation

### Why Keep Some Stubs?
- **80/20 Rule**: 20% of methods handle 80% of functionality
- **Complexity**: Some systems can be disabled initially
- **Time**: Full implementation would take months
- **Goal**: Get a working .nro first, then add features

### Technical Debt Tracking
All quick fixes are documented here for future refactoring:
1. TypeK/TypeV should become proper templates
2. Some synchronized blocks may need finer-grained locking
3. Stub methods need real implementations
4. Memory management needs review (smart pointers vs raw)

---

## Current Status

- **Generic Types**: ✅ Fixed with aliases
- **instanceof**: 🔄 In progress (50+ occurrences)
- **synchronized**: 📋 Planned (30+ occurrences)
- **Method Stubs**: 📋 Planned (1000s of occurrences)

Last Updated: January 17, 2026
