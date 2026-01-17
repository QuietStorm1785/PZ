# Project Zomboid - C++ Conversion Dependency Map

## Executive Summary
This document maps the core dependencies and architecture of Project Zomboid for conversion from Java to C++ for Nintendo Switch.

**Codebase Size:** 563 Java files, ~105,000 lines of code  
**Target Platform:** Nintendo Switch (ARM architecture)  
**Graphics API:** SDL2 (instead of LWJGL/OpenGL)

---

## Core Architecture Overview

### Main Entry Point & Game Loop
**Entry:** `GameWindow.java::main()` → `run()`

```
main() 
  ├─ LuaManager.init()
  ├─ ZomboidGlobals.Load()
  ├─ SoundStore.init()
  ├─ Display.create()
  ├─ Core.init()
  └─ run() [MAIN GAME LOOP]
       └─ while (!Display.isCloseRequested())
            ├─ Display.update()          // Process events
            ├─ logic()                    // Update game state
            ├─ updateFPS()                // FPS calculation
            ├─ render()                   // Draw frame
            └─ Display.sync(60)           // 60 FPS cap
```

---

## Tier 1: Core Engine Classes (Must Convert First)

### 1. **Core** (`zombie.core.Core`)
**Dependencies:** OpenGL, Display
**Responsibility:** Graphics initialization, frame management, screen management
**Key Methods:**
- `init(width, height)` - Initialize graphics
- `StartFrame()` - Begin frame rendering
- `EndFrame()` - End frame rendering  
- `StartFrameUI()` - Begin UI rendering
- `EndFrameUI()` - End UI rendering
**Conversion Priority:** ⭐⭐⭐⭐⭐ CRITICAL
**C++ Notes:** Replace LWJGL with SDL2, implement OpenGL context management

### 2. **GameWindow** (`zombie.GameWindow`)
**Dependencies:** Core, Display, GameStateMachine, Input
**Responsibility:** Main loop, timing, event handling
**Key Methods:**
- `main()` - Entry point
- `run()` - Main game loop
- `logic()` - Update game state machine
- `render()` - Render current state
- `updateFPS()` - FPS tracking and multiplier calculation
**Conversion Priority:** ⭐⭐⭐⭐⭐ CRITICAL
**C++ Notes:** SDL2 event loop, timing with SDL_GetTicks()

### 3. **GameStateMachine** (`zombie.gameStates.GameStateMachine`)
**Dependencies:** GameState (base class)
**Responsibility:** State management (menu, gameplay, loading)
**Key States:**
- LoginState
- MainScreenState  
- LoadGamePopupState
- GameLoadingState
- IngameState (most complex)
**Conversion Priority:** ⭐⭐⭐⭐⭐ CRITICAL
**C++ Notes:** Simple state pattern, easy to convert

### 4. **GameState** (`zombie.gameStates.GameState`)
**Dependencies:** None (base class)
**Responsibility:** Base class for all game states
**Key Methods:**
- `enter()` - Called when state begins
- `exit()` - Called when state ends
- `update()` - Frame update logic
- `render()` - Frame rendering
**Conversion Priority:** ⭐⭐⭐⭐⭐ CRITICAL
**C++ Notes:** Pure virtual base class

### 5. **GameTime** (`zombie.GameTime`)
**Dependencies:** None (standalone)
**Responsibility:** Time of day, game speed, day/night cycle
**Key Fields:**
- `TimeOfDay` - Current hour (0-24)
- `Day` - Current day
- `Month` - Current month
- `FPSMultiplier` - Speed correction for framerate
**Conversion Priority:** ⭐⭐⭐⭐ HIGH
**C++ Notes:** Simple data class with update logic

---

## Tier 2: Rendering & Graphics

### 6. **SpriteRenderer** (`zombie.core.SpriteRenderer`)
**Dependencies:** Core, OpenGL, Texture
**Responsibility:** 2D sprite batch rendering
**Conversion Priority:** ⭐⭐⭐⭐ HIGH
**C++ Notes:** SDL2_image for loading, SDL_Renderer for 2D or OpenGL quads

### 7. **Texture** / **TextureID** (`zombie.core.textures.*`)
**Dependencies:** OpenGL, file I/O
**Responsibility:** Texture loading, caching, binding
**Conversion Priority:** ⭐⭐⭐⭐ HIGH
**C++ Notes:** SDL_Texture or OpenGL textures with stb_image

### 8. **IsoSprite** (`zombie.iso.sprite.IsoSprite`)
**Dependencies:** Texture, animations
**Responsibility:** Animated sprite definitions
**Conversion Priority:** ⭐⭐⭐ MEDIUM
**C++ Notes:** Frame animation system

---

## Tier 3: Game World & Simulation

### 9. **IsoWorld** (`zombie.iso.IsoWorld`)
**Dependencies:** IsoCell, saves, chunks
**Responsibility:** World container, cell management
**Conversion Priority:** ⭐⭐⭐ MEDIUM

### 10. **IsoCell** (`zombie.iso.IsoCell`)
**Dependencies:** IsoGridSquare, objects, zombies
**Responsibility:** Loaded area of the world (chunk system)
**Conversion Priority:** ⭐⭐⭐ MEDIUM

### 11. **IsoGridSquare** (`zombie.iso.IsoGridSquare`)
**Dependencies:** IsoObject, pathfinding
**Responsibility:** Single tile in the world
**Conversion Priority:** ⭐⭐⭐ MEDIUM

---

## Tier 4: Entities & Characters

### 12. **IsoGameCharacter** (base class)
**Dependencies:** IsoMovingObject, stats, inventory
**Responsibility:** Base class for player/zombies/NPCs
**Conversion Priority:** ⭐⭐⭐ MEDIUM

### 13. **IsoPlayer** (`zombie.characters.IsoPlayer`)
**Dependencies:** IsoGameCharacter, input, UI
**Responsibility:** Player character
**Conversion Priority:** ⭐⭐⭐ MEDIUM

### 14. **IsoZombie** (`zombie.characters.IsoZombie`)
**Dependencies:** IsoGameCharacter, AI
**Responsibility:** Zombie entity
**Conversion Priority:** ⭐⭐ LOW (can simplify for prototype)

---

## Tier 5: UI System

### 15. **UIManager** (`zombie.ui.UIManager`)
**Dependencies:** UIElement, Core
**Responsibility:** UI rendering, event dispatching
**Conversion Priority:** ⭐⭐⭐ MEDIUM

### 16. **UIElement** (base)
**Dependencies:** Input, rendering
**Responsibility:** Base UI widget class
**Conversion Priority:** ⭐⭐⭐ MEDIUM

---

## Tier 6: Input & Sound

### 17. **Input** (`zombie.core.input.Input`)
**Dependencies:** Keyboard, Mouse, Controllers (LWJGL)
**Responsibility:** Input abstraction
**Conversion Priority:** ⭐⭐⭐⭐ HIGH
**C++ Notes:** SDL2 input events (SDL_Event)

### 18. **SoundManager** (`zombie.SoundManager`)
**Dependencies:** OpenAL (LWJGL)
**Responsibility:** 3D positional audio
**Conversion Priority:** ⭐⭐ LOW (use SDL_mixer initially)

---

## Tier 7: Scripting & Data

### 19. **LuaManager** (`zombie.Lua.LuaManager`)
**Dependencies:** LuaJava bindings
**Responsibility:** Lua scripting integration
**Conversion Priority:** ⭐⭐ LOW (use LuaBridge or sol2 in C++)

### 20. **ScriptManager** (`zombie.scripting.ScriptManager`)
**Dependencies:** Script objects, items, recipes
**Responsibility:** Game data script loading
**Conversion Priority:** ⭐⭐ LOW (data files remain same format)

---

## Critical Third-Party Dependencies

| Java Library | C++ Replacement | Notes |
|--------------|-----------------|-------|
| LWJGL (OpenGL) | SDL2 + OpenGL | Graphics, windowing, input |
| LWJGL (OpenAL) | SDL_mixer | Audio |
| LuaJava | sol2 / LuaBridge | Lua scripting |
| Java Collections | STL (vector, map, unordered_map) | Data structures |
| GNU Trove | Custom/STL | High-perf collections |
| Java I/O | C++ fstream/SDL_RWops | File I/O |
| Java Networking | SDL_net or ASIO | Multiplayer (if needed) |

---

## Memory Management Hotspots

### High-Frequency Allocations (Need Object Pools):
1. **Zombies** - 750+ active entities  
2. **IsoObject** - Thousands of world objects
3. **UIElement** - UI widgets during gameplay
4. **Vector2/Vector3** - Temporary math vectors (use stack allocation)
5. **Texture Bindings** - Texture switches per frame

### Strategies:
- **Object Pools** for entities (zombies, items, particles)
- **Stack Allocation** for temporary vectors/matrices
- **Smart Pointers** (unique_ptr, shared_ptr) for ownership
- **Arena Allocators** for per-frame temporary allocations
- **Pre-allocation** for collections with known max sizes

---

## Conversion Phases (Recommended Order)

### Phase 1: Core Engine (Week 1-2)
✅ GameWindow → SDL2 main loop  
✅ Core → SDL2/OpenGL setup  
✅ GameStateMachine → State pattern  
✅ Input → SDL2 events  
✅ GameTime → Time management

### Phase 2: Basic Rendering (Week 3-4)
- Texture loading (SDL_image)
- Sprite rendering (SDL_Renderer or OpenGL quads)
- Basic 2D camera
- UI rendering foundation

### Phase 3: World Simulation (Week 5-8)
- IsoWorld/IsoCell structure
- IsoGridSquare tiles
- Basic pathfinding
- World loading/saving

### Phase 4: Entities (Week 9-12)
- IsoGameCharacter base
- IsoPlayer implementation
- IsoZombie (simplified AI)
- Inventory system

### Phase 5: Polish & Optimization (Week 13+)
- Memory optimization
- Object pooling
- Switch-specific optimizations
- Performance profiling

---

## Platform-Specific Switch Considerations

### Memory Constraints
- **Total RAM:** 4GB (3.25GB available to games)
- **Target:** Keep under 2GB for safety
- **Java GC overhead removed** = ~20-30% memory savings
- **Texture compression** = DXT/ASTC formats
- **Asset streaming** = Load/unload chunks dynamically

### Performance Targets
- **60 FPS docked** (1920x1080)
- **30-60 FPS handheld** (1280x720)
- **CPU:** 4x ARM Cortex-A57 @ 1.02 GHz
- **GPU:** NVIDIA Tegra X1 (256 CUDA cores)

### Switch-Specific APIs (If Official SDK)
- **NVN** graphics API (more efficient than OpenGL)
- **nn::hid** for Joy-Con input
- **nn::audio** for audio output
- **nn::fs** for save data

---

## Risk Assessment

| Risk | Severity | Mitigation |
|------|----------|------------|
| Decompiled code quality | HIGH | Manual cleanup, testing |
| Memory management complexity | HIGH | Object pools, smart pointers |
| Lua binding differences | MEDIUM | Use mature C++ Lua library |
| Performance on Switch | MEDIUM | Profiling, optimization passes |
| Multiplayer networking | MEDIUM | Start with single-player |
| Asset pipeline | LOW | Keep existing formats |

---

## Estimated Effort

**Full Conversion:** 12-18 months (3-5 person team)  
**Minimal Playable Prototype:** 2-3 months (1-2 person team)  
**Core Engine Only:** 1 month (1 person, no gameplay)

---

## Next Steps for Prototype

1. ✅ Convert GameWindow + Core + GameStateMachine
2. ✅ Create basic "Hello World" SDL2 window
3. ✅ Implement state switching
4. Texture loading and basic sprite rendering
5. Create minimal test world (single screen)
6. Add player movement (no collision)
7. Benchmark performance

**End of Dependency Map**
