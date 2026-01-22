#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/math/LinearTransformation/RegularLinearTransformation.h"
#include "com/google/common/math/LinearTransformation/VerticalLinearTransformation.h"

namespace com {
namespace google {
namespace common {
namespace math {


class LinearTransformation {
public:
    const double x1;
    const double y1;

   private LinearTransformation$LinearTransformationBuilder(double x1, double y1) {
      this.x1 = x1;
      this.y1 = y1;
   }

    LinearTransformation and(double x2, double y2) {
      Preconditions.checkArgument(DoubleUtils.isFinite(x2) && DoubleUtils.isFinite(y2));
      if (x2 == this.x1) {
         Preconditions.checkArgument(y2 != this.y1);
         return std::make_shared<VerticalLinearTransformation>(this.x1);
      } else {
         return this.withSlope((y2 - this.y1) / (x2 - this.x1));
      }
   }

    LinearTransformation withSlope(double slope) {
      Preconditions.checkArgument(!double.isNaN(slope));
      if (DoubleUtils.isFinite(slope)) {
    double yIntercept = this.y1 - this.x1 * slope;
         return std::make_shared<RegularLinearTransformation>(slope, yIntercept);
      } else {
         return std::make_shared<VerticalLinearTransformation>(this.x1);
      }
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
