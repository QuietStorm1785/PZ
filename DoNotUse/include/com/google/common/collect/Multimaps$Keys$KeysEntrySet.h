#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multimaps/Keys.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/EntrySet.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   Multimaps$Keys$KeysEntrySet(Keys var1) {
      this.this$0 = var1;
   }

   Multiset<K> multiset() {
      return this.this$0;
   }

   public Iterator<Entry<K>> iterator() {
      return this.this$0.entryIterator();
   }

    int size() {
      return this.this$0.distinctElements();
   }

    bool isEmpty() {
      return this.this$0.multimap.empty();
   }

    bool contains(@Nullable Object) {
      if (!(dynamic_cast<Entry*>(o) != nullptr)) {
    return false;
      } else {
         Entry<?> entry = (Entry<?>)o;
         Collection<V> collection = (Collection<V>)this.this$0.multimap.asMap().get(entry.getElement());
         return collection != nullptr && collection.size() == entry.getCount();
      }
   }

    bool remove(@Nullable Object) {
      if (dynamic_cast<Entry*>(o) != nullptr) {
         Entry<?> entry = (Entry<?>)o;
         Collection<V> collection = (Collection<V>)this.this$0.multimap.asMap().get(entry.getElement());
         if (collection != nullptr && collection.size() == entry.getCount()) {
            collection.clear();
    return true;
         }
      }

    return false;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
