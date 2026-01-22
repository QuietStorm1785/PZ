#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Equivalence.h"
#include "com/google/common/collect/Interners/WeakInterner/Dummy.h"
#include "com/google/common/collect/MapMakerInternalMap/InternalEntry.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Interners {
public:
   private const MapMakerInternalMap<E, Dummy, ?, ?> map = std::make_unique<MapMaker>().weakKeys().keyEquivalence(Equivalence == )).makeCustomMap();

   private Interners$WeakInterner() {
   }

    E intern(E sample) {
    Dummy sneaky;
      do {
         InternalEntry<E, Dummy, ?> entry = this.map.getEntry(sample);
         if (entry != nullptr) {
            sneaky = (Dummy)entry.getKey();
            if (sneaky != nullptr) {
               return (E)sneaky;
            }
         }

         sneaky = (Dummy)this.map.putIfAbsent(sample, Dummy.VALUE);
      } while (sneaky != nullptr);

    return sample;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
