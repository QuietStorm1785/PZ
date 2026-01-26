# Project Zomboid C++ Systems and File Locations

This document provides an overview of major gameplay and engine systems in the Project Zomboid C++ codebase, along with the primary files and folders where their logic is implemented. Use this as a reference for navigating and extending the codebase.

---

## 1. Weather Systems
- **Description:** Handles rain, snow, fog, lightning, and related overlays.
- **Key Files:**
  - `src/zombie/iso/IsoCell.cpp` / `IsoCell.h` (FX coordination, render/update calls)
  - `src/zombie/iso/IsoWeatherFX.cpp` / `IsoWeatherFX.h` (main weather FX)
  - `src/zombie/iso/RainFX.cpp` / `RainFX.h` (rain)
  - `src/zombie/iso/LightningFX.cpp` / `LightningFX.h` (lightning)
  - `src/zombie/iso/FogFX.cpp` / `FogFX.h` (fog)
  - `src/zombie/iso/` (other FX: rain splashes, wet surfaces, puddles, etc.)
  - `Docs/Weather_Systems_Implementation.md` (design/usage)

## 2. Building System
- **Description:** Manages buildings, building search, scoring, and player construction.
- **Key Files:**
  - `src/zombie/iso/areas/IsoBuilding.cpp` / `IsoBuilding.h` (building logic)
  - `src/zombie/iso/areas/BuildingScore.cpp` / `BuildingScore.h` (scoring)
  - `src/zombie/iso/BuildingDef.cpp` / `BuildingDef.h` (definitions)
  - `src/zombie/iso/MultiStageBuilding.cpp` / `MultiStageBuilding.h` (multi-stage buildings)
  - `src/zombie/iso/IsoCell/BuildingSearchCriteria.h` (search criteria)
  - `src/zombie/core/stash/StashBuilding.cpp` / `StashBuilding.h` (stash logic)
  - `src/zombie/randomizedWorld/randomizedBuilding/RandomizedBuildingBase.cpp` / `.h` (randomized buildings)

## 3. Grid and Tile System
- **Description:** World grid, grid square management, tile access, and navigation.
- **Key Files:**
  - `src/zombie/iso/IsoCell.cpp` / `IsoCell.h` (main grid logic)
  - `src/zombie/iso/IsoGridSquare.cpp` / `IsoGridSquare.h` (grid square logic)
  - `src/zombie/iso/IsoChunk.cpp` / `IsoChunk.h` (chunk logic)
  - `src/zombie/iso/IsoLot.cpp` / `IsoLot.h` (lot logic)

## 4. Object and Inventory System
- **Description:** Handles world objects, inventory items, and their processing.
- **Key Files:**
  - `src/zombie/iso/IsoObject.cpp` / `IsoObject.h` (base object)
  - `src/zombie/iso/InventoryItem.cpp` / `InventoryItem.h` (inventory)
  - `src/zombie/iso/IsoWorldInventoryObject.cpp` / `IsoWorldInventoryObject.h` (world inventory)
  - `src/zombie/iso/IsoCell.cpp` (object/inventory processing methods)

## 5. Player and Character System
- **Description:** Player state, movement, and character logic.
- **Key Files:**
  - `src/zombie/characters/IsoPlayer.cpp` / `IsoPlayer.h` (player logic)
  - `src/zombie/characters/IsoGameCharacter.cpp` / `IsoGameCharacter.h` (base character)
  - `src/zombie/iso/IsoCell.cpp` (player-related methods)

## 6. Event and System Methods
- **Description:** Game events, system resets, and event-driven updates.
- **Key Files:**
  - `src/zombie/iso/IsoCell.cpp` (OnPlayerDeath, OnPlayerSpawn, OnGameStart, OnGameEnd, updateEventSystems, resetForNewGame)

## 7. Rendering and Lighting
- **Description:** Tile/object rendering, lighting, and visual effects.
- **Key Files:**
  - `src/zombie/iso/IsoCell.cpp` (render pipeline)
  - `src/zombie/iso/IsoGridSquare.cpp` / `IsoGridSquare.h` (lighting)
  - `src/zombie/iso/IndieGL.cpp` / `IndieGL.h` (OpenGL-like rendering)

## 8. Lua Scripting Integration
- **Description:** Lua state, drag tables, and Lua-exposed objects.
- **Key Files:**
  - `src/zombie/iso/IsoCell.cpp` (Lua drag logic, getLuaObjectList)
  - `src/zombie/iso/IsoObject.cpp` / `IsoObject.h` (Lua exposure)
  - `src/zombie/iso/` (Lua integration points)

## 9. Miscellaneous Systems
- **Description:** Miscellaneous features such as heat sources, vehicles, and unique systems.
- **Key Files:**
  - `src/zombie/iso/IsoCell.cpp` (heat source, vehicle, and other stubs)
  - `src/zombie/iso/IsoHeatSource.cpp` / `IsoHeatSource.h` (heat logic)
  - `src/zombie/vehicles/` (vehicle logic)

---

## How to Extend or Locate a System
- Search for the system name or related class in `src/zombie/`.
- Check both `.cpp` and `.h` files for implementation and interface.
- Refer to the Docs/ folder for design and integration notes.

---

For further details, see the respective source/header files and documentation in the Docs/ directory.
