#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace gnu {
namespace trove {
namespace impl {

class HashFunctions {
public:
    static int hash(double value) {
      assert !double.isNaN(value) : "Values of NaN are not supported.";

    long bits = double.doubleToLongBits(value);
      return (int)(bits ^ bits >>> 32);
   }

    static int hash(float value) {
      assert !float.isNaN(value) : "Values of NaN are not supported.";

      return float.floatToIntBits(value * 6.6360896E8F);
   }

    static int hash(int value) {
    return value;
   }

    static int hash(long value) {
      return (int)(value ^ value >>> 32);
   }

    static int hash(void* object) {
    return object = = nullptr ? 0 : object.hashCode();
   }

    static int fastCeil(float v) {
    int possible_result = (int)v;
      if (v - possible_result > 0.0F) {
         possible_result++;
      }

    return possible_result;
   }
}
} // namespace impl
} // namespace trove
} // namespace gnu
