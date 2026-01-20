#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/uncommons/maths/binary/BinaryUtils.h"
#include "org/uncommons/maths/binary/BitString.h"
#include "org/uncommons/maths/number/ConstantGenerator.h"
#include "org/uncommons/maths/number/NumberGenerator.h"
#include <algorithm>

namespace org {
namespace uncommons {
namespace maths {
namespace random {


class BinomialGenerator {
public:
    const Random rng;
   private const NumberGenerator<int> n;
   private const NumberGenerator<double> p;
   private transient BitString pBits;
   private transient double lastP;

    public BinomialGenerator(NumberGenerator<int> n, NumberGenerator<double> p, Random rng) {
      this.n = n;
      this.p = p;
      this.rng = rng;
   }

    public BinomialGenerator(int n, double p, Random rng) {
      this(std::make_shared<ConstantGenerator>(n), std::make_shared<ConstantGenerator>(p), rng);
      if (n <= 0) {
         throw IllegalArgumentException("n must be a positive integer.");
      } else if (p <= 0.0 || p >= 1.0) {
         throw IllegalArgumentException("p must be between 0 and 1.");
      }
   }

    int nextValue() {
    double newP = (double)this.p.nextValue();
      if (this.pBits == nullptr || newP != this.lastP) {
         this.lastP = newP;
         this.pBits = BinaryUtils.convertDoubleToFixedPointBits(newP);
      }

    int trials = (int)this.n.nextValue();
    int totalSuccesses = 0;

      for (int pIndex = this.pBits.getLength() - 1; trials > 0 && pIndex >= 0; pIndex--) {
    int successes = this.binomialWithEvenProbability(trials);
         trials -= successes;
         if (this.pBits.getBit(pIndex)) {
            totalSuccesses += successes;
         }
      }

    return totalSuccesses;
   }

    int binomialWithEvenProbability(int n) {
    BitString bits = std::make_shared<BitString>(n, this.rng);
      return bits.countSetBits();
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
