#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/profiling/PerformanceProfileProbe.h"

namespace zombie {
namespace iso {


class IsoCell {
public:
    const PerformanceProfileProbe renderIsoWater = std::make_shared<PerformanceProfileProbe>("renderIsoWater");
    const PerformanceProfileProbe renderFloor = std::make_shared<PerformanceProfileProbe>("renderFloor");
    const PerformanceProfileProbe renderPuddles = std::make_shared<PerformanceProfileProbe>("renderPuddles");
    const PerformanceProfileProbe renderShore = std::make_shared<PerformanceProfileProbe>("renderShore");
    const PerformanceProfileProbe renderSnow = std::make_shared<PerformanceProfileProbe>("renderSnow");
    const PerformanceProfileProbe renderBlood = std::make_shared<PerformanceProfileProbe>("renderBlood");
    const PerformanceProfileProbe vegetationCorpses = std::make_shared<PerformanceProfileProbe>("vegetationCorpses");
    const PerformanceProfileProbe renderFloorShading = std::make_shared<PerformanceProfileProbe>("renderFloorShading");
    const PerformanceProfileProbe renderShadows = std::make_shared<PerformanceProfileProbe>("renderShadows");
    const PerformanceProfileProbe luaOnPostFloorLayerDraw = std::make_shared<PerformanceProfileProbe>("luaOnPostFloorLayerDraw");
    const PerformanceProfileProbe minusFloorCharacters = std::make_shared<PerformanceProfileProbe>("minusFloorCharacters");

   IsoCell$s_performance$renderTiles$PperformRenderTilesLayer(std::string var1) {
      super(var1);
   }
}
} // namespace iso
} // namespace zombie
