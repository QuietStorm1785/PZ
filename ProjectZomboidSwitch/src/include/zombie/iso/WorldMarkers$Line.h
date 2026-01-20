#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/WorldMarkers/Point.h"

namespace zombie {
namespace iso {


class WorldMarkers {
public:
    Point s;
    Point e;

   WorldMarkers$Line(Point var1, Point var2) {
      this.s = var1;
      this.e = var2;
   }

    std::string toString() {
      return std::string.format("{s: %s, e: %s}", this.s, this.e);
   }
}
} // namespace iso
} // namespace zombie
