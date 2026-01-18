#pragma once
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Contains all car model with their associated skin index
 */
class VehicleType {
public:
public
  final ArrayList<VehicleType.VehicleTypeDefinition> vehiclesDefinition =
      std::make_unique<ArrayList<>>();
  int chanceToSpawnNormal = 80;
  int chanceToSpawnBurnt = 0;
  int spawnRate = 16;
  int chanceOfOverCar = 0;
  bool randomAngle = false;
  float baseVehicleQuality = 1.0F;
  std::string name = "";
  int chanceToSpawnKey = 70;
  int chanceToPartDamage = 0;
  bool isSpecialCar = false;
  bool isBurntCar = false;
  int chanceToSpawnSpecial = 5;
public
  static final HashMap<String, VehicleType> vehicles =
      std::make_unique<HashMap<>>();
public
  static final ArrayList<VehicleType> specialVehicles =
      std::make_unique<ArrayList<>>();

public
  VehicleType(const std::string &_name) { this.name = _name; }

  static void init() {
    initNormal();
    validate(vehicles.values());
    validate(specialVehicles);
  }

  static void validate(Collection<VehicleType> var0) {}

  static void initNormal() {
    bool boolean0 = DebugLog.isEnabled(DebugType.Lua);
    KahluaTableImpl kahluaTableImpl0 =
        (KahluaTableImpl)LuaManager.env.rawget("VehicleZoneDistribution");

    for (Entry entry0 : kahluaTableImpl0.delegate.entrySet()) {
      std::string string0 = entry0.getKey().toString();
      VehicleType vehicleType0 = new VehicleType(string0);
      std::vector arrayList = vehicleType0.vehiclesDefinition;
      KahluaTableImpl kahluaTableImpl1 = (KahluaTableImpl)entry0.getValue();
      KahluaTableImpl kahluaTableImpl2 =
          (KahluaTableImpl)kahluaTableImpl1.rawget("vehicles");

      for (Entry entry1 : kahluaTableImpl2.delegate.entrySet()) {
        std::string string1 = entry1.getKey().toString();
        VehicleScript vehicleScript0 =
            ScriptManager.instance.getVehicle(string1);
        if (vehicleScript0 == nullptr) {
          DebugLog.General.warn("vehicle type \"" + string1 +
                                "\" doesn't exist");
        }

        KahluaTableImpl kahluaTableImpl3 = (KahluaTableImpl)entry1.getValue();
        arrayList.add(new VehicleType.VehicleTypeDefinition(
            string1, kahluaTableImpl3.rawgetInt("index"),
            kahluaTableImpl3.rawgetFloat("spawnChance")));
      }

      float float0 = 0.0F;

      for (int int0 = 0; int0 < arrayList.size(); int0++) {
        float0 += ((VehicleType.VehicleTypeDefinition)arrayList.get(int0))
                      .spawnChance;
      }

      float0 = 100.0F / float0;
      if (boolean0) {
        DebugLog.Lua.println("Vehicle spawn rate:");
      }

      for (int int1 = 0; int1 < arrayList.size(); int1++) {
        ((VehicleType.VehicleTypeDefinition)arrayList.get(int1)).spawnChance *=
            float0;
        if (boolean0) {
          DebugLog.Lua.println(
              string0 + ": " +
              ((VehicleType.VehicleTypeDefinition)arrayList.get(int1))
                  .vehicleType +
              " " +
              ((VehicleType.VehicleTypeDefinition)arrayList.get(int1))
                  .spawnChance +
              "%");
        }
      }

      if (kahluaTableImpl1.delegate.containsKey("chanceToPartDamage")) {
        vehicleType0.chanceToPartDamage =
            kahluaTableImpl1.rawgetInt("chanceToPartDamage");
      }

      if (kahluaTableImpl1.delegate.containsKey("chanceToSpawnNormal")) {
        vehicleType0.chanceToSpawnNormal =
            kahluaTableImpl1.rawgetInt("chanceToSpawnNormal");
      }

      if (kahluaTableImpl1.delegate.containsKey("chanceToSpawnSpecial")) {
        vehicleType0.chanceToSpawnSpecial =
            kahluaTableImpl1.rawgetInt("chanceToSpawnSpecial");
      }

      if (kahluaTableImpl1.delegate.containsKey("specialCar")) {
        vehicleType0.isSpecialCar = kahluaTableImpl1.rawgetBool("specialCar");
      }

      if (kahluaTableImpl1.delegate.containsKey("burntCar")) {
        vehicleType0.isBurntCar = kahluaTableImpl1.rawgetBool("burntCar");
      }

      if (kahluaTableImpl1.delegate.containsKey("baseVehicleQuality")) {
        vehicleType0.baseVehicleQuality =
            kahluaTableImpl1.rawgetFloat("baseVehicleQuality");
      }

      if (kahluaTableImpl1.delegate.containsKey("chanceOfOverCar")) {
        vehicleType0.chanceOfOverCar =
            kahluaTableImpl1.rawgetInt("chanceOfOverCar");
      }

      if (kahluaTableImpl1.delegate.containsKey("randomAngle")) {
        vehicleType0.randomAngle = kahluaTableImpl1.rawgetBool("randomAngle");
      }

      if (kahluaTableImpl1.delegate.containsKey("spawnRate")) {
        vehicleType0.spawnRate = kahluaTableImpl1.rawgetInt("spawnRate");
      }

      if (kahluaTableImpl1.delegate.containsKey("chanceToSpawnKey")) {
        vehicleType0.chanceToSpawnKey =
            kahluaTableImpl1.rawgetInt("chanceToSpawnKey");
      }

      if (kahluaTableImpl1.delegate.containsKey("chanceToSpawnBurnt")) {
        vehicleType0.chanceToSpawnBurnt =
            kahluaTableImpl1.rawgetInt("chanceToSpawnBurnt");
      }

      vehicles.put(string0, vehicleType0);
      if (vehicleType0.isSpecialCar) {
        specialVehicles.add(vehicleType0);
      }
    }

    std::unordered_set hashSet = new HashSet();

    for (VehicleType vehicleType1 : vehicles.values()) {
      for (VehicleType.VehicleTypeDefinition vehicleTypeDefinition :
           vehicleType1.vehiclesDefinition) {
        hashSet.add(vehicleTypeDefinition.vehicleType);
      }
    }

    for (VehicleScript vehicleScript1 :
         ScriptManager.instance.getAllVehicleScripts()) {
      if (!hashSet.contains(vehicleScript1.getFullName())) {
        DebugLog.General.warn("vehicle type \"" + vehicleScript1.getFullName() +
                              "\" isn't in VehicleZoneDistribution");
      }
    }
  }

  static bool hasTypeForZone(const std::string &zoneName) {
    if (vehicles.isEmpty()) {
      init();
    }

    zoneName = zoneName.toLowerCase();
    return vehicles.containsKey(zoneName);
  }

  static VehicleType getRandomVehicleType(const std::string &zoneName) {
    return getRandomVehicleType();
  }

  static VehicleType getRandomVehicleType(const std::string &zoneName,
                                          bool doNormalWhenSpecific) {
    if (vehicles.isEmpty()) {
      init();
    }

    zoneName = zoneName.toLowerCase();
    VehicleType vehicleType = vehicles.get(zoneName);
    if (vehicleType == nullptr) {
      DebugLog.log(zoneName + " Don't exist in VehicleZoneDistribution");
      return null;
    } else if (Rand.Next(100) < vehicleType.chanceToSpawnBurnt) {
      if (Rand.Next(100) < 80) {
        vehicleType = vehicles.get("normalburnt");
      } else {
        vehicleType = vehicles.get("specialburnt");
      }

      return vehicleType;
    } else {
      if (doNormalWhenSpecific && vehicleType.isSpecialCar &&
          Rand.Next(100) < vehicleType.chanceToSpawnNormal) {
        vehicleType = vehicles.get("parkingstall");
      }

      if (!vehicleType.isBurntCar && !vehicleType.isSpecialCar &&
          Rand.Next(100) < vehicleType.chanceToSpawnSpecial) {
        vehicleType = PZArrayUtil.pickRandom(specialVehicles);
      }

      if (vehicleType.isBurntCar) {
        if (Rand.Next(100) < 80) {
          vehicleType = vehicles.get("normalburnt");
        } else {
          vehicleType = vehicles.get("specialburnt");
        }
      }

      return vehicleType;
    }
  }

  static VehicleType getTypeFromName(const std::string &_name) {
    if (vehicles.isEmpty()) {
      init();
    }

    return vehicles.get(_name);
  }

  float getBaseVehicleQuality() { return this.baseVehicleQuality; }

  float getRandomBaseVehicleQuality() {
    return Rand.Next(this.baseVehicleQuality - 0.1F,
                     this.baseVehicleQuality + 0.1F);
  }

  int getChanceToSpawnKey() { return this.chanceToSpawnKey; }

  void setChanceToSpawnKey(int _chanceToSpawnKey) {
    this.chanceToSpawnKey = _chanceToSpawnKey;
  }

  static void Reset() {
    vehicles.clear();
    specialVehicles.clear();
  }

public
  static class VehicleTypeDefinition {
    std::string vehicleType;
    int index = -1;
    float spawnChance = 0.0F;

  public
    VehicleTypeDefinition(const std::string &string, int int0, float float0) {
      this.vehicleType = string;
      this.index = int0;
      this.spawnChance = float0;
    }
  }
}
} // namespace vehicles
} // namespace zombie
