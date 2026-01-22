#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {


class VehicleStorySpawnData {
public:
    RandomizedVehicleStoryBase m_story;
    Zone m_zone;
    float m_spawnX;
    float m_spawnY;
    float m_direction;
    int m_x1;
    int m_y1;
    int m_x2;
    int m_y2;

    public VehicleStorySpawnData(RandomizedVehicleStoryBase var1, Zone var2, float var3, float var4, float var5, int var6, int var7, int var8, int var9) {
      this.m_story = var1;
      this.m_zone = var2;
      this.m_spawnX = var3;
      this.m_spawnY = var4;
      this.m_direction = var5;
      this.m_x1 = var6;
      this.m_y1 = var7;
      this.m_x2 = var8;
      this.m_y2 = var9;
   }

    bool isValid(Zone var1, IsoChunk var2) {
      if (var1 != this.m_zone) {
    return false;
      } else if (!this.m_story.isFullyStreamedIn(this.m_x1, this.m_y1, this.m_x2, this.m_y2)) {
    return false;
      } else {
         var2.setRandomVehicleStoryToSpawnLater(nullptr);
         return this.m_story.isValid(var1, var2, false);
      }
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
