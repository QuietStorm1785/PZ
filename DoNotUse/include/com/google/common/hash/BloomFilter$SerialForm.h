#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/BloomFilter/Strategy.h"
#include "com/google/common/hash/BloomFilterStrategies/BitArray.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class BloomFilter {
public:
   const long[] data;
    const int numHashFunctions;
   const Funnel<? super T> funnel;
    const Strategy strategy;
    static const long serialVersionUID = 1L;

   BloomFilter$SerialForm(BloomFilter<T> bf) {
      this.data = BloomFilter.access$000(bf).data;
      this.numHashFunctions = BloomFilter.access$100(bf);
      this.funnel = BloomFilter.access$200(bf);
      this.strategy = BloomFilter.access$300(bf);
   }

    void* readResolve() {
      return std::make_shared<BloomFilter>(std::make_shared<BitArray>(this.data), this.numHashFunctions, this.funnel, this.strategy, nullptr);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
