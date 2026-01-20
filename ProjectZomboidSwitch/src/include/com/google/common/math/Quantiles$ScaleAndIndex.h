#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/primitives/Doubles.h"
#include "java/math/RoundingMode.h"

namespace com {
namespace google {
namespace common {
namespace math {


class Quantiles {
public:
    const int scale;
    const int index;

   private Quantiles$ScaleAndIndex(int scale, int index) {
      Quantiles.access$300(index, scale);
      this.scale = scale;
      this.index = index;
   }

    double compute(Collection<? extends) {
      return this.computeInPlace(Doubles.toArray(dataset));
   }

    double compute(double... dataset) {
      return this.computeInPlace((double[])dataset.clone());
   }

    double compute(long... dataset) {
      return this.computeInPlace(Quantiles.access$400(dataset));
   }

    double compute(int... dataset) {
      return this.computeInPlace(Quantiles.access$500(dataset));
   }

    double computeInPlace(double... dataset) {
      Preconditions.checkArgument(dataset.length > 0, "Cannot calculate quantiles of an empty dataset");
      if (Quantiles.access$600(dataset)) {
         return double.NaN;
      } else {
    long numerator = (long)this.index * (dataset.length - 1);
    int quotient = (int)LongMath.divide(numerator, this.scale, RoundingMode.DOWN);
    int remainder = (int)(numerator - (long)quotient * this.scale);
         Quantiles.access$700(quotient, dataset, 0, dataset.length - 1);
         if (remainder == 0) {
            return dataset[quotient];
         } else {
            Quantiles.access$700(quotient + 1, dataset, quotient + 1, dataset.length - 1);
            return Quantiles.access$800(dataset[quotient], dataset[quotient + 1], remainder, this.scale);
         }
      }
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
