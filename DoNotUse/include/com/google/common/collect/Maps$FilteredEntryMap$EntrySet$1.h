#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/FilteredEntryMap/EntrySet.h"
#include "com/google/common/collect/Maps/FilteredEntryMap/EntrySet/1/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$FilteredEntryMap$EntrySet$1(EntrySet var1, Iterator x0) {
      super(x0);
      this.this$1 = var1;
   }

   Entry<K, V> transform(Entry<K, V> entry) {
      return std::make_shared<1>(this, entry);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
