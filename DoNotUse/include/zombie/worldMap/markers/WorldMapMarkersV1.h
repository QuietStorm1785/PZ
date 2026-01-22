#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaManager/Exposer.h"
#include "zombie/worldMap/UIWorldMap.h"
#include "zombie/worldMap/markers/WorldMapMarkersV1/WorldMapGridSquareMarkerV1.h"
#include "zombie/worldMap/markers/WorldMapMarkersV1/WorldMapMarkerV1.h"
#include <algorithm>

namespace zombie {
namespace worldMap {
namespace markers {


class WorldMapMarkersV1 {
public:
    const UIWorldMap m_ui;
   private const std::vector<WorldMapMarkerV1> m_markers = std::make_unique<std::vector<>>();

    public WorldMapMarkersV1(UIWorldMap var1) {
      Objects.requireNonNull(var1);
      this.m_ui = var1;
   }

    WorldMapGridSquareMarkerV1 addGridSquareMarker(int var1, int var2, int var3, float var4, float var5, float var6, float var7) {
    WorldMapGridSquareMarker var8 = this.m_ui.getAPIv1().getMarkers().addGridSquareMarker(var1, var2, var3, var4, var5, var6, var7);
    WorldMapGridSquareMarkerV1 var9 = std::make_shared<WorldMapGridSquareMarkerV1>(var8);
      this.m_markers.push_back(var9);
    return var9;
   }

    void removeMarker(WorldMapMarkerV1 var1) {
      if (this.m_markers.remove(var1)) {
         this.m_ui.getAPIv1().getMarkers().removeMarker(var1.m_marker);
      }
   }

    void clear() {
      this.m_ui.getAPIv1().getMarkers().clear();
      this.m_markers.clear();
   }

    static void setExposed(Exposer var0) {
      var0.setExposed(WorldMapMarkersV1.class);
      var0.setExposed(WorldMapMarkerV1.class);
      var0.setExposed(WorldMapGridSquareMarkerV1.class);
   }
}
} // namespace markers
} // namespace worldMap
} // namespace zombie
