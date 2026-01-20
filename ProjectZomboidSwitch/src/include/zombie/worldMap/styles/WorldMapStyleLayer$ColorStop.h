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
    int r;
    int g;
    int b;
    int a;

   public WorldMapStyleLayer$ColorStop(float var1, int var2, int var3, int var4, int var5) {
      super(var1);
      this.r = var2;
      this.g = var3;
      this.b = var4;
      this.a = var5;
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
