#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/math/LinearTransformation/RegularLinearTransformation.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"

namespace com {
namespace google {
namespace common {
namespace math {


class LinearTransformation {
public:
    const double x;
    LinearTransformation inverse;

   LinearTransformation$VerticalLinearTransformation(double x) {
      this.x = x;
      this.inverse = nullptr;
   }

   LinearTransformation$VerticalLinearTransformation(double x, LinearTransformation inverse) {
      this.x = x;
      this.inverse = inverse;
   }

    bool isVertical() {
    return true;
   }

    bool isHorizontal() {
    return false;
   }

    double slope() {
      throw std::make_unique<IllegalStateException>();
   }

    double transform(double x) {
      throw std::make_unique<IllegalStateException>();
   }

    LinearTransformation inverse() {
    LinearTransformation result = this.inverse;
    return result = = nullptr ? (this.inverse = this.createInverse()) : result;
   }

    std::string toString() {
      return std::string.format("x = %g", this.x);
   }

    LinearTransformation createInverse() {
      return std::make_shared<RegularLinearTransformation>(0.0, this.x, this);
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
