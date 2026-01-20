#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapStyleLayer {
public:
    float r;
    float g;
    float b;
    float a;
   public static const ObjectPool<WorldMapStyleLayer$RGBAf> s_pool = std::make_shared<ObjectPool>(WorldMapStyleLayer$RGBAf::new);

   public WorldMapStyleLayer$RGBAf() {
      this.r = this.g = this.b = this.a = 1.0F;
   }

   public WorldMapStyleLayer$RGBAf init(float var1, float var2, float var3, float var4) {
      this.r = var1;
      this.g = var2;
      this.b = var3;
      this.a = var4;
    return this;
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
