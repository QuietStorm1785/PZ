# World System Quick Reference

## File Locations

```
Headers:        /workspaces/PZ/PZ-Switch/include/
Sources:        /workspaces/PZ/PZ-Switch/src/
Data:           /workspaces/PZ/media/lots/
Binary:         /workspaces/PZ/PZ-Switch/build/ProjectZomboidCpp
```

## Core Classes

| Class | Purpose | Location |
|-------|---------|----------|
| IsoGridSquare | Single tile (stores objects/chars) | IsoGridSquare.h/cpp |
| IsoChunk | 32×32 tile region | IsoChunk.h/cpp |
| IsoCell | World manager (chunks, entities) | IsoCell.h/cpp |
| IsoPlayer | Player character | IsoPlayer.h/cpp |
| IsoZombie | Zombie AI | IsoZombie.h/cpp |
| IsoObject | World object base class | IsoObject.h/cpp |
| IsoTree | Tree (non-solid) | WorldContent.h/cpp |
| IsoFurniture | Furniture (solid) | WorldContent.h/cpp |
| IsoContainer | Container (solid) | WorldContent.h/cpp |
| AStarPathfinder | Pathfinding with caching | Pathfinding.h/cpp |
| WorldLoader | .lot file parser | WorldLoader.h/cpp |

## Common Operations

### Create World
```cpp
auto world = std::make_unique<IsoCell>(300, 300);
```

### Add Player
```cpp
auto player = std::make_shared<IsoPlayer>();
world->addCharacter(player);  // auto-binds
```

### Add Zombie
```cpp
auto zombie = std::make_shared<IsoZombie>();
zombie->setWorld(world.get());  // init pathfinder
world->addZombie(zombie);
```

### Load Content
```cpp
WorldLoader::loadLotFile("media/lots/world.lot", world.get());
```

### Get Grid Square
```cpp
IsoGridSquare* sq = world->getGridSquare(x, y, z);
```

### Check Collision
```cpp
bool blocked = !sq->isFree(true);  // include chars
```

### Interact with Objects
```cpp
player->interact();  // calls onInteract() on all objects on square
```

## .lot File Format

```
# Comment (ignored)
TYPE X Y Z SOLID

# Example
Tree 10 10 0 0
Furniture 20 20 0 1
Container 30 30 0 1
```

**Types:** tree, furniture, container, crate, locker
**Coordinates:** World grid positions
**Z:** Height level (usually 0)
**Solid:** 0 = non-blocking, 1 = solid

## Control Keys

| Key | Action |
|-----|--------|
| WASD | Move |
| Shift | Sprint |
| E | Interact with objects on square |
| Space | Attack nearby zombies |
| Arrow Keys | Pan camera |
| ESC | Quit |

## Performance Targets

- Movement collision: <1 μs per frame
- Pathfinding (cached): ~100 μs per zombie
- Grid square update: <1 μs
- 8 zombies: ~1 ms total

## Debugging Tips

**Objects not loading?**
```cpp
// Check console output in GameWindow::enter()
WorldLoader::loadLotFile(...);  // logs placement count
```

**Player stuck?**
```cpp
// Add debug to canMoveTo()
// Print sq->isFree() and sq->isBlocked()
```

**Zombies not moving?**
```cpp
// Verify setWorld() called
// Check pathfinder has neighbor provider
```

**Paths not caching?**
```cpp
// Check generation bumps on walkability change
// Verify cache size > 0
```

## Memory Usage

| Item | Size |
|------|------|
| IsoGridSquare | ~40 bytes |
| IsoChunk (32×32) | ~200 KB |
| IsoObject | ~30 bytes |
| Path cache entry | ~200 bytes |
| 4×4 chunks | ~3.2 MB |

## Build

```bash
cd /workspaces/PZ/PZ-Switch/build
cmake ..
make -j4
./ProjectZomboidCpp
```

## Quick Test

1. Run executable
2. Player spawns at (64, 64)
3. Trees visible at (40, 40), (42, 40), (44, 41)
4. Walk to tree, press E
5. See: "You rustle the tree leaves."

---

**More help:** See WORLD_SYSTEM_BUILD_GUIDE.md
