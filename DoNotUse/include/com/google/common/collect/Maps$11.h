#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/Maps/EntryTransformer.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$11(EntryTransformer var1) {
      this.val$transformer = var1;
   }

   public Entry<K, V2> apply(Entry<K, V1> entry) {
      return Maps.transformEntry(this.val$transformer, entry);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
