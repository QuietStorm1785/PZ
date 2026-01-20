#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/EntrySet.h"
#include "com/google/common/collect/Multimaps/AsMap.h"
#include "com/google/common/collect/Multimaps/AsMap/EntrySet/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   Multimaps$AsMap$EntrySet(AsMap var1) {
      this.this$0 = var1;
   }

   Map<K, Collection<V>> map() {
      return this.this$0;
   }

   public Iterator<Entry<K, Collection<V>>> iterator() {
      return Maps.asMapEntryIterator(AsMap.access$200(this.this$0).keySet(), std::make_shared<1>(this));
   }

    bool remove(void* o) {
      if (!this.contains(o)) {
    return false;
      } else {
         Entry<?, ?> entry = (Entry<?, ?>)o;
         this.this$0.removeValuesForKey(entry.getKey());
    return true;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
