# Java Library Conversion Guide

## Overview

The original Project Zomboid uses several Java libraries (JAR files). For the C++ port, we don't need to "convert" these JARs - instead, we use their **C++ equivalents** or implement similar functionality.

---

## Library Mapping: Java → C++

### 1. **lwjgl.jar** (LWJGL - Lightweight Java Game Library)
**Java Usage:** OpenGL bindings, window management, input handling  
**C++ Replacement:** ✅ **SDL2**

```cpp
// Java (LWJGL)
Display.create();
Display.update();
GL11.glClear(GL11.GL_COLOR_BUFFER_BIT);

// C++ (SDL2)
SDL_CreateWindow(...);
SDL_RenderPresent(renderer);
SDL_RenderClear(renderer);
```

**Status:** ✅ Implemented in Core.cpp

---

### 2. **lwjgl_util.jar** (LWJGL Utilities)
**Java Usage:** GLU functions, vector math, display utilities  
**C++ Replacement:** ✅ **GLM** (OpenGL Mathematics) or custom Vector2/Vector3 classes

```cpp
// Java (LWJGL)
org.lwjgl.util.vector.Vector2f pos = new Vector2f(x, y);

// C++ (Custom or GLM)
struct Vector2 { float x, y; };
glm::vec2 pos(x, y);
```

**Status:** ⚠️ Basic Vector2 exists in original code, can be ported as needed

---

### 3. **com.jar** (JOrbis - Ogg Vorbis decoder)
**Java Usage:** Audio decoding (OGG/Vorbis files)  
**C++ Replacement:** ✅ **SDL_mixer** or **stb_vorbis**

```cpp
// Java
JOrbis decoder = new JOrbis();
decoder.decode(oggFile);

// C++ (SDL_mixer)
Mix_Music* music = Mix_LoadMUS("file.ogg");
Mix_PlayMusic(music, -1);

// Or (stb_vorbis - header-only)
#include "stb_vorbis.c"
int samples = stb_vorbis_decode_filename("file.ogg", &channels, &rate, &output);
```

**Status:** ⚠️ Not yet implemented (audio system pending)

---

### 4. **gnu.jar** (GNU Trove - High-performance collections)
**Java Usage:** Optimized HashMap, ArrayList, primitive collections  
**C++ Replacement:** ✅ **C++ STL** (already faster, no boxing)

```cpp
// Java (Trove)
THashMap<String, Integer> map = new THashMap<>();
TIntArrayList numbers = new TIntArrayList();

// C++ (STL)
std::unordered_map<std::string, int> map;
std::vector<int> numbers;
```

**Status:** ✅ Using STL throughout codebase

---

### 5. **org.jar** (Kahlua/LuaJ - Lua interpreter)
**Java Usage:** Lua scripting integration  
**C++ Replacement:** ✅ **sol2**, **LuaBridge**, or **plain Lua C API**

```cpp
// Java (Kahlua)
KahluaTable globals = platform.newEnvironment();
LuaClosure func = luaState.loadstring("return 5 + 5");

// C++ (sol2 - modern, recommended)
#include <sol/sol.hpp>
sol::state lua;
lua.script("return 5 + 5");

// Or (Lua C API)
lua_State* L = luaL_newstate();
luaL_dostring(L, "return 5 + 5");
```

**Status:** ⚠️ Not yet implemented (Lua integration pending)

**Recommended:** sol2 (header-only, type-safe, modern C++)

---

### 6. **se.jar** (Kahlua extensions)
**Java Usage:** Additional Lua converter utilities  
**C++ Replacement:** ✅ Part of sol2 or custom converters

**Status:** ⚠️ Handled by sol2 when Lua is integrated

---

### 7. **zombie.jar** (Game-specific utilities)
**Java Usage:** Custom debug, Lua helpers specific to Project Zomboid  
**C++ Replacement:** ✅ **Custom implementation** (we convert these classes)

This contains:
- `LineDrawer` - Debug line rendering → Convert to C++ (simple)
- Custom Lua converters → Part of Lua integration

**Status:** ⚠️ Will be converted as needed (minimal code)

---

## Asset Loading

### Media Directory Structure

The `media/` folder contains all game assets:
- `ui/` - UI textures (PNG)
- `texturepacks/` - Character/zombie sprites
- `inventory/` - Item icons
- `lua/` - Lua scripts
- `scripts/` - Game data (items, recipes)
- `shaders/` - GLSL shaders
- `sound/` - Audio files

### C++ Asset Loading

✅ **Implemented:** TextureManager.cpp

```cpp
// Initialize
TextureManager::getInstance()->init(renderer);
TextureManager::getInstance()->setMediaPath("media/");

// Load texture
SDL_Texture* tex = TextureManager::getInstance()->loadTexture("ui/mouse.png");

// Render
SDL_RenderCopy(renderer, tex, nullptr, &destRect);
```

**Features:**
- Automatic caching
- PNG/JPG/BMP support via SDL2_image
- Relative path resolution
- Texture reuse

---

## Installation Status

### ✅ Currently Installed
- SDL2 2.30.0 (graphics, input, window)
- SDL2_image 2.8.2 (PNG/JPG loading)
- C++ STL (collections)

### ⚠️ To Be Added (when needed)
- SDL_mixer (audio)
- sol2 (Lua scripting)
- GLM (advanced vector math)
- stb_image/stb_vorbis (alternative loaders)

---

## Build System Integration

### CMakeLists.txt Configuration

```cmake
# SDL2 (graphics)
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# SDL2_image (texture loading)
find_package(PkgConfig)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})

# Future: SDL_mixer (audio)
# pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

# Future: Lua (scripting)
# find_package(Lua REQUIRED)
```

### Nintendo Switch

For Switch builds, equivalent libraries are available via **devkitPro pacman**:

```bash
sudo dkp-pacman -S switch-sdl2        # ✅ Installed
sudo dkp-pacman -S switch-sdl2_image  # ✅ Installed
sudo dkp-pacman -S switch-sdl2_mixer  # ⚠️ For future audio
sudo dkp-pacman -S switch-lua         # ⚠️ For future scripting
```

---

## Implementation Priority

### Phase 1: Core (✅ Complete)
- SDL2 window/rendering
- SDL2_image texture loading
- STL collections
- Asset manager

### Phase 2: Audio (Next)
- SDL_mixer integration
- OGG/WAV playback
- 3D positional audio (later)

### Phase 3: Scripting (Later)
- sol2 Lua integration
- Load game scripts from media/lua/
- Expose C++ game systems to Lua

### Phase 4: Advanced (Future)
- Custom shaders (GLSL)
- Advanced pathfinding
- Network code (multiplayer)

---

## Why We Don't "Convert" JARs

JARs are **compiled Java bytecode**. We can't "convert" them directly because:

1. **Different paradigms:** Java (GC, objects) vs C++ (manual memory, templates)
2. **Libraries already have C++ versions:** LWJGL → SDL2, Trove → STL
3. **Better performance:** Native C++ implementations are faster
4. **Platform compatibility:** C++ libs work on Switch, Java doesn't

---

## Current Build Sizes

| Platform | Executable | With SDL2_image | Assets (symlink) |
|----------|------------|-----------------|------------------|
| Linux    | 120 KB     | +50 KB          | 0 (symlinked)    |
| Switch   | 7.6 MB     | (included)      | +TBD (romfs)     |

---

## Asset Integration Status

✅ **Working:**
- Texture loading from media/
- PNG/JPG support
- Automatic caching
- Media directory symlink (desktop)

⚠️ **TODO:**
- Sprite animation system
- Font rendering (.fnt files)
- Lua script execution
- Audio playback
- Shader loading

---

## Testing Asset Loading

The current build demonstrates:

```cpp
// Main menu shows a logo
SDL_Texture* logo = texMgr->getTexture("ui/LoneMan.png");

// Ingame shows mouse cursor
SDL_Texture* mouse = texMgr->getTexture("ui/mouse.png");

// Time indicator uses white.png
SDL_Texture* white = texMgr->getTexture("white.png");
```

Run: `./build/ProjectZomboidCpp`

You should see:
- Main menu with character art
- Gameplay with mouse cursor following pointer
- Yellow time bar showing time of day progression

---

## Summary

| Java Library | C++ Equivalent | Status |
|--------------|----------------|--------|
| lwjgl.jar | SDL2 | ✅ Implemented |
| lwjgl_util.jar | GLM / Custom | ⚠️ As needed |
| com.jar (JOrbis) | SDL_mixer | ⚠️ Pending |
| gnu.jar (Trove) | C++ STL | ✅ Using |
| org.jar (Kahlua) | sol2 | ⚠️ Pending |
| se.jar | sol2 | ⚠️ Pending |
| zombie.jar | Custom C++ | ⚠️ As needed |

**Current Progress:**
- Graphics: ✅ Working with real assets
- Audio: ⚠️ Not yet implemented
- Scripting: ⚠️ Not yet implemented
- Assets: ✅ Loading textures from media/

**Next Steps:**
1. Implement sprite animation system
2. Add SDL_mixer for audio
3. Integrate sol2 for Lua scripting
4. Port more game-specific classes

---

**Last Updated:** January 16, 2026  
**Build Status:** ✅ Desktop + Switch with texture loading
