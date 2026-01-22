#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/objects/IsoZombieGiblets/GibletType.h"

namespace zombie {
namespace iso {
namespace objects {


// $VF: synthetic class
class IsoZombieGiblets {
public:
   static {
      try {
         $SwitchMap$zombie$iso$objects$IsoZombieGiblets$GibletType[GibletType.A.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$iso$objects$IsoZombieGiblets$GibletType[GibletType.B.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$iso$objects$IsoZombieGiblets$GibletType[GibletType.Eye.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
