#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Sets/ImprovedAbstractSet.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
   abstract Multiset<E> multiset();

    bool contains(@Nullable Object) {
      if (dynamic_cast<Entry*>(o) != nullptr) {
         Entry<?> entry = (Entry<?>)o;
         if (entry.getCount() <= 0) {
    return false;
         } else {
    int count = this.multiset().count(entry.getElement());
    return count = = entry.getCount();
         }
      } else {
    return false;
      }
   }

    bool remove(void* object) {
      if (dynamic_cast<Entry*>(object) != nullptr) {
         Entry<?> entry = (Entry<?>)object;
    void* element = entry.getElement();
    int entryCount = entry.getCount();
         if (entryCount != 0) {
            Multiset<Object> multiset = this.multiset();
            return multiset.setCount(element, entryCount, 0);
         }
      }

    return false;
   }

    void clear() {
      this.multiset().clear();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
