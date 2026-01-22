#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/math/LinearTransformation/VerticalLinearTransformation.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"

namespace com {
namespace google {
namespace common {
namespace math {


class LinearTransformation {
public:
    const double slope;
    const double yIntercept;
    LinearTransformation inverse;

   LinearTransformation$RegularLinearTransformation(double slope, double yIntercept) {
      this.slope = slope;
      this.yIntercept = yIntercept;
      this.inverse = nullptr;
   }

   LinearTransformation$RegularLinearTransformation(double slope, double yIntercept, LinearTransformation inverse) {
      this.slope = slope;
      this.yIntercept = yIntercept;
      this.inverse = inverse;
   }

    bool isVertical() {
    return false;
   }

    bool isHorizontal() {
      return this.slope == 0.0;
   }

    double slope() {
      return this.slope;
   }

    double transform(double x) {
      return x * this.slope + this.yIntercept;
   }

    LinearTransformation inverse() {
    LinearTransformation result = this.inverse;
    return result = = nullptr ? (this.inverse = this.createInverse()) : result;
   }

    std::string toString() {
      return std::string.format("y = %g * x + %g", this.slope, this.yIntercept);
   }

    LinearTransformation createInverse() {
      return (LinearTransformation)(this.slope != 0.0
         ? new LinearTransformation$RegularLinearTransformation(1.0 / this.slope, -1.0 * this.yIntercept / this.slope, this)
         : std::make_shared<VerticalLinearTransformation>(this.yIntercept, this));
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
