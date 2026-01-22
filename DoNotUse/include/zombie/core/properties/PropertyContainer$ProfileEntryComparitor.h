#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/properties/PropertyContainer/MostTested.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace properties {


class PropertyContainer {
public:
   public PropertyContainer$ProfileEntryComparitor() {
   }

    int compare(void* var1, void* var2) {
    double var3 = ((MostTested)var1).count;
    double var5 = ((MostTested)var2).count;
      if (var3 > var5) {
         return -1;
      } else {
         return var5 > var3 ? 1 : 0;
      }
   }
}
} // namespace properties
} // namespace core
} // namespace zombie
