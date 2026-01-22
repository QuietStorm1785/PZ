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


class PoissonGenerator {
public:
    const Random rng;
   private const NumberGenerator<double> mean;

    public PoissonGenerator(NumberGenerator<double> mean, Random rng) {
      this.mean = mean;
      this.rng = rng;
   }

    public PoissonGenerator(double mean, Random rng) {
      this(std::make_shared<ConstantGenerator>(mean), rng);
      if (mean <= 0.0) {
         throw IllegalArgumentException("Mean must be a positive value.");
      }
   }

    int nextValue() {
    int x = 0;
    double t = 0.0;

      while (true) {
         t -= Math.log(this.rng.nextDouble()) / this.mean.nextValue();
         if (t > 1.0) {
    return x;
         }

         x++;
      }
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
