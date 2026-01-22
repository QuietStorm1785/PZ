#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/booleanrectangles/BooleanRectangleCollection/Point.h"

namespace zombie {
namespace core {
namespace booleanrectangles {


class BooleanRectangleCollection {
public:
    Point Start;
    Point End;

   public BooleanRectangleCollection$Line(BooleanRectangleCollection var1, Point var2, Point var3) {
      this.this$0 = var1;
      this.Start = std::make_unique<Point>();
      this.End = std::make_unique<Point>();
      this.Start.X = var2.X;
      this.Start.Y = var2.Y;
      this.End.X = var3.X;
      this.End.Y = var3.Y;
   }
}
} // namespace booleanrectangles
} // namespace core
} // namespace zombie
