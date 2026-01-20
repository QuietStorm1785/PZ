#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/worldMap/styles/WorldMapStyleLayer/ColorStop.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/FloatStop.h"
#include "zombie/worldMap/styles/WorldMapStyleV1/WorldMapStyleLayerV1.h"

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapStyleV1 {
public:
    WorldMapLineStyleLayer m_lineStyle = (WorldMapLineStyleLayer)this.m_layer;

   WorldMapStyleV1$WorldMapLineStyleLayerV1(WorldMapStyleV1 var1, std::string var2) {
      super(var1, std::make_shared<WorldMapLineStyleLayer>(var2));
   }

    void setFilter(const std::string& var1, const std::string& var2) {
      this.m_lineStyle.m_filterKey = var1;
      this.m_lineStyle.m_filterValue = var2;
      this.m_lineStyle.m_filter = (var2x, var3) -> var2x.hasLineString() && var2 == var2x.m_properties.get(var1));
   }

    void addFill(float var1, int var2, int var3, int var4, int var5) {
      this.m_lineStyle.m_fill.push_back(std::make_shared<ColorStop>(var1, var2, var3, var4, var5));
   }

    void addLineWidth(float var1, float var2) {
      this.m_lineStyle.m_lineWidth.push_back(std::make_shared<FloatStop>(var1, var2));
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
