#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions/BooleanSandboxOption.h"
#include "zombie/SandboxOptions/DoubleSandboxOption.h"
#include "zombie/SandboxOptions/EnumSandboxOption.h"
#include "zombie/SandboxOptions/IntegerSandboxOption.h"
#include "zombie/SandboxOptions/Map.h"
#include "zombie/SandboxOptions/SandboxOption.h"
#include "zombie/SandboxOptions/StringSandboxOption.h"
#include "zombie/SandboxOptions/ZombieConfig.h"
#include "zombie/SandboxOptions/ZombieLore.h"
#include "zombie/config/ConfigFile.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/SliceY.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerSettingsManager.h"
#include "zombie/sandbox/CustomBooleanSandboxOption.h"
#include "zombie/sandbox/CustomDoubleSandboxOption.h"
#include "zombie/sandbox/CustomEnumSandboxOption.h"
#include "zombie/sandbox/CustomIntegerSandboxOption.h"
#include "zombie/sandbox/CustomSandboxOption.h"
#include "zombie/sandbox/CustomSandboxOptions.h"
#include "zombie/sandbox/CustomStringSandboxOption.h"
#include "zombie/util/Type.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {


class SandboxOptions {
:
    static const SandboxOptions instance = new SandboxOptions();
    int Speed = 3;
    const EnumSandboxOption Zombies;
    const EnumSandboxOption Distribution;
    const EnumSandboxOption DayLength;
    const EnumSandboxOption StartYear;
    const EnumSandboxOption StartMonth;
    const EnumSandboxOption StartDay;
    const EnumSandboxOption StartTime;
    const EnumSandboxOption WaterShut;
    const EnumSandboxOption ElecShut;
    const IntegerSandboxOption WaterShutModifier;
    const IntegerSandboxOption ElecShutModifier;
    const EnumSandboxOption FoodLoot;
    const EnumSandboxOption LiteratureLoot;
    const EnumSandboxOption MedicalLoot;
    const EnumSandboxOption SurvivalGearsLoot;
    const EnumSandboxOption CannedFoodLoot;
    const EnumSandboxOption WeaponLoot;
    const EnumSandboxOption RangedWeaponLoot;
    const EnumSandboxOption AmmoLoot;
    const EnumSandboxOption MechanicsLoot;
    const EnumSandboxOption OtherLoot;
    const EnumSandboxOption Temperature;
    const EnumSandboxOption Rain;
    const EnumSandboxOption ErosionSpeed;
    const IntegerSandboxOption ErosionDays;
    const DoubleSandboxOption XpMultiplier;
    const BooleanSandboxOption XpMultiplierAffectsPassive;
    const EnumSandboxOption Farming;
    const EnumSandboxOption CompostTime;
    const EnumSandboxOption StatsDecrease;
    const EnumSandboxOption NatureAbundance;
    const EnumSandboxOption Alarm;
    const EnumSandboxOption LockedHouses;
    const BooleanSandboxOption StarterKit;
    const BooleanSandboxOption Nutrition;
    const EnumSandboxOption FoodRotSpeed;
    const EnumSandboxOption FridgeFactor;
    const EnumSandboxOption LootRespawn;
    const IntegerSandboxOption SeenHoursPreventLootRespawn;
    const StringSandboxOption WorldItemRemovalList;
    const DoubleSandboxOption HoursForWorldItemRemoval;
    const BooleanSandboxOption ItemRemovalListBlacklistToggle;
    const EnumSandboxOption TimeSinceApo;
    const EnumSandboxOption PlantResilience;
    const EnumSandboxOption PlantAbundance;
    const EnumSandboxOption EndRegen;
    const EnumSandboxOption Helicopter;
    const EnumSandboxOption MetaEvent;
    const EnumSandboxOption SleepingEvent;
    const DoubleSandboxOption GeneratorFuelConsumption;
    const EnumSandboxOption GeneratorSpawning;
    const EnumSandboxOption SurvivorHouseChance;
    const EnumSandboxOption AnnotatedMapChance;
    const IntegerSandboxOption CharacterFreePoints;
    const EnumSandboxOption ConstructionBonusPoints;
    const EnumSandboxOption NightDarkness;
    const EnumSandboxOption NightLength;
    const BooleanSandboxOption BoneFracture;
    const EnumSandboxOption InjurySeverity;
    const DoubleSandboxOption HoursForCorpseRemoval;
    const EnumSandboxOption DecayingCorpseHealthImpact;
    const EnumSandboxOption BloodLevel;
    const EnumSandboxOption ClothingDegradation;
    const BooleanSandboxOption FireSpread;
    const IntegerSandboxOption DaysForRottenFoodRemoval;
    const BooleanSandboxOption AllowExteriorGenerator;
    const EnumSandboxOption MaxFogIntensity;
    const EnumSandboxOption MaxRainFxIntensity;
    const BooleanSandboxOption EnableSnowOnGround;
    const BooleanSandboxOption AttackBlockMovements;
    const EnumSandboxOption VehicleStoryChance;
    const EnumSandboxOption ZoneStoryChance;
    const BooleanSandboxOption AllClothesUnlocked;
    const BooleanSandboxOption EnableTaintedWaterText;
    const BooleanSandboxOption EnableVehicles;
    const EnumSandboxOption CarSpawnRate;
    const DoubleSandboxOption ZombieAttractionMultiplier;
    const BooleanSandboxOption VehicleEasyUse;
    const EnumSandboxOption InitialGas;
    const EnumSandboxOption FuelStationGas;
    const EnumSandboxOption LockedCar;
    const DoubleSandboxOption CarGasConsumption;
    const EnumSandboxOption CarGeneralCondition;
    const EnumSandboxOption CarDamageOnImpact;
    const EnumSandboxOption DamageToPlayerFromHitByACar;
    const BooleanSandboxOption TrafficJam;
    const EnumSandboxOption CarAlarm;
    const BooleanSandboxOption PlayerDamageFromCrash;
    const DoubleSandboxOption SirenShutoffHours;
    const EnumSandboxOption ChanceHasGas;
    const EnumSandboxOption RecentlySurvivorVehicles;
    const BooleanSandboxOption MultiHitZombies;
    const EnumSandboxOption RearVulnerability;
    const EnumSandboxOption EnablePoisoning;
    const EnumSandboxOption MaggotSpawn;
    const DoubleSandboxOption LightBulbLifespan;
   protected ArrayList<SandboxOption> options = std::make_unique<ArrayList<>>();
   protected HashMap<String, SandboxOption> optionByName = std::make_unique<HashMap<>>();
    const std::unordered_map Map = new Map(this);
    const ZombieLore Lore = new ZombieLore(this);
    const ZombieConfig zombieConfig = new ZombieConfig(this);
    const int FIRST_YEAR = 1993;
    const int SANDBOX_VERSION = 5;
   private ArrayList<SandboxOption> m_customOptions = std::make_unique<ArrayList<>>();

     SandboxOptions() {
      this.Zombies = (EnumSandboxOption)this.newEnumOption("Zombies", 6, 4).setTranslation("ZombieCount");
      this.Distribution = (EnumSandboxOption)this.newEnumOption("Distribution", 2, 1).setTranslation("ZombieDistribution");
      this.DayLength = this.newEnumOption("DayLength", 26, 2);
      this.StartYear = this.newEnumOption("StartYear", 100, 1);
      this.StartMonth = this.newEnumOption("StartMonth", 12, 7);
      this.StartDay = this.newEnumOption("StartDay", 31, 23);
      this.StartTime = this.newEnumOption("StartTime", 9, 2);
      this.WaterShut = this.newEnumOption("WaterShut", 8, 2).setValueTranslation("Shutoff");
      this.ElecShut = this.newEnumOption("ElecShut", 8, 2).setValueTranslation("Shutoff");
      this.WaterShutModifier = (IntegerSandboxOption)this.newIntegerOption("WaterShutModifier", -1, Integer.MAX_VALUE, 14).setTranslation("WaterShut");
      this.ElecShutModifier = (IntegerSandboxOption)this.newIntegerOption("ElecShutModifier", -1, Integer.MAX_VALUE, 14).setTranslation("ElecShut");
      this.FoodLoot = (EnumSandboxOption)this.newEnumOption("FoodLoot", 7, 4).setValueTranslation("Rarity").setTranslation("LootFood");
      this.CannedFoodLoot = (EnumSandboxOption)this.newEnumOption("CannedFoodLoot", 7, 4).setValueTranslation("Rarity").setTranslation("LootCannedFood");
      this.LiteratureLoot = (EnumSandboxOption)this.newEnumOption("LiteratureLoot", 7, 4).setValueTranslation("Rarity").setTranslation("LootLiterature");
      this.SurvivalGearsLoot = (EnumSandboxOption)this.newEnumOption("SurvivalGearsLoot", 7, 4)
         .setValueTranslation("Rarity")
         .setTranslation("LootSurvivalGears");
      this.MedicalLoot = (EnumSandboxOption)this.newEnumOption("MedicalLoot", 7, 4).setValueTranslation("Rarity").setTranslation("LootMedical");
      this.WeaponLoot = (EnumSandboxOption)this.newEnumOption("WeaponLoot", 7, 4).setValueTranslation("Rarity").setTranslation("LootWeapon");
      this.RangedWeaponLoot = (EnumSandboxOption)this.newEnumOption("RangedWeaponLoot", 7, 4).setValueTranslation("Rarity").setTranslation("LootRangedWeapon");
      this.AmmoLoot = (EnumSandboxOption)this.newEnumOption("AmmoLoot", 7, 4).setValueTranslation("Rarity").setTranslation("LootAmmo");
      this.MechanicsLoot = (EnumSandboxOption)this.newEnumOption("MechanicsLoot", 7, 4).setValueTranslation("Rarity").setTranslation("LootMechanics");
      this.OtherLoot = (EnumSandboxOption)this.newEnumOption("OtherLoot", 7, 4).setValueTranslation("Rarity").setTranslation("LootOther");
      this.Temperature = (EnumSandboxOption)this.newEnumOption("Temperature", 5, 3).setTranslation("WorldTemperature");
      this.Rain = (EnumSandboxOption)this.newEnumOption("Rain", 5, 3).setTranslation("RainAmount");
      this.ErosionSpeed = this.newEnumOption("ErosionSpeed", 5, 3);
      this.ErosionDays = this.newIntegerOption("ErosionDays", -1, 36500, 0);
      this.XpMultiplier = this.newDoubleOption("XpMultiplier", 0.001, 1000.0, 1.0);
      this.XpMultiplierAffectsPassive = this.newBooleanOption("XpMultiplierAffectsPassive", false);
      this.ZombieAttractionMultiplier = this.newDoubleOption("ZombieAttractionMultiplier", 0.0, 100.0, 1.0);
      this.VehicleEasyUse = this.newBooleanOption("VehicleEasyUse", false);
      this.Farming = (EnumSandboxOption)this.newEnumOption("Farming", 5, 3).setTranslation("FarmingSpeed");
      this.CompostTime = this.newEnumOption("CompostTime", 8, 2);
      this.StatsDecrease = (EnumSandboxOption)this.newEnumOption("StatsDecrease", 5, 3).setTranslation("StatDecrease");
      this.NatureAbundance = (EnumSandboxOption)this.newEnumOption("NatureAbundance", 5, 3).setTranslation("NatureAmount");
      this.Alarm = (EnumSandboxOption)this.newEnumOption("Alarm", 6, 4).setTranslation("HouseAlarmFrequency");
      this.LockedHouses = (EnumSandboxOption)this.newEnumOption("LockedHouses", 6, 4).setTranslation("LockedHouseFrequency");
      this.StarterKit = this.newBooleanOption("StarterKit", false);
      this.Nutrition = this.newBooleanOption("Nutrition", false);
      this.FoodRotSpeed = (EnumSandboxOption)this.newEnumOption("FoodRotSpeed", 5, 3).setTranslation("FoodSpoil");
      this.FridgeFactor = (EnumSandboxOption)this.newEnumOption("FridgeFactor", 5, 3).setTranslation("FridgeEffect");
      this.LootRespawn = this.newEnumOption("LootRespawn", 5, 1).setValueTranslation("Respawn");
      this.SeenHoursPreventLootRespawn = this.newIntegerOption("SeenHoursPreventLootRespawn", 0, Integer.MAX_VALUE, 0);
      this.WorldItemRemovalList = this.newStringOption("WorldItemRemovalList", "Base.Hat,Base.Glasses", -1);
      this.HoursForWorldItemRemoval = this.newDoubleOption("HoursForWorldItemRemoval", 0.0, 2.147483647E9, 24.0);
      this.ItemRemovalListBlacklistToggle = this.newBooleanOption("ItemRemovalListBlacklistToggle", false);
      this.TimeSinceApo = this.newEnumOption("TimeSinceApo", 13, 1);
      this.PlantResilience = this.newEnumOption("PlantResilience", 5, 3);
      this.PlantAbundance = this.newEnumOption("PlantAbundance", 5, 3).setValueTranslation("NatureAmount");
      this.EndRegen = (EnumSandboxOption)this.newEnumOption("EndRegen", 5, 3).setTranslation("EnduranceRegen");
      this.Helicopter = this.newEnumOption("Helicopter", 4, 2).setValueTranslation("HelicopterFreq");
      this.MetaEvent = this.newEnumOption("MetaEvent", 3, 2).setValueTranslation("MetaEventFreq");
      this.SleepingEvent = this.newEnumOption("SleepingEvent", 3, 1).setValueTranslation("MetaEventFreq");
      this.GeneratorSpawning = this.newEnumOption("GeneratorSpawning", 5, 3);
      this.GeneratorFuelConsumption = this.newDoubleOption("GeneratorFuelConsumption", 0.0, 100.0, 1.0);
      this.SurvivorHouseChance = this.newEnumOption("SurvivorHouseChance", 6, 3);
      this.VehicleStoryChance = this.newEnumOption("VehicleStoryChance", 6, 3).setValueTranslation("SurvivorHouseChance");
      this.ZoneStoryChance = this.newEnumOption("ZoneStoryChance", 6, 3).setValueTranslation("SurvivorHouseChance");
      this.AnnotatedMapChance = this.newEnumOption("AnnotatedMapChance", 6, 4);
      this.CharacterFreePoints = this.newIntegerOption("CharacterFreePoints", -100, 100, 0);
      this.ConstructionBonusPoints = this.newEnumOption("ConstructionBonusPoints", 5, 3);
      this.NightDarkness = this.newEnumOption("NightDarkness", 4, 3);
      this.NightLength = this.newEnumOption("NightLength", 5, 3);
      this.InjurySeverity = this.newEnumOption("InjurySeverity", 3, 2);
      this.BoneFracture = this.newBooleanOption("BoneFracture", true);
      this.HoursForCorpseRemoval = this.newDoubleOption("HoursForCorpseRemoval", -1.0, 2.147483647E9, -1.0);
      this.DecayingCorpseHealthImpact = this.newEnumOption("DecayingCorpseHealthImpact", 4, 3);
      this.BloodLevel = this.newEnumOption("BloodLevel", 5, 3);
      this.ClothingDegradation = this.newEnumOption("ClothingDegradation", 4, 3);
      this.FireSpread = this.newBooleanOption("FireSpread", true);
      this.DaysForRottenFoodRemoval = this.newIntegerOption("DaysForRottenFoodRemoval", -1, Integer.MAX_VALUE, -1);
      this.AllowExteriorGenerator = this.newBooleanOption("AllowExteriorGenerator", true);
      this.MaxFogIntensity = this.newEnumOption("MaxFogIntensity", 3, 1);
      this.MaxRainFxIntensity = this.newEnumOption("MaxRainFxIntensity", 3, 1);
      this.EnableSnowOnGround = this.newBooleanOption("EnableSnowOnGround", true);
      this.MultiHitZombies = this.newBooleanOption("MultiHitZombies", false);
      this.RearVulnerability = this.newEnumOption("RearVulnerability", 3, 3);
      this.AttackBlockMovements = this.newBooleanOption("AttackBlockMovements", true);
      this.AllClothesUnlocked = this.newBooleanOption("AllClothesUnlocked", false);
      this.EnableTaintedWaterText = this.newBooleanOption("EnableTaintedWaterText", true);
      this.CarSpawnRate = this.newEnumOption("CarSpawnRate", 5, 4);
      this.ChanceHasGas = this.newEnumOption("ChanceHasGas", 3, 2);
      this.InitialGas = this.newEnumOption("InitialGas", 6, 3);
      this.FuelStationGas = this.newEnumOption("FuelStationGas", 9, 5);
      this.CarGasConsumption = this.newDoubleOption("CarGasConsumption", 0.0, 100.0, 1.0);
      this.LockedCar = this.newEnumOption("LockedCar", 6, 4);
      this.CarGeneralCondition = this.newEnumOption("CarGeneralCondition", 5, 3);
      this.CarDamageOnImpact = this.newEnumOption("CarDamageOnImpact", 5, 3);
      this.DamageToPlayerFromHitByACar = this.newEnumOption("DamageToPlayerFromHitByACar", 5, 1);
      this.TrafficJam = this.newBooleanOption("TrafficJam", true);
      this.CarAlarm = (EnumSandboxOption)this.newEnumOption("CarAlarm", 6, 4).setTranslation("CarAlarmFrequency");
      this.PlayerDamageFromCrash = this.newBooleanOption("PlayerDamageFromCrash", true);
      this.SirenShutoffHours = this.newDoubleOption("SirenShutoffHours", 0.0, 168.0, 0.0);
      this.RecentlySurvivorVehicles = this.newEnumOption("RecentlySurvivorVehicles", 4, 3);
      this.EnableVehicles = this.newBooleanOption("EnableVehicles", true);
      this.EnablePoisoning = this.newEnumOption("EnablePoisoning", 3, 1);
      this.MaggotSpawn = this.newEnumOption("MaggotSpawn", 3, 1);
      this.LightBulbLifespan = this.newDoubleOption("LightBulbLifespan", 0.0, 1000.0, 1.0);
      CustomSandboxOptions.instance.initInstance(this);
      this.loadGameFile("Apocalypse");
      this.setDefaultsToCurrentValues();
   }

    static SandboxOptions getInstance() const {
    return instance;
   }

    void toLua() {
    KahluaTable var1 = (KahluaTable)LuaManager.env.rawget("SandboxVars");

      for (int var2 = 0; var2 < this.options.size(); var2++) {
         this.options.get(var2).toTable(var1);
      }
   }

    void updateFromLua() {
      if (Core.GameMode == "LastStand")) {
         GameTime.instance.multiplierBias = 1.2F;
      }

    KahluaTable var1 = (KahluaTable)LuaManager.env.rawget("SandboxVars");

      for (int var2 = 0; var2 < this.options.size(); var2++) {
         this.options.get(var2).fromTable(var1);
      }

      switch (this.Speed) {
         case 1:
            GameTime.instance.multiplierBias = 0.8F;
            break;
         case 2:
            GameTime.instance.multiplierBias = 0.9F;
            break;
         case 3:
            GameTime.instance.multiplierBias = 1.0F;
            break;
         case 4:
            GameTime.instance.multiplierBias = 1.1F;
            break;
         case 5:
            GameTime.instance.multiplierBias = 1.2F;
      }

      if (this.Zombies.getValue() == 1) {
         VirtualZombieManager.instance.MaxRealZombies = 400;
      }

      if (this.Zombies.getValue() == 2) {
         VirtualZombieManager.instance.MaxRealZombies = 350;
      }

      if (this.Zombies.getValue() == 3) {
         VirtualZombieManager.instance.MaxRealZombies = 300;
      }

      if (this.Zombies.getValue() == 4) {
         VirtualZombieManager.instance.MaxRealZombies = 200;
      }

      if (this.Zombies.getValue() == 5) {
         VirtualZombieManager.instance.MaxRealZombies = 100;
      }

      if (this.Zombies.getValue() == 6) {
         VirtualZombieManager.instance.MaxRealZombies = 0;
      }

      VirtualZombieManager.instance.MaxRealZombies = 1;
      this.applySettings();
   }

    void initSandboxVars() {
    KahluaTable var1 = (KahluaTable)LuaManager.env.rawget("SandboxVars");

      for (int var2 = 0; var2 < this.options.size(); var2++) {
    SandboxOption var3 = this.options.get(var2);
         var3.fromTable(var1);
         var3.toTable(var1);
      }
   }

    int randomWaterShut(int var1) {
      switch (var1) {
         case 2:
            return Rand.Next(0, 30);
         case 3:
            return Rand.Next(0, 60);
         case 4:
            return Rand.Next(0, 180);
         case 5:
            return Rand.Next(0, 360);
         case 6:
            return Rand.Next(0, 1800);
         case 7:
            return Rand.Next(60, 180);
         case 8:
            return Rand.Next(180, 360);
         default:
            return -1;
      }
   }

    int randomElectricityShut(int var1) {
      switch (var1) {
         case 2:
            return Rand.Next(14, 30);
         case 3:
            return Rand.Next(14, 60);
         case 4:
            return Rand.Next(14, 180);
         case 5:
            return Rand.Next(14, 360);
         case 6:
            return Rand.Next(14, 1800);
         case 7:
            return Rand.Next(60, 180);
         case 8:
            return Rand.Next(180, 360);
         default:
            return -1;
      }
   }

    int getTemperatureModifier() const {
      return this.Temperature.getValue();
   }

    int getRainModifier() const {
      return this.Rain.getValue();
   }

    int getErosionSpeed() const {
      return this.ErosionSpeed.getValue();
   }

    int getFoodLootModifier() const {
      return this.FoodLoot.getValue();
   }

    int getWeaponLootModifier() const {
      return this.WeaponLoot.getValue();
   }

    int getOtherLootModifier() const {
      return this.OtherLoot.getValue();
   }

    int getWaterShutModifier() const {
      return this.WaterShutModifier.getValue();
   }

    int getElecShutModifier() const {
      return this.ElecShutModifier.getValue();
   }

    int getTimeSinceApo() const {
      return this.TimeSinceApo.getValue();
   }

    double getEnduranceRegenMultiplier() const {
      switch (this.EndRegen.getValue()) {
         case 1:
            return 1.8;
         case 2:
            return 1.3;
         case 3:
         default:
            return 1.0;
         case 4:
            return 0.7;
         case 5:
            return 0.4;
      }
   }

    double getStatsDecreaseMultiplier() const {
      switch (this.StatsDecrease.getValue()) {
         case 1:
            return 2.0;
         case 2:
            return 1.6;
         case 3:
         default:
            return 1.0;
         case 4:
            return 0.8;
         case 5:
            return 0.65;
      }
   }

    int getDayLengthMinutes() const {
      switch (this.DayLength.getValue()) {
         case 1:
    return 15;
         case 2:
    return 30;
         default:
            return (this.DayLength.getValue() - 2) * 60;
      }
   }

    int getDayLengthMinutesDefault() const {
      switch (this.DayLength.getDefaultValue()) {
         case 1:
    return 15;
         case 2:
    return 30;
         default:
            return (this.DayLength.getDefaultValue() - 2) * 60;
      }
   }

    int getCompostHours() const {
      switch (this.CompostTime.getValue()) {
         case 1:
    return 168;
         case 2:
    return 336;
         case 3:
    return 504;
         case 4:
    return 672;
         case 5:
    return 1008;
         case 6:
    return 1344;
         case 7:
    return 1680;
         case 8:
    return 2016;
         default:
    return 336;
      }
   }

    void applySettings() {
      GameTime.instance.setStartYear(this.getFirstYear() + this.StartYear.getValue() - 1);
      GameTime.instance.setStartMonth(this.StartMonth.getValue() - 1);
      GameTime.instance.setStartDay(this.StartDay.getValue() - 1);
      GameTime.instance.setMinutesPerDay(this.getDayLengthMinutes());
      if (this.StartTime.getValue() == 1) {
         GameTime.instance.setStartTimeOfDay(7.0F);
      } else if (this.StartTime.getValue() == 2) {
         GameTime.instance.setStartTimeOfDay(9.0F);
      } else if (this.StartTime.getValue() == 3) {
         GameTime.instance.setStartTimeOfDay(12.0F);
      } else if (this.StartTime.getValue() == 4) {
         GameTime.instance.setStartTimeOfDay(14.0F);
      } else if (this.StartTime.getValue() == 5) {
         GameTime.instance.setStartTimeOfDay(17.0F);
      } else if (this.StartTime.getValue() == 6) {
         GameTime.instance.setStartTimeOfDay(21.0F);
      } else if (this.StartTime.getValue() == 7) {
         GameTime.instance.setStartTimeOfDay(0.0F);
      } else if (this.StartTime.getValue() == 8) {
         GameTime.instance.setStartTimeOfDay(2.0F);
      } else if (this.StartTime.getValue() == 9) {
         GameTime.instance.setStartTimeOfDay(5.0F);
      }
   }

    void save(ByteBuffer var1) {
      var1.put((byte)83);
      var1.put((byte)65);
      var1.put((byte)78);
      var1.put((byte)68);
      var1.putInt(195);
      var1.putInt(5);
      var1.putInt(this.options.size());

      for (int var2 = 0; var2 < this.options.size(); var2++) {
    SandboxOption var3 = this.options.get(var2);
         GameWindow.WriteStringUTF(var1, var3.asConfigOption().getName());
         GameWindow.WriteStringUTF(var1, var3.asConfigOption().getValueAsString());
      }
   }

    void load(ByteBuffer var1) {
      var1.mark();
    uint8_t var3 = var1.get();
    uint8_t var4 = var1.get();
    uint8_t var5 = var1.get();
    uint8_t var6 = var1.get();
    int var2;
      if (var3 == 83 && var4 == 65 && var5 == 78 && var6 == 68) {
         var2 = var1.getInt();
      } else {
         var2 = 41;
         var1.reset();
      }

      if (var2 >= 88) {
    int var7 = 2;
         if (var2 >= 131) {
            var7 = var1.getInt();
         }

    int var8 = var1.getInt();

         for (int var9 = 0; var9 < var8; var9++) {
    std::string var10 = GameWindow.ReadStringUTF(var1);
    std::string var11 = GameWindow.ReadStringUTF(var1);
            var10 = this.upgradeOptionName(var10, var7);
            var11 = this.upgradeOptionValue(var10, var11, var7);
    SandboxOption var12 = this.optionByName.get(var10);
            if (var12 == nullptr) {
               DebugLog.log("ERROR unknown SandboxOption \"" + var10 + "\"");
            } else {
               var12.asConfigOption().parse(var11);
            }
         }

         if (var2 < 157) {
            instance.CannedFoodLoot.setValue(instance.FoodLoot.getValue());
            instance.AmmoLoot.setValue(instance.WeaponLoot.getValue());
            instance.RangedWeaponLoot.setValue(instance.WeaponLoot.getValue());
            instance.MedicalLoot.setValue(instance.OtherLoot.getValue());
            instance.LiteratureLoot.setValue(instance.OtherLoot.getValue());
            instance.SurvivalGearsLoot.setValue(instance.OtherLoot.getValue());
            instance.MechanicsLoot.setValue(instance.OtherLoot.getValue());
         }
      }
   }

    int getFirstYear() const {
    return 1993;
   }

   private static String[] parseName(String var0) {
      String[] var1 = new String[]{nullptr, var0};
      if (var0.contains(".")) {
         String[] var2 = var0.split("\\.");
         if (var2.length == 2) {
            var1[0] = var2[0];
            var1[1] = var2[1];
         }
      }

    return var1;
   }

    BooleanSandboxOption newBooleanOption(const std::string& var1, bool var2) {
      return new BooleanSandboxOption(this, var1, var2);
   }

    DoubleSandboxOption newDoubleOption(const std::string& var1, double var2, double var4, double var6) {
      return new DoubleSandboxOption(this, var1, var2, var4, var6);
   }

    EnumSandboxOption newEnumOption(const std::string& var1, int var2, int var3) {
      return new EnumSandboxOption(this, var1, var2, var3);
   }

    IntegerSandboxOption newIntegerOption(const std::string& var1, int var2, int var3, int var4) {
      return new IntegerSandboxOption(this, var1, var2, var3, var4);
   }

    StringSandboxOption newStringOption(const std::string& var1, const std::string& var2, int var3) {
      return new StringSandboxOption(this, var1, var2, var3);
   }

    SandboxOptions addOption(SandboxOption var1) {
      this.options.add(var1);
      this.optionByName.put(var1.asConfigOption().getName(), var1);
    return this;
   }

    int getNumOptions() const {
      return this.options.size();
   }

    SandboxOption getOptionByIndex(int var1) {
      return this.options.get(var1);
   }

    SandboxOption getOptionByName(const std::string& var1) {
      return this.optionByName.get(var1);
   }

    void set(const std::string& var1, void* var2) {
      if (var1 != nullptr && var2 != nullptr) {
    SandboxOption var3 = this.optionByName.get(var1);
         if (var3 == nullptr) {
            throw IllegalArgumentException("unknown SandboxOption \"" + var1 + "\"");
         } else {
            var3.asConfigOption().setValueFromObject(var2);
         }
      } else {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    void copyValuesFrom(SandboxOptions var1) {
      if (var1 == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         for (int var2 = 0; var2 < this.options.size(); var2++) {
            this.options.get(var2).asConfigOption().setValueFromObject(var1.options.get(var2).asConfigOption().getValueAsObject());
         }
      }
   }

    void resetToDefault() {
      for (int var1 = 0; var1 < this.options.size(); var1++) {
         this.options.get(var1).asConfigOption().resetToDefault();
      }
   }

    void setDefaultsToCurrentValues() {
      for (int var1 = 0; var1 < this.options.size(); var1++) {
         this.options.get(var1).asConfigOption().setDefaultToCurrentValue();
      }
   }

    SandboxOptions newCopy() {
    SandboxOptions var1 = new SandboxOptions();
      var1.copyValuesFrom(this);
    return var1;
   }

    static bool isValidPresetName(const std::string& var0) {
      return var0 == nullptr || var0.isEmpty()
         ? false
         : !var0.contains("/") && !var0.contains("\\") && !var0.contains(":") && !var0.contains(";") && !var0.contains("\"") && !var0.contains(".");
   }

    bool readTextFile(const std::string& var1, bool var2) {
    ConfigFile var3 = new ConfigFile();
      if (!var3.read(var1)) {
    return false;
      } else {
    int var4 = var3.getVersion();
    std::unordered_set var5 = nullptr;
         if (var2 && var4 == 1) {
            var5 = std::make_unique<HashSet>();

            for (int var6 = 0; var6 < this.options.size(); var6++) {
               if ("ZombieLore" == this.options.get(var6).getTableName())) {
                  var5.add(this.options.get(var6).getShortName());
               }
            }
         }

         for (int var11 = 0; var11 < var3.getOptions().size(); var11++) {
    ConfigOption var7 = (ConfigOption)var3.getOptions().get(var11);
    std::string var8 = var7.getName();
    std::string var9 = var7.getValueAsString();
            if (var5 != nullptr && var5.contains(var8)) {
               var8 = "ZombieLore." + var8;
            }

            if (var2 && var4 == 1) {
               if ("WaterShutModifier" == var8)) {
                  var8 = "WaterShut";
               } else if ("ElecShutModifier" == var8)) {
                  var8 = "ElecShut";
               }
            }

            var8 = this.upgradeOptionName(var8, var4);
            var9 = this.upgradeOptionValue(var8, var9, var4);
    SandboxOption var10 = this.optionByName.get(var8);
            if (var10 != nullptr) {
               var10.asConfigOption().parse(var9);
            }
         }

    return true;
      }
   }

    bool writeTextFile(const std::string& var1, int var2) {
    ConfigFile var3 = new ConfigFile();
    std::vector var4 = new ArrayList();

      for (SandboxOption var6 : this.options) {
         var4.add(var6.asConfigOption());
      }

      return var3.write(var1, var2, var4);
   }

    bool loadServerTextFile(const std::string& var1) {
      return this.readTextFile(ServerSettingsManager.instance.getNameInSettingsFolder(var1 + "_sandbox.ini"), false);
   }

    bool loadServerLuaFile(const std::string& var1) {
    bool var2 = this.readLuaFile(ServerSettingsManager.instance.getNameInSettingsFolder(var1 + "_SandboxVars.lua"));
      if (this.Lore.Speed.getValue() == 1) {
         this.Lore.Speed.setValue(2);
      }

    return var2;
   }

    bool saveServerLuaFile(const std::string& var1) {
      return this.writeLuaFile(ServerSettingsManager.instance.getNameInSettingsFolder(var1 + "_SandboxVars.lua"), false);
   }

    bool loadPresetFile(const std::string& var1) {
      return this.readTextFile(LuaManager.getSandboxCacheDir() + File.separator + var1 + ".cfg", true);
   }

    bool savePresetFile(const std::string& var1) {
      return !isValidPresetName(var1) ? false : this.writeTextFile(LuaManager.getSandboxCacheDir() + File.separator + var1 + ".cfg", 5);
   }

    bool loadGameFile(const std::string& var1) {
    File var2 = ZomboidFileSystem.instance.getMediaFile("lua/shared/Sandbox/" + var1 + ".lua");
      if (!var2.exists()) {
         throw RuntimeException("media/lua/shared/Sandbox/" + var1 + ".lua not found");
      } else {
         try {
            LuaManager.loaded.remove(var2.getAbsolutePath().replace("\\", "/"));
    void* var3 = LuaManager.RunLua(var2.getAbsolutePath());
            if (!(var3 instanceof KahluaTable)) {
               throw RuntimeException(var2.getName() + " must return a SandboxVars table");
            } else {
               for (int var4 = 0; var4 < this.options.size(); var4++) {
                  this.options.get(var4).fromTable((KahluaTable)var3);
               }

    return true;
            }
         } catch (Exception var5) {
            ExceptionLogger.logException(var5);
    return false;
         }
      }
   }

    bool saveGameFile(const std::string& var1) {
      return !Core.bDebug ? false : this.writeLuaFile("media/lua/shared/Sandbox/" + var1 + ".lua", true);
   }

    void saveCurrentGameBinFile() {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_sand.bin");

      try (
    FileOutputStream var2 = new FileOutputStream(var1);
    BufferedOutputStream var3 = new BufferedOutputStream(var2);
      ) {
         synchronized (SliceY.SliceBufferLock) {
            SliceY.SliceBuffer.clear();
            this.save(SliceY.SliceBuffer);
            var3.write(SliceY.SliceBuffer.array(), 0, SliceY.SliceBuffer.position());
         }
      } catch (Exception var11) {
         ExceptionLogger.logException(var11);
      }
   }

    void handleOldZombiesFile1() {
      if (!GameServer.bServer) {
    std::string var1 = ZomboidFileSystem.instance.getFileNameInCurrentSave("zombies.ini");
    ConfigFile var2 = new ConfigFile();
         if (var2.read(var1)) {
            for (int var3 = 0; var3 < var2.getOptions().size(); var3++) {
    ConfigOption var4 = (ConfigOption)var2.getOptions().get(var3);
    SandboxOption var5 = this.optionByName.get("ZombieConfig." + var4.getName());
               if (var5 != nullptr) {
                  var5.asConfigOption().parse(var4.getValueAsString());
               }
            }
         }
      }
   }

    void handleOldZombiesFile2() {
      if (!GameServer.bServer) {
    std::string var1 = ZomboidFileSystem.instance.getFileNameInCurrentSave("zombies.ini");
    File var2 = new File(var1);
         if (var2.exists()) {
            try {
               DebugLog.log("deleting " + var2.getAbsolutePath());
               var2.delete();
               this.saveCurrentGameBinFile();
            } catch (Exception var4) {
               ExceptionLogger.logException(var4);
            }
         }
      }
   }

    void handleOldServerZombiesFile() {
      if (GameServer.bServer) {
         if (this.loadServerZombiesFile(GameServer.ServerName)) {
    std::string var1 = ServerSettingsManager.instance.getNameInSettingsFolder(GameServer.ServerName + "_zombies.ini");

            try {
    File var2 = new File(var1);
               DebugLog.log("deleting " + var2.getAbsolutePath());
               var2.delete();
               this.saveServerLuaFile(GameServer.ServerName);
            } catch (Exception var3) {
               ExceptionLogger.logException(var3);
            }
         }
      }
   }

    bool loadServerZombiesFile(const std::string& var1) {
    std::string var2 = ServerSettingsManager.instance.getNameInSettingsFolder(var1 + "_zombies.ini");
    ConfigFile var3 = new ConfigFile();
      if (var3.read(var2)) {
         for (int var4 = 0; var4 < var3.getOptions().size(); var4++) {
    ConfigOption var5 = (ConfigOption)var3.getOptions().get(var4);
    SandboxOption var6 = this.optionByName.get("ZombieConfig." + var5.getName());
            if (var6 != nullptr) {
               var6.asConfigOption().parse(var5.getValueAsString());
            }
         }

    return true;
      } else {
    return false;
      }
   }

    bool readLuaFile(const std::string& var1) {
    File var2 = new File(var1).getAbsoluteFile();
      if (!var2.exists()) {
    return false;
      } else {
    void* var3 = LuaManager.env.rawget("SandboxVars");
    KahluaTable var4 = nullptr;
         if (var3 instanceof KahluaTable) {
            var4 = (KahluaTable)var3;
         }

         LuaManager.env.rawset("SandboxVars", nullptr);

    bool var7;
         try {
            LuaManager.loaded.remove(var2.getAbsolutePath().replace("\\", "/"));
    void* var5 = LuaManager.RunLua(var2.getAbsolutePath());
    void* var16 = LuaManager.env.rawget("SandboxVars");
            if (var16 != nullptr) {
               if (var16 instanceof KahluaTable var17) {
    int var8 = 0;
    void* var9 = var17.rawget("VERSION");
                  if (var9 != nullptr) {
                     if (var9 instanceof Double) {
                        var8 = ((Double)var9).intValue();
                     } else {
                        DebugLog.log("ERROR: VERSION=\"" + var9 + "\" in " + var1);
                     }

                     var17.rawset("VERSION", nullptr);
                  }

    KahluaTable var18 = this.upgradeLuaTable("", var17, var8);

                  for (int var10 = 0; var10 < this.options.size(); var10++) {
                     this.options.get(var10).fromTable(var18);
                  }
               }

    return true;
            }

            var7 = false;
         } catch (Exception var14) {
            ExceptionLogger.logException(var14);
    return false;
         } finally {
            if (var4 != nullptr) {
               LuaManager.env.rawset("SandboxVars", var4);
            }
         }

    return var7;
      }
   }

    bool writeLuaFile(const std::string& var1, bool var2) {
    File var3 = new File(var1).getAbsoluteFile();
      DebugLog.log("writing " + var1);

      try {
         try (FileWriter var4 = new FileWriter(var3)) {
    std::unordered_map var5 = new HashMap();
    std::vector var6 = new ArrayList();
            var5.put("", std::make_unique<ArrayList>());

            for (SandboxOption var8 : this.options) {
               if (var8.getTableName() == nullptr) {
                  ((ArrayList)var5.get("")).add(var8);
               } else {
                  if (var5.get(var8.getTableName()) == nullptr) {
                     var5.put(var8.getTableName(), std::make_unique<ArrayList>());
                     var6.add(var8.getTableName());
                  }

                  ((ArrayList)var5.get(var8.getTableName())).add(var8);
               }
            }

    std::string var20 = System.lineSeparator();
            if (var2) {
               var4.write("return {" + var20);
            } else {
               var4.write("SandboxVars = {" + var20);
            }

            var4.write("    VERSION = 5," + var20);

            for (SandboxOption var9 : (ArrayList)var5.get("")) {
               if (!var2) {
    std::string var10 = var9.asConfigOption().getTooltip();
                  if (var10 != nullptr) {
                     var10 = var10.replace("\\n", " ").replace("\\\"", "\"");
                     var10 = var10.replaceAll("\n", var20 + "    -- ");
                     var4.write("    -- " + var10 + var20);
                  }

    EnumSandboxOption var11 = (EnumSandboxOption)Type.tryCastTo(var9, EnumSandboxOption.class);
                  if (var11 != nullptr) {
                     for (int var12 = 1; var12 < var11.getNumValues(); var12++) {
                        try {
    std::string var13 = var11.getValueTranslationByIndexOrNull(var12);
                           if (var13 != nullptr) {
                              var4.write("    -- " + var12 + " = " + var13.replace("\\\"", "\"") + var20);
                           }
                        } catch (Exception var17) {
                           ExceptionLogger.logException(var17);
                        }
                     }
                  }
               }

               var4.write("    " + var9.asConfigOption().getName() + " = " + var9.asConfigOption().getValueAsLuaString() + "," + var20);
            }

    for (auto& var23 : var6)               var4.write("    " + var23 + " = {" + var20);

               for (SandboxOption var27 : (ArrayList)var5.get(var23)) {
                  if (!var2) {
    std::string var28 = var27.asConfigOption().getTooltip();
                     if (var28 != nullptr) {
                        var28 = var28.replace("\\n", " ").replace("\\\"", "\"");
                        var28 = var28.replaceAll("\n", var20 + "        -- ");
                        var4.write("        -- " + var28 + var20);
                     }

                     if (var27 instanceof EnumSandboxOption) {
                        for (int var31 = 1; var31 < ((EnumSandboxOption)var27).getNumValues(); var31++) {
                           try {
    std::string var14 = ((EnumSandboxOption)var27).getValueTranslationByIndexOrNull(var31);
                              if (var14 != nullptr) {
                                 var4.write("        -- " + var31 + " = " + var14 + var20);
                              }
                           } catch (Exception var16) {
                              ExceptionLogger.logException(var16);
                           }
                        }
                     }
                  }

                  var4.write("        " + var27.getShortName() + " = " + var27.asConfigOption().getValueAsLuaString() + "," + var20);
               }

               var4.write("    }," + var20);
            }

            var4.write("}" + var20);
         }

    return true;
      } catch (Exception var19) {
         ExceptionLogger.logException(var19);
    return false;
      }
   }

    void load() {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_sand.bin");

      try {
         try (
    FileInputStream var2 = new FileInputStream(var1);
    BufferedInputStream var3 = new BufferedInputStream(var2);
         ) {
            synchronized (SliceY.SliceBufferLock) {
               SliceY.SliceBuffer.clear();
    int var5 = var3.read(SliceY.SliceBuffer.array());
               SliceY.SliceBuffer.limit(var5);
               this.load(SliceY.SliceBuffer);
               this.handleOldZombiesFile1();
               this.applySettings();
               this.toLua();
            }
         }

         return;
      } catch (FileNotFoundException var12) {
      } catch (Exception var13) {
         ExceptionLogger.logException(var13);
      }

      this.resetToDefault();
      this.updateFromLua();
   }

    void loadCurrentGameBinFile() {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_sand.bin");

      try (
    FileInputStream var2 = new FileInputStream(var1);
    BufferedInputStream var3 = new BufferedInputStream(var2);
      ) {
         synchronized (SliceY.SliceBufferLock) {
            SliceY.SliceBuffer.clear();
    int var5 = var3.read(SliceY.SliceBuffer.array());
            SliceY.SliceBuffer.limit(var5);
            this.load(SliceY.SliceBuffer);
         }

         this.toLua();
      } catch (Exception var12) {
         ExceptionLogger.logException(var12);
      }
   }

    std::string upgradeOptionName(const std::string& var1, int var2) {
    return var1;
   }

    std::string upgradeOptionValue(const std::string& var1, const std::string& var2, int var3) {
      if (var3 < 3 && "DayLength" == var1)) {
         this.DayLength.parse(var2);
         if (this.DayLength.getValue() == 8) {
            this.DayLength.setValue(14);
         } else if (this.DayLength.getValue() == 9) {
            this.DayLength.setValue(26);
         }

         var2 = this.DayLength.getValueAsString();
      }

      if (var3 < 4 && "CarSpawnRate" == var1)) {
         try {
    int var4 = (int)Double.parseDouble(var2);
            if (var4 > 1) {
               var2 = Integer.toString(var4 + 1);
            }
         } catch (NumberFormatException var8) {
            var8.printStackTrace();
         }
      }

      if (var3 < 5) {
         if ("FoodLoot" == var1)
            || "CannedFoodLoot" == var1)
            || "LiteratureLoot" == var1)
            || "SurvivalGearsLoot" == var1)
            || "MedicalLoot" == var1)
            || "WeaponLoot" == var1)
            || "RangedWeaponLoot" == var1)
            || "AmmoLoot" == var1)
            || "MechanicsLoot" == var1)
            || "OtherLoot" == var1)) {
            try {
    int var9 = (int)Double.parseDouble(var2);
               if (var9 > 0) {
                  var2 = Integer.toString(var9 + 2);
               }
            } catch (NumberFormatException var7) {
               var7.printStackTrace();
            }
         }

         if ("FuelStationGas" == var1)) {
            try {
    int var10 = (int)Double.parseDouble(var2);
               if (var10 > 1) {
                  var2 = Integer.toString(var10 + 1);
               }
            } catch (NumberFormatException var6) {
               var6.printStackTrace();
            }
         }

         if ("RecentlySurvivorVehicles" == var1)) {
            try {
    int var11 = (int)Double.parseDouble(var2);
               if (var11 > 0) {
                  var2 = Integer.toString(var11 + 1);
               }
            } catch (NumberFormatException var5) {
               var5.printStackTrace();
            }
         }
      }

    return var2;
   }

    KahluaTable upgradeLuaTable(const std::string& var1, KahluaTable var2, int var3) {
    KahluaTable var4 = LuaManager.platform.newTable();
    KahluaTableIterator var5 = var2.iterator();

      while (var5.advance()) {
         if (!(var5.getKey() instanceof String)) {
            throw IllegalStateException("expected a String key");
         }

         if (var5.getValue() instanceof KahluaTable) {
    KahluaTable var6 = this.upgradeLuaTable(var1 + var5.getKey() + ".", (KahluaTable)var5.getValue(), var3);
            var4.rawset(var5.getKey(), var6);
         } else {
    std::string var8 = this.upgradeOptionName(var1 + var5.getKey(), var3);
    std::string var7 = this.upgradeOptionValue(var8, var5.getValue().toString(), var3);
            var4.rawset(var8.replace((CharSequence)var1, ""), var7);
         }
      }

    return var4;
   }

    void sendToServer() {
      if (GameClient.bClient) {
         GameClient.instance.sendSandboxOptionsToServer(this);
      }
   }

    void newCustomOption(CustomSandboxOption var1) {
    CustomBooleanSandboxOption var2 = (CustomBooleanSandboxOption)Type.tryCastTo(var1, CustomBooleanSandboxOption.class);
      if (var2 != nullptr) {
         this.addCustomOption(new BooleanSandboxOption(this, var2.m_id, var2.defaultValue), var1);
      } else {
    CustomDoubleSandboxOption var3 = (CustomDoubleSandboxOption)Type.tryCastTo(var1, CustomDoubleSandboxOption.class);
         if (var3 != nullptr) {
            this.addCustomOption(new DoubleSandboxOption(this, var3.m_id, var3.min, var3.max, var3.defaultValue), var1);
         } else {
    CustomEnumSandboxOption var4 = (CustomEnumSandboxOption)Type.tryCastTo(var1, CustomEnumSandboxOption.class);
            if (var4 != nullptr) {
    EnumSandboxOption var7 = new EnumSandboxOption(this, var4.m_id, var4.numValues, var4.defaultValue);
               if (var4.m_valueTranslation != nullptr) {
                  var7.setValueTranslation(var4.m_valueTranslation);
               }

               this.addCustomOption(var7, var1);
            } else {
    CustomIntegerSandboxOption var5 = (CustomIntegerSandboxOption)Type.tryCastTo(var1, CustomIntegerSandboxOption.class);
               if (var5 != nullptr) {
                  this.addCustomOption(new IntegerSandboxOption(this, var5.m_id, var5.min, var5.max, var5.defaultValue), var1);
               } else {
    CustomStringSandboxOption var6 = (CustomStringSandboxOption)Type.tryCastTo(var1, CustomStringSandboxOption.class);
                  if (var6 != nullptr) {
                     this.addCustomOption(new StringSandboxOption(this, var6.m_id, var6.defaultValue, -1), var1);
                  } else {
                     throw IllegalArgumentException("unhandled CustomSandboxOption " + var1);
                  }
               }
            }
         }
      }
   }

    void addCustomOption(SandboxOption var1, CustomSandboxOption var2) {
      var1.setCustom();
      if (var2.m_page != nullptr) {
         var1.setPageName(var2.m_page);
      }

      if (var2.m_translation != nullptr) {
         var1.setTranslation(var2.m_translation);
      }

      this.m_customOptions.add(var1);
   }

    void removeCustomOptions() {
      this.options.removeAll(this.m_customOptions);

      for (SandboxOption var2 : this.m_customOptions) {
         this.optionByName.remove(var2.asConfigOption().getName());
      }

      this.m_customOptions.clear();
   }

    static void Reset() {
      instance.removeCustomOptions();
   }

    bool getAllClothesUnlocked() const {
      return this.AllClothesUnlocked.getValue();
   }
}
} // namespace zombie
