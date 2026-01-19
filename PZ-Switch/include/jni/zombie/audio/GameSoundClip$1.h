#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/GameSound/MasterVolume.h"

namespace zombie {
namespace audio {


// $VF: synthetic class
class GameSoundClip {
:
   static {
      try {
         $SwitchMap$zombie$audio$GameSound$MasterVolume[MasterVolume.Primary.ordinal()] = 1;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$audio$GameSound$MasterVolume[MasterVolume.Ambient.ordinal()] = 2;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$audio$GameSound$MasterVolume[MasterVolume.Music.ordinal()] = 3;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$audio$GameSound$MasterVolume[MasterVolume.VehicleEngine.ordinal()] = 4;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace audio
} // namespace zombie
