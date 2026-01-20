#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/ZombieThumpManager.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace ai {
namespace states {


class ThumpState : public State {
public:
    static const ThumpState _instance = std::make_shared<ThumpState>();

    static ThumpState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      if (!GameClient.bClient || var1.isLocal()) {
         switch (Rand.Next(3)) {
            case 0:
               var1.setVariable("ThumpType", "DoorClaw");
               break;
            case 1:
               var1.setVariable("ThumpType", "Door");
               break;
            case 2:
               var1.setVariable("ThumpType", "DoorBang");
         }
      }

      if (GameClient.bClient && var1.isLocal()) {
         GameClient.sendThump(var1, var1.getThumpTarget());
      }
   }

    void execute(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
    Thumpable var3 = var1.getThumpTarget();
      if (dynamic_cast<IsoObject*>(var3) != nullptr) {
         var1.faceThisObject((IsoObject)var3);
      }

    bool var4 = GameServer.bServer && GameServer.bFastForward || !GameServer.bServer && IsoPlayer.allPlayersAsleep();
      if (var4 || var1.actionContext.hasEventOccurred("thumpframe")) {
         var1.actionContext.clearEvent("thumpframe");
         var1.setTimeThumping(var1.getTimeThumping() + 1);
         if (var2.TimeSinceSeenFlesh < 5.0F) {
            var1.setTimeThumping(0);
         }

    int var5 = 1;
         if (var1.getCurrentSquare() != nullptr) {
            var5 = var1.getCurrentSquare().getMovingObjects().size();
         }

         for (int var6 = 0; var6 < var5 && this.isThumpTargetValid(var1, var1.getThumpTarget()); var6++) {
            var1.getThumpTarget().Thump(var1);
         }

    Thumpable var12 = var1.getThumpTarget() == nullptr ? nullptr : var1.getThumpTarget().getThumpableFor(var1);
    bool var7 = GameServer.bServer || SoundManager.instance.isListenerInRange(var1.x, var1.y, 20.0F);
         if (var7 && !IsoPlayer.allPlayersAsleep()) {
            if (dynamic_cast<IsoWindow*>(var12) != nullptr) {
               var2.setThumpFlag(Rand.Next(3) == 0 ? 2 : 3);
               var2.setThumpCondition(var12.getThumpCondition());
               if (!GameServer.bServer) {
                  ZombieThumpManager.instance.addCharacter(var2);
               }
            } else if (var12 != nullptr) {
    std::string var8 = "ZombieThumpGeneric";
    IsoBarricade var9 = (IsoBarricade)Type.tryCastTo(var12, IsoBarricade.class);
               if (var9 == nullptr || !var9.isMetal() && !var9.isMetalBar()) {
                  if (dynamic_cast<IsoDoor*>(var12) != nullptr) {
                     var8 = ((IsoDoor)var12).getThumpSound();
                  } else if (dynamic_cast<IsoThumpable*>(var12) != nullptr) {
                     var8 = ((IsoThumpable)var12).getThumpSound();
                  }
               } else {
                  var8 = "ZombieThumpMetal";
               }

               if ("ZombieThumpGeneric" == var8)) {
                  var2.setThumpFlag(1);
               } else if ("ZombieThumpWindow" == var8)) {
                  var2.setThumpFlag(3);
               } else if ("ZombieThumpMetal" == var8)) {
                  var2.setThumpFlag(4);
               } else if ("ZombieThumpGarageDoor" == var8)) {
                  var2.setThumpFlag(5);
               } else {
                  var2.setThumpFlag(1);
               }

               var2.setThumpCondition(var12.getThumpCondition());
               if (!GameServer.bServer) {
                  ZombieThumpManager.instance.addCharacter(var2);
               }
            }
         }
      }

      if (!this.isThumpTargetValid(var1, var1.getThumpTarget())) {
         var1.setThumpTarget(nullptr);
         var1.setTimeThumping(0);
         if (dynamic_cast<IsoWindow*>(var3) != nullptr && ((IsoWindow)var3).canClimbThrough(var1)) {
            var1.climbThroughWindow((IsoWindow)var3);
         } else {
            if (dynamic_cast<IsoDoor*>(var3) != nullptr && (((IsoDoor)var3).open || var3.isDestroyed())) {
    IsoDoor var10 = (IsoDoor)var3;
    IsoGridSquare var13 = var10.getSquare();
    IsoGridSquare var15 = var10.getOppositeSquare();
               if (this.lungeThroughDoor(var2, var13, var15)) {
                  return;
               }
            }

            if (dynamic_cast<IsoThumpable*>(var3) != nullptr && ((IsoThumpable)var3).isDoor && (((IsoThumpable)var3).open || var3.isDestroyed())) {
    IsoThumpable var11 = (IsoThumpable)var3;
    IsoGridSquare var14 = var11.getSquare();
    IsoGridSquare var16 = var11.getInsideSquare();
               if (this.lungeThroughDoor(var2, var14, var16)) {
                  return;
               }
            }

            if (var2.LastTargetSeenX != -1) {
               var1.pathToLocation(var2.LastTargetSeenX, var2.LastTargetSeenY, var2.LastTargetSeenZ);
            }
         }
      }
   }

    void exit(IsoGameCharacter var1) {
      var1.setThumpTarget(nullptr);
      ((IsoZombie)var1).setThumpTimer(200);
      if (GameClient.bClient && var1.isLocal()) {
         GameClient.sendThump(var1, var1.getThumpTarget());
      }
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if (var2.m_EventName.equalsIgnoreCase("ThumpFrame")) {
      }
   }

    IsoPlayer findPlayer(int var1, int var2, int var3, int var4, int var5) {
      for (int var6 = var3; var6 <= var4; var6++) {
         for (int var7 = var1; var7 <= var2; var7++) {
    IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var7, var6, var5);
            if (var8 != nullptr) {
               for (int var9 = 0; var9 < var8.getMovingObjects().size(); var9++) {
    IsoMovingObject var10 = (IsoMovingObject)var8.getMovingObjects().get(var9);
                  if (dynamic_cast<IsoPlayer*>(var10) != nullptr && !((IsoPlayer)var10).isGhostMode()) {
                     return (IsoPlayer)var10;
                  }
               }
            }
         }
      }

    return nullptr;
   }

    bool lungeThroughDoor(IsoZombie var1, IsoGridSquare var2, IsoGridSquare var3) {
      if (var2 != nullptr && var3 != nullptr) {
    bool var4 = var2.getY() > var3.getY();
    IsoGridSquare var5 = nullptr;
    IsoPlayer var6 = nullptr;
         if (var1.getCurrentSquare() == var2) {
            var5 = var3;
            if (var4) {
               var6 = this.findPlayer(var3.getX() - 1, var3.getX() + 1, var3.getY() - 1, var3.getY(), var3.getZ());
            } else {
               var6 = this.findPlayer(var3.getX() - 1, var3.getX(), var3.getY() - 1, var3.getY() + 1, var3.getZ());
            }
         } else if (var1.getCurrentSquare() == var3) {
            var5 = var2;
            if (var4) {
               var6 = this.findPlayer(var2.getX() - 1, var2.getX() + 1, var2.getY(), var2.getY() + 1, var2.getZ());
            } else {
               var6 = this.findPlayer(var2.getX(), var2.getX() + 1, var2.getY() - 1, var2.getY() + 1, var2.getZ());
            }
         }

         if (var6 != nullptr && !LosUtil.lineClearCollide(var5.getX(), var5.getY(), var5.getZ(), (int)var6.getX(), (int)var6.getY(), (int)var6.getZ(), false)) {
            var1.setTarget(var6);
            var1.vectorToTarget.x = var6.getX();
            var1.vectorToTarget.y = var6.getY();
            var1.vectorToTarget.x = var1.vectorToTarget.x - var1.getX();
            var1.vectorToTarget.y = var1.vectorToTarget.y - var1.getY();
            var1.TimeSinceSeenFlesh = 0.0F;
            var1.setThumpTarget(nullptr);
    return true;
         } else {
    return false;
         }
      } else {
    return false;
      }
   }

    static int getFastForwardDamageMultiplier() {
    GameTime var0 = GameTime.getInstance();
      if (GameServer.bServer) {
         return (int)(GameServer.bFastForward ? ServerOptions.instance.FastForwardMultiplier.getValue() / var0.getDeltaMinutesPerDay() : 1.0);
      } else if (GameClient.bClient) {
         return (int)(GameClient.bFastForward ? ServerOptions.instance.FastForwardMultiplier.getValue() / var0.getDeltaMinutesPerDay() : 1.0);
      } else {
         return IsoPlayer.allPlayersAsleep() ? (int)(200.0F * (30.0F / PerformanceSettings.getLockFPS()) / 1.6F) : (int)var0.getTrueMultiplier();
      }
   }

    bool isThumpTargetValid(IsoGameCharacter var1, Thumpable var2) {
      if (var2 == nullptr) {
    return false;
      } else if (var2.isDestroyed()) {
    return false;
      } else {
    IsoObject var3 = (IsoObject)Type.tryCastTo(var2, IsoObject.class);
         if (var3 == nullptr) {
    return false;
         } else if (dynamic_cast<BaseVehicle*>(var2) != nullptr) {
            return var3.getMovingObjectIndex() != -1;
         } else if (var3.getObjectIndex() == -1) {
    return false;
         } else {
    int var4 = var3.getSquare().getX() / 10;
    int var5 = var3.getSquare().getY() / 10;
    IsoChunk var6 = GameServer.bServer ? ServerMap.instance.getChunk(var4, var5) : IsoWorld.instance.CurrentCell.getChunk(var4, var5);
    return var6 = = nullptr ? false : var2.getThumpableFor(var1) != nullptr;
         }
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
