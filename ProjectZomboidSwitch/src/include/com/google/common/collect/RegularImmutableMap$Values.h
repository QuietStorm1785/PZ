#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/RegularImmutableMap/Values/SerializedForm.h"
#include "com/google/j2objc/annotations/Weak.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableMap {
public:
   const RegularImmutableMap<K, V> map;

   RegularImmutableMap$Values(RegularImmutableMap<K, V> map) {
      this.map = map;
   }

    V get(int index) {
      return (V)RegularImmutableMap.access$000(this.map)[index].getValue();
   }

    int size() {
      return this.map.size();
   }

    bool isPartialView() {
    return true;
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.map);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
