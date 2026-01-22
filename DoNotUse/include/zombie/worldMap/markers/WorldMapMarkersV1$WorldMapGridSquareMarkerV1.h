#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/worldMap/markers/WorldMapMarkersV1/WorldMapMarkerV1.h"

namespace zombie {
namespace worldMap {
namespace markers {


class WorldMapMarkersV1 {
public:
    const WorldMapGridSquareMarker m_gridSquareMarker;

   WorldMapMarkersV1$WorldMapGridSquareMarkerV1(WorldMapGridSquareMarker var1) {
      super(var1);
      this.m_gridSquareMarker = var1;
   }

    void setBlink(bool var1) {
      this.m_gridSquareMarker.setBlink(var1);
   }

    void setMinScreenRadius(int var1) {
      this.m_gridSquareMarker.setMinScreenRadius(var1);
   }
}
} // namespace markers
} // namespace worldMap
} // namespace zombie
