# Optimization Systems - Quick Reference

## Entity Pooling

### Include
```cpp
#include "ObjectPool.h"
using namespace zombie::memory;
```

### Create Pool
```cpp
// 50 initial entities, max 500
EntityPool pool(50, 500);

// Or use default (50 initial, 500 max)
EntityPool pool;
```

### Acquire Entity
```cpp
Entity* entity = pool.acquire();
if (entity) {
    entity->setPosition(100, 200);
    entity->setHealth(50);
    // Use entity...
}
```

### Release Entity
```cpp
pool.release(entity);
// Entity returned to pool, automatically reset
```

### Statistics
```cpp
pool.getPoolSize()      // Entities available in pool
pool.getActiveCount()   // Entities in use
pool.getTotalCreated()  // Total unique entities created
pool.getTotalAcquired() // Total acquisitions
pool.getTotalReleased() // Total releases
pool.getHitRate()       // % reused (not newly created)
```

### Custom Reset
```cpp
pool.setResetFunction([](Entity* e) {
    e->setPosition(0, 0);
    e->setVelocity(0, 0);
    e->setHealth(100);
});
```

---

## Asset Streaming

### Include
```cpp
#include "AssetStreaming.h"
using namespace zombie::assets;
```

### Configuration
```cpp
AssetStreamingSystem::Config config;
config.maxMemoryBytes = 256 * 1024 * 1024;  // 256 MB
config.maxCachedAssets = 1000;
config.autoUnload = true;
config.unloadDelay = 5.0f;  // seconds
```

### Singleton Usage
```cpp
auto& mgr = StreamingTextureManager::getInstance();

// Request texture (loads if not cached)
auto handle = mgr.requestTexture("media/zombies.png");

if (handle.isValid()) {
    SDL_Texture* tex = handle.get();
    // Render with texture
}
// handle destroyed here, refcount decremented
```

### Preload
```cpp
// Load in background
mgr.preloadTexture("media/player.png");
```

### Update (call once per frame)
```cpp
void gameLoop() {
    auto& mgr = StreamingTextureManager::getInstance();
    
    while (running) {
        float deltaTime = 0.016f;  // 60 FPS
        
        // Update streaming system
        mgr.update(deltaTime);
        
        // Render...
    }
}
```

### Statistics
```cpp
size_t memUsage = mgr.getCurrentMemoryUsage();     // bytes
float hitRate = mgr.getCacheHitRate() * 100;        // percentage
size_t requests = mgr.getTotalRequests();           // total
size_t hits = mgr.getCacheHits();                   // cached
size_t misses = mgr.getCacheMisses();               // loaded
```

### Manual Control
```cpp
// Check if loaded
bool loaded = mgr.isLoaded("media/zombies.png");

// Unload specific texture
mgr.unload("media/zombies.png");

// Unload all unused
mgr.unloadUnused();
```

---

## Performance Tips

### Entity Pooling
- Use larger initial pool size for frequently created entities
- Monsters/bullets benefit most (high creation rate)
- Call `pool.clear()` between level loads
- Check hit rate to tune pool size

### Asset Streaming
- Preload main menu assets before showing menu
- Set memory budget based on target platform
- Monitor hit rate (should be 70%+ in normal gameplay)
- Reduce budget for low-memory devices
- Increase unload delay for frequently reused assets

---

## Example: Zombie Spawning with Pooling

```cpp
class ZombieSpawner {
    EntityPool zombiePool{100, 1000};
    
public:
    void spawnZombie(float x, float y) {
        Entity* entity = zombiePool.acquire();
        if (!entity) return;  // Pool full
        
        entity->setPosition(x, y);
        entity->setType(EntityType::ZOMBIE);
        // Initialize zombie...
        
        activeZombies.push_back(entity);
    }
    
    void removeZombie(Entity* zombie) {
        activeZombies.erase(zombie);
        zombiePool.release(zombie);  // Back to pool
    }
    
    void printStats() {
        std::cout << "Pool: " << zombiePool.getPoolSize() << " available\n";
        std::cout << "Active: " << zombiePool.getActiveCount() << "\n";
        std::cout << "Hit rate: " << zombiePool.getHitRate() << "%\n";
    }
};
```

---

## Example: Texture Loading with Streaming

```cpp
class GameScene {
    AssetHandle<SDL_Texture> playerTex;
    AssetHandle<SDL_Texture> bgTex;
    
public:
    void load() {
        auto& mgr = StreamingTextureManager::getInstance();
        
        // Will load immediately or from cache
        playerTex = mgr.requestTexture("media/player.png");
        bgTex = mgr.requestTexture("media/background.png");
    }
    
    void render(SDL_Renderer* r) {
        if (playerTex.isValid()) {
            renderTexture(r, playerTex.get(), playerPos);
        }
        if (bgTex.isValid()) {
            renderTexture(r, bgTex.get(), bgPos);
        }
    }
    
    void unload() {
        auto& mgr = StreamingTextureManager::getInstance();
        
        // Handles destroyed here, refcounts decremented
        playerTex = AssetHandle<SDL_Texture>();
        bgTex = AssetHandle<SDL_Texture>();
        
        // Unload unused after delay
        mgr.update(1.0f);  // 1 second passed
    }
};
```

---

## Memory Calculation

### Entity Pooling
```
Pool Memory ≈ EntityCount × sizeof(Entity)
- Entity object: ~500 bytes
- 100 pooled entities: ~50 KB
- 1000 pooled entities: ~500 KB
```

### Asset Streaming
```
Texture Memory = Width × Height × 4 bytes (RGBA)
- 256×256: 256 KB
- 512×512: 1 MB
- 1024×1024: 4 MB
- 2048×2048: 16 MB

Budget Examples:
- 64 MB: ~16 high-res textures
- 128 MB: ~32 high-res textures
- 256 MB: ~64 high-res textures
```

---

## Test Suites

### Run Pooling Tests
```bash
cd build
./test_pooling
```

Output shows:
- Pool size and active count
- Hit rate percentage
- Total created/acquired/released
- Entity reset verification

### Run Streaming Tests
```bash
cd build
./test_streaming
```

Output shows:
- SDL initialization
- Cache behavior
- Memory usage
- Hit rate statistics

---

## Debugging

### Entity Pool Issues
```cpp
// Print pool state
std::cout << "Pool size: " << pool.getPoolSize() << std::endl;
std::cout << "Active: " << pool.getActiveCount() << std::endl;
std::cout << "Hit rate: " << pool.getHitRate() << "%" << std::endl;

// If hit rate is 0%, pool might not be reusing
// Check: Are entities being released back?
```

### Asset Streaming Issues
```cpp
auto& mgr = StreamingTextureManager::getInstance();

// Check cache hit rate
float hitRate = mgr.getCacheHitRate();
if (hitRate < 0.5f) {
    std::cout << "WARNING: Low cache hit rate\n";
}

// Monitor memory
size_t usage = mgr.getCurrentMemoryUsage();
size_t budget = 128 * 1024 * 1024;
if (usage > budget) {
    std::cout << "WARNING: Exceeding memory budget\n";
}
```

---

## Integration Checklist

- [ ] EntityPool used for zombie spawning
- [ ] EntityPool used for bullet/projectiles
- [ ] EntityPool used for effects/particles
- [ ] StreamingTextureManager used for all texture loads
- [ ] Memory budget set per platform
- [ ] Statistics monitored in debug view
- [ ] Performance profiled with systems enabled
- [ ] Hit rates logged to file for analysis
