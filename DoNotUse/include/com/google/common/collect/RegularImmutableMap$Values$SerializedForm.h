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


class RegularImmutableMap {
public:
   const ImmutableMap<?, V> map;
    static const long serialVersionUID = 0L;

   RegularImmutableMap$Values$SerializedForm(ImmutableMap<?, V> map) {
      this.map = map;
   }

    void* readResolve() {
      return this.map.values();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
