#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/Lua/MapObjects.h"
#include "zombie/SandboxOptions.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/SurvivorFactory.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/population/Outfit.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/iso/objects/IsoZombieGiblets/GibletType.h"
#include "zombie/randomizedWorld/randomizedBuilding/RandomizedBuildingBase/HumanCorpse.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleType.h"
#include "zombie/vehicles/VehiclesDB2.h"

namespace zombie {
namespace randomizedWorld {


class RandomizedWorldBase {
:
    static const Vector2 s_tempVector2 = new Vector2();
    int minimumDays = 0;
    int maximumDays = 0;
    int minimumRooms = 0;
    bool unique = false;
    bool rvsVehicleKeyAddedToZombie = false;
    std::string name = nullptr;
    std::string debugLine = "";

    BaseVehicle addVehicle(Zone var1, IsoGridSquare var2, IsoChunk var3, std::string_view var4, std::string_view var5, IsoDirections var6) {
      return this.addVehicle(var1, var2, var3, var4, var5, nullptr, var6, nullptr);
   }

    BaseVehicle addVehicleFlipped(Zone var1, IsoGridSquare var2, IsoChunk var3, std::string_view var4, std::string_view var5, int var6, IsoDirections var7, std::string_view var8) {
      if (var2 == nullptr) {
    return nullptr;
      } else {
         if (var7 == nullptr) {
            var7 = IsoDirections.getRandom();
         }

    Vector2 var9 = var7.ToVector();
         return this.addVehicleFlipped(var1, var2.x, var2.y, var2.z, var9.getDirection(), var4, var5, var6, var8);
      }
   }

    BaseVehicle addVehicleFlipped(Zone var1, float var2, float var3, float var4, float var5, std::string_view var6, std::string_view var7, int var8, std::string_view var9) {
      if (StringUtils.isNullOrEmpty(var6)) {
         var6 = "junkyard";
      }

    IsoGridSquare var10 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var10 == nullptr) {
    return nullptr;
      } else {
    IsoChunk var11 = var10.getChunk();
    IsoDirections var12 = IsoDirections.fromAngle(var5);
    BaseVehicle var13 = new BaseVehicle(IsoWorld.instance.CurrentCell);
         var13.specificDistributionId = var9;
    VehicleType var14 = VehicleType.getRandomVehicleType(var6, false);
         if (!StringUtils.isNullOrEmpty(var7)) {
            var13.setScriptName(var7);
            var13.setScript();
            if (var8 != nullptr) {
               var13.setSkinIndex(var8);
            }
         } else {
            if (var14 == nullptr) {
    return nullptr;
            }

            var13.setVehicleType(var14.name);
            if (!var11.RandomizeModel(var13, var1, var6, var14)) {
    return nullptr;
            }
         }

         if (var14.isSpecialCar) {
            var13.setDoColor(false);
         }

         var13.setDir(var12);
    float var15 = var5 - (float) (Math.PI / 2);

         while (var15 > Math.PI * 2) {
            var15 = (float)(var15 - (Math.PI * 2));
         }

         var13.savedRot.rotationXYZ(0.0F, -var15, (float) Math.PI);
         var13.jniTransform.setRotation(var13.savedRot);
         var13.setX(var2);
         var13.setY(var3);
         var13.setZ(var4);
         if (IsoChunk.doSpawnedVehiclesInInvalidPosition(var13)) {
            var13.setSquare(var10);
            var10.chunk.vehicles.add(var13);
            var13.chunk = var10.chunk;
            var13.addToWorld();
            VehiclesDB2.instance.addVehicle(var13);
         }

         var13.setGeneralPartCondition(0.2F, 70.0F);
         var13.rust = Rand.Next(100) < 70 ? 1.0F : 0.0F;
    return var13;
      }
   }

    BaseVehicle addVehicle(Zone var1, IsoGridSquare var2, IsoChunk var3, std::string_view var4, std::string_view var5, int var6, IsoDirections var7, std::string_view var8) {
      if (var2 == nullptr) {
    return nullptr;
      } else {
         if (var7 == nullptr) {
            var7 = IsoDirections.getRandom();
         }

    Vector2 var9 = var7.ToVector();
         var9.rotate(Rand.Next(-0.5F, 0.5F));
         return this.addVehicle(var1, var2.x, var2.y, var2.z, var9.getDirection(), var4, var5, var6, var8);
      }
   }

    BaseVehicle addVehicle(Zone var1, float var2, float var3, float var4, float var5, std::string_view var6, std::string_view var7, int var8, std::string_view var9) {
      if (StringUtils.isNullOrEmpty(var6)) {
         var6 = "junkyard";
      }

    IsoGridSquare var10 = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
      if (var10 == nullptr) {
    return nullptr;
      } else {
    IsoChunk var11 = var10.getChunk();
    IsoDirections var12 = IsoDirections.fromAngle(var5);
    BaseVehicle var13 = new BaseVehicle(IsoWorld.instance.CurrentCell);
         var13.specificDistributionId = var9;
    VehicleType var14 = VehicleType.getRandomVehicleType(var6, false);
         if (!StringUtils.isNullOrEmpty(var7)) {
            var13.setScriptName(var7);
            var13.setScript();
            if (var8 != nullptr) {
               var13.setSkinIndex(var8);
            }
         } else {
            if (var14 == nullptr) {
    return nullptr;
            }

            var13.setVehicleType(var14.name);
            if (!var11.RandomizeModel(var13, var1, var6, var14)) {
    return nullptr;
            }
         }

         if (var14.isSpecialCar) {
            var13.setDoColor(false);
         }

         var13.setDir(var12);
    float var15 = var5 - (float) (Math.PI / 2);

         while (var15 > Math.PI * 2) {
            var15 = (float)(var15 - (Math.PI * 2));
         }

         var13.savedRot.setAngleAxis(-var15, 0.0F, 1.0F, 0.0F);
         var13.jniTransform.setRotation(var13.savedRot);
         var13.setX(var2);
         var13.setY(var3);
         var13.setZ(var4);
         if (IsoChunk.doSpawnedVehiclesInInvalidPosition(var13)) {
            var13.setSquare(var10);
            var10.chunk.vehicles.add(var13);
            var13.chunk = var10.chunk;
            var13.addToWorld();
            VehiclesDB2.instance.addVehicle(var13);
         }

         var13.setGeneralPartCondition(0.2F, 70.0F);
         var13.rust = Rand.Next(100) < 70 ? 1.0F : 0.0F;
    return var13;
      }
   }

    static void removeAllVehiclesOnZone(Zone var0) {
      for (int var1 = var0.x; var1 < var0.x + var0.w; var1++) {
         for (int var2 = var0.y; var2 < var0.y + var0.h; var2++) {
    IsoGridSquare var3 = IsoCell.getInstance().getGridSquare(var1, var2, 0);
            if (var3 != nullptr) {
    BaseVehicle var4 = var3.getVehicleContainer();
               if (var4 != nullptr) {
                  var4.permanentlyRemove();
               }
            }
         }
      }
   }

    ArrayList<IsoZombie> addZombiesOnVehicle(int var1, String var2, Integer var3, BaseVehicle var4) {
    std::vector var5 = new ArrayList();
      if (var4 == nullptr) {
    return var5;
      } else {
    int var6 = 100;
    IsoGridSquare var7 = var4.getSquare();
         if (var7 != nullptr && var7.getCell() != nullptr) {
            for (; var1 > 0; var6 = 100) {
               while (var6 > 0) {
    IsoGridSquare var8 = var7.getCell().getGridSquare(Rand.Next(var7.x - 4, var7.x + 4), Rand.Next(var7.y - 4, var7.y + 4), var7.z);
                  if (var8 != nullptr && var8.getVehicleContainer() == nullptr) {
                     var1--;
                     var5.addAll(this.addZombiesOnSquare(1, var2, var3, var8));
                     break;
                  }

                  var6--;
               }
            }

            if (!this.rvsVehicleKeyAddedToZombie && !var5.isEmpty()) {
    IsoZombie var9 = (IsoZombie)var5.get(Rand.Next(0, var5.size()));
               var9.addItemToSpawnAtDeath(var4.createVehicleKey());
               this.rvsVehicleKeyAddedToZombie = true;
            }

    return var5;
         } else {
    return var5;
         }
      }
   }

    static IsoDeadBody createRandomDeadBody(RoomDef var0, int var1) {
      if (IsoWorld.getZombiesDisabled()) {
    return nullptr;
      } else if (var0 == nullptr) {
    return nullptr;
      } else {
    IsoGridSquare var2 = getRandomSquareForCorpse(var0);
    return var2 = = nullptr ? nullptr : createRandomDeadBody(var2, nullptr, var1, 0, nullptr);
      }
   }

    ArrayList<IsoZombie> addZombiesOnSquare(int var1, String var2, Integer var3, IsoGridSquare var4) {
    std::vector var5 = new ArrayList();
      if (IsoWorld.getZombiesDisabled()) {
    return var5;
      } else if (var4 == nullptr) {
    return var5;
      } else {
         for (int var6 = 0; var6 < var1; var6++) {
            VirtualZombieManager.instance.choices.clear();
            VirtualZombieManager.instance.choices.add(var4);
    IsoZombie var7 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.getRandom().index(), false);
            if (var7 != nullptr) {
               if (var3 != nullptr) {
                  var7.setFemaleEtc(Rand.Next(100) < var3);
               }

               if (var2 != nullptr) {
                  var7.dressInPersistentOutfit(var2);
                  var7.bDressInRandomOutfit = false;
               } else {
                  var7.dressInRandomOutfit();
                  var7.bDressInRandomOutfit = false;
               }

               var5.add(var7);
            }
         }

         ZombieSpawnRecorder.instance.record(var5, this.getClass().getSimpleName());
    return var5;
      }
   }

    static IsoDeadBody createRandomDeadBody(int var0, int var1, int var2, IsoDirections var3, int var4) {
    return createRandomDeadBody();
   }

    static IsoDeadBody createRandomDeadBody(int var0, int var1, int var2, IsoDirections var3, int var4, int var5) {
    IsoGridSquare var6 = IsoCell.getInstance().getGridSquare(var0, var1, var2);
    return createRandomDeadBody();
   }

    static IsoDeadBody createRandomDeadBody(IsoGridSquare var0, IsoDirections var1, int var2, int var3, std::string_view var4) {
      if (var0 == nullptr) {
    return nullptr;
      } else {
    bool var5 = var1 == nullptr;
         if (var5) {
            var1 = IsoDirections.getRandom();
         }

         return createRandomDeadBody(
            var0.x + Rand.Next(0.05F, 0.95F), var0.y + Rand.Next(0.05F, 0.95F), var0.z, var1.ToVector().getDirection(), var5, var2, var3, var4
         );
      }
   }

    static IsoDeadBody createRandomDeadBody(float var0, float var1, float var2, float var3, bool var4, int var5, int var6, std::string_view var7) {
      if (IsoWorld.getZombiesDisabled()) {
    return nullptr;
      } else {
    IsoGridSquare var8 = IsoCell.getInstance().getGridSquare(var0, var1, var2);
         if (var8 == nullptr) {
    return nullptr;
         } else {
    IsoDirections var9 = IsoDirections.fromAngle(var3);
            VirtualZombieManager.instance.choices.clear();
            VirtualZombieManager.instance.choices.add(var8);
    IsoZombie var10 = VirtualZombieManager.instance.createRealZombieAlways(var9.index(), false);
            if (var10 == nullptr) {
    return nullptr;
            } else {
               if (var7 != nullptr) {
                  var10.dressInPersistentOutfit(var7);
                  var10.bDressInRandomOutfit = false;
               } else {
                  var10.dressInRandomOutfit();
               }

               if (Rand.Next(100) < var6) {
                  var10.setFakeDead(true);
                  var10.setCrawler(true);
                  var10.setCanWalk(false);
                  var10.setCrawlerType(1);
               } else {
                  var10.setFakeDead(false);
                  var10.setHealth(0.0F);
               }

               var10.upKillCount = false;
               var10.getHumanVisual().zombieRotStage = ((HumanVisual)var10.getVisual()).pickRandomZombieRotStage();

               for (int var11 = 0; var11 < var5; var11++) {
                  var10.addBlood(nullptr, false, true, true);
               }

               var10.DoCorpseInventory();
               var10.setX(var0);
               var10.setY(var1);
               var10.getForwardDirection().setLengthAndDirection(var3, 1.0F);
               if (var4 || var10.isSkeleton()) {
                  alignCorpseToSquare(var10, var8);
               }

    IsoDeadBody var12 = new IsoDeadBody(var10, true);
               if (!var12.isFakeDead() && !var12.isSkeleton() && Rand.Next(20) == 0) {
                  var12.setFakeDead(true);
                  if (Rand.Next(5) == 0) {
                     var12.setCrawling(true);
                  }
               }

    return var12;
            }
         }
      }
   }

    void addTraitOfBlood(IsoDirections var1, int var2, int var3, int var4, int var5) {
      for (int var6 = 0; var6 < var2; var6++) {
    float var7 = 0.0F;
    float var8 = 0.0F;
         if (var1 == IsoDirections.S) {
            var8 = Rand.Next(-2.0F, 0.5F);
         }

         if (var1 == IsoDirections.N) {
            var8 = Rand.Next(-0.5F, 2.0F);
         }

         if (var1 == IsoDirections.E) {
            var7 = Rand.Next(-2.0F, 0.5F);
         }

         if (var1 == IsoDirections.W) {
            var7 = Rand.Next(-0.5F, 2.0F);
         }

    new IsoZombieGiblets();
      }
   }

    void addTrailOfBlood(float var1, float var2, float var3, float var4, int var5) {
    Vector2 var6 = s_tempVector2;

      for (int var7 = 0; var7 < var5; var7++) {
    float var8 = Rand.Next(-0.5F, 2.0F);
         if (var8 < 0.0F) {
            var6.setLengthAndDirection(var4 + (float) Math.PI, -var8);
         } else {
            var6.setLengthAndDirection(var4, var8);
         }

    new IsoZombieGiblets();
      }
   }

    void addBloodSplat(IsoGridSquare var1, int var2) {
      for (int var3 = 0; var3 < var2; var3++) {
         var1.getChunk().addBloodSplat(var1.x + Rand.Next(-0.5F, 0.5F), var1.y + Rand.Next(-0.5F, 0.5F), var1.z, Rand.Next(8));
      }
   }

    void setAttachedItem(IsoZombie var1, std::string_view var2, std::string_view var3, std::string_view var4) {
    InventoryItem var5 = InventoryItemFactory.CreateItem(var3);
      if (var5 != nullptr) {
         var5.setCondition(Rand.Next(Math.max(2, var5.getConditionMax() - 5), var5.getConditionMax()));
         if (var5 instanceof HandWeapon) {
            ((HandWeapon)var5).randomizeBullets();
         }

         var1.setAttachedItem(var2, var5);
         if (!StringUtils.isNullOrEmpty(var4)) {
            var1.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem(var4));
         }
      }
   }

    static IsoGameCharacter createRandomZombie(RoomDef var0) {
    IsoGridSquare var1 = getRandomSpawnSquare(var0);
    return createRandomZombie();
   }

    static IsoGameCharacter createRandomZombieForCorpse(RoomDef var0) {
    IsoGridSquare var1 = getRandomSquareForCorpse(var0);
      if (var1 == nullptr) {
    return nullptr;
      } else {
    IsoGameCharacter var2 = createRandomZombie(var1.getX(), var1.getY(), var1.getZ());
         if (var2 != nullptr) {
            alignCorpseToSquare(var2, var1);
         }

    return var2;
      }
   }

    static IsoDeadBody createBodyFromZombie(IsoGameCharacter var0) {
      if (IsoWorld.getZombiesDisabled()) {
    return nullptr;
      } else {
         for (int var1 = 0; var1 < 6; var1++) {
            var0.splatBlood(Rand.Next(1, 4), 0.3F);
         }

         return new IsoDeadBody(var0, true);
      }
   }

    static IsoGameCharacter createRandomZombie(int var0, int var1, int var2) {
    HumanCorpse var3 = new HumanCorpse(IsoWorld.instance.getCell(), var0, var1, var2);
      var3.setDescriptor(SurvivorFactory.CreateSurvivor());
      var3.setFemale(var3.getDescriptor().isFemale());
      var3.setDir(IsoDirections.fromIndex(Rand.Next(8)));
      var3.initWornItems("Human");
      var3.initAttachedItems("Human");
    Outfit var4 = var3.getRandomDefaultOutfit();
      var3.dressInNamedOutfit(var4.m_Name);
      var3.initSpritePartsEmpty();
      var3.Dressup(var3.getDescriptor());
    return var3;
   }

    static bool isSquareClear(IsoGridSquare var0) {
      return var0 != nullptr
         && canSpawnAt(var0)
         && !var0.HasStairs()
         && !var0.HasTree()
         && !var0.getProperties().Is(IsoFlagType.bed)
         && !var0.getProperties().Is(IsoFlagType.waterPiped);
   }

    static bool isSquareClear(IsoGridSquare var0, IsoDirections var1) {
    IsoGridSquare var2 = var0.getAdjacentSquare(var1);
    return isSquareClear();
   }

    static bool is1x2AreaClear(IsoGridSquare var0) {
    return isSquareClear();
   }

    static bool is2x1AreaClear(IsoGridSquare var0) {
    return isSquareClear();
   }

    static bool is2x1or1x2AreaClear(IsoGridSquare var0) {
    return isSquareClear();
   }

    static bool is2x2AreaClear(IsoGridSquare var0) {
    return isSquareClear();
   }

    static void alignCorpseToSquare(IsoGameCharacter var0, IsoGridSquare var1) {
    int var2 = var1.x;
    int var3 = var1.y;
    IsoDirections var4 = IsoDirections.fromIndex(Rand.Next(8));
    bool var5 = is1x2AreaClear(var1);
    bool var6 = is2x1AreaClear(var1);
      if (var5 && var6) {
         var5 = Rand.Next(2) == 0;
         var6 = !var5;
      }

      if (is2x2AreaClear(var1)) {
         var0.setX(var2);
         var0.setY(var3);
      } else if (var5) {
         var0.setX(var2 + 0.5F);
         var0.setY(var3);
         var4 = Rand.Next(2) == 0 ? IsoDirections.N : IsoDirections.S;
      } else if (var6) {
         var0.setX(var2);
         var0.setY(var3 + 0.5F);
         var4 = Rand.Next(2) == 0 ? IsoDirections.W : IsoDirections.E;
      } else if (is1x2AreaClear(var1.getAdjacentSquare(IsoDirections.S))) {
         var0.setX(var2 + 0.5F);
         var0.setY(var3 + 0.99F);
         var4 = Rand.Next(2) == 0 ? IsoDirections.N : IsoDirections.S;
      } else if (is2x1AreaClear(var1.getAdjacentSquare(IsoDirections.E))) {
         var0.setX(var2 + 0.99F);
         var0.setY(var3 + 0.5F);
         var4 = Rand.Next(2) == 0 ? IsoDirections.W : IsoDirections.E;
      }

      var0.setDir(var4);
      var0.lx = var0.nx = var0.x;
      var0.ly = var0.ny = var0.y;
      var0.setScriptnx(var0.x);
      var0.setScriptny(var0.y);
   }

    RoomDef getRandomRoom(BuildingDef var1, int var2) {
    RoomDef var3 = (RoomDef)var1.getRooms().get(Rand.Next(0, var1.getRooms().size()));
      if (var2 > 0 && var3.area >= var2) {
    return var3;
      } else {
    int var4 = 0;

         while (var4 <= 20) {
            var4++;
            var3 = (RoomDef)var1.getRooms().get(Rand.Next(0, var1.getRooms().size()));
            if (var3.area >= var2) {
    return var3;
            }
         }

    return var3;
      }
   }

    RoomDef getRoom(BuildingDef var1, std::string_view var2) {
      for (int var3 = 0; var3 < var1.rooms.size(); var3++) {
    RoomDef var4 = (RoomDef)var1.rooms.get(var3);
         if (var4.getName().equalsIgnoreCase(var2)) {
    return var4;
         }
      }

    return nullptr;
   }

    RoomDef getLivingRoomOrKitchen(BuildingDef var1) {
    RoomDef var2 = this.getRoom(var1, "livingroom");
      if (var2 == nullptr) {
         var2 = this.getRoom(var1, "kitchen");
      }

    return var2;
   }

    static bool canSpawnAt(IsoGridSquare var0) {
      if (var0 == nullptr) {
    return false;
      } else {
         return var0.HasStairs() ? false : VirtualZombieManager.instance.canSpawnAt(var0.x, var0.y, var0.z);
      }
   }

    static IsoGridSquare getRandomSpawnSquare(RoomDef var0) {
    return var0 = = nullptr ? nullptr : var0.getRandomSquare(RandomizedWorldBase::canSpawnAt);
   }

    static IsoGridSquare getRandomSquareForCorpse(RoomDef var0) {
    IsoGridSquare var1 = var0.getRandomSquare(RandomizedWorldBase::is2x2AreaClear);
    IsoGridSquare var2 = var0.getRandomSquare(RandomizedWorldBase::is2x1or1x2AreaClear);
      if (var1 == nullptr || var2 != nullptr && Rand.Next(4) == 0) {
         var1 = var2;
      }

    return var1;
   }

    BaseVehicle spawnCarOnNearestNav(std::string_view var1, BuildingDef var2) {
    IsoGridSquare var3 = nullptr;
    int var4 = (var2.x + var2.x2) / 2;
    int var5 = (var2.y + var2.y2) / 2;

      for (int var6 = var4; var6 < var4 + 20; var6++) {
    IsoGridSquare var7 = IsoCell.getInstance().getGridSquare(var6, var5, 0);
         if (var7 != nullptr && "Nav" == var7.getZoneType())) {
            var3 = var7;
            break;
         }
      }

      if (var3 != nullptr) {
         return this.spawnCar(var1, var3);
      } else {
         for (int var8 = var4; var8 > var4 - 20; var8--) {
    IsoGridSquare var11 = IsoCell.getInstance().getGridSquare(var8, var5, 0);
            if (var11 != nullptr && "Nav" == var11.getZoneType())) {
               var3 = var11;
               break;
            }
         }

         if (var3 != nullptr) {
            return this.spawnCar(var1, var3);
         } else {
            for (int var9 = var5; var9 < var5 + 20; var9++) {
    IsoGridSquare var12 = IsoCell.getInstance().getGridSquare(var4, var9, 0);
               if (var12 != nullptr && "Nav" == var12.getZoneType())) {
                  var3 = var12;
                  break;
               }
            }

            if (var3 != nullptr) {
               return this.spawnCar(var1, var3);
            } else {
               for (int var10 = var5; var10 > var5 - 20; var10--) {
    IsoGridSquare var13 = IsoCell.getInstance().getGridSquare(var4, var10, 0);
                  if (var13 != nullptr && "Nav" == var13.getZoneType())) {
                     var3 = var13;
                     break;
                  }
               }

               return var3 != nullptr ? this.spawnCar(var1, var3) : nullptr;
            }
         }
      }
   }

    BaseVehicle spawnCar(std::string_view var1, IsoGridSquare var2) {
    BaseVehicle var3 = new BaseVehicle(IsoWorld.instance.CurrentCell);
      var3.setScriptName(var1);
      var3.setX(var2.x + 0.5F);
      var3.setY(var2.y + 0.5F);
      var3.setZ(0.0F);
      var3.savedRot.setAngleAxis(Rand.Next(0.0F, (float) (Math.PI * 2)), 0.0F, 1.0F, 0.0F);
      var3.jniTransform.setRotation(var3.savedRot);
      if (IsoChunk.doSpawnedVehiclesInInvalidPosition(var3)) {
         var3.keySpawned = 1;
         var3.setSquare(var2);
         var3.square.chunk.vehicles.add(var3);
         var3.chunk = var3.square.chunk;
         var3.addToWorld();
         VehiclesDB2.instance.addVehicle(var3);
      }

      var3.setGeneralPartCondition(0.3F, 70.0F);
    return var3;
   }

    InventoryItem addItemOnGround(IsoGridSquare var1, std::string_view var2) {
      return var1 != nullptr && !StringUtils.isNullOrWhitespace(var2)
         ? var1.AddWorldInventoryItem(var2, Rand.Next(0.2F, 0.8F), Rand.Next(0.2F, 0.8F), 0.0F)
         : nullptr;
   }

    InventoryItem addItemOnGround(IsoGridSquare var1, InventoryItem var2) {
      return var1 != nullptr && var2 != nullptr ? var1.AddWorldInventoryItem(var2, Rand.Next(0.2F, 0.8F), Rand.Next(0.2F, 0.8F), 0.0F) : nullptr;
   }

    void addRandomItemsOnGround(RoomDef var1, std::string_view var2, int var3) {
      for (int var4 = 0; var4 < var3; var4++) {
    IsoGridSquare var5 = getRandomSpawnSquare(var1);
         this.addItemOnGround(var5, var2);
      }
   }

    void addRandomItemsOnGround(RoomDef var1, ArrayList<String> var2, int var3) {
      for (int var4 = 0; var4 < var3; var4++) {
    IsoGridSquare var5 = getRandomSpawnSquare(var1);
         this.addRandomItemOnGround(var5, var2);
      }
   }

    InventoryItem addRandomItemOnGround(IsoGridSquare var1, ArrayList<String> var2) {
      if (var1 != nullptr && !var2.isEmpty()) {
    std::string var3 = (String)PZArrayUtil.pickRandom(var2);
         return this.addItemOnGround(var1, var3);
      } else {
    return nullptr;
      }
   }

    HandWeapon addWeapon(std::string_view var1, bool var2) {
    HandWeapon var3 = (HandWeapon)InventoryItemFactory.CreateItem(var1);
      if (var3 == nullptr) {
    return nullptr;
      } else {
         if (var3.isRanged() && var2) {
            if (!StringUtils.isNullOrWhitespace(var3.getMagazineType())) {
               var3.setContainsClip(true);
            }

            var3.setCurrentAmmoCount(Rand.Next(Math.max(var3.getMaxAmmo() - 8, 0), var3.getMaxAmmo() - 2));
         }

    return var3;
      }
   }

    IsoDeadBody createSkeletonCorpse(RoomDef var1) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
    IsoGridSquare var2 = var1.getRandomSquare(RandomizedWorldBase::is2x1or1x2AreaClear);
         if (var2 == nullptr) {
    return nullptr;
         } else {
            VirtualZombieManager.instance.choices.clear();
            VirtualZombieManager.instance.choices.add(var2);
    IsoZombie var3 = VirtualZombieManager.instance.createRealZombieAlways(Rand.Next(8), false);
            if (var3 == nullptr) {
    return nullptr;
            } else {
               ZombieSpawnRecorder.instance.record(var3, this.getClass().getSimpleName());
               alignCorpseToSquare(var3, var2);
               var3.setFakeDead(false);
               var3.setHealth(0.0F);
               var3.upKillCount = false;
               var3.setSkeleton(true);
               var3.getHumanVisual().setSkinTextureIndex(Rand.Next(1, 3));
               return new IsoDeadBody(var3, true);
            }
         }
      }
   }

    bool isTimeValid(bool var1) {
      if (this.minimumDays != 0 && this.maximumDays != 0) {
    float var2 = (float)GameTime.getInstance().getWorldAgeHours() / 24.0F;
         var2 += (SandboxOptions.instance.TimeSinceApo.getValue() - 1) * 30;
         return this.minimumDays > 0 && var2 < this.minimumDays ? false : this.maximumDays <= 0 || !(var2 > this.maximumDays);
      } else {
    return true;
      }
   }

    std::string getName() const {
      return this.name;
   }

    std::string getDebugLine() const {
      return this.debugLine;
   }

    void setDebugLine(std::string_view var1) {
      this.debugLine = var1;
   }

    int getMaximumDays() const {
      return this.maximumDays;
   }

    void setMaximumDays(int var1) {
      this.maximumDays = var1;
   }

    bool isUnique() {
      return this.unique;
   }

    void setUnique(bool var1) {
      this.unique = var1;
   }

    IsoGridSquare getSq(int var1, int var2, int var3) {
      return IsoWorld.instance.getCell().getGridSquare(var1, var2, var3);
   }

    IsoObject addTileObject(int var1, int var2, int var3, std::string_view var4) {
      return this.addTileObject(this.getSq(var1, var2, var3), var4);
   }

    IsoObject addTileObject(IsoGridSquare var1, std::string_view var2) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
    IsoObject var3 = IsoObject.getNew(var1, var2, nullptr, false);
         var1.AddTileObject(var3);
         MapObjects.newGridSquare(var1);
         MapObjects.loadGridSquare(var1);
    return var3;
      }
   }

    IsoObject addTentNorthSouth(int var1, int var2, int var3) {
      this.addTileObject(var1, var2 - 1, var3, "camping_01_1");
      return this.addTileObject(var1, var2, var3, "camping_01_0");
   }

    IsoObject addTentWestEast(int var1, int var2, int var3) {
      this.addTileObject(var1 - 1, var2, var3, "camping_01_2");
      return this.addTileObject(var1, var2, var3, "camping_01_3");
   }

    BaseVehicle addTrailer(BaseVehicle var1, Zone var2, IsoChunk var3, std::string_view var4, std::string_view var5, std::string_view var6) {
    IsoGridSquare var7 = var1.getSquare();
    IsoDirections var8 = var1.getDir();
    uint8_t var9 = 0;
    uint8_t var10 = 0;
      if (var8 == IsoDirections.S) {
         var10 = -3;
      }

      if (var8 == IsoDirections.N) {
         var10 = 3;
      }

      if (var8 == IsoDirections.W) {
         var9 = 3;
      }

      if (var8 == IsoDirections.E) {
         var9 = -3;
      }

    BaseVehicle var11 = this.addVehicle(var2, this.getSq(var7.x + var9, var7.y + var10, var7.z), var3, var4, var6, nullptr, var8, var5);
      if (var11 != nullptr) {
         var1.positionTrailer(var11);
      }

    return var11;
   }
}
} // namespace randomizedWorld
} // namespace zombie
