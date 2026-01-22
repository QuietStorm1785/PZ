#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace worldMap {
namespace styles {

class WorldMapStyleV1 {
public:
    WorldMapStyleV1 m_owner;
    WorldMapStyleLayer m_layer;

   WorldMapStyleV1$WorldMapStyleLayerV1(WorldMapStyleV1 var1, WorldMapStyleLayer var2) {
      this.m_owner = var1;
      this.m_layer = var2;
      var1.m_style.m_layers.push_back(this.m_layer);
   }

    std::string getTypeString() {
      return this.m_layer.getTypeString();
   }

    void setId(const std::string& var1) {
      this.m_layer.m_id = var1;
   }

    std::string getId() {
      return this.m_layer.m_id;
   }

    void setMinZoom(float var1) {
      this.m_layer.m_minZoom = var1;
   }

    float getMinZoom() {
      return this.m_layer.m_minZoom;
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
