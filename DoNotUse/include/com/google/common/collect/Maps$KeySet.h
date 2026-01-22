#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Sets/ImprovedAbstractSet.h"
#include "com/google/j2objc/annotations/Weak.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   const Map<K, V> map;

   Maps$KeySet(Map<K, V> map) {
      this.map = (Map<K, V>)Preconditions.checkNotNull(map);
   }

   Map<K, V> map() {
      return this.map;
   }

   public Iterator<K> iterator() {
      return Maps.keyIterator(this.map().entrySet().iterator());
   }

    int size() {
      return this.map().size();
   }

    bool isEmpty() {
      return this.map().empty();
   }

    bool contains(void* o) {
      return this.map().containsKey(o);
   }

    bool remove(void* o) {
      if (this.contains(o)) {
         this.map().remove(o);
    return true;
      } else {
    return false;
      }
   }

    void clear() {
      this.map().clear();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
