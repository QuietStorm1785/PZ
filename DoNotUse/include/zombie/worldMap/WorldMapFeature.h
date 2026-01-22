#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/worldMap/WorldMapGeometry/Type.h"

namespace zombie {
namespace worldMap {


class WorldMapFeature {
public:
    const WorldMapCell m_cell;
   public const std::vector<WorldMapGeometry> m_geometries = std::make_unique<std::vector<>>();
    WorldMapProperties m_properties = nullptr;

   WorldMapFeature(WorldMapCell var1) {
      this.m_cell = var1;
   }

    bool hasLineString() {
      for (int var1 = 0; var1 < this.m_geometries.size(); var1++) {
         if (this.m_geometries.get(var1).m_type == Type.LineString) {
    return true;
         }
      }

    return false;
   }

    bool hasPoint() {
      for (int var1 = 0; var1 < this.m_geometries.size(); var1++) {
         if (this.m_geometries.get(var1).m_type == Type.Point) {
    return true;
         }
      }

    return false;
   }

    bool hasPolygon() {
      for (int var1 = 0; var1 < this.m_geometries.size(); var1++) {
         if (this.m_geometries.get(var1).m_type == Type.Polygon) {
    return true;
         }
      }

    return false;
   }

    bool containsPoint(float var1, float var2) {
      for (int var3 = 0; var3 < this.m_geometries.size(); var3++) {
    WorldMapGeometry var4 = this.m_geometries.get(var3);
         if (var4.containsPoint(var1, var2)) {
    return true;
         }
      }

    return false;
   }

    void dispose() {
      for (WorldMapGeometry var2 : this.m_geometries) {
         var2.dispose();
      }

      this.m_properties.clear();
   }
}
} // namespace worldMap
} // namespace zombie
