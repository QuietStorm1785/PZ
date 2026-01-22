#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/Strength.h"

namespace com {
namespace google {
namespace common {
namespace cache {


// $VF: synthetic class
class CacheBuilderSpec {
public:
   static {
      try {
         $SwitchMap$com$google$common$cache$LocalCache$Strength[Strength.WEAK.ordinal()] = 1;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$com$google$common$cache$LocalCache$Strength[Strength.SOFT.ordinal()] = 2;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
