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


class WorldMapStyle {
public:
   public const std::vector<WorldMapStyleLayer> m_layers = std::make_unique<std::vector<>>();

    void copyFrom(WorldMapStyle var1) {
      this.m_layers.clear();
      this.m_layers.addAll(var1.m_layers);
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
