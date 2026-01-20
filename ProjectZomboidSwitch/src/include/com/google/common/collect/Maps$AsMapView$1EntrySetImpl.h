#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/AsMapView.h"
#include "com/google/common/collect/Maps/EntrySet.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$AsMapView$1EntrySetImpl(AsMapView var1) {
      this.this$0 = var1;
   }

   Map<K, V> map() {
      return this.this$0;
   }

   public Iterator<Entry<K, V>> iterator() {
      return Maps.asMapEntryIterator(this.this$0.backingSet(), this.this$0.function);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
