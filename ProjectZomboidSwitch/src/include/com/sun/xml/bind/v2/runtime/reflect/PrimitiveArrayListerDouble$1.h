#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {

class PrimitiveArrayListerDouble {
public:
    int idx;

   PrimitiveArrayListerDouble$1(PrimitiveArrayListerDouble this$0, double[] var2) {
      this.this$0 = this$0;
      this.val$objects = var2;
      this.idx = 0;
   }

    bool hasNext() {
      return this.idx < this.val$objects.length;
   }

    double next() {
      return this.val$objects[this.idx++];
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
