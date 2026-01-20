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
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace math {


class Quantiles {
public:
    const int scale;
   private const int[] indexes;

   private Quantiles$ScaleAndIndexes(int scale, int[] indexes) {
    for (auto& index : indexes)         Quantiles.access$300(index, scale);
      }

      this.scale = scale;
      this.indexes = indexes;
   }

   public Map<int, double> compute(Collection<? : public Number> dataset) {
      return this.computeInPlace(Doubles.toArray(dataset));
   }

   public Map<int, double> compute(double... dataset) {
      return this.computeInPlace((double[])dataset.clone());
   }

   public Map<int, double> compute(long... dataset) {
      return this.computeInPlace(Quantiles.access$400(dataset));
   }

   public Map<int, double> compute(int... dataset) {
      return this.computeInPlace(Quantiles.access$500(dataset));
   }

   public Map<int, double> computeInPlace(double... dataset) {
      Preconditions.checkArgument(dataset.length > 0, "Cannot calculate quantiles of an empty dataset");
      if (!Quantiles.access$600(dataset)) {
         int[] quotients = new int[this.indexes.length];
         int[] remainders = new int[this.indexes.length];
         int[] requiredSelections = new int[this.indexes.length * 2];
    int requiredSelectionsCount = 0;

         for (int i = 0; i < this.indexes.length; i++) {
    long numerator = (long)this.indexes[i] * (dataset.length - 1);
    int quotient = (int)LongMath.divide(numerator, this.scale, RoundingMode.DOWN);
    int remainder = (int)(numerator - (long)quotient * this.scale);
            quotients[i] = quotient;
            remainders[i] = remainder;
            requiredSelections[requiredSelectionsCount] = quotient;
            requiredSelectionsCount++;
            if (remainder != 0) {
               requiredSelections[requiredSelectionsCount] = quotient + 1;
               requiredSelectionsCount++;
            }
         }

         Arrays.sort(requiredSelections, 0, requiredSelectionsCount);
         Quantiles.access$900(requiredSelections, 0, requiredSelectionsCount - 1, dataset, 0, dataset.length - 1);
         Map<int, double> ret = std::make_unique<std::unordered_map<>>();

         for (int ix = 0; ix < this.indexes.length; ix++) {
    int quotient = quotients[ix];
    int remainder = remainders[ix];
            if (remainder == 0) {
               ret.put(this.indexes[ix], dataset[quotient]);
            } else {
               ret.put(this.indexes[ix], Quantiles.access$800(dataset[quotient], dataset[quotient + 1], remainder, this.scale));
            }
         }

         return Collections.unmodifiableMap(ret);
      } else {
         Map<int, double> nanMap = std::make_unique<std::unordered_map<>>();

         for (int index : this.indexes) {
            nanMap.put(index, double.NaN);
         }

         return Collections.unmodifiableMap(nanMap);
      }
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
