#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Platform {
public:
   static <T> T[] newArray(T[] reference, int length) {
      Class<?> type = reference.getClass().getComponentType();
      return (T[])((Object[])Array.newInstance(type, length));
   }

    static MapMaker tryWeakKeys(MapMaker mapMaker) {
      return mapMaker.weakKeys();
   }

    private Platform() {
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
