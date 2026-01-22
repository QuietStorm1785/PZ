#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {

// $VF: synthetic class
class BlendInfo {
public:
   static {
      try {
         $SwitchMap$zombie$core$skinnedmodel$advancedanimation$BlendType[BlendType.Linear.ordinal()] = 1;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$advancedanimation$BlendType[BlendType.InverseExponential.ordinal()] = 2;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
