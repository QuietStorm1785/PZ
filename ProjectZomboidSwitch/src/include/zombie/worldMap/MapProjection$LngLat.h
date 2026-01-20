#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace worldMap {

class MapProjection {
public:
    double longitude = 0.0;
    double latitude = 0.0;

   public MapProjection$LngLat(double var1, double var3) {
      this.longitude = var1;
      this.latitude = var3;
   }
}
} // namespace worldMap
} // namespace zombie
