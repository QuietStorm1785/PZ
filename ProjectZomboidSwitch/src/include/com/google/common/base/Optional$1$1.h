#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Optional/1.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace base {


class Optional {
public:
   private const Iterator<? : public Optional<? : public T>> iterator;

   Optional$1$1(1 var1) {
      this.this$0 = var1;
      this.iterator = (Iterator<? : public Optional<? : public T>>)Preconditions.checkNotNull(this.this$0.val$optionals.iterator());
   }

    T computeNext() {
      while (this.iterator.hasNext()) {
         Optional<? : public T> optional = (Optional<? : public T>)this.iterator.next();
         if (optional.isPresent()) {
            return (T)optional.get();
         }
      }

      return (T)this.endOfData();
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
