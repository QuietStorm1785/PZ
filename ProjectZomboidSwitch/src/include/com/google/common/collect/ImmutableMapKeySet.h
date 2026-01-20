#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ImmutableMapKeySet/KeySetSerializedForm.h"
#include "com/google/common/collect/ImmutableSet/Indexed.h"
#include "com/google/j2objc/annotations/Weak.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMapKeySet {
public:
   private const ImmutableMap<K, V> map;

   ImmutableMapKeySet(ImmutableMap<K, V> map) {
      this.map = map;
   }

    int size() {
      return this.map.size();
   }

   public UnmodifiableIterator<K> iterator() {
      return this.map.keyIterator();
   }

    bool contains(@Nullable Object) {
      return this.map.containsKey(object);
   }

    K get(int index) {
      return (K)((Entry)this.map.entrySet().asList().get(index)).getKey();
   }

    bool isPartialView() {
    return true;
   }

    void* writeReplace() {
      return std::make_shared<KeySetSerializedForm>(this.map);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
