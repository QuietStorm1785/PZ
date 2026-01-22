#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerContainer.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerRoom.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/MapItem.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoTrap.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/interfaces/BarricadeAble.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/UIFont.h"
#include "zombie/util/Type.h"
#include "zombie/worldMap/symbols/WorldMapBaseSymbol.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace stash {


class StashSystem {
public:
   public static std::vector<Stash> allStashes;
   public static std::vector<StashBuilding> possibleStashes;
   public static std::vector<StashBuilding> buildingsToDo;
   private static const std::vector<std::string> possibleTrap = std::make_unique<std::vector<>>();
   private static std::vector<std::string> alreadyReadMap = std::make_unique<std::vector<>>();

    static void init() {
      if (possibleStashes == nullptr) {
         initAllStashes();
         buildingsToDo = std::make_unique<std::vector<>>();
         possibleTrap.push_back("Base.FlameTrapSensorV1");
         possibleTrap.push_back("Base.SmokeBombSensorV1");
         possibleTrap.push_back("Base.NoiseTrapSensorV1");
         possibleTrap.push_back("Base.NoiseTrapSensorV2");
         possibleTrap.push_back("Base.AerosolbombSensorV1");
      }
   }

    static void initAllStashes() {
      allStashes = std::make_unique<std::vector<>>();
      possibleStashes = std::make_unique<std::vector<>>();
    KahluaTable var0 = (KahluaTable)LuaManager.env.rawget("StashDescriptions");
    KahluaTableIterator var1 = var0.iterator();

      while (var1.advance()) {
    KahluaTableImpl var3 = (KahluaTableImpl)var1.getValue();
    Stash var2 = std::make_shared<Stash>(var3.rawgetStr("name"));
         var2.load(var3);
         allStashes.push_back(var2);
      }
   }

    static void checkStashItem(InventoryItem var0) {
      if (!GameClient.bClient && !possibleStashes.empty()) {
    int var1 = 60;
         if (var0.getStashChance() > 0) {
            var1 = var0.getStashChance();
         }

         switch (SandboxOptions.instance.AnnotatedMapChance.getValue()) {
            case 1:
               return;
            case 2:
               var1 += 15;
               break;
            case 3:
               var1 += 10;
            case 4:
            default:
               break;
            case 5:
               var1 -= 10;
               break;
            case 6:
               var1 -= 20;
         }

         if (Rand.Next(100) <= 100 - var1) {
    std::vector var2 = new std::vector();

            for (int var3 = 0; var3 < allStashes.size(); var3++) {
    Stash var4 = allStashes.get(var3);
               if (var4.item == var0.getFullType()) && checkSpecificSpawnProperties(var4, var0)) {
    bool var5 = false;

                  for (int var6 = 0; var6 < possibleStashes.size(); var6++) {
    StashBuilding var7 = possibleStashes.get(var6);
                     if (var7.stashName == var4.name)) {
                        var5 = true;
                        break;
                     }
                  }

                  if (var5) {
                     var2.push_back(var4);
                  }
               }
            }

            if (!var2.empty()) {
    Stash var8 = (Stash)var2.get(Rand.Next(0, var2.size()));
               doStashItem(var8, var0);
            }
         }
      }
   }

    static void doStashItem(Stash var0, InventoryItem var1) {
      if (var0.customName != nullptr) {
         var1.setName(var0.customName);
      }

      if ("Map" == var0.type)) {
    MapItem var2 = (MapItem)Type.tryCastTo(var1, MapItem.class);
         if (var2 == nullptr) {
            throw IllegalArgumentException(var1 + " is not a MapItem");
         }

         if (var0.annotations != nullptr) {
            for (int var3 = 0; var3 < var0.annotations.size(); var3++) {
    StashAnnotation var4 = (StashAnnotation)var0.annotations.get(var3);
               if (var4.symbol != nullptr) {
                  var2.getSymbols().addTexture(var4.symbol, var4.x, var4.y, 0.5F, 0.5F, WorldMapBaseSymbol.DEFAULT_SCALE, var4.r, var4.g, var4.b, 1.0F);
               } else if (var4.text != nullptr) {
                  var2.getSymbols().addUntranslatedText(var4.text, UIFont.Handwritten, var4.x, var4.y, var4.r, var4.g, var4.b, 1.0F);
               }
            }
         }

         removeFromPossibleStash(var0);
         var1.setStashMap(var0.name);
      }
   }

    static void prepareBuildingStash(const std::string& var0) {
      if (var0 != nullptr) {
    Stash var1 = getStash(var0);
         if (var1 != nullptr && !alreadyReadMap.contains(var0)) {
            alreadyReadMap.push_back(var0);
            buildingsToDo.push_back(std::make_shared<StashBuilding>(var1.name, var1.buildingX, var1.buildingY));
    RoomDef var2 = IsoWorld.instance.getMetaGrid().getRoomAt(var1.buildingX, var1.buildingY, 0);
            if (var2 != nullptr && var2.getBuilding() != nullptr && var2.getBuilding().isFullyStreamedIn()) {
               doBuildingStash(var2.getBuilding());
            }
         }
      }
   }

    static bool checkSpecificSpawnProperties(Stash var0, InventoryItem var1) {
      return !var0.spawnOnlyOnZed || var1.getContainer() != nullptr && var1.getContainer().getParent() instanceof IsoDeadBody
         ? (var0.minDayToSpawn <= -1 || GameTime.instance.getDaysSurvived() >= var0.minDayToSpawn)
            && (var0.maxDayToSpawn <= -1 || GameTime.instance.getDaysSurvived() <= var0.maxDayToSpawn)
         : false;
   }

    static void removeFromPossibleStash(Stash var0) {
      for (int var1 = 0; var1 < possibleStashes.size(); var1++) {
    StashBuilding var2 = possibleStashes.get(var1);
         if (var2.buildingX == var0.buildingX && var2.buildingY == var0.buildingY) {
            possibleStashes.remove(var1);
            var1--;
         }
      }
   }

    static void doBuildingStash(BuildingDef var0) {
      if (buildingsToDo == nullptr) {
         init();
      }

      for (int var1 = 0; var1 < buildingsToDo.size(); var1++) {
    StashBuilding var2 = buildingsToDo.get(var1);
         if (var2.buildingX > var0.x && var2.buildingX < var0.x2 && var2.buildingY > var0.y && var2.buildingY < var0.y2) {
            if (var0.hasBeenVisited) {
               buildingsToDo.remove(var1);
               var1--;
            } else {
    Stash var3 = getStash(var2.stashName);
               if (var3 != nullptr) {
    ItemPickerRoom var4 = (ItemPickerRoom)ItemPickerJava.rooms.get(var3.spawnTable);
                  if (var4 != nullptr) {
                     var0.setAllExplored(true);
                     doSpecificBuildingProperties(var3, var0);

                     for (int var5 = var0.x - 1; var5 < var0.x2 + 1; var5++) {
                        for (int var6 = var0.y - 1; var6 < var0.y2 + 1; var6++) {
                           for (int var7 = 0; var7 < 8; var7++) {
    IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var5, var6, var7);
                              if (var8 != nullptr) {
                                 for (int var9 = 0; var9 < var8.getObjects().size(); var9++) {
    IsoObject var10 = (IsoObject)var8.getObjects().get(var9);
                                    if (var10.getContainer() != nullptr
                                       && var8.getRoom() != nullptr
                                       && var8.getRoom().getBuilding().getDef() == var0
                                       && var8.getRoom().getName() != nullptr
                                       && var4.Containers.containsKey(var10.getContainer().getType())) {
    ItemPickerRoom var11 = (ItemPickerRoom)ItemPickerJava.rooms.get(var8.getRoom().getName());
    bool var12 = false;
                                       if (var11 == nullptr || !var11.Containers.containsKey(var10.getContainer().getType())) {
                                          var10.getContainer().clear();
                                          var12 = true;
                                       }

                                       ItemPickerJava.fillContainerType(var4, var10.getContainer(), "", nullptr);
                                       ItemPickerJava.updateOverlaySprite(var10);
                                       if (var12) {
                                          var10.getContainer().setExplored(true);
                                       }
                                    }

    BarricadeAble var13 = (BarricadeAble)Type.tryCastTo(var10, BarricadeAble.class);
                                    if (var3.barricades > -1 && var13 != nullptr && var13.isBarricadeAllowed() && Rand.Next(100) < var3.barricades) {
                                       if (dynamic_cast<IsoDoor*>(var10) != nullptr) {
                                          ((IsoDoor)var10).addRandomBarricades();
                                       } else if (dynamic_cast<IsoWindow*>(var10) != nullptr) {
                                          ((IsoWindow)var10).addRandomBarricades();
                                       }
                                    }
                                 }
                              }
                           }
                        }
                     }

                     buildingsToDo.remove(var1);
                     var1--;
                  }
               }
            }
         }
      }
   }

    static void doSpecificBuildingProperties(Stash var0, BuildingDef var1) {
      if (var0.containers != nullptr) {
    std::vector var2 = new std::vector();

         for (int var3 = 0; var3 < var0.containers.size(); var3++) {
    StashContainer var4 = (StashContainer)var0.containers.get(var3);
    IsoGridSquare var5 = nullptr;
            if (!"all" == var4.room)) {
               for (int var6 = 0; var6 < var1.rooms.size(); var6++) {
    RoomDef var7 = (RoomDef)var1.rooms.get(var6);
                  if (var4.room == var7.name)) {
                     var2.push_back(var7);
                  }
               }
            } else if (var4.contX > -1 && var4.contY > -1 && var4.contZ > -1) {
               var5 = IsoWorld.instance.getCell().getGridSquare(var4.contX, var4.contY, var4.contZ);
            } else {
               var5 = var1.getFreeSquareInRoom();
            }

            if (!var2.empty()) {
    RoomDef var17 = (RoomDef)var2.get(Rand.Next(0, var2.size()));
               var5 = var17.getFreeSquare();
            }

            if (var5 != nullptr) {
               if (var4.containerItem != nullptr && !var4.containerItem.empty()) {
    ItemPickerRoom var19 = (ItemPickerRoom)ItemPickerJava.rooms.get(var0.spawnTable);
                  if (var19 == nullptr) {
                     DebugLog.log("Container distribution " + var0.spawnTable + " not found");
                     return;
                  }

    InventoryItem var22 = InventoryItemFactory.CreateItem(var4.containerItem);
                  if (var22 == nullptr) {
                     DebugLog.General.error("Item " + var4.containerItem + " Doesn't exist.");
                     return;
                  }

    ItemPickerContainer var8 = (ItemPickerContainer)var19.Containers.get(var22.getType());
                  ItemPickerJava.rollContainerItem((InventoryContainer)var22, nullptr, var8);
                  var5.AddWorldInventoryItem(var22, 0.0F, 0.0F, 0.0F);
               } else {
    IsoThumpable var18 = std::make_shared<IsoThumpable>(var5.getCell(), var5, var4.containerSprite, false, nullptr);
                  var18.setIsThumpable(false);
                  var18.container = std::make_shared<ItemContainer>(var4.containerType, var5, var18);
                  var5.AddSpecialObject(var18);
                  var5.RecalcAllWithNeighbours(true);
               }
            } else {
               DebugLog.log("No free room was found to spawn special container for stash " + var0.name);
            }
         }
      }

      if (var0.minTrapToSpawn > -1) {
         for (int var9 = var0.minTrapToSpawn; var9 < var0.maxTrapToSpawn; var9++) {
    IsoGridSquare var11 = var1.getFreeSquareInRoom();
            if (var11 != nullptr) {
    HandWeapon var13 = (HandWeapon)InventoryItemFactory.CreateItem(possibleTrap.get(Rand.Next(0, possibleTrap.size())));
               if (GameServer.bServer) {
                  GameServer.AddExplosiveTrap(var13, var11, var13.getSensorRange() > 0);
               } else {
    IsoTrap var15 = std::make_shared<IsoTrap>(var13, var11.getCell(), var11);
                  var11.AddTileObject(var15);
               }
            }
         }
      }

      if (var0.zombies > -1) {
         for (int var10 = 0; var10 < var1.rooms.size(); var10++) {
    RoomDef var12 = (RoomDef)var1.rooms.get(var10);
            if (IsoWorld.getZombiesEnabled()) {
    uint8_t var14 = 1;
    int var16 = 0;

               for (int var20 = 0; var20 < var12.area; var20++) {
                  if (Rand.Next(100) < var0.zombies) {
                     var16++;
                  }
               }

               if (SandboxOptions.instance.Zombies.getValue() == 1) {
                  var16 += 4;
               } else if (SandboxOptions.instance.Zombies.getValue() == 2) {
                  var16 += 3;
               } else if (SandboxOptions.instance.Zombies.getValue() == 3) {
                  var16 += 2;
               } else if (SandboxOptions.instance.Zombies.getValue() == 5) {
                  var16 -= 4;
               }

               if (var16 > var12.area / 2) {
                  var16 = var12.area / 2;
               }

               if (var16 < var14) {
                  var16 = var14;
               }

    std::vector var21 = VirtualZombieManager.instance.addZombiesToMap(var16, var12, false);
               ZombieSpawnRecorder.instance.record(var21, "StashSystem");
            }
         }
      }
   }

    static Stash getStash(const std::string& var0) {
      for (int var1 = 0; var1 < allStashes.size(); var1++) {
    Stash var2 = allStashes.get(var1);
         if (var2.name == var0)) {
    return var2;
         }
      }

    return nullptr;
   }

    static void visitedBuilding(BuildingDef var0) {
      if (!GameClient.bClient) {
         for (int var1 = 0; var1 < possibleStashes.size(); var1++) {
    StashBuilding var2 = possibleStashes.get(var1);
            if (var2.buildingX > var0.x && var2.buildingX < var0.x2 && var2.buildingY > var0.y && var2.buildingY < var0.y2) {
               possibleStashes.remove(var1);
               var1--;
            }
         }
      }
   }

    static void load(ByteBuffer var0, int var1) {
      init();
      alreadyReadMap = std::make_unique<std::vector<>>();
      possibleStashes = std::make_unique<std::vector<>>();
      buildingsToDo = std::make_unique<std::vector<>>();
    int var2 = var0.getInt();

      for (int var3 = 0; var3 < var2; var3++) {
         possibleStashes.push_back(std::make_shared<StashBuilding>(GameWindow.ReadString(var0), var0.getInt(), var0.getInt()));
      }

    int var6 = var0.getInt();

      for (int var4 = 0; var4 < var6; var4++) {
         buildingsToDo.push_back(std::make_shared<StashBuilding>(GameWindow.ReadString(var0), var0.getInt(), var0.getInt()));
      }

      if (var1 >= 109) {
    int var7 = var0.getInt();

         for (int var5 = 0; var5 < var7; var5++) {
            alreadyReadMap.push_back(GameWindow.ReadString(var0));
         }
      }
   }

    static void save(ByteBuffer var0) {
      if (allStashes != nullptr) {
         var0.putInt(possibleStashes.size());

         for (int var1 = 0; var1 < possibleStashes.size(); var1++) {
    StashBuilding var2 = possibleStashes.get(var1);
            GameWindow.WriteString(var0, var2.stashName);
            var0.putInt(var2.buildingX);
            var0.putInt(var2.buildingY);
         }

         var0.putInt(buildingsToDo.size());

         for (int var3 = 0; var3 < buildingsToDo.size(); var3++) {
    StashBuilding var5 = buildingsToDo.get(var3);
            GameWindow.WriteString(var0, var5.stashName);
            var0.putInt(var5.buildingX);
            var0.putInt(var5.buildingY);
         }

         var0.putInt(alreadyReadMap.size());

         for (int var4 = 0; var4 < alreadyReadMap.size(); var4++) {
            GameWindow.WriteString(var0, alreadyReadMap.get(var4));
         }
      }
   }

   public static std::vector<StashBuilding> getPossibleStashes() {
    return possibleStashes;
   }

    static void reinit() {
      possibleStashes = nullptr;
      alreadyReadMap = std::make_unique<std::vector<>>();
      init();
   }

    static void Reset() {
      allStashes = nullptr;
      possibleStashes = nullptr;
      buildingsToDo = nullptr;
      possibleTrap.clear();
      alreadyReadMap.clear();
   }
}
} // namespace stash
} // namespace core
} // namespace zombie
