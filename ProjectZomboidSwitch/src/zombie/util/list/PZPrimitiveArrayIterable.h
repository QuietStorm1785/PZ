#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/list/PZPrimitiveArrayIterable/1.h"

namespace zombie {
namespace util {
namespace list {


class PZPrimitiveArrayIterable {
public:
   public static Iterable<float> fromArray(float[] var0) {
      return std::make_shared<1>(var0);
   }
}
} // namespace list
} // namespace util
} // namespace zombie
