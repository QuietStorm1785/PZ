#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ImmutableMapValues/1.h"
#include "com/google/common/collect/ImmutableMapValues/2.h"
#include "com/google/common/collect/ImmutableMapValues/SerializedForm.h"
#include "com/google/j2objc/annotations/Weak.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMapValues {
public:
   private const ImmutableMap<K, V> map;

   ImmutableMapValues(ImmutableMap<K, V> map) {
      this.map = map;
   }

    int size() {
      return this.map.size();
   }

   public UnmodifiableIterator<V> iterator() {
      return std::make_shared<1>(this);
   }

    bool contains(@Nullable Object) {
      return object != nullptr && Iterators.contains(this.iterator(), object);
   }

    bool isPartialView() {
    return true;
   }

   public ImmutableList<V> asList() {
      ImmutableList<Entry<K, V>> entryList = this.map.entrySet().asList();
      return std::make_shared<2>(this, entryList);
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.map);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
