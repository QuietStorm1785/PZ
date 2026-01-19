# Medium-Term Optimizations Implementation Guide

**Date:** January 19, 2026  
**Status:** Ready for Integration  
**Estimated Impact:** 10-30% performance improvement

---

## Overview

This guide covers implementing medium-term performance optimizations across the PZ-Switch codebase:

1. **Entity Pool Optimization** - Pre-allocated entity pools for cache-friendly allocation
2. **Texture/Sprite LRU Caching** - Memory-efficient texture caching with LRU eviction
3. **Audio Batching System** - Batch audio commands to reduce function call overhead
4. **Hot-Path Profiling** - Framework for identifying and optimizing performance bottlenecks

---

## 1. Entity Pool Optimization

### Purpose
Pre-allocate entities in contiguous memory blocks to improve CPU cache efficiency and reduce allocation overhead.

### Key Components

**Header:** `PZ-Switch/include/EntityPooling.h`

#### ContiguousEntityPool<T>
Pre-allocates all entities upfront for cache locality:
```cpp
// Create a pool for Zombie entities (capacity 2048)
auto zombie_pool = std::make_unique<jni::pooling::ContiguousEntityPool<Zombie>>(2048, "Zombies");

// Allocate from pool
Zombie* zombie = zombie_pool->allocate();

// Release back to pool
zombie_pool->release(zombie);
```

#### PooledEntity<T> (RAII Wrapper)
Automatic resource management:
```cpp
// Entity automatically returned to pool when it goes out of scope
jni::pooling::PooledEntity<Zombie> zombie(pool.allocate(), &pool);
zombie->set_position(x, y);
// Automatic release on destruction
```

#### MultiTierPoolManager<T>
Manages multiple pool sizes for different entity types:
```cpp
jni::pooling::MultiTierPoolManager<Zombie> pool_manager("ZombieManager");
pool_manager.add_tier(1024, "Small Zombies");   // 1024 entities
pool_manager.add_tier(512, "Medium Zombies");   // 512 entities
pool_manager.add_tier(256, "Large Zombies");    // 256 entities

Zombie* zombie = pool_manager.allocate();
pool_manager.release(zombie);
```

### Integration Points

1. **ZombiePopulationManager.h** - Replace ArrayList-based zombie storage
2. **NetworkZombieSimulator.h** - Use pooling for networked zombies
3. **Character spawning** - Use pool for player/NPC entities

### Performance Characteristics

- **Memory:** Pre-allocated, no fragmentation
- **Allocation:** O(1) amortized
- **Cache:** Contiguous memory = better CPU cache hits
- **Estimated Gain:** 3-8% faster entity creation/destruction

---

## 2. Texture/Sprite LRU Caching

### Purpose
Implement intelligent caching with automatic eviction to reduce memory usage and speed up texture lookups.

### Key Components

**Header:** `PZ-Switch/include/LRUCache.h`

#### LRUCache<KeyT, ValueT>
Thread-safe LRU cache with automatic eviction:
```cpp
// Create texture cache (max 512 MB)
jni::caching::LRUCache<std::string, Texture> texture_cache(512 * 1024 * 1024);

// Get or create texture
auto texture = texture_cache.get_or_create("media/textures/zombie.png", texture_size);

// Check if cached
if (texture_cache.contains("media/textures/player.png")) {
    auto cached = texture_cache.get("media/textures/player.png");
}

// Get statistics
auto stats = texture_cache.get_statistics();
printf("Cache hit rate: %.1f%%\n", stats.hit_rate());
printf("Memory usage: %.2f MB\n", stats.current_size_bytes / 1024.0f / 1024.0f);
```

#### TextureLRUCache Specialization
Pre-configured for texture caching:
```cpp
jni::caching::TextureLRUCache sprite_cache(256 * 1024 * 1024);  // 256 MB

// Custom eviction callback (cleanup resources)
auto evict_fn = [](const std::string& key, const Texture& tex) {
    printf("Evicting texture: %s\n", key.c_str());
    // Release GPU resources, etc.
};

sprite_cache.put("sprite_key", texture_ptr, texture_size);
```

### Eviction Strategy
- **Policy:** Least Recently Used (LRU)
- **Trigger:** When cache size exceeds max_size_bytes
- **Eviction Order:** Oldest unused items first

### Integration Points

1. **TextureManager.h** - Add LRU cache for texture loading
2. **AnimationController.h** - Cache sprite animation frames
3. **UITextureCache.h** - Cache UI textures

### Performance Characteristics

- **Lookup:** O(1) hash table
- **Eviction:** O(1) amortized
- **Memory:** Bounded by max_size_bytes
- **Estimated Gain:** 5-15% faster texture access, reduced memory pressure

---

## 3. Audio Batching System

### Purpose
Batch audio commands to reduce per-command overhead and enable better audio processing.

### Key Components

**Header:** `PZ-Switch/include/AudioBatching.h`

#### AudioBatchingSystem
Accumulates audio commands and flushes in batches:
```cpp
jni::audio::AudioBatchingSystem audio_batch(256);  // 256 cmd batch size

// Queue commands (automatically batches)
audio_batch.play_sound("sounds/zombie_growl.ogg", x, y, z, volume, range);
audio_batch.set_volume(sound_id, new_volume);
audio_batch.stop_sound(sound_id);

// Flush manually or auto-flush at batch size
audio_batch.flush_batch();

// Process all batches at once
audio_batch.process_all_batches([&](const auto& batch) {
    for (const auto& cmd : batch.get_commands()) {
        // Apply audio command
        audio_system.execute_command(cmd);
    }
});
```

#### SpatialAudioManager
Handles 3D audio positioning:
```cpp
jni::audio::SpatialAudioManager spatial_audio(audio_batch);

// Update listener (player) position
spatial_audio.set_listener_position(player_x, player_y, player_z);

// Calculate distance-based volume
float volume = spatial_audio.calculate_volume_attenuation(
    sound_x, sound_y, sound_z, max_range);

// Calculate stereo panning
float pan = spatial_audio.calculate_pan(sound_x, sound_y);
```

### Batching Strategy
- **Batch Size:** 256 commands (auto-flush)
- **Trigger:** Time-based or size-based flush
- **Ordering:** Preserves command order within batch

### Integration Points

1. **SoundManager.h** - Use batching for entity sounds
2. **AmbientSoundManager.h** - Batch ambient audio updates
3. **GameProfiler.h** - Profile audio system overhead

### Performance Characteristics

- **Overhead Reduction:** ~80% fewer function calls
- **Processing:** Single thread can handle more sounds
- **Estimated Gain:** 10-20% faster audio system (CPU-bound)

---

## 4. Hot-Path Profiling

### Purpose
Identify performance bottlenecks through instrumentation and statistical analysis.

### Key Components

**Header:** `PZ-Switch/include/HotPathProfiler.h`

#### HotPathProfiler
Global profiler for tracking function performance:
```cpp
// Get global profiler
auto& profiler = jni::profiling::get_global_profiler();

// Record a sample
auto start = std::chrono::high_resolution_clock::now();
// ... do work ...
auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
profiler.record_sample("function_name", duration);

// Get statistics
auto stats = profiler.get_stats("function_name");
printf("Average: %.2f us, Min: %.2f us, Max: %.2f us\n",
       stats.average_time_us(), stats.min_time_us(), stats.max_time_us());

// Get top 10 hottest functions
auto hottest = profiler.get_hottest_functions(10);
profiler.print_report("Game Loop Profile");
```

#### ScopedProfiler (RAII Profiling)
Automatic function timing:
```cpp
{
    PROFILE_FUNCTION();  // Automatically times function
    // ... function code ...
}  // Timing recorded on scope exit

// Or manually:
{
    PROFILE_SCOPE("custom_operation");
    // ... operation code ...
}
```

### Profiling Macros
```cpp
// Profile entire function
void expensive_function() {
    PROFILE_FUNCTION();
    // ...
}

// Profile code block
{
    PROFILE_SCOPE("texture_loading");
    load_textures();
}
```

### Integration Points

1. **GameProfiler.h** - Add hot-path analysis
2. **EntityUpdate loops** - Profile update performance
3. **Rendering pipeline** - Profile render call overhead
4. **Audio processing** - Profile audio thread performance

### Analysis Workflow

1. **Enable Profiling** - Add PROFILE_SCOPE to hot paths
2. **Run Game** - Play through typical gameplay scenarios
3. **Collect Data** - Accumulate profiling samples
4. **Analyze** - `profiler.print_report()` to view hottest functions
5. **Optimize** - Focus on top 5-10 functions

---

## Implementation Roadmap

### Phase 1: Framework Integration (2-3 days)
```
Day 1:
  ✓ Create EntityPooling.h
  ✓ Create LRUCache.h
  ✓ Create AudioBatching.h
  ✓ Create HotPathProfiler.h

Day 2:
  □ Integrate EntityPooling into ZombiePopulationManager
  □ Add TextureCache to TextureManager
  □ Setup AudioBatchingSystem in GameSounds
  □ Add profiling macros to hot paths

Day 3:
  □ Compile and resolve any issues
  □ Run unit tests
  □ Profile baseline performance
```

### Phase 2: Optimization & Tuning (3-5 days)
```
Day 4-5:
  □ Profile with HotPathProfiler
  □ Identify top 10 bottlenecks
  □ Tune pool sizes and cache limits
  □ Benchmark before/after
```

### Phase 3: Validation (2-3 days)
```
Day 6-7:
  □ Run full regression tests
  □ Profile with real game workloads
  □ Verify memory usage
  □ Performance report
```

---

## Performance Targets

| Optimization | Target Gain | Method |
|---|---|---|
| Entity Pooling | 3-8% | Faster allocation, cache locality |
| Texture Caching | 5-15% | Reduced load times, hit rate optimization |
| Audio Batching | 10-20% | Reduced function call overhead |
| Profiling Insights | 5-10% | Identify + fix remaining bottlenecks |
| **Combined Total** | **15-30%** | All optimizations together |

---

## Configuration & Tuning

### EntityPooling Defaults
```cpp
// Zombie pool (most common entity)
auto zombie_pool = std::make_unique<jni::pooling::ContiguousEntityPool<Zombie>>(2048);

// NPC pool
auto npc_pool = std::make_unique<jni::pooling::ContiguousEntityPool<NPC>>(512);

// Projectile pool (fast-moving, frequent creation)
auto proj_pool = std::make_unique<jni::pooling::ContiguousEntityPool<Projectile>>(4096);
```

### TextureCache Sizing
```cpp
// GPU memory available on Switch: ~128 MB total
// Allocate 64 MB for LRU cache
jni::caching::TextureLRUCache sprite_cache(64 * 1024 * 1024);

// Desktop/PC: 256 MB cache
jni::caching::TextureLRUCache desktop_cache(256 * 1024 * 1024);
```

### Audio Batch Sizing
```cpp
// Switch: smaller batch size (more frequent processing)
jni::audio::AudioBatchingSystem audio_batch(128);

// PC: larger batch size (better batching)
jni::audio::AudioBatchingSystem audio_batch_pc(512);
```

### Profiling Overhead
```cpp
// Production build: minimal profiling (only critical paths)
// Debug build: comprehensive profiling

#ifdef DEBUG
  #define PROFILE_SCOPE(x) ::jni::profiling::ScopedProfiler _prof(..., x)
#else
  #define PROFILE_SCOPE(x)  // No-op in production
#endif
```

---

## Monitoring & Diagnostics

### Statistics Reporting
```cpp
// Print entity pool status
for (const auto& stats : zombie_pool_mgr.get_all_statistics()) {
    printf("Pool Utilization: %.1f%%\n", 
           (float)stats.currently_in_use / stats.total_allocated * 100);
}

// Print texture cache status
texture_cache.print_report("TextureCache");

// Print audio system status
audio_batch.print_report("AudioBatching");

// Print hot-path profile
profiler.print_report("Game Loop Profile");
```

### Memory Monitoring
```cpp
// Check memory pressure
if (zombie_pool->get_utilization() > 90.0f) {
    printf("WARNING: Zombie pool nearly full\n");
}

if (texture_cache.get_size_bytes() > 60 * 1024 * 1024) {  // 60 MB of 64 MB
    printf("WARNING: Texture cache near limit\n");
}
```

---

## Troubleshooting

### Entity Pool Exhaustion
**Symptom:** `allocate()` returns nullptr  
**Cause:** Pool capacity exceeded  
**Solution:** Increase pool size or implement better entity recycling

### Texture Cache Misses
**Symptom:** High miss rate (< 50%)  
**Cause:** Cache too small for working set  
**Solution:** Increase cache size or reduce texture resolution

### Audio Batch Overflow
**Symptom:** Audio commands being dropped  
**Cause:** Batch processing can't keep up  
**Solution:** Increase batch size or reduce audio command frequency

### Profiling Overhead
**Symptom:** Performance degradation when profiling  
**Cause:** Profiling instrumentation too heavy  
**Solution:** Reduce profiling scope or disable in production

---

## Next Steps

1. **Compile with new headers** - Ensure no build errors
2. **Create simple tests** - Validate each component
3. **Integrate into game** - Replace existing systems gradually
4. **Profile & tune** - Use HotPathProfiler to find sweet spots
5. **Benchmark** - Measure actual performance improvements

---

## References

- `EntityPooling.h` - Object pooling framework
- `LRUCache.h` - Caching framework
- `AudioBatching.h` - Audio command batching
- `HotPathProfiler.h` - Performance profiling
- `MemoryPool.h` - Existing memory pooling (reference)
- `JNIBridge.h` - Threading utilities

---

**Status:** Ready for integration  
**Estimated Performance Gain:** 15-30%  
**Complexity:** Medium  
**Risk Level:** Low (backward compatible)
