#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/ZomboidAbstractMap/2.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class ZomboidAbstractMap {
public:
   private Iterator<Entry<K, V>> i;

   ZomboidAbstractMap$2$1(2 var1) {
      this.this$1 = var1;
      this.i = this.this$1.this$0.entrySet().iterator();
   }

    bool hasNext() {
      return this.i.hasNext();
   }

    V next() {
      return (V)((Entry)this.i.next()).getValue();
   }

    void remove() {
      this.i.remove();
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
