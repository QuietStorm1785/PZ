#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Lister {
public:
    ListIterator iterator(void* o, XMLSerializer context) {
      return Lister.access$300();
   }

    void* startPacking(void* o, Accessor accessor) {
    return nullptr;
   }

    void addToPack(void* o, void* o1) {
   }

    void endPacking(void* o, void* o1, Accessor accessor) {
   }

    void reset(void* o, Accessor accessor) {
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
