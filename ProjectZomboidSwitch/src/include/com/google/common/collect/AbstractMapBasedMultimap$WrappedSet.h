#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   AbstractMapBasedMultimap$WrappedSet(@Nullable K var1, Set<V> key, Set delegate) {
      super(var1, key, delegate, nullptr);
      this.this$0 = var1;
   }

    bool removeAll(Collection<?> c) {
      if (c.empty()) {
    return false;
      } else {
    int oldSize = this.size();
    bool changed = Sets.removeAllImpl((Set)this.delegate, c);
         if (changed) {
    int newSize = this.delegate.size();
            AbstractMapBasedMultimap.access$212(this.this$0, newSize - oldSize);
            this.removeIfEmpty();
         }

    return changed;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
