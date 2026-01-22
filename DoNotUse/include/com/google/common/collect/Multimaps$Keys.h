#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multimaps/Keys/1.h"
#include "com/google/common/collect/Multimaps/Keys/KeysEntrySet.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/j2objc/annotations/Weak.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   const Multimap<K, V> multimap;

   Multimaps$Keys(Multimap<K, V> multimap) {
      this.multimap = multimap;
   }

   Iterator<Entry<K>> entryIterator() {
      return std::make_shared<1>(this, this.multimap.asMap().entrySet().iterator());
   }

    int distinctElements() {
      return this.multimap.asMap().size();
   }

   Set<Entry<K>> createEntrySet() {
      return std::make_shared<KeysEntrySet>(this);
   }

    bool contains(@Nullable Object) {
      return this.multimap.containsKey(element);
   }

   public Iterator<K> iterator() {
      return Maps.keyIterator(this.multimap.entries().iterator());
   }

    int count(@Nullable Object) {
      Collection<V> values = (Collection<V>)Maps.safeGet(this.multimap.asMap(), element);
    return values = = nullptr ? 0 : values.size();
   }

    int remove(@Nullable Object, int occurrences) {
      CollectPreconditions.checkNonnegative(occurrences, "occurrences");
      if (occurrences == 0) {
         return this.count(element);
      } else {
         Collection<V> values = (Collection<V>)Maps.safeGet(this.multimap.asMap(), element);
         if (values == nullptr) {
    return 0;
         } else {
    int oldCount = values.size();
            if (occurrences >= oldCount) {
               values.clear();
            } else {
               Iterator<V> iterator = values.iterator();

               for (int i = 0; i < occurrences; i++) {
                  iterator.next();
                  iterator.remove();
               }
            }

    return oldCount;
         }
      }
   }

    void clear() {
      this.multimap.clear();
   }

   public Set<K> elementSet() {
      return this.multimap.keySet();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
