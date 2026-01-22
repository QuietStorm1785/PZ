#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerRoom.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoCurtain.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoRadio.h"
#include "zombie/iso/objects/IsoStove.h"
#include "zombie/iso/objects/IsoTelevision.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/network/GameServer.h"
#include "zombie/randomizedWorld/randomizedBuilding/TableStories/RBTableStoryBase.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSBandPractice.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSBathroomZed.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSBedroomZed.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSBleach.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSCorpsePsycho.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSDeadDrunk.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSFootballNight.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSGunmanInBathroom.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSGunslinger.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSHenDo.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSHockeyPsycho.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSHouseParty.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSPokerNight.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSPoliceAtHouse.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSPrisonEscape.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSPrisonEscapeWithPolice.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSSkeletonPsycho.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSSpecificProfession.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSStagDo.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSStudentNight.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSSuicidePact.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSTinFoilHat.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSZombieLockedBathroom.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RDSZombiesEating.h"
#include "zombie/randomizedWorld/randomizedDeadSurvivor/RandomizedDeadSurvivorBase.h"
#include <iterator>

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBBasic : public RandomizedBuildingBase {
public:
   private const std::vector<std::string> specificProfessionDistribution = std::make_unique<std::vector<>>();
   private const Map<std::string, std::string> specificProfessionRoomDistribution = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<int, std::string> kitchenSinkItems = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<int, std::string> kitchenCounterItems = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<int, std::string> kitchenStoveItems = std::make_unique<std::unordered_map<>>();
   private static const std::unordered_map<int, std::string> bathroomSinkItems = std::make_unique<std::unordered_map<>>();
   private const std::vector<std::string> coldFood = std::make_unique<std::vector<>>();
   private const Map<std::string, std::string> plankStash = std::make_unique<std::unordered_map<>>();
   private const std::vector<RandomizedDeadSurvivorBase> deadSurvivorsStory = std::make_unique<std::vector<>>();
    int totalChanceRDS = 0;
   private static const std::unordered_map<RandomizedDeadSurvivorBase, int> rdsMap = std::make_unique<std::unordered_map<>>();
   private static const std::vector<std::string> uniqueRDSSpawned = std::make_unique<std::vector<>>();
   private std::vector<IsoObject> tablesDone = std::make_unique<std::vector<>>();
    bool doneTable = false;

    void randomizeBuilding(BuildingDef var1) {
      this.tablesDone = std::make_unique<std::vector<>>();
    bool var2 = Rand.Next(100) <= 20;
    std::vector var3 = new std::vector();
    std::string var4 = this.specificProfessionDistribution.get(Rand.Next(0, this.specificProfessionDistribution.size()));
    ItemPickerRoom var5 = (ItemPickerRoom)ItemPickerJava.rooms.get(var4);
    IsoCell var6 = IsoWorld.instance.CurrentCell;
    bool var7 = Rand.NextBool(9);

      for (int var8 = var1.x - 1; var8 < var1.x2 + 1; var8++) {
         for (int var9 = var1.y - 1; var9 < var1.y2 + 1; var9++) {
            for (int var10 = 0; var10 < 8; var10++) {
    IsoGridSquare var11 = var6.getGridSquare(var8, var9, var10);
               if (var11 != nullptr) {
                  if (var7 && var11.getFloor() != nullptr && this.plankStash.containsKey(var11.getFloor().getSprite().getName())) {
    IsoThumpable var12 = std::make_shared<IsoThumpable>(var11.getCell(), var11, this.plankStash.get(var11.getFloor().getSprite().getName()), false, nullptr);
                     var12.setIsThumpable(false);
                     var12.container = std::make_shared<ItemContainer>("plankstash", var11, var12);
                     var11.AddSpecialObject(var12);
                     var11.RecalcAllWithNeighbours(true);
                     var7 = false;
                  }

                  for (int var18 = 0; var18 < var11.getObjects().size(); var18++) {
    IsoObject var13 = (IsoObject)var11.getObjects().get(var18);
                     if (Rand.Next(100) <= 65 && dynamic_cast<IsoDoor*>(var13) != nullptr && !((IsoDoor)var13).isExteriorDoor(nullptr)) {
                        ((IsoDoor)var13).ToggleDoorSilent();
                        ((IsoDoor)var13).syncIsoObject(true, (byte)1, nullptr, nullptr);
                     }

                     if (dynamic_cast<IsoWindow*>(var13) != nullptr var14) {
                        if (Rand.NextBool(80)) {
                           var1.bAlarmed = false;
                           var14.ToggleWindow(nullptr);
                        }

    IsoCurtain var15 = var14.HasCurtains();
                        if (var15 != nullptr && Rand.NextBool(15)) {
                           var15.ToggleDoorSilent();
                        }
                     }

                     if (var2
                        && Rand.Next(100) <= 70
                        && var13.getContainer() != nullptr
                        && var11.getRoom() != nullptr
                        && var11.getRoom().getName() != nullptr
                        && this.specificProfessionRoomDistribution.get(var4).contains(var11.getRoom().getName())
                        && var5.Containers.containsKey(var13.getContainer().getType())) {
                        var13.getContainer().clear();
                        var3.push_back(var13.getContainer());
                        var13.getContainer().setExplored(true);
                     }

                     if (Rand.Next(100) < 15 && var13.getContainer() != nullptr && var13.getContainer().getType() == "stove")) {
    InventoryItem var19 = var13.getContainer().AddItem(this.coldFood.get(Rand.Next(0, this.coldFood.size())));
                        var19.setCooked(true);
                        var19.setAutoAge();
                     }

                     if (!this.tablesDone.contains(var13) && var13.getProperties().isTable() && var13.getContainer() == nullptr && !this.doneTable) {
                        this.checkForTableSpawn(var1, var13);
                     }
                  }

                  if (var11.getRoom() != nullptr && "kitchen" == var11.getRoom().getName())) {
                     this.doKitchenStuff(var11);
                  }

                  if (var11.getRoom() != nullptr && "bathroom" == var11.getRoom().getName())) {
                     this.doBathroomStuff(var11);
                  }

                  if (var11.getRoom() != nullptr && "bedroom" == var11.getRoom().getName())) {
                     this.doBedroomStuff(var11);
                  }

                  if (var11.getRoom() != nullptr && "livingroom" == var11.getRoom().getName())) {
                     this.doLivingRoomStuff(var11);
                  }
               }
            }
         }
      }

      for (int var16 = 0; var16 < var3.size(); var16++) {
    ItemContainer var17 = (ItemContainer)var3.get(var16);
         ItemPickerJava.fillContainerType(var5, var17, "", nullptr);
         ItemPickerJava.updateOverlaySprite(var17.getParent());
         if (GameServer.bServer) {
            GameServer.sendItemsInContainer(var17.getParent(), var17);
         }
      }

      if (!var2 && Rand.Next(100) < 25) {
         this.addRandomDeadSurvivorStory(var1);
         var1.setAllExplored(true);
         var1.bAlarmed = false;
      }

      this.doneTable = false;
   }

    void doLivingRoomStuff(IsoGridSquare var1) {
    IsoObject var2 = nullptr;
    bool var3 = false;

      for (int var4 = 0; var4 < var1.getObjects().size(); var4++) {
    IsoObject var5 = (IsoObject)var1.getObjects().get(var4);
         if (Rand.NextBool(5)
            && var5.getProperties().Val("BedType") == nullptr
            && var5.getSurfaceOffsetNoTable() > 0.0F
            && var5.getSurfaceOffsetNoTable() < 30.0F
            && !(dynamic_cast<IsoRadio*>(var5) != nullptr)) {
            var2 = var5;
         }

         if (dynamic_cast<IsoRadio*>(var5) != nullptr || dynamic_cast<IsoTelevision*>(var5) != nullptr) {
            var3 = true;
            break;
         }
      }

      if (!var3 && var2 != nullptr) {
    int var7 = Rand.Next(0, 6);
    std::string var8 = "Base.TVRemote";
         switch (var7) {
            case 0:
               var8 = "Base.TVRemote";
               break;
            case 1:
               var8 = "Base.TVMagazine";
               break;
            case 2:
               var8 = "Base.Newspaper";
               break;
            case 3:
               var8 = "Base.VideoGame";
               break;
            case 4:
               var8 = "Base.Mugl";
               break;
            case 5:
               var8 = "Base.Headphones";
         }

    IsoDirections var6 = this.getFacing(var2.getSprite());
         if (var6 != nullptr) {
            if (var6 == IsoDirections.E) {
               this.addWorldItem(var8, var1, 0.4F, Rand.Next(0.34F, 0.74F), var2.getSurfaceOffsetNoTable() / 96.0F);
            }

            if (var6 == IsoDirections.W) {
               this.addWorldItem(var8, var1, 0.64F, Rand.Next(0.34F, 0.74F), var2.getSurfaceOffsetNoTable() / 96.0F);
            }

            if (var6 == IsoDirections.N) {
               this.addWorldItem(var8, var1, Rand.Next(0.44F, 0.64F), 0.67F, var2.getSurfaceOffsetNoTable() / 96.0F);
            }

            if (var6 == IsoDirections.S) {
               this.addWorldItem(var8, var1, Rand.Next(0.44F, 0.64F), 0.42F, var2.getSurfaceOffsetNoTable() / 96.0F);
            }
         }
      }
   }

    void doBedroomStuff(IsoGridSquare var1) {
      for (int var2 = 0; var2 < var1.getObjects().size(); var2++) {
    IsoObject var3 = (IsoObject)var1.getObjects().get(var2);
         if (var3.getSprite() == nullptr || var3.getSprite().getName() == nullptr) {
            return;
         }

         if (Rand.NextBool(7) && var3.getSprite().getName().contains("bedding") && var3.getProperties().Val("BedType") != nullptr) {
    int var4 = Rand.Next(0, 14);
            switch (var4) {
               case 0:
                  this.addWorldItem("Shirt_FormalTINT", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 1:
                  this.addWorldItem("Shirt_FormalWhite_ShortSleeveTINT", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 2:
                  this.addWorldItem("Tshirt_DefaultDECAL_TINT", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 3:
                  this.addWorldItem("Tshirt_PoloStripedTINT", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 4:
                  this.addWorldItem("Tshirt_PoloTINT", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 5:
                  this.addWorldItem("Jacket_WhiteTINT", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 6:
                  this.addWorldItem("Jumper_DiamondPatternTINT", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 7:
                  this.addWorldItem("Jumper_TankTopDiamondTINT", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 8:
                  this.addWorldItem("HoodieDOWN_WhiteTINT", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 9:
                  this.addWorldItem("Trousers_DefaultTEXTURE_TINT", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 10:
                  this.addWorldItem("Trousers_WhiteTINT", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 11:
                  this.addWorldItem("Trousers_Denim", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 12:
                  this.addWorldItem("Trousers_Padded", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 13:
                  this.addWorldItem("TrousersMesh_DenimLight", var1, 0.6F, 0.6F, var3.getSurfaceOffsetNoTable() / 96.0F);
            }
         }

         if (Rand.NextBool(7) && var3.getContainer() != nullptr && "sidetable" == var3.getContainer().getType())) {
    int var7 = Rand.Next(0, 4);
    std::string var5 = "Base.Book";
            switch (var7) {
               case 0:
                  var5 = "Base.Book";
                  break;
               case 1:
                  var5 = "Base.Notebook";
                  break;
               case 2:
                  var5 = "Base.VideoGame";
                  break;
               case 3:
                  var5 = "Base.CDPlayer";
            }

    IsoDirections var6 = this.getFacing(var3.getSprite());
            if (var6 != nullptr) {
               if (var6 == IsoDirections.E) {
                  this.addWorldItem(var5, var1, 0.42F, Rand.Next(0.34F, 0.74F), var3.getSurfaceOffsetNoTable() / 96.0F);
               }

               if (var6 == IsoDirections.W) {
                  this.addWorldItem(var5, var1, 0.64F, Rand.Next(0.34F, 0.74F), var3.getSurfaceOffsetNoTable() / 96.0F);
               }

               if (var6 == IsoDirections.N) {
                  this.addWorldItem(var5, var1, Rand.Next(0.44F, 0.64F), 0.67F, var3.getSurfaceOffsetNoTable() / 96.0F);
               }

               if (var6 == IsoDirections.S) {
                  this.addWorldItem(var5, var1, Rand.Next(0.44F, 0.64F), 0.42F, var3.getSurfaceOffsetNoTable() / 96.0F);
               }
            }

            return;
         }
      }
   }

    void doKitchenStuff(IsoGridSquare var1) {
    bool var2 = false;
    bool var3 = false;

      for (int var4 = 0; var4 < var1.getObjects().size(); var4++) {
    IsoObject var5 = (IsoObject)var1.getObjects().get(var4);
         if (var5.getSprite() == nullptr || var5.getSprite().getName() == nullptr) {
            return;
         }

         if (!var2 && var5.getSprite().getName().contains("sink") && Rand.NextBool(4)) {
    IsoDirections var10 = this.getFacing(var5.getSprite());
            if (var10 != nullptr) {
               this.generateSinkClutter(var10, var5, var1, kitchenSinkItems);
               var2 = true;
            }
         } else if (!var3 && var5.getContainer() != nullptr && "counter" == var5.getContainer().getType()) && Rand.NextBool(6)) {
    bool var9 = true;

            for (int var7 = 0; var7 < var1.getObjects().size(); var7++) {
    IsoObject var8 = (IsoObject)var1.getObjects().get(var7);
               if (var8.getSprite() != nullptr && var8.getSprite().getName() != nullptr && var8.getSprite().getName().contains("sink")
                  || dynamic_cast<IsoStove*>(var8) != nullptr
                  || dynamic_cast<IsoRadio*>(var8) != nullptr) {
                  var9 = false;
                  break;
               }
            }

            if (var9) {
    IsoDirections var11 = this.getFacing(var5.getSprite());
               if (var11 != nullptr) {
                  this.generateCounterClutter(var11, var5, var1, kitchenCounterItems);
                  var3 = true;
               }
            }
         } else if (dynamic_cast<IsoStove*>(var5) != nullptr && var5.getContainer() != nullptr && "stove" == var5.getContainer().getType()) && Rand.NextBool(4)) {
    IsoDirections var6 = this.getFacing(var5.getSprite());
            if (var6 != nullptr) {
               this.generateKitchenStoveClutter(var6, var5, var1);
            }
         }
      }
   }

    void doBathroomStuff(IsoGridSquare var1) {
    bool var2 = false;
    bool var3 = false;

      for (int var4 = 0; var4 < var1.getObjects().size(); var4++) {
    IsoObject var5 = (IsoObject)var1.getObjects().get(var4);
         if (var5.getSprite() == nullptr || var5.getSprite().getName() == nullptr) {
            return;
         }

         if (!var2 && !var3 && var5.getSprite().getName().contains("sink") && Rand.NextBool(5) && var5.getSurfaceOffsetNoTable() > 0.0F) {
    IsoDirections var9 = this.getFacing(var5.getSprite());
            if (var9 != nullptr) {
               this.generateSinkClutter(var9, var5, var1, bathroomSinkItems);
               var2 = true;
            }
         } else if (!var2 && !var3 && var5.getContainer() != nullptr && "counter" == var5.getContainer().getType()) && Rand.NextBool(5)) {
    bool var6 = true;

            for (int var7 = 0; var7 < var1.getObjects().size(); var7++) {
    IsoObject var8 = (IsoObject)var1.getObjects().get(var7);
               if (var8.getSprite() != nullptr && var8.getSprite().getName() != nullptr && var8.getSprite().getName().contains("sink")
                  || dynamic_cast<IsoStove*>(var8) != nullptr
                  || dynamic_cast<IsoRadio*>(var8) != nullptr) {
                  var6 = false;
                  break;
               }
            }

            if (var6) {
    IsoDirections var10 = this.getFacing(var5.getSprite());
               if (var10 != nullptr) {
                  this.generateCounterClutter(var10, var5, var1, bathroomSinkItems);
                  var3 = true;
               }
            }
         }
      }
   }

    void generateKitchenStoveClutter(IsoDirections var1, IsoObject var2, IsoGridSquare var3) {
    int var4 = Rand.Next(1, 3);
    std::string var5 = kitchenStoveItems.get(Rand.Next(1, kitchenStoveItems.size()));
      if (var1 == IsoDirections.W) {
         switch (var4) {
            case 1:
               this.addWorldItem(var5, var3, 0.5703125F, 0.8046875F, var2.getSurfaceOffsetNoTable() / 96.0F);
               break;
            case 2:
               this.addWorldItem(var5, var3, 0.5703125F, 0.2578125F, var2.getSurfaceOffsetNoTable() / 96.0F);
         }
      }

      if (var1 == IsoDirections.E) {
         switch (var4) {
            case 1:
               this.addWorldItem(var5, var3, 0.5F, 0.7890625F, var2.getSurfaceOffsetNoTable() / 96.0F);
               break;
            case 2:
               this.addWorldItem(var5, var3, 0.5F, 0.1875F, var2.getSurfaceOffsetNoTable() / 96.0F);
         }
      }

      if (var1 == IsoDirections.S) {
         switch (var4) {
            case 1:
               this.addWorldItem(var5, var3, 0.3125F, 0.53125F, var2.getSurfaceOffsetNoTable() / 96.0F);
               break;
            case 2:
               this.addWorldItem(var5, var3, 0.875F, 0.53125F, var2.getSurfaceOffsetNoTable() / 96.0F);
         }
      }

      if (var1 == IsoDirections.N) {
         switch (var4) {
            case 1:
               this.addWorldItem(var5, var3, 0.3203F, 0.523475F, var2.getSurfaceOffsetNoTable() / 96.0F);
               break;
            case 2:
               this.addWorldItem(var5, var3, 0.8907F, 0.523475F, var2.getSurfaceOffsetNoTable() / 96.0F);
         }
      }
   }

    void generateCounterClutter(IsoDirections var1, IsoObject var2, IsoGridSquare var3, std::string> var4) {
    int var5 = Math.min(5, var4.size() + 1);
    int var6 = Rand.Next(1, var5);
    std::vector var7 = new std::vector();

      for (int var8 = 0; var8 < var6; var8++) {
    int var9 = Rand.Next(1, 5);
    bool var10 = false;

         while (!var10) {
            if (!var7.contains(var9)) {
               var7.push_back(var9);
               var10 = true;
            } else {
               var9 = Rand.Next(1, 5);
            }
         }

         if (var7.size() == 4) {
         }
      }

    std::vector var13 = new std::vector();

      for (int var14 = 0; var14 < var7.size(); var14++) {
    int var15 = (int)var7.get(var14);
    int var11 = Rand.Next(1, var4.size() + 1);
    std::string var12 = nullptr;

         while (var12 == nullptr) {
            var12 = (std::string)var4.get(var11);
            if (var13.contains(var12)) {
               var12 = nullptr;
               var11 = Rand.Next(1, var4.size() + 1);
            }
         }

         var13.push_back(var12);
         if (var1 == IsoDirections.S) {
            switch (var15) {
               case 1:
                  this.addWorldItem(var12, var3, 0.138F, Rand.Next(0.2F, 0.523F), var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 2:
                  this.addWorldItem(var12, var3, 0.383F, Rand.Next(0.2F, 0.523F), var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 3:
                  this.addWorldItem(var12, var3, 0.633F, Rand.Next(0.2F, 0.523F), var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 4:
                  this.addWorldItem(var12, var3, 0.78F, Rand.Next(0.2F, 0.523F), var2.getSurfaceOffsetNoTable() / 96.0F);
            }
         }

         if (var1 == IsoDirections.N) {
            switch (var15) {
               case 1:
                  var3.AddWorldInventoryItem(var12, 0.133F, Rand.Next(0.53125F, 0.9375F), var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 2:
                  var3.AddWorldInventoryItem(var12, 0.38F, Rand.Next(0.53125F, 0.9375F), var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 3:
                  var3.AddWorldInventoryItem(var12, 0.625F, Rand.Next(0.53125F, 0.9375F), var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 4:
                  var3.AddWorldInventoryItem(var12, 0.92F, Rand.Next(0.53125F, 0.9375F), var2.getSurfaceOffsetNoTable() / 96.0F);
            }
         }

         if (var1 == IsoDirections.E) {
            switch (var15) {
               case 1:
                  var3.AddWorldInventoryItem(var12, Rand.Next(0.226F, 0.593F), 0.14F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 2:
                  var3.AddWorldInventoryItem(var12, Rand.Next(0.226F, 0.593F), 0.33F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 3:
                  var3.AddWorldInventoryItem(var12, Rand.Next(0.226F, 0.593F), 0.64F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 4:
                  var3.AddWorldInventoryItem(var12, Rand.Next(0.226F, 0.593F), 0.92F, var2.getSurfaceOffsetNoTable() / 96.0F);
            }
         }

         if (var1 == IsoDirections.W) {
            switch (var15) {
               case 1:
                  var3.AddWorldInventoryItem(var12, Rand.Next(0.5859375F, 0.9F), 0.21875F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 2:
                  var3.AddWorldInventoryItem(var12, Rand.Next(0.5859375F, 0.9F), 0.421875F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 3:
                  var3.AddWorldInventoryItem(var12, Rand.Next(0.5859375F, 0.9F), 0.71F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 4:
                  var3.AddWorldInventoryItem(var12, Rand.Next(0.5859375F, 0.9F), 0.9175F, var2.getSurfaceOffsetNoTable() / 96.0F);
            }
         }
      }
   }

    void generateSinkClutter(IsoDirections var1, IsoObject var2, IsoGridSquare var3, std::string> var4) {
    int var5 = Math.min(5, var4.size() + 1);
    int var6 = Rand.Next(1, var5);
    std::vector var7 = new std::vector();

      for (int var8 = 0; var8 < var6; var8++) {
    int var9 = Rand.Next(1, 5);
    bool var10 = false;

         while (!var10) {
            if (!var7.contains(var9)) {
               var7.push_back(var9);
               var10 = true;
            } else {
               var9 = Rand.Next(1, 5);
            }
         }

         if (var7.size() == 4) {
         }
      }

    std::vector var13 = new std::vector();

      for (int var14 = 0; var14 < var7.size(); var14++) {
    int var15 = (int)var7.get(var14);
    int var11 = Rand.Next(1, var4.size() + 1);
    std::string var12 = nullptr;

         while (var12 == nullptr) {
            var12 = (std::string)var4.get(var11);
            if (var13.contains(var12)) {
               var12 = nullptr;
               var11 = Rand.Next(1, var4.size() + 1);
            }
         }

         var13.push_back(var12);
         if (var1 == IsoDirections.S) {
            switch (var15) {
               case 1:
                  this.addWorldItem(var12, var3, 0.71875F, 0.125F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 2:
                  this.addWorldItem(var12, var3, 0.0935F, 0.21875F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 3:
                  this.addWorldItem(var12, var3, 0.1328125F, 0.589375F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 4:
                  this.addWorldItem(var12, var3, 0.7890625F, 0.589375F, var2.getSurfaceOffsetNoTable() / 96.0F);
            }
         }

         if (var1 == IsoDirections.N) {
            switch (var15) {
               case 1:
                  this.addWorldItem(var12, var3, 0.921875F, 0.921875F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 2:
                  this.addWorldItem(var12, var3, 0.1640625F, 0.8984375F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 3:
                  this.addWorldItem(var12, var3, 0.021875F, 0.5F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 4:
                  this.addWorldItem(var12, var3, 0.8671875F, 0.5F, var2.getSurfaceOffsetNoTable() / 96.0F);
            }
         }

         if (var1 == IsoDirections.E) {
            switch (var15) {
               case 1:
                  this.addWorldItem(var12, var3, 0.234375F, 0.859375F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 2:
                  this.addWorldItem(var12, var3, 0.59375F, 0.875F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 3:
                  this.addWorldItem(var12, var3, 0.53125F, 0.125F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 4:
                  this.addWorldItem(var12, var3, 0.210937F, 0.1328125F, var2.getSurfaceOffsetNoTable() / 96.0F);
            }
         }

         if (var1 == IsoDirections.W) {
            switch (var15) {
               case 1:
                  this.addWorldItem(var12, var3, 0.515625F, 0.109375F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 2:
                  this.addWorldItem(var12, var3, 0.578125F, 0.890625F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 3:
                  this.addWorldItem(var12, var3, 0.8828125F, 0.8984375F, var2.getSurfaceOffsetNoTable() / 96.0F);
                  break;
               case 4:
                  this.addWorldItem(var12, var3, 0.8671875F, 0.1653125F, var2.getSurfaceOffsetNoTable() / 96.0F);
            }
         }
      }
   }

    IsoDirections getFacing(IsoSprite var1) {
      if (var1 != nullptr && var1.getProperties().Is("Facing")) {
    std::string var2 = var1.getProperties().Val("Facing");
         switch (var2) {
            case "N":
               return IsoDirections.N;
            case "S":
               return IsoDirections.S;
            case "W":
               return IsoDirections.W;
            case "E":
               return IsoDirections.E;
         }
      }

    return nullptr;
   }

    void checkForTableSpawn(BuildingDef var1, IsoObject var2) {
      if (Rand.NextBool(10)) {
    RBTableStoryBase var3 = RBTableStoryBase.getRandomStory(var2.getSquare(), var2);
         if (var3 != nullptr) {
            var3.randomizeBuilding(var1);
            this.doneTable = true;
         }
      }
   }

    IsoObject checkForTable(IsoGridSquare var1, IsoObject var2) {
      if (!this.tablesDone.contains(var2) && var1 != nullptr) {
         for (int var3 = 0; var3 < var1.getObjects().size(); var3++) {
    IsoObject var4 = (IsoObject)var1.getObjects().get(var3);
            if (!this.tablesDone.contains(var4)
               && var4.getProperties().isTable()
               && var4.getProperties().getSurface() == 34
               && var4.getContainer() == nullptr
               && var4 != var2) {
    return var4;
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

    void doProfessionStory(BuildingDef var1, const std::string& var2) {
      this.spawnItemsInContainers(var1, var2, 70);
   }

    void addRandomDeadSurvivorStory(BuildingDef var1) {
      this.initRDSMap(var1);
    int var2 = Rand.Next(this.totalChanceRDS);
    Iterator var3 = rdsMap.keySet().iterator();
    int var4 = 0;

      while (var3.hasNext()) {
    RandomizedDeadSurvivorBase var5 = (RandomizedDeadSurvivorBase)var3.next();
         var4 += rdsMap.get(var5);
         if (var2 < var4) {
            var5.randomizeDeadSurvivor(var1);
            if (var5.isUnique()) {
               getUniqueRDSSpawned().push_back(var5.getName());
            }
            break;
         }
      }
   }

    void initRDSMap(BuildingDef var1) {
      this.totalChanceRDS = 0;
      rdsMap.clear();

      for (int var2 = 0; var2 < this.deadSurvivorsStory.size(); var2++) {
    RandomizedDeadSurvivorBase var3 = this.deadSurvivorsStory.get(var2);
         if (var3.isValid(var1, false) && var3.isTimeValid(false) && (var3.isUnique() && !getUniqueRDSSpawned().contains(var3.getName()) || !var3.isUnique())) {
            this.totalChanceRDS = this.totalChanceRDS + this.deadSurvivorsStory.get(var2).getChance();
            rdsMap.put(this.deadSurvivorsStory.get(var2), this.deadSurvivorsStory.get(var2).getChance());
         }
      }
   }

    void doRandomDeadSurvivorStory(BuildingDef var1, RandomizedDeadSurvivorBase var2) {
      var2.randomizeDeadSurvivor(var1);
   }

    public RBBasic() {
      this.name = "RBBasic";
      this.deadSurvivorsStory.push_back(std::make_unique<RDSBleach>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSGunslinger>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSGunmanInBathroom>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSZombieLockedBathroom>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSDeadDrunk>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSSpecificProfession>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSZombiesEating>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSBandPractice>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSBathroomZed>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSBedroomZed>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSFootballNight>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSHenDo>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSStagDo>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSStudentNight>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSPokerNight>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSSuicidePact>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSPrisonEscape>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSPrisonEscapeWithPolice>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSSkeletonPsycho>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSCorpsePsycho>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSPoliceAtHouse>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSHouseParty>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSTinFoilHat>());
      this.deadSurvivorsStory.push_back(std::make_unique<RDSHockeyPsycho>());
      this.specificProfessionDistribution.push_back("Carpenter");
      this.specificProfessionDistribution.push_back("Electrician");
      this.specificProfessionDistribution.push_back("Farmer");
      this.specificProfessionDistribution.push_back("Nurse");
      this.specificProfessionRoomDistribution.put("Carpenter", "kitchen");
      this.specificProfessionRoomDistribution.put("Electrician", "kitchen");
      this.specificProfessionRoomDistribution.put("Farmer", "kitchen");
      this.specificProfessionRoomDistribution.put("Nurse", "kitchen");
      this.specificProfessionRoomDistribution.put("Nurse", "bathroom");
      this.coldFood.push_back("Base.Chicken");
      this.coldFood.push_back("Base.Steak");
      this.coldFood.push_back("Base.PorkChop");
      this.coldFood.push_back("Base.MuttonChop");
      this.coldFood.push_back("Base.MeatPatty");
      this.coldFood.push_back("Base.FishFillet");
      this.coldFood.push_back("Base.Salmon");
      this.plankStash.put("floors_interior_tilesandwood_01_40", "floors_interior_tilesandwood_01_56");
      this.plankStash.put("floors_interior_tilesandwood_01_41", "floors_interior_tilesandwood_01_57");
      this.plankStash.put("floors_interior_tilesandwood_01_42", "floors_interior_tilesandwood_01_58");
      this.plankStash.put("floors_interior_tilesandwood_01_43", "floors_interior_tilesandwood_01_59");
      this.plankStash.put("floors_interior_tilesandwood_01_44", "floors_interior_tilesandwood_01_60");
      this.plankStash.put("floors_interior_tilesandwood_01_45", "floors_interior_tilesandwood_01_61");
      this.plankStash.put("floors_interior_tilesandwood_01_46", "floors_interior_tilesandwood_01_62");
      this.plankStash.put("floors_interior_tilesandwood_01_47", "floors_interior_tilesandwood_01_63");
      this.plankStash.put("floors_interior_tilesandwood_01_52", "floors_interior_tilesandwood_01_68");
      kitchenSinkItems.put(1, "Soap2");
      kitchenSinkItems.put(2, "CleaningLiquid2");
      kitchenSinkItems.put(3, "Sponge");
      kitchenCounterItems.put(1, "Dogfood");
      kitchenCounterItems.put(2, "CannedCorn");
      kitchenCounterItems.put(3, "CannedPeas");
      kitchenCounterItems.put(4, "CannedPotato2");
      kitchenCounterItems.put(5, "CannedSardines");
      kitchenCounterItems.put(6, "CannedTomato2");
      kitchenCounterItems.put(7, "CannedCarrots2");
      kitchenCounterItems.put(8, "CannedChili");
      kitchenCounterItems.put(9, "CannedBolognese");
      kitchenCounterItems.put(10, "TinOpener");
      kitchenCounterItems.put(11, "WaterBottleFull");
      kitchenCounterItems.put(12, "Cereal");
      kitchenCounterItems.put(13, "CerealBowl");
      kitchenCounterItems.put(14, "Spoon");
      kitchenCounterItems.put(15, "Fork");
      kitchenCounterItems.put(16, "KitchenKnife");
      kitchenCounterItems.put(17, "ButterKnife");
      kitchenCounterItems.put(18, "BreadKnife");
      kitchenCounterItems.put(19, "DishCloth");
      kitchenCounterItems.put(20, "RollingPin");
      kitchenCounterItems.put(21, "EmptyJar");
      kitchenCounterItems.put(22, "Bowl");
      kitchenCounterItems.put(23, "MugWhite");
      kitchenCounterItems.put(24, "MugRed");
      kitchenCounterItems.put(25, "Mugl");
      kitchenCounterItems.put(26, "WaterPot");
      kitchenCounterItems.put(27, "WaterSaucepan");
      kitchenCounterItems.put(28, "PotOfSoup");
      kitchenCounterItems.put(29, "StewBowl");
      kitchenCounterItems.put(30, "SoupBowl");
      kitchenCounterItems.put(31, "WaterSaucepanPasta");
      kitchenCounterItems.put(32, "WaterSaucepanRice");
      kitchenStoveItems.put(1, "WaterSaucepanRice");
      kitchenStoveItems.put(2, "WaterSaucepanPasta");
      kitchenStoveItems.put(3, "WaterPot");
      kitchenStoveItems.put(4, "PotOfSoup");
      kitchenStoveItems.put(5, "WaterSaucepan");
      kitchenStoveItems.put(6, "PotOfStew");
      kitchenStoveItems.put(7, "PastaPot");
      kitchenStoveItems.put(8, "RicePot");
      bathroomSinkItems.put(1, "Comb");
      bathroomSinkItems.put(2, "Cologne");
      bathroomSinkItems.put(3, "Antibiotics");
      bathroomSinkItems.put(4, "Bandage");
      bathroomSinkItems.put(5, "Pills");
      bathroomSinkItems.put(6, "PillsAntiDep");
      bathroomSinkItems.put(7, "PillsBeta");
      bathroomSinkItems.put(8, "PillsSleepingTablets");
      bathroomSinkItems.put(9, "PillsVitamins");
      bathroomSinkItems.put(10, "Lipstick");
      bathroomSinkItems.put(11, "MakeupEyeshadow");
      bathroomSinkItems.put(12, "MakeupFoundation");
      bathroomSinkItems.put(13, "Perfume");
      bathroomSinkItems.put(14, "Razor");
      bathroomSinkItems.put(15, "Toothbrush");
      bathroomSinkItems.put(16, "Toothpaste");
      bathroomSinkItems.put(17, "Tweezers");
   }

   public std::vector<RandomizedDeadSurvivorBase> getSurvivorStories() {
      return this.deadSurvivorsStory;
   }

   public std::vector<std::string> getSurvivorProfession() {
      return this.specificProfessionDistribution;
   }

   public static std::vector<std::string> getUniqueRDSSpawned() {
    return uniqueRDSSpawned;
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
