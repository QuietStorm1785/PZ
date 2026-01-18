# Enhancement Implementation Guide

## Overview
This document outlines the implementation plan for 4 prioritized enhancements to the Project Zomboid C++ engine.

**Total Estimated Time:** 20-27 hours
- Quick Wins: 6-9 hours (Audio + Visibility)
- Medium Term: 14-18 hours (Inventory + Threading)

---

## Enhancement 1: Audio on Interactions ⏱️ 2-3 hours

### Framework Created ✅
- `AudioInteractionSystem.h` - Singleton audio manager
- `AudioInteractionSystem.cpp` - Stub implementation

### Status
**Framework Complete** - Ready for integration

### What Works Now
- Sound registry (type → audio path mappings)
- Action-specific sounds (object type → action → audio path)
- Default sound initialization

### Integration Points Needed

#### 1. Hook into IsoObject.h (Critical)
```cpp
// In IsoObject::onInteract()
void onInteract(IsoPlayer* player) override {
    AudioInteractionSystem::getInstance()->playInteractionSound(type, x, y);
    // ... existing interaction logic
}
```

#### 2. Hook into Container Operations
```cpp
// In ContainerInteractionSystem.cpp
bool ContainerInteractionSystem::openContainer(...) {
    if (openContainer) {
        AudioInteractionSystem::getInstance()->playObjectSound(
            "container", "open", player->getX(), player->getY()
        );
    }
}
```

#### 3. Add Sound Files
Create audio files or register existing ones:
```
media/sound/
  ├── door_interact.wav
  ├── window_interact.wav
  ├── container_open.wav
  ├── container_close.wav
  ├── furniture_activate.wav
  └── etc.
```

#### 4. SoundManager Integration
Update `SoundManager.playSound()` to support spatial audio (position-based volume/panning).

### Testing Checklist
- [ ] Sounds play on door interactions
- [ ] Sounds play on container open/close
- [ ] Sounds are position-aware (louder when close)
- [ ] No audio lag or stutter during interactions

---

## Enhancement 2: Visibility System / Fog of War ⏱️ 4-6 hours

### Framework Created ✅
- `VisibilitySystem.h` - VisibilityChecker + FogOfWarSystem
- `VisibilitySystem.cpp` - Stub implementation

### Status
**Framework Complete** - Core algorithms need implementation

### What Works Now
- Bresenham line tracing (ray casting)
- Visibility query caching (hash-based O(1) lookup)
- Fog of war grid storage
- Query methods (canSee, canSeeObject, getVisibleObjects)

### Integration Points Needed

#### 1. Occlusion Logic (Critical)
Implement `VisibilityChecker::isOccluding()`:
```cpp
bool VisibilityChecker::isOccluding(IsoGridSquare* square) {
    if (!square) return false;
    
    // Check terrain type
    if (square->getTerrainType() == TERRAIN_WALL) return true;
    
    // Check for solid objects
    for (auto obj : square->getObjects()) {
        if (obj->isSolid() && !obj->isTransparent()) return true;
    }
    
    return false;
}
```

#### 2. NPC Vision Integration
Update NPC AI to use visibility system:
```cpp
// In AIBehaviors.cpp
if (visibilitySystem->canSeeObject(npc, player)) {
    npc->setState(ALERT);
    npc->setTarget(player);
}
```

#### 3. Rendering Integration
Update renderer to use fog of war:
```cpp
// In rendering pipeline
if (fogSystem->getFogState(x, y, z) == UNEXPLORED) {
    skipRenderingTile(x, y, z);  // Don't render
} else if (fogSystem->getFogState(x, y, z) == EXPLORED) {
    renderTileGrayscale(x, y, z);  // Render darkened
} else {
    renderTileNormal(x, y, z);  // Render normally
}
```

#### 4. Performance Optimization
- Enable visibility query caching in frequently called code paths
- Profile raycasting performance with complex terrain
- Consider spatial partitioning for large FOV updates

### Testing Checklist
- [ ] Line-of-sight calculations are accurate
- [ ] Occlusion works for walls and solid objects
- [ ] Cache hit rate is > 80% in typical gameplay
- [ ] No performance regression with fog of war rendering
- [ ] Fog states transition smoothly (UNEXPLORED → EXPLORED → VISIBLE)

---

## Enhancement 3: Inventory System Integration ⏱️ 6-8 hours

### Framework Created ✅
- `InventoryManager.h` - Player inventory management
- `InventoryManager.cpp` - Stub implementation
- `Item` class - Basic item representation
- `ContainerInteractionSystem` - Container open/close/transfer logic

### Status
**Framework Complete** - UI and advanced features need work

### What Works Now
- Adding/removing items from inventory
- Weight tracking (max 100kg)
- Slot limits (max 40 items)
- Item type categorization
- Container transfer logic (framework)

### Integration Points Needed

#### 1. Hookup to IsoPlayer
```cpp
// In IsoPlayer.h
class IsoPlayer {
    InventoryManager* getInventory() { return inventory; }
private:
    InventoryManager* inventory;
};

// In IsoPlayer.cpp constructor
IsoPlayer::IsoPlayer() : inventory(new InventoryManager(this)) {}
```

#### 2. Container Implementation (TODO)
Define `IsoContainer` class:
```cpp
class IsoContainer {
public:
    void addItem(Item* item);
    void removeItem(Item* item);
    const std::vector<Item*>& getItems() const;
    int getMaxItems() const;
    bool isLocked() const;
private:
    std::vector<Item*> items;
    int maxItems;
    bool locked;
};
```

#### 3. UI Integration (Critical for playability)
- Create inventory UI panel
- Display inventory contents with weight/slot info
- Implement drag-and-drop item transfer
- Show container contents when opened
- Add pickup/drop item buttons

#### 4. Item Drop/Pickup System
```cpp
// Ground items appear as IsoObjects
class GroundItem : public IsoObject {
    Item* getItem() const { return item; }
    void pickUp(IsoPlayer* player) {
        player->getInventory()->addItem(item);
        destroy();
    }
private:
    Item* item;
};
```

#### 5. Audio Integration
Wire up container sounds:
```cpp
bool ContainerInteractionSystem::openContainer(...) {
    if (openContainer(container, player)) {
        AudioInteractionSystem::getInstance()->playObjectSound(
            "container", "open", player->getX(), player->getY()
        );
        return true;
    }
    return false;
}
```

### Testing Checklist
- [ ] Items can be added/removed from inventory
- [ ] Weight is calculated correctly
- [ ] Items cannot be added if inventory full/overweight
- [ ] Container transfers work bidirectionally
- [ ] Items can be dropped and picked up
- [ ] Ground items are visible and clickable
- [ ] Inventory UI displays correctly

---

## Enhancement 4: Multi-Threading Pathfinding ⏱️ 8-10 hours

### Framework Created ✅
- `PathfindingThreadPool.h` - Thread pool + request queue
- `PathfindingThreadPool.cpp` - Worker thread implementation
- `AsyncPathfinder` - Callback-based API

### Status
**Framework Complete** - A* algorithm needs proper implementation

### What Works Now
- Thread pool initialization
- Request queueing and result retrieval
- Callback mechanism for async results
- Simple straight-line pathfinding (placeholder)

### Implementation Work Needed

#### 1. A* Algorithm Implementation (Critical)
Replace simple straight-line with proper A*:
```cpp
bool PathfindingThreadPool::computePath(const PathRequest& request, 
                                       std::vector<std::pair<int, int>>& outPath) {
    // Priority queue of nodes
    std::priority_queue<PathNode*, std::vector<PathNode*>, 
                       std::function<bool(PathNode*, PathNode*)>> openSet(
        [](PathNode* a, PathNode* b) { return a->fCost > b->fCost; }
    );
    
    // Start node
    PathNode* startNode = new PathNode(startX, startY, startZ);
    openSet.push(startNode);
    
    // A* main loop
    while (!openSet.empty()) {
        PathNode* current = openSet.top();
        openSet.pop();
        
        if (current->x == endX && current->y == endY) {
            // Path found - reconstruct
            while (current != nullptr) {
                outPath.push_back({current->x, current->y});
                current = current->parent;
            }
            std::reverse(outPath.begin(), outPath.end());
            return true;
        }
        
        // Explore neighbors...
    }
    
    return false;  // Path not found
}
```

#### 2. Terrain Cost Integration
Implement `getTerrainCost()` properly:
```cpp
float PathfindingThreadPool::getTerrainCost(IsoGridSquare* square) {
    if (!square) return INFINITY;
    if (!isWalkable(square)) return INFINITY;
    
    switch (square->getTerrainType()) {
        case TERRAIN_GRASS: return 1.0f;
        case TERRAIN_ROAD: return 0.5f;
        case TERRAIN_WATER: return 5.0f;
        case TERRAIN_ROUGH: return 2.0f;
        case TERRAIN_WALL: return INFINITY;
        default: return 1.0f;
    }
}
```

#### 3. Visibility Integration
Incorporate visibility in pathfinding:
```cpp
// When exploring neighbors in A*
for (auto neighbor : getNeighbors(current)) {
    // Check if walkable
    if (!isWalkable(neighbor)) continue;
    
    // Check visibility for AI (don't path through unexplored areas)
    if (observer && !visibilitySystem->canSee(...)) {
        // Penalize unexplored areas
        neighbor->gCost *= 1.5f;
    }
}
```

#### 4. NPC Pathfinding Integration
Update NPC AI to use async pathfinding:
```cpp
// In AIBehaviors.cpp
void NPC::updatePathfinding() {
    if (!hasPath() || pathDone()) {
        // Request new path asynchronously
        int requestId = AsyncPathfinder::requestPathWithCallback(
            x, y, z, targetX, targetY, targetZ,
            [this](int id, const auto& path) {
                this->setPath(path);
            },
            priority  // Higher priority for nearby NPCs
        );
    }
}
```

#### 5. Main Thread Integration
Call callback updates in game loop:
```cpp
// In Core.cpp or GameStateMachine update
void update() {
    // ... other updates
    
    // Update async pathfinding results
    AsyncPathfinder::updateCallbacks();
    
    // ... rest of update
}
```

### Performance Considerations

#### Thread Pool Sizing
- 4 worker threads (DEFAULT_THREAD_COUNT) for typical 4-core systems
- Auto-detect core count for better scaling
- Consider background threads vs. dedicated pathfinding

#### Request Priority
- Low (0-2): Background zombie pathfinding
- Medium (3-7): NPC behavior
- High (8-10): Player or nearby threats

#### Memory Management
- Reuse PathNode objects in object pool
- Clear completed requests periodically
- Monitor queue size to detect bottlenecks

### Testing Checklist
- [ ] A* produces shortest/near-shortest paths
- [ ] Threading doesn't cause race conditions
- [ ] Request priority queue works correctly
- [ ] Callback mechanism executes on main thread
- [ ] Performance improvement over synchronous pathfinding is measurable
- [ ] No crashes during heavy NPC activity
- [ ] Game loop doesn't stutter during pathfinding

---

## Integration Priorities

### Phase 1: Quick Wins (Hours 0-9)
1. ✅ Create headers and stubs
2. Complete Audio Integration (2-3 hours)
   - Hook into IsoObject
   - Add sound files
   - Test interactions
3. Complete Visibility Framework (4-6 hours)
   - Implement occlusion logic
   - Hook into rendering
   - Test line-of-sight accuracy

### Phase 2: Medium Term (Hours 9-27)
4. Complete Inventory System (6-8 hours)
   - Implement IsoContainer
   - Build inventory UI
   - Item drop/pickup mechanics
5. Complete Pathfinding Threading (8-10 hours)
   - Implement A* algorithm
   - Integrate into NPC AI
   - Performance tuning

---

## Compilation & Testing

### Build Command
```bash
cd /workspaces/PZ/PZ-Switch
mkdir -p build
cd build
cmake ..
make -j4
```

### Run Tests
```bash
./ProjectZomboidCpp
# or for Switch build:
cd ../build-switch && make -j4
```

### Expected Outputs
- ✅ No compiler errors
- ✅ No linker errors
- ✅ All systems initialized
- ✅ Game window opens
- ✅ Game runs without crashes

---

## Next Steps

1. **Compile the framework** - Verify headers and stubs build without errors
2. **Choose first enhancement** - Audio is quickest, impacts player experience immediately
3. **Implement integration points** - Focus on one enhancement at a time
4. **Test thoroughly** - Each enhancement should be fully tested before moving to next
5. **Optimize performance** - Profile and tune after all systems are working

---

## File Structure

```
include/
  ├── AudioInteractionSystem.h ✅
  ├── VisibilitySystem.h ✅
  ├── InventoryManager.h ✅
  └── PathfindingThreadPool.h ✅

src/
  ├── AudioInteractionSystem.cpp ✅
  ├── VisibilitySystem.cpp ✅
  ├── InventoryManager.cpp ✅
  └── PathfindingThreadPool.cpp ✅

CMakeLists.txt ✅ (Updated to include new files)
```

---

## References

### Related Systems
- [ENHANCEMENTS_STATUS.md](ENHANCEMENTS_STATUS.md) - Current enhancement tracking
- [FUTURE_ENHANCEMENTS_ROADMAP.md](FUTURE_ENHANCEMENTS_ROADMAP.md) - Full roadmap
- [RENDERING_SYSTEMS.md](RENDERING_SYSTEMS.md) - Rendering integration points
- [WORLD_SYSTEM.md](WORLD_SYSTEM.md) - World system architecture

### External Resources
- **A* Algorithm**: https://en.wikipedia.org/wiki/A*_search_algorithm
- **Bresenham Line**: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
- **Fog of War Techniques**: Game Programming Gems series
- **Multi-threading Audio**: SDL2_mixer documentation

---

## Estimated Timeline

| Phase | Enhancement | Duration | Priority |
|-------|-------------|----------|----------|
| 1 | Audio on Interactions | 2-3h | High |
| 1 | Visibility/FOW | 4-6h | High |
| 2 | Inventory System | 6-8h | Medium |
| 2 | Pathfinding Threading | 8-10h | Medium |

**Total: 20-27 hours**
