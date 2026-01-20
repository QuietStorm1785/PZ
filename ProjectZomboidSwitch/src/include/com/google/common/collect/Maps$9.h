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
   Maps$9(EntryTransformer var1) {
      this.val$transformer = var1;
   }

    V2 apply(V1> entry) {
      return (V2)this.val$transformer.transformEntry(entry.getKey(), entry.getValue());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
