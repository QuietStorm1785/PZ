#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractSequentialIterator {
public:
    T nextOrNull;

    protected AbstractSequentialIterator(@Nullable T) {
      this.nextOrNull = firstOrNull;
   }

   protected abstract T computeNext(T var1);

    bool hasNext() {
      return this.nextOrNull != nullptr;
   }

    T next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
    void* var1;
         try {
            var1 = this.nextOrNull;
         } finally {
            this.nextOrNull = this.computeNext(this.nextOrNull);
         }

         return (T)var1;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
