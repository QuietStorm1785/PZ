#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableType.h"

namespace zombie {
namespace characters {


// $VF: synthetic class
class IsoGameCharacter {
public:
   static {
      try {
         $SwitchMap$zombie$core$skinnedmodel$advancedanimation$AnimationVariableType[AnimationVariableType.std::string.ordinal()] = 1;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$advancedanimation$AnimationVariableType[AnimationVariableType.float.ordinal()] = 2;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$advancedanimation$AnimationVariableType[AnimationVariableType.bool.ordinal()] = 3;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$advancedanimation$AnimationVariableType[AnimationVariableType.Void.ordinal()] = 4;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace characters
} // namespace zombie
