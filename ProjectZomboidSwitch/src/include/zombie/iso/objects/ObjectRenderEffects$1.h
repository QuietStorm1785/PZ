#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace objects {

// $VF: synthetic class
class ObjectRenderEffects {
public:
   static {
      try {
         $SwitchMap$zombie$iso$objects$RenderEffectType[RenderEffectType.Hit_Tree_Shudder.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$iso$objects$RenderEffectType[RenderEffectType.Vegetation_Rustle.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$iso$objects$RenderEffectType[RenderEffectType.Hit_Door.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
