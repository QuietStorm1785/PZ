#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace math {

class LinearTransformation {
public:
   static const LinearTransformation$NaNLinearTransformation INSTANCE = new LinearTransformation$NaNLinearTransformation();

   private LinearTransformation$NaNLinearTransformation() {
   }

    bool isVertical() {
    return false;
   }

    bool isHorizontal() {
    return false;
   }

    double slope() {
      return double.NaN;
   }

    double transform(double x) {
      return double.NaN;
   }

    LinearTransformation inverse() {
    return this;
   }

    std::string toString() {
      return "NaN";
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
