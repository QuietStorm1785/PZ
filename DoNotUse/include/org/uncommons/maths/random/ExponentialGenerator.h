#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/uncommons/maths/number/ConstantGenerator.h"
#include "org/uncommons/maths/number/NumberGenerator.h"
#include <algorithm>

namespace org {
namespace uncommons {
namespace maths {
namespace random {


class ExponentialGenerator {
public:
   private const NumberGenerator<double> rate;
    const Random rng;

    public ExponentialGenerator(NumberGenerator<double> rate, Random rng) {
      this.rate = rate;
      this.rng = rng;
   }

    public ExponentialGenerator(double rate, Random rng) {
      this(std::make_shared<ConstantGenerator>(rate), rng);
   }

    double nextValue() {
    double u;
      do {
         u = this.rng.nextDouble();
      } while (u == 0.0);

      return -Math.log(u) / (double)this.rate.nextValue();
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
