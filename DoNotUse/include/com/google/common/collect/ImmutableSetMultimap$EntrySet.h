#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/j2objc/annotations/Weak.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSetMultimap {
public:
   private const transient ImmutableSetMultimap<K, V> multimap;

   ImmutableSetMultimap$EntrySet(ImmutableSetMultimap<K, V> multimap) {
      this.multimap = multimap;
   }

    bool contains(@Nullable Object) {
      if (dynamic_cast<Entry*>(object) != nullptr) {
         Entry<?, ?> entry = (Entry<?, ?>)object;
         return this.multimap.containsEntry(entry.getKey(), entry.getValue());
      } else {
    return false;
      }
   }

    int size() {
      return this.multimap.size();
   }

   public UnmodifiableIterator<Entry<K, V>> iterator() {
      return this.multimap.entryIterator();
   }

    bool isPartialView() {
    return false;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
