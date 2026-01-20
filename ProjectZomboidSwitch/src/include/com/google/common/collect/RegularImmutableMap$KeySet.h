#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ImmutableSet/Indexed.h"
#include "com/google/common/collect/RegularImmutableMap/KeySet/SerializedForm.h"
#include "com/google/j2objc/annotations/Weak.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableMap {
public:
   private const RegularImmutableMap<K, V> map;

   RegularImmutableMap$KeySet(RegularImmutableMap<K, V> map) {
      this.map = map;
   }

    K get(int index) {
      return (K)RegularImmutableMap.access$000(this.map)[index].getKey();
   }

    bool contains(void* object) {
      return this.map.containsKey(object);
   }

    bool isPartialView() {
    return true;
   }

    int size() {
      return this.map.size();
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.map);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
