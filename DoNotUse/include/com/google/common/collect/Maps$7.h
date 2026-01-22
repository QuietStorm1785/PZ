#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/Maps/EntryTransformer.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$7(Function var1) {
      this.val$function = var1;
   }

    V2 transformEntry(K key, V1 value) {
      return (V2)this.val$function.apply(value);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
