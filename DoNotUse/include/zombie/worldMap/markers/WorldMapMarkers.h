#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/worldMap/UIWorldMap.h"

namespace zombie {
namespace worldMap {
namespace markers {


class WorldMapMarkers {
public:
   private static const Pool<WorldMapGridSquareMarker> s_gridSquareMarkerPool = std::make_shared<Pool>(WorldMapGridSquareMarker::new);
   private const std::vector<WorldMapMarker> m_markers = std::make_unique<std::vector<>>();

    WorldMapGridSquareMarker addGridSquareMarker(int var1, int var2, int var3, float var4, float var5, float var6, float var7) {
    WorldMapGridSquareMarker var8 = ((WorldMapGridSquareMarker)s_gridSquareMarkerPool.alloc()).init(var1, var2, var3, var4, var5, var6, var7);
      this.m_markers.push_back(var8);
    return var8;
   }

    void removeMarker(WorldMapMarker var1) {
      if (this.m_markers.contains(var1)) {
         this.m_markers.remove(var1);
         var1.release();
      }
   }

    void clear() {
      for (int var1 = 0; var1 < this.m_markers.size(); var1++) {
         this.m_markers.get(var1).release();
      }

      this.m_markers.clear();
   }

    void render(UIWorldMap var1) {
      for (int var2 = 0; var2 < this.m_markers.size(); var2++) {
         this.m_markers.get(var2).render(var1);
      }
   }
}
} // namespace markers
} // namespace worldMap
} // namespace zombie
