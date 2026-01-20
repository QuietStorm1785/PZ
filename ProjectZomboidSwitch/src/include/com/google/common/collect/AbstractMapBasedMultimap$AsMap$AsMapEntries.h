#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractMapBasedMultimap/AsMap.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/AsMap/AsMapIterator.h"
#include "com/google/common/collect/Maps/EntrySet.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   AbstractMapBasedMultimap$AsMap$AsMapEntries(AsMap var1) {
      this.this$1 = var1;
   }

   Map<K, Collection<V>> map() {
      return this.this$1;
   }

   public Iterator<Entry<K, Collection<V>>> iterator() {
      return std::make_shared<AsMapIterator>(this.this$1);
   }

    bool contains(void* o) {
      return Collections2.safeContains(this.this$1.submap.entrySet(), o);
   }

    bool remove(void* o) {
      if (!this.contains(o)) {
    return false;
      } else {
         Entry<?, ?> entry = (Entry<?, ?>)o;
         AbstractMapBasedMultimap.access$400(this.this$1.this$0, entry.getKey());
    return true;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
