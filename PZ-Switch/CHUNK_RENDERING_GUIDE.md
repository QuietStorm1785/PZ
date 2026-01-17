# Chunk Rendering System Documentation

## Overview

The chunk rendering system provides efficient display of isometric tile-based worlds with layer support. It integrates with the existing GameWindow batch renderer and implements view frustum culling for performance.

## Architecture

### Core Components

**ChunkRenderer**
- Renders chunks to screen with isometric projection
- Manages render layers (ground, wall, object, character, roof)
- Implements view frustum culling to skip off-screen chunks
- Uses SpriteBatch for efficient rendering

**RenderLayer Enum**
```cpp
enum class RenderLayer {
    GROUND = 0,      // Floor tiles
    WALL = 1,        // Walls
    OBJECT = 2,      // Furniture, items
    CHARACTER = 3,   // Players, zombies
    ROOF = 4,        // Roofs, overhead
    FX = 5,          // Particles
    UI = 6           // Debug info
};
```

**CameraController**
- Manages camera position following game entities
- Implements smooth lerp for camera movement
- Prevents jerky camera transitions

**PlayerChunkSync**
- Synchronizes player position with chunk loading
- Detects chunk boundary crossings
- Handles smooth Z-level transitions
- Loads/unloads chunks based on player distance

### Coordinate Systems

The system uses three coordinate systems:

1. **World Coordinates** - Infinite space, can be any integer
   - Player position, entity location, etc.
   - Range: -∞ to +∞

2. **Chunk Coordinates** - Which 32×32 chunk
   - Formula: `chunkCoord = worldCoord / 32`
   - Range: -∞ to +∞

3. **Local Coordinates** - Position within chunk (0-31)
   - Formula: `localCoord = worldCoord % 32`
   - Range: 0-31

4. **Screen Coordinates** - Pixel position for rendering
   - Isometric projection formula:
   - `screenX = (gridX - gridY) * 16`
   - `screenY = (gridX + gridY) * 8 + z * 8`

### Tile Layers

Each IsoGridSquare tile now supports layer information:

```cpp
bool hasGroundTile;   // Ground/floor layer
bool hasWall;         // Wall/obstacle layer
bool hasRoofTile;     // Roof/overhead layer
```

These control which render layers display content on each tile.

## Usage

### Basic Rendering

```cpp
// Create chunk renderer
SDL_Renderer* renderer = window->getRenderer();
ChunkRenderer::Config config;
config.enableCulling = true;
config.viewDistance = 500.0f;
ChunkRenderer renderer(sdlRenderer, config);

// Render all chunks around player
ChunkRenderer::renderAllChunks(cell, currentZ, cameraX, cameraY, batch);
```

### Camera Management

```cpp
// Create camera controller
CameraController camera(1280, 720);

// Update each frame
camera.updateToFollowEntity(player->getX(), player->getY());
float camX = camera.getCameraX();
float camY = camera.getCameraY();
```

### Player Chunk Synchronization

```cpp
// Create player chunk tracker
PlayerChunkSync::Config config;
config.loadDistance = 3;
config.transitionSpeed = 0.15f;
PlayerChunkSync sync(cell, player, chunkManager, config);

// Update each frame
sync.update(deltaTime);

// Check for transitions
if (sync.isPlayerChunkBoundary()) {
    // Handle boundary crossing
}

if (sync.isPlayerZTransition()) {
    float progress = sync.getZTransitionProgress();
    // Apply transition effect
}
```

## Performance Considerations

### View Frustum Culling

Chunks are culled based on distance from camera:
- Threshold: `viewDistance` pixels (default 500)
- Chunks outside this radius are not rendered
- Can be disabled with `enableCulling = false`

### Tile-Level Culling

Individual tiles are also culled:
- Only tiles within `viewDistance` are rendered
- Skipped tiles are counted in statistics

### Batch Rendering

- Uses existing SpriteBatch system for efficiency
- Renders all layers of a chunk before moving to next
- Reduces draw calls significantly

### Memory Management

Chunks track memory usage:
- ~1MB per loaded chunk (1024 tiles × sizeof(IsoGridSquare))
- Objects stored as pointers (8 bytes each)
- ~2 objects/tile average on typical chunks

## Statistics

The renderer provides frame statistics:

```cpp
struct Stats {
    int chunksRendered;      // Chunks drawn this frame
    int tilesRendered;       // Tiles drawn
    int tilesSkipped;        // Tiles culled
    int objectsRendered;     // Objects (entities) drawn
    float lastFrameTime;     // Time spent rendering (seconds)
};
```

Access with: `renderer.getLastStats()`

## Debug Features

### Debug Rendering Modes

```cpp
config.debugShowChunkBounds = true;   // Draw red outlines around chunks
config.debugShowTileBounds = true;    // Draw tile grid
```

### Statistics Logging

```cpp
auto stats = renderer.getLastStats();
printf("Chunks: %d, Tiles: %d (skipped: %d), Time: %.3fms\n",
       stats.chunksRendered, stats.tilesRendered,
       stats.tilesSkipped, stats.lastFrameTime * 1000);
```

## Integration with GameWindow

The chunk rendering integrates into the main game loop:

1. GameWindow::logic() - Update player position, chunks
2. GameWindow::render()
   - Clear screen
   - Update camera to follow player
   - Render all visible chunks by layer
   - Render UI/debug info

## Z-Level Support

Each chunk can have tiles on multiple Z-levels (0-7):
- Ground level: Z=0
- Upper floors: Z=1-7
- Smooth transitions between levels
- Camera follows player's Z-level automatically

## Future Enhancements

1. **Sprite/Texture Rendering**
   - Replace solid color rectangles with actual sprite graphics
   - Implement texture atlasing for efficiency

2. **Advanced Culling**
   - Frustum culling using viewport boundaries
   - Occlusion culling for interior/roofed areas

3. **Lighting System**
   - Per-tile lighting calculation
   - Dynamic shadow rendering
   - Integration with visibility system

4. **Particle Effects**
   - Render effects layer (FX layer)
   - Weather particle systems
   - Explosion/impact effects

5. **Animation**
   - Animated tile rendering
   - Character animation integration
   - Object animation support

6. **Performance Profiling**
   - Detailed timing information
   - GPU memory tracking
   - Batch count optimization

## Troubleshooting

### Chunks Not Visible
- Check that chunks are loaded in IsoCell
- Verify PlayerChunkSync is updating chunk loading
- Ensure camera position is initialized

### Rendering Artifacts
- Enable debug bounds to verify layer rendering order
- Check isometric projection math
- Verify coordinate conversion between systems

### Performance Issues
- Enable culling (`enableCulling = true`)
- Reduce `viewDistance` to render fewer chunks
- Check statistics for unexpectedly high tile counts

### Z-Level Problems
- Verify player Z-level is correct
- Check that chunks at different Z-levels are loaded
- Ensure Z-level transitions complete properly

