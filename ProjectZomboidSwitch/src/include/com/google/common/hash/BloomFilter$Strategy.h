#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/BloomFilterStrategies/BitArray.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class BloomFilter {
public:
    virtual ~BloomFilter() = default;
   <T> boolean put(T var1, Funnel<? super T> var2, int var3, BitArray var4);

   <T> boolean mightContain(T var1, Funnel<? super T> var2, int var3, BitArray var4);

    int ordinal();
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
