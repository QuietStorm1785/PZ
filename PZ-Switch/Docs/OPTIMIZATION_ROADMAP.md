# Performance & Optimization Roadmap

## Quick Wins (Can implement immediately)

### 1. Add `noexcept` to Functions
Helps compiler optimize and prevents accidental exceptions.

```cpp
// Before
int getValue() { return value; }

// After  
int getValue() const noexcept { return value; }
```

**Impact:** Compiler can optimize better, no runtime cost
**Effort:** Low - mostly copy-paste
**Files to check:** All in PZ-Switch/include/

### 2. Add `const` to Getters
Logical improvement for thread-safety analysis.

```cpp
// Before
int getHealth() { return health; }

// After
int getHealth() const { return health; }
```

**Impact:** Prevents accidental mutations, helps const-correctness
**Effort:** Low
**Files to check:** All game entity classes

### 3. Use `std::string_view` for Read-only String Parameters
Avoids unnecessary copies.

```cpp
// Before
void processName(const std::string& name) { ... }

// After
void processName(std::string_view name) { ... }
```

**Impact:** Zero-copy passing, no temporary string allocations
**Effort:** Medium - need to verify C++17 support
**Files to check:** JNIBridge.h, string utilities

---

## Medium-Term Optimizations (1-2 weeks)

### 4. Entity Pool Optimization
Pre-allocate entities in contiguous memory for better cache behavior.

```cpp
// Example: Zombie entity pooling
jni::ObjectPool<zombie::Zombie> zombie_pool(2048);
auto zombie = zombie_pool.allocate(x, y, type);
// Automatic cleanup when shared_ptr released
```

### 5. Texture/Sprite Caching
Implement LRU cache for textures to reduce memory churn.

```cpp
class TextureCache {
    std::unordered_map<std::string, std::shared_ptr<Texture>> cache;
    jni::threading::ThreadSafeContainer<std::queue<std::string>> lru;
};
```

### 6. Sound Manager Optimization
Batch audio updates instead of per-entity.

---

## Long-Term Improvements (1+ months)

### 7. SIMD Math Operations
Use vectorized operations for game math.

```cpp
// Vector operations can use SIMD
std::array<float, 4> vec_a, vec_b;
// Auto-vectorized or explicit SIMD
```

### 8. Multithreading Architecture
Properly split work across cores:
- Render thread
- Logic thread
- Audio thread
- Pathfinding worker threads

### 9. Asset Streaming
Stream large assets (textures, sounds) asynchronously.

---

## Metrics to Track

1. **Allocation Performance**
   - Track pool statistics in real-time
   - Alert if pool exhaustion happens

2. **Render Performance**
   - Frame time
   - GPU utilization
   - Drawcalls

3. **Memory Usage**
   - Peak memory
   - Fragmentation
   - GC pressure (if applicable)

4. **Thread Safety**
   - Lock contention
   - Thread stalls
   - Context switches

---

## Compilation Optimization Flags

Add to CMakeLists.txt for Release builds:

```cmake
# CPU-specific optimizations
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -mtune=native")

# Link-time optimization
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

# Fast math for graphics
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")

# Visibility for symbol hiding (smaller binary, faster)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
```

---

## Testing & Validation

Before deploying any optimization:

1. **Compile with ASan**
   ```bash
   cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_ASAN=ON ..
   ```

2. **Profile with perf**
   ```bash
   perf record -F 99 -g ./ProjectZomboidCpp
   perf report
   ```

3. **Memory profiling**
   ```bash
   valgrind --leak-check=full ./ProjectZomboidCpp
   ```

4. **Benchmark**
   ```bash
   ./ProjectZomboidCpp --benchmark
   ```

---

## Success Metrics (After All Optimizations)

| Metric | Current | Target | Win |
|--------|---------|--------|-----|
| Startup Time | ? | <2s | ? |
| Frame Time | ? | <16.67ms (60 FPS) | ? |
| Memory Usage | ? | <500MB | ? |
| Entity Count | ? | 10,000+ | ? |
| Allocation Latency | <10ns | <5ns | 2x |
| Cache Miss Rate | ? | <5% | ? |

