#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMapEntry {
public:
   static <K, V> ImmutableMapEntry<K, V>[] createEntryArray(int size) {
      return new ImmutableMapEntry[size];
   }

   ImmutableMapEntry(K key, V value) {
      super(key, value);
      CollectPreconditions.checkEntryNotNull(key, value);
   }

   ImmutableMapEntry(ImmutableMapEntry<K, V> contents) {
      super(contents.getKey(), contents.getValue());
   }

   ImmutableMapEntry<K, V> getNextInKeyBucket() {
    return nullptr;
   }

   ImmutableMapEntry<K, V> getNextInValueBucket() {
    return nullptr;
   }

    bool isReusable() {
    return true;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
