#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/CharacterSoundEmitter/footstep.h"

namespace zombie {
namespace characters {


// $VF: synthetic class
class CharacterSoundEmitter {
public:
   static {
      try {
         $SwitchMap$zombie$characters$CharacterSoundEmitter$footstep[footstep.wood.ordinal()] = 1;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$characters$CharacterSoundEmitter$footstep[footstep.grass.ordinal()] = 2;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$characters$CharacterSoundEmitter$footstep[footstep.upstairs.ordinal()] = 3;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$characters$CharacterSoundEmitter$footstep[footstep.snow.ordinal()] = 4;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$characters$CharacterSoundEmitter$footstep[footstep.gravel.ordinal()] = 5;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$characters$CharacterSoundEmitter$footstep[footstep.concrete.ordinal()] = 6;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace characters
} // namespace zombie
