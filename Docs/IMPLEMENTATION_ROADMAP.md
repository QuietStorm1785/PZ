# Project Zomboid C++ Implementation Roadmap

## Phase 1: Core Infrastructure (STARTING NOW)
**Goal:** Get basic game loop running with SDL2 on Switch

### 1.1 Core Game Loop ✓ (Already working in /Converted)
- [x] GameWindow - Main loop, timing
- [x] GameTime - Time management
- [x] Core - SDL2 initialization
- [x] GameStateMachine - State management

### 1.2 Graphics System (Priority: HIGH)
- [ ] Merge /converted2 sprite classes with /Converted
- [ ] Implement IsoSprite for isometric rendering
- [ ] Port texture management
- [ ] Implement camera system
- [ ] Basic tile rendering

### 1.3 Input System ✓ (Already working)
- [x] InputManager - SDL2 gamepad support
- [ ] Port IsoPlayer input handling
- [ ] Add Switch-specific controls

### 1.4 Audio System ✓ (Already working)
- [x] SoundManager - SDL_mixer integration
- [ ] Port WorldSoundManager
- [ ] Add music system

## Phase 2: Entity System (NEXT)
**Goal:** Get player and zombies moving

### 2.1 Character System
- [ ] Port IsoGameCharacter (base class)
- [ ] Implement IsoPlayer
- [ ] Implement IsoZombie
- [ ] Character stats and moodles

### 2.2 World System
- [ ] IsoCell - World grid
- [ ] IsoGridSquare - Individual tiles
- [ ] IsoChunk - World chunks
- [ ] Basic collision

### 2.3 AI & Pathfinding
- [ ] A* pathfinding
- [ ] Zombie AI states
- [ ] Behavior system

## Phase 3: Game Systems
**Goal:** Playable game with items and interaction

### 3.1 Inventory System
- [ ] InventoryItem base
- [ ] ItemContainer
- [ ] Item types (food, weapons)
- [ ] Crafting recipes

### 3.2 Building & Objects
- [ ] IsoObject base
- [ ] Doors, windows
- [ ] Containers
- [ ] Barricading

### 3.3 Combat System
- [ ] Weapon handling
- [ ] Damage system
- [ ] Body damage
- [ ] Death states

## Phase 4: Lua Integration
**Goal:** Mod support working

### 4.1 Lua Engine
- [ ] LuaJIT for Switch
- [ ] LuaManager implementation
- [ ] Script loading
- [ ] Event system

### 4.2 Script Bindings
- [ ] Expose core classes to Lua
- [ ] Item definitions
- [ ] Recipe system
- [ ] Mod loader

## Phase 5: UI System
**Goal:** Functional game interface

### 5.1 Core UI
- [ ] UIElement base
- [ ] UIManager
- [ ] Text rendering (BitmapFont)
- [ ] Basic HUD

### 5.2 Game UI
- [ ] Inventory screen
- [ ] Health panel
- [ ] Context menus
- [ ] Radial menu

## Phase 6: Advanced Features
- [ ] Save/Load system
- [ ] Weather effects
- [ ] Day/night cycle
- [ ] Building interiors
- [ ] Multiplayer (future)

## Implementation Strategy

### Week 1-2: Core Integration
1. Merge /Converted and /converted2
2. Implement IsoSprite and sprite rendering
3. Port IsoPlayer basics
4. Get player moving on screen

### Week 3-4: World & Entities
1. Implement IsoCell and grid system
2. Basic tile rendering
3. Zombie spawning and AI
4. Collision detection

### Week 5-6: Items & Interaction
1. Inventory system
2. Item pickup/drop
3. Basic crafting
4. Doors and containers

### Week 7-8: Lua & Polish
1. Lua integration
2. Script loading
3. UI improvements
4. Performance optimization

## Technical Decisions

### Graphics
- **Engine:** SDL2 (native Switch support)
- **Rendering:** OpenGL ES 2.0 (Switch compatible)
- **Sprites:** Texture atlases for performance
- **Camera:** Isometric projection

### Input
- **Library:** SDL2 GameController API
- **Switch Mapping:** Joy-Con and Pro Controller
- **Touch:** SDL2 touch events (handheld mode)

### Audio
- **Engine:** SDL_mixer (Switch compatible)
- **Music:** OGG Vorbis
- **SFX:** WAV files
- **3D Sound:** Custom attenuation

### Scripting
- **Engine:** LuaJIT (ARM support)
- **Version:** Lua 5.1 (PZ compatibility)
- **Bindings:** Manual C++ bindings
- **Loading:** From romfs on Switch

### Build System
- **Tool:** CMake
- **Cross-compile:** devkitPro toolchain
- **Dependencies:** Portlibs (Switch packages)

## Current Status

**Phase 1:** 40% complete
- Core loop: ✓ Working
- Graphics: ✓ Basic sprites
- Input: ✓ Working
- Audio: ✓ Working
- Entities: ✓ Basic system

**Next Immediate Steps:**
1. Port IsoPlayer from converted2
2. Implement IsoCell/GridSquare
3. Merge sprite systems
4. Get isometric rendering working

## Files to Start With

### Priority 1 (This Week)
1. `/converted2/include/IsoPlayer.h` → Implement player movement
2. `/converted2/include/IsoCell.h` → World management
3. `/converted2/include/IsoGridSquare.h` → Tile system
4. `/converted2/include/IsoSprite.h` → Isometric sprites
5. `/converted2/include/IsoGameCharacter.h` → Character base

### Priority 2 (Next Week)
6. `/converted2/include/IsoZombie.h` → Enemy AI
7. `/converted2/include/InventoryItem.h` → Items
8. `/converted2/include/ItemContainer.h` → Containers
9. `/converted2/include/PathFinder.h` → Pathfinding
10. `/converted2/include/BodyDamage.h` → Health system
