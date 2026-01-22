#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace worldMap {


class WorldMapCell {
public:
    int m_x;
    int m_y;
   public const std::vector<WorldMapFeature> m_features = std::make_unique<std::vector<>>();

    void hitTest(float var1, float var2, std::vector<WorldMapFeature> var3) {
      var1 -= this.m_x * 300;
      var2 -= this.m_y * 300;

      for (int var4 = 0; var4 < this.m_features.size(); var4++) {
    WorldMapFeature var5 = this.m_features.get(var4);
         if (var5.containsPoint(var1, var2)) {
            var3.push_back(var5);
         }
      }
   }

    void dispose() {
      for (WorldMapFeature var2 : this.m_features) {
         var2.dispose();
      }

      this.m_features.clear();
   }
}
} // namespace worldMap
} // namespace zombie
