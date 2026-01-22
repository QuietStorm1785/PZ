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


class GaussianGenerator {
public:
    const Random rng;
   private const NumberGenerator<double> mean;
   private const NumberGenerator<double> standardDeviation;

    public GaussianGenerator(NumberGenerator<double> mean, NumberGenerator<double> standardDeviation, Random rng) {
      this.mean = mean;
      this.standardDeviation = standardDeviation;
      this.rng = rng;
   }

    public GaussianGenerator(double mean, double standardDeviation, Random rng) {
      this(std::make_shared<ConstantGenerator>(mean), std::make_shared<ConstantGenerator>(standardDeviation), rng);
   }

    double nextValue() {
      return this.rng.nextGaussian() * (double)this.standardDeviation.nextValue() + (double)this.mean.nextValue();
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
