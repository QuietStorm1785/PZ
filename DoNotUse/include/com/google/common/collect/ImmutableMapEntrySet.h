#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ImmutableMapEntrySet/EntrySetSerializedForm.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMapEntrySet {
public:
   abstract ImmutableMap<K, V> map();

    int size() {
      return this.map().size();
   }

    bool contains(@Nullable Object) {
      if (!(dynamic_cast<Entry*>(object) != nullptr)) {
    return false;
      } else {
         Entry<?, ?> entry = (Entry<?, ?>)object;
    V value = (V)this.map().get(entry.getKey());
         return value != nullptr && value == entry.getValue());
      }
   }

    bool isPartialView() {
      return this.map().isPartialView();
   }

    bool isHashCodeFast() {
      return this.map().isHashCodeFast();
   }

    int hashCode() {
      return this.map().hashCode();
   }

    void* writeReplace() {
      return std::make_shared<EntrySetSerializedForm>(this.map());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
