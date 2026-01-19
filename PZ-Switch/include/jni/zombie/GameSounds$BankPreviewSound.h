#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMOD_STUDIO_PLAYBACK_STATE.h"
#include "fmod/javafmod.h"
#include "zombie/GameSounds/IPreviewSound.h"
#include "zombie/audio/GameSound/MasterVolume.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/debug/DebugLog.h"

namespace zombie {


class GameSounds {
:
    long instance;
    GameSoundClip clip;
    float effectiveGain;

   private GameSounds$BankPreviewSound() {
   }

    bool play(GameSoundClip var1) {
      if (var1.eventDescription == nullptr) {
         DebugLog.log("failed to get event " + var1.getEvent());
    return false;
      } else {
         this.instance = javafmod.FMOD_Studio_System_CreateEventInstance(var1.eventDescription.address);
         if (this.instance < 0L) {
            DebugLog.log("failed to create EventInstance: error=" + this.instance);
            this.instance = 0L;
    return false;
         } else {
            this.clip = var1;
            this.effectiveGain = var1.getEffectiveVolumeInMenu();
            javafmod.FMOD_Studio_EventInstance_SetVolume(this.instance, this.effectiveGain);
            javafmod.FMOD_Studio_EventInstance_SetParameterByName(this.instance, "Occlusion", 0.0F);
            javafmod.FMOD_Studio_StartEvent(this.instance);
            if (var1.gameSound.master == MasterVolume.Music) {
               javafmod.FMOD_Studio_EventInstance_SetParameterByName(this.instance, "Volume", 10.0F);
            }

    return true;
         }
      }
   }

    bool isPlaying() {
      if (this.instance == 0L) {
    return false;
      } else {
    int var1 = javafmod.FMOD_Studio_GetPlaybackState(this.instance);
         return var1 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPING.index
            ? true
            : var1 != FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPED.index;
      }
   }

    bool update() {
      if (this.instance == 0L) {
    return false;
      } else {
    int var1 = javafmod.FMOD_Studio_GetPlaybackState(this.instance);
         if (var1 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPING.index) {
    return false;
         } else if (var1 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPED.index) {
            javafmod.FMOD_Studio_ReleaseEventInstance(this.instance);
            this.instance = 0L;
            this.clip = nullptr;
    return true;
         } else {
    float var2 = this.clip.getEffectiveVolumeInMenu();
            if (this.effectiveGain != var2) {
               this.effectiveGain = var2;
               javafmod.FMOD_Studio_EventInstance_SetVolume(this.instance, this.effectiveGain);
            }

    return false;
         }
      }
   }

    void stop() {
      if (this.instance != 0L) {
         javafmod.FMOD_Studio_EventInstance_Stop(this.instance, false);
         javafmod.FMOD_Studio_ReleaseEventInstance(this.instance);
         this.instance = 0L;
         this.clip = nullptr;
      }
   }
}
} // namespace zombie
