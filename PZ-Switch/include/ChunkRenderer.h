#pragma once
#include <vector>
#include <memory>
#include <cstdint>
#include <SDL2/SDL.h>

class IsoChunk;
class IsoGridSquare;
class IsoCell;
class SpriteBatch;

namespace zombie {
 namespace graphics { class Sprite; class AnimatedSprite; }
 namespace characters { class IsoGameCharacter; }
}

/**
 * Layer types for isometric rendering
 * Objects are rendered in this order for proper depth
 */
enum class RenderLayer : int {
 GROUND = 0, // Floor tiles, grass
 WALL = 1, // Walls, obstacles
 OBJECT = 2, // Furniture, items
 CHARACTER = 3, // Players, zombies
 ROOF = 4, // Roofs, overhead objects
 FX = 5, // Particles, effects
 UI = 6 // Debug info, UI overlay
};

/**
 * ChunkRenderer - Renders IsoChunk tiles and objects
 * 
 * Features:
 * - Layer-based rendering (ground, wall, object, character, roof)
 * - View frustum culling (only render visible chunks)
 * - Batch rendering for performance
 * - Depth sorting for isometric perspective
 */
class ChunkRenderer {
public:
 struct Config {
 bool enableCulling; // Skip off-screen chunks
 bool debugShowChunkBounds; // Draw chunk outlines
 bool debugShowTileBounds; // Draw tile outlines
 int maxTilesPerBatch; // Tiles per SpriteBatch
 float viewDistance; // Pixels to render around camera
 
 Config() : enableCulling(true), debugShowChunkBounds(false),
 debugShowTileBounds(false), maxTilesPerBatch(1024),
 viewDistance(500.0f) {}
 };

 explicit ChunkRenderer(SDL_Renderer* renderer, const Config& config = Config());
 ~ChunkRenderer();

 // Render a single chunk
 void renderChunk(IsoChunk* chunk, const SpriteBatch* batch, 
 float cameraX, float cameraY);

 // Render all loaded chunks in a world
 void renderAllChunks(IsoCell* cell, int currentZ, 
 float cameraX, float cameraY,
 SpriteBatch* batch);

 // Render specific layer
 void renderLayer(IsoChunk* chunk, RenderLayer layer, 
 float cameraX, float cameraY,
 SpriteBatch* batch);

 // Configuration
 void setConfig(const Config& cfg) { config = cfg; }
 const Config& getConfig() const { return config; }

 // Statistics
 struct Stats {
 int chunksRendered = 0;
 int tilesRendered = 0;
 int tilesSkipped = 0; // Culled
 int objectsRendered = 0;
 float lastFrameTime = 0.0f;
 };
 const Stats& getLastStats() const { return lastStats; }

private:
 SDL_Renderer* renderer;
 Config config;
 mutable Stats lastStats;

 // Check if chunk is visible
 bool isChunkInView(IsoChunk* chunk, float cameraX, float cameraY);
 
 // Convert grid coordinates to screen coordinates (isometric)
 void gridToScreen(int gridX, int gridY, int z, float& screenX, float& screenY);
 
 // Check if tile is in view
 bool isTileInView(int gridX, int gridY, float cameraX, float cameraY);
 
 // Render a single tile
 void renderTile(IsoGridSquare* square, RenderLayer layer, 
 float cameraX, float cameraY, SpriteBatch* batch);

 // Render objects on tile
 void renderObjects(IsoGridSquare* square, RenderLayer layer,
 float cameraX, float cameraY, SpriteBatch* batch);
 
 // Render sprite at isometric position
 void renderSprite(zombie::graphics::Sprite* sprite, 
 float gridX, float gridY, float z,
 float cameraX, float cameraY);
 
 // Render animated character sprite
 void renderCharacter(zombie::characters::IsoGameCharacter* character,
 float cameraX, float cameraY);
};

/**
 * CameraController - Follows player and manages view
 */
class CameraController {
public:
 explicit CameraController(float width = 1280, float height = 720);

 // Update camera to follow entity
 void updateToFollowEntity(float entityX, float entityY);

 // Get camera position
 float getCameraX() const { return cameraX; }
 float getCameraY() const { return cameraY; }

 // Smooth transitions
 void setLerpSpeed(float speed) { lerpSpeed = speed; }
 float getLerpSpeed() const { return lerpSpeed; }

 // Bounds
 float getViewWidth() const { return viewWidth; }
 float getViewHeight() const { return viewHeight; }

private:
 float cameraX = 0.0f, cameraY = 0.0f;
 float targetX = 0.0f, targetY = 0.0f;
 float viewWidth, viewHeight;
 float lerpSpeed = 0.1f; // Smooth following
};
