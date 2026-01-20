#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class LongAddables {
public:
   private LongAddables$PureJavaLongAddable() {
   }

    void increment() {
      this.getAndIncrement();
   }

    void add(long x) {
      this.getAndAdd(x);
   }

    long sum() {
      return this.get();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
