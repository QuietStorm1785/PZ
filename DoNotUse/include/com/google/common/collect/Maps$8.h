#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/Maps/EntryTransformer.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$8(EntryTransformer var1, Object var2) {
      this.val$transformer = var1;
      this.val$key = var2;
   }

    V2 apply(@Nullable V1) {
      return (V2)this.val$transformer.transformEntry(this.val$key, v1);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
