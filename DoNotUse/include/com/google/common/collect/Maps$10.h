#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/EntryTransformer.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$10(Entry var1, EntryTransformer var2) {
      this.val$entry = var1;
      this.val$transformer = var2;
   }

    K getKey() {
      return (K)this.val$entry.getKey();
   }

    V2 getValue() {
      return (V2)this.val$transformer.transformEntry(this.val$entry.getKey(), this.val$entry.getValue());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
