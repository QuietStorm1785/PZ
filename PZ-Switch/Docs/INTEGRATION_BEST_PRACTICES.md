# C++ Integration Best Practices & Optimization Guide

## Overview

This guide documents best practices for using the converted Java-to-C++ code and the integration layer in the PZ-Switch codebase.

---

## 1. Memory Management

### Using Shared Pointers

All converted Java objects are wrapped in `std::shared_ptr` for automatic reference counting:

```cpp
// Safe allocation - shared pointer handles cleanup
auto inventory = std::make_shared<zombie::Inventory>();
inventory->addItem(item);

// No need for explicit delete - cleaned up automatically
// when all references are released
```

### Object Pooling for Performance

For frequently allocated objects, use the memory pool system:

```cpp
#include "MemoryPool.h"

// Small objects (< 64 bytes)
void* small_obj = jni::pools::small_objects.allocate();

// Medium objects (< 256 bytes)
void* medium_obj = jni::pools::medium_objects.allocate();

// Check pool statistics
auto stats = jni::pools::small_objects.getStats();
std::cout << "Available: " << stats.available << "\n";

// Don't forget to deallocate
jni::pools::small_objects.deallocate(small_obj);
```

### Arena Allocator for Frame-Based Data

For temporary allocations within a frame:

```cpp
// Allocate temporary data
void* frame_data = jni::pools::frame_arena.allocate(1024);

// ... use data ...

// Clear all frame allocations at end of frame
jni::pools::frame_arena.clear();

// Reset arena for next frame (when needed)
jni::pools::frame_arena.reset();
```

---

## 2. Thread Safety

### Critical: Synchronized Access

Java's `synchronized` keyword is lost in conversion. Use thread-safety utilities:

```cpp
#include "JNIBridge.h"

// Global mutex for synchronized data access
static std::mutex world_state_lock;

// Synchronized block - RAII lock guard
{
    JNI_SYNCHRONIZED_BLOCK(world_state_lock) {
        // Modify world state safely
        worldState->update(deltaTime);
        worldState->tick();
    }
}

// Thread-safe value wrapper
jni::threading::ThreadSafeValue<int> zombie_count(0);

// Get value safely
int count = zombie_count.get();

// Set value safely
zombie_count.set(count + 1);

// Update with callback
zombie_count.update([](int& count) {
    count++;
});
```

### Thread-Safe Containers

```cpp
// Wrap containers that need thread safety
jni::threading::ThreadSafeContainer<std::vector<zombie::Entity>> entities;

// Safe operations
entities.push(new_entity);
size_t count = entities.size();

// Access with locked callback
entities.withLock([](std::vector<zombie::Entity>& vec) {
    // All operations here are safe
    vec.clear();
    vec.resize(100);
});
```

### Main Thread Only Operations

Graphics operations must run on the main thread:

```cpp
// Mark operations that require main thread
jni::threading::MainThreadOnly graphics_marker;

// Always ensure graphics updates run on main thread
if (isMainThread()) {
    renderer->render(scene);
} else {
    // Queue for main thread execution
    mainThreadQueue.enqueue([this]() { renderer->render(scene); });
}
```

---

## 3. String Handling

### UTF-8 and UTF-16 Conversion

```cpp
#include "JNIBridge.h"

// Java String to C++ std::string
std::string cpp_str = jni::string::toString(java_string);

// C++ std::string to Java String
jni::jstring java_str = jni::string::toJavaString(cpp_str);

// UTF-16 conversion for file paths, etc.
std::u16string utf16 = jni::string::toUtf16(utf8_string);
std::string utf8 = jni::string::fromUtf16(utf16_string);
```

---

## 4. Collection Compatibility

### Mapping Java Collections to C++ STL

| Java Type | C++ Type | Usage |
|-----------|----------|-------|
| `ArrayList<T>` | `std::vector<T>` | Dynamic arrays |
| `HashMap<K,V>` | `std::unordered_map<K,V>` | Hash tables |
| `TreeMap<K,V>` | `std::map<K,V>` | Ordered maps |
| `HashSet<T>` | `std::unordered_set<T>` | Unique elements |
| `LinkedList<T>` | `std::list<T>` | Doubly-linked list |
| `Stack<T>` | `std::stack<T>` | LIFO |
| `Queue<T>` | `std::queue<T>` | FIFO |

### Example Usage

```cpp
// ArrayList equivalent
auto items = std::make_shared<std::vector<zombie::Item>>();
items->push_back(item);
items->resize(100);

// HashMap equivalent
auto properties = std::make_shared<std::unordered_map<std::string, int>>();
(*properties)["health"] = 100;
int value = properties->at("health");

// TreeMap for sorted iteration
auto sorted_data = std::make_shared<std::map<std::string, std::shared_ptr<zombie::Entity>>>();
for (const auto& [name, entity] : *sorted_data) {
    std::cout << name << ": " << entity << "\n";
}
```

---

## 5. Exception Handling

### Java Exception to C++ Exception

```cpp
#include "JNIBridge.h"

try {
    // Converted Java code might throw JavaException
    auto result = convertedJavaFunction();
} catch (const jni::JavaException& e) {
    std::cerr << "Java error: " << e.what() << "\n";
    // Handle Java-origin exceptions
} catch (const std::exception& e) {
    std::cerr << "C++ error: " << e.what() << "\n";
}
```

---

## 6. Null Safety

### Null Pointer Checking

```cpp
// Always check for nullptr after allocation
auto obj = std::make_shared<SomeClass>();
if (obj) {
    obj->method();
}

// Use optional for clearer intent
std::optional<std::shared_ptr<SomeClass>> maybe_obj;
if (maybe_obj.has_value()) {
    (*maybe_obj)->method();
}

// Safe getter pattern
std::shared_ptr<SomeClass> getObject() {
    if (valid_condition) {
        return std::make_shared<SomeClass>();
    }
    return nullptr; // Use nullptr instead of null
}
```

---

## 7. Performance Optimization

### Object Pooling Pattern

```cpp
// For objects created frequently each frame
template<typename T>
class FrameObjectPool {
private:
    jni::ObjectPool<T> pool{256};
    
public:
    std::shared_ptr<T> create() {
        return pool.allocate();
    }
    
    void endFrame() {
        jni::pools::resetFrame();
    }
};

// Usage
FrameObjectPool<zombie::Particle> particle_pool;
auto particle = particle_pool.create(); // Reuses from pool
```

### Batch Operations

```cpp
// Process entities in batches for cache efficiency
const size_t BATCH_SIZE = 64;
for (size_t i = 0; i < entities.size(); i += BATCH_SIZE) {
    size_t batch_end = std::min(i + BATCH_SIZE, entities.size());
    
    // Process batch with better cache locality
    for (size_t j = i; j < batch_end; ++j) {
        entities[j]->update(deltaTime);
    }
}
```

### Avoid Unnecessary Copies

```cpp
// Bad - copies entire vector
std::vector<Item> items_copy = inventory->getItems();

// Good - reference to original
const auto& items_ref = inventory->getItems();

// Good - use iterators
for (const auto& item : inventory->getItems()) {
    process(item);
}
```

---

## 8. Common Patterns

### Singleton from Java Static

```cpp
// Java: static Instance instance = new Instance();
// Converted C++:

class Singleton {
public:
    static std::shared_ptr<Singleton>& getInstance() {
        static auto instance = std::make_shared<Singleton>();
        return instance;
    }
    
private:
    Singleton() = default;
};

// Usage
auto instance = Singleton::getInstance();
```

### Builder Pattern

```cpp
// Chain-building for complex objects
auto entity = EntityBuilder()
    .setPosition(x, y)
    .setHealth(100)
    .setType(EntityType::Zombie)
    .build();
```

### Resource Acquisition Is Initialization (RAII)

```cpp
// Ensures cleanup on scope exit
class FileHandle {
private:
    FILE* m_file;
    
public:
    FileHandle(const std::string& path) {
        m_file = fopen(path.c_str(), "rb");
        if (!m_file) throw std::runtime_error("Failed to open file");
    }
    
    ~FileHandle() {
        if (m_file) fclose(m_file);
    }
};

{
    FileHandle file("data.bin"); // Opens
    // ... use file ...
} // Automatically closes
```

---

## 9. Debugging Converted Code

### Enable Memory Pool Statistics

```cpp
// In debug builds
#ifdef DEBUG
    std::cout << "\n=== Memory Pool Statistics ===\n";
    jni::pools::printStats();
#endif
```

### Thread Safety Markers

```cpp
// Look for /* THREAD_SAFE */ comments in converted code
// These indicate methods that were synchronized in Java

// Example (from converted code):
class WorldState {
public:
    /* THREAD_SAFE */ void update() { ... } // Was: synchronized void update()
};

// When calling, ensure proper synchronization!
JNI_SYNCHRONIZED_BLOCK(world_lock) {
    worldState->update();
}
```

### Memory Leak Detection

```cpp
// Use Valgrind or AddressSanitizer
// Compile with: -fsanitize=address
// Run: valgrind --leak-check=full ./program

// Monitor pool exhaustion
if (jni::pools::small_objects.getStats().available == 0) {
    std::cerr << "Small object pool exhausted!\n";
}
```

---

## 10. Performance Profiling

### Measure Function Execution Time

```cpp
#include <chrono>

auto start = std::chrono::high_resolution_clock::now();
{
    // Code to profile
    convertedJavaFunction();
}
auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
std::cout << "Execution time: " << duration.count() << "ms\n";
```

### Memory Usage Tracking

```cpp
// Before/after memory pool checks
auto before = jni::pools::small_objects.getStats();
doSomething();
auto after = jni::pools::small_objects.getStats();

std::cout << "Small objects allocated: " 
          << (before.in_use - after.in_use) << "\n";
```

---

## 11. Migration Checklist

When integrating a new converted module:

- [ ] Check for `synchronized` methods (need manual locking)
- [ ] Verify all `new` statements are converted to `make_shared`
- [ ] Check for `static final` fields (converted to `constexpr`)
- [ ] Review exception handling (`JavaException` usage)
- [ ] Add thread-safety guards around mutable state
- [ ] Profile memory usage with pools
- [ ] Test with ASAN/Valgrind
- [ ] Add unit tests for critical paths
- [ ] Document any Java-specific behaviors that changed
- [ ] Add performance benchmarks

---

## 12. Troubleshooting

### "Pool exhausted" errors
- Increase pool size in `MemoryPool.h`
- Implement object recycling
- Profile to find leaks

### Memory leaks with shared_ptr
- Check for circular references
- Use `std::weak_ptr` to break cycles
- Run leak detector

### Thread safety issues
- Add locks around all shared state access
- Use `JNI_SYNCHRONIZED_BLOCK` for converted `synchronized` methods
- Never access mutable state without locks

### Performance regressions
- Profile before/after conversion
- Check pool statistics
- Verify no unnecessary copies
- Use arena allocator for frame temps

---

## Recommended Reading

- Scott Meyers - "Effective Modern C++"
- Herb Sutter - "More Exceptional C++"
- LLVM/Clang Address Sanitizer documentation
- C++ Core Guidelines

---

## Support

For issues with converted code integration:
1. Check thread safety annotations
2. Review memory management patterns
3. Profile with provided tools
4. Add detailed error messages
5. Report findings to development team
