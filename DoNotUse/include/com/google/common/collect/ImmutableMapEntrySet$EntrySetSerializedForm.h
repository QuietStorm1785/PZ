#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMapEntrySet {
public:
   const ImmutableMap<K, V> map;
    static const long serialVersionUID = 0L;

   ImmutableMapEntrySet$EntrySetSerializedForm(ImmutableMap<K, V> map) {
      this.map = map;
   }

    void* readResolve() {
      return this.map.entrySet();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
