#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ForwardingSet.h"
#include "com/google/common/reflect/MutableTypeToInstanceMap/UnmodifiableEntry.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace reflect {


class MutableTypeToInstanceMap {
public:
   MutableTypeToInstanceMap$UnmodifiableEntry$1(Set var1) {
      this.val$entries = var1;
   }

   protected Set<Entry<K, V>> delegate() {
      return this.val$entries;
   }

   public Iterator<Entry<K, V>> iterator() {
      return UnmodifiableEntry.access$000(super.iterator());
   }

   public Object[] toArray() {
      return this.standardToArray();
   }

   public <T> T[] toArray(T[] array) {
      return (T[])this.standardToArray(array);
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
