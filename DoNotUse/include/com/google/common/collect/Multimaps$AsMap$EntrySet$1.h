#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/Multimaps/AsMap.h"
#include "com/google/common/collect/Multimaps/AsMap/EntrySet.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   Multimaps$AsMap$EntrySet$1(EntrySet var1) {
      this.this$1 = var1;
   }

   public Collection<V> apply(K key) {
      return AsMap.access$200(this.this$1.this$0).get(key);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
