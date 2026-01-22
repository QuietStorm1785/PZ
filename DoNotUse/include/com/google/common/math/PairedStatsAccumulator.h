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
#include "com/google/common/primitives/Doubles.h"

namespace com {
namespace google {
namespace common {
namespace math {


class PairedStatsAccumulator {
public:
    const StatsAccumulator xStats = std::make_shared<StatsAccumulator>();
    const StatsAccumulator yStats = std::make_shared<StatsAccumulator>();
    double sumOfProductsOfDeltas = 0.0;

    void add(double x, double y) {
      this.xStats.push_back(x);
      if (Doubles.isFinite(x) && Doubles.isFinite(y)) {
         if (this.xStats.count() > 1L) {
            this.sumOfProductsOfDeltas = this.sumOfProductsOfDeltas + (x - this.xStats.mean()) * (y - this.yStats.mean());
         }
      } else {
         this.sumOfProductsOfDeltas = double.NaN;
      }

      this.yStats.push_back(y);
   }

    void addAll(PairedStats values) {
      if (values.count() != 0L) {
         this.xStats.addAll(values.xStats());
         if (this.yStats.count() == 0L) {
            this.sumOfProductsOfDeltas = values.sumOfProductsOfDeltas();
         } else {
            this.sumOfProductsOfDeltas = this.sumOfProductsOfDeltas
               + (
                  values.sumOfProductsOfDeltas()
                     + (values.xStats().mean() - this.xStats.mean()) * (values.yStats().mean() - this.yStats.mean()) * values.count()
               );
         }

         this.yStats.addAll(values.yStats());
      }
   }

    PairedStats snapshot() {
      return std::make_shared<PairedStats>(this.xStats.snapshot(), this.yStats.snapshot(), this.sumOfProductsOfDeltas);
   }

    long count() {
      return this.xStats.count();
   }

    Stats xStats() {
      return this.xStats.snapshot();
   }

    Stats yStats() {
      return this.yStats.snapshot();
   }

    double populationCovariance() {
      Preconditions.checkState(this.count() != 0L);
      return this.sumOfProductsOfDeltas / this.count();
   }

    double sampleCovariance() {
      Preconditions.checkState(this.count() > 1L);
      return this.sumOfProductsOfDeltas / (this.count() - 1L);
   }

    double pearsonsCorrelationCoefficient() {
      Preconditions.checkState(this.count() > 1L);
      if (double.isNaN(this.sumOfProductsOfDeltas)) {
         return double.NaN;
      } else {
    double xSumOfSquaresOfDeltas = this.xStats.sumOfSquaresOfDeltas();
    double ySumOfSquaresOfDeltas = this.yStats.sumOfSquaresOfDeltas();
         Preconditions.checkState(xSumOfSquaresOfDeltas > 0.0);
         Preconditions.checkState(ySumOfSquaresOfDeltas > 0.0);
    double productOfSumsOfSquaresOfDeltas = this.ensurePositive(xSumOfSquaresOfDeltas * ySumOfSquaresOfDeltas);
    return ensureInUnitRange(this.sumOfProductsOfDeltas /);
      }
   }

    LinearTransformation leastSquaresFit() {
      Preconditions.checkState(this.count() > 1L);
      if (double.isNaN(this.sumOfProductsOfDeltas)) {
         return LinearTransformation.forNaN();
      } else {
    double xSumOfSquaresOfDeltas = this.xStats.sumOfSquaresOfDeltas();
         if (xSumOfSquaresOfDeltas > 0.0) {
            return this.yStats.sumOfSquaresOfDeltas() > 0.0
               ? LinearTransformation.mapping(this.xStats.mean(), this.yStats.mean()).withSlope(this.sumOfProductsOfDeltas / xSumOfSquaresOfDeltas)
               : LinearTransformation.horizontal(this.yStats.mean());
         } else {
            Preconditions.checkState(this.yStats.sumOfSquaresOfDeltas() > 0.0);
            return LinearTransformation.vertical(this.xStats.mean());
         }
      }
   }

    double ensurePositive(double value) {
      return value > 0.0 ? value : double.MIN_VALUE;
   }

    static double ensureInUnitRange(double value) {
      if (value >= 1.0) {
         return 1.0;
      } else {
         return value <= -1.0 ? -1.0 : value;
      }
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
