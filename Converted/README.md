# Project Zomboid C++ Port

This is a C++ conversion of Project Zomboid's core game engine, targeting the Nintendo Switch and other platforms.

## Project Status

**Phase:** Prototype / Proof of Concept  
**Completion:** Core game loop implemented (~5% of full game)

### Implemented:
- ✅ SDL2-based game window and rendering
- ✅ Game state machine (menu → gameplay transitions)
- ✅ Core frame management
- ✅ FPS tracking and time management
- ✅ Day/night cycle simulation
- ✅ Game time system
- ✅ **Texture loading from media/ directory**
- ✅ **Asset manager with caching**
- ✅ **Real PNG/JPG image loading**
- ✅ **Sprite rendering system**
- ✅ **Sprite transformations (position, rotation, scale)**
- ✅ **Color modulation and alpha blending**
- ✅ **SpriteBatch for efficient rendering**
- ✅ **Primitive rendering (rectangles, lines)**
- ✅ **Sprite animation system (frame-based)**
- ✅ **Animation loader for PZ texture pack format**
- ✅ **BitmapFont system (AngelCode BMFont .fnt)**
- ✅ **Tile rendering system**
- ✅ **Tile map with layers**
- ✅ **Lot file parser (.lot format)**
- ✅ **Entity system (base class, manager)**
- ✅ **Player entity with movement**
- ✅ **Zombie entity with AI**
- ✅ **Collision detection (AABB, spatial grid)**
- ✅ **Input system (keyboard, mouse, gamepad)**
- ✅ **Sound system (SDL_mixer, music, SFX)**

### Not Yet Implemented:
- ❌ Font texture loading (textures not in media)
- ❌ World rendering (advanced lighting)
- ❌ Physics (momentum, friction)
- ❌ UI framework (menus, inventory screens)
- ❌ Advanced AI pathfinding
- ❌ Inventory system
- ❌ Save/load system
- ❌ Networking
- ❌ Lua scripting integration

## Building

### Prerequisites
- CMake 3.10+
- SDL2 development libraries
- SDL2_image (PNG/JPG support)
- SDL2_mixer (audio support)
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)

### Linux/macOS
```bash
# Install SDL2
# Ubuntu/Debian:
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev

# macOS (Homebrew):
brew install sdl2 sdl2_image sdl2_mixer

# Build
mkdir build && cd build
cmake ..
make
./ProjectZomboidCpp
```

### Windows (Visual Studio)
```batch
# Install SDL2 (download from libsdl.org or use vcpkg)
vcpkg install sdl2:x64-windows

# Build
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

### Nintendo Switch (devkitPro)
```bash
# Install devkitPro and switch-sdl2
# https://devkitpro.org/wiki/Getting_Started

# Quick build
./build-switch.sh

# Output: build-switch/ProjectZomboidCpp.nro 
# Copy to Switch SD card: /switch/ProjectZomboidCpp.nro
```

**See [SWITCH_BUILD.md](SWITCH_BUILD.md) for detailed Switch build instructions.**

## Command Line Options

```bash
./ProjectZomboidCpp [options]

Options:
  -width <num>      Window width (default: 1280)
  -height <num>     Window height (default: 720)
  -fullscreen       Run in fullscreen mode
  -debug            Enable debug output
```

## What You'll See

**Main Menu (3 seconds):**
- Blue gradient background
- Character artwork from `media/ui/LoneMan.png` with rotation animation
- Smooth sprite rendering with transformations

**Gameplay:**
- Sky color changes with time of day (day/night cycle)
- **Tile-based world rendering with checkerboard pattern**
- **Camera controls (arrow keys) to pan the view**
- Mouse cursor sprite from `media/ui/mouse.png` follows mouse position
- Yellow time bar showing current hour (0-24)
- Feature indicators (colored boxes)
- Press **ESC** to exit

## Architecture

### Core Classes

```
GameWindow           - Main loop, timing, FPS management
├─ Core              - SDL2 initialization, rendering context
│  ├─ drawSprite()   - Render sprites with transformations
│  ├─ drawTexture()  - Direct texture rendering
│  └─ drawRect/Line  - Primitive shape rendering
├─ Sprite            - 2D sprite with position, rotation, scale, color
├─ AnimatedSprite    - Sprite with animation support
├─ SpriteAnimation   - Frame-based animation system
├─ AnimationLoader   - Load PZ texture pack format
├─ SpriteBatch       - Batch rendering for performance optimization
├─ BitmapFont        - AngelCode BMFont (.fnt) renderer
├─ TileMap           - Grid-based tile world (multi-layer)
├─ TileRegistry      - Tile definition management
├─ LotLoader         - Parse .lot files
├─ Entity            - Base class for all game entities
├─ EntityManager     - Entity lifecycle management
├─ Player            - Player entity with movement
├─ Zombie            - Zombie AI entity
├─ CollisionSystem   - AABB collision detection with spatial grid
├─ InputManager      - Centralized input handling (keyboard, mouse, gamepad)
├─ SoundManager      - Audio playback (SDL_mixer)
├─ TextureManager    - Asset loading and caching
├─ GameStateMachine  - State management (menu, gameplay, etc.)
│  ├─ GameState      - Base class for states
│  ├─ MainMenuState  - Main menu (demo)
│  └─ IngameState    - Gameplay state (demo)
└─ GameTime          - Time of day, day/night cycle, game speed
```

### Memory Management Strategy

- **Smart Pointers:** `std::unique_ptr` for ownership, `std::shared_ptr` when needed
- **Object Pools:** Planned for entities (zombies, items)
- **Stack Allocation:** Temporary vectors, matrices
- **Pre-allocation:** Containers with known max sizes

## Original Java Code

The original Project Zomboid Java source is in `/src/zombie/`

Key conversions:
- `GameWindow.java` → `GameWindow.cpp`
- `Core.java` → `Core.cpp`
- `GameStateMachine.java` → `GameStateMachine.cpp`
- `GameTime.java` → `GameTime.cpp`

## Performance Targets

### Desktop
- 60 FPS @ 1920x1080

### Nintendo Switch
- 60 FPS docked (1920x1080)
- 30-60 FPS handheld (1280x720)

## Documentation

See [DEPENDENCY_MAP.md](DEPENDENCY_MAP.md) for:
- Complete dependency analysis
- Conversion strategy
- Risk assessment
- Platform-specific considerations

## License

This is a conversion for educational/porting purposes. Original Project Zomboid is © The Indie Stone.

## Development Status

This is an **early prototype** demonstrating the core game loop architecture. It successfully:
1. Creates a window using SDL2
2. Manages state transitions
3. Tracks FPS and adjusts game speed
4. Simulates day/night cycle
5. **Renders sprites with full transformation support**
6. **Implements efficient batch rendering**
7. **Displays animated menu and gameplay graphics**
8. **Supports frame-based sprite animations**
9. **Renders tile-based worlds with camera system**
10. **Parses .lot and .fnt file formats**

**Next steps:** Integrate new systems into game states, implement interactive gameplay with player movement and zombie interactions, add sound effects and music.

## Controls (Current Demo)

- **ESC** - Quit application
- **Window Close** - Exit

The demo auto-transitions from the main menu to the gameplay state after 3 seconds.

## Contact / Contribution

This is a proof-of-concept conversion. For the official Project Zomboid game, visit:
https://projectzomboid.com/

---
**Last Updated:** January 2026
