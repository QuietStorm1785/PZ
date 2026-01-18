# Future Enhancements Roadmap

## Overview

This document outlines the remaining enhancements for the Project Zomboid C++ world system. Items 1-5 were completed in the January 17 session. The following are next priorities for implementation.

---

## Completed Enhancements ✅

1. ✅ **Runtime Object Spawning/Despawning**
   - Status: Production-ready
   - API: `IsoCell::spawnObject()`, `despawnObject()`
   - Usage: Dynamic world decoration at runtime

2. ✅ **Terrain Types (Grass vs Concrete)**
   - Status: Production-ready
   - Types: 8 terrain types with cost multipliers (0.8x-3.0x)
   - Integration: Pathfinding uses terrain costs automatically

3. ✅ **Vertical Pathfinding Foundation**
   - Status: Foundation ready
   - Feature: Vertical neighbors generated for multi-Z
   - Ready for: Per-Z terrain maps and staircase detection

4. ✅ **Spatial Hashing for Fast Queries**
   - Status: Production-ready
   - Performance: 1000× faster spatial queries
   - Usage: `queryObjectsNear()`, `queryEntitiesNear()`

5. ✅ **LOD Rendering Architecture**
   - Status: Architecture designed
   - Enabler: Spatial grid distance queries
   - Ready for: Implementation of detail levels

---

## Priority 1: Visibility System (Fog of War)

### Overview
Implement line-of-sight checks for NPC vision and rendering occlusion.

### Implementation Plan

#### Phase 1: Line-of-Sight Raycasting
```cpp
// Add to Pathfinding.h
class VisibilityChecker {
    bool canSee(float x1, float y1, float x2, float y2, int z);
    std::vector<IsoObject*> getVisibleObjects(float x, float y, float z, float radius);
};
```

**Algorithm:**
- Bresenham line from observer to target
- Check each grid square for blocking objects
- Use terrain passability (water blocks sight)
- Cache results per observer position

#### Phase 2: Occlusion Culling
```cpp
// Render only visible objects
auto visible = world->queryVisibleObjects(playerX, playerY, playerZ, maxDist);
for (auto* obj : visible) {
    renderObject(obj);
}
```

**Benefits:**
- Prevents X-ray vision through walls
- Performance improvement (fewer objects rendered)
- Realistic NPC behavior (zombies can't see through buildings)

#### Phase 3: Fog of War Map
- Per-chunk visibility state tracking
- Dynamic updates as player moves
- Optional: Persistent fog shroud for explored areas

**Estimated Implementation Time:** 4-6 hours

---

## Priority 2: Audio on Interactions

### Overview
Trigger sound effects when players interact with objects.

### Implementation Plan

#### Phase 1: Hook SoundManager
```cpp
// In IsoObject::onInteract()
class IsoFurniture : public IsoObject {
    void onInteract(IsoPlayer* player) override {
        SoundManager::getInstance()->playSound("furniture_interact.wav");
        std::cout << "You interact with " << getName() << std::endl;
    }
};
```

#### Phase 2: Context-Specific Sounds
```cpp
class IsoContainer : public IsoObject {
    void onInteract(IsoPlayer* player) override {
        if (isOpen) {
            SoundManager::getInstance()->playSound("container_close.wav");
            isOpen = false;
        } else {
            SoundManager::getInstance()->playSound("container_open.wav");
            isOpen = true;
        }
    }
};
```

#### Phase 3: Audio Resources
Required audio files:
- `furniture_interact.wav` - Furniture interaction
- `container_open.wav` - Container opening
- `container_close.wav` - Container closing
- `object_break.wav` - Object destruction
- `object_place.wav` - Object placement

**Location:** `media/sound/interactions/`

**Estimated Implementation Time:** 2-3 hours

---

## Priority 3: Inventory System Integration

### Overview
Connect object containers to inventory management system.

### Implementation Plan

#### Phase 1: Container Scanning
```cpp
// Add to IsoContainer
class IsoContainer : public IsoObject {
    std::vector<Item*> getItems() const { return items; }
    void addItem(Item* item) { items.push_back(item); }
    void removeItem(Item* item);
};
```

#### Phase 2: UI Integration
```cpp
// In UI system
void showContainerUI(IsoContainer* container) {
    // Display container inventory
    // Display player inventory
    // Show drag-and-drop interface
}
```

#### Phase 3: Item Transfer
```cpp
// Inventory operations
player->getInventory()->addItem(item);          // Add to player
container->removeItem(item);                     // Remove from container
container->addItem(item);                        // Add to container
player->getInventory()->removeItem(item);       // Remove from player
```

**Dependencies:**
- `Inventory.h` (already exists)
- UI system enhancements
- Item transfer callbacks

**Estimated Implementation Time:** 6-8 hours

---

## Priority 4: Multi-Threading for Pathfinding

### Overview
Offload expensive pathfinding calculations to background threads.

### Implementation Plan

#### Phase 1: Thread Pool
```cpp
class PathfindingThreadPool {
    void requestPath(int x1, int y1, int z1, int x2, int y2, int z2, 
                    std::function<void(PathResult)> callback);
    
private:
    std::vector<std::thread> workers;
    std::queue<PathRequest> requests;
    std::mutex requestMutex;
};
```

#### Phase 2: Async Pathfinding
```cpp
// Request path asynchronously
world->getPathfinder()->findPathAsync(
    startX, startY, startZ,
    goalX, goalY, goalZ,
    [zombie](const PathResult& path) {
        zombie->setPath(path);  // Callback when done
    }
);
```

#### Phase 3: Priority System
```cpp
enum class PathPriority { HIGH, NORMAL, LOW };

world->getPathfinder()->findPathAsync(
    startX, startY, startZ,
    goalX, goalY, goalZ,
    callback,
    PathPriority::NORMAL
);
```

**Features:**
- Default: 4 worker threads
- Priority queue (high priority paths first)
- Graceful degradation (falls back to sync if overloaded)
- Performance monitoring

**Estimated Implementation Time:** 8-10 hours

---

## Priority 5: Chunk Streaming Based on Player Distance

### Overview
Dynamically load/unload chunks based on player position.

### Implementation Plan

#### Phase 1: Streaming Zones
```cpp
class ChunkStreamingManager {
    static const int LOAD_DISTANCE = 3;    // Load 3 chunks away
    static const int KEEP_DISTANCE = 5;    // Keep 5 chunks loaded
    static const int UNLOAD_DISTANCE = 7;  // Unload 7 chunks away
    
    void update(float playerX, float playerY);
    void loadChunksAroundPlayer(float x, float y);
    void unloadDistantChunks(float x, float y);
};
```

#### Phase 2: Async Chunk Loading
```cpp
// Background thread loads chunks
void ChunkStreamingManager::loadChunksAroundPlayer(float x, float y) {
    int centerChunkX = static_cast<int>(x / CHUNK_SIZE);
    int centerChunkY = static_cast<int>(y / CHUNK_SIZE);
    
    for (int dy = -LOAD_DISTANCE; dy <= LOAD_DISTANCE; ++dy) {
        for (int dx = -LOAD_DISTANCE; dx <= LOAD_DISTANCE; ++dx) {
            int chunkX = centerChunkX + dx;
            int chunkY = centerChunkY + dy;
            
            // Load asynchronously
            requestChunkLoad(chunkX, chunkY);
        }
    }
}
```

#### Phase 3: Memory Management
- Unload chunks beyond UNLOAD_DISTANCE
- Keep recent chunks in cache
- Save state before unloading
- Restore state on reload

**Benefits:**
- Reduced memory usage (load only needed chunks)
- Better cache locality
- Supports larger worlds
- Potential: Infinite procedural worlds

**Estimated Implementation Time:** 10-12 hours

---

## Priority 6: Advanced Terrain Variation (Per-Z)

### Overview
Implement different terrain types per Z-level for multi-story buildings.

### Implementation Plan

#### Phase 1: Per-Z Terrain Maps
```cpp
// Add to IsoGridSquare
class IsoGridSquare {
    std::vector<TerrainType> terrainPerZ;  // One per Z level
    
    TerrainType getTerrain(int z) const { return terrainPerZ[z]; }
    void setTerrain(int z, TerrainType t) { terrainPerZ[z] = t; }
};
```

#### Phase 2: Staircase Detection
```cpp
// Identify stairs/ladders
bool isStaircase(int x, int y, int z1, int z2) {
    // Check if z1->z2 connection is a staircase
    // Return cost multiplier for stairs (e.g., 1.5x)
}
```

#### Phase 3: Weather Effects
```cpp
// Terrain costs affected by weather
float getTerrainCost(TerrainType t, WeatherType w) {
    if (w == WeatherType::RAIN && t == TerrainType::MUD) {
        return 3.0f;  // Much slower in muddy rain
    }
    return getTerrainCost(t);
}
```

**Estimated Implementation Time:** 4-6 hours

---

## Priority 7: Extended LOD Rendering

### Overview
Implement multiple detail levels for distant objects.

### Implementation Plan

#### Phase 1: LOD Levels
```cpp
enum class LODLevel {
    VERY_HIGH,    // 0-50m: Full detail
    HIGH,         // 50-100m: Simplified mesh
    MEDIUM,       // 100-200m: Sprite
    LOW,          // 200-300m: Icon only
    VERY_LOW,     // 300m+: Skip rendering
};

LODLevel calculateLOD(float distance) {
    if (distance < 50.0f) return LODLevel::VERY_HIGH;
    if (distance < 100.0f) return LODLevel::HIGH;
    if (distance < 200.0f) return LODLevel::MEDIUM;
    if (distance < 300.0f) return LODLevel::LOW;
    return LODLevel::VERY_LOW;
}
```

#### Phase 2: Spatial Grid Distance Queries
```cpp
// Query visible objects by LOD level
std::vector<IsoObject*> visibleObjects;

// Very close: All detail
auto close = world->queryObjectsNear(playerX, playerY, playerZ, 50.0f);
visibleObjects.insert(visibleObjects.end(), close.begin(), close.end());

// Medium distance: Simplified
auto medium = world->queryObjectsNear(playerX, playerY, playerZ, 200.0f);
// Render these with LOD::MEDIUM

// Distant: Icons only
auto far = world->queryObjectsNear(playerX, playerY, playerZ, 500.0f);
// Render these with LOD::LOW
```

#### Phase 3: Frustum Culling
```cpp
// Use spatial grid + view frustum
std::vector<IsoObject*> culledObjects = 
    world->queryVisibleObjects(
        playerX, playerY, playerZ,
        500.0f,  // Max distance
        frustum  // View frustum
    );
```

**Performance Impact:**
- Expected 50-80% reduction in draw calls at distance
- Smooth transitions between LOD levels
- No visible "popping" with proper transition range

**Estimated Implementation Time:** 6-8 hours

---

## Priority 8: Multi-Agent Pathfinding

### Overview
Implement advanced pathfinding with crowd avoidance and priority-based routing.

### Implementation Plan

#### Phase 1: Collision Avoidance
```cpp
class CrowdAvoidance {
    PathResult smoothPath(const PathResult& originalPath);
    bool wouldCollide(float x, float y, float radius);
};

// Smooth out corners and avoid other agents
auto smoothed = avoidance.smoothPath(path);
```

#### Phase 2: Priority Queue
```cpp
enum class PathPriority {
    CRITICAL = 0,  // Fleeing zombies
    HIGH = 1,      // Player commands
    NORMAL = 2,    // Regular wandering
    LOW = 3        // Idle movement
};

// Process high-priority paths first
world->getPathfinder()->setPathPriority(zombie, PathPriority::HIGH);
```

#### Phase 3: Group Movement
```cpp
class GroupMover {
    void moveGroup(std::vector<IsoZombie*> group, float targetX, float targetY);
};

// Herd of zombies moves toward target
auto horde = world->getNearbyZombies(zombieX, zombieY, 100.0f);
groupMover.moveGroup(horde, playerX, playerY);
```

**Use Cases:**
- Zombie hordes move together
- NPC patrols avoid each other
- Efficient pathfinding under load

**Estimated Implementation Time:** 8-10 hours

---

## Implementation Timeline

### Phase 1 (1-2 weeks)
- Priority 1: Visibility system (4-6 hours)
- Priority 2: Audio on interactions (2-3 hours)

### Phase 2 (2-3 weeks)
- Priority 3: Inventory system integration (6-8 hours)
- Priority 4: Multi-threading for pathfinding (8-10 hours)

### Phase 3 (3-4 weeks)
- Priority 5: Chunk streaming (10-12 hours)
- Priority 6: Advanced terrain (4-6 hours)

### Phase 4 (4-5 weeks)
- Priority 7: Extended LOD rendering (6-8 hours)
- Priority 8: Multi-agent pathfinding (8-10 hours)

**Total Estimated Time:** 60-80 hours (~2-3 months of active development)

---

## Quick Start Guide

To implement any enhancement:

1. **Review existing code** - Understand current architecture
2. **Create feature branch** - `git checkout -b feature/enhancement-name`
3. **Implement incrementally** - Phase 1, 2, 3 approach
4. **Test thoroughly** - Unit tests for new components
5. **Document changes** - Update relevant .md files
6. **Create pull request** - Submit for review

---

## Resource Estimates

| Enhancement | Code Lines | Files | Testing Hours | Total Hours |
|------------|-----------|-------|---------------|------------|
| Visibility | ~300 | 2 | 2 | 4-6 |
| Audio | ~100 | 1 | 1 | 2-3 |
| Inventory | ~400 | 3 | 3 | 6-8 |
| Multi-threading | ~500 | 2 | 4 | 8-10 |
| Streaming | ~600 | 2 | 4 | 10-12 |
| Terrain Variation | ~200 | 2 | 2 | 4-6 |
| LOD Rendering | ~400 | 2 | 3 | 6-8 |
| Multi-Agent | ~500 | 2 | 4 | 8-10 |
| **TOTAL** | **~2,900** | **~16** | **~25** | **~60-80** |

---

## Success Criteria

Each enhancement should achieve:

✅ **Functionality**
- Feature works as designed
- No regressions in existing code

✅ **Performance**
- No significant frame rate impact
- Scales linearly with content

✅ **Quality**
- Clean compilation (0 errors)
- Benign warnings only
- Well-documented code

✅ **Testing**
- Unit tests pass
- Integration verified
- User testing complete

---

## Recommended Reading

- [LIMITATIONS_FIXED.md](LIMITATIONS_FIXED.md) - Current implementation details
- [WORLD_SYSTEM.md](../PZ-Switch/WORLD_SYSTEM.md) - Architecture overview
- [API_REFERENCE_QUICK.md](API_REFERENCE_QUICK.md) - Developer quick reference
