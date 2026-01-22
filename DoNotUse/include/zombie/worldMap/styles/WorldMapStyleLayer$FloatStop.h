#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/worldMap/styles/WorldMapStyleLayer/Stop.h"

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapStyleLayer {
public:
    float f;

   public WorldMapStyleLayer$FloatStop(float var1, float var2) {
      super(var1);
      this.f = var2;
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
