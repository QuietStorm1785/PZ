#include "PlayerChunkSync.h"
#include "IsoPlayer.h"
#include "IsoCell.h"
#include "ChunkManager.h"
#include "IsoChunk.h"
#include <cmath>
#include <algorithm>

PlayerChunkSync::PlayerChunkSync(IsoCell* cell, void* player, ChunkManager* manager,
 const Config& config)
 : cell(cell), player(player), chunkManager(manager), config(config) {
 // Position will be initialized on first update
 playerChunkX = 0;
 playerChunkY = 0;
 playerChunkZ = 0;
}

PlayerChunkSync::~PlayerChunkSync() = default;

void PlayerChunkSync::update(float deltaTime) {
 if (!player || !cell) return;

 updateChunkPosition();
 updateChunkLoading();
 updateCameraPosition(deltaTime);
 updateBoundaryDetection();
 updateZTransition(deltaTime);
}

void PlayerChunkSync::updateChunkPosition() {
 if (!player) return;
 
 // Will be updated once player position is available
 // For now, just track that we need to update
 // Full implementation: calculate newChunkX/Y/Z and detect changes
}

void PlayerChunkSync::updateChunkLoading() {
 // Request chunks in radius around player
 requestChunksAround(playerChunkX, playerChunkY);
}

void PlayerChunkSync::requestChunksAround(int cx, int cy) {
 if (!cell) return;

 // Request loading of chunks in load distance
 for (int x = -config.loadDistance; x <= config.loadDistance; x++) {
 for (int y = -config.loadDistance; y <= config.loadDistance; y++) {
 int chunkX = cx + x;
 int chunkY = cy + y;
 
 // Use IsoCell to load chunks
 cell->loadChunk(chunkX, chunkY, playerChunkZ);
 stats.chunksLoaded++;
 }
 }

 // Unload far chunks
 for (int x = -config.unloadDistance - 1; x <= config.unloadDistance + 1; x++) {
 for (int y = -config.unloadDistance - 1; y <= config.unloadDistance + 1; y++) {
 if (std::abs(x) <= config.loadDistance && std::abs(y) <= config.loadDistance) {
 continue; // Don't unload chunks we just loaded
 }
 
 int chunkX = cx + x;
 int chunkY = cy + y;
 
 // Use IsoCell to unload chunks
 cell->unloadChunk(chunkX, chunkY, playerChunkZ);
 stats.chunksUnloaded++;
 }
 }
}

void PlayerChunkSync::updateCameraPosition(float deltaTime) {
 if (!player) return;
 
 // Smooth lerp - camera will follow player
 float lerpFactor = 1.0f - std::pow(1.0f - config.transitionSpeed, deltaTime);
 cameraPos.x += (targetCameraPos.x - cameraPos.x) * lerpFactor;
 cameraPos.y += (targetCameraPos.y - cameraPos.y) * lerpFactor;
}

void PlayerChunkSync::updateBoundaryDetection() {
 if (!player) return;
 
 // Simplified boundary detection - just mark as close to boundaries
 // Full implementation would check localX/Y against 32
 nearChunkBoundary = boundaryDistance < 5.0f;
}

void PlayerChunkSync::updateZTransition(float deltaTime) {
 if (!inZTransition) return;

 zTransitionProgress += config.transitionSpeed * deltaTime;
 
 if (zTransitionProgress >= 1.0f) {
 zTransitionProgress = 1.0f;
 playerChunkZ = targetZ;
 inZTransition = false;
 }
}
