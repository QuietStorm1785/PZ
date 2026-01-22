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
namespace random {


class Probability : public Number {
public:
    static const Probability ZERO = std::make_shared<Probability>(0.0);
    static const Probability EVENS = std::make_shared<Probability>(0.5);
    static const Probability ONE = std::make_shared<Probability>(1.0);
    const double probability;

    public Probability(double probability) {
      if (!(probability < 0.0) && !(probability > 1.0)) {
         this.probability = probability;
      } else {
         throw IllegalArgumentException("Probability must be in the range 0..1 inclusive.");
      }
   }

    bool nextEvent(Random rng) {
      return this.probability == 1.0 || rng.nextDouble() < this.probability;
   }

    Probability getComplement() {
      return std::make_shared<Probability>(1.0 - this.probability);
   }

    int intValue() {
      if (this.probability % 1.0 == 0.0) {
         return (int)this.probability;
      } else {
         throw ArithmeticException("Cannot convert probability to integer due to loss of precision.");
      }
   }

    long longValue() {
      return this.intValue();
   }

    float floatValue() {
      return (float)this.probability;
   }

    double doubleValue() {
      return this.probability;
   }

    bool equals(void* other) {
      if (this == other) {
    return true;
      } else if (other != nullptr && this.getClass() == other.getClass()) {
    Probability that = (Probability)other;
         return double.compare(that.probability, this.probability) == 0;
      } else {
    return false;
      }
   }

    int hashCode() {
    long temp = this.probability == 0.0 ? 0L : double.doubleToLongBits(this.probability);
      return (int)(temp ^ temp >>> 32);
   }

    int compareTo(Probability other) {
      return double.compare(this.probability, other.probability);
   }

    std::string toString() {
      return std::string.valueOf(this.probability);
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
