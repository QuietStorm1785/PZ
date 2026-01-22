#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODSoundEmitter.h"
#include "org/joml/Vector3f.h"
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/ai/states/ZombieIdleState.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace vehicles {


class AttackVehicleState : public State {
public:
    static const AttackVehicleState _instance = std::make_shared<AttackVehicleState>();
    BaseSoundEmitter emitter;
    const Vector3f worldPos = std::make_shared<Vector3f>();

    static AttackVehicleState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
   }

    void execute(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
      if (var2.dynamic_cast<IsoGameCharacter*>(target) != nullptr var3) {
         if (var3.isDead()) {
            if (var3.getLeaveBodyTimedown() > 3600.0F) {
               var2.changeState(ZombieIdleState.instance());
               var2.setTarget(nullptr);
            } else {
               var3.setLeaveBodyTimedown(var3.getLeaveBodyTimedown() + GameTime.getInstance().getMultiplier() / 1.6F);
               if (!GameServer.bServer && !Core.SoundDisabled && Rand.Next(Rand.AdjustForFramerate(15)) == 0) {
                  if (this.emitter == nullptr) {
                     this.emitter = std::make_unique<FMODSoundEmitter>();
                  }

    std::string var6 = var2.isFemale() ? "FemaleZombieEating" : "MaleZombieEating";
                  if (!this.emitter.isPlaying(var6)) {
                     this.emitter.playSound(var6);
                  }
               }
            }

            var2.TimeSinceSeenFlesh = 0.0F;
         } else {
    BaseVehicle var4 = var3.getVehicle();
            if (var4 != nullptr && var4.isCharacterAdjacentTo(var1)) {
    Vector3f var5 = var4.chooseBestAttackPosition(var3, var1, this.worldPos);
               if (var5 == nullptr) {
                  if (var2.AllowRepathDelay <= 0.0F) {
                     var1.pathToCharacter(var3);
                     var2.AllowRepathDelay = 6.25F;
                  }
               } else if (var5 != nullptr && (Math.abs(var5.x - var1.x) > 0.1F || Math.abs(var5.y - var1.y) > 0.1F)) {
                  if (!(Math.abs(var4.getCurrentSpeedKmHour()) > 0.8F) || !var4.isCharacterAdjacentTo(var1) && !(var4.DistToSquared(var1) < 16.0F)) {
                     if (var2.AllowRepathDelay <= 0.0F) {
                        var1.pathToCharacter(var3);
                        var2.AllowRepathDelay = 6.25F;
                     }
                  }
               } else {
                  var1.faceThisObject(var3);
               }
            }
         }
      }
   }

    void exit(IsoGameCharacter var1) {
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
    IsoZombie var3 = (IsoZombie)var1;
      if (var3.dynamic_cast<IsoGameCharacter*>(target) != nullptr var4) {
    BaseVehicle var5 = var4.getVehicle();
         if (var5 != nullptr) {
            if (!var4.isDead()) {
               if (var2.m_EventName.equalsIgnoreCase("AttackCollisionCheck")) {
                  var4.getBodyDamage().AddRandomDamageFromZombie(var3, nullptr);
                  var4.getBodyDamage().Update();
                  if (var4.isDead()) {
                     if (var4.isFemale()) {
                        var3.getEmitter().playVocals("FemaleBeingEatenDeath");
                     } else {
                        var3.getEmitter().playVocals("MaleBeingEatenDeath");
                     }

                     var4.setHealth(0.0F);
                  } else if (var4.isAsleep()) {
                     if (GameServer.bServer) {
                        var4.sendObjectChange("wakeUp");
                        var4.setAsleep(false);
                     } else {
                        var4.forceAwake();
                     }
                  }
               } else if (var2.m_EventName.equalsIgnoreCase("ThumpFrame")) {
    VehicleWindow var6 = nullptr;
    VehiclePart var7 = nullptr;
    int var8 = var5.getSeat(var4);
    std::string var9 = var5.getPassengerArea(var8);
                  if (var5.isInArea(var9, var1)) {
    VehiclePart var10 = var5.getPassengerDoor(var8);
                     if (var10 != nullptr && var10.getDoor() != nullptr && var10.getInventoryItem() != nullptr && !var10.getDoor().isOpen()) {
                        var6 = var10.findWindow();
                        if (var6 != nullptr && !var6.isHittable()) {
                           var6 = nullptr;
                        }

                        if (var6 == nullptr) {
                           var7 = var10;
                        }
                     }
                  } else {
                     var7 = var5.getNearestBodyworkPart(var1);
                     if (var7 != nullptr) {
                        var6 = var7.getWindow();
                        if (var6 == nullptr) {
                           var6 = var7.findWindow();
                        }

                        if (var6 != nullptr && !var6.isHittable()) {
                           var6 = nullptr;
                        }

                        if (var6 != nullptr) {
                           var7 = nullptr;
                        }
                     }
                  }

                  if (var6 != nullptr) {
                     var6.damage(var3.strength);
                     var5.setBloodIntensity(var6.part.getId(), var5.getBloodIntensity(var6.part.getId()) + 0.025F);
                     if (!GameServer.bServer) {
                        var3.setVehicleHitLocation(var5);
                        var1.getEmitter().playSound("ZombieThumpVehicleWindow", var5);
                     }

                     var3.setThumpFlag(3);
                  } else {
                     if (!GameServer.bServer) {
                        var3.setVehicleHitLocation(var5);
                        var1.getEmitter().playSound("ZombieThumpVehicle", var5);
                     }

                     var3.setThumpFlag(1);
                  }

                  var5.setAddThumpWorldSound(true);
                  if (var7 != nullptr && var7.getWindow() == nullptr && var7.getCondition() > 0) {
                     var7.setCondition(var7.getCondition() - var3.strength);
                     var7.doInventoryItemStats(var7.getInventoryItem(), 0);
                     var5.transmitPartCondition(var7);
                  }

                  if (var4.isAsleep()) {
                     if (GameServer.bServer) {
                        var4.sendObjectChange("wakeUp");
                        var4.setAsleep(false);
                     } else {
                        var4.forceAwake();
                     }
                  }
               }
            }
         }
      }
   }

    bool isAttacking(IsoGameCharacter var1) {
    return true;
   }

    bool isPassengerExposed(IsoGameCharacter var1) {
      if (!(dynamic_cast<IsoZombie*>(var1) != nullptr var2)) {
    return false;
      } else if (!(var2.dynamic_cast<IsoGameCharacter*>(target) != nullptr var3)) {
    return false;
      } else {
    BaseVehicle var4 = var3.getVehicle();
         if (var4 == nullptr) {
    return false;
         } else {
    bool var5 = false;
    void* var6 = nullptr;
    int var7 = var4.getSeat(var3);
    std::string var8 = var4.getPassengerArea(var7);
    VehiclePart var9 = nullptr;
            if (var4.isInArea(var8, var1)) {
               var9 = var4.getPassengerDoor(var7);
               if (var9 != nullptr && var9.getDoor() != nullptr) {
                  if (var9.getInventoryItem() != nullptr && !var9.getDoor().isOpen()) {
                     var6 = var9.findWindow();
                     if (var6 != nullptr) {
                        if (!var6.isHittable()) {
                           var6 = nullptr;
                        }

                        var5 = var6 == nullptr;
                     } else {
                        var5 = false;
                     }
                  } else {
                     var5 = true;
                  }
               }
            } else {
               var9 = var4.getNearestBodyworkPart(var1);
               if (var9 != nullptr) {
                  var6 = var9.findWindow();
                  if (var6 != nullptr && !var6.isHittable()) {
                     var6 = nullptr;
                  }
               }
            }

    return var5;
         }
      }
   }
}
} // namespace vehicles
} // namespace zombie
