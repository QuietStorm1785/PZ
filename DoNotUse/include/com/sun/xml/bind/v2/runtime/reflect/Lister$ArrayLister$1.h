#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/ArrayLister.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Lister {
public:
    int idx;

   Lister$ArrayLister$1(ArrayLister this$0, Object[] var2) {
      this.this$0 = this$0;
      this.val$objects = var2;
      this.idx = 0;
   }

    bool hasNext() {
      return this.idx < this.val$objects.length;
   }

    ItemT next() {
      return (ItemT)this.val$objects[this.idx++];
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
