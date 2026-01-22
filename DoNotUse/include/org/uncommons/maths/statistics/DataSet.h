#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace org {
namespace uncommons {
namespace maths {
namespace statistics {


class DataSet {
public:
    static const int DEFAULT_CAPACITY = 50;
    static const double GROWTH_RATE = 1.5;
   private double[] dataSet;
    int dataSetSize = 0;
    double total = 0.0;
    double product = 1.0;
    double reciprocalSum = 0.0;
    double minimum = double.MAX_VALUE;
    double maximum = double.MIN_VALUE;

    public DataSet() {
      this(50);
   }

    public DataSet(int capacity) {
      this.dataSet = new double[capacity];
      this.dataSetSize = 0;
   }

    public DataSet(double[] dataSet) {
      this.dataSet = (double[])dataSet.clone();
      this.dataSetSize = dataSet.length;

      for (double value : this.dataSet) {
         this.updateStatsWithNewValue(value);
      }
   }

    void addValue(double value) {
      if (this.dataSetSize == this.dataSet.length) {
    int newLength = (int)(1.5 * this.dataSetSize);
         double[] newDataSet = new double[newLength];
         System.arraycopy(this.dataSet, 0, newDataSet, 0, this.dataSetSize);
         this.dataSet = newDataSet;
      }

      this.dataSet[this.dataSetSize] = value;
      this.updateStatsWithNewValue(value);
      this.dataSetSize++;
   }

    void updateStatsWithNewValue(double value) {
      this.total += value;
      this.product *= value;
      this.reciprocalSum += 1.0 / value;
      this.minimum = Math.min(this.minimum, value);
      this.maximum = Math.max(this.maximum, value);
   }

    void assertNotEmpty() {
      if (this.getSize() == 0) {
         throw std::make_unique<EmptyDataSetException>();
      }
   }

    int getSize() {
      return this.dataSetSize;
   }

    double getMinimum() {
      this.assertNotEmpty();
      return this.minimum;
   }

    double getMaximum() {
      this.assertNotEmpty();
      return this.maximum;
   }

    double getMedian() {
      this.assertNotEmpty();
      double[] dataCopy = new double[this.getSize()];
      System.arraycopy(this.dataSet, 0, dataCopy, 0, dataCopy.length);
      Arrays.sort(dataCopy);
    int midPoint = dataCopy.length / 2;
      return dataCopy.length % 2 != 0 ? dataCopy[midPoint] : dataCopy[midPoint - 1] + (dataCopy[midPoint] - dataCopy[midPoint - 1]) / 2.0;
   }

    double getAggregate() {
      this.assertNotEmpty();
      return this.total;
   }

    double getProduct() {
      this.assertNotEmpty();
      return this.product;
   }

    double getArithmeticMean() {
      this.assertNotEmpty();
      return this.total / this.dataSetSize;
   }

    double getGeometricMean() {
      this.assertNotEmpty();
      return Math.pow(this.product, 1.0 / this.dataSetSize);
   }

    double getHarmonicMean() {
      this.assertNotEmpty();
      return this.dataSetSize / this.reciprocalSum;
   }

    double getMeanDeviation() {
    double mean = this.getArithmeticMean();
    double diffs = 0.0;

      for (int i = 0; i < this.dataSetSize; i++) {
         diffs += Math.abs(mean - this.dataSet[i]);
      }

      return diffs / this.dataSetSize;
   }

    double getVariance() {
      return this.sumSquaredDiffs() / this.getSize();
   }

    double sumSquaredDiffs() {
    double mean = this.getArithmeticMean();
    double squaredDiffs = 0.0;

      for (int i = 0; i < this.getSize(); i++) {
    double diff = mean - this.dataSet[i];
         squaredDiffs += diff * diff;
      }

    return squaredDiffs;
   }

    double getStandardDeviation() {
      return Math.sqrt(this.getVariance());
   }

    double getSampleVariance() {
      return this.sumSquaredDiffs() / (this.getSize() - 1);
   }

    double getSampleStandardDeviation() {
      return Math.sqrt(this.getSampleVariance());
   }
}
} // namespace statistics
} // namespace maths
} // namespace uncommons
} // namespace org
