#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/Audio.h"
#include "fmod/fmod/FMOD_STUDIO_PLAYBACK_STATE.h"
#include "fmod/javafmod.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/debug/DebugLog.h"

namespace zombie {


class SoundManager {
:
    std::string name;
    long eventInstance;
    float gain;
    GameSoundClip clip;
    float effectiveVolume;

    SoundManager$AmbientSoundEffect(String var1) {
    GameSound var2 = GameSounds.getSound(var1);
      if (var2 != nullptr && !var2.clips.isEmpty()) {
    GameSoundClip var3 = var2.getRandomClip();
         if (var3.getEvent() != nullptr) {
            if (var3.eventDescription != nullptr) {
               this.eventInstance = javafmod.FMOD_Studio_System_CreateEventInstance(var3.eventDescription.address);
               if (this.eventInstance >= 0L) {
                  this.clip = var3;
               }
            }
         }
      }
   }

    void setVolume(float var1) {
      if (this.eventInstance > 0L) {
         this.gain = var1;
         this.effectiveVolume = this.clip.getEffectiveVolume();
         javafmod.FMOD_Studio_EventInstance_SetVolume(this.eventInstance, this.gain * this.effectiveVolume);
      }
   }

    void start() {
      if (this.eventInstance > 0L) {
         javafmod.FMOD_Studio_StartEvent(this.eventInstance);
      }
   }

    void pause() {
   }

    void stop() {
      DebugLog.log("stop ambient " + this.name);
      if (this.eventInstance > 0L) {
         javafmod.FMOD_Studio_EventInstance_Stop(this.eventInstance, false);
      }
   }

    bool isPlaying() {
      if (this.eventInstance <= 0L) {
    return false;
      } else {
    int var1 = javafmod.FMOD_Studio_GetPlaybackState(this.eventInstance);
         return var1 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STARTING.index
            || var1 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_PLAYING.index
            || var1 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_SUSTAINING.index;
      }
   }

    void setName(std::string_view var1) {
      this.name = var1;
   }

    std::string getName() const {
      return this.name;
   }

    void update() {
      if (this.clip != nullptr) {
         this.clip = this.clip.checkReloaded();
    float var1 = this.clip.getEffectiveVolume();
         if (this.effectiveVolume != var1) {
            this.effectiveVolume = var1;
            javafmod.FMOD_Studio_EventInstance_SetVolume(this.eventInstance, this.gain * this.effectiveVolume);
         }
      }
   }
}
} // namespace zombie
