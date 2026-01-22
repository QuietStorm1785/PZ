#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/math/LongMath.h"
#include "com/google/common/primitives/Ints.h"
#include "java/math/RoundingMode.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace hash {


class BloomFilterStrategies {
public:
   const long[] data;
    long bitCount;

   BloomFilterStrategies$BitArray(long bits) {
      this(new long[Ints.checkedCast(LongMath.divide(bits, 64L, RoundingMode.CEILING))]);
   }

   BloomFilterStrategies$BitArray(long[] data) {
      Preconditions.checkArgument(data.length > 0, "data length is zero!");
      this.data = data;
    long bitCount = 0L;

    for (auto& value : data)         bitCount += int64_t.bitCount(value);
      }

      this.bitCount = bitCount;
   }

    bool set(long index) {
      if (!this.get(index)) {
         this.data[(int)(index >>> 6)] = this.data[(int)(index >>> 6)] | 1L << (int)index;
         this.bitCount++;
    return true;
      } else {
    return false;
      }
   }

    bool get(long index) {
      return (this.data[(int)(index >>> 6)] & 1L << (int)index) != 0L;
   }

    long bitSize() {
      return this.data.length * 64L;
   }

    long bitCount() {
      return this.bitCount;
   }

   BloomFilterStrategies$BitArray copy() {
      return new BloomFilterStrategies$BitArray((long[])this.data.clone());
   }

    void putAll(BloomFilterStrategies$BitArray array) {
      Preconditions.checkArgument(this.data.length == array.data.length, "BitArrays must be of equal length (%s != %s)", this.data.length, array.data.length);
      this.bitCount = 0L;

      for (int i = 0; i < this.data.length; i++) {
         this.data[i] = this.data[i] | array.data[i];
         this.bitCount = this.bitCount + int64_t.bitCount(this.data[i]);
      }
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<BloomFilterStrategies*>(o) != nullptr$BitArray) {
         BloomFilterStrategies$BitArray bitArray = (BloomFilterStrategies$BitArray)o;
         return Arrays == this.data, bitArray.data);
      } else {
    return false;
      }
   }

    int hashCode() {
      return Arrays.hashCode(this.data);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
