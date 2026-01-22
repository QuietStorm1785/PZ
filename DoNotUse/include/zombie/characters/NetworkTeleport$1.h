#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/NetworkTeleport/Type.h"

namespace zombie {
namespace characters {


// $VF: synthetic class
class NetworkTeleport {
public:
   static {
      try {
         $SwitchMap$zombie$characters$NetworkTeleport$Type[Type.disappearing.ordinal()] = 1;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$characters$NetworkTeleport$Type[Type.teleportation.ordinal()] = 2;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$characters$NetworkTeleport$Type[Type.materialization.ordinal()] = 3;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace characters
} // namespace zombie
