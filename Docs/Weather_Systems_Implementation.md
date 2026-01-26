# Weather-Related Systems Implementation Guide

This document details the implementation and extensibility of weather-related systems in the Project Zomboid C++ codebase, focusing on the rendering and management of weather effects such as rain, snow, lightning, fog, and related overlays.

## 1. Weather FX Architecture

Weather effects are modular and extensible, with each major effect (rain, snow, lightning, fog, etc.) encapsulated in its own FX class. The `IsoCell` class coordinates the rendering and update cycles for these systems.

### Key Members in `IsoCell`
- `std::unique_ptr<IsoWeatherFX> weatherFX;` — Main weather FX system (e.g., snow, general weather overlays)
- `std::unique_ptr<RainFX> rainFX;` — Rain rendering system
- `std::unique_ptr<LightningFX> lightningFX;` — Lightning effect system
- `std::unique_ptr<FogFX> fogFX;` — Fog overlay system
- `std::unique_ptr<RainSplashesFX> rainSplashesFX;` — Rain splash effect system
- `std::unique_ptr<WetSurfacesFX> wetSurfacesFX;` — Wet surface effect system
- `std::unique_ptr<PuddlesFX> puddlesFX;` — Puddles effect system

Each system is responsible for its own initialization, update, and render logic. The `IsoCell` methods call these systems if they are present.

## 2. Rendering Methods

### `IsoCell::renderWeatherFx()`
- Renders the main weather FX (`weatherFX`), lightning (`lightningFX`), and fog (`fogFX`).
- Each FX system is checked for existence before rendering.
- Designed for easy expansion: add new FX systems as members and call their `render()` methods here.

### `IsoCell::renderRain()`
- Renders the rain FX (`rainFX`), rain splashes (`rainSplashesFX`), wet surfaces (`wetSurfacesFX`), and puddles (`puddlesFX`).
- Each effect is modular and can be enabled/disabled or extended independently.

#### Example (C++):
```cpp
void IsoCell::renderWeatherFx() {
    if (weatherFX) weatherFX->render();
    if (lightningFX) lightningFX->render();
    if (fogFX) fogFX->render();
    // Add new weather overlays here
}

void IsoCell::renderRain() {
    if (rainFX) rainFX->render();
    if (rainSplashesFX) rainSplashesFX->render();
    if (wetSurfacesFX) wetSurfacesFX->render();
    if (puddlesFX) puddlesFX->render();
    // Add new rain overlays here
}
```

## 3. Extending Weather Systems

To add a new weather effect:
1. Create a new FX class (e.g., `HailFX`) with `init()`, `update()`, and `render()` methods.
2. Add a member to `IsoCell` (e.g., `std::unique_ptr<HailFX> hailFX;`).
3. Initialize the FX in the appropriate place (e.g., during world or weather system setup).
4. Call the FX's `render()` method in `renderWeatherFx()` or `renderRain()` as appropriate.

## 4. System Initialization and Update
- Weather FX systems are typically initialized in `IsoCell::initWeatherFx()` or similar setup methods.
- Updates are performed in `IsoCell::updateWeatherFx()` or the main update loop.
- Each FX system should manage its own state, resources, and rendering pipeline.

## 5. Integration with Game State
- Weather FX can be toggled or modified based on game state (e.g., current weather, time of day, player location).
- Use configuration or scripting (Lua) to control FX parameters at runtime.

## 6. Best Practices
- Keep each FX system modular and self-contained.
- Use smart pointers for resource management.
- Check for FX existence before calling methods.
- Document new FX systems and their integration points in this document.

## 7. Future Expansion
- Additional overlays (e.g., wind, sandstorms, ash) can be added following the same pattern.
- Consider performance implications and batching where possible.
- Integrate with Lua scripting for dynamic weather control.

---

For further details, see the implementation in `IsoCell.cpp` and related FX class headers and sources.
