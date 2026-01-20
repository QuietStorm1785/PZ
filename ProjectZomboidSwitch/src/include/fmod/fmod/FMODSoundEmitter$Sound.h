#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/GameSoundClip.h"
#include "zombie/iso/IsoObject.h"

namespace fmod {
namespace fmod {


class FMODSoundEmitter {
public:
    FMODSoundEmitter emitter;
    GameSoundClip clip;
    std::string name;
    float volume = 1.0F;
    float pitch = 1.0F;
    IsoObject parent;
    float setVolume = 1.0F;
    float setX = 0.0F;
    float setY = 0.0F;
    float setZ = 0.0F;

   FMODSoundEmitter$Sound(FMODSoundEmitter var1) {
      this.emitter = var1;
   }

   abstract long getRef();

   abstract void stop();

   abstract void set3D(boolean var1);

   abstract void release();

   abstract boolean tick(boolean var1);

    float getVolume() {
      this.clip = this.clip.checkReloaded();
      return this.volume * this.clip.getEffectiveVolume();
   }

   abstract void setParameterValue(FMOD_STUDIO_PARAMETER_DESCRIPTION var1, float var2);

   abstract void setTimelinePosition(std::string var1);

   abstract void triggerCue();

   abstract boolean isTriggeredCue();

   abstract boolean restart();
}
} // namespace fmod
} // namespace fmod
