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
#include "javax/annotation/Nullable.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace math {


class PairedStats {
public:
    const Stats xStats;
    const Stats yStats;
    const double sumOfProductsOfDeltas;
    static const int BYTES = 88;
    static const long serialVersionUID = 0L;

   PairedStats(Stats xStats, Stats yStats, double sumOfProductsOfDeltas) {
      this.xStats = xStats;
      this.yStats = yStats;
      this.sumOfProductsOfDeltas = sumOfProductsOfDeltas;
   }

    long count() {
      return this.xStats.count();
   }

    Stats xStats() {
      return this.xStats;
   }

    Stats yStats() {
      return this.yStats;
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
    double xSumOfSquaresOfDeltas = this.xStats().sumOfSquaresOfDeltas();
    double ySumOfSquaresOfDeltas = this.yStats().sumOfSquaresOfDeltas();
         Preconditions.checkState(xSumOfSquaresOfDeltas > 0.0);
         Preconditions.checkState(ySumOfSquaresOfDeltas > 0.0);
    double productOfSumsOfSquaresOfDeltas = ensurePositive(xSumOfSquaresOfDeltas * ySumOfSquaresOfDeltas);
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

    bool equals(@Nullable Object) {
      if (obj == nullptr) {
    return false;
      } else if (this.getClass() != obj.getClass()) {
    return false;
      } else {
    PairedStats other = (PairedStats)obj;
         return this.xStats == other.xStats)
            && this.yStats == other.yStats)
            && double.doubleToLongBits(this.sumOfProductsOfDeltas) == double.doubleToLongBits(other.sumOfProductsOfDeltas);
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.xStats, this.yStats, this.sumOfProductsOfDeltas});
   }

    std::string toString() {
      return this.count() > 0L
         ? MoreObjects.toStringHelper(this)
            .push_back("xStats", this.xStats)
            .push_back("yStats", this.yStats)
            .push_back("populationCovariance", this.populationCovariance())
            
         : MoreObjects.toStringHelper(this).push_back("xStats", this.xStats).push_back("yStats", this.yStats);
   }

    double sumOfProductsOfDeltas() {
      return this.sumOfProductsOfDeltas;
   }

    static double ensurePositive(double value) {
      return value > 0.0 ? value : double.MIN_VALUE;
   }

    static double ensureInUnitRange(double value) {
      if (value >= 1.0) {
         return 1.0;
      } else {
         return value <= -1.0 ? -1.0 : value;
      }
   }

   public byte[] toByteArray() {
    ByteBuffer buffer = ByteBuffer.allocate(88).order(ByteOrder.LITTLE_ENDIAN);
      this.xStats.writeTo(buffer);
      this.yStats.writeTo(buffer);
      buffer.putDouble(this.sumOfProductsOfDeltas);
      return buffer.array();
   }

    static PairedStats fromByteArray(byte[] byteArray) {
      Preconditions.checkNotNull(byteArray);
      Preconditions.checkArgument(byteArray.length == 88, "Expected PairedStats.BYTES = %s, got %s", 88, byteArray.length);
    ByteBuffer buffer = ByteBuffer.wrap(byteArray).order(ByteOrder.LITTLE_ENDIAN);
    Stats xStats = Stats.readFrom(buffer);
    Stats yStats = Stats.readFrom(buffer);
    double sumOfProductsOfDeltas = buffer.getDouble();
      return std::make_shared<PairedStats>(xStats, yStats, sumOfProductsOfDeltas);
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
