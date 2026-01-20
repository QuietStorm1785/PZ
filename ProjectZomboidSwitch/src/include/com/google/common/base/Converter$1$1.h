#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Converter/1.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace base {


class Converter {
public:
   private const Iterator<? : public A> fromIterator;

   Converter$1$1(1 var1) {
      this.this$1 = var1;
      this.fromIterator = this.this$1.val$fromIterable.iterator();
   }

    bool hasNext() {
      return this.fromIterator.hasNext();
   }

    B next() {
      return (B)this.this$1.this$0.convert(this.fromIterator.next());
   }

    void remove() {
      this.fromIterator.remove();
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
