#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_EVENT_DESCRIPTION.h"
#include "fmod/javafmod.h"
#include "zombie/GameSounds.h"
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/Helicopter/1.h"
#include "zombie/iso/Helicopter/State.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {


class Helicopter {
public:
    static float MAX_BOTHER_SECONDS = 60.0F;
    static float MAX_UNSEEN_SECONDS = 15.0F;
    static int RADIUS_HOVER = 50;
    static int RADIUS_SEARCH = 100;
    State state;
    IsoGameCharacter target;
    float timeSinceChopperSawPlayer;
    float hoverTime;
    float searchTime;
    float x;
    float y;
    float targetX;
    float targetY;
    Vector2 move = std::make_shared<Vector2>();
    bool bActive;
    static long inst;
    static FMOD_STUDIO_EVENT_DESCRIPTION event;
    bool bSoundStarted;
    float volume;
    float occlusion;

    void pickRandomTarget() {
    std::vector var1;
      if (GameServer.bServer) {
         var1 = GameServer.getPlayers();
      } else {
         if (GameClient.bClient) {
            throw IllegalStateException("can't call this on the client");
         }

         var1 = std::make_unique<std::vector>();

         for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
            if (var3 != nullptr && var3.isAlive()) {
               var1.push_back(var3);
            }
         }
      }

      if (var1.empty()) {
         this.bActive = false;
         this.target = nullptr;
      } else {
         this.setTarget((IsoGameCharacter)var1.get(Rand.Next(var1.size())));
      }
   }

    void setTarget(IsoGameCharacter var1) {
      this.target = var1;
      this.x = this.target.x + 1000.0F;
      this.y = this.target.y + 1000.0F;
      this.targetX = this.target.x;
      this.targetY = this.target.y;
      this.move.x = this.targetX - this.x;
      this.move.y = this.targetY - this.y;
      this.move.normalize();
      this.move.setLength(0.5F);
      this.state = State.Arriving;
      this.bActive = true;
      DebugLog.log("chopper: activated");
   }

    void changeState(State var1) {
      DebugLog.log("chopper: state " + this.state + " -> " + var1);
      this.state = var1;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void update() {
      if (this.bActive) {
         if (GameClient.bClient) {
            this.updateSound();
         } else {
    float var1 = 1.0F;
            if (GameServer.bServer) {
               if (!GameServer.Players.contains(this.target)) {
                  this.target = nullptr;
               }
            } else {
               var1 = GameTime.getInstance().getTrueMultiplier();
            }

            switch (1.$SwitchMap$zombie$iso$Helicopter$State[this.state.ordinal()]) {
               case 1:
                  if (this.target != nullptr && !this.target.isDead()) {
                     if (IsoUtils.DistanceToSquared(this.x, this.y, this.targetX, this.targetY) < 4.0F) {
                        this.changeState(State.Hovering);
                        this.hoverTime = 0.0F;
                        this.searchTime = 0.0F;
                        this.timeSinceChopperSawPlayer = 0.0F;
                     } else {
                        this.targetX = this.target.x;
                        this.targetY = this.target.y;
                        this.move.x = this.targetX - this.x;
                        this.move.y = this.targetY - this.y;
                        this.move.normalize();
                        this.move.setLength(0.75F);
                     }
                  } else {
                     this.changeState(State.Leaving);
                  }
                  break;
               case 2:
                  if (this.target != nullptr && !this.target.isDead()) {
                     this.hoverTime = this.hoverTime + GameTime.getInstance().getRealworldSecondsSinceLastUpdate() * var1;
                     if (this.hoverTime + this.searchTime > MAX_BOTHER_SECONDS) {
                        this.changeState(State.Leaving);
                     } else {
                        if (!this.isTargetVisible()) {
                           this.timeSinceChopperSawPlayer = this.timeSinceChopperSawPlayer + GameTime.getInstance().getRealworldSecondsSinceLastUpdate() * var1;
                           if (this.timeSinceChopperSawPlayer > MAX_UNSEEN_SECONDS) {
                              this.changeState(State.Searching);
                              break;
                           }
                        }

                        if (IsoUtils.DistanceToSquared(this.x, this.y, this.targetX, this.targetY) < 1.0F) {
                           this.targetX = this.target.x + (Rand.Next(RADIUS_HOVER * 2) - RADIUS_HOVER);
                           this.targetY = this.target.y + (Rand.Next(RADIUS_HOVER * 2) - RADIUS_HOVER);
                           this.move.x = this.targetX - this.x;
                           this.move.y = this.targetY - this.y;
                           this.move.normalize();
                           this.move.setLength(0.5F);
                        }
                     }
                  } else {
                     this.changeState(State.Leaving);
                  }
                  break;
               case 3:
                  if (this.target != nullptr && !this.target.isDead()) {
                     this.searchTime = this.searchTime + GameTime.getInstance().getRealworldSecondsSinceLastUpdate() * var1;
                     if (this.hoverTime + this.searchTime > MAX_BOTHER_SECONDS) {
                        this.changeState(State.Leaving);
                     } else if (this.isTargetVisible()) {
                        this.timeSinceChopperSawPlayer = 0.0F;
                        this.changeState(State.Hovering);
                     } else if (IsoUtils.DistanceToSquared(this.x, this.y, this.targetX, this.targetY) < 1.0F) {
                        this.targetX = this.target.x + (Rand.Next(RADIUS_SEARCH * 2) - RADIUS_SEARCH);
                        this.targetY = this.target.y + (Rand.Next(RADIUS_SEARCH * 2) - RADIUS_SEARCH);
                        this.move.x = this.targetX - this.x;
                        this.move.y = this.targetY - this.y;
                        this.move.normalize();
                        this.move.setLength(0.5F);
                     }
                  } else {
                     this.state = State.Leaving;
                  }
                  break;
               case 4:
    bool var2 = false;
                  if (GameServer.bServer) {
    std::vector var7 = GameServer.getPlayers();

                     for (int var9 = 0; var9 < var7.size(); var9++) {
    IsoPlayer var5 = (IsoPlayer)var7.get(var9);
                        if (IsoUtils.DistanceToSquared(this.x, this.y, var5.getX(), var5.getY()) < 1000000.0F) {
                           var2 = true;
                           break;
                        }
                     }
                  } else {
                     for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
    IsoPlayer var4 = IsoPlayer.players[var3];
                        if (var4 != nullptr && IsoUtils.DistanceToSquared(this.x, this.y, var4.getX(), var4.getY()) < 1000000.0F) {
                           var2 = true;
                           break;
                        }
                     }
                  }

                  if (!var2) {
                     this.deactivate();
                     return;
                  }
            }

            if (Rand.Next(Rand.AdjustForFramerate(300)) == 0) {
               WorldSoundManager.instance.addSound(nullptr, (int)this.x, (int)this.y, 0, 500, 500);
            }

    float var6 = this.move.x * (GameTime.getInstance().getMultiplier() / 1.6F);
    float var8 = this.move.y * (GameTime.getInstance().getMultiplier() / 1.6F);
            if (this.state != State.Leaving
               && IsoUtils.DistanceToSquared(this.x + var6, this.y + var8, this.targetX, this.targetY)
                  > IsoUtils.DistanceToSquared(this.x, this.y, this.targetX, this.targetY)) {
               this.x = this.targetX;
               this.y = this.targetY;
            } else {
               this.x += var6;
               this.y += var8;
            }

            if (GameServer.bServer) {
               GameServer.sendHelicopter(this.x, this.y, this.bActive);
            }

            this.updateSound();
         }
      }
   }

    void updateSound() {
      if (!GameServer.bServer) {
         if (!Core.SoundDisabled) {
            if (FMODManager.instance.getNumListeners() != 0) {
    GameSound var1 = GameSounds.getSound("Helicopter");
               if (var1 != nullptr && !var1.clips.empty()) {
                  if (inst == 0L) {
    GameSoundClip var2 = var1.getRandomClip();
                     event = var2.eventDescription;
                     if (event != nullptr) {
                        javafmod.FMOD_Studio_LoadEventSampleData(event.address);
                        inst = javafmod.FMOD_Studio_System_CreateEventInstance(event.address);
                     }
                  }

                  if (inst != 0L) {
    float var5 = SoundManager.instance.getSoundVolume();
                     var5 *= var1.getUserVolume();
                     if (var5 != this.volume) {
                        javafmod.FMOD_Studio_EventInstance_SetVolume(inst, var5);
                        this.volume = var5;
                     }

                     javafmod.FMOD_Studio_EventInstance3D(inst, this.x, this.y, 200.0F);
    float var3 = 0.0F;
                     if (IsoPlayer.numPlayers == 1) {
    IsoGridSquare var4 = IsoPlayer.getInstance().getCurrentSquare();
                        if (var4 != nullptr && !var4.Is(IsoFlagType.exterior)) {
                           var3 = 1.0F;
                        }
                     }

                     if (this.occlusion != var3) {
                        this.occlusion = var3;
                        javafmod.FMOD_Studio_EventInstance_SetParameterByName(inst, "Occlusion", this.occlusion);
                     }

                     if (!this.bSoundStarted) {
                        javafmod.FMOD_Studio_StartEvent(inst);
                        this.bSoundStarted = true;
                     }
                  }
               }
            }
         }
      }
   }

    bool isTargetVisible() {
      if (this.target != nullptr && !this.target.isDead()) {
    IsoGridSquare var1 = this.target.getCurrentSquare();
         if (var1 == nullptr) {
    return false;
         } else if (!var1.getProperties().Is(IsoFlagType.exterior)) {
    return false;
         } else {
    Zone var2 = var1.getZone();
    return var2 = = nullptr ? true : !"Forest" == var2.getType()) && !"DeepForest" == var2.getType());
         }
      } else {
    return false;
      }
   }

    void deactivate() {
      if (this.bActive) {
         this.bActive = false;
         if (this.bSoundStarted) {
            javafmod.FMOD_Studio_EventInstance_Stop(inst, false);
            this.bSoundStarted = false;
         }

         if (GameServer.bServer) {
            GameServer.sendHelicopter(this.x, this.y, this.bActive);
         }

         DebugLog.log("chopper: deactivated");
      }
   }

    bool isActive() {
      return this.bActive;
   }

    void clientSync(float var1, float var2, bool var3) {
      if (GameClient.bClient) {
         this.x = var1;
         this.y = var2;
         if (!var3) {
            this.deactivate();
         }

         this.bActive = var3;
      }
   }
}
} // namespace iso
} // namespace zombie
