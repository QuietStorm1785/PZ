#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/list/PZPrimitiveArrayIterable/1.h"
#include <iterator>

namespace zombie {
namespace util {
namespace list {


class PZPrimitiveArrayIterable {
public:
    int pos;

   PZPrimitiveArrayIterable$1$1(1 var1) {
      this.this$0 = var1;
      this.pos = 0;
   }

    bool hasNext() {
      return this.this$0.m_list.length > this.pos;
   }

    float next() {
      return this.this$0.m_list[this.pos++];
   }
}
} // namespace list
} // namespace util
} // namespace zombie
