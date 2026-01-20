#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableRangeMap/Builder.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableRangeMap {
public:
   private const ImmutableMap<Range<K>, V> mapOfRanges;
    static const long serialVersionUID = 0L;

   ImmutableRangeMap$SerializedForm(ImmutableMap<Range<K>, V> mapOfRanges) {
      this.mapOfRanges = mapOfRanges;
   }

    void* readResolve() {
      return this.mapOfRanges.empty() ? ImmutableRangeMap.of() : this.createRangeMap();
   }

    void* createRangeMap() {
      Builder<K, V> builder = std::make_unique<Builder>();

      for (Entry<Range<K>, V> entry : this.mapOfRanges.entrySet()) {
         builder.put(entry.getKey(), entry.getValue());
      }

      return builder.build();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
