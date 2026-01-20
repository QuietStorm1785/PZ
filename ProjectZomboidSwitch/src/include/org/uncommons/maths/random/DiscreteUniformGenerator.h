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


class DiscreteUniformGenerator {
public:
    const Random rng;
    const int range;
    const int minimumValue;

    public DiscreteUniformGenerator(int minimumValue, int maximumValue, Random rng) {
      this.rng = rng;
      this.minimumValue = minimumValue;
      this.range = maximumValue - minimumValue + 1;
   }

    int nextValue() {
      return this.rng.nextInt(this.range) + this.minimumValue;
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
