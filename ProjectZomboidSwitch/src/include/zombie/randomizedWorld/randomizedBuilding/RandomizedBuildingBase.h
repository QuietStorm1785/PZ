#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerRoom.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/WeaponPart.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/SpawnPoints.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/randomizedWorld/RandomizedWorldBase.h"
#include <iterator>

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RandomizedBuildingBase : public RandomizedWorldBase {
public:
    int chance = 0;
    static int totalChance = 0;
   private static std::unordered_map<RandomizedBuildingBase, int> rbMap = std::make_unique<std::unordered_map<>>();
    static const int KBBuildingX = 10744;
    static const int KBBuildingY = 9409;
    bool alwaysDo = false;
   private static std::unordered_map<std::string, std::string> weaponsList = std::make_unique<std::unordered_map<>>();

    void randomizeBuilding(BuildingDef var1) {
      var1.bAlarmed = false;
   }

    void init() {
      if (weaponsList.empty()) {
         weaponsList.put("Base.Shotgun", "Base.ShotgunShellsBox");
         weaponsList.put("Base.Pistol", "Base.Bullets9mmBox");
         weaponsList.put("Base.Pistol2", "Base.Bullets45Box");
         weaponsList.put("Base.Pistol3", "Base.Bullets44Box");
         weaponsList.put("Base.VarmintRifle", "Base.223Box");
         weaponsList.put("Base.HuntingRifle", "Base.308Box");
      }
   }

    static void initAllRBMapChance() {
      for (int var0 = 0; var0 < IsoWorld.instance.getRandomizedBuildingList().size(); var0++) {
         totalChance = totalChance + ((RandomizedBuildingBase)IsoWorld.instance.getRandomizedBuildingList().get(var0)).getChance();
         rbMap.put(
            (RandomizedBuildingBase)IsoWorld.instance.getRandomizedBuildingList().get(var0),
            ((RandomizedBuildingBase)IsoWorld.instance.getRandomizedBuildingList().get(var0)).getChance()
         );
      }
   }

    bool isValid(BuildingDef var1, bool var2) {
      this.debugLine = "";
      if (GameClient.bClient) {
    return false;
      } else if (var1.isAllExplored() && !var2) {
    return false;
      } else {
         if (!GameServer.bServer) {
            if (!var2
               && IsoPlayer.getInstance().getSquare() != nullptr
               && IsoPlayer.getInstance().getSquare().getBuilding() != nullptr
               && IsoPlayer.getInstance().getSquare().getBuilding().def == var1) {
               this.customizeStartingHouse(IsoPlayer.getInstance().getSquare().getBuilding().def);
    return false;
            }
         } else if (!var2) {
            for (int var3 = 0; var3 < GameServer.Players.size(); var3++) {
    IsoPlayer var4 = (IsoPlayer)GameServer.Players.get(var3);
               if (var4.getSquare() != nullptr && var4.getSquare().getBuilding() != nullptr && var4.getSquare().getBuilding().def == var1) {
    return false;
               }
            }
         }

    bool var8 = false;
    bool var9 = false;
    bool var5 = false;

         for (int var6 = 0; var6 < var1.rooms.size(); var6++) {
    RoomDef var7 = (RoomDef)var1.rooms.get(var6);
            if ("bedroom" == var7.name)) {
               var8 = true;
            }

            if ("kitchen" == var7.name) || "livingroom" == var7.name)) {
               var9 = true;
            }

            if ("bathroom" == var7.name)) {
               var5 = true;
            }
         }

         if (!var8) {
            this.debugLine = this.debugLine + "no bedroom ";
         }

         if (!var5) {
            this.debugLine = this.debugLine + "no bathroom ";
         }

         if (!var9) {
            this.debugLine = this.debugLine + "no living room or kitchen ";
         }

         return var8 && var5 && var9;
      }
   }

    void customizeStartingHouse(BuildingDef var1) {
   }

    int getMinimumDays() {
      return this.minimumDays;
   }

    void setMinimumDays(int var1) {
      this.minimumDays = var1;
   }

    int getMinimumRooms() {
      return this.minimumRooms;
   }

    void setMinimumRooms(int var1) {
      this.minimumRooms = var1;
   }

    static void ChunkLoaded(IsoBuilding var0) {
      if (!GameClient.bClient && var0.def != nullptr && !var0.def.seen && var0.def.isFullyStreamedIn()) {
         if (GameServer.bServer && GameServer.Players.empty()) {
            return;
         }

         for (int var1 = 0; var1 < var0.Rooms.size(); var1++) {
            if (((IsoRoom)var0.Rooms.get(var1)).def.bExplored) {
               return;
            }
         }

         if (!var0.def.isAnyChunkNewlyLoaded()) {
            var0.def.seen = true;
            return;
         }

    std::vector var5 = new std::vector();

         for (int var2 = 0; var2 < IsoWorld.instance.getRandomizedBuildingList().size(); var2++) {
    RandomizedBuildingBase var3 = (RandomizedBuildingBase)IsoWorld.instance.getRandomizedBuildingList().get(var2);
            if (var3.isAlwaysDo() && var3.isValid(var0.def, false)) {
               var5.push_back(var3);
            }
         }

         var0.def.seen = true;
         if (var0.def.x == 10744 && var0.def.y == 9409 && Rand.Next(100) < 31) {
    RBKateAndBaldspot var8 = std::make_shared<RBKateAndBaldspot>();
            var8.randomizeBuilding(var0.def);
            return;
         }

         if (!var5.empty()) {
    RandomizedBuildingBase var6 = (RandomizedBuildingBase)var5.get(Rand.Next(0, var5.size()));
            if (var6 != nullptr) {
               var6.randomizeBuilding(var0.def);
               return;
            }
         }

         if (GameServer.bServer && SpawnPoints.instance.isSpawnBuilding(var0.getDef())) {
            return;
         }

    RandomizedBuildingBase var7 = IsoWorld.instance.getRBBasic();
         if ("Tutorial" == Core.GameMode)) {
            return;
         }

         try {
    uint8_t var9 = 10;
            switch (SandboxOptions.instance.SurvivorHouseChance.getValue()) {
               case 1:
                  return;
               case 2:
                  var9 -= 5;
               case 3:
               default:
                  break;
               case 4:
                  var9 += 5;
                  break;
               case 5:
                  var9 += 10;
                  break;
               case 6:
                  var9 += 20;
            }

            if (Rand.Next(100) <= var9) {
               if (totalChance == 0) {
                  initAllRBMapChance();
               }

               var7 = getRandomStory();
               if (var7 == nullptr) {
                  return;
               }
            }

            if (var7.isValid(var0.def, false) && var7.isTimeValid(false)) {
               var7.randomizeBuilding(var0.def);
            }
         } catch (Exception var4) {
            var4.printStackTrace();
         }
      }
   }

    int getChance() {
      return this.chance;
   }

    void setChance(int var1) {
      this.chance = var1;
   }

    bool isAlwaysDo() {
      return this.alwaysDo;
   }

    void setAlwaysDo(bool var1) {
      this.alwaysDo = var1;
   }

    static RandomizedBuildingBase getRandomStory() {
    int var0 = Rand.Next(totalChance);
    Iterator var1 = rbMap.keySet().iterator();
    int var2 = 0;

      while (var1.hasNext()) {
    RandomizedBuildingBase var3 = (RandomizedBuildingBase)var1.next();
         var2 += rbMap.get(var3);
         if (var0 < var2) {
    return var3;
         }
      }

    return nullptr;
   }

   public std::vector<IsoZombie> addZombiesOnSquare(int var1, std::string var2, int var3, IsoGridSquare var4) {
      if (!IsoWorld.getZombiesDisabled() && !"Tutorial" == Core.GameMode)) {
    std::vector var5 = new std::vector();

         for (int var6 = 0; var6 < var1; var6++) {
            VirtualZombieManager.instance.choices.clear();
            VirtualZombieManager.instance.choices.push_back(var4);
    IsoZombie var7 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.getRandom().index(), false);
            if (var7 != nullptr) {
               if ("Kate" == var2) || "Bob" == var2) || "Raider" == var2)) {
                  var7.doDirtBloodEtc = false;
               }

               if (var3 != nullptr) {
                  var7.setFemaleEtc(Rand.Next(100) < var3);
               }

               if (var2 != nullptr) {
                  var7.dressInPersistentOutfit(var2);
                  var7.bDressInRandomOutfit = false;
               } else {
                  var7.bDressInRandomOutfit = true;
               }

               var5.push_back(var7);
            }
         }

         ZombieSpawnRecorder.instance.record(var5, this.getClass().getSimpleName());
    return var5;
      } else {
    return nullptr;
      }
   }

   public std::vector<IsoZombie> addZombies(BuildingDef var1, int var2, std::string var3, int var4, RoomDef var5) {
    bool var6 = var5 == nullptr;
    std::vector var7 = new std::vector();
      if (!IsoWorld.getZombiesDisabled() && !"Tutorial" == Core.GameMode)) {
         if (var5 == nullptr) {
            var5 = this.getRandomRoom(var1, 6);
         }

    int var8 = 2;
    int var9 = var5.area / 2;
         if (var2 == 0) {
            if (SandboxOptions.instance.Zombies.getValue() == 1) {
               var9 += 4;
            } else if (SandboxOptions.instance.Zombies.getValue() == 2) {
               var9 += 3;
            } else if (SandboxOptions.instance.Zombies.getValue() == 3) {
               var9 += 2;
            } else if (SandboxOptions.instance.Zombies.getValue() == 5) {
               var9 -= 4;
            }

            if (var9 > 8) {
               var9 = 8;
            }

            if (var9 < var8) {
               var9 = var8 + 1;
            }
         } else {
            var8 = var2;
            var9 = var2;
         }

    int var10 = Rand.Next(var8, var9);

         for (int var11 = 0; var11 < var10; var11++) {
    IsoGridSquare var12 = getRandomSpawnSquare(var5);
            if (var12 == nullptr) {
               break;
            }

            VirtualZombieManager.instance.choices.clear();
            VirtualZombieManager.instance.choices.push_back(var12);
    IsoZombie var13 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.getRandom().index(), false);
            if (var13 != nullptr) {
               if (var4 != nullptr) {
                  var13.setFemaleEtc(Rand.Next(100) < var4);
               }

               if (var3 != nullptr) {
                  var13.dressInPersistentOutfit(var3);
                  var13.bDressInRandomOutfit = false;
               } else {
                  var13.bDressInRandomOutfit = true;
               }

               var7.push_back(var13);
               if (var6) {
                  var5 = this.getRandomRoom(var1, 6);
               }
            }
         }

         ZombieSpawnRecorder.instance.record(var7, this.getClass().getSimpleName());
    return var7;
      } else {
    return var7;
      }
   }

    HandWeapon addRandomRangedWeapon(ItemContainer var1, bool var2, bool var3, bool var4) {
      if (weaponsList == nullptr || weaponsList.empty()) {
         this.init();
      }

    std::vector var5 = new std::vector<>(weaponsList.keySet());
    std::string var6 = (std::string)var5.get(Rand.Next(0, var5.size()));
    HandWeapon var7 = this.addWeapon(var6, var2);
      if (var7 == nullptr) {
    return nullptr;
      } else {
         if (var3) {
            var1.addItem(InventoryItemFactory.CreateItem(weaponsList.get(var6)));
         }

         if (var4) {
    KahluaTable var8 = (KahluaTable)LuaManager.env.rawget("WeaponUpgrades");
            if (var8 == nullptr) {
    return nullptr;
            }

    KahluaTable var9 = (KahluaTable)var8.rawget(var7.getType());
            if (var9 == nullptr) {
    return nullptr;
            }

    int var10 = Rand.Next(1, var9.len() + 1);

            for (int var11 = 1; var11 <= var10; var11++) {
    int var12 = Rand.Next(var9.len()) + 1;
    WeaponPart var13 = (WeaponPart)InventoryItemFactory.CreateItem((std::string)var9.rawget(var12));
               var7.attachWeaponPart(var13);
            }
         }

    return var7;
      }
   }

    void spawnItemsInContainers(BuildingDef var1, const std::string& var2, int var3) {
    std::vector var4 = new std::vector();
    ItemPickerRoom var5 = (ItemPickerRoom)ItemPickerJava.rooms.get(var2);
    IsoCell var6 = IsoWorld.instance.CurrentCell;

      for (int var7 = var1.x - 1; var7 < var1.x2 + 1; var7++) {
         for (int var8 = var1.y - 1; var8 < var1.y2 + 1; var8++) {
            for (int var9 = 0; var9 < 8; var9++) {
    IsoGridSquare var10 = var6.getGridSquare(var7, var8, var9);
               if (var10 != nullptr) {
                  for (int var11 = 0; var11 < var10.getObjects().size(); var11++) {
    IsoObject var12 = (IsoObject)var10.getObjects().get(var11);
                     if (Rand.Next(100) <= var3
                        && var12.getContainer() != nullptr
                        && var10.getRoom() != nullptr
                        && var10.getRoom().getName() != nullptr
                        && var5.Containers.containsKey(var12.getContainer().getType())) {
                        var12.getContainer().clear();
                        var4.push_back(var12.getContainer());
                        var12.getContainer().setExplored(true);
                     }
                  }
               }
            }
         }
      }

      for (int var13 = 0; var13 < var4.size(); var13++) {
    ItemContainer var14 = (ItemContainer)var4.get(var13);
         ItemPickerJava.fillContainerType(var5, var14, "", nullptr);
         ItemPickerJava.updateOverlaySprite(var14.getParent());
         if (GameServer.bServer) {
            GameServer.sendItemsInContainer(var14.getParent(), var14);
         }
      }
   }

    void removeAllZombies(BuildingDef var1) {
      for (int var2 = var1.x - 1; var2 < var1.x + var1.x2 + 1; var2++) {
         for (int var3 = var1.y - 1; var3 < var1.y + var1.y2 + 1; var3++) {
            for (int var4 = 0; var4 < 8; var4++) {
    IsoGridSquare var5 = this.getSq(var2, var3, var4);
               if (var5 != nullptr) {
                  for (int var6 = 0; var6 < var5.getMovingObjects().size(); var6++) {
                     var5.getMovingObjects().remove(var6);
                     var6--;
                  }
               }
            }
         }
      }
   }

    IsoWindow getWindow(IsoGridSquare var1) {
      for (int var2 = 0; var2 < var1.getObjects().size(); var2++) {
    IsoObject var3 = (IsoObject)var1.getObjects().get(var2);
         if (dynamic_cast<IsoWindow*>(var3) != nullptr) {
            return (IsoWindow)var3;
         }
      }

    return nullptr;
   }

    IsoDoor getDoor(IsoGridSquare var1) {
      for (int var2 = 0; var2 < var1.getObjects().size(); var2++) {
    IsoObject var3 = (IsoObject)var1.getObjects().get(var2);
         if (dynamic_cast<IsoDoor*>(var3) != nullptr) {
            return (IsoDoor)var3;
         }
      }

    return nullptr;
   }

    void addBarricade(IsoGridSquare var1, int var2) {
      for (int var3 = 0; var3 < var1.getObjects().size(); var3++) {
    IsoObject var4 = (IsoObject)var1.getObjects().get(var3);
         if (dynamic_cast<IsoDoor*>(var4) != nullptr) {
            if (!((IsoDoor)var4).isBarricadeAllowed()) {
               continue;
            }

    IsoGridSquare var5 = var1.getRoom() == nullptr ? var1 : ((IsoDoor)var4).getOppositeSquare();
            if (var5 != nullptr && var5.getRoom() == nullptr) {
    bool var6 = var5 != var1;
    IsoBarricade var7 = IsoBarricade.AddBarricadeToObject((IsoDoor)var4, var6);
               if (var7 != nullptr) {
                  for (int var8 = 0; var8 < var2; var8++) {
                     var7.addPlank(nullptr, nullptr);
                  }

                  if (GameServer.bServer) {
                     var7.transmitCompleteItemToClients();
                  }
               }
            }
         }

         if (dynamic_cast<IsoWindow*>(var4) != nullptr && ((IsoWindow)var4).isBarricadeAllowed()) {
    IsoGridSquare var9 = var1.getRoom() == nullptr ? var1 : ((IsoWindow)var4).getOppositeSquare();
    bool var10 = var9 != var1;
    IsoBarricade var11 = IsoBarricade.AddBarricadeToObject((IsoWindow)var4, var10);
            if (var11 != nullptr) {
               for (int var12 = 0; var12 < var2; var12++) {
                  var11.addPlank(nullptr, nullptr);
               }

               if (GameServer.bServer) {
                  var11.transmitCompleteItemToClients();
               }
            }
         }
      }
   }

    InventoryItem addWorldItem(const std::string& var1, IsoGridSquare var2, float var3, float var4, float var5) {
      return this.addWorldItem(var1, var2, var3, var4, var5, 0);
   }

    InventoryItem addWorldItem(const std::string& var1, IsoGridSquare var2, float var3, float var4, float var5, int var6) {
      if (var1 != nullptr && var2 != nullptr) {
    InventoryItem var7 = InventoryItemFactory.CreateItem(var1);
         if (var7 != nullptr) {
            var7.setAutoAge();
            var7.setWorldZRotation(var6);
            if (dynamic_cast<HandWeapon*>(var7) != nullptr) {
               var7.setCondition(Rand.Next(2, var7.getConditionMax()));
            }

            return var2.AddWorldInventoryItem(var7, var3, var4, var5);
         } else {
    return nullptr;
         }
      } else {
    return nullptr;
      }
   }

    InventoryItem addWorldItem(const std::string& var1, IsoGridSquare var2, IsoObject var3) {
      if (var1 != nullptr && var2 != nullptr) {
    float var4 = 0.0F;
         if (var3 != nullptr) {
            var4 = var3.getSurfaceOffsetNoTable() / 96.0F;
         }

    InventoryItem var5 = InventoryItemFactory.CreateItem(var1);
         if (var5 != nullptr) {
            var5.setAutoAge();
            return var2.AddWorldInventoryItem(var5, Rand.Next(0.3F, 0.9F), Rand.Next(0.3F, 0.9F), var4);
         } else {
    return nullptr;
         }
      } else {
    return nullptr;
      }
   }

    bool isTableFor3DItems(IsoObject var1, IsoGridSquare var2) {
      return var1.getSurfaceOffsetNoTable() > 0.0F
         && var1.getContainer() == nullptr
         && var2.getProperties().Val("waterAmount") == nullptr
         && !var1.hasWater()
         && var1.getProperties().Val("BedType") == nullptr;
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
