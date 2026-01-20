#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerRoom.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpawnPoints.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBSafehouse : public RandomizedBuildingBase {
public:
    void randomizeBuilding(BuildingDef var1) {
      var1.bAlarmed = false;
      var1.setHasBeenVisited(true);
    ItemPickerRoom var2 = (ItemPickerRoom)ItemPickerJava.rooms.get("SafehouseLoot");
    IsoCell var3 = IsoWorld.instance.CurrentCell;

      for (int var4 = var1.x - 1; var4 < var1.x2 + 1; var4++) {
         for (int var5 = var1.y - 1; var5 < var1.y2 + 1; var5++) {
            for (int var6 = 0; var6 < 8; var6++) {
    IsoGridSquare var7 = var3.getGridSquare(var4, var5, var6);
               if (var7 != nullptr) {
                  for (int var8 = 0; var8 < var7.getObjects().size(); var8++) {
    IsoObject var9 = (IsoObject)var7.getObjects().get(var8);
                     if (dynamic_cast<IsoDoor*>(var9) != nullptr && ((IsoDoor)var9).isBarricadeAllowed() && !SpawnPoints.instance.isSpawnBuilding(var1)) {
    IsoGridSquare var10 = var7.getRoom() == nullptr ? var7 : ((IsoDoor)var9).getOppositeSquare();
                        if (var10 != nullptr && var10.getRoom() == nullptr) {
    bool var11 = var10 != var7;
    IsoBarricade var12 = IsoBarricade.AddBarricadeToObject((IsoDoor)var9, var11);
                           if (var12 != nullptr) {
    int var13 = Rand.Next(1, 4);

                              for (int var14 = 0; var14 < var13; var14++) {
                                 var12.addPlank(nullptr, nullptr);
                              }

                              if (GameServer.bServer) {
                                 var12.transmitCompleteItemToClients();
                              }
                           }
                        }
                     }

                     if (dynamic_cast<IsoWindow*>(var9) != nullptr) {
    IsoGridSquare var15 = var7.getRoom() == nullptr ? var7 : ((IsoWindow)var9).getOppositeSquare();
                        if (((IsoWindow)var9).isBarricadeAllowed() && var6 == 0 && var15 != nullptr && var15.getRoom() == nullptr) {
    bool var16 = var15 != var7;
    IsoBarricade var17 = IsoBarricade.AddBarricadeToObject((IsoWindow)var9, var16);
                           if (var17 != nullptr) {
    int var18 = Rand.Next(1, 4);

                              for (int var19 = 0; var19 < var18; var19++) {
                                 var17.addPlank(nullptr, nullptr);
                              }

                              if (GameServer.bServer) {
                                 var17.transmitCompleteItemToClients();
                              }
                           }
                        } else {
                           ((IsoWindow)var9).addSheet(nullptr);
                           ((IsoWindow)var9).HasCurtains().ToggleDoor(nullptr);
                        }
                     }

                     if (var9.getContainer() != nullptr
                        && var7.getRoom() != nullptr
                        && var7.getRoom().getBuilding().getDef() == var1
                        && Rand.Next(100) <= 70
                        && var7.getRoom().getName() != nullptr
                        && var2.Containers.containsKey(var9.getContainer().getType())) {
                        var9.getContainer().clear();
                        ItemPickerJava.fillContainerType(var2, var9.getContainer(), "", nullptr);
                        ItemPickerJava.updateOverlaySprite(var9);
                        var9.getContainer().setExplored(true);
                     }
                  }
               }
            }
         }
      }

      var1.setAllExplored(true);
      var1.bAlarmed = false;
      this.addZombies(var1);
   }

    void addZombies(BuildingDef var1) {
      this.addZombies(var1, 0, nullptr, nullptr, nullptr);
      if (Rand.Next(5) == 0) {
         this.addZombies(var1, 1, "Survivalist", nullptr, nullptr);
      }

      if (Rand.Next(100) <= 60) {
         RandomizedBuildingBase.createRandomDeadBody(this.getLivingRoomOrKitchen(var1), Rand.Next(3, 7));
      }

      if (Rand.Next(100) <= 60) {
         RandomizedBuildingBase.createRandomDeadBody(this.getLivingRoomOrKitchen(var1), Rand.Next(3, 7));
      }
   }

    bool isValid(BuildingDef var1, bool var2) {
      if (!super.isValid(var1, var2)) {
    return false;
      } else {
         return var1.getRooms().size() > 20 ? false : !SpawnPoints.instance.isSpawnBuilding(var1);
      }
   }

    public RBSafehouse() {
      this.name = "Safehouse";
      this.setChance(10);
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
