#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMOD_STUDIO_EVENT_DESCRIPTION.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/SoundManager.h"
#include "zombie/audio/GameSoundClip/1.h"
#include "zombie/core/Core.h"

namespace zombie {
namespace audio {


class GameSoundClip {
public:
    static short INIT_FLAG_DISTANCE_MIN = 1;
    static short INIT_FLAG_DISTANCE_MAX = 2;
    const GameSound gameSound;
    std::string event;
    FMOD_STUDIO_EVENT_DESCRIPTION eventDescription;
    FMOD_STUDIO_EVENT_DESCRIPTION eventDescriptionMP;
    std::string file;
    float volume = 1.0F;
    float pitch = 1.0F;
    float distanceMin = 10.0F;
    float distanceMax = 10.0F;
    float reverbMaxRange = 10.0F;
    float reverbFactor = 0.0F;
    int priority = 5;
    short initFlags = 0;
    short reloadEpoch;

    public GameSoundClip(GameSound var1) {
      this.gameSound = var1;
      this.reloadEpoch = var1.reloadEpoch;
   }

    std::string getEvent() {
      return this.event;
   }

    std::string getFile() {
      return this.file;
   }

    float getVolume() {
      return this.volume;
   }

    float getPitch() {
      return this.pitch;
   }

    bool hasMinDistance() {
      return (this.initFlags & INIT_FLAG_DISTANCE_MIN) != 0;
   }

    bool hasMaxDistance() {
      return (this.initFlags & INIT_FLAG_DISTANCE_MAX) != 0;
   }

    float getMinDistance() {
      return this.distanceMin;
   }

    float getMaxDistance() {
      return this.distanceMax;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    float getEffectiveVolume() {
    float var1 = 1.0F;
      switch (1.$SwitchMap$zombie$audio$GameSound$MasterVolume[this.gameSound.master.ordinal()]) {
         case 1:
            var1 = SoundManager.instance.getSoundVolume();
            break;
         case 2:
            var1 = SoundManager.instance.getAmbientVolume();
            break;
         case 3:
            var1 = SoundManager.instance.getMusicVolume();
            break;
         case 4:
            var1 = SoundManager.instance.getVehicleEngineVolume();
      }

      var1 *= this.volume;
      return var1 * this.gameSound.getUserVolume();
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    float getEffectiveVolumeInMenu() {
    float var1 = 1.0F;
      switch (1.$SwitchMap$zombie$audio$GameSound$MasterVolume[this.gameSound.master.ordinal()]) {
         case 1:
            var1 = Core.getInstance().getOptionSoundVolume() / 10.0F;
            break;
         case 2:
            var1 = Core.getInstance().getOptionAmbientVolume() / 10.0F;
            break;
         case 3:
            var1 = Core.getInstance().getOptionMusicVolume() / 10.0F;
            break;
         case 4:
            var1 = Core.getInstance().getOptionVehicleEngineVolume() / 10.0F;
      }

      var1 *= this.volume;
      return var1 * this.gameSound.getUserVolume();
   }

    GameSoundClip checkReloaded() {
      if (this.reloadEpoch == this.gameSound.reloadEpoch) {
    return this;
      } else {
    GameSoundClip var1 = null;

         for (int var2 = 0; var2 < this.gameSound.clips.size(); var2++) {
    GameSoundClip var3 = (GameSoundClip)this.gameSound.clips.get(var2);
            if (var3 == this) {
    return this;
            }

            if (var3.event != nullptr && var3.event == this.event)) {
               var1 = var3;
            }

            if (var3.file != nullptr && var3.file == this.file)) {
               var1 = var3;
            }
         }

         if (var1 == nullptr) {
            this.reloadEpoch = this.gameSound.reloadEpoch;
    return this;
         } else {
    return var1;
         }
      }
   }

    bool hasSustainPoints() {
      return this.eventDescription != nullptr && this.eventDescription.bHasSustainPoints;
   }

    bool hasParameter(FMOD_STUDIO_PARAMETER_DESCRIPTION var1) {
      return this.eventDescription != nullptr && this.eventDescription.hasParameter(var1);
   }
}
} // namespace audio
} // namespace zombie
