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
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoWindow.h"

namespace fmod {
namespace fmod {


class FMODSoundEmitter {
public:
    long sound;
    long channel;
    uint8_t is3D = -1;
    bool ambient;
    float lx;
    float ly;
    float lz;

   FMODSoundEmitter$FileSound(FMODSoundEmitter var1) {
      super(var1);
   }

    long getRef() {
      return this.channel;
   }

    void stop() {
      if (this.channel != 0L) {
         javafmod.FMOD_Channel_Stop(this.channel);
         this.sound = 0L;
         this.channel = 0L;
      }
   }

    void set3D(bool var1) {
      if (this.is3D != (byte)(var1 ? 1 : 0)) {
         javafmod.FMOD_Channel_SetMode(this.channel, var1 ? FMODManager.FMOD_3D : FMODManager.FMOD_2D);
         if (var1) {
            javafmod.FMOD_Channel_Set3DAttributes(this.channel, this.emitter.x, this.emitter.y, this.emitter.z * 3.0F, 0.0F, 0.0F, 0.0F);
         }

         this.is3D = (byte)(var1 ? 1 : 0);
      }
   }

    void release() {
      this.stop();
      this.emitter.releaseFileSound(this);
   }

    bool tick(bool var1) {
      if (var1 && this.clip.gameSound.isLooped()) {
         javafmod.FMOD_Channel_SetMode(this.channel, FMODManager.FMOD_LOOP_NORMAL);
      }

    float var2 = this.clip.distanceMin;
      if (!var1 && !javafmod.FMOD_Channel_IsPlaying(this.channel)) {
    return true;
      } else {
    float var3 = this.emitter.x;
    float var4 = this.emitter.y;
    float var5 = this.emitter.z;
         if (!this.clip.gameSound.is3D || var3 == 0.0F && var4 == 0.0F) {
            if ((var3 != 0.0F || var4 != 0.0F) && (var1 || var3 != this.lx || var4 != this.ly) && this.is3D == 1) {
               javafmod.FMOD_Channel_Set3DAttributes(this.channel, var3, var4, var5 * 3.0F, 0.0F, 0.0F, 0.0F);
            }

            javafmod.FMOD_Channel_SetVolume(this.channel, this.getVolume());
            javafmod.FMOD_Channel_SetPitch(this.channel, this.pitch);
            if (var1) {
               javafmod.FMOD_Channel_SetPaused(this.channel, false);
            }

    return false;
         } else {
            this.lx = var3;
            this.ly = var4;
            this.lz = var5;
            javafmod.FMOD_Channel_Set3DAttributes(this.channel, var3, var4, var5 * 3.0F, var3 - this.lx, var4 - this.ly, var5 * 3.0F - this.lz * 3.0F);
    float var6 = float.MAX_VALUE;

            for (int var7 = 0; var7 < IsoPlayer.numPlayers; var7++) {
    IsoPlayer var8 = IsoPlayer.players[var7];
               if (var8 != nullptr && !var8.isDeaf()) {
    float var9 = IsoUtils.DistanceTo(var3, var4, var5 * 3.0F, var8.x, var8.y, var8.z * 3.0F);
                  var6 = PZMath.min(var6, var9);
               }
            }

    float var16 = 2.0F;
    float var23 = var6 >= var16 ? 1.0F : 1.0F - (var16 - var6) / var16;
            javafmodJNI.FMOD_Channel_Set3DLevel(this.channel, var23);
            if (IsoPlayer.numPlayers > 1) {
               if (var1) {
                  javafmod.FMOD_System_SetReverbDefault(0, FMODManager.FMOD_PRESET_OFF);
                  javafmod.FMOD_Channel_Set3DMinMaxDistance(this.channel, this.clip.distanceMin, this.clip.distanceMax);
                  javafmod.FMOD_Channel_Set3DOcclusion(this.channel, 0.0F, 0.0F);
               }

               javafmod.FMOD_Channel_SetVolume(this.channel, this.getVolume());
               if (var1) {
                  javafmod.FMOD_Channel_SetPaused(this.channel, false);
               }

               javafmod.FMOD_Channel_SetReverbProperties(this.channel, 0, 0.0F);
               javafmod.FMOD_Channel_SetReverbProperties(this.channel, 1, 0.0F);
               javafmod.FMOD_System_SetReverbDefault(1, FMODManager.FMOD_PRESET_OFF);
               javafmod.FMOD_Channel_Set3DOcclusion(this.channel, 0.0F, 0.0F);
    return false;
            } else {
               var6 = this.clip.reverbMaxRange;
               var16 = IsoUtils.DistanceManhatten(var3, var4, IsoPlayer.getInstance().x, IsoPlayer.getInstance().y, var5, IsoPlayer.getInstance().z) / var6;
    IsoGridSquare var24 = IsoPlayer.getInstance().getCurrentSquare();
               if (var24 == nullptr) {
                  javafmod.FMOD_Channel_Set3DMinMaxDistance(this.channel, var2, this.clip.distanceMax);
                  javafmod.FMOD_Channel_SetVolume(this.channel, this.getVolume());
                  if (var1) {
                     javafmod.FMOD_Channel_SetPaused(this.channel, false);
                  }

    return false;
               } else {
                  if (var24.getRoom() == nullptr) {
                     if (!this.ambient) {
                        var16 += IsoPlayer.getInstance().numNearbyBuildingsRooms / 32.0F;
                     }

                     if (!this.ambient) {
                        var16 += 0.08F;
                     }
                  } else {
    float var25 = var24.getRoom().Squares.size();
                     if (!this.ambient) {
                        var16 += var25 / 500.0F;
                     }
                  }

                  if (var16 > 1.0F) {
                     var16 = 1.0F;
                  }

                  var16 *= var16;
                  var16 *= var16;
                  var16 *= this.clip.reverbFactor;
                  var16 *= 10.0F;
                  if (IsoPlayer.getInstance().getCurrentSquare().getRoom() == nullptr && var16 < 0.1F) {
                     var16 = 0.1F;
                  }

    uint8_t var10;
    uint8_t var11;
    uint8_t var26;
                  if (!this.ambient) {
                     if (var24.getRoom() != nullptr) {
                        var26 = 0;
                        var10 = 1;
                        var11 = 2;
                     } else {
                        var26 = 2;
                        var10 = 0;
                        var11 = 1;
                     }
                  } else {
                     var26 = 2;
                     var10 = 0;
                     var11 = 1;
                  }

    IsoGridSquare var12 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
                  if (var12 != nullptr
                     && var12.getZone() != nullptr
                     && (var12.getZone().getType() == "Forest") || var12.getZone().getType() == "DeepForest"))) {
                     var26 = 1;
                     var10 = 0;
                     var11 = 2;
                  }

                  javafmod.FMOD_Channel_SetReverbProperties(this.channel, var26, 0.0F);
                  javafmod.FMOD_Channel_SetReverbProperties(this.channel, var10, 0.0F);
                  javafmod.FMOD_Channel_SetReverbProperties(this.channel, var11, 0.0F);
                  javafmod.FMOD_Channel_Set3DMinMaxDistance(this.channel, var2, this.clip.distanceMax);
    IsoGridSquare var27 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
    float var28 = 0.0F;
    float var29 = 0.0F;
                  if (var27 != nullptr) {
                     if (this.emitter.dynamic_cast<IsoWindow*>(parent) != nullptr || this.emitter.dynamic_cast<IsoDoor*>(parent) != nullptr) {
    IsoRoom var32 = IsoPlayer.getInstance().getCurrentSquare().getRoom();
                        if (var32 != this.emitter.parent.square.getRoom()) {
                           if (var32 != nullptr && var32.getBuilding() == this.emitter.parent.square.getBuilding()) {
                              var28 = 0.33F;
                              var29 = 0.33F;
                           } else {
    void* var13 = nullptr;
                              if (this.emitter.dynamic_cast<IsoDoor*>(parent) != nullptr var14) {
                                 if (var14.north) {
                                    var13 = IsoWorld.instance.CurrentCell.getGridSquare(var14.getX(), var14.getY() - 1.0F, var14.getZ());
                                 } else {
                                    var13 = IsoWorld.instance.CurrentCell.getGridSquare(var14.getX() - 1.0F, var14.getY(), var14.getZ());
                                 }
                              } else {
    IsoWindow var36 = (IsoWindow)this.emitter.parent;
                                 if (var36.north) {
                                    var13 = IsoWorld.instance.CurrentCell.getGridSquare(var36.getX(), var36.getY() - 1.0F, var36.getZ());
                                 } else {
                                    var13 = IsoWorld.instance.CurrentCell.getGridSquare(var36.getX() - 1.0F, var36.getY(), var36.getZ());
                                 }
                              }

                              if (var13 != nullptr) {
    IsoRoom var33 = IsoPlayer.getInstance().getCurrentSquare().getRoom();
                                 if (var33 != nullptr || var13.getRoom() == nullptr) {
                                    if (var33 == nullptr || var13.getRoom() == nullptr || var33.building != var13.getBuilding()) {
                                       var28 = 0.33F;
                                       var29 = 0.33F;
                                    } else if (var33 != var13.getRoom()) {
                                       if (var33.def.level == var13.getZ()) {
                                          var28 = 0.33F;
                                          var29 = 0.33F;
                                       } else {
                                          var28 = 0.6F;
                                          var29 = 0.6F;
                                       }
                                    }
                                 }
                              }
                           }
                        }
                     } else if (var27.getRoom() != nullptr) {
    IsoRoom var30 = IsoPlayer.getInstance().getCurrentSquare().getRoom();
                        if (var30 == nullptr) {
                           var28 = 0.33F;
                           var29 = 0.23F;
                        } else if (var30 != var27.getRoom()) {
                           var28 = 0.24F;
                           var29 = 0.24F;
                        }

                        if (var30 != nullptr && var27.getRoom().getBuilding() != var30.getBuilding()) {
                           var28 = 1.0F;
                           var29 = 0.8F;
                        }

                        if (var30 != nullptr && var27.getRoom().def.level != (int)IsoPlayer.getInstance().z) {
                           var28 = 0.6F;
                           var29 = 0.6F;
                        }
                     } else {
    IsoRoom var31 = IsoPlayer.getInstance().getCurrentSquare().getRoom();
                        if (var31 != nullptr) {
                           var28 = 0.79F;
                           var29 = 0.59F;
                        }
                     }

                     if (!var27.isCouldSee(IsoPlayer.getPlayerIndex()) && var27 != IsoPlayer.getInstance().getCurrentSquare()) {
                        var28 += 0.4F;
                     }
                  } else {
                     if (IsoWorld.instance.MetaGrid.getRoomAt((int)var3, (int)var4, (int)var5) != nullptr) {
                        var28 = 1.0F;
                        var29 = 1.0F;
                     }

    IsoRoom var34 = IsoPlayer.getInstance().getCurrentSquare().getRoom();
                     if (var34 != nullptr) {
                        var28 += 0.94F;
                     } else {
                        var28 += 0.6F;
                     }
                  }

                  if (var27 != nullptr && (int)IsoPlayer.getInstance().z != var27.getZ()) {
                     var28 *= 1.3F;
                  }

                  if (var28 > 0.9F) {
                     var28 = 0.9F;
                  }

                  if (var29 > 0.9F) {
                     var29 = 0.9F;
                  }

                  if (this.emitter.emitterType == EmitterType.Footstep
                     && var5 > IsoPlayer.getInstance().z
                     && var27.getBuilding() == IsoPlayer.getInstance().getBuilding()) {
                     var28 = 0.0F;
                     var29 = 0.0F;
                  }

                  if ("HouseAlarm" == this.name)) {
                     var28 = 0.0F;
                     var29 = 0.0F;
                  }

                  javafmod.FMOD_Channel_Set3DOcclusion(this.channel, var28, var29);
                  javafmod.FMOD_Channel_SetVolume(this.channel, this.getVolume());
                  javafmod.FMOD_Channel_SetPitch(this.channel, this.pitch);
                  if (var1) {
                     javafmod.FMOD_Channel_SetPaused(this.channel, false);
                  }

                  this.lx = var3;
                  this.ly = var4;
                  this.lz = var5;
    return false;
               }
            }
         }
      }
   }

    void setParameterValue(FMOD_STUDIO_PARAMETER_DESCRIPTION var1, float var2) {
   }

    void setTimelinePosition(const std::string& var1) {
   }

    void triggerCue() {
   }

    bool isTriggeredCue() {
    return false;
   }

    bool restart() {
    return false;
   }
}
} // namespace fmod
} // namespace fmod
