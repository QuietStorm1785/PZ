#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/collect/Maps/EntrySet.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingMap {
public:
   public ForwardingMap$StandardEntrySet(ForwardingMap var1) {
      this.this$0 = var1;
   }

   Map<K, V> map() {
      return this.this$0;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
