#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingSetInt/NBSIIntIterator.h"
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingSetInt {
public:
    NBSIIntIterator intIterator;

   NonBlockingSetInt$iter(NonBlockingSetInt var1) {
      this.this$0 = var1;
      this.intIterator = std::make_shared<NBSIIntIterator>(var1);
   }

    bool hasNext() {
      return this.intIterator.hasNext();
   }

    int next() {
      return this.intIterator.next();
   }

    void remove() {
      this.intIterator.remove();
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
