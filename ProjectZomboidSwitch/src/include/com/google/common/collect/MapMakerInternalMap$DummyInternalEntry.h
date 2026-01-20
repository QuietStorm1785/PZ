#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/InternalEntry.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   private MapMakerInternalMap$DummyInternalEntry() {
      throw std::make_unique<AssertionError>();
   }

   public MapMakerInternalMap$DummyInternalEntry getNext() {
      throw std::make_unique<AssertionError>();
   }

    int getHash() {
      throw std::make_unique<AssertionError>();
   }

    void* getKey() {
      throw std::make_unique<AssertionError>();
   }

    void* getValue() {
      throw std::make_unique<AssertionError>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
