#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/VirtualZombieManager.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSZombieLockedBathroom : public RandomizedDeadSurvivorBase {
public:
    void randomizeDeadSurvivor(BuildingDef var1) {
    IsoDeadBody var2 = nullptr;

      for (int var3 = 0; var3 < var1.rooms.size(); var3++) {
    RoomDef var4 = (RoomDef)var1.rooms.get(var3);
    IsoGridSquare var5 = nullptr;
         if ("bathroom" == var4.name)) {
            if (IsoWorld.getZombiesEnabled()) {
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var4.getX(), var4.getY(), var4.getZ());
               if (var6 != nullptr && var6.getRoom() != nullptr) {
    IsoRoom var7 = var6.getRoom();
                  var6 = var7.getRandomFreeSquare();
                  if (var6 != nullptr) {
                     VirtualZombieManager.instance.choices.clear();
                     VirtualZombieManager.instance.choices.push_back(var6);
    IsoZombie var8 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.fromIndex(Rand.Next(8)).index(), false);
                     ZombieSpawnRecorder.instance.record(var8, this.getClass().getSimpleName());
                  }
               }
            }

            for (int var12 = var4.x - 1; var12 < var4.x2 + 1; var12++) {
               for (int var13 = var4.y - 1; var13 < var4.y2 + 1; var13++) {
                  var5 = IsoWorld.instance.getCell().getGridSquare(var12, var13, var4.getZ());
                  if (var5 != nullptr) {
    IsoDoor var14 = var5.getIsoDoor();
                     if (var14 != nullptr && this.isDoorToRoom(var14, var4)) {
                        if (var14.IsOpen()) {
                           var14.ToggleDoor(nullptr);
                        }

    IsoBarricade var9 = IsoBarricade.AddBarricadeToObject(var14, var5.getRoom().def == var4);
                        if (var9 != nullptr) {
                           var9.addPlank(nullptr, nullptr);
                           if (GameServer.bServer) {
                              var9.transmitCompleteItemToClients();
                           }
                        }

                        var2 = this.addDeadBodyTheOtherSide(var14);
                        break;
                     }
                  }
               }

               if (var2 != nullptr) {
                  break;
               }
            }

            if (var2 != nullptr) {
               var2.setPrimaryHandItem(super.addWeapon("Base.Pistol", true));
            }

            return;
         }
      }
   }

    bool isDoorToRoom(IsoDoor var1, RoomDef var2) {
      if (var1 != nullptr && var2 != nullptr) {
    IsoGridSquare var3 = var1.getSquare();
    IsoGridSquare var4 = var1.getOppositeSquare();
         return var3 != nullptr && var4 != nullptr ? var3.getRoomID() == var2.ID != (var4.getRoomID() == var2.ID) : false;
      } else {
    return false;
      }
   }

    bool checkIsBathroom(IsoGridSquare var1) {
      return var1.getRoom() != nullptr && "bathroom" == var1.getRoom().getName());
   }

    IsoDeadBody addDeadBodyTheOtherSide(IsoDoor var1) {
    void* var2 = nullptr;
      if (var1.north) {
         var2 = IsoWorld.instance.getCell().getGridSquare(var1.getX(), var1.getY(), var1.getZ());
         if (this.checkIsBathroom((IsoGridSquare)var2)) {
            var2 = IsoWorld.instance.getCell().getGridSquare(var1.getX(), var1.getY() - 1.0F, var1.getZ());
         }
      } else {
         var2 = IsoWorld.instance.getCell().getGridSquare(var1.getX(), var1.getY(), var1.getZ());
         if (this.checkIsBathroom((IsoGridSquare)var2)) {
            var2 = IsoWorld.instance.getCell().getGridSquare(var1.getX() - 1.0F, var1.getY(), var1.getZ());
         }
      }

      return RandomizedDeadSurvivorBase.createRandomDeadBody(var2.getX(), var2.getY(), var2.getZ(), nullptr, Rand.Next(5, 10));
   }

    public RDSZombieLockedBathroom() {
      this.name = "Locked in Bathroom";
      this.setChance(5);
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
