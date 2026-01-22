#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Maps/FilteredEntryMap/EntrySet/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$FilteredEntryMap$EntrySet$1$1(1 var1, Entry var2) {
      this.this$2 = var1;
      this.val$entry = var2;
   }

   protected Entry<K, V> delegate() {
      return this.val$entry;
   }

    V setValue(V newValue) {
      Preconditions.checkArgument(this.this$2.this$1.this$0.apply(this.getKey(), newValue));
      return (V)super.setValue(newValue);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
