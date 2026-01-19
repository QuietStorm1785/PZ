#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/debug/DebugLog.h"

namespace zombie {


class ZomboidGlobals {
public:
    static double RunningEnduranceReduce = 0.0;
    static double SprintingEnduranceReduce = 0.0;
    static double ImobileEnduranceReduce = 0.0;
    static double SittingEnduranceMultiplier = 5.0;
    static double ThirstIncrease = 0.0;
    static double ThirstSleepingIncrease = 0.0;
    static double ThirstLevelToAutoDrink = 0.0;
    static double ThirstLevelReductionOnAutoDrink = 0.0;
    static double HungerIncrease = 0.0;
    static double HungerIncreaseWhenWellFed = 0.0;
    static double HungerIncreaseWhileAsleep = 0.0;
    static double HungerIncreaseWhenExercise = 0.0;
    static double FatigueIncrease = 0.0;
    static double StressReduction = 0.0;
    static double BoredomIncreaseRate = 0.0;
    static double BoredomDecreaseRate = 0.0;
    static double UnhappinessIncrease = 0.0;
    static double StressFromSoundsMultiplier = 0.0;
    static double StressFromBiteOrScratch = 0.0;
    static double StressFromHemophobic = 0.0;
    static double AngerDecrease = 0.0;
    static double BroodingAngerDecreaseMultiplier = 0.0;
    static double SleepFatigueReduction = 0.0;
    static double WetnessIncrease = 0.0;
    static double WetnessDecrease = 0.0;
    static double CatchAColdIncreaseRate = 0.0;
    static double CatchAColdDecreaseRate = 0.0;
    static double PoisonLevelDecrease = 0.0;
    static double PoisonHealthReduction = 0.0;
    static double FoodSicknessDecrease = 0.0;

    static void Load() {
    KahluaTable var0 = static_cast<KahluaTable>(LuaManager).env.rawget("ZomboidGlobals");
      SprintingEnduranceReduce = static_cast<Double>(var0).rawget("SprintingEnduranceReduce");
      RunningEnduranceReduce = static_cast<Double>(var0).rawget("RunningEnduranceReduce");
      ImobileEnduranceReduce = static_cast<Double>(var0).rawget("ImobileEnduranceIncrease");
      ThirstIncrease = static_cast<Double>(var0).rawget("ThirstIncrease");
      ThirstSleepingIncrease = static_cast<Double>(var0).rawget("ThirstSleepingIncrease");
      ThirstLevelToAutoDrink = static_cast<Double>(var0).rawget("ThirstLevelToAutoDrink");
      ThirstLevelReductionOnAutoDrink = static_cast<Double>(var0).rawget("ThirstLevelReductionOnAutoDrink");
      HungerIncrease = static_cast<Double>(var0).rawget("HungerIncrease");
      HungerIncreaseWhenWellFed = static_cast<Double>(var0).rawget("HungerIncreaseWhenWellFed");
      HungerIncreaseWhileAsleep = static_cast<Double>(var0).rawget("HungerIncreaseWhileAsleep");
      HungerIncreaseWhenExercise = static_cast<Double>(var0).rawget("HungerIncreaseWhenExercise");
      FatigueIncrease = static_cast<Double>(var0).rawget("FatigueIncrease");
      StressReduction = static_cast<Double>(var0).rawget("StressDecrease");
      BoredomIncreaseRate = static_cast<Double>(var0).rawget("BoredomIncrease");
      BoredomDecreaseRate = static_cast<Double>(var0).rawget("BoredomDecrease");
      UnhappinessIncrease = static_cast<Double>(var0).rawget("UnhappinessIncrease");
      StressFromSoundsMultiplier = static_cast<Double>(var0).rawget("StressFromSoundsMultiplier");
      StressFromBiteOrScratch = static_cast<Double>(var0).rawget("StressFromBiteOrScratch");
      StressFromHemophobic = static_cast<Double>(var0).rawget("StressFromHemophobic");
      AngerDecrease = static_cast<Double>(var0).rawget("AngerDecrease");
      BroodingAngerDecreaseMultiplier = static_cast<Double>(var0).rawget("BroodingAngerDecreaseMultiplier");
      SleepFatigueReduction = static_cast<Double>(var0).rawget("SleepFatigueReduction");
      WetnessIncrease = static_cast<Double>(var0).rawget("WetnessIncrease");
      WetnessDecrease = static_cast<Double>(var0).rawget("WetnessDecrease");
      CatchAColdIncreaseRate = static_cast<Double>(var0).rawget("CatchAColdIncreaseRate");
      CatchAColdDecreaseRate = static_cast<Double>(var0).rawget("CatchAColdDecreaseRate");
      PoisonLevelDecrease = static_cast<Double>(var0).rawget("PoisonLevelDecrease");
      PoisonHealthReduction = static_cast<Double>(var0).rawget("PoisonHealthReduction");
      FoodSicknessDecrease = static_cast<Double>(var0).rawget("FoodSicknessDecrease");
   }

    static void toLua() {
    KahluaTable var0 = static_cast<KahluaTable>(LuaManager).env.rawget("ZomboidGlobals");
      if (var0 == nullptr) {
         DebugLog.log("ERROR: ZomboidGlobals table undefined in Lua");
      } else {
    double var1 = 1.0;
         if (SandboxOptions.instance.getFoodLootModifier() == 1) {
            var1 = 0.0;
         } else if (SandboxOptions.instance.getFoodLootModifier() == 2) {
            var1 = 0.05;
         } else if (SandboxOptions.instance.getFoodLootModifier() == 3) {
            var1 = 0.2;
         } else if (SandboxOptions.instance.getFoodLootModifier() == 4) {
            var1 = 0.6;
         } else if (SandboxOptions.instance.getFoodLootModifier() == 5) {
            var1 = 1.0;
         } else if (SandboxOptions.instance.getFoodLootModifier() == 6) {
            var1 = 2.0;
         } else if (SandboxOptions.instance.getFoodLootModifier() == 7) {
            var1 = 4.0;
         }

         var0.rawset("FoodLootModifier", var1);
    double var3 = 1.0;
         if (SandboxOptions.instance.getWeaponLootModifier() == 1) {
            var3 = 0.0;
         } else if (SandboxOptions.instance.getWeaponLootModifier() == 2) {
            var3 = 0.05;
         } else if (SandboxOptions.instance.getWeaponLootModifier() == 3) {
            var3 = 0.2;
         } else if (SandboxOptions.instance.getWeaponLootModifier() == 4) {
            var3 = 0.6;
         } else if (SandboxOptions.instance.getWeaponLootModifier() == 5) {
            var3 = 1.0;
         } else if (SandboxOptions.instance.getWeaponLootModifier() == 6) {
            var3 = 2.0;
         } else if (SandboxOptions.instance.getWeaponLootModifier() == 7) {
            var3 = 4.0;
         }

         var0.rawset("WeaponLootModifier", var3);
    double var5 = 1.0;
         if (SandboxOptions.instance.getOtherLootModifier() == 1) {
            var5 = 0.0;
         } else if (SandboxOptions.instance.getOtherLootModifier() == 2) {
            var5 = 0.05;
         } else if (SandboxOptions.instance.getOtherLootModifier() == 3) {
            var5 = 0.2;
         } else if (SandboxOptions.instance.getOtherLootModifier() == 4) {
            var5 = 0.6;
         } else if (SandboxOptions.instance.getOtherLootModifier() == 5) {
            var5 = 1.0;
         } else if (SandboxOptions.instance.getOtherLootModifier() == 6) {
            var5 = 2.0;
         } else if (SandboxOptions.instance.getOtherLootModifier() == 7) {
            var5 = 4.0;
         }

         var0.rawset("OtherLootModifier", var5);
      }
   }
}
} // namespace zombie
