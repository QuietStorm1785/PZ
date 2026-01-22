#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/VehicleType/VehicleTypeDefinition.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class VehicleType {
public:
   public const std::vector<VehicleTypeDefinition> vehiclesDefinition = std::make_unique<std::vector<>>();
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
   public static const std::unordered_map<std::string, VehicleType> vehicles = std::make_unique<std::unordered_map<>>();
   public static const std::vector<VehicleType> specialVehicles = std::make_unique<std::vector<>>();

    public VehicleType(const std::string& var1) {
      this.name = var1;
   }

    static void init() {
      initNormal();
      validate(vehicles.values());
      validate(specialVehicles);
   }

    static void validate(Collection<VehicleType> var0) {
   }

    static void initNormal() {
    bool var0 = DebugLog.isEnabled(DebugType.Lua);
    KahluaTableImpl var1 = (KahluaTableImpl)LuaManager.env.rawget("VehicleZoneDistribution");

      for (Entry var3 : var1.delegate.entrySet()) {
    std::string var4 = var3.getKey();
    VehicleType var5 = std::make_shared<VehicleType>(var4);
    std::vector var6 = var5.vehiclesDefinition;
    KahluaTableImpl var7 = (KahluaTableImpl)var3.getValue();
    KahluaTableImpl var8 = (KahluaTableImpl)var7.rawget("vehicles");

         for (Entry var10 : var8.delegate.entrySet()) {
    std::string var11 = var10.getKey();
    VehicleScript var12 = ScriptManager.instance.getVehicle(var11);
            if (var12 == nullptr) {
               DebugLog.General.warn("vehicle type \"" + var11 + "\" doesn't exist");
            }

    KahluaTableImpl var13 = (KahluaTableImpl)var10.getValue();
            var6.push_back(std::make_shared<VehicleTypeDefinition>(var11, var13.rawgetInt("index"), var13.rawgetFloat("spawnChance")));
         }

    float var21 = 0.0F;

         for (int var23 = 0; var23 < var6.size(); var23++) {
            var21 += ((VehicleTypeDefinition)var6.get(var23)).spawnChance;
         }

         var21 = 100.0F / var21;
         if (var0) {
            DebugLog.Lua.println("Vehicle spawn rate:");
         }

         for (int var24 = 0; var24 < var6.size(); var24++) {
            ((VehicleTypeDefinition)var6.get(var24)).spawnChance *= var21;
            if (var0) {
               DebugLog.Lua
                  .println(
                     var4 + ": " + ((VehicleTypeDefinition)var6.get(var24)).vehicleType + " " + ((VehicleTypeDefinition)var6.get(var24)).spawnChance + "%"
                  );
            }
         }

         if (var7.delegate.containsKey("chanceToPartDamage")) {
            var5.chanceToPartDamage = var7.rawgetInt("chanceToPartDamage");
         }

         if (var7.delegate.containsKey("chanceToSpawnNormal")) {
            var5.chanceToSpawnNormal = var7.rawgetInt("chanceToSpawnNormal");
         }

         if (var7.delegate.containsKey("chanceToSpawnSpecial")) {
            var5.chanceToSpawnSpecial = var7.rawgetInt("chanceToSpawnSpecial");
         }

         if (var7.delegate.containsKey("specialCar")) {
            var5.isSpecialCar = var7.rawgetBool("specialCar");
         }

         if (var7.delegate.containsKey("burntCar")) {
            var5.isBurntCar = var7.rawgetBool("burntCar");
         }

         if (var7.delegate.containsKey("baseVehicleQuality")) {
            var5.baseVehicleQuality = var7.rawgetFloat("baseVehicleQuality");
         }

         if (var7.delegate.containsKey("chanceOfOverCar")) {
            var5.chanceOfOverCar = var7.rawgetInt("chanceOfOverCar");
         }

         if (var7.delegate.containsKey("randomAngle")) {
            var5.randomAngle = var7.rawgetBool("randomAngle");
         }

         if (var7.delegate.containsKey("spawnRate")) {
            var5.spawnRate = var7.rawgetInt("spawnRate");
         }

         if (var7.delegate.containsKey("chanceToSpawnKey")) {
            var5.chanceToSpawnKey = var7.rawgetInt("chanceToSpawnKey");
         }

         if (var7.delegate.containsKey("chanceToSpawnBurnt")) {
            var5.chanceToSpawnBurnt = var7.rawgetInt("chanceToSpawnBurnt");
         }

         vehicles.put(var4, var5);
         if (var5.isSpecialCar) {
            specialVehicles.push_back(var5);
         }
      }

    std::unordered_set var14 = new std::unordered_set();

      for (VehicleType var17 : vehicles.values()) {
         for (VehicleTypeDefinition var20 : var17.vehiclesDefinition) {
            var14.push_back(var20.vehicleType);
         }
      }

      for (VehicleScript var18 : ScriptManager.instance.getAllVehicleScripts()) {
         if (!var14.contains(var18.getFullName())) {
            DebugLog.General.warn("vehicle type \"" + var18.getFullName() + "\" isn't in VehicleZoneDistribution");
         }
      }
   }

    static bool hasTypeForZone(const std::string& var0) {
      if (vehicles.empty()) {
         init();
      }

      var0 = var0.toLowerCase();
      return vehicles.containsKey(var0);
   }

    static VehicleType getRandomVehicleType(const std::string& var0) {
    return getRandomVehicleType();
   }

    static VehicleType getRandomVehicleType(const std::string& var0, bool var1) {
      if (vehicles.empty()) {
         init();
      }

      var0 = var0.toLowerCase();
    VehicleType var2 = vehicles.get(var0);
      if (var2 == nullptr) {
         DebugLog.log(var0 + " Don't exist in VehicleZoneDistribution");
    return nullptr;
      } else if (Rand.Next(100) < var2.chanceToSpawnBurnt) {
         if (Rand.Next(100) < 80) {
            var2 = vehicles.get("normalburnt");
         } else {
            var2 = vehicles.get("specialburnt");
         }

    return var2;
      } else {
         if (var1 && var2.isSpecialCar && Rand.Next(100) < var2.chanceToSpawnNormal) {
            var2 = vehicles.get("parkingstall");
         }

         if (!var2.isBurntCar && !var2.isSpecialCar && Rand.Next(100) < var2.chanceToSpawnSpecial) {
            var2 = (VehicleType)PZArrayUtil.pickRandom(specialVehicles);
         }

         if (var2.isBurntCar) {
            if (Rand.Next(100) < 80) {
               var2 = vehicles.get("normalburnt");
            } else {
               var2 = vehicles.get("specialburnt");
            }
         }

    return var2;
      }
   }

    static VehicleType getTypeFromName(const std::string& var0) {
      if (vehicles.empty()) {
         init();
      }

      return vehicles.get(var0);
   }

    float getBaseVehicleQuality() {
      return this.baseVehicleQuality;
   }

    float getRandomBaseVehicleQuality() {
      return Rand.Next(this.baseVehicleQuality - 0.1F, this.baseVehicleQuality + 0.1F);
   }

    int getChanceToSpawnKey() {
      return this.chanceToSpawnKey;
   }

    void setChanceToSpawnKey(int var1) {
      this.chanceToSpawnKey = var1;
   }

    static void Reset() {
      vehicles.clear();
      specialVehicles.clear();
   }
}
} // namespace vehicles
} // namespace zombie
