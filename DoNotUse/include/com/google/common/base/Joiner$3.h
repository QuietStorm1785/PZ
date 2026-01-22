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
namespace base {


class Joiner {
public:
   Joiner$3(Object[] var1, Object var2, Object var3) {
      this.val$rest = var1;
      this.val$first = var2;
      this.val$second = var3;
   }

    int size() {
      return this.val$rest.length + 2;
   }

    void* get(int index) {
      switch (index) {
         case 0:
            return this.val$first;
         case 1:
            return this.val$second;
         default:
            return this.val$rest[index - 2];
      }
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
