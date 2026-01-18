#include "ChunkRenderer.h"
#include "IsoChunk.h"
#include "IsoCell.h"
#include "IsoGridSquare.h"
#include "IsoObject.h"
#include "IsoPlayer.h"
#include "SpriteBatch.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include <cmath>
#include <algorithm>

// ===== ChunkRenderer =====

ChunkRenderer::ChunkRenderer(SDL_Renderer* renderer, const Config& config)
    : renderer(renderer), config(config) {
}

ChunkRenderer::~ChunkRenderer() = default;

bool ChunkRenderer::isChunkInView(IsoChunk* chunk, float cameraX, float cameraY) {
    if (!config.enableCulling) return true;
    
    // Convert chunk corners to screen space
    int chunkX = chunk->getChunkX();
    int chunkY = chunk->getChunkY();
    int z = chunk->getZ();
    
    // Check corners
    float corners[4][2];
    gridToScreen(chunkX * 32, chunkY * 32, z, corners[0][0], corners[0][1]);
    gridToScreen((chunkX + 1) * 32, chunkY * 32, z, corners[1][0], corners[1][1]);
    gridToScreen(chunkX * 32, (chunkY + 1) * 32, z, corners[2][0], corners[2][1]);
    gridToScreen((chunkX + 1) * 32, (chunkY + 1) * 32, z, corners[3][0], corners[3][1]);
    
    // Check if any corner is in view
    for (int i = 0; i < 4; i++) {
        float dx = corners[i][0] - cameraX;
        float dy = corners[i][1] - cameraY;
        float dist = std::sqrt(dx * dx + dy * dy);
        if (dist < config.viewDistance) return true;
    }
    return false;
}

void ChunkRenderer::gridToScreen(int gridX, int gridY, int z, float& screenX, float& screenY) {
    // Isometric projection: standard formula
    // screenX = (gridX - gridY) * tileWidth/2
    // screenY = (gridX + gridY) * tileHeight/2 + z * zHeight
    const float TILE_WIDTH = 32.0f;
    const float TILE_HEIGHT = 16.0f;
    const float Z_HEIGHT = 8.0f;
    
    screenX = (gridX - gridY) * (TILE_WIDTH / 2.0f);
    screenY = (gridX + gridY) * (TILE_HEIGHT / 2.0f) + z * Z_HEIGHT;
}

bool ChunkRenderer::isTileInView(int gridX, int gridY, float cameraX, float cameraY) {
    if (!config.enableCulling) return true;
    
    float screenX, screenY;
    gridToScreen(gridX, gridY, 0, screenX, screenY);
    
    float dx = screenX - cameraX;
    float dy = screenY - cameraY;
    float dist = std::sqrt(dx * dx + dy * dy);
    
    return dist < config.viewDistance;
}

void ChunkRenderer::renderTile(IsoGridSquare* square, RenderLayer layer,
                              float cameraX, float cameraY, SpriteBatch* batch) {
    if (!square) return;
    
    int x = square->getX();
    int y = square->getY();
    int z = square->getZ();
    
    float screenX, screenY;
    gridToScreen(x, y, z, screenX, screenY);
    
    // Offset from camera
    screenX -= cameraX;
    screenY -= cameraY;
    
    // Draw ground layer
    if (layer == RenderLayer::GROUND) {
        // Draw floor tile (beige/tan color for now)
        SDL_SetRenderDrawColor(renderer, 210, 180, 140, 255);
        SDL_Rect rect = {(int)screenX, (int)screenY, 32, 16};
        SDL_RenderFillRect(renderer, &rect);
        
        if (config.debugShowTileBounds) {
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
    
    // Wall layer
    if (layer == RenderLayer::WALL) {
        // Check for wall tile
        if (square->isWall()) {
            SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
            SDL_Rect rect = {(int)screenX, (int)screenY - 16, 32, 32};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    
    // Object layer
    if (layer == RenderLayer::OBJECT) {
        renderObjects(square, layer, cameraX, cameraY, batch);
    }
}

void ChunkRenderer::renderObjects(IsoGridSquare* square, RenderLayer layer,
                                 float cameraX, float cameraY, SpriteBatch* batch) {
    (void)layer;
    (void)batch;
    // Render IsoObjects on this square
    for (IsoObject* obj : square->getObjects()) {
        if (!obj) continue;
        
        // Check if object has a sprite - if so, use it
        if (obj->getSprite()) {
            renderSprite(obj->getSprite(), obj->getX(), obj->getY(), obj->getZ(), 
                        cameraX, cameraY);
            lastStats.objectsRendered++;
        } else {
            // Fallback: Draw simple rect for objects without sprites
            float x = obj->getX();
            float y = obj->getY();
            float screenX, screenY;
            gridToScreen((int)x, (int)y, obj->getZ(), screenX, screenY);
            
            screenX -= cameraX;
            screenY -= cameraY;
            
            SDL_SetRenderDrawColor(renderer, 200, 100, 50, 255);
            SDL_Rect rect = {(int)screenX - 8, (int)screenY - 16, 16, 24};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void ChunkRenderer::renderLayer(IsoChunk* chunk, RenderLayer layer,
                               float cameraX, float cameraY,
                               SpriteBatch* batch) {
    if (!chunk || !chunk->isLoaded()) return;
    
    for (int x = 0; x < IsoChunk::CHUNK_SIZE; x++) {
        for (int y = 0; y < IsoChunk::CHUNK_SIZE; y++) {
            IsoGridSquare* square = chunk->getGridSquare(x, y);
            if (!square) continue;
            
            if (!isTileInView(square->getX(), square->getY(), cameraX, cameraY)) {
                lastStats.tilesSkipped++;
                continue;
            }
            
            renderTile(square, layer, cameraX, cameraY, batch);
            lastStats.tilesRendered++;
        }
    }
}

void ChunkRenderer::renderChunk(IsoChunk* chunk, const SpriteBatch* batch,
                               float cameraX, float cameraY) {
    if (!chunk || !chunk->isLoaded()) return;
    
    if (!isChunkInView(chunk, cameraX, cameraY)) return;
    
    lastStats.chunksRendered++;
    
    // Render all layers in order
    for (int layer = 0; layer <= (int)RenderLayer::UI; layer++) {
        renderLayer(chunk, (RenderLayer)layer, cameraX, cameraY, (SpriteBatch*)batch);
    }
    
    if (config.debugShowChunkBounds) {
        float x1, y1, x2, y2, x3, y3, x4, y4;
        int cx = chunk->getChunkX();
        int cy = chunk->getChunkY();
        int z = chunk->getZ();
        
        gridToScreen(cx * 32, cy * 32, z, x1, y1);
        gridToScreen((cx + 1) * 32, cy * 32, z, x2, y2);
        gridToScreen((cx + 1) * 32, (cy + 1) * 32, z, x3, y3);
        gridToScreen(cx * 32, (cy + 1) * 32, z, x4, y4);
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, (int)(x1 - cameraX), (int)(y1 - cameraY),
                          (int)(x2 - cameraX), (int)(y2 - cameraY));
        SDL_RenderDrawLine(renderer, (int)(x2 - cameraX), (int)(y2 - cameraY),
                          (int)(x3 - cameraX), (int)(y3 - cameraY));
        SDL_RenderDrawLine(renderer, (int)(x3 - cameraX), (int)(y3 - cameraY),
                          (int)(x4 - cameraX), (int)(y4 - cameraY));
        SDL_RenderDrawLine(renderer, (int)(x4 - cameraX), (int)(y4 - cameraY),
                          (int)(x1 - cameraX), (int)(y1 - cameraY));
    }
}

void ChunkRenderer::renderAllChunks(IsoCell* cell, int currentZ,
                                   float cameraX, float cameraY,
                                   SpriteBatch* batch) {
    if (!cell) return;
    
    lastStats = Stats();
    
    auto startTime = SDL_GetTicks();
    
    cell->forEachLoadedChunk(currentZ, [&](const IsoChunk* chunk) {
        renderChunk(const_cast<IsoChunk*>(chunk), batch, cameraX, cameraY);
    });
    
    lastStats.lastFrameTime = (SDL_GetTicks() - startTime) / 1000.0f;
}

// ===== CameraController =====

CameraController::CameraController(float width, float height)
    : viewWidth(width), viewHeight(height) {
}

void CameraController::updateToFollowEntity(float entityX, float entityY) {
    targetX = entityX;
    targetY = entityY;
    
    // Smooth lerp towards target
    cameraX += (targetX - cameraX) * lerpSpeed;
    cameraY += (targetY - cameraY) * lerpSpeed;
}

// ===== Sprite Rendering Methods =====

void ChunkRenderer::renderSprite(zombie::graphics::Sprite* sprite,
                                float gridX, float gridY, float z,
                                float cameraX, float cameraY) {
    if (!sprite) return;
    
    // Convert grid position to screen position
    float screenX, screenY;
    gridToScreen((int)gridX, (int)gridY, (int)z, screenX, screenY);
    
    // Apply camera offset
    screenX -= cameraX;
    screenY -= cameraY;
    
    // Position sprite at screen coordinates
    sprite->setPosition(screenX, screenY);
    
    // Render using sprite's built-in render method
    sprite->render(renderer);
}

void ChunkRenderer::renderCharacter(zombie::characters::IsoGameCharacter* character,
                                   float cameraX, float cameraY) {
    if (!character) return;
    
    // Try to get sprite from character (if it's a player with AnimatedSprite)
    zombie::graphics::AnimatedSprite* sprite = nullptr;
    
    // Check if this is an IsoPlayer (has getSprite method)
    if (zombie::characters::IsoPlayer* player = dynamic_cast<zombie::characters::IsoPlayer*>(character)) {
        sprite = player->getSprite();
    }
    
    if (sprite) {
        renderSprite(sprite, character->getX(), character->getY(), 0, cameraX, cameraY);
    } else {
        // Fallback: Draw simple colored rect for characters without sprites
        float screenX, screenY;
        gridToScreen((int)character->getX(), (int)character->getY(), 0, screenX, screenY);
        
        screenX -= cameraX;
        screenY -= cameraY;
        
        SDL_SetRenderDrawColor(renderer, 50, 150, 255, 255);
        SDL_Rect rect = {(int)screenX - 12, (int)screenY - 24, 24, 32};
        SDL_RenderFillRect(renderer, &rect);
    }
}
