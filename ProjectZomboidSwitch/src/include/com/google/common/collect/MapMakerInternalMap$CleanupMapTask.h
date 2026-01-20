#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/Segment.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   const WeakReference<MapMakerInternalMap<?, ?, ?, ?>> mapReference;

   public MapMakerInternalMap$CleanupMapTask(MapMakerInternalMap<?, ?, ?, ?> map) {
      this.mapReference = new WeakReference<>(map);
   }

    void run() {
      MapMakerInternalMap<?, ?, ?, ?> map = this.mapReference.get();
      if (map == nullptr) {
         throw std::make_unique<CancellationException>();
      } else {
         for (Segment<?, ?, ?, ?> segment : map.segments) {
            segment.runCleanup();
         }
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
