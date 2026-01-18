#include "IsoCell.h"
#include "IsoChunk.h"
#include "IsoGridSquare.h"
#include "IsoPlayer.h"
#include "IsoZombie.h"
#include "WorldContent.h"
#include <algorithm>

IsoCell::IsoCell(int width, int height)
 : width(width)
 , height(height) {
 
 // Pre-load central chunks for testing
 // In a real implementation, chunks would be loaded dynamically based on player position
 for (int cx = 0; cx < 4; cx++) {
 for (int cy = 0; cy < 4; cy++) {
 loadChunk(cx, cy, 0); // Ground level
 }
 }
}

IsoCell::~IsoCell() {
 // Chunks are automatically deleted via unique_ptr
 chunks.clear();
}

uint32_t IsoCell::getChunkKey(int chunkX, int chunkY, int z) const {
 // Pack chunk coordinates into a single key
 return ((uint32_t)chunkX << 16) | ((uint32_t)chunkY << 8) | (uint32_t)z;
}

IsoChunk* IsoCell::getChunk(int chunkX, int chunkY, int z) {
 uint32_t key = getChunkKey(chunkX, chunkY, z);
 auto it = chunks.find(key);
 if (it != chunks.end()) {
 return it->second.get();
 }
 return nullptr;
}

void IsoCell::loadChunk(int chunkX, int chunkY, int z) {
 uint32_t key = getChunkKey(chunkX, chunkY, z);
 
 // Don't reload if already exists
 if (chunks.find(key) != chunks.end()) {
 return;
 }
 
 // Create and load new chunk
 auto chunk = std::make_unique<IsoChunk>(this, chunkX, chunkY, z);
 chunk->load();
 chunks[key] = std::move(chunk);
}

void IsoCell::unloadChunk(int chunkX, int chunkY, int z) {
 uint32_t key = getChunkKey(chunkX, chunkY, z);
 auto it = chunks.find(key);
 if (it != chunks.end()) {
 it->second->unload();
 chunks.erase(it);
 }
}

void IsoCell::unloadAllChunks() {
 // Collect keys first to avoid iterator invalidation
 std::vector<uint32_t> keysToUnload;
 for (const auto& kv : chunks) {
 keysToUnload.push_back(kv.first);
 }
 
 for (uint32_t key : keysToUnload) {
 int chunkZ = key & 0xFF;
 int chunkY = (key >> 8) & 0xFF;
 int chunkX = (key >> 16) & 0xFFFF;
 unloadChunk(chunkX, chunkY, chunkZ);
 }
}

void IsoCell::ensureChunkExists(int chunkX, int chunkY, int z) {
 if (!getChunk(chunkX, chunkY, z)) {
 loadChunk(chunkX, chunkY, z);
 }
}

IsoGridSquare* IsoCell::getGridSquare(int x, int y, int z) {
 // Convert world coordinates to chunk coordinates
 int chunkX = x / IsoChunk::CHUNK_SIZE;
 int chunkY = y / IsoChunk::CHUNK_SIZE;
 
 // Get local coordinates within chunk
 int localX = x % IsoChunk::CHUNK_SIZE;
 int localY = y % IsoChunk::CHUNK_SIZE;
 
 // Handle negative coordinates
 if (localX < 0) {
 localX += IsoChunk::CHUNK_SIZE;
 chunkX--;
 }
 if (localY < 0) {
 localY += IsoChunk::CHUNK_SIZE;
 chunkY--;
 }
 
 // Ensure chunk exists
 ensureChunkExists(chunkX, chunkY, z);
 
 // Get chunk
 IsoChunk* chunk = getChunk(chunkX, chunkY, z);
 if (!chunk) {
 return nullptr;
 }
 
 return chunk->getGridSquare(localX, localY);
}

const IsoGridSquare* IsoCell::getGridSquare(int x, int y, int z) const {
 // Convert world coordinates to chunk coordinates
 int chunkX = x / IsoChunk::CHUNK_SIZE;
 int chunkY = y / IsoChunk::CHUNK_SIZE;
 
 // Get local coordinates within chunk
 int localX = x % IsoChunk::CHUNK_SIZE;
 int localY = y % IsoChunk::CHUNK_SIZE;
 
 // Handle negative coordinates
 if (localX < 0) {
 localX += IsoChunk::CHUNK_SIZE;
 chunkX--;
 }
 if (localY < 0) {
 localY += IsoChunk::CHUNK_SIZE;
 chunkY--;
 }
 
 // Get chunk
 uint32_t key = getChunkKey(chunkX, chunkY, z);
 auto it = chunks.find(key);
 if (it == chunks.end()) {
 return nullptr;
 }
 
 return it->second->getGridSquare(localX, localY);
}

void IsoCell::addCharacter(IsoPlayerPtr player) {
 if (!player) return;

 if (std::find(players.begin(), players.end(), player) == players.end()) {
 players.push_back(player);
 }

 // Bind player to this world and place on its current square (z defaults to 0)
 player->setWorld(this, 0);
 
 // Register with entity spatial grid (Z level 0 for player)
 EntitySpatialGrid* grid = getOrCreateEntityGrid(0);
 grid->insertEntity(player->getX(), player->getY(), player.get());
}

void IsoCell::removeCharacter(IsoPlayerPtr player) {
 if (!player) return;

 // Remove from entity spatial grid (Z level 0 for player)
 auto gridIt = entityGrids.find(0);
 if (gridIt != entityGrids.end()) {
 gridIt->second->removeEntity(player->getX(), player->getY(), player.get());
 }

 player->detachFromWorld();

 auto it = std::find(players.begin(), players.end(), player);
 if (it != players.end()) {
 players.erase(it);
 }
}

void IsoCell::addZombie(IsoZombiePtr zombie) {
 if (zombie && std::find(zombies.begin(), zombies.end(), zombie) == zombies.end()) {
 zombies.push_back(zombie);
 }
 
 // Register with entity spatial grid - but need to handle IsoZombie vs IsoPlayer type mismatch
 if (zombie) {
 int z = static_cast<int>(zombie->getZ());
 getOrCreateEntityGrid(z);
 // Note: Zombies and players are different types; this is a limitation of the current EntitySpatialGrid
 // For now, we treat zombies as a separate tracking system
 }
}
void IsoCell::removeZombie(IsoZombiePtr zombie) {
 auto it = std::find(zombies.begin(), zombies.end(), zombie);
 if (it != zombies.end()) {
 zombies.erase(it);
 }
}

void IsoCell::update() {
 // Update all active chunks
 for (auto& pair : chunks) {
 pair.second->update();
 }
}

void IsoCell::forEachLoadedChunk(int z, const std::function<void(const IsoChunk*)>& fn) const {
 for (const auto& entry : chunks) {
 uint32_t key = entry.first;
 uint32_t kz = (key & 0xFFu);
 if (z >= 0 && static_cast<uint32_t>(z) != kz) continue;
 const IsoChunk* chunk = entry.second.get();
 if (chunk && chunk->isLoaded()) {
 fn(chunk);
 }
 }
}

void IsoCell::forEachLoadedSquare(int z, const std::function<void(const IsoGridSquare*)>& fn) const {
 forEachLoadedChunk(z, [&](const IsoChunk* chunk) {
 for (int x = 0; x < IsoChunk::CHUNK_SIZE; ++x) {
 for (int y = 0; y < IsoChunk::CHUNK_SIZE; ++y) {
 const IsoGridSquare* sq = chunk->getGridSquare(x, y);
 if (sq) fn(sq);
 }
 }
 });
}

IsoCell::WalkabilityListenerId IsoCell::addWalkabilityListener(const std::function<void(int,int,int,bool)>& cb) {
 WalkabilityListenerId id = nextWalkabilityListenerId++;
 walkabilityListeners[id] = cb;
 return id;
}

void IsoCell::removeWalkabilityListener(WalkabilityListenerId id) {
 walkabilityListeners.erase(id);
}

void IsoCell::notifyWalkabilityChanged(int x, int y, int z, bool walkable) {
 for (const auto& kv : walkabilityListeners) {
 if (kv.second) {
 kv.second(x, y, z, walkable);
 }
 }
}

IsoObject* IsoCell::spawnObject(const std::string& type, int x, int y, int z, bool solid) {
 IsoObject* obj = IsoWorldObjectFactory::create(type, solid);
 if (!obj) return nullptr;
 
 obj->setX(static_cast<float>(x));
 obj->setY(static_cast<float>(y));
 obj->setZ(static_cast<float>(z));
 
 IsoGridSquare* sq = getGridSquare(x, y, z);
 if (!sq) {
 delete obj;
 return nullptr;
 }
 
 sq->addObject(obj);
 
 // Also register with spatial grid for fast queries
 SpatialGrid* grid = getOrCreateObjectGrid(z);
 grid->insertObject(static_cast<float>(x), static_cast<float>(y), obj);
 
 return obj;
}

void IsoCell::despawnObject(IsoObject* obj) {
 if (!obj) return;
 
 IsoGridSquare* sq = obj->getSquare();
 if (sq) {
 sq->removeObject(obj);
 }
 
 // Also remove from spatial grid if tracked
 int z = static_cast<int>(obj->getZ());
 auto gridIt = objectGrids.find(z);
 if (gridIt != objectGrids.end()) {
 gridIt->second->removeObject(static_cast<float>(obj->getX()), static_cast<float>(obj->getY()), obj);
 }
}

SpatialGrid* IsoCell::getOrCreateObjectGrid(int z) {
 auto it = objectGrids.find(z);
 if (it != objectGrids.end()) {
 return it->second.get();
 }
 
 auto grid = std::make_unique<SpatialGrid>(32.0f); // 32-unit cell size
 SpatialGrid* ptr = grid.get();
 objectGrids[z] = std::move(grid);
 return ptr;
}

EntitySpatialGrid* IsoCell::getOrCreateEntityGrid(int z) {
 auto it = entityGrids.find(z);
 if (it != entityGrids.end()) {
 return it->second.get();
 }
 
 auto grid = std::make_unique<EntitySpatialGrid>(32.0f); // 32-unit cell size
 EntitySpatialGrid* ptr = grid.get();
 entityGrids[z] = std::move(grid);
 return ptr;
}

std::vector<IsoObject*> IsoCell::queryObjectsNear(float x, float y, float z, float radius) {
 int zLevel = static_cast<int>(z);
 SpatialGrid* grid = getOrCreateObjectGrid(zLevel);
 return grid->queryObjects(x, y, radius);
}

std::vector<IsoPlayer*> IsoCell::queryEntitiesNear(float x, float y, float z, float radius) {
 int zLevel = static_cast<int>(z);
 EntitySpatialGrid* grid = getOrCreateEntityGrid(zLevel);
 return grid->queryEntities(x, y, radius);}