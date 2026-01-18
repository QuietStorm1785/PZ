#pragma once
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
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/randomizedWorld/randomizedBuilding/RandomizedBuildingBase.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleType.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RandomizedWorldBase {
public:
  static const Vector2 s_tempVector2 = new Vector2();
  int minimumDays = 0;
  int maximumDays = 0;
  int minimumRooms = 0;
  bool unique = false;
  bool rvsVehicleKeyAddedToZombie = false;
  std::string name = null;
  std::string debugLine = "";

  BaseVehicle addVehicle(IsoMetaGrid.Zone zone, IsoGridSquare sq,
                         IsoChunk chunk, const std::string &zoneName,
                         const std::string &scriptName, IsoDirections dir) {
    return this.addVehicle(zone, sq, chunk, zoneName, scriptName, nullptr, dir,
                           nullptr);
  }

public
  BaseVehicle addVehicleFlipped(IsoMetaGrid.Zone zone, IsoGridSquare sq,
                                IsoChunk chunk, String zoneName,
                                String scriptName, Integer skinIndex,
                                IsoDirections dir, String specificContainer) {
    if (sq == nullptr) {
      return null;
    } else {
      if (dir == nullptr) {
        dir = IsoDirections.getRandom();
      }

      Vector2 vector = dir.ToVector();
      return this.addVehicleFlipped(zone, sq.x, sq.y, sq.z,
                                    vector.getDirection(), zoneName, scriptName,
                                    skinIndex, specificContainer);
    }
  }

public
  BaseVehicle addVehicleFlipped(IsoMetaGrid.Zone zone, float vehicleX,
                                float vehicleY, float vehicleZ, float direction,
                                String zoneName, String scriptName,
                                Integer skinIndex, String specificContainer) {
    if (StringUtils.isNullOrEmpty(zoneName)) {
      zoneName = "junkyard";
    }

    IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(
        (double)vehicleX, (double)vehicleY, (double)vehicleZ);
    if (square == nullptr) {
      return null;
    } else {
      IsoChunk chunk = square.getChunk();
      IsoDirections directions = IsoDirections.fromAngle(direction);
      BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
      vehicle.specificDistributionId = specificContainer;
      VehicleType vehicleType =
          VehicleType.getRandomVehicleType(zoneName, false);
      if (!StringUtils.isNullOrEmpty(scriptName)) {
        vehicle.setScriptName(scriptName);
        vehicle.setScript();
        if (skinIndex != nullptr) {
          vehicle.setSkinIndex(skinIndex);
        }
      } else {
        if (vehicleType == nullptr) {
          return null;
        }

        vehicle.setVehicleType(vehicleType.name);
        if (!chunk.RandomizeModel(vehicle, zone, zoneName, vehicleType)) {
          return null;
        }
      }

      if (vehicleType.isSpecialCar) {
        vehicle.setDoColor(false);
      }

      vehicle.setDir(directions);
      float float0 = direction - (float)(Math.PI / 2);

      while (float0 > Math.PI * 2) {
        float0 = (float)(float0 - (Math.PI * 2));
      }

      vehicle.savedRot.rotationXYZ(0.0F, -float0, (float)Math.PI);
      vehicle.jniTransform.setRotation(vehicle.savedRot);
      vehicle.setX(vehicleX);
      vehicle.setY(vehicleY);
      vehicle.setZ(vehicleZ);
      if (IsoChunk.doSpawnedVehiclesInInvalidPosition(vehicle)) {
        vehicle.setSquare(square);
        square.chunk.vehicles.add(vehicle);
        vehicle.chunk = square.chunk;
        vehicle.addToWorld();
        VehiclesDB2.instance.addVehicle(vehicle);
      }

      vehicle.setGeneralPartCondition(0.2F, 70.0F);
      vehicle.rust = Rand.Next(100) < 70 ? 1.0F : 0.0F;
      return vehicle;
    }
  }

public
  BaseVehicle addVehicle(IsoMetaGrid.Zone zone, IsoGridSquare sq,
                         IsoChunk chunk, String zoneName, String scriptName,
                         Integer skinIndex, IsoDirections dir,
                         String specificContainer) {
    if (sq == nullptr) {
      return null;
    } else {
      if (dir == nullptr) {
        dir = IsoDirections.getRandom();
      }

      Vector2 vector = dir.ToVector();
      vector.rotate(Rand.Next(-0.5F, 0.5F));
      return this.addVehicle(zone, sq.x, sq.y, sq.z, vector.getDirection(),
                             zoneName, scriptName, skinIndex,
                             specificContainer);
    }
  }

public
  BaseVehicle addVehicle(IsoMetaGrid.Zone zone, float vehicleX, float vehicleY,
                         float vehicleZ, float direction, String zoneName,
                         String scriptName, Integer skinIndex,
                         String specificContainer) {
    if (StringUtils.isNullOrEmpty(zoneName)) {
      zoneName = "junkyard";
    }

    IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(
        (double)vehicleX, (double)vehicleY, (double)vehicleZ);
    if (square == nullptr) {
      return null;
    } else {
      IsoChunk chunk = square.getChunk();
      IsoDirections directions = IsoDirections.fromAngle(direction);
      BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
      vehicle.specificDistributionId = specificContainer;
      VehicleType vehicleType =
          VehicleType.getRandomVehicleType(zoneName, false);
      if (!StringUtils.isNullOrEmpty(scriptName)) {
        vehicle.setScriptName(scriptName);
        vehicle.setScript();
        if (skinIndex != nullptr) {
          vehicle.setSkinIndex(skinIndex);
        }
      } else {
        if (vehicleType == nullptr) {
          return null;
        }

        vehicle.setVehicleType(vehicleType.name);
        if (!chunk.RandomizeModel(vehicle, zone, zoneName, vehicleType)) {
          return null;
        }
      }

      if (vehicleType.isSpecialCar) {
        vehicle.setDoColor(false);
      }

      vehicle.setDir(directions);
      float float0 = direction - (float)(Math.PI / 2);

      while (float0 > Math.PI * 2) {
        float0 = (float)(float0 - (Math.PI * 2));
      }

      vehicle.savedRot.setAngleAxis(-float0, 0.0F, 1.0F, 0.0F);
      vehicle.jniTransform.setRotation(vehicle.savedRot);
      vehicle.setX(vehicleX);
      vehicle.setY(vehicleY);
      vehicle.setZ(vehicleZ);
      if (IsoChunk.doSpawnedVehiclesInInvalidPosition(vehicle)) {
        vehicle.setSquare(square);
        square.chunk.vehicles.add(vehicle);
        vehicle.chunk = square.chunk;
        vehicle.addToWorld();
        VehiclesDB2.instance.addVehicle(vehicle);
      }

      vehicle.setGeneralPartCondition(0.2F, 70.0F);
      vehicle.rust = Rand.Next(100) < 70 ? 1.0F : 0.0F;
      return vehicle;
    }
  }

  static void removeAllVehiclesOnZone(IsoMetaGrid.Zone zone) {
    for (int int0 = zone.x; int0 < zone.x + zone.w; int0++) {
      for (int int1 = zone.y; int1 < zone.y + zone.h; int1++) {
        IsoGridSquare square =
            IsoCell.getInstance().getGridSquare(int0, int1, 0);
        if (square != nullptr) {
          BaseVehicle vehicle = square.getVehicleContainer();
          if (vehicle != nullptr) {
            vehicle.permanentlyRemove();
          }
        }
      }
    }
  }

  /**
   * Add zombies near the vehicles, around a 4x4 square around it, avoiding
   * being  ON the vehicle & randomizing square for each zombies
   */
public
  ArrayList<IsoZombie> addZombiesOnVehicle(int totalZombies, String outfit,
                                           Integer femaleChance,
                                           BaseVehicle vehicle) {
    std::vector arrayList = new ArrayList();
    if (vehicle == nullptr) {
      return arrayList;
    } else {
      int int0 = 100;
      IsoGridSquare square0 = vehicle.getSquare();
      if (square0 != nullptr && square0.getCell() != nullptr) {
        for (; totalZombies > 0; int0 = 100) {
          while (int0 > 0) {
            IsoGridSquare square1 = square0.getCell().getGridSquare(
                Rand.Next(square0.x - 4, square0.x + 4),
                Rand.Next(square0.y - 4, square0.y + 4), square0.z);
            if (square1 != nullptr &&
                square1.getVehicleContainer() == nullptr) {
              totalZombies--;
              arrayList.addAll(
                  this.addZombiesOnSquare(1, outfit, femaleChance, square1));
              break;
            }

            int0--;
          }
        }

        if (!this.rvsVehicleKeyAddedToZombie && !arrayList.isEmpty()) {
          IsoZombie zombie0 =
              (IsoZombie)arrayList.get(Rand.Next(0, arrayList.size()));
          zombie0.addItemToSpawnAtDeath(vehicle.createVehicleKey());
          this.rvsVehicleKeyAddedToZombie = true;
        }

        return arrayList;
      } else {
        return arrayList;
      }
    }
  }

  static IsoDeadBody createRandomDeadBody(RoomDef room, int blood) {
    if (IsoWorld.getZombiesDisabled()) {
      return null;
    } else if (room == nullptr) {
      return null;
    } else {
      IsoGridSquare square = getRandomSquareForCorpse(room);
      return square = =
                 null ? null
                      : createRandomDeadBody(square, null, blood, 0, null);
    }
  }

public
  ArrayList<IsoZombie> addZombiesOnSquare(int totalZombies, String outfit,
                                          Integer femaleChance,
                                          IsoGridSquare square) {
    std::vector arrayList = new ArrayList();
    if (IsoWorld.getZombiesDisabled()) {
      return arrayList;
    } else if (square == nullptr) {
      return arrayList;
    } else {
      for (int int0 = 0; int0 < totalZombies; int0++) {
        VirtualZombieManager.instance.choices.clear();
        VirtualZombieManager.instance.choices.add(square);
        IsoZombie zombie0 =
            VirtualZombieManager.instance.createRealZombieAlways(
                IsoDirections.getRandom().index(), false);
        if (zombie0 != nullptr) {
          if (femaleChance != nullptr) {
            zombie0.setFemaleEtc(Rand.Next(100) < femaleChance);
          }

          if (outfit != nullptr) {
            zombie0.dressInPersistentOutfit(outfit);
            zombie0.bDressInRandomOutfit = false;
          } else {
            zombie0.dressInRandomOutfit();
            zombie0.bDressInRandomOutfit = false;
          }

          arrayList.add(zombie0);
        }
      }

      ZombieSpawnRecorder.instance.record(arrayList,
                                          this.getClass().getSimpleName());
      return arrayList;
    }
  }

  static IsoDeadBody createRandomDeadBody(int x, int y, int z,
                                          IsoDirections dir, int blood) {
    return createRandomDeadBody();
  }

  static IsoDeadBody createRandomDeadBody(int x, int y, int z,
                                          IsoDirections dir, int blood,
                                          int crawlerChance) {
    IsoGridSquare square = IsoCell.getInstance().getGridSquare(x, y, z);
    return createRandomDeadBody();
  }

  static IsoDeadBody createRandomDeadBody(IsoGridSquare sq, IsoDirections dir,
                                          int blood, int crawlerChance,
                                          const std::string &outfit) {
    if (sq == nullptr) {
      return null;
    } else {
      bool boolean0 = dir == null;
      if (boolean0) {
        dir = IsoDirections.getRandom();
      }

      return createRandomDeadBody(sq.x + Rand.Next(0.05F, 0.95F),
                                  sq.y + Rand.Next(0.05F, 0.95F), sq.z,
                                  dir.ToVector().getDirection(), boolean0,
                                  blood, crawlerChance, outfit);
    }
  }

public
  static IsoDeadBody createRandomDeadBody(float x, float y, float z,
                                          float direction,
                                          boolean alignToSquare, int blood,
                                          int crawlerChance, String outfit) {
    if (IsoWorld.getZombiesDisabled()) {
      return null;
    } else {
      IsoGridSquare square =
          IsoCell.getInstance().getGridSquare((double)x, (double)y, (double)z);
      if (square == nullptr) {
        return null;
      } else {
        IsoDirections directions = IsoDirections.fromAngle(direction);
        VirtualZombieManager.instance.choices.clear();
        VirtualZombieManager.instance.choices.add(square);
        IsoZombie zombie0 =
            VirtualZombieManager.instance.createRealZombieAlways(
                directions.index(), false);
        if (zombie0 == nullptr) {
          return null;
        } else {
          if (outfit != nullptr) {
            zombie0.dressInPersistentOutfit(outfit);
            zombie0.bDressInRandomOutfit = false;
          } else {
            zombie0.dressInRandomOutfit();
          }

          if (Rand.Next(100) < crawlerChance) {
            zombie0.setFakeDead(true);
            zombie0.setCrawler(true);
            zombie0.setCanWalk(false);
            zombie0.setCrawlerType(1);
          } else {
            zombie0.setFakeDead(false);
            zombie0.setHealth(0.0F);
          }

          zombie0.upKillCount = false;
          zombie0.getHumanVisual().zombieRotStage =
              ((HumanVisual)zombie0.getVisual()).pickRandomZombieRotStage();

          for (int int0 = 0; int0 < blood; int0++) {
            zombie0.addBlood(nullptr, false, true, true);
          }

          zombie0.DoCorpseInventory();
          zombie0.setX(x);
          zombie0.setY(y);
          zombie0.getForwardDirection().setLengthAndDirection(direction, 1.0F);
          if (alignToSquare || zombie0.isSkeleton()) {
            alignCorpseToSquare(zombie0, square);
          }

          IsoDeadBody deadBody = new IsoDeadBody(zombie0, true);
          if (!deadBody.isFakeDead() && !deadBody.isSkeleton() &&
              Rand.Next(20) == 0) {
            deadBody.setFakeDead(true);
            if (Rand.Next(5) == 0) {
              deadBody.setCrawling(true);
            }
          }

          return deadBody;
        }
      }
    }
  }

  void addTraitOfBlood(IsoDirections dir, int time, int x, int y, int z) {
    for (int int0 = 0; int0 < time; int0++) {
      float float0 = 0.0F;
      float float1 = 0.0F;
      if (dir == IsoDirections.S) {
        float1 = Rand.Next(-2.0F, 0.5F);
      }

      if (dir == IsoDirections.N) {
        float1 = Rand.Next(-0.5F, 2.0F);
      }

      if (dir == IsoDirections.E) {
        float0 = Rand.Next(-2.0F, 0.5F);
      }

      if (dir == IsoDirections.W) {
        float0 = Rand.Next(-0.5F, 2.0F);
      }

      new IsoZombieGiblets();
    }
  }

  void addTrailOfBlood(float x, float y, float z, float direction, int count) {
    Vector2 vector = s_tempVector2;

    for (int int0 = 0; int0 < count; int0++) {
      float float0 = Rand.Next(-0.5F, 2.0F);
      if (float0 < 0.0F) {
        vector.setLengthAndDirection(direction + (float)Math.PI, -float0);
      } else {
        vector.setLengthAndDirection(direction, float0);
      }

      new IsoZombieGiblets();
    }
  }

  void addBloodSplat(IsoGridSquare sq, int nbr) {
    for (int int0 = 0; int0 < nbr; int0++) {
      sq.getChunk().addBloodSplat(sq.x + Rand.Next(-0.5F, 0.5F),
                                  sq.y + Rand.Next(-0.5F, 0.5F), sq.z,
                                  Rand.Next(8));
    }
  }

  void setAttachedItem(IsoZombie zombie, const std::string &location,
                       const std::string &item, const std::string &ensureItem) {
    InventoryItem _item = InventoryItemFactory.CreateItem(item);
    if (_item != nullptr) {
      _item.setCondition(Rand.Next(Math.max(2, _item.getConditionMax() - 5),
                                   _item.getConditionMax()));
      if (_item instanceof HandWeapon) {
        ((HandWeapon)_item).randomizeBullets();
      }

      zombie.setAttachedItem(location, _item);
      if (!StringUtils.isNullOrEmpty(ensureItem)) {
        zombie.addItemToSpawnAtDeath(
            InventoryItemFactory.CreateItem(ensureItem));
      }
    }
  }

  static IsoGameCharacter createRandomZombie(RoomDef room) {
    IsoGridSquare square = getRandomSpawnSquare(room);
    return createRandomZombie();
  }

  static IsoGameCharacter createRandomZombieForCorpse(RoomDef room) {
    IsoGridSquare square = getRandomSquareForCorpse(room);
    if (square == nullptr) {
      return null;
    } else {
      IsoGameCharacter character =
          createRandomZombie(square.getX(), square.getY(), square.getZ());
      if (character != nullptr) {
        alignCorpseToSquare(character, square);
      }

      return character;
    }
  }

  static IsoDeadBody createBodyFromZombie(IsoGameCharacter chr) {
    if (IsoWorld.getZombiesDisabled()) {
      return null;
    } else {
      for (int int0 = 0; int0 < 6; int0++) {
        chr.splatBlood(Rand.Next(1, 4), 0.3F);
      }

      return new IsoDeadBody(chr, true);
    }
  }

  static IsoGameCharacter createRandomZombie(int x, int y, int z) {
    RandomizedBuildingBase.HumanCorpse humanCorpse =
        new RandomizedBuildingBase.HumanCorpse(IsoWorld.instance.getCell(), x,
                                               y, z);
    humanCorpse.setDescriptor(SurvivorFactory.CreateSurvivor());
    humanCorpse.setFemale(humanCorpse.getDescriptor().isFemale());
    humanCorpse.setDir(IsoDirections.fromIndex(Rand.Next(8)));
    humanCorpse.initWornItems("Human");
    humanCorpse.initAttachedItems("Human");
    Outfit outfit = humanCorpse.getRandomDefaultOutfit();
    humanCorpse.dressInNamedOutfit(outfit.m_Name);
    humanCorpse.initSpritePartsEmpty();
    humanCorpse.Dressup(humanCorpse.getDescriptor());
    return humanCorpse;
  }

  static bool isSquareClear(IsoGridSquare square) {
    return square != nullptr && canSpawnAt(square) && !square.HasStairs() &&
           !square.HasTree() && !square.getProperties().Is(IsoFlagType.bed) &&
           !square.getProperties().Is(IsoFlagType.waterPiped);
  }

  static bool isSquareClear(IsoGridSquare square1, IsoDirections directions) {
    IsoGridSquare square0 = square1.getAdjacentSquare(directions);
    return isSquareClear();
  }

  static bool is1x2AreaClear(IsoGridSquare square) { return isSquareClear(); }

  static bool is2x1AreaClear(IsoGridSquare square) { return isSquareClear(); }

  static bool is2x1or1x2AreaClear(IsoGridSquare square) {
    return isSquareClear();
  }

  static bool is2x2AreaClear(IsoGridSquare square) {
    return isSquareClear();
    &&isSquareClear(square, IsoDirections.N) &&
        isSquareClear(square, IsoDirections.W) &&
        isSquareClear(square, IsoDirections.NW);
  }

  static void alignCorpseToSquare(IsoGameCharacter chr, IsoGridSquare square) {
    int int0 = square.x;
    int int1 = square.y;
    IsoDirections directions = IsoDirections.fromIndex(Rand.Next(8));
    bool boolean0 = is1x2AreaClear(square);
    bool boolean1 = is2x1AreaClear(square);
    if (boolean0 && boolean1) {
      boolean0 = Rand.Next(2) == 0;
      boolean1 = !boolean0;
    }

    if (is2x2AreaClear(square)) {
      chr.setX(int0);
      chr.setY(int1);
    } else if (boolean0) {
      chr.setX(int0 + 0.5F);
      chr.setY(int1);
      directions = Rand.Next(2) == 0 ? IsoDirections.N : IsoDirections.S;
    } else if (boolean1) {
      chr.setX(int0);
      chr.setY(int1 + 0.5F);
      directions = Rand.Next(2) == 0 ? IsoDirections.W : IsoDirections.E;
    } else if (is1x2AreaClear(square.getAdjacentSquare(IsoDirections.S))) {
      chr.setX(int0 + 0.5F);
      chr.setY(int1 + 0.99F);
      directions = Rand.Next(2) == 0 ? IsoDirections.N : IsoDirections.S;
    } else if (is2x1AreaClear(square.getAdjacentSquare(IsoDirections.E))) {
      chr.setX(int0 + 0.99F);
      chr.setY(int1 + 0.5F);
      directions = Rand.Next(2) == 0 ? IsoDirections.W : IsoDirections.E;
    }

    chr.setDir(directions);
    chr.lx = chr.nx = chr.x;
    chr.ly = chr.ny = chr.y;
    chr.setScriptnx(chr.x);
    chr.setScriptny(chr.y);
  }

  /**
   * Get a random room in the building
   */
  RoomDef getRandomRoom(BuildingDef bDef, int minArea) {
    RoomDef roomDef = bDef.getRooms().get(Rand.Next(0, bDef.getRooms().size()));
    if (minArea > 0 && roomDef.area >= minArea) {
      return roomDef;
    } else {
      int int0 = 0;

      while (int0 <= 20) {
        int0++;
        roomDef = bDef.getRooms().get(Rand.Next(0, bDef.getRooms().size()));
        if (roomDef.area >= minArea) {
          return roomDef;
        }
      }

      return roomDef;
    }
  }

  /**
   * Return the wanted room
   */
  RoomDef getRoom(BuildingDef bDef, const std::string &roomName) {
    for (int int0 = 0; int0 < bDef.rooms.size(); int0++) {
      RoomDef roomDef = bDef.rooms.get(int0);
      if (roomDef.getName().equalsIgnoreCase(roomName)) {
        return roomDef;
      }
    }

    return null;
  }

  /**
   * Get either the living room or kitchen (in this order)
   */
  RoomDef getLivingRoomOrKitchen(BuildingDef bDef) {
    RoomDef roomDef = this.getRoom(bDef, "livingroom");
    if (roomDef == nullptr) {
      roomDef = this.getRoom(bDef, "kitchen");
    }

    return roomDef;
  }

  static bool canSpawnAt(IsoGridSquare square) {
    if (square == nullptr) {
      return false;
    } else {
      return square.HasStairs() ? false
                                : VirtualZombieManager.instance.canSpawnAt(
                                      square.x, square.y, square.z);
    }
  }

  static IsoGridSquare getRandomSpawnSquare(RoomDef roomDef) {
    return roomDef = =
               null ? null
                    : roomDef.getRandomSquare(RandomizedWorldBase::canSpawnAt);
  }

  static IsoGridSquare getRandomSquareForCorpse(RoomDef roomDef) {
    IsoGridSquare square0 =
        roomDef.getRandomSquare(RandomizedWorldBase::is2x2AreaClear);
    IsoGridSquare square1 =
        roomDef.getRandomSquare(RandomizedWorldBase::is2x1or1x2AreaClear);
    if (square0 == nullptr || square1 != nullptr && Rand.Next(4) == 0) {
      square0 = square1;
    }

    return square0;
  }

  BaseVehicle spawnCarOnNearestNav(const std::string &carName,
                                   BuildingDef def) {
    IsoGridSquare square0 = null;
    int int0 = (def.x + def.x2) / 2;
    int int1 = (def.y + def.y2) / 2;

    for (int int2 = int0; int2 < int0 + 20; int2++) {
      IsoGridSquare square1 =
          IsoCell.getInstance().getGridSquare(int2, int1, 0);
      if (square1 != nullptr && "Nav" == square1.getZoneType())) {
          square0 = square1;
          break;
        }
    }

    if (square0 != nullptr) {
      return this.spawnCar(carName, square0);
    } else {
      for (int int3 = int0; int3 > int0 - 20; int3--) {
        IsoGridSquare square2 =
            IsoCell.getInstance().getGridSquare(int3, int1, 0);
        if (square2 != nullptr && "Nav" == square2.getZoneType())) {
            square0 = square2;
            break;
          }
      }

      if (square0 != nullptr) {
        return this.spawnCar(carName, square0);
      } else {
        for (int int4 = int1; int4 < int1 + 20; int4++) {
          IsoGridSquare square3 =
              IsoCell.getInstance().getGridSquare(int0, int4, 0);
          if (square3 != nullptr && "Nav" == square3.getZoneType())) {
              square0 = square3;
              break;
            }
        }

        if (square0 != nullptr) {
          return this.spawnCar(carName, square0);
        } else {
          for (int int5 = int1; int5 > int1 - 20; int5--) {
            IsoGridSquare square4 =
                IsoCell.getInstance().getGridSquare(int0, int5, 0);
            if (square4 != nullptr && "Nav" == square4.getZoneType())) {
                square0 = square4;
                break;
              }
          }

          return square0 != nullptr ? this.spawnCar(carName, square0) : nullptr;
        }
      }
    }
  }

  BaseVehicle spawnCar(const std::string &string, IsoGridSquare square) {
    BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
    vehicle.setScriptName(string);
    vehicle.setX(square.x + 0.5F);
    vehicle.setY(square.y + 0.5F);
    vehicle.setZ(0.0F);
    vehicle.savedRot.setAngleAxis(Rand.Next(0.0F, (float)(Math.PI * 2)), 0.0F,
                                  1.0F, 0.0F);
    vehicle.jniTransform.setRotation(vehicle.savedRot);
    if (IsoChunk.doSpawnedVehiclesInInvalidPosition(vehicle)) {
      vehicle.keySpawned = 1;
      vehicle.setSquare(square);
      vehicle.square.chunk.vehicles.add(vehicle);
      vehicle.chunk = vehicle.square.chunk;
      vehicle.addToWorld();
      VehiclesDB2.instance.addVehicle(vehicle);
    }

    vehicle.setGeneralPartCondition(0.3F, 70.0F);
    return vehicle;
  }

  InventoryItem addItemOnGround(IsoGridSquare square, const std::string &type) {
    return square != nullptr && !StringUtils.isNullOrWhitespace(type)
               ? square.AddWorldInventoryItem(type, Rand.Next(0.2F, 0.8F),
                                              Rand.Next(0.2F, 0.8F), 0.0F)
               : nullptr;
  }

  InventoryItem addItemOnGround(IsoGridSquare square, InventoryItem item) {
    return square != nullptr && item != nullptr
               ? square.AddWorldInventoryItem(item, Rand.Next(0.2F, 0.8F),
                                              Rand.Next(0.2F, 0.8F), 0.0F)
               : nullptr;
  }

  void addRandomItemsOnGround(RoomDef room, const std::string &type,
                              int count) {
    for (int int0 = 0; int0 < count; int0++) {
      IsoGridSquare square = getRandomSpawnSquare(room);
      this.addItemOnGround(square, type);
    }
  }

  void addRandomItemsOnGround(RoomDef room, ArrayList<String> types,
                              int count) {
    for (int int0 = 0; int0 < count; int0++) {
      IsoGridSquare square = getRandomSpawnSquare(room);
      this.addRandomItemOnGround(square, types);
    }
  }

  InventoryItem addRandomItemOnGround(IsoGridSquare square,
                                      ArrayList<String> types) {
    if (square != nullptr && !types.isEmpty()) {
      std::string string = PZArrayUtil.pickRandom(types);
      return this.addItemOnGround(square, string);
    } else {
      return null;
    }
  }

  /**
   * Create and return a weapon, if it's ranged you can ask for some bullets in
   * it
   */
  HandWeapon addWeapon(const std::string &type, bool addRandomBullets) {
    HandWeapon weapon = (HandWeapon)InventoryItemFactory.CreateItem(type);
    if (weapon == nullptr) {
      return null;
    } else {
      if (weapon.isRanged() && addRandomBullets) {
        if (!StringUtils.isNullOrWhitespace(weapon.getMagazineType())) {
          weapon.setContainsClip(true);
        }

        weapon.setCurrentAmmoCount(Rand.Next(
            Math.max(weapon.getMaxAmmo() - 8, 0), weapon.getMaxAmmo() - 2));
      }

      return weapon;
    }
  }

  IsoDeadBody createSkeletonCorpse(RoomDef room) {
    if (room == nullptr) {
      return null;
    } else {
      IsoGridSquare square =
          room.getRandomSquare(RandomizedWorldBase::is2x1or1x2AreaClear);
      if (square == nullptr) {
        return null;
      } else {
        VirtualZombieManager.instance.choices.clear();
        VirtualZombieManager.instance.choices.add(square);
        IsoZombie zombie0 =
            VirtualZombieManager.instance.createRealZombieAlways(Rand.Next(8),
                                                                 false);
        if (zombie0 == nullptr) {
          return null;
        } else {
          ZombieSpawnRecorder.instance.record(zombie0,
                                              this.getClass().getSimpleName());
          alignCorpseToSquare(zombie0, square);
          zombie0.setFakeDead(false);
          zombie0.setHealth(0.0F);
          zombie0.upKillCount = false;
          zombie0.setSkeleton(true);
          zombie0.getHumanVisual().setSkinTextureIndex(Rand.Next(1, 3));
          return new IsoDeadBody(zombie0, true);
        }
      }
    }
  }

  /**
   * Check if the world age is correct for our definition
   */
  bool isTimeValid(bool force) {
    if (this.minimumDays != 0 && this.maximumDays != 0) {
      float float0 = (float)GameTime.getInstance().getWorldAgeHours() / 24.0F;
      float0 += (SandboxOptions.instance.TimeSinceApo.getValue() - 1) * 30;
      return this.minimumDays > 0 && float0 < this.minimumDays
                 ? false
                 : this.maximumDays <= 0 || !(float0 > this.maximumDays);
    } else {
      return true;
    }
  }

  std::string getName() { return this.name; }

  std::string getDebugLine() { return this.debugLine; }

  void setDebugLine(const std::string &_debugLine) {
    this.debugLine = _debugLine;
  }

  int getMaximumDays() { return this.maximumDays; }

  void setMaximumDays(int _maximumDays) { this.maximumDays = _maximumDays; }

  bool isUnique() { return this.unique; }

  void setUnique(bool _unique) { this.unique = _unique; }

  IsoGridSquare getSq(int x, int y, int z) {
    return IsoWorld.instance.getCell().getGridSquare(x, y, z);
  }

  IsoObject addTileObject(int x, int y, int z, const std::string &spriteName) {
    return this.addTileObject(this.getSq(x, y, z), spriteName);
  }

  IsoObject addTileObject(IsoGridSquare sq, const std::string &spriteName) {
    if (sq == nullptr) {
      return null;
    } else {
      IsoObject object = IsoObject.getNew(sq, spriteName, null, false);
      sq.AddTileObject(object);
      MapObjects.newGridSquare(sq);
      MapObjects.loadGridSquare(sq);
      return object;
    }
  }

  IsoObject addTentNorthSouth(int x, int y, int z) {
    this.addTileObject(x, y - 1, z, "camping_01_1");
    return this.addTileObject(x, y, z, "camping_01_0");
  }

  IsoObject addTentWestEast(int x, int y, int z) {
    this.addTileObject(x - 1, y, z, "camping_01_2");
    return this.addTileObject(x, y, z, "camping_01_3");
  }

  BaseVehicle addTrailer(BaseVehicle v, IsoMetaGrid.Zone zone, IsoChunk chunk,
                         const std::string &zoneName,
                         const std::string &vehicleDistrib,
                         const std::string &trailerName) {
    IsoGridSquare square = v.getSquare();
    IsoDirections directions = v.getDir();
    uint8_t byte0 = 0;
    uint8_t byte1 = 0;
    if (directions == IsoDirections.S) {
      byte1 = -3;
    }

    if (directions == IsoDirections.N) {
      byte1 = 3;
    }

    if (directions == IsoDirections.W) {
      byte0 = 3;
    }

    if (directions == IsoDirections.E) {
      byte0 = -3;
    }

    BaseVehicle vehicle = this.addVehicle(
        zone, this.getSq(square.x + byte0, square.y + byte1, square.z), chunk,
        zoneName, trailerName, nullptr, directions, vehicleDistrib);
    if (vehicle != nullptr) {
      v.positionTrailer(vehicle);
    }

    return vehicle;
  }
}
} // namespace randomizedWorld
} // namespace zombie
