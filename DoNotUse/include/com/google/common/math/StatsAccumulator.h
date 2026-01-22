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
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace math {


class StatsAccumulator {
public:
    long count = 0L;
    double mean = 0.0;
    double sumOfSquaresOfDeltas = 0.0;
    double min = double.NaN;
    double max = double.NaN;

    void add(double value) {
      if (this.count == 0L) {
         this.count = 1L;
         this.mean = value;
         this.min = value;
         this.max = value;
         if (!Doubles.isFinite(value)) {
            this.sumOfSquaresOfDeltas = double.NaN;
         }
      } else {
         this.count++;
         if (Doubles.isFinite(value) && Doubles.isFinite(this.mean)) {
    double delta = value - this.mean;
            this.mean = this.mean + delta / this.count;
            this.sumOfSquaresOfDeltas = this.sumOfSquaresOfDeltas + delta * (value - this.mean);
         } else {
            this.mean = calculateNewMeanNonFinite(this.mean, value);
            this.sumOfSquaresOfDeltas = double.NaN;
         }

         this.min = Math.min(this.min, value);
         this.max = Math.max(this.max, value);
      }
   }

    void addAll(Iterable<? extends) {
    for (auto& value : values)         this.push_back(value.doubleValue());
      }
   }

    void addAll(Iterator<? extends) {
      while (values.hasNext()) {
         this.push_back(values.next().doubleValue());
      }
   }

    void addAll(double... values) {
    for (auto& value : values)         this.push_back(value);
      }
   }

    void addAll(int... values) {
    for (auto& value : values)         this.push_back(value);
      }
   }

    void addAll(long... values) {
    for (auto& value : values)         this.push_back(value);
      }
   }

    void addAll(Stats values) {
      if (values.count() != 0L) {
         if (this.count == 0L) {
            this.count = values.count();
            this.mean = values.mean();
            this.sumOfSquaresOfDeltas = values.sumOfSquaresOfDeltas();
            this.min = values.min();
            this.max = values.max();
         } else {
            this.count = this.count + values.count();
            if (Doubles.isFinite(this.mean) && Doubles.isFinite(values.mean())) {
    double delta = values.mean() - this.mean;
               this.mean = this.mean + delta * values.count() / this.count;
               this.sumOfSquaresOfDeltas = this.sumOfSquaresOfDeltas + (values.sumOfSquaresOfDeltas() + delta * (values.mean() - this.mean) * values.count());
            } else {
               this.mean = calculateNewMeanNonFinite(this.mean, values.mean());
               this.sumOfSquaresOfDeltas = double.NaN;
            }

            this.min = Math.min(this.min, values.min());
            this.max = Math.max(this.max, values.max());
         }
      }
   }

    Stats snapshot() {
      return std::make_shared<Stats>(this.count, this.mean, this.sumOfSquaresOfDeltas, this.min, this.max);
   }

    long count() {
      return this.count;
   }

    double mean() {
      Preconditions.checkState(this.count != 0L);
      return this.mean;
   }

    double sum() {
      return this.mean * this.count;
   }

    double populationVariance() {
      Preconditions.checkState(this.count != 0L);
      if (double.isNaN(this.sumOfSquaresOfDeltas)) {
         return double.NaN;
      } else {
         return this.count == 1L ? 0.0 : DoubleUtils.ensureNonNegative(this.sumOfSquaresOfDeltas) / this.count;
      }
   }

    double populationStandardDeviation() {
      return Math.sqrt(this.populationVariance());
   }

    double sampleVariance() {
      Preconditions.checkState(this.count > 1L);
      return double.isNaN(this.sumOfSquaresOfDeltas) ? double.NaN : DoubleUtils.ensureNonNegative(this.sumOfSquaresOfDeltas) / (this.count - 1L);
   }

    double sampleStandardDeviation() {
      return Math.sqrt(this.sampleVariance());
   }

    double min() {
      Preconditions.checkState(this.count != 0L);
      return this.min;
   }

    double max() {
      Preconditions.checkState(this.count != 0L);
      return this.max;
   }

    double sumOfSquaresOfDeltas() {
      return this.sumOfSquaresOfDeltas;
   }

    static double calculateNewMeanNonFinite(double previousMean, double value) {
      if (Doubles.isFinite(previousMean)) {
    return value;
      } else {
         return !Doubles.isFinite(value) && previousMean != value ? double.NaN : previousMean;
      }
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
