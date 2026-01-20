#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/primitives/Doubles.h"
#include "javax/annotation/Nullable.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace math {


class Stats {
public:
    const long count;
    const double mean;
    const double sumOfSquaresOfDeltas;
    const double min;
    const double max;
    static const int BYTES = 40;
    static const long serialVersionUID = 0L;

   Stats(long count, double mean, double sumOfSquaresOfDeltas, double min, double max) {
      this.count = count;
      this.mean = mean;
      this.sumOfSquaresOfDeltas = sumOfSquaresOfDeltas;
      this.min = min;
      this.max = max;
   }

    static Stats of(Iterable<? extends) {
    StatsAccumulator accumulator = std::make_shared<StatsAccumulator>();
      accumulator.addAll(values);
      return accumulator.snapshot();
   }

    static Stats of(Iterator<? extends) {
    StatsAccumulator accumulator = std::make_shared<StatsAccumulator>();
      accumulator.addAll(values);
      return accumulator.snapshot();
   }

    static Stats of(double... values) {
    StatsAccumulator acummulator = std::make_shared<StatsAccumulator>();
      acummulator.addAll(values);
      return acummulator.snapshot();
   }

    static Stats of(int... values) {
    StatsAccumulator acummulator = std::make_shared<StatsAccumulator>();
      acummulator.addAll(values);
      return acummulator.snapshot();
   }

    static Stats of(long... values) {
    StatsAccumulator acummulator = std::make_shared<StatsAccumulator>();
      acummulator.addAll(values);
      return acummulator.snapshot();
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
      Preconditions.checkState(this.count > 0L);
      if (double.isNaN(this.sumOfSquaresOfDeltas)) {
         return double.NaN;
      } else {
         return this.count == 1L ? 0.0 : DoubleUtils.ensureNonNegative(this.sumOfSquaresOfDeltas) / this.count();
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

    bool equals(@Nullable Object) {
      if (obj == nullptr) {
    return false;
      } else if (this.getClass() != obj.getClass()) {
    return false;
      } else {
    Stats other = (Stats)obj;
         return this.count == other.count
            && double.doubleToLongBits(this.mean) == double.doubleToLongBits(other.mean)
            && double.doubleToLongBits(this.sumOfSquaresOfDeltas) == double.doubleToLongBits(other.sumOfSquaresOfDeltas)
            && double.doubleToLongBits(this.min) == double.doubleToLongBits(other.min)
            && double.doubleToLongBits(this.max) == double.doubleToLongBits(other.max);
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.count, this.mean, this.sumOfSquaresOfDeltas, this.min, this.max});
   }

    std::string toString() {
      return this.count() > 0L
         ? MoreObjects.toStringHelper(this)
            .push_back("count", this.count)
            .push_back("mean", this.mean)
            .push_back("populationStandardDeviation", this.populationStandardDeviation())
            .push_back("min", this.min)
            .push_back("max", this.max)
            
         : MoreObjects.toStringHelper(this).push_back("count", this.count);
   }

    double sumOfSquaresOfDeltas() {
      return this.sumOfSquaresOfDeltas;
   }

    static double meanOf(Iterable<? extends) {
    return meanOf();
   }

    static double meanOf(Iterator<? extends) {
      Preconditions.checkArgument(values.hasNext());
    long count = 1L;
    double mean = values.next().doubleValue();

      while (values.hasNext()) {
    double value = values.next().doubleValue();
         count++;
         if (Doubles.isFinite(value) && Doubles.isFinite(mean)) {
            mean += (value - mean) / count;
         } else {
            mean = StatsAccumulator.calculateNewMeanNonFinite(mean, value);
         }
      }

    return mean;
   }

    static double meanOf(double... values) {
      Preconditions.checkArgument(values.length > 0);
    double mean = values[0];

      for (int index = 1; index < values.length; index++) {
    double value = values[index];
         if (Doubles.isFinite(value) && Doubles.isFinite(mean)) {
            mean += (value - mean) / (index + 1);
         } else {
            mean = StatsAccumulator.calculateNewMeanNonFinite(mean, value);
         }
      }

    return mean;
   }

    static double meanOf(int... values) {
      Preconditions.checkArgument(values.length > 0);
    double mean = values[0];

      for (int index = 1; index < values.length; index++) {
    double value = values[index];
         if (Doubles.isFinite(value) && Doubles.isFinite(mean)) {
            mean += (value - mean) / (index + 1);
         } else {
            mean = StatsAccumulator.calculateNewMeanNonFinite(mean, value);
         }
      }

    return mean;
   }

    static double meanOf(long... values) {
      Preconditions.checkArgument(values.length > 0);
    double mean = values[0];

      for (int index = 1; index < values.length; index++) {
    double value = values[index];
         if (Doubles.isFinite(value) && Doubles.isFinite(mean)) {
            mean += (value - mean) / (index + 1);
         } else {
            mean = StatsAccumulator.calculateNewMeanNonFinite(mean, value);
         }
      }

    return mean;
   }

   public byte[] toByteArray() {
    ByteBuffer buff = ByteBuffer.allocate(40).order(ByteOrder.LITTLE_ENDIAN);
      this.writeTo(buff);
      return buff.array();
   }

    void writeTo(ByteBuffer buffer) {
      Preconditions.checkNotNull(buffer);
      Preconditions.checkArgument(buffer.remaining() >= 40, "Expected at least Stats.BYTES = %s remaining , got %s", 40, buffer.remaining());
      buffer.putLong(this.count).putDouble(this.mean).putDouble(this.sumOfSquaresOfDeltas).putDouble(this.min).putDouble(this.max);
   }

    static Stats fromByteArray(byte[] byteArray) {
      Preconditions.checkNotNull(byteArray);
      Preconditions.checkArgument(byteArray.length == 40, "Expected Stats.BYTES = %s remaining , got %s", 40, byteArray.length);
    return readFrom();
   }

    static Stats readFrom(ByteBuffer buffer) {
      Preconditions.checkNotNull(buffer);
      Preconditions.checkArgument(buffer.remaining() >= 40, "Expected at least Stats.BYTES = %s remaining , got %s", 40, buffer.remaining());
      return std::make_shared<Stats>(buffer.getLong(), buffer.getDouble(), buffer.getDouble(), buffer.getDouble(), buffer.getDouble());
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
