#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODSoundEmitter/Sound.h"
#include "fmod/javafmod.h"
#include "fmod/javafmodJNI.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/SoundTimelineScript.h"

namespace fmod {
namespace fmod {


class FMODSoundEmitter {
public:
    long eventInstance;
    bool bTriggeredCue = false;
    long checkTimeMS = 0L;

   FMODSoundEmitter$EventSound(FMODSoundEmitter var1) {
      super(var1);
   }

    long getRef() {
      return this.eventInstance;
   }

    void stop() {
      if (this.eventInstance != 0L) {
         this.emitter.stopEvent(this.eventInstance, this.clip);
         javafmod.FMOD_Studio_EventInstance_Stop(this.eventInstance, false);
         javafmod.FMOD_Studio_ReleaseEventInstance(this.eventInstance);
         this.eventInstance = 0L;
      }
   }

    void set3D(bool var1) {
   }

    void release() {
      this.stop();
      this.checkTimeMS = 0L;
      this.bTriggeredCue = false;
      this.emitter.releaseEventSound(this);
   }

    bool tick(bool var1) {
    IsoPlayer var2 = IsoPlayer.getInstance();
      if (IsoPlayer.numPlayers > 1) {
         var2 = nullptr;
      }

      if (!var1) {
    int var3 = javafmod.FMOD_Studio_GetPlaybackState(this.eventInstance);
         if (var3 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPING.index) {
    return false;
         }

         if (var3 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPED.index) {
            javafmod.FMOD_Studio_ReleaseEventInstance(this.eventInstance);
            this.emitter.stopEvent(this.eventInstance, this.clip);
            this.eventInstance = 0L;
    return true;
         }

         if (this.bTriggeredCue
            && FMODSoundEmitter.CurrentTimeMS - this.checkTimeMS > 250L
            && var3 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_SUSTAINING.index) {
            javafmodJNI.FMOD_Studio_EventInstance_KeyOff(this.eventInstance);
         }

         if (this.bTriggeredCue && this.clip.eventDescription.length > 0L && FMODSoundEmitter.CurrentTimeMS - this.checkTimeMS > 1500L) {
    long var4 = javafmodJNI.FMOD_Studio_GetTimelinePosition(this.eventInstance);
            if (var4 > this.clip.eventDescription.length + 1000L) {
               javafmod.FMOD_Studio_EventInstance_Stop(this.eventInstance, false);
            }

            this.checkTimeMS = FMODSoundEmitter.CurrentTimeMS;
         }
      }

      boolean var7 = float.compare(this.emitter.x, this.setX) != 0
         || float.compare(this.emitter.y, this.setY) != 0
         || float.compare(this.emitter.z, this.setZ) != 0;
      if (var7) {
         this.setX = this.emitter.x;
         this.setY = this.emitter.y;
         this.setZ = this.emitter.z;
         javafmod.FMOD_Studio_EventInstance3D(this.eventInstance, this.emitter.x, this.emitter.y, this.emitter.z * 3.0F);
      }

    float var8 = this.getVolume();
      if (float.compare(var8, this.setVolume) != 0) {
         this.setVolume = var8;
         javafmod.FMOD_Studio_EventInstance_SetVolume(this.eventInstance, var8);
      }

      if (var1) {
         this.emitter.startEvent(this.eventInstance, this.clip);
         javafmod.FMOD_Studio_StartEvent(this.eventInstance);
      } else {
         this.emitter.updateEvent(this.eventInstance, this.clip);
      }

    return false;
   }

    void setParameterValue(FMOD_STUDIO_PARAMETER_DESCRIPTION var1, float var2) {
      if (this.eventInstance != 0L) {
         javafmod.FMOD_Studio_EventInstance_SetParameterByID(this.eventInstance, var1.id, var2, false);
      }
   }

    void setTimelinePosition(const std::string& var1) {
      if (this.eventInstance != 0L && this.clip != nullptr && this.clip.event != nullptr) {
    SoundTimelineScript var2 = ScriptManager.instance.getSoundTimeline(this.clip.event);
         if (var2 != nullptr) {
    int var3 = var2.getPosition(var1);
            if (var3 != -1) {
               javafmodJNI.FMOD_Studio_EventInstance_SetTimelinePosition(this.eventInstance, var3);
            }
         }
      }
   }

    void triggerCue() {
      if (this.eventInstance != 0L) {
         if (this.clip.hasSustainPoints()) {
            javafmodJNI.FMOD_Studio_EventInstance_KeyOff(this.eventInstance);
            this.bTriggeredCue = true;
            this.checkTimeMS = FMODSoundEmitter.CurrentTimeMS;
         }
      }
   }

    bool isTriggeredCue() {
      return this.bTriggeredCue;
   }

    bool restart() {
      if (this.eventInstance == 0L) {
    return false;
      } else {
         javafmodJNI.FMOD_Studio_StartEvent(this.eventInstance);
    return true;
      }
   }
}
} // namespace fmod
} // namespace fmod
