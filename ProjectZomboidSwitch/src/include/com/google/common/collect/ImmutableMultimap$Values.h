#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/j2objc/annotations/Weak.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMultimap {
public:
   private const transient ImmutableMultimap<K, V> multimap;
    static const long serialVersionUID = 0L;

   ImmutableMultimap$Values(ImmutableMultimap<K, V> multimap) {
      this.multimap = multimap;
   }

    bool contains(@Nullable Object) {
      return this.multimap.containsValue(object);
   }

   public UnmodifiableIterator<V> iterator() {
      return this.multimap.valueIterator();
   }

    int copyIntoArray(Object[] dst, int offset) {
      for (ImmutableCollection<V> valueCollection : this.multimap.map.values()) {
         offset = valueCollection.copyIntoArray(dst, offset);
      }

    return offset;
   }

    int size() {
      return this.multimap.size();
   }

    bool isPartialView() {
    return true;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
