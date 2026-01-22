#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/FliesSound.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ZomboidGlobals.h"
#include "zombie/audio/parameters/ParameterZombieState/State.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/ClothingWetness.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/Stats.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/Drainable.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/Literature.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/util/StringUtils.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/vehicles/VehicleWindow.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace characters {
namespace BodyDamage {


class BodyDamage {
public:
   public const std::vector<BodyPart> BodyParts = new std::vector<>(18);
   public const std::vector<BodyPartLast> BodyPartsLastState = new std::vector<>(18);
    int DamageModCount = 60;
    float InfectionGrowthRate = 0.001F;
    float InfectionLevel = 0.0F;
    bool IsInfected;
    float InfectionTime = -1.0F;
    float InfectionMortalityDuration = -1.0F;
    float FakeInfectionLevel = 0.0F;
    bool IsFakeInfected;
    float OverallBodyHealth = 100.0F;
    float StandardHealthAddition = 0.002F;
    float ReducedHealthAddition = 0.0013F;
    float SeverlyReducedHealthAddition = 8.0E-4F;
    float SleepingHealthAddition = 0.02F;
    float HealthFromFood = 0.015F;
    float HealthReductionFromSevereBadMoodles = 0.0165F;
    int StandardHealthFromFoodTime = 1600;
    float HealthFromFoodTimer = 0.0F;
    float BoredomLevel = 0.0F;
    float BoredomDecreaseFromReading = 0.5F;
    float InitialThumpPain = 14.0F;
    float InitialScratchPain = 18.0F;
    float InitialBitePain = 25.0F;
    float InitialWoundPain = 80.0F;
    float ContinualPainIncrease = 0.001F;
    float PainReductionFromMeds = 30.0F;
    float StandardPainReductionWhenWell = 0.01F;
    int OldNumZombiesVisible = 0;
    int CurrentNumZombiesVisible = 0;
    float PanicIncreaseValue = 7.0F;
    float PanicIncreaseValueFrame = 0.035F;
    float PanicReductionValue = 0.06F;
    float DrunkIncreaseValue = 20.5F;
    float DrunkReductionValue = 0.0042F;
    bool IsOnFire = false;
    bool BurntToDeath = false;
    float Wetness = 0.0F;
    float CatchACold = 0.0F;
    bool HasACold = false;
    float ColdStrength = 0.0F;
    float ColdProgressionRate = 0.0112F;
    int TimeToSneezeOrCough = 0;
    int MildColdSneezeTimerMin = 600;
    int MildColdSneezeTimerMax = 800;
    int ColdSneezeTimerMin = 300;
    int ColdSneezeTimerMax = 600;
    int NastyColdSneezeTimerMin = 200;
    int NastyColdSneezeTimerMax = 300;
    int SneezeCoughActive = 0;
    int SneezeCoughTime = 0;
    int SneezeCoughDelay = 25;
    float UnhappynessLevel = 0.0F;
    float ColdDamageStage = 0.0F;
    IsoGameCharacter ParentChar;
    float FoodSicknessLevel = 0.0F;
    int RemotePainLevel;
    float Temperature = 37.0F;
    float lastTemperature = 37.0F;
    float PoisonLevel = 0.0F;
    bool reduceFakeInfection = false;
    float painReduction = 0.0F;
    float coldReduction = 0.0F;
    Thermoregulator thermoregulator;
    static const float InfectionLevelToZombify = 0.001F;
    static std::string behindStr = "BEHIND";
    static std::string leftStr = "LEFT";
    static std::string rightStr = "RIGHT";

    public BodyDamage(IsoGameCharacter var1) {
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.Hand_L, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.Hand_R, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.ForeArm_L, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.ForeArm_R, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.UpperArm_L, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.UpperArm_R, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.Torso_Upper, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.Torso_Lower, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.Head, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.Neck, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.Groin, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.UpperLeg_L, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.UpperLeg_R, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.LowerLeg_L, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.LowerLeg_R, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.Foot_L, var1));
      this.BodyParts.push_back(std::make_shared<BodyPart>(BodyPartType.Foot_R, var1));

      for (BodyPart var3 : this.BodyParts) {
         this.BodyPartsLastState.push_back(std::make_unique<BodyPartLast>());
      }

      this.RestoreToFullHealth();
      this.ParentChar = var1;
      if (this.dynamic_cast<IsoPlayer*>(ParentChar) != nullptr) {
         this.thermoregulator = std::make_shared<Thermoregulator>(this);
      }

      this.setBodyPartsLastState();
   }

    BodyPart getBodyPart(BodyPartType var1) {
      return this.BodyParts.get(BodyPartType.ToIndex(var1));
   }

    BodyPartLast getBodyPartsLastState(BodyPartType var1) {
      return this.BodyPartsLastState.get(BodyPartType.ToIndex(var1));
   }

    void setBodyPartsLastState() {
      for (int var1 = 0; var1 < this.getBodyParts().size(); var1++) {
    BodyPart var2 = this.getBodyParts().get(var1);
    BodyPartLast var3 = this.BodyPartsLastState.get(var1);
         var3.copy(var2);
      }
   }

    void load(ByteBuffer var1, int var2) {
      for (int var3 = 0; var3 < this.getBodyParts().size(); var3++) {
    BodyPart var4 = this.getBodyParts().get(var3);
         var4.SetBitten(var1.get() == 1);
         var4.setScratched(var1.get() == 1, false);
         var4.setBandaged(var1.get() == 1, 0.0F);
         var4.setBleeding(var1.get() == 1);
         var4.setDeepWounded(var1.get() == 1);
         var4.SetFakeInfected(var1.get() == 1);
         var4.SetInfected(var1.get() == 1);
         var4.SetHealth(var1.getFloat());
         if (var2 >= 37 && var2 <= 43) {
            var1.getInt();
         }

         if (var2 >= 44) {
            if (var4.bandaged()) {
               var4.setBandageLife(var1.getFloat());
            }

            var4.setInfectedWound(var1.get() == 1);
            if (var4.isInfectedWound()) {
               var4.setWoundInfectionLevel(var1.getFloat());
            }

            var4.setBiteTime(var1.getFloat());
            var4.setScratchTime(var1.getFloat());
            var4.setBleedingTime(var1.getFloat());
            var4.setAlcoholLevel(var1.getFloat());
            var4.setAdditionalPain(var1.getFloat());
            var4.setDeepWoundTime(var1.getFloat());
            var4.setHaveGlass(var1.get() == 1);
            var4.setGetBandageXp(var1.get() == 1);
            if (var2 >= 48) {
               var4.setStitched(var1.get() == 1);
               var4.setStitchTime(var1.getFloat());
            }

            var4.setGetStitchXp(var1.get() == 1);
            var4.setGetSplintXp(var1.get() == 1);
            var4.setFractureTime(var1.getFloat());
            var4.setSplint(var1.get() == 1, 0.0F);
            if (var4.isSplint()) {
               var4.setSplintFactor(var1.getFloat());
            }

            var4.setHaveBullet(var1.get() == 1, 0);
            var4.setBurnTime(var1.getFloat());
            var4.setNeedBurnWash(var1.get() == 1);
            var4.setLastTimeBurnWash(var1.getFloat());
            var4.setSplintItem(GameWindow.ReadString(var1));
            var4.setBandageType(GameWindow.ReadString(var1));
            var4.setCutTime(var1.getFloat());
            if (var2 >= 153) {
               var4.setWetness(var1.getFloat());
            }

            if (var2 >= 167) {
               var4.setStiffness(var1.getFloat());
            }
         }
      }

      this.setBodyPartsLastState();
      this.setInfectionLevel(var1.getFloat());
      this.setFakeInfectionLevel(var1.getFloat());
      this.setWetness(var1.getFloat());
      this.setCatchACold(var1.getFloat());
      this.setHasACold(var1.get() == 1);
      this.setColdStrength(var1.getFloat());
      this.setUnhappynessLevel(var1.getFloat());
      this.setBoredomLevel(var1.getFloat());
      this.setFoodSicknessLevel(var1.getFloat());
      this.PoisonLevel = var1.getFloat();
    float var5 = var1.getFloat();
      this.setTemperature(var5);
      this.setReduceFakeInfection(var1.get() == 1);
      this.setHealthFromFoodTimer(var1.getFloat());
      this.painReduction = var1.getFloat();
      this.coldReduction = var1.getFloat();
      this.InfectionTime = var1.getFloat();
      this.InfectionMortalityDuration = var1.getFloat();
      this.ColdDamageStage = var1.getFloat();
      this.calculateOverallHealth();
      if (var2 >= 153 && var1.get() == 1) {
         if (this.thermoregulator != nullptr) {
            this.thermoregulator.load(var1, var2);
         } else {
    Thermoregulator var6 = std::make_shared<Thermoregulator>(this);
            var6.load(var1, var2);
            DebugLog.log("Couldnt load Thermoregulator, == nullptr");
         }
      }
   }

    void save(ByteBuffer var1) {
      for (int var2 = 0; var2 < this.getBodyParts().size(); var2++) {
    BodyPart var3 = this.getBodyParts().get(var2);
         var1.put((byte)(var3.bitten() ? 1 : 0));
         var1.put((byte)(var3.scratched() ? 1 : 0));
         var1.put((byte)(var3.bandaged() ? 1 : 0));
         var1.put((byte)(var3.bleeding() ? 1 : 0));
         var1.put((byte)(var3.deepWounded() ? 1 : 0));
         var1.put((byte)(var3.IsFakeInfected() ? 1 : 0));
         var1.put((byte)(var3.IsInfected() ? 1 : 0));
         var1.putFloat(var3.getHealth());
         if (var3.bandaged()) {
            var1.putFloat(var3.getBandageLife());
         }

         var1.put((byte)(var3.isInfectedWound() ? 1 : 0));
         if (var3.isInfectedWound()) {
            var1.putFloat(var3.getWoundInfectionLevel());
         }

         var1.putFloat(var3.getBiteTime());
         var1.putFloat(var3.getScratchTime());
         var1.putFloat(var3.getBleedingTime());
         var1.putFloat(var3.getAlcoholLevel());
         var1.putFloat(var3.getAdditionalPain());
         var1.putFloat(var3.getDeepWoundTime());
         var1.put((byte)(var3.haveGlass() ? 1 : 0));
         var1.put((byte)(var3.isGetBandageXp() ? 1 : 0));
         var1.put((byte)(var3.stitched() ? 1 : 0));
         var1.putFloat(var3.getStitchTime());
         var1.put((byte)(var3.isGetStitchXp() ? 1 : 0));
         var1.put((byte)(var3.isGetSplintXp() ? 1 : 0));
         var1.putFloat(var3.getFractureTime());
         var1.put((byte)(var3.isSplint() ? 1 : 0));
         if (var3.isSplint()) {
            var1.putFloat(var3.getSplintFactor());
         }

         var1.put((byte)(var3.haveBullet() ? 1 : 0));
         var1.putFloat(var3.getBurnTime());
         var1.put((byte)(var3.isNeedBurnWash() ? 1 : 0));
         var1.putFloat(var3.getLastTimeBurnWash());
         GameWindow.WriteString(var1, var3.getSplintItem());
         GameWindow.WriteString(var1, var3.getBandageType());
         var1.putFloat(var3.getCutTime());
         var1.putFloat(var3.getWetness());
         var1.putFloat(var3.getStiffness());
      }

      var1.putFloat(this.InfectionLevel);
      var1.putFloat(this.getFakeInfectionLevel());
      var1.putFloat(this.getWetness());
      var1.putFloat(this.getCatchACold());
      var1.put((byte)(this.isHasACold() ? 1 : 0));
      var1.putFloat(this.getColdStrength());
      var1.putFloat(this.getUnhappynessLevel());
      var1.putFloat(this.getBoredomLevel());
      var1.putFloat(this.getFoodSicknessLevel());
      var1.putFloat(this.PoisonLevel);
      var1.putFloat(this.Temperature);
      var1.put((byte)(this.isReduceFakeInfection() ? 1 : 0));
      var1.putFloat(this.HealthFromFoodTimer);
      var1.putFloat(this.painReduction);
      var1.putFloat(this.coldReduction);
      var1.putFloat(this.InfectionTime);
      var1.putFloat(this.InfectionMortalityDuration);
      var1.putFloat(this.ColdDamageStage);
      var1.put((byte)(this.thermoregulator != nullptr ? 1 : 0));
      if (this.thermoregulator != nullptr) {
         this.thermoregulator.save(var1);
      }
   }

    bool IsFakeInfected() {
      return this.isIsFakeInfected();
   }

    void OnFire(bool var1) {
      this.setIsOnFire(var1);
   }

    bool IsOnFire() {
      return this.isIsOnFire();
   }

    bool WasBurntToDeath() {
      return this.isBurntToDeath();
   }

    void IncreasePanicFloat(float var1) {
    float var2 = 1.0F;
      if (this.getParentChar().getBetaEffect() > 0.0F) {
         var2 -= this.getParentChar().getBetaDelta();
         if (var2 > 1.0F) {
            var2 = 1.0F;
         }

         if (var2 < 0.0F) {
            var2 = 0.0F;
         }
      }

      if (this.getParentChar().getCharacterTraits().Cowardly.isSet()) {
         var2 *= 2.0F;
      }

      if (this.getParentChar().getCharacterTraits().Brave.isSet()) {
         var2 *= 0.3F;
      }

      if (this.getParentChar().getCharacterTraits().Desensitized.isSet()) {
         var2 = 0.0F;
      }

    Stats var10000 = this.ParentChar.getStats();
      var10000.Panic = var10000.Panic + this.getPanicIncreaseValueFrame() * var1 * var2;
      if (this.getParentChar().getStats().Panic > 100.0F) {
         this.ParentChar.getStats().Panic = 100.0F;
      }
   }

    void IncreasePanic(int var1) {
      if (this.getParentChar().getVehicle() != nullptr) {
         var1 /= 2;
      }

    float var2 = 1.0F;
      if (this.getParentChar().getBetaEffect() > 0.0F) {
         var2 -= this.getParentChar().getBetaDelta();
         if (var2 > 1.0F) {
            var2 = 1.0F;
         }

         if (var2 < 0.0F) {
            var2 = 0.0F;
         }
      }

      if (this.getParentChar().getCharacterTraits().Cowardly.isSet()) {
         var2 *= 2.0F;
      }

      if (this.getParentChar().getCharacterTraits().Brave.isSet()) {
         var2 *= 0.3F;
      }

      if (this.getParentChar().getCharacterTraits().Desensitized.isSet()) {
         var2 = 0.0F;
      }

    Stats var10000 = this.ParentChar.getStats();
      var10000.Panic = var10000.Panic + this.getPanicIncreaseValue() * var1 * var2;
      if (this.getParentChar().getStats().Panic > 100.0F) {
         this.ParentChar.getStats().Panic = 100.0F;
      }
   }

    void ReducePanic() {
      if (!(this.ParentChar.getStats().Panic <= 0.0F)) {
    float var1 = this.getPanicReductionValue() * (GameTime.getInstance().getMultiplier() / 1.6F);
    int var2 = (int)Math.floor(std::make_shared<double>(GameTime.instance.getNightsSurvived()) / 30.0);
         if (var2 > 5) {
            var2 = 5;
         }

         var1 += this.getPanicReductionValue() * var2;
         if (this.ParentChar.isAsleep()) {
            var1 *= 2.0F;
         }

         this.ParentChar.getStats().Panic -= var1;
         if (this.getParentChar().getStats().Panic < 0.0F) {
            this.ParentChar.getStats().Panic = 0.0F;
         }
      }
   }

    void UpdatePanicState() {
    int var1 = this.getParentChar().getStats().NumVisibleZombies;
      if (var1 > this.getOldNumZombiesVisible()) {
         this.IncreasePanic(var1 - this.getOldNumZombiesVisible());
      } else {
         this.ReducePanic();
      }

      this.setOldNumZombiesVisible(var1);
   }

    void JustDrankBooze(Food var1, float var2) {
    float var3 = 1.0F;
      if (this.getParentChar().Traits.HeavyDrinker.isSet()) {
         var3 = 0.3F;
      }

      if (this.getParentChar().Traits.LightDrinker.isSet()) {
         var3 = 4.0F;
      }

      if (var1.getBaseHunger() != 0.0F) {
         var2 = var1.getHungChange() * var2 / var1.getBaseHunger() * 2.0F;
      }

      var3 *= var2;
      if (var1.getName().toLowerCase().contains("beer") || var1.hasTag("LowAlcohol")) {
         var3 *= 0.25F;
      }

      if (this.getParentChar().getStats().hunger > 0.8) {
         var3 = (float)(var3 * 1.25);
      } else if (this.getParentChar().getStats().hunger > 0.6) {
         var3 = (float)(var3 * 1.1);
      }

    Stats var10000 = this.ParentChar.getStats();
      var10000.Drunkenness = var10000.Drunkenness + this.getDrunkIncreaseValue() * var3;
      if (this.getParentChar().getStats().Drunkenness > 100.0F) {
         this.ParentChar.getStats().Drunkenness = 100.0F;
      }

      this.getParentChar().SleepingTablet(0.02F * var2);
      this.getParentChar().BetaAntiDepress(0.4F * var2);
      this.getParentChar().BetaBlockers(0.2F * var2);
      this.getParentChar().PainMeds(0.2F * var2);
   }

    void JustTookPill(InventoryItem var1) {
      if ("PillsBeta" == var1.getType())) {
         if (this.getParentChar() != nullptr && this.getParentChar().getStats().Drunkenness > 10.0F) {
            this.getParentChar().BetaBlockers(0.15F);
         } else {
            this.getParentChar().BetaBlockers(0.3F);
         }

         var1.Use();
      } else if ("PillsAntiDep" == var1.getType())) {
         if (this.getParentChar() != nullptr && this.getParentChar().getStats().Drunkenness > 10.0F) {
            this.getParentChar().BetaAntiDepress(0.15F);
         } else {
            this.getParentChar().BetaAntiDepress(0.3F);
         }

         var1.Use();
      } else if ("PillsSleepingTablets" == var1.getType())) {
         var1.Use();
         this.getParentChar().SleepingTablet(0.1F);
         if (this.getParentChar() instanceof IsoPlayer) {
            ((IsoPlayer)this.getParentChar()).setSleepingPillsTaken(((IsoPlayer)this.getParentChar()).getSleepingPillsTaken() + 1);
         }
      } else if ("Pills" == var1.getType())) {
         var1.Use();
         if (this.getParentChar() != nullptr && this.getParentChar().getStats().Drunkenness > 10.0F) {
            this.getParentChar().PainMeds(0.15F);
         } else {
            this.getParentChar().PainMeds(0.45F);
         }
      } else if ("PillsVitamins" == var1.getType())) {
         var1.Use();
         if (this.getParentChar() != nullptr && this.getParentChar().getStats().Drunkenness > 10.0F) {
    Stats var2 = this.getParentChar().getStats();
            var2.fatigue = var2.fatigue + var1.getFatigueChange() / 2.0F;
         } else {
    Stats var10000 = this.getParentChar().getStats();
            var10000.fatigue = var10000.fatigue + var1.getFatigueChange();
         }
      }
   }

    void JustAteFood(Food var1, float var2) {
      if (var1.getPoisonPower() > 0) {
    float var3 = var1.getPoisonPower() * var2;
         if (this.getParentChar().Traits.IronGut.isSet()) {
            var3 /= 2.0F;
         }

         if (this.getParentChar().Traits.WeakStomach.isSet()) {
            var3 *= 2.0F;
         }

         this.PoisonLevel += var3;
    Stats var10000 = this.ParentChar.getStats();
         var10000.Pain = var10000.Pain + var1.getPoisonPower() * var2 / 6.0F;
      }

      if (var1.isTaintedWater()) {
         this.PoisonLevel += 20.0F * var2;
         this.ParentChar.getStats().Pain += 10.0F * var2 / 6.0F;
      }

      if (var1.getReduceInfectionPower() > 0.0F) {
         this.getParentChar().setReduceInfectionPower(var1.getReduceInfectionPower());
      }

      this.setBoredomLevel(this.getBoredomLevel() + var1.getBoredomChange() * var2);
      if (this.getBoredomLevel() < 0.0F) {
         this.setBoredomLevel(0.0F);
      }

      this.setUnhappynessLevel(this.getUnhappynessLevel() + var1.getUnhappyChange() * var2);
      if (this.getUnhappynessLevel() < 0.0F) {
         this.setUnhappynessLevel(0.0F);
      }

      if (var1.isAlcoholic()) {
         this.JustDrankBooze(var1, var2);
      }

      if (this.getParentChar().getStats().hunger <= 0.0F) {
    float var5 = Math.abs(var1.getHungerChange()) * var2;
         this.setHealthFromFoodTimer((int)(this.getHealthFromFoodTimer() + var5 * this.getHealthFromFoodTimeByHunger()));
         if (var1.isCooked()) {
            this.setHealthFromFoodTimer((int)(this.getHealthFromFoodTimer() + var5 * this.getHealthFromFoodTimeByHunger()));
         }

         if (this.getHealthFromFoodTimer() > 11000.0F) {
            this.setHealthFromFoodTimer(11000.0F);
         }
      }

      if (!"Tutorial" == Core.getInstance().getGameMode())) {
         if (!var1.isCooked() && var1.isbDangerousUncooked()) {
            this.setHealthFromFoodTimer(0.0F);
    uint8_t var6 = 75;
            if (var1.hasTag("Egg")) {
               var6 = 5;
            }

            if (this.getParentChar().Traits.IronGut.isSet()) {
               var6 /= 2;
               if (var1.hasTag("Egg")) {
                  var6 = 0;
               }
            }

            if (this.getParentChar().Traits.WeakStomach.isSet()) {
               var6 *= 2;
            }

            if (var6 > 0 && Rand.Next(100) < var6 && !this.isInfected()) {
               this.PoisonLevel += 15.0F * var2;
            }
         }

         if (var1.getAge() >= var1.getOffAgeMax()) {
    float var7 = var1.getAge() - var1.getOffAgeMax();
            if (var7 == 0.0F) {
               var7 = 1.0F;
            }

            if (var7 > 5.0F) {
               var7 = 5.0F;
            }

    int var4;
            if (var1.getOffAgeMax() > var1.getOffAge()) {
               var4 = (int)(var7 / (var1.getOffAgeMax() - var1.getOffAge()) * 100.0F);
            } else {
               var4 = 100;
            }

            if (this.getParentChar().Traits.IronGut.isSet()) {
               var4 /= 2;
            }

            if (this.getParentChar().Traits.WeakStomach.isSet()) {
               var4 *= 2;
            }

            if (Rand.Next(100) < var4 && !this.isInfected()) {
               this.PoisonLevel = this.PoisonLevel + 5.0F * Math.abs(var1.getHungChange() * 10.0F) * var2;
            }
         }
      }
   }

    void JustAteFood(Food var1) {
      this.JustAteFood(var1, 100.0F);
   }

    float getHealthFromFoodTimeByHunger() {
      return 13000.0F;
   }

    void JustReadSomething(Literature var1) {
      this.setBoredomLevel(this.getBoredomLevel() + var1.getBoredomChange());
      if (this.getBoredomLevel() < 0.0F) {
         this.setBoredomLevel(0.0F);
      }

      this.setUnhappynessLevel(this.getUnhappynessLevel() + var1.getUnhappyChange());
      if (this.getUnhappynessLevel() < 0.0F) {
         this.setUnhappynessLevel(0.0F);
      }
   }

    void JustTookPainMeds() {
    Stats var10000 = this.ParentChar.getStats();
      var10000.Pain = var10000.Pain - this.getPainReductionFromMeds();
      if (this.getParentChar().getStats().Pain < 0.0F) {
         this.ParentChar.getStats().Pain = 0.0F;
      }
   }

    void UpdateWetness() {
    IsoGridSquare var1 = this.getParentChar().getCurrentSquare();
    BaseVehicle var2 = this.getParentChar().getVehicle();
    IsoGameCharacter var3 = this.getParentChar();
    bool var4 = var1 == nullptr || !var1.isInARoom() && !var1.haveRoof;
      if (var2 != nullptr && var2.hasRoof(var2.getSeat(this.getParentChar()))) {
         var4 = false;
      }

    ClothingWetness var5 = this.getParentChar().getClothingWetness();
    float var6 = 0.0F;
    float var7 = 0.0F;
    float var8 = 0.0F;
      if (var2 != nullptr && ClimateManager.getInstance().isRaining()) {
    VehiclePart var9 = var2.getPartById("Windshield");
         if (var9 != nullptr) {
    VehicleWindow var10 = var9.getWindow();
            if (var10 != nullptr && var10.isDestroyed()) {
    float var11 = ClimateManager.getInstance().getRainIntensity();
               var11 *= var11;
               var11 *= var2.getCurrentSpeedKmHour() / 50.0F;
               if (var11 < 0.1F) {
                  var11 = 0.0F;
               }

               if (var11 > 1.0F) {
                  var11 = 1.0F;
               }

               var8 = var11 * 3.0F;
               var6 = var11;
            }
         }
      }

      if (var4 && var3.isAsleep() && var3.getBed() != nullptr && "Tent" == var3.getBed().getName())) {
         var4 = false;
      }

      if (var4 && ClimateManager.getInstance().isRaining()) {
    float var13 = ClimateManager.getInstance().getRainIntensity();
         if (var13 < 0.1) {
            var13 = 0.0F;
         }

         var6 = var13;
      } else if (!var4 || !ClimateManager.getInstance().isRaining()) {
    float var12 = ClimateManager.getInstance().getAirTemperatureForCharacter(this.getParentChar());
    float var15 = 0.1F;
         if (var12 > 5.0F) {
            var15 += (var12 - 5.0F) / 10.0F;
         }

         var15 -= var8;
         if (var15 < 0.0F) {
            var15 = 0.0F;
         }

         var7 = var15;
      }

      if (var5 != nullptr) {
         var5.updateWetness(var6, var7);
      }

    float var14 = 0.0F;
      if (this.BodyParts.size() > 0) {
         for (int var17 = 0; var17 < this.BodyParts.size(); var17++) {
            var14 += this.BodyParts.get(var17).getWetness();
         }

         var14 /= this.BodyParts.size();
      }

      this.Wetness = PZMath.clamp(var14, 0.0F, 100.0F);
    float var18 = 0.0F;
      if (this.thermoregulator != nullptr) {
         var18 = this.thermoregulator.getCatchAColdDelta();
      }

      if (!this.isHasACold() && var18 > 0.1F) {
         if (this.getParentChar().Traits.ProneToIllness.isSet()) {
            var18 *= 1.7F;
         }

         if (this.getParentChar().Traits.Resilient.isSet()) {
            var18 *= 0.45F;
         }

         if (this.getParentChar().Traits.Outdoorsman.isSet()) {
            var18 *= 0.1F;
         }

         this.setCatchACold(this.getCatchACold() + (float)ZomboidGlobals.CatchAColdIncreaseRate * var18 * GameTime.instance.getMultiplier());
         if (this.getCatchACold() >= 100.0F) {
            this.setCatchACold(0.0F);
            this.setHasACold(true);
            this.setColdStrength(20.0F);
            this.setTimeToSneezeOrCough(0);
         }
      }

      if (var18 <= 0.1F) {
         this.setCatchACold(this.getCatchACold() - (float)ZomboidGlobals.CatchAColdDecreaseRate);
         if (this.getCatchACold() <= 0.0F) {
            this.setCatchACold(0.0F);
         }
      }
   }

    void TriggerSneezeCough() {
      if (this.getSneezeCoughActive() <= 0) {
         if (Rand.Next(100) > 50) {
            this.setSneezeCoughActive(1);
         } else {
            this.setSneezeCoughActive(2);
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.HasACold) == 2) {
            this.setSneezeCoughActive(1);
         }

         this.setSneezeCoughTime(this.getSneezeCoughDelay());
         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.HasACold) == 2) {
            this.setTimeToSneezeOrCough(this.getMildColdSneezeTimerMin() + Rand.Next(this.getMildColdSneezeTimerMax() - this.getMildColdSneezeTimerMin()));
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.HasACold) == 3) {
            this.setTimeToSneezeOrCough(this.getColdSneezeTimerMin() + Rand.Next(this.getColdSneezeTimerMax() - this.getColdSneezeTimerMin()));
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.HasACold) == 4) {
            this.setTimeToSneezeOrCough(this.getNastyColdSneezeTimerMin() + Rand.Next(this.getNastyColdSneezeTimerMax() - this.getNastyColdSneezeTimerMin()));
         }

    bool var1 = false;
         if (this.getParentChar().getPrimaryHandItem() == nullptr
            || !this.getParentChar().getPrimaryHandItem().getType() == "Tissue")
               && !this.getParentChar().getPrimaryHandItem().getType() == "ToiletPaper")) {
            if (this.getParentChar().getSecondaryHandItem() != nullptr
               && (
                  this.getParentChar().getSecondaryHandItem().getType() == "Tissue")
                     || this.getParentChar().getSecondaryHandItem().getType() == "ToiletPaper")
               )
               && ((Drainable)this.getParentChar().getSecondaryHandItem()).getUsedDelta() > 0.0F) {
               ((Drainable)this.getParentChar().getSecondaryHandItem())
                  .setUsedDelta(((Drainable)this.getParentChar().getSecondaryHandItem()).getUsedDelta() - 0.1F);
               if (((Drainable)this.getParentChar().getSecondaryHandItem()).getUsedDelta() <= 0.0F) {
                  this.getParentChar().getSecondaryHandItem().Use();
               }

               var1 = true;
            }
         } else if (((Drainable)this.getParentChar().getPrimaryHandItem()).getUsedDelta() > 0.0F) {
            ((Drainable)this.getParentChar().getPrimaryHandItem()).setUsedDelta(((Drainable)this.getParentChar().getPrimaryHandItem()).getUsedDelta() - 0.1F);
            if (((Drainable)this.getParentChar().getPrimaryHandItem()).getUsedDelta() <= 0.0F) {
               this.getParentChar().getPrimaryHandItem().Use();
            }

            var1 = true;
         }

         if (var1) {
            this.setSneezeCoughActive(this.getSneezeCoughActive() + 2);
         } else {
    uint8_t var2 = 20;
    uint8_t var3 = 20;
            if (this.getSneezeCoughActive() == 1) {
               var2 = 20;
               var3 = 25;
            }

            if (this.getSneezeCoughActive() == 2) {
               var2 = 35;
               var3 = 40;
            }

            WorldSoundManager.instance
               .addSound(
                  this.getParentChar(), (int)this.getParentChar().getX(), (int)this.getParentChar().getY(), (int)this.getParentChar().getZ(), var2, var3, true
               );
         }
      }
   }

    int IsSneezingCoughing() {
      return this.getSneezeCoughActive();
   }

    void UpdateCold() {
      if (this.isHasACold()) {
    bool var1 = true;
    IsoGridSquare var2 = this.getParentChar().getCurrentSquare();
         if (var2 == nullptr
            || !var2.isInARoom()
            || this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Wet) > 0
            || this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Hypothermia) >= 1
            || this.getParentChar().getStats().fatigue > 0.5F
            || this.getParentChar().getStats().hunger > 0.25F
            || this.getParentChar().getStats().thirst > 0.25F) {
            var1 = false;
         }

         if (this.getColdReduction() > 0.0F) {
            var1 = true;
            this.setColdReduction(this.getColdReduction() - 0.005F * GameTime.instance.getMultiplier());
            if (this.getColdReduction() < 0.0F) {
               this.setColdReduction(0.0F);
            }
         }

         if (var1) {
    float var3 = 1.0F;
            if (this.getParentChar().Traits.ProneToIllness.isSet()) {
               var3 = 0.5F;
            }

            if (this.getParentChar().Traits.Resilient.isSet()) {
               var3 = 1.5F;
            }

            this.setColdStrength(this.getColdStrength() - this.getColdProgressionRate() * var3 * GameTime.instance.getMultiplier());
            if (this.getColdReduction() > 0.0F) {
               this.setColdStrength(this.getColdStrength() - this.getColdProgressionRate() * var3 * GameTime.instance.getMultiplier());
            }

            if (this.getColdStrength() < 0.0F) {
               this.setColdStrength(0.0F);
               this.setHasACold(false);
               this.setCatchACold(0.0F);
            }
         } else {
    float var4 = 1.0F;
            if (this.getParentChar().Traits.ProneToIllness.isSet()) {
               var4 = 1.2F;
            }

            if (this.getParentChar().Traits.Resilient.isSet()) {
               var4 = 0.8F;
            }

            this.setColdStrength(this.getColdStrength() + this.getColdProgressionRate() * var4 * GameTime.instance.getMultiplier());
            if (this.getColdStrength() > 100.0F) {
               this.setColdStrength(100.0F);
            }
         }

         if (this.getSneezeCoughTime() > 0) {
            this.setSneezeCoughTime(this.getSneezeCoughTime() - 1);
            if (this.getSneezeCoughTime() == 0) {
               this.setSneezeCoughActive(0);
            }
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.HasACold) > 1 && this.getTimeToSneezeOrCough() >= 0 && !this.ParentChar.IsSpeaking()) {
            this.setTimeToSneezeOrCough(this.getTimeToSneezeOrCough() - 1);
            if (this.getTimeToSneezeOrCough() <= 0) {
               this.TriggerSneezeCough();
            }
         }
      }
   }

    float getColdStrength() {
      return this.isHasACold() ? this.ColdStrength : 0.0F;
   }

    float getWetness() {
      return this.Wetness;
   }

    void AddDamage(BodyPartType var1, float var2) {
      this.getBodyParts().get(BodyPartType.ToIndex(var1)).AddDamage(var2);
   }

    void AddGeneralHealth(float var1) {
    int var2 = 0;

      for (int var3 = 0; var3 < BodyPartType.ToIndex(BodyPartType.MAX); var3++) {
         if (this.getBodyParts().get(var3).getHealth() < 100.0F) {
            var2++;
         }
      }

      if (var2 > 0) {
    float var5 = var1 / var2;

         for (int var4 = 0; var4 < BodyPartType.ToIndex(BodyPartType.MAX); var4++) {
            if (this.getBodyParts().get(var4).getHealth() < 100.0F) {
               this.getBodyParts().get(var4).AddHealth(var5);
            }
         }
      }
   }

    void ReduceGeneralHealth(float var1) {
      if (this.getOverallBodyHealth() <= 10.0F) {
         this.getParentChar().forceAwake();
      }

      if (!(var1 <= 0.0F)) {
    float var2 = var1 / BodyPartType.ToIndex(BodyPartType.MAX);

         for (int var3 = 0; var3 < BodyPartType.ToIndex(BodyPartType.MAX); var3++) {
            this.getBodyParts().get(var3).ReduceHealth(var2 / BodyPartType.getDamageModifyer(var3));
         }
      }
   }

    void AddDamage(int var1, float var2) {
      this.getBodyParts().get(var1).AddDamage(var2);
   }

    void splatBloodFloorBig() {
      this.getParentChar().splatBloodFloorBig();
      this.getParentChar().splatBloodFloorBig();
      this.getParentChar().splatBloodFloorBig();
   }

    void DamageFromWeapon(HandWeapon var1) {
      if (GameServer.bServer) {
         if (var1 != nullptr) {
            this.getParentChar().sendObjectChange("DamageFromWeapon", new Object[]{"weapon", var1.getFullType()});
         }
      } else if (!(this.getParentChar() instanceof IsoPlayer) || ((IsoPlayer)this.getParentChar()).isLocalPlayer()) {
    int var2 = 0;
    uint8_t var3 = 1;
    bool var4 = true;
         var2 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.MAX));
         if (DebugOptions.instance.MultiplayerTorsoHit.getValue()) {
            var2 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Torso_Upper), BodyPartType.ToIndex(BodyPartType.Head));
         }

    bool var5 = false;
    bool var6 = false;
    bool var7 = false;
    bool var8 = true;
    bool var9 = true;
         if (var1.getCategories().contains("Blunt") || var1.getCategories().contains("SmallBlunt")) {
            var9 = false;
            var3 = 0;
            var5 = true;
         } else if (!var1.isAimedFirearm()) {
            var3 = 1;
            var6 = true;
         } else {
            var7 = true;
            var3 = 2;
         }

    BodyPart var10 = this.getBodyPart(BodyPartType.FromIndex(var2));
    float var11 = this.getParentChar().getBodyPartClothingDefense(var10.getIndex(), var6, var7);
         if (Rand.Next(100) < var11) {
            var4 = false;
            this.getParentChar().addHoleFromZombieAttacks(BloodBodyPartType.FromIndex(var2), false);
         }

         if (var4) {
            this.getParentChar().addHole(BloodBodyPartType.FromIndex(var2));
            this.getParentChar().splatBloodFloorBig();
            this.getParentChar().splatBloodFloorBig();
            this.getParentChar().splatBloodFloorBig();
            if (var6) {
               if (Rand.NextBool(6)) {
                  var10.generateDeepWound();
               } else if (Rand.NextBool(3)) {
                  var10.setCut(true);
               } else {
                  var10.setScratched(true, true);
               }
            } else if (var5) {
               if (Rand.NextBool(4)) {
                  var10.setCut(true);
               } else {
                  var10.setScratched(true, true);
               }
            } else if (var7) {
               var10.setHaveBullet(true, 0);
            }

    float var12 = Rand.Next(var1.getMinDamage(), var1.getMaxDamage()) * 15.0F;
            if (var2 == BodyPartType.ToIndex(BodyPartType.Head)) {
               var12 *= 4.0F;
            }

            if (var2 == BodyPartType.ToIndex(BodyPartType.Neck)) {
               var12 *= 4.0F;
            }

            if (var2 == BodyPartType.ToIndex(BodyPartType.Torso_Upper)) {
               var12 *= 2.0F;
            }

            if (GameClient.bClient) {
               if (var1.isRanged()) {
                  var12 = (float)(var12 * ServerOptions.getInstance().PVPFirearmDamageModifier.getValue());
               } else {
                  var12 = (float)(var12 * ServerOptions.getInstance().PVPMeleeDamageModifier.getValue());
               }
            }

            this.AddDamage(var2, var12);
            switch (var3) {
               case 0:
    Stats var18 = this.ParentChar.getStats();
                  var18.Pain = var18.Pain + this.getInitialThumpPain() * BodyPartType.getPainModifyer(var2);
                  break;
               case 1:
    Stats var17 = this.ParentChar.getStats();
                  var17.Pain = var17.Pain + this.getInitialScratchPain() * BodyPartType.getPainModifyer(var2);
                  break;
               case 2:
    Stats var10000 = this.ParentChar.getStats();
                  var10000.Pain = var10000.Pain + this.getInitialBitePain() * BodyPartType.getPainModifyer(var2);
            }

            if (this.getParentChar().getStats().Pain > 100.0F) {
               this.ParentChar.getStats().Pain = 100.0F;
            }

            if (this.dynamic_cast<IsoPlayer*>(ParentChar) != nullptr && GameClient.bClient && ((IsoPlayer)this.ParentChar).isLocalPlayer()) {
    IsoPlayer var13 = (IsoPlayer)this.ParentChar;
               var13.updateMovementRates();
               GameClient.sendPlayerInjuries(var13);
               GameClient.sendPlayerDamage(var13);
            }
         }
      }
   }

    bool AddRandomDamageFromZombie(IsoZombie var1, const std::string& var2) {
      if (StringUtils.isNullOrEmpty(var2)) {
         var2 = "Bite";
      }

      this.getParentChar().setVariable("hitpvp", false);
      if (GameServer.bServer) {
         this.getParentChar().sendObjectChange("AddRandomDamageFromZombie", new Object[]{"zombie", var1.OnlineID});
    return true;
      } else {
    uint8_t var3 = 0;
    int var4 = 0;
    int var5 = 15 + this.getParentChar().getMeleeCombatMod();
    int var6 = 85;
    int var7 = 65;
    std::string var8 = this.getParentChar().testDotSide(var1);
    bool var9 = var8 == behindStr);
    bool var10 = var8 == leftStr) || var8 == rightStr);
    int var11 = this.getParentChar().getSurroundingAttackingZombies();
         var11 = Math.max(var11, 1);
         var5 -= (var11 - 1) * 10;
         var6 -= (var11 - 1) * 30;
         var7 -= (var11 - 1) * 15;
    uint8_t var12 = 3;
         if (SandboxOptions.instance.Lore.Strength.getValue() == 1) {
            var12 = 2;
         }

         if (SandboxOptions.instance.Lore.Strength.getValue() == 3) {
            var12 = 6;
         }

         if (this.ParentChar.Traits.ThickSkinned.isSet()) {
            var5 = (int)(var5 * 1.3);
         }

         if (this.ParentChar.Traits.ThinSkinned.isSet()) {
            var5 = (int)(var5 / 1.3);
         }

         if (!"EndDeath" == this.getParentChar().getHitReaction())) {
            if (!this.getParentChar().isGodMod()
               && var11 >= var12
               && SandboxOptions.instance.Lore.ZombiesDragDown.getValue()
               && !this.getParentChar().isSitOnGround()) {
               var6 = 0;
               var7 = 0;
               var5 = 0;
               this.getParentChar().setHitReaction("EndDeath");
               this.getParentChar().setDeathDragDown(true);
            } else {
               this.getParentChar().setHitReaction(var2);
            }
         }

         if (var9) {
            var5 -= 15;
            var6 -= 25;
            var7 -= 35;
            if (SandboxOptions.instance.RearVulnerability.getValue() == 1) {
               var5 += 15;
               var6 += 25;
               var7 += 35;
            }

            if (SandboxOptions.instance.RearVulnerability.getValue() == 2) {
               var5 += 7;
               var6 += 17;
               var7 += 23;
            }

            if (var11 > 2) {
               var6 -= 15;
               var7 -= 15;
            }
         }

         if (var10) {
            var5 -= 30;
            var6 -= 7;
            var7 -= 27;
            if (SandboxOptions.instance.RearVulnerability.getValue() == 1) {
               var5 += 30;
               var6 += 7;
               var7 += 27;
            }

            if (SandboxOptions.instance.RearVulnerability.getValue() == 2) {
               var5 += 15;
               var6 += 4;
               var7 += 15;
            }
         }

         if (!var1.bCrawling) {
            if (Rand.Next(10) == 0) {
               var4 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.Groin) + 1);
            } else {
               var4 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.Neck) + 1);
            }

    float var13 = 10.0F * var11;
            if (var9) {
               var13 += 5.0F;
            }

            if (var10) {
               var13 += 2.0F;
            }

            if (var9 && Rand.Next(100) < var13) {
               var4 = BodyPartType.ToIndex(BodyPartType.Neck);
            }

            if (var4 == BodyPartType.ToIndex(BodyPartType.Head) || var4 == BodyPartType.ToIndex(BodyPartType.Neck)) {
    uint8_t var14 = 70;
               if (var9) {
                  var14 = 90;
               }

               if (var10) {
                  var14 = 80;
               }

               if (Rand.Next(100) > var14) {
    bool var15 = false;

                  while (!var15) {
                     var15 = true;
                     var4 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Torso_Lower) + 1);
                     if (var4 == BodyPartType.ToIndex(BodyPartType.Head)
                        || var4 == BodyPartType.ToIndex(BodyPartType.Neck)
                        || var4 == BodyPartType.ToIndex(BodyPartType.Groin)) {
                        var15 = false;
                     }
                  }
               }
            }
         } else {
            if (Rand.Next(2) != 0) {
    return false;
            }

            if (Rand.Next(10) == 0) {
               var4 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Groin), BodyPartType.ToIndex(BodyPartType.MAX));
            } else {
               var4 = Rand.Next(BodyPartType.ToIndex(BodyPartType.UpperLeg_L), BodyPartType.ToIndex(BodyPartType.MAX));
            }
         }

         if (var1.inactive) {
            var5 += 20;
            var6 += 20;
            var7 += 20;
         }

    float var23 = Rand.Next(1000) / 1000.0F;
         var23 *= Rand.Next(10) + 10;
         if (GameServer.bServer && this.dynamic_cast<IsoPlayer*>(ParentChar) != nullptr || Core.bDebug && this.dynamic_cast<IsoPlayer*>(ParentChar) != nullptr) {
            DebugLog.log(
               DebugType.Combat,
               "zombie did "
                  + var23
                  + " dmg to "
                  + ((IsoPlayer)this.ParentChar).getDisplayName()
                  + " on body part "
                  + BodyPartType.getDisplayName(BodyPartType.FromIndex(var4))
            );
         }

    bool var25 = false;
    bool var26 = true;
         if (Rand.Next(100) > var5) {
            var1.scratch = true;
            this.getParentChar().helmetFall(var4 == BodyPartType.ToIndex(BodyPartType.Neck) || var4 == BodyPartType.ToIndex(BodyPartType.Head));
            if (Rand.Next(100) > var7) {
               var1.scratch = false;
               var1.laceration = true;
            }

            if (Rand.Next(100) > var6) {
               var1.scratch = false;
               var1.laceration = false;
               var26 = false;
            }

            if (var1.scratch) {
    float var16 = this.getParentChar().getBodyPartClothingDefense(var4, false, false);
               var1.parameterZombieState.setState(State.AttackScratch);
               if (this.getHealth() > 0.0F) {
                  this.getParentChar().getEmitter().playSoundImpl("ZombieScratch", (IsoObject)nullptr);
               }

               if (Rand.Next(100) < var16) {
                  this.getParentChar().addHoleFromZombieAttacks(BloodBodyPartType.FromIndex(var4), var26);
    return false;
               }

    bool var17 = this.getParentChar().addHole(BloodBodyPartType.FromIndex(var4), true);
               if (var17) {
                  this.getParentChar().getEmitter().playSoundImpl("ZombieRipClothing", (IsoObject)nullptr);
               }

               var25 = true;
               this.AddDamage(var4, var23);
               this.SetScratched(var4, true);
               this.getParentChar().addBlood(BloodBodyPartType.FromIndex(var4), true, false, true);
               var3 = 1;
               if (GameServer.bServer && this.dynamic_cast<IsoPlayer*>(ParentChar) != nullptr) {
                  DebugLog.log(DebugType.Combat, "zombie scratched " + ((IsoPlayer)this.ParentChar).username);
               }
            } else if (var1.laceration) {
    float var27 = this.getParentChar().getBodyPartClothingDefense(var4, false, false);
               var1.parameterZombieState.setState(State.AttackLacerate);
               if (this.getHealth() > 0.0F) {
                  this.getParentChar().getEmitter().playSoundImpl("ZombieScratch", (IsoObject)nullptr);
               }

               if (Rand.Next(100) < var27) {
                  this.getParentChar().addHoleFromZombieAttacks(BloodBodyPartType.FromIndex(var4), var26);
    return false;
               }

    bool var30 = this.getParentChar().addHole(BloodBodyPartType.FromIndex(var4), true);
               if (var30) {
                  this.getParentChar().getEmitter().playSoundImpl("ZombieRipClothing", (IsoObject)nullptr);
               }

               var25 = true;
               this.AddDamage(var4, var23);
               this.SetCut(var4, true);
               this.getParentChar().addBlood(BloodBodyPartType.FromIndex(var4), true, false, true);
               var3 = 1;
               if (GameServer.bServer && this.dynamic_cast<IsoPlayer*>(ParentChar) != nullptr) {
                  DebugLog.log(DebugType.Combat, "zombie laceration " + ((IsoPlayer)this.ParentChar).username);
               }
            } else {
    float var28 = this.getParentChar().getBodyPartClothingDefense(var4, true, false);
               var1.parameterZombieState.setState(State.AttackBite);
               if (this.getHealth() > 0.0F) {
                  this.getParentChar().getEmitter().playSoundImpl("ZombieBite", (IsoObject)nullptr);
               }

               if (Rand.Next(100) < var28) {
                  this.getParentChar().addHoleFromZombieAttacks(BloodBodyPartType.FromIndex(var4), var26);
    return false;
               }

    bool var31 = this.getParentChar().addHole(BloodBodyPartType.FromIndex(var4), true);
               if (var31) {
                  this.getParentChar().getEmitter().playSoundImpl("ZombieRipClothing", (IsoObject)nullptr);
               }

               var25 = true;
               this.AddDamage(var4, var23);
               this.SetBitten(var4, true);
               if (var4 == BodyPartType.ToIndex(BodyPartType.Neck)) {
                  this.getParentChar().addBlood(BloodBodyPartType.FromIndex(var4), false, true, true);
                  this.getParentChar().addBlood(BloodBodyPartType.FromIndex(var4), false, true, true);
                  this.getParentChar().addBlood(BloodBodyPartType.Torso_Upper, false, true, false);
               }

               this.getParentChar().addBlood(BloodBodyPartType.FromIndex(var4), false, true, true);
               if (GameServer.bServer && this.dynamic_cast<IsoPlayer*>(ParentChar) != nullptr) {
                  DebugLog.log(DebugType.Combat, "zombie bite " + ((IsoPlayer)this.ParentChar).username);
               }

               var3 = 2;
               this.getParentChar().splatBloodFloorBig();
               this.getParentChar().splatBloodFloorBig();
               this.getParentChar().splatBloodFloorBig();
            }
         }

         if (!var25) {
            this.getParentChar().addHoleFromZombieAttacks(BloodBodyPartType.FromIndex(var4), var26);
         }

         switch (var3) {
            case 0:
    Stats var33 = this.ParentChar.getStats();
               var33.Pain = var33.Pain + this.getInitialThumpPain() * BodyPartType.getPainModifyer(var4);
               break;
            case 1:
    Stats var32 = this.ParentChar.getStats();
               var32.Pain = var32.Pain + this.getInitialScratchPain() * BodyPartType.getPainModifyer(var4);
               break;
            case 2:
    Stats var10000 = this.ParentChar.getStats();
               var10000.Pain = var10000.Pain + this.getInitialBitePain() * BodyPartType.getPainModifyer(var4);
         }

         if (this.getParentChar().getStats().Pain > 100.0F) {
            this.ParentChar.getStats().Pain = 100.0F;
         }

         if (this.dynamic_cast<IsoPlayer*>(ParentChar) != nullptr && GameClient.bClient && ((IsoPlayer)this.ParentChar).isLocalPlayer()) {
    IsoPlayer var29 = (IsoPlayer)this.ParentChar;
            var29.updateMovementRates();
            GameClient.sendPlayerInjuries(var29);
            GameClient.sendPlayerDamage(var29);
         }

    return true;
      }
   }

    bool doesBodyPartHaveInjury(BodyPartType var1) {
      return this.getBodyParts().get(BodyPartType.ToIndex(var1)).HasInjury();
   }

    bool doBodyPartsHaveInjuries(BodyPartType var1, BodyPartType var2) {
      return this.doesBodyPartHaveInjury(var1) || this.doesBodyPartHaveInjury(var2);
   }

    bool isBodyPartBleeding(BodyPartType var1) {
      return this.getBodyPart(var1).getBleedingTime() > 0.0F;
   }

    bool areBodyPartsBleeding(BodyPartType var1, BodyPartType var2) {
      return this.isBodyPartBleeding(var1) || this.isBodyPartBleeding(var2);
   }

    void DrawUntexturedQuad(int var1, int var2, int var3, int var4, float var5, float var6, float var7, float var8) {
      SpriteRenderer.instance.renderi(nullptr, var1, var2, var3, var4, var5, var6, var7, var8, nullptr);
   }

    float getBodyPartHealth(BodyPartType var1) {
      return this.getBodyParts().get(BodyPartType.ToIndex(var1)).getHealth();
   }

    float getBodyPartHealth(int var1) {
      return this.getBodyParts().get(var1).getHealth();
   }

    std::string getBodyPartName(BodyPartType var1) {
      return BodyPartType.ToString(var1);
   }

    std::string getBodyPartName(int var1) {
      return BodyPartType.ToString(BodyPartType.FromIndex(var1));
   }

    float getHealth() {
      return this.getOverallBodyHealth();
   }

    float getInfectionLevel() {
      return this.InfectionLevel;
   }

    float getApparentInfectionLevel() {
    float var1 = this.getFakeInfectionLevel() > this.InfectionLevel ? this.getFakeInfectionLevel() : this.InfectionLevel;
      return this.getFoodSicknessLevel() > var1 ? this.getFoodSicknessLevel() : var1;
   }

    int getNumPartsBleeding() {
    int var1 = 0;

      for (int var2 = 0; var2 < BodyPartType.ToIndex(BodyPartType.MAX); var2++) {
         if (this.getBodyParts().get(var2).bleeding()) {
            var1++;
         }
      }

    return var1;
   }

    int getNumPartsScratched() {
    int var1 = 0;

      for (int var2 = 0; var2 < BodyPartType.ToIndex(BodyPartType.MAX); var2++) {
         if (this.getBodyParts().get(var2).scratched()) {
            var1++;
         }
      }

    return var1;
   }

    int getNumPartsBitten() {
    int var1 = 0;

      for (int var2 = 0; var2 < BodyPartType.ToIndex(BodyPartType.MAX); var2++) {
         if (this.getBodyParts().get(var2).bitten()) {
            var1++;
         }
      }

    return var1;
   }

    bool HasInjury() {
      for (int var1 = 0; var1 < BodyPartType.ToIndex(BodyPartType.MAX); var1++) {
         if (this.getBodyParts().get(var1).HasInjury()) {
    return true;
         }
      }

    return false;
   }

    bool IsBandaged(BodyPartType var1) {
      return this.getBodyParts().get(BodyPartType.ToIndex(var1)).bandaged();
   }

    bool IsDeepWounded(BodyPartType var1) {
      return this.getBodyParts().get(BodyPartType.ToIndex(var1)).deepWounded();
   }

    bool IsBandaged(int var1) {
      return this.getBodyParts().get(var1).bandaged();
   }

    bool IsBitten(BodyPartType var1) {
      return this.getBodyParts().get(BodyPartType.ToIndex(var1)).bitten();
   }

    bool IsBitten(int var1) {
      return this.getBodyParts().get(var1).bitten();
   }

    bool IsBleeding(BodyPartType var1) {
      return this.getBodyParts().get(BodyPartType.ToIndex(var1)).bleeding();
   }

    bool IsBleeding(int var1) {
      return this.getBodyParts().get(var1).bleeding();
   }

    bool IsBleedingStemmed(BodyPartType var1) {
      return this.getBodyParts().get(BodyPartType.ToIndex(var1)).IsBleedingStemmed();
   }

    bool IsBleedingStemmed(int var1) {
      return this.getBodyParts().get(var1).IsBleedingStemmed();
   }

    bool IsCortorised(BodyPartType var1) {
      return this.getBodyParts().get(BodyPartType.ToIndex(var1)).IsCortorised();
   }

    bool IsCortorised(int var1) {
      return this.getBodyParts().get(var1).IsCortorised();
   }

    bool IsInfected() {
      return this.IsInfected;
   }

    bool IsInfected(BodyPartType var1) {
      return this.getBodyParts().get(BodyPartType.ToIndex(var1)).IsInfected();
   }

    bool IsInfected(int var1) {
      return this.getBodyParts().get(var1).IsInfected();
   }

    bool IsFakeInfected(int var1) {
      return this.getBodyParts().get(var1).IsFakeInfected();
   }

    void DisableFakeInfection(int var1) {
      this.getBodyParts().get(var1).DisableFakeInfection();
   }

    bool IsScratched(BodyPartType var1) {
      return this.getBodyParts().get(BodyPartType.ToIndex(var1)).scratched();
   }

    bool IsCut(BodyPartType var1) {
      return this.getBodyParts().get(BodyPartType.ToIndex(var1)).getCutTime() > 0.0F;
   }

    bool IsScratched(int var1) {
      return this.getBodyParts().get(var1).scratched();
   }

    bool IsStitched(BodyPartType var1) {
      return this.getBodyParts().get(BodyPartType.ToIndex(var1)).stitched();
   }

    bool IsStitched(int var1) {
      return this.getBodyParts().get(var1).stitched();
   }

    bool IsWounded(BodyPartType var1) {
      return this.getBodyParts().get(BodyPartType.ToIndex(var1)).deepWounded();
   }

    bool IsWounded(int var1) {
      return this.getBodyParts().get(var1).deepWounded();
   }

    void RestoreToFullHealth() {
      for (int var1 = 0; var1 < BodyPartType.ToIndex(BodyPartType.MAX); var1++) {
         this.getBodyParts().get(var1).RestoreToFullHealth();
      }

      if (this.getParentChar() != nullptr && this.getParentChar().getStats() != nullptr) {
         this.getParentChar().getStats().resetStats();
      }

      this.setInfected(false);
      this.setIsFakeInfected(false);
      this.setOverallBodyHealth(100.0F);
      this.setInfectionLevel(0.0F);
      this.setFakeInfectionLevel(0.0F);
      this.setBoredomLevel(0.0F);
      this.setWetness(0.0F);
      this.setCatchACold(0.0F);
      this.setHasACold(false);
      this.setColdStrength(0.0F);
      this.setSneezeCoughActive(0);
      this.setSneezeCoughTime(0);
      this.setTemperature(37.0F);
      this.setUnhappynessLevel(0.0F);
      this.PoisonLevel = 0.0F;
      this.setFoodSicknessLevel(0.0F);
      this.Temperature = 37.0F;
      this.lastTemperature = this.Temperature;
      this.setInfectionTime(-1.0F);
      this.setInfectionMortalityDuration(-1.0F);
      if (this.thermoregulator != nullptr) {
         this.thermoregulator.reset();
      }
   }

    void SetBandaged(int var1, bool var2, float var3, bool var4, const std::string& var5) {
      this.getBodyParts().get(var1).setBandaged(var2, var3, var4, var5);
   }

    void SetBitten(BodyPartType var1, bool var2) {
      this.getBodyParts().get(BodyPartType.ToIndex(var1)).SetBitten(var2);
   }

    void SetBitten(int var1, bool var2) {
      this.getBodyParts().get(var1).SetBitten(var2);
   }

    void SetBitten(int var1, bool var2, bool var3) {
      this.getBodyParts().get(var1).SetBitten(var2, var3);
   }

    void SetBleeding(BodyPartType var1, bool var2) {
      this.getBodyParts().get(BodyPartType.ToIndex(var1)).setBleeding(var2);
   }

    void SetBleeding(int var1, bool var2) {
      this.getBodyParts().get(var1).setBleeding(var2);
   }

    void SetBleedingStemmed(BodyPartType var1, bool var2) {
      this.getBodyParts().get(BodyPartType.ToIndex(var1)).SetBleedingStemmed(var2);
   }

    void SetBleedingStemmed(int var1, bool var2) {
      this.getBodyParts().get(var1).SetBleedingStemmed(var2);
   }

    void SetCortorised(BodyPartType var1, bool var2) {
      this.getBodyParts().get(BodyPartType.ToIndex(var1)).SetCortorised(var2);
   }

    void SetCortorised(int var1, bool var2) {
      this.getBodyParts().get(var1).SetCortorised(var2);
   }

    BodyPart setScratchedWindow() {
    int var1 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.ForeArm_R) + 1);
      this.getBodyPart(BodyPartType.FromIndex(var1)).AddDamage(10.0F);
      this.getBodyPart(BodyPartType.FromIndex(var1)).SetScratchedWindow(true);
      return this.getBodyPart(BodyPartType.FromIndex(var1));
   }

    void SetScratched(BodyPartType var1, bool var2) {
      this.getBodyParts().get(BodyPartType.ToIndex(var1)).setScratched(var2, false);
   }

    void SetScratched(int var1, bool var2) {
      this.getBodyParts().get(var1).setScratched(var2, false);
   }

    void SetScratchedFromWeapon(int var1, bool var2) {
      this.getBodyParts().get(var1).SetScratchedWeapon(var2);
   }

    void SetCut(int var1, bool var2) {
      this.getBodyParts().get(var1).setCut(var2, false);
   }

    void SetWounded(BodyPartType var1, bool var2) {
      this.getBodyParts().get(BodyPartType.ToIndex(var1)).setDeepWounded(var2);
   }

    void SetWounded(int var1, bool var2) {
      this.getBodyParts().get(var1).setDeepWounded(var2);
   }

    void ShowDebugInfo() {
      if (this.getDamageModCount() > 0) {
         this.setDamageModCount(this.getDamageModCount() - 1);
      }
   }

    void UpdateBoredom() {
      if (!(this.getParentChar() instanceof IsoSurvivor)) {
         if (!(this.getParentChar() instanceof IsoPlayer) || !((IsoPlayer)this.getParentChar()).Asleep) {
            if (this.getParentChar().getCurrentSquare().isInARoom()) {
               if (!this.getParentChar().isReading()) {
                  this.setBoredomLevel((float)(this.getBoredomLevel() + ZomboidGlobals.BoredomIncreaseRate * GameTime.instance.getMultiplier()));
               } else {
                  this.setBoredomLevel((float)(this.getBoredomLevel() + ZomboidGlobals.BoredomIncreaseRate / 5.0 * GameTime.instance.getMultiplier()));
               }

               if (this.getParentChar().IsSpeaking() && !this.getParentChar().callOut) {
                  this.setBoredomLevel((float)(this.getBoredomLevel() - ZomboidGlobals.BoredomDecreaseRate * GameTime.instance.getMultiplier()));
               }

               if (this.getParentChar().getNumSurvivorsInVicinity() > 0) {
                  this.setBoredomLevel((float)(this.getBoredomLevel() - ZomboidGlobals.BoredomDecreaseRate * 0.1F * GameTime.instance.getMultiplier()));
               }
            } else if (this.getParentChar().getVehicle() != nullptr) {
    float var1 = this.getParentChar().getVehicle().getCurrentSpeedKmHour();
               if (Math.abs(var1) <= 0.1F) {
                  if (this.getParentChar().isReading()) {
                     this.setBoredomLevel((float)(this.getBoredomLevel() + ZomboidGlobals.BoredomIncreaseRate / 5.0 * GameTime.instance.getMultiplier()));
                  } else {
                     this.setBoredomLevel((float)(this.getBoredomLevel() + ZomboidGlobals.BoredomIncreaseRate * GameTime.instance.getMultiplier()));
                  }
               } else {
                  this.setBoredomLevel((float)(this.getBoredomLevel() - ZomboidGlobals.BoredomDecreaseRate * 0.5 * GameTime.instance.getMultiplier()));
               }
            } else {
               this.setBoredomLevel((float)(this.getBoredomLevel() - ZomboidGlobals.BoredomDecreaseRate * 0.1F * GameTime.instance.getMultiplier()));
            }

            if (this.getParentChar().getStats().Drunkenness > 20.0F) {
               this.setBoredomLevel((float)(this.getBoredomLevel() - ZomboidGlobals.BoredomDecreaseRate * 2.0 * GameTime.instance.getMultiplier()));
            }

            if (this.getParentChar().getStats().Panic > 5.0F) {
               this.setBoredomLevel(0.0F);
            }

            if (this.getBoredomLevel() > 100.0F) {
               this.setBoredomLevel(100.0F);
            }

            if (this.getBoredomLevel() < 0.0F) {
               this.setBoredomLevel(0.0F);
            }

            if (this.getUnhappynessLevel() > 100.0F) {
               this.setUnhappynessLevel(100.0F);
            }

            if (this.getUnhappynessLevel() < 0.0F) {
               this.setUnhappynessLevel(0.0F);
            }

            if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Bored) > 1 && !this.getParentChar().isReading()) {
               this.setUnhappynessLevel(
                  (float)(
                     this.getUnhappynessLevel()
                        + ZomboidGlobals.UnhappinessIncrease
                           * this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Bored)
                           * GameTime.instance.getMultiplier()
                  )
               );
            }

            if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Stress) > 1 && !this.getParentChar().isReading()) {
               this.setUnhappynessLevel(
                  (float)(
                     this.getUnhappynessLevel()
                        + ZomboidGlobals.UnhappinessIncrease
                           / 2.0
                           * this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Stress)
                           * GameTime.instance.getMultiplier()
                  )
               );
            }

            if (this.getParentChar().Traits.Smoker.isSet()) {
               this.getParentChar().setTimeSinceLastSmoke(this.getParentChar().getTimeSinceLastSmoke() + 1.0E-4F * GameTime.instance.getMultiplier());
               if (this.getParentChar().getTimeSinceLastSmoke() > 1.0F) {
    double var3 = Math.floor(this.getParentChar().getTimeSinceLastSmoke() / 10.0F) + 1.0;
                  if (var3 > 10.0) {
                     var3 = 10.0;
                  }

                  this.getParentChar()
                     .getStats()
                     .setStressFromCigarettes(
                        (float)(
                           this.getParentChar().getStats().getStressFromCigarettes()
                              + ZomboidGlobals.StressFromBiteOrScratch / 8.0 * var3 * GameTime.instance.getMultiplier()
                        )
                     );
               }
            }
         }
      }
   }

    float getUnhappynessLevel() {
      return this.UnhappynessLevel;
   }

    float getBoredomLevel() {
      return this.BoredomLevel;
   }

    void UpdateStrength() {
      if (this.getParentChar() == this.getParentChar()) {
    int var1 = 0;
         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 2) {
            var1++;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 3) {
            var1 += 2;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 4) {
            var1 += 2;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 2) {
            var1++;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 3) {
            var1 += 2;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 4) {
            var1 += 2;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) == 2) {
            var1++;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) == 3) {
            var1 += 2;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) == 4) {
            var1 += 3;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Bleeding) == 2) {
            var1++;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Bleeding) == 3) {
            var1++;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Bleeding) == 4) {
            var1++;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Injured) == 2) {
            var1++;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Injured) == 3) {
            var1 += 2;
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Injured) == 4) {
            var1 += 3;
         }

         this.getParentChar().setMaxWeight((int)(this.getParentChar().getMaxWeightBase() * this.getParentChar().getWeightMod()) - var1);
         if (this.getParentChar().getMaxWeight() < 0) {
            this.getParentChar().setMaxWeight(0);
         }

         if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.FoodEaten) > 0) {
            this.getParentChar().setMaxWeight(this.getParentChar().getMaxWeight() + 2);
         }

         if (this.getParentChar() instanceof IsoPlayer) {
            this.getParentChar().setMaxWeight((int)(this.getParentChar().getMaxWeight() * ((IsoPlayer)this.getParentChar()).getMaxWeightDelta()));
         }
      }
   }

    float pickMortalityDuration() {
    float var1 = 1.0F;
      if (this.getParentChar().Traits.Resilient.isSet()) {
         var1 = 1.25F;
      }

      if (this.getParentChar().Traits.ProneToIllness.isSet()) {
         var1 = 0.75F;
      }

      switch (SandboxOptions.instance.Lore.Mortality.getValue()) {
         case 1:
            return 0.0F;
         case 2:
            return Rand.Next(0.0F, 30.0F) / 3600.0F * var1;
         case 3:
            return Rand.Next(0.5F, 1.0F) / 60.0F * var1;
         case 4:
            return Rand.Next(3.0F, 12.0F) * var1;
         case 5:
            return Rand.Next(2.0F, 3.0F) * 24.0F * var1;
         case 6:
            return Rand.Next(1.0F, 2.0F) * 7.0F * 24.0F * var1;
         case 7:
            return -1.0F;
         default:
            return -1.0F;
      }
   }

    void Update() {
      if (!(this.getParentChar() instanceof IsoZombie)) {
         if (GameServer.bServer) {
            this.RestoreToFullHealth();
    uint8_t var13 = ((IsoPlayer)this.getParentChar()).bleedingLevel;
            if (var13 > 0) {
    float var17 = 1.0F / var13 * 200.0F * GameTime.instance.getInvMultiplier();
               if (Rand.Next((int)var17) < var17 * 0.3F) {
                  this.getParentChar().splatBloodFloor();
               }

               if (Rand.Next((int)var17) == 0) {
                  this.getParentChar().splatBloodFloor();
               }
            }
         } else if (GameClient.bClient && this.getParentChar() instanceof IsoPlayer && ((IsoPlayer)this.getParentChar()).bRemote) {
            if (this.getParentChar().isAlive()) {
               this.RestoreToFullHealth();
    uint8_t var12 = ((IsoPlayer)this.getParentChar()).bleedingLevel;
               if (var12 > 0) {
    float var16 = 1.0F / var12 * 200.0F * GameTime.instance.getInvMultiplier();
                  if (Rand.Next((int)var16) < var16 * 0.3F) {
                     this.getParentChar().splatBloodFloor();
                  }

                  if (Rand.Next((int)var16) == 0) {
                     this.getParentChar().splatBloodFloor();
                  }
               }
            }
         } else if (this.getParentChar().isGodMod()) {
            this.RestoreToFullHealth();
            ((IsoPlayer)this.getParentChar()).bleedingLevel = 0;
         } else if (this.getParentChar().isInvincible()) {
            this.setOverallBodyHealth(100.0F);

            for (int var11 = 0; var11 < BodyPartType.MAX.index(); var11++) {
               this.getBodyPart(BodyPartType.FromIndex(var11)).SetHealth(100.0F);
            }
         } else {
    float var1 = this.ParentChar.getStats().Pain;
    int var2 = this.getNumPartsBleeding() * 2;
            var2 += this.getNumPartsScratched();
            var2 += this.getNumPartsBitten() * 6;
            if (this.getHealth() >= 60.0F && var2 <= 3) {
               var2 = 0;
            }

            ((IsoPlayer)this.getParentChar()).bleedingLevel = (byte)var2;
            if (var2 > 0) {
    float var3 = 1.0F / var2 * 200.0F * GameTime.instance.getInvMultiplier();
               if (Rand.Next((int)var3) < var3 * 0.3F) {
                  this.getParentChar().splatBloodFloor();
               }

               if (Rand.Next((int)var3) == 0) {
                  this.getParentChar().splatBloodFloor();
               }
            }

            if (this.thermoregulator != nullptr) {
               this.thermoregulator.update();
            }

            this.UpdateWetness();
            this.UpdateCold();
            this.UpdateBoredom();
            this.UpdateStrength();
            this.UpdatePanicState();
            this.UpdateTemperatureState();
            this.UpdateIllness();
            if (this.getOverallBodyHealth() != 0.0F) {
               if (this.PoisonLevel == 0.0F && this.getFoodSicknessLevel() > 0.0F) {
                  this.setFoodSicknessLevel(this.getFoodSicknessLevel() - (float)(ZomboidGlobals.FoodSicknessDecrease * GameTime.instance.getMultiplier()));
               }

               if (!this.isInfected()) {
                  for (int var18 = 0; var18 < BodyPartType.ToIndex(BodyPartType.MAX); var18++) {
                     if (this.IsInfected(var18)) {
                        this.setInfected(true);
                        if (this.IsFakeInfected(var18)) {
                           this.DisableFakeInfection(var18);
                           this.setInfectionLevel(this.getFakeInfectionLevel());
                           this.setFakeInfectionLevel(0.0F);
                           this.setIsFakeInfected(false);
                           this.setReduceFakeInfection(false);
                        }
                     }
                  }

                  if (this.isInfected() && this.getInfectionTime() < 0.0F && SandboxOptions.instance.Lore.Mortality.getValue() != 7) {
                     this.setInfectionTime(this.getCurrentTimeForInfection());
                     this.setInfectionMortalityDuration(this.pickMortalityDuration());
                  }
               }

               if (!this.isInfected() && !this.isIsFakeInfected()) {
                  for (int var19 = 0; var19 < BodyPartType.ToIndex(BodyPartType.MAX); var19++) {
                     if (this.IsFakeInfected(var19)) {
                        this.setIsFakeInfected(true);
                        break;
                     }
                  }
               }

               if (this.isIsFakeInfected() && !this.isReduceFakeInfection() && this.getParentChar().getReduceInfectionPower() == 0.0F) {
                  this.setFakeInfectionLevel(this.getFakeInfectionLevel() + this.getInfectionGrowthRate() * GameTime.instance.getMultiplier());
                  if (this.getFakeInfectionLevel() > 100.0F) {
                     this.setFakeInfectionLevel(100.0F);
                     this.setReduceFakeInfection(true);
                  }
               }

    Stats var10000 = this.ParentChar.getStats();
               var10000.Drunkenness = var10000.Drunkenness - this.getDrunkReductionValue() * GameTime.instance.getMultiplier();
               if (this.getParentChar().getStats().Drunkenness < 0.0F) {
                  this.ParentChar.getStats().Drunkenness = 0.0F;
               }

    float var20 = 0.0F;
               if (this.getHealthFromFoodTimer() > 0.0F) {
                  var20 += this.getHealthFromFood() * GameTime.instance.getMultiplier();
                  this.setHealthFromFoodTimer(this.getHealthFromFoodTimer() - 1.0F * GameTime.instance.getMultiplier());
               }

    uint8_t var4 = 0;
               if (this.getParentChar() == this.getParentChar()
                  && (
                     this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 2
                        || this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) == 2
                        || this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 2
                  )) {
                  var4 = 1;
               }

               if (this.getParentChar() == this.getParentChar()
                  && (
                     this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 3
                        || this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) == 3
                        || this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 3
                  )) {
                  var4 = 2;
               }

               if (this.getParentChar() == this.getParentChar()
                  && (
                     this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 4
                        || this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 4
                  )) {
                  var4 = 3;
               }

               if (this.getParentChar().isAsleep()) {
                  var4 = -1;
               }

               switch (var4) {
                  case 0:
                     var20 += this.getStandardHealthAddition() * GameTime.instance.getMultiplier();
                     break;
                  case 1:
                     var20 += this.getReducedHealthAddition() * GameTime.instance.getMultiplier();
                     break;
                  case 2:
                     var20 += this.getSeverlyReducedHealthAddition() * GameTime.instance.getMultiplier();
                     break;
                  case 3:
                     var20 += 0.0F;
               }

               if (this.getParentChar().isAsleep()) {
                  if (GameClient.bClient) {
                     var20 += 15.0F * GameTime.instance.getGameWorldSecondsSinceLastUpdate() / 3600.0F;
                  } else {
                     var20 += this.getSleepingHealthAddition() * GameTime.instance.getMultiplier();
                  }

                  if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 4
                     || this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 4) {
                     var20 = 0.0F;
                  }
               }

               this.AddGeneralHealth(var20);
               var20 = 0.0F;
    float var28 = 0.0F;
    float var5 = 0.0F;
    float var6 = 0.0F;
    float var7 = 0.0F;
    float var8 = 0.0F;
    float var9 = 0.0F;
               if (this.PoisonLevel > 0.0F) {
                  if (this.PoisonLevel > 10.0F && this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) >= 1) {
                     var28 = 0.0035F * Math.min(this.PoisonLevel / 10.0F, 3.0F) * GameTime.instance.getMultiplier();
                     var20 += var28;
                  }

    float var10 = 0.0F;
                  if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.FoodEaten) > 0) {
                     var10 = 1.5E-4F * this.getParentChar().getMoodles().getMoodleLevel(MoodleType.FoodEaten);
                  }

                  this.PoisonLevel = (float)(this.PoisonLevel - (var10 + ZomboidGlobals.PoisonLevelDecrease * GameTime.instance.getMultiplier()));
                  if (this.PoisonLevel < 0.0F) {
                     this.PoisonLevel = 0.0F;
                  }

                  this.setFoodSicknessLevel(
                     this.getFoodSicknessLevel()
                        + this.getInfectionGrowthRate() * (2 + Math.round(this.PoisonLevel / 10.0F)) * GameTime.instance.getMultiplier()
                  );
                  if (this.getFoodSicknessLevel() > 100.0F) {
                     this.setFoodSicknessLevel(100.0F);
                  }
               }

               if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 4) {
                  var5 = this.getHealthReductionFromSevereBadMoodles() / 50.0F * GameTime.instance.getMultiplier();
                  var20 += var5;
               }

               if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) == 4 && this.FoodSicknessLevel > this.InfectionLevel) {
                  var6 = this.getHealthReductionFromSevereBadMoodles() * GameTime.instance.getMultiplier();
                  var20 += var6;
               }

               if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Bleeding) == 4) {
                  var7 = this.getHealthReductionFromSevereBadMoodles() * GameTime.instance.getMultiplier();
                  var20 += var7;
               }

               if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 4) {
                  var8 = this.getHealthReductionFromSevereBadMoodles() / 10.0F * GameTime.instance.getMultiplier();
                  var20 += var8;
               }

               if (this.getParentChar().getMoodles().getMoodleLevel(MoodleType.HeavyLoad) > 2
                  && this.getParentChar().getVehicle() == nullptr
                  && !this.getParentChar().isAsleep()
                  && !this.getParentChar().isSitOnGround()
                  && this.getThermoregulator().getMetabolicTarget() != Metabolics.SeatedResting.getMet()
                  && this.getHealth() > 75.0F
                  && Rand.Next(Rand.AdjustForFramerate(10)) == 0) {
                  var9 = this.getHealthReductionFromSevereBadMoodles()
                     / ((5 - this.getParentChar().getMoodles().getMoodleLevel(MoodleType.HeavyLoad)) / 10.0F)
                     * GameTime.instance.getMultiplier();
                  var20 += var9;
               }

               this.ReduceGeneralHealth(var20);
    IsoGameCharacter var37 = this.getParentChar();
               if (var28 > 0.0F) {
                  LuaEventManager.triggerEvent("OnPlayerGetDamage", var37, "POISON", var28);
               }

               if (var5 > 0.0F) {
                  LuaEventManager.triggerEvent("OnPlayerGetDamage", var37, "HUNGRY", var5);
               }

               if (var6 > 0.0F) {
                  LuaEventManager.triggerEvent("OnPlayerGetDamage", var37, "SICK", var6);
               }

               if (var7 > 0.0F) {
                  LuaEventManager.triggerEvent("OnPlayerGetDamage", var37, "BLEEDING", var7);
               }

               if (var8 > 0.0F) {
                  LuaEventManager.triggerEvent("OnPlayerGetDamage", var37, "THIRST", var8);
               }

               if (var9 > 0.0F) {
                  LuaEventManager.triggerEvent("OnPlayerGetDamage", var37, "HEAVYLOAD", var9);
               }

               if (this.ParentChar.getPainEffect() > 0.0F) {
                  var10000 = this.ParentChar.getStats();
                  var10000.Pain = var10000.Pain - 0.023333333F * (GameTime.getInstance().getMultiplier() / 1.6F);
                  this.ParentChar.setPainEffect(this.ParentChar.getPainEffect() - GameTime.getInstance().getMultiplier() / 1.6F);
               } else {
                  this.ParentChar.setPainDelta(0.0F);
                  var20 = 0.0F;

                  for (int var29 = 0; var29 < BodyPartType.ToIndex(BodyPartType.MAX); var29++) {
                     var20 += this.getBodyParts().get(var29).getPain() * BodyPartType.getPainModifyer(var29);
                  }

                  var20 -= this.getPainReduction();
                  if (var20 > this.ParentChar.getStats().Pain) {
                     var10000 = this.ParentChar.getStats();
                     var10000.Pain = var10000.Pain + (var20 - this.ParentChar.getStats().Pain) / 500.0F;
                  } else {
                     this.ParentChar.getStats().Pain = var20;
                  }
               }

               this.setPainReduction(this.getPainReduction() - 0.005F * GameTime.getInstance().getMultiplier());
               if (this.getPainReduction() < 0.0F) {
                  this.setPainReduction(0.0F);
               }

               if (this.getParentChar().getStats().Pain > 100.0F) {
                  this.ParentChar.getStats().Pain = 100.0F;
               }

               if (this.isInfected()) {
    int var24 = SandboxOptions.instance.Lore.Mortality.getValue();
                  if (var24 == 1) {
                     this.ReduceGeneralHealth(110.0F);
                     LuaEventManager.triggerEvent("OnPlayerGetDamage", this.ParentChar, "INFECTION", 110);
                     this.setInfectionLevel(100.0F);
                  } else if (var24 != 7) {
    float var30 = this.getCurrentTimeForInfection();
                     if (this.InfectionMortalityDuration < 0.0F) {
                        this.InfectionMortalityDuration = this.pickMortalityDuration();
                     }

                     if (this.InfectionTime < 0.0F) {
                        this.InfectionTime = var30;
                     }

                     if (this.InfectionTime > var30) {
                        this.InfectionTime = var30;
                     }

                     var5 = (var30 - this.InfectionTime) / this.InfectionMortalityDuration;
                     var5 = Math.min(var5, 1.0F);
                     this.setInfectionLevel(var5 * 100.0F);
                     if (var5 == 1.0F) {
                        this.ReduceGeneralHealth(110.0F);
                        LuaEventManager.triggerEvent("OnPlayerGetDamage", this.ParentChar, "INFECTION", 110);
                     } else {
                        var5 *= var5;
                        var5 *= var5;
                        var6 = (1.0F - var5) * 100.0F;
                        var7 = this.getOverallBodyHealth() - var6;
                        if (var7 > 0.0F && var6 <= 99.0F) {
                           this.ReduceGeneralHealth(var7);
                           LuaEventManager.triggerEvent("OnPlayerGetDamage", this.ParentChar, "INFECTION", var7);
                        }
                     }
                  }
               }

               for (int var25 = 0; var25 < BodyPartType.ToIndex(BodyPartType.MAX); var25++) {
                  this.getBodyParts().get(var25).DamageUpdate();
               }

               this.calculateOverallHealth();
               if (this.getOverallBodyHealth() <= 0.0F) {
                  if (GameClient.bClient && this.getParentChar() instanceof IsoPlayer && !((IsoPlayer)this.getParentChar()).bRemote) {
                     GameClient.sendPlayerDamage((IsoPlayer)this.getParentChar());
                  }

                  if (this.isIsOnFire()) {
                     this.setBurntToDeath(true);

                     for (int var26 = 0; var26 < BodyPartType.ToIndex(BodyPartType.MAX); var26++) {
                        this.getBodyParts().get(var26).SetHealth(Rand.Next(90));
                     }
                  } else {
                     this.setBurntToDeath(false);
                  }
               }

               if (this.isReduceFakeInfection() && this.getOverallBodyHealth() > 0.0F) {
                  this.setFakeInfectionLevel(this.getFakeInfectionLevel() - this.getInfectionGrowthRate() * GameTime.instance.getMultiplier() * 2.0F);
               }

               if (this.getParentChar().getReduceInfectionPower() > 0.0F && this.getOverallBodyHealth() > 0.0F) {
                  this.setFakeInfectionLevel(this.getFakeInfectionLevel() - this.getInfectionGrowthRate() * GameTime.instance.getMultiplier());
                  this.getParentChar()
                     .setReduceInfectionPower(
                        this.getParentChar().getReduceInfectionPower() - this.getInfectionGrowthRate() * GameTime.instance.getMultiplier()
                     );
                  if (this.getParentChar().getReduceInfectionPower() < 0.0F) {
                     this.getParentChar().setReduceInfectionPower(0.0F);
                  }
               }

               if (this.getFakeInfectionLevel() <= 0.0F) {
                  for (int var27 = 0; var27 < BodyPartType.ToIndex(BodyPartType.MAX); var27++) {
                     this.getBodyParts().get(var27).SetFakeInfected(false);
                  }

                  this.setIsFakeInfected(false);
                  this.setFakeInfectionLevel(0.0F);
                  this.setReduceFakeInfection(false);
               }

               if (var1 == this.ParentChar.getStats().Pain) {
                  var10000 = this.ParentChar.getStats();
                  var10000.Pain = (float)(var10000.Pain - 0.25 * (GameTime.getInstance().getMultiplier() / 1.6F));
               }

               if (this.ParentChar.getStats().Pain < 0.0F) {
                  this.ParentChar.getStats().Pain = 0.0F;
               }
            }
         }
      }
   }

    void calculateOverallHealth() {
    float var1 = 0.0F;

      for (int var2 = 0; var2 < BodyPartType.ToIndex(BodyPartType.MAX); var2++) {
    BodyPart var3 = this.getBodyParts().get(var2);
         var1 += (100.0F - var3.getHealth()) * BodyPartType.getDamageModifyer(var2);
      }

      var1 += this.getDamageFromPills();
      if (var1 > 100.0F) {
         var1 = 100.0F;
      }

      this.setOverallBodyHealth(100.0F - var1);
   }

    static float getSicknessFromCorpsesRate(int var0) {
      if (SandboxOptions.instance.DecayingCorpseHealthImpact.getValue() == 1) {
         return 0.0F;
      } else if (var0 > 5) {
    float var1 = (float)ZomboidGlobals.FoodSicknessDecrease * 0.07F;
         switch (SandboxOptions.instance.DecayingCorpseHealthImpact.getValue()) {
            case 2:
               var1 = (float)ZomboidGlobals.FoodSicknessDecrease * 0.01F;
               break;
            case 4:
               var1 = (float)ZomboidGlobals.FoodSicknessDecrease * 0.11F;
         }

    int var2 = Math.min(var0 - 5, 20);
         return var1 * var2;
      } else {
         return 0.0F;
      }
   }

    void UpdateIllness() {
      if (SandboxOptions.instance.DecayingCorpseHealthImpact.getValue() != 1) {
    int var1 = FliesSound.instance.getCorpseCount(this.getParentChar());
    float var2 = getSicknessFromCorpsesRate(var1);
         if (var2 > 0.0F) {
            this.setFoodSicknessLevel(this.getFoodSicknessLevel() + var2 * GameTime.getInstance().getMultiplier());
         }
      }
   }

    void UpdateTemperatureState() {
    float var1 = 0.06F;
      if (this.getParentChar() instanceof IsoPlayer) {
         if (this.ColdDamageStage > 0.0F) {
    float var2 = 100.0F - this.ColdDamageStage * 100.0F;
            if (this.OverallBodyHealth > var2) {
               this.ReduceGeneralHealth(this.OverallBodyHealth - var2);
            }
         }

         ((IsoPlayer)this.getParentChar()).setMoveSpeed(var1);
      }
   }

    float getDamageFromPills() {
      if (this.getParentChar() instanceof IsoPlayer) {
    IsoPlayer var1 = (IsoPlayer)this.getParentChar();
         if (var1.getSleepingPillsTaken() == 10) {
            return 40.0F;
         }

         if (var1.getSleepingPillsTaken() == 11) {
            return 80.0F;
         }

         if (var1.getSleepingPillsTaken() >= 12) {
            return 100.0F;
         }
      }

      return 0.0F;
   }

    bool UseBandageOnMostNeededPart() {
    uint8_t var1 = 0;
    BodyPart var2 = nullptr;

      for (int var3 = 0; var3 < this.getBodyParts().size(); var3++) {
    uint8_t var4 = 0;
         if (!this.getBodyParts().get(var3).bandaged()) {
            if (this.getBodyParts().get(var3).bleeding()) {
               var4 += 100;
            }

            if (this.getBodyParts().get(var3).scratched()) {
               var4 += 50;
            }

            if (this.getBodyParts().get(var3).bitten()) {
               var4 += 50;
            }

            if (var4 > var1) {
               var1 = var4;
               var2 = this.getBodyParts().get(var3);
            }
         }
      }

      if (var1 > 0 && var2 != nullptr) {
         var2.setBandaged(true, 10.0F);
    return true;
      } else {
    return false;
      }
   }

   public std::vector<BodyPart> getBodyParts() {
      return this.BodyParts;
   }

    int getDamageModCount() {
      return this.DamageModCount;
   }

    void setDamageModCount(int var1) {
      this.DamageModCount = var1;
   }

    float getInfectionGrowthRate() {
      return this.InfectionGrowthRate;
   }

    void setInfectionGrowthRate(float var1) {
      this.InfectionGrowthRate = var1;
   }

    void setInfectionLevel(float var1) {
      this.InfectionLevel = var1;
   }

    bool isInfected() {
      return this.IsInfected;
   }

    void setInfected(bool var1) {
      this.IsInfected = var1;
   }

    float getInfectionTime() {
      return this.InfectionTime;
   }

    void setInfectionTime(float var1) {
      this.InfectionTime = var1;
   }

    float getInfectionMortalityDuration() {
      return this.InfectionMortalityDuration;
   }

    void setInfectionMortalityDuration(float var1) {
      this.InfectionMortalityDuration = var1;
   }

    float getCurrentTimeForInfection() {
      return this.getParentChar() instanceof IsoPlayer
         ? (float)((IsoPlayer)this.getParentChar()).getHoursSurvived()
         : (float)GameTime.getInstance().getWorldAgeHours();
   }

    bool isInf() {
      return this.IsInfected;
   }

    void setInf(bool var1) {
      this.IsInfected = var1;
   }

    float getFakeInfectionLevel() {
      return this.FakeInfectionLevel;
   }

    void setFakeInfectionLevel(float var1) {
      this.FakeInfectionLevel = var1;
   }

    bool isIsFakeInfected() {
      return this.IsFakeInfected;
   }

    void setIsFakeInfected(bool var1) {
      this.IsFakeInfected = var1;
      this.getBodyParts().get(0).SetFakeInfected(var1);
   }

    float getOverallBodyHealth() {
      return this.OverallBodyHealth;
   }

    void setOverallBodyHealth(float var1) {
      this.OverallBodyHealth = var1;
   }

    float getStandardHealthAddition() {
      return this.StandardHealthAddition;
   }

    void setStandardHealthAddition(float var1) {
      this.StandardHealthAddition = var1;
   }

    float getReducedHealthAddition() {
      return this.ReducedHealthAddition;
   }

    void setReducedHealthAddition(float var1) {
      this.ReducedHealthAddition = var1;
   }

    float getSeverlyReducedHealthAddition() {
      return this.SeverlyReducedHealthAddition;
   }

    void setSeverlyReducedHealthAddition(float var1) {
      this.SeverlyReducedHealthAddition = var1;
   }

    float getSleepingHealthAddition() {
      return this.SleepingHealthAddition;
   }

    void setSleepingHealthAddition(float var1) {
      this.SleepingHealthAddition = var1;
   }

    float getHealthFromFood() {
      return this.HealthFromFood;
   }

    void setHealthFromFood(float var1) {
      this.HealthFromFood = var1;
   }

    float getHealthReductionFromSevereBadMoodles() {
      return this.HealthReductionFromSevereBadMoodles;
   }

    void setHealthReductionFromSevereBadMoodles(float var1) {
      this.HealthReductionFromSevereBadMoodles = var1;
   }

    int getStandardHealthFromFoodTime() {
      return this.StandardHealthFromFoodTime;
   }

    void setStandardHealthFromFoodTime(int var1) {
      this.StandardHealthFromFoodTime = var1;
   }

    float getHealthFromFoodTimer() {
      return this.HealthFromFoodTimer;
   }

    void setHealthFromFoodTimer(float var1) {
      this.HealthFromFoodTimer = var1;
   }

    void setBoredomLevel(float var1) {
      this.BoredomLevel = var1;
   }

    float getBoredomDecreaseFromReading() {
      return this.BoredomDecreaseFromReading;
   }

    void setBoredomDecreaseFromReading(float var1) {
      this.BoredomDecreaseFromReading = var1;
   }

    float getInitialThumpPain() {
      return this.InitialThumpPain;
   }

    void setInitialThumpPain(float var1) {
      this.InitialThumpPain = var1;
   }

    float getInitialScratchPain() {
      return this.InitialScratchPain;
   }

    void setInitialScratchPain(float var1) {
      this.InitialScratchPain = var1;
   }

    float getInitialBitePain() {
      return this.InitialBitePain;
   }

    void setInitialBitePain(float var1) {
      this.InitialBitePain = var1;
   }

    float getInitialWoundPain() {
      return this.InitialWoundPain;
   }

    void setInitialWoundPain(float var1) {
      this.InitialWoundPain = var1;
   }

    float getContinualPainIncrease() {
      return this.ContinualPainIncrease;
   }

    void setContinualPainIncrease(float var1) {
      this.ContinualPainIncrease = var1;
   }

    float getPainReductionFromMeds() {
      return this.PainReductionFromMeds;
   }

    void setPainReductionFromMeds(float var1) {
      this.PainReductionFromMeds = var1;
   }

    float getStandardPainReductionWhenWell() {
      return this.StandardPainReductionWhenWell;
   }

    void setStandardPainReductionWhenWell(float var1) {
      this.StandardPainReductionWhenWell = var1;
   }

    int getOldNumZombiesVisible() {
      return this.OldNumZombiesVisible;
   }

    void setOldNumZombiesVisible(int var1) {
      this.OldNumZombiesVisible = var1;
   }

    int getCurrentNumZombiesVisible() {
      return this.CurrentNumZombiesVisible;
   }

    void setCurrentNumZombiesVisible(int var1) {
      this.CurrentNumZombiesVisible = var1;
   }

    float getPanicIncreaseValue() {
      return this.PanicIncreaseValue;
   }

    float getPanicIncreaseValueFrame() {
      return this.PanicIncreaseValueFrame;
   }

    void setPanicIncreaseValue(float var1) {
      this.PanicIncreaseValue = var1;
   }

    float getPanicReductionValue() {
      return this.PanicReductionValue;
   }

    void setPanicReductionValue(float var1) {
      this.PanicReductionValue = var1;
   }

    float getDrunkIncreaseValue() {
      return this.DrunkIncreaseValue;
   }

    void setDrunkIncreaseValue(float var1) {
      this.DrunkIncreaseValue = var1;
   }

    float getDrunkReductionValue() {
      return this.DrunkReductionValue;
   }

    void setDrunkReductionValue(float var1) {
      this.DrunkReductionValue = var1;
   }

    bool isIsOnFire() {
      return this.IsOnFire;
   }

    void setIsOnFire(bool var1) {
      this.IsOnFire = var1;
   }

    bool isBurntToDeath() {
      return this.BurntToDeath;
   }

    void setBurntToDeath(bool var1) {
      this.BurntToDeath = var1;
   }

    void setWetness(float var1) {
    float var2 = 0.0F;
      if (this.BodyParts.size() > 0) {
         for (int var4 = 0; var4 < this.BodyParts.size(); var4++) {
    BodyPart var3 = this.BodyParts.get(var4);
            var3.setWetness(var1);
            var2 += var3.getWetness();
         }

         var2 /= this.BodyParts.size();
      }

      this.Wetness = PZMath.clamp(var2, 0.0F, 100.0F);
   }

    float getCatchACold() {
      return this.CatchACold;
   }

    void setCatchACold(float var1) {
      this.CatchACold = var1;
   }

    bool isHasACold() {
      return this.HasACold;
   }

    void setHasACold(bool var1) {
      this.HasACold = var1;
   }

    void setColdStrength(float var1) {
      this.ColdStrength = var1;
   }

    float getColdProgressionRate() {
      return this.ColdProgressionRate;
   }

    void setColdProgressionRate(float var1) {
      this.ColdProgressionRate = var1;
   }

    int getTimeToSneezeOrCough() {
      return this.TimeToSneezeOrCough;
   }

    void setTimeToSneezeOrCough(int var1) {
      this.TimeToSneezeOrCough = var1;
   }

    int getMildColdSneezeTimerMin() {
      return this.MildColdSneezeTimerMin;
   }

    void setMildColdSneezeTimerMin(int var1) {
      this.MildColdSneezeTimerMin = var1;
   }

    int getMildColdSneezeTimerMax() {
      return this.MildColdSneezeTimerMax;
   }

    void setMildColdSneezeTimerMax(int var1) {
      this.MildColdSneezeTimerMax = var1;
   }

    int getColdSneezeTimerMin() {
      return this.ColdSneezeTimerMin;
   }

    void setColdSneezeTimerMin(int var1) {
      this.ColdSneezeTimerMin = var1;
   }

    int getColdSneezeTimerMax() {
      return this.ColdSneezeTimerMax;
   }

    void setColdSneezeTimerMax(int var1) {
      this.ColdSneezeTimerMax = var1;
   }

    int getNastyColdSneezeTimerMin() {
      return this.NastyColdSneezeTimerMin;
   }

    void setNastyColdSneezeTimerMin(int var1) {
      this.NastyColdSneezeTimerMin = var1;
   }

    int getNastyColdSneezeTimerMax() {
      return this.NastyColdSneezeTimerMax;
   }

    void setNastyColdSneezeTimerMax(int var1) {
      this.NastyColdSneezeTimerMax = var1;
   }

    int getSneezeCoughActive() {
      return this.SneezeCoughActive;
   }

    void setSneezeCoughActive(int var1) {
      this.SneezeCoughActive = var1;
   }

    int getSneezeCoughTime() {
      return this.SneezeCoughTime;
   }

    void setSneezeCoughTime(int var1) {
      this.SneezeCoughTime = var1;
   }

    int getSneezeCoughDelay() {
      return this.SneezeCoughDelay;
   }

    void setSneezeCoughDelay(int var1) {
      this.SneezeCoughDelay = var1;
   }

    void setUnhappynessLevel(float var1) {
      this.UnhappynessLevel = var1;
   }

    IsoGameCharacter getParentChar() {
      return this.ParentChar;
   }

    void setParentChar(IsoGameCharacter var1) {
      this.ParentChar = var1;
   }

    float getTemperature() {
      return this.Temperature;
   }

    void setTemperature(float var1) {
      this.lastTemperature = this.Temperature;
      this.Temperature = var1;
   }

    float getTemperatureChangeTick() {
      return this.Temperature - this.lastTemperature;
   }

    void setPoisonLevel(float var1) {
      this.PoisonLevel = var1;
   }

    float getPoisonLevel() {
      return this.PoisonLevel;
   }

    float getFoodSicknessLevel() {
      return this.FoodSicknessLevel;
   }

    void setFoodSicknessLevel(float var1) {
      this.FoodSicknessLevel = Math.max(var1, 0.0F);
   }

    bool isReduceFakeInfection() {
      return this.reduceFakeInfection;
   }

    void setReduceFakeInfection(bool var1) {
      this.reduceFakeInfection = var1;
   }

    void AddRandomDamage() {
    BodyPart var1 = this.getBodyParts().get(Rand.Next(this.getBodyParts().size()));
      switch (Rand.Next(4)) {
         case 0:
            var1.generateDeepWound();
            if (Rand.Next(4) == 0) {
               var1.setInfectedWound(true);
            }
            break;
         case 1:
            var1.generateDeepShardWound();
            if (Rand.Next(4) == 0) {
               var1.setInfectedWound(true);
            }
            break;
         case 2:
            var1.setFractureTime(Rand.Next(30, 50));
            break;
         case 3:
            var1.setBurnTime(Rand.Next(30, 50));
      }
   }

    float getPainReduction() {
      return this.painReduction;
   }

    void setPainReduction(float var1) {
      this.painReduction = var1;
   }

    float getColdReduction() {
      return this.coldReduction;
   }

    void setColdReduction(float var1) {
      this.coldReduction = var1;
   }

    int getRemotePainLevel() {
      return this.RemotePainLevel;
   }

    void setRemotePainLevel(int var1) {
      this.RemotePainLevel = var1;
   }

    float getColdDamageStage() {
      return this.ColdDamageStage;
   }

    void setColdDamageStage(float var1) {
      this.ColdDamageStage = var1;
   }

    Thermoregulator getThermoregulator() {
      return this.thermoregulator;
   }

    void decreaseBodyWetness(float var1) {
    float var2 = 0.0F;
      if (this.BodyParts.size() > 0) {
         for (int var4 = 0; var4 < this.BodyParts.size(); var4++) {
    BodyPart var3 = this.BodyParts.get(var4);
            var3.setWetness(var3.getWetness() - var1);
            var2 += var3.getWetness();
         }

         var2 /= this.BodyParts.size();
      }

      this.Wetness = PZMath.clamp(var2, 0.0F, 100.0F);
   }

    void increaseBodyWetness(float var1) {
    float var2 = 0.0F;
      if (this.BodyParts.size() > 0) {
         for (int var4 = 0; var4 < this.BodyParts.size(); var4++) {
    BodyPart var3 = this.BodyParts.get(var4);
            var3.setWetness(var3.getWetness() + var1);
            var2 += var3.getWetness();
         }

         var2 /= this.BodyParts.size();
      }

      this.Wetness = PZMath.clamp(var2, 0.0F, 100.0F);
   }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
