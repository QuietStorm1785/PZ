# Medium-Term Optimizations Usage Examples

**Date:** January 19, 2026

---

## Table of Contents

1. [Entity Pool Usage](#entity-pool-usage)
2. [Texture Caching Usage](#texture-caching-usage)
3. [Audio Batching Usage](#audio-batching-usage)
4. [Hot-Path Profiling Usage](#hot-path-profiling-usage)
5. [Integrated Game System Example](#integrated-game-system-example)
6. [Performance Monitoring](#performance-monitoring)

---

## Entity Pool Usage

### Basic Entity Pool

```cpp
#include "EntityPooling.h"

class ZombieManager {
private:
    jni::pooling::ContiguousEntityPool<Zombie> zombie_pool_;
    std::vector<Zombie*> active_zombies_;

public:
    ZombieManager()
        : zombie_pool_(2048, "ZombiePool") {}

    // Spawn zombie
    Zombie* spawn_zombie(float x, float y, const std::string& type) {
        Zombie* zombie = zombie_pool_.allocate();
        if (!zombie) {
            printf("ERROR: Zombie pool exhausted!\n");
            return nullptr;
        }
        
        zombie->initialize(x, y, type);
        active_zombies_.push_back(zombie);
        return zombie;
    }

    // Remove zombie
    void remove_zombie(Zombie* zombie) {
        auto it = std::find(active_zombies_.begin(), active_zombies_.end(), zombie);
        if (it != active_zombies_.end()) {
            active_zombies_.erase(it);
            zombie_pool_.release(zombie);
        }
    }

    // Get pool statistics
    void print_status() {
        auto stats = zombie_pool_.get_statistics();
        printf("Zombie Pool: %u/%u in use (%.1f%%)\n",
               stats.currently_in_use, 
               stats.total_allocated,
               zombie_pool_.get_utilization());
    }
};
```

### Multi-Tier Pool Manager

```cpp
class EntityManager {
private:
    jni::pooling::MultiTierPoolManager<Entity> entity_manager_;

public:
    EntityManager() : entity_manager_("EntityManager") {
        // Tier 1: Small entities (zombies, NPCs)
        entity_manager_.add_tier(2048, "SmallEntities");
        
        // Tier 2: Medium entities (vehicles, barricades)
        entity_manager_.add_tier(512, "MediumEntities");
        
        // Tier 3: Large entities (buildings, structures)
        entity_manager_.add_tier(128, "LargeEntities");
    }

    Entity* create_entity() {
        return entity_manager_.allocate();
    }

    void destroy_entity(Entity* entity) {
        entity_manager_.release(entity);
    }

    void print_pool_status() {
        entity_manager_.print_report();
    }
};
```

### Pooled Entity with RAII

```cpp
class ZombieAI {
public:
    void update_zombies(ZombieManager& manager) {
        for (int i = 0; i < 100; ++i) {
            // Auto-cleanup when pool_zombie goes out of scope
            jni::pooling::PooledEntity<Zombie> pool_zombie(
                manager.zombie_pool_.allocate(), 
                &manager.zombie_pool_);
            
            if (!pool_zombie) {
                printf("Pool exhausted, skipping spawn\n");
                continue;
            }
            
            pool_zombie->set_position(rand() % 1000, rand() % 1000);
            pool_zombie->set_type("Walker");
            
            // Automatically released on scope exit
        }
    }
};
```

---

## Texture Caching Usage

### Basic Texture Cache

```cpp
#include "LRUCache.h"

class TextureManager {
private:
    jni::caching::LRUCache<std::string, Texture> texture_cache_;
    const size_t MAX_TEXTURE_CACHE = 128 * 1024 * 1024;  // 128 MB

public:
    TextureManager() 
        : texture_cache_(MAX_TEXTURE_CACHE) {}

    std::shared_ptr<Texture> get_texture(const std::string& path) {
        // Check if already cached
        auto cached = texture_cache_.get(path);
        if (cached) {
            printf("Cache HIT: %s\n", path.c_str());
            return cached;
        }

        printf("Cache MISS: %s (loading from disk)\n", path.c_str());

        // Load from disk
        auto texture = load_texture_from_disk(path);
        size_t size_bytes = texture->get_width() * texture->get_height() * 4;

        // Cache for future use
        texture_cache_.put(path, texture, size_bytes);
        return texture;
    }

    void preload_textures(const std::vector<std::string>& paths) {
        for (const auto& path : paths) {
            get_texture(path);
        }
    }

    void print_cache_stats() {
        auto stats = texture_cache_.get_statistics();
        printf("\nTexture Cache Statistics:\n");
        printf("  Items: %u\n", stats.num_items);
        printf("  Memory: %.2f MB / %.2f MB\n",
               stats.current_size_bytes / 1024.0f / 1024.0f,
               stats.max_size_bytes / 1024.0f / 1024.0f);
        printf("  Hit Rate: %.1f%% (%llu hits, %llu misses)\n",
               stats.hit_rate(), stats.hits, stats.misses);
    }

private:
    std::shared_ptr<Texture> load_texture_from_disk(const std::string& path) {
        // Stub - actual implementation loads from disk
        return std::make_shared<Texture>();
    }
};
```

### Sprite Animation Frame Cache

```cpp
class AnimationController {
private:
    jni::caching::LRUCache<std::string, SpriteFrame> frame_cache_;

public:
    AnimationController()
        : frame_cache_(64 * 1024 * 1024) {}  // 64 MB for frames

    SpriteFrame* get_animation_frame(const std::string& animation_id,
                                     int frame_number) {
        std::string cache_key = animation_id + "_" + std::to_string(frame_number);
        
        auto cached = frame_cache_.get(cache_key);
        if (cached) {
            return cached.get();
        }

        // Load frame from animation resource
        auto frame = load_frame(animation_id, frame_number);
        size_t frame_size = calculate_frame_size(frame.get());
        
        frame_cache_.put(cache_key, frame, frame_size);
        return frame.get();
    }

private:
    std::shared_ptr<SpriteFrame> load_frame(const std::string& id, int num) {
        return std::make_shared<SpriteFrame>();
    }

    size_t calculate_frame_size(SpriteFrame* frame) const {
        return 256 * 256 * 4;  // Assuming 256x256 RGBA
    }
};
```

---

## Audio Batching Usage

### Basic Audio Batching

```cpp
#include "AudioBatching.h"

class SoundSystem {
private:
    jni::audio::AudioBatchingSystem batch_system_;
    jni::audio::SpatialAudioManager spatial_audio_;

public:
    SoundSystem()
        : batch_system_(256),
          spatial_audio_(batch_system_) {}

    void play_zombie_sound(float x, float y, float z,
                          const std::string& sound_file) {
        // Automatically batched, flushed when batch full
        batch_system_.play_sound(sound_file, x, y, z, 0.8f, 100.0f);
    }

    void update_player_position(float x, float y, float z) {
        spatial_audio_.set_listener_position(x, y, z);
    }

    void process_audio() {
        // Flush any pending commands
        batch_system_.flush_batch();

        // Process all batches
        batch_system_.process_all_batches([this](const auto& batch) {
            for (const auto& cmd : batch.get_commands()) {
                // Apply audio command to underlying system
                execute_command(cmd);
            }
        });
    }

    void print_stats() {
        batch_system_.print_report("SoundSystem");
    }

private:
    void execute_command(const jni::audio::AudioCommand& cmd) {
        // Implementation-specific command execution
    }
};
```

### Advanced Spatial Audio

```cpp
class GameAudioSystem {
private:
    jni::audio::AudioBatchingSystem batch_system_;
    jni::audio::SpatialAudioManager spatial_audio_;
    
public:
    GameAudioSystem()
        : batch_system_(512),
          spatial_audio_(batch_system_) {}

    void play_sound_3d(const std::string& sound_file,
                      float source_x, float source_y, float source_z,
                      float max_range = 100.0f) {
        // Calculate volume based on distance
        float volume = spatial_audio_.calculate_volume_attenuation(
            source_x, source_y, source_z, max_range);

        // Calculate panning for stereo
        float pan = spatial_audio_.calculate_pan(source_x, source_y);

        if (volume > 0.0f) {
            batch_system_.play_sound(sound_file, source_x, source_y, source_z,
                                    volume, max_range);
        }
    }

    void update_game() {
        // Update listener (player) position
        float player_x, player_y, player_z;
        get_player_position(player_x, player_y, player_z);
        spatial_audio_.set_listener_position(player_x, player_y, player_z);

        // Process batch
        process_audio();
    }

private:
    void process_audio() {
        batch_system_.flush_batch();
        batch_system_.process_all_batches([](const auto& batch) {
            // Apply audio commands
        });
    }

    void get_player_position(float& x, float& y, float& z) {
        // Get from player object
    }
};
```

---

## Hot-Path Profiling Usage

### Function-Level Profiling

```cpp
#include "HotPathProfiler.h"

class GameLoop {
public:
    void update() {
        {
            PROFILE_FUNCTION_CALL();
            update_game_logic();
        }

        {
            PROFILE_FUNCTION_CALL();
            render_frame();
        }

        {
            PROFILE_FUNCTION_CALL();
            update_audio();
        }
    }

private:
    void update_game_logic() {
        PROFILE_BLOCK("ZombieUpdate");
        // Update zombies
        
        PROFILE_BLOCK("PlayerUpdate");
        // Update player
        
        PROFILE_BLOCK("VehicleUpdate");
        // Update vehicles
    }

    void render_frame() {
        PROFILE_BLOCK("Rendering");
        // Render
    }

    void update_audio() {
        PROFILE_BLOCK("AudioProcessing");
        // Process audio
    }
};
```

### Performance Reporting

```cpp
class PerformanceMonitor {
public:
    void print_performance_report() {
        auto& profiler = jni::profiling::get_global_profiler();
        
        printf("\n=== FRAME PERFORMANCE ANALYSIS ===\n");
        
        // Print all stats
        profiler.print_report("Frame Breakdown");

        // Get top 5 bottlenecks
        auto hottest = profiler.get_hottest_functions(5);
        
        printf("\nTop Bottlenecks (optimization targets):\n");
        for (size_t i = 0; i < hottest.size(); ++i) {
            const auto& stat = hottest[i];
            printf("%zu. %s (%.2f%% of frame time)\n",
                   i + 1, 
                   stat.function_name.c_str(),
                   stat.percentage_of_total(profiler.get_total_time()));
        }
    }

    void reset_profiling() {
        auto& profiler = jni::profiling::get_global_profiler();
        profiler.reset();
    }
};
```

---

## Integrated Game System Example

```cpp
class OptimizedGameEngine {
private:
    // Entity pooling
    jni::pooling::ContiguousEntityPool<Zombie> zombie_pool_{2048, "Zombies"};
    
    // Texture caching
    jni::caching::LRUCache<std::string, Texture> texture_cache_{128 * 1024 * 1024};
    
    // Audio batching
    jni::audio::AudioBatchingSystem audio_batch_{256};
    jni::audio::SpatialAudioManager spatial_audio_{audio_batch_};

public:
    void update_frame() {
        // Profile the entire frame
        PROFILE_FUNCTION_CALL();

        // Update game logic
        {
            PROFILE_BLOCK("GameLogic");
            update_zombies();
            update_player();
            update_world();
        }

        // Render
        {
            PROFILE_BLOCK("Rendering");
            render_game();
        }

        // Process audio
        {
            PROFILE_BLOCK("Audio");
            audio_batch_.flush_batch();
            audio_batch_.process_all_batches([](const auto& batch) {
                // Execute audio commands
            });
        }
    }

    void print_diagnostics() {
        printf("\n╔═══════════════════════════════════╗\n");
        printf("║   GAME ENGINE DIAGNOSTICS        ║\n");
        printf("╚═══════════════════════════════════╝\n\n");

        // Entity pools
        printf("Zombie Pool: %u/%u (%.1f%%)\n",
               zombie_pool_.get_statistics().currently_in_use,
               zombie_pool_.capacity(),
               zombie_pool_.get_utilization());

        // Texture cache
        auto tex_stats = texture_cache_.get_statistics();
        printf("Texture Cache: %.1f%% hit rate, %.2f MB used\n",
               tex_stats.hit_rate(),
               tex_stats.current_size_bytes / 1024.0f / 1024.0f);

        // Audio batching
        auto audio_stats = audio_batch_.get_statistics();
        printf("Audio Batching: %.1f avg cmds/batch\n",
               audio_stats.avg_batch_size());

        // Hot-path profiling
        auto& profiler = jni::profiling::get_global_profiler();
        profiler.print_report("Frame Performance");
    }

private:
    void update_zombies() {
        PROFILE_BLOCK("ZombieLogic");
        // Update all active zombies
        // Spawn new zombies from pool as needed
    }

    void update_player() {
        PROFILE_BLOCK("PlayerLogic");
        // Update player position for spatial audio
        spatial_audio_.set_listener_position(player_x, player_y, player_z);
    }

    void update_world() {
        PROFILE_BLOCK("WorldLogic");
        // Update world state
    }

    void render_game() {
        PROFILE_BLOCK("RenderWorld");
        // Load textures from cache
        auto texture = texture_cache_.get("player_skin.png");
        
        // Render
    }
};
```

---

## Performance Monitoring

### Real-time Dashboard

```cpp
class PerformanceDashboard {
private:
    struct FrameStats {
        double fps = 0.0;
        std::chrono::microseconds frame_time{0};
        std::chrono::microseconds logic_time{0};
        std::chrono::microseconds render_time{0};
        std::chrono::microseconds audio_time{0};
    };

public:
    void update() {
        auto start = std::chrono::high_resolution_clock::now();

        // Update game
        game_engine_.update_frame();

        auto end = std::chrono::high_resolution_clock::now();
        auto frame_time = std::chrono::duration_cast<std::chrono::microseconds>(
            end - start);

        // Record frame metrics
        frame_stats_.frame_time = frame_time;
        frame_stats_.fps = 1.0e6 / frame_time.count();
    }

    void print_dashboard() {
        printf("\n┌─────────────────────────────────────┐\n");
        printf("│   REAL-TIME PERFORMANCE DASHBOARD   │\n");
        printf("├─────────────────────────────────────┤\n");
        printf("│ FPS: %.1f                            │\n", frame_stats_.fps);
        printf("│ Frame Time: %.2f ms                  │\n", 
               frame_stats_.frame_time.count() / 1000.0);
        printf("└─────────────────────────────────────┘\n");
    }

private:
    OptimizedGameEngine game_engine_;
    FrameStats frame_stats_;
};
```

---

## Compilation & Integration Checklist

- [ ] All `.h` files compile without errors
- [ ] Entity pool integration tested
- [ ] Texture cache hit rate > 80%
- [ ] Audio commands batching properly
- [ ] Profiling overhead < 5%
- [ ] Performance improvement measured
- [ ] No memory leaks detected
- [ ] All systems thread-safe

---

**Next Steps:**

1. Integrate these examples into actual game systems
2. Measure baseline performance
3. Enable profiling in debug builds
4. Identify bottlenecks with HotPathProfiler
5. Apply targeted optimizations
6. Verify performance improvements
