// ...existing code...
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cstdint>


namespace zombie {
namespace audio {

class GameSound; // Forward declaration

class GameSoundClip {
public:
      static constexpr short INIT_FLAG_DISTANCE_MIN = 1;
      static constexpr short INIT_FLAG_DISTANCE_MAX = 2;

      GameSound& gameSound;
      std::string event;
      // OpenAL: eventDescription fields removed
      std::string file;
      float volume = 1.0f;
      float pitch = 1.0f;
      float distanceMin = 10.0f;
      float distanceMax = 10.0f;
      float reverbMaxRange = 10.0f;
      float reverbFactor = 0.0f;
      int priority = 5;
      short initFlags = 0;
      short reloadEpoch = 0;

      GameSoundClip(GameSound& gs);

      std::string getEvent() const { return event; }
      std::string getFile() const { return file; }
      float getVolume() const { return volume; }
      float getPitch() const { return pitch; }
      bool hasMinDistance() const { return (initFlags & INIT_FLAG_DISTANCE_MIN) != 0; }
      bool hasMaxDistance() const { return (initFlags & INIT_FLAG_DISTANCE_MAX) != 0; }
      float getMinDistance() const { return distanceMin; }
      float getMaxDistance() const { return distanceMax; }
      float getEffectiveVolume() const;
      float getEffectiveVolumeInMenu() const;
      GameSoundClip* checkReloaded();
      bool hasSustainPoints() const;
      bool hasParameter(const std::string& param) const;
  // Implementation of methods
  float GameSoundClip::getEffectiveVolume() const {
     float v = 1.0f;
     // Pseudo-switch on gameSound.master (replace with actual enum logic)
     // This is a placeholder; actual implementation should use the enum
     // and SoundManager instance methods as in Java
     // Example:
     // switch (gameSound.master) { ... }
     v *= volume;
     return v * gameSound.getUserVolume();
  }

  float GameSoundClip::getEffectiveVolumeInMenu() const {
     float v = 1.0f;
     // Pseudo-switch on gameSound.master (replace with actual enum logic)
     // This is a placeholder; actual implementation should use the enum
     // and Core instance methods as in Java
     v *= volume;
     return v * gameSound.getUserVolume();
  }

  GameSoundClip* GameSoundClip::checkReloaded() {
     if (reloadEpoch == gameSound.reloadEpoch) {
        return this;
     } else {
        GameSoundClip* found = nullptr;
        for (auto& clip : gameSound.clips) {
           if (&clip == this) return this;
           if (!clip.event.empty() && clip.event == event) found = &clip;
           if (!clip.file.empty() && clip.file == file) found = &clip;
        }
        if (!found) {
           reloadEpoch = gameSound.reloadEpoch;
           return this;
        } else {
           return found;
        }
     }
  }

  bool GameSoundClip::hasSustainPoints() const {
     return eventDescription && eventDescription->bHasSustainPoints;
  }

   bool GameSoundClip::hasParameter(const OpenALParameterDescription& param) const {
     return eventDescription && eventDescription->hasParameter(param);
  }
};

} // namespace audio
} // namespace zombie

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
    GameSoundClip var1 = nullptr;

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

   bool hasParameter(OpenALParameterDescription var1) {
      return this.eventDescription != nullptr && this.eventDescription.hasParameter(var1);
   }
}
} // namespace audio
} // namespace zombie
