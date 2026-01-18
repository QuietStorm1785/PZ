#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoMetaGrid.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class VehicleStorySpawnData {
public:
 RandomizedVehicleStoryBase m_story;
 public IsoMetaGrid.Zone m_zone;
 float m_spawnX;
 float m_spawnY;
 float m_direction;
 int m_x1;
 int m_y1;
 int m_x2;
 int m_y2;

 public VehicleStorySpawnData(
 RandomizedVehicleStoryBase story, IsoMetaGrid.Zone zone, float spawnX, float spawnY, float direction, int x1, int y1, int x2, int y2
 ) {
 this->m_story = story;
 this->m_zone = zone;
 this->m_spawnX = spawnX;
 this->m_spawnY = spawnY;
 this->m_direction = direction;
 this->m_x1 = x1;
 this->m_y1 = y1;
 this->m_x2 = x2;
 this->m_y2 = y2;
 }

 bool isValid(IsoMetaGrid.Zone zone, IsoChunk chunk) {
 if (zone != this->m_zone) {
 return false;
 } else if (!this->m_story.isFullyStreamedIn(this->m_x1, this->m_y1, this->m_x2, this->m_y2) {
 return false;
 } else {
 chunk.setRandomVehicleStoryToSpawnLater(nullptr);
 return this->m_story.isValid(zone, chunk, false);
 }
 }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
