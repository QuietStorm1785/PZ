#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/j2objc/annotations/Weak.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMultimap {
public:
   const ImmutableMultimap<K, V> multimap;
    static const long serialVersionUID = 0L;

   ImmutableMultimap$EntryCollection(ImmutableMultimap<K, V> multimap) {
      this.multimap = multimap;
   }

   public UnmodifiableIterator<Entry<K, V>> iterator() {
      return this.multimap.entryIterator();
   }

    bool isPartialView() {
      return this.multimap.isPartialView();
   }

    int size() {
      return this.multimap.size();
   }

    bool contains(void* object) {
      if (dynamic_cast<Entry*>(object) != nullptr) {
         Entry<?, ?> entry = (Entry<?, ?>)object;
         return this.multimap.containsEntry(entry.getKey(), entry.getValue());
      } else {
    return false;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
