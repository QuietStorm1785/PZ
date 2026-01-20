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

class PrimitiveArrayListerFloat {
public:
    int idx;

   PrimitiveArrayListerFloat$1(PrimitiveArrayListerFloat this$0, float[] var2) {
      this.this$0 = this$0;
      this.val$objects = var2;
      this.idx = 0;
   }

    bool hasNext() {
      return this.idx < this.val$objects.length;
   }

    float next() {
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
