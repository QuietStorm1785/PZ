#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/booleanrectangles/BooleanRectangleCollection/Point.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace booleanrectangles {


class BooleanRectangleCollection {
public:
   BooleanRectangleCollection$1(BooleanRectangleCollection var1) {
      this.this$0 = var1;
   }

    int compare(Point var1, Point var2) {
      return var1.Y != var2.Y ? var1.Y - var2.Y : var1.X - var2.X;
   }
}
} // namespace booleanrectangles
} // namespace core
} // namespace zombie
