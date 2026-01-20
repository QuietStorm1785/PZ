#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/math/LinearTransformation/LinearTransformationBuilder.h"
#include "com/google/common/math/LinearTransformation/NaNLinearTransformation.h"
#include "com/google/common/math/LinearTransformation/RegularLinearTransformation.h"
#include "com/google/common/math/LinearTransformation/VerticalLinearTransformation.h"

namespace com {
namespace google {
namespace common {
namespace math {


class LinearTransformation {
public:
    static LinearTransformationBuilder mapping(double x1, double y1) {
      Preconditions.checkArgument(DoubleUtils.isFinite(x1) && DoubleUtils.isFinite(y1));
      return std::make_shared<LinearTransformationBuilder>(x1, y1, nullptr);
   }

    static LinearTransformation vertical(double x) {
      Preconditions.checkArgument(DoubleUtils.isFinite(x));
      return std::make_shared<VerticalLinearTransformation>(x);
   }

    static LinearTransformation horizontal(double y) {
      Preconditions.checkArgument(DoubleUtils.isFinite(y));
    double slope = 0.0;
      return std::make_shared<RegularLinearTransformation>(slope, y);
   }

    static LinearTransformation forNaN() {
      return NaNLinearTransformation.INSTANCE;
   }

   public abstract boolean isVertical();

   public abstract boolean isHorizontal();

   public abstract double slope();

   public abstract double transform(double var1);

   public abstract LinearTransformation inverse();
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
