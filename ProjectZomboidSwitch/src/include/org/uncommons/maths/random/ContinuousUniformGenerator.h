#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/uncommons/maths/number/NumberGenerator.h"
#include <algorithm>

namespace org {
namespace uncommons {
namespace maths {
namespace random {


class ContinuousUniformGenerator {
public:
    const Random rng;
    const double range;
    const double minimumValue;

    public ContinuousUniformGenerator(double minimumValue, double maximumValue, Random rng) {
      this.rng = rng;
      this.minimumValue = minimumValue;
      this.range = maximumValue - minimumValue;
   }

    double nextValue() {
      return this.rng.nextDouble() * this.range + this.minimumValue;
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
