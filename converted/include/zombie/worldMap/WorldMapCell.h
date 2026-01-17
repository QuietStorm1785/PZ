#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapCell {
public:
  int m_x;
  int m_y;
public
  final ArrayList<WorldMapFeature> m_features = std::make_unique<ArrayList<>>();

  void hitTest(float x, float y, ArrayList<WorldMapFeature> features) {
    x -= this.m_x * 300;
    y -= this.m_y * 300;

    for (int int0 = 0; int0 < this.m_features.size(); int0++) {
      WorldMapFeature worldMapFeature = this.m_features.get(int0);
      if (worldMapFeature.containsPoint(x, y)) {
        features.add(worldMapFeature);
      }
    }
  }

  void dispose() {
    for (WorldMapFeature worldMapFeature : this.m_features) {
      worldMapFeature.dispose();
    }

    this.m_features.clear();
  }
}
} // namespace worldMap
} // namespace zombie
