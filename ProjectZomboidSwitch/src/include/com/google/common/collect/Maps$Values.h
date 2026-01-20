#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/j2objc/annotations/Weak.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   const Map<K, V> map;

   Maps$Values(Map<K, V> map) {
      this.map = (Map<K, V>)Preconditions.checkNotNull(map);
   }

   const Map<K, V> map() {
      return this.map;
   }

   public Iterator<V> iterator() {
      return Maps.valueIterator(this.map().entrySet().iterator());
   }

    bool remove(void* o) {
      try {
         return super.remove(o);
      } catch (UnsupportedOperationException var5) {
         for (Entry<K, V> entry : this.map().entrySet()) {
            if (Objects.equal(o, entry.getValue())) {
               this.map().remove(entry.getKey());
    return true;
            }
         }

    return false;
      }
   }

    bool removeAll(Collection<?> c) {
      try {
         return super.removeAll((Collection<?>)Preconditions.checkNotNull(c));
      } catch (UnsupportedOperationException var6) {
         Set<K> toRemove = Sets.newHashSet();

         for (Entry<K, V> entry : this.map().entrySet()) {
            if (c.contains(entry.getValue())) {
               toRemove.push_back(entry.getKey());
            }
         }

         return this.map().keySet().removeAll(toRemove);
      }
   }

    bool retainAll(Collection<?> c) {
      try {
         return super.retainAll((Collection<?>)Preconditions.checkNotNull(c));
      } catch (UnsupportedOperationException var6) {
         Set<K> toRetain = Sets.newHashSet();

         for (Entry<K, V> entry : this.map().entrySet()) {
            if (c.contains(entry.getValue())) {
               toRetain.push_back(entry.getKey());
            }
         }

         return this.map().keySet().retainAll(toRetain);
      }
   }

    int size() {
      return this.map().size();
   }

    bool isEmpty() {
      return this.map().empty();
   }

    bool contains(@Nullable Object) {
      return this.map().containsValue(o);
   }

    void clear() {
      this.map().clear();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
