#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_EVENT_DESCRIPTION.h"
#include "fmod/fmod/FMOD_STUDIO_PLAYBACK_STATE.h"
#include "fmod/javafmod.h"
#include "zombie/GameSounds.h"
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/audio/GameSound.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {


class Alarm {
public:
    static long inst;
    static FMOD_STUDIO_EVENT_DESCRIPTION event;
    bool finished = false;
    int x;
    int y;
    float volume;
    float occlusion;
    float endGameTime;

    public Alarm(int var1, int var2) {
      this.x = var1;
      this.y = var2;
    uint8_t var3 = 49;
    float var4 = (float)GameTime.instance.getWorldAgeHours();
      this.endGameTime = var4 + var3 / 3600.0F * (1440.0F / GameTime.instance.getMinutesPerDay());
   }

    void update() {
      if (!GameClient.bClient) {
         WorldSoundManager.instance.addSound(this, this.x, this.y, 0, 600, 600);
      }

      if (!GameServer.bServer) {
         this.updateSound();
         if (GameTime.getInstance().getWorldAgeHours() >= this.endGameTime) {
            if (inst != 0L) {
               javafmod.FMOD_Studio_EventInstance_Stop(inst, false);
               inst = 0L;
            }

            this.finished = true;
         }
      }
   }

    void updateSound() {
      if (!GameServer.bServer && !Core.SoundDisabled && !this.finished) {
         if (FMODManager.instance.getNumListeners() != 0) {
            if (inst == 0L) {
               event = FMODManager.instance.getEventDescription("event:/Meta/HouseAlarm");
               if (event != nullptr) {
                  javafmod.FMOD_Studio_LoadEventSampleData(event.address);
                  inst = javafmod.FMOD_Studio_System_CreateEventInstance(event.address);
               }
            }

            if (inst > 0L) {
    float var1 = SoundManager.instance.getSoundVolume();
    GameSound var2 = GameSounds.getSound("HouseAlarm");
               if (var2 != nullptr) {
                  var1 *= var2.getUserVolume();
               }

               if (var1 != this.volume) {
                  javafmod.FMOD_Studio_EventInstance_SetVolume(inst, var1);
                  this.volume = var1;
               }

               javafmod.FMOD_Studio_EventInstance3D(inst, this.x, this.y, 0.0F);
               if (javafmod.FMOD_Studio_GetPlaybackState(inst) != FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_PLAYING.index
                  && javafmod.FMOD_Studio_GetPlaybackState(inst) != FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STARTING.index) {
                  if (javafmod.FMOD_Studio_GetPlaybackState(inst) == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPING.index) {
                     this.finished = true;
                     return;
                  }

                  javafmod.FMOD_Studio_StartEvent(inst);
                  System.out.println(javafmod.FMOD_Studio_GetPlaybackState(inst));
               }

    float var3 = 0.0F;
               if (IsoPlayer.numPlayers == 1) {
    IsoGridSquare var4 = IsoPlayer.getInstance().getCurrentSquare();
                  if (var4 != nullptr && !var4.Is(IsoFlagType.exterior)) {
                     var3 = 0.2F;
    IsoGridSquare var5 = IsoWorld.instance.getCell().getGridSquare(this.x, this.y, 0);
                     if (var5 != nullptr && var5.getBuilding() == var4.getBuilding()) {
                        var3 = 0.0F;
                     }
                  }
               }

               if (this.occlusion != var3) {
                  this.occlusion = var3;
                  javafmod.FMOD_Studio_EventInstance_SetParameterByName(inst, "Occlusion", this.occlusion);
               }
            }
         }
      }
   }
}
} // namespace iso
} // namespace zombie
