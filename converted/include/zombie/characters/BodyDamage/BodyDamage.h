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
#include "zombie/audio/parameters/ParameterZombieState.h"
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class BodyDamage {
public:
 public ArrayList<BodyPart> BodyParts = new ArrayList<>(18);
 public ArrayList<BodyPartLast> BodyPartsLastState = new ArrayList<>(18);
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

 public BodyDamage(IsoGameCharacter ParentCharacter) {
 this->BodyParts.add(new BodyPart(BodyPartType.Hand_L, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.Hand_R, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.ForeArm_L, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.ForeArm_R, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.UpperArm_L, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.UpperArm_R, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.Torso_Upper, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.Torso_Lower, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.Head, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.Neck, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.Groin, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.UpperLeg_L, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.UpperLeg_R, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.LowerLeg_L, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.LowerLeg_R, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.Foot_L, ParentCharacter);
 this->BodyParts.add(new BodyPart(BodyPartType.Foot_R, ParentCharacter);

 for (BodyPart bodyPart : this->BodyParts) {
 this->BodyPartsLastState.add(std::make_unique<BodyPartLast>());
 }

 this->RestoreToFullHealth();
 this->ParentChar = ParentCharacter;
 if (this->ParentChar instanceof IsoPlayer) {
 this->thermoregulator = new Thermoregulator(this);
 }

 this->setBodyPartsLastState();
 }

 BodyPart getBodyPart(BodyPartType type) {
 return this->BodyParts.get(BodyPartType.ToIndex(type);
 }

 BodyPartLast getBodyPartsLastState(BodyPartType type) {
 return this->BodyPartsLastState.get(BodyPartType.ToIndex(type);
 }

 void setBodyPartsLastState() {
 for (int int0 = 0; int0 < this->getBodyParts().size(); int0++) {
 BodyPart bodyPart = this->getBodyParts().get(int0);
 BodyPartLast bodyPartLast = this->BodyPartsLastState.get(int0);
 bodyPartLast.copy(bodyPart);
 }
 }

 void load(ByteBuffer input, int WorldVersion) {
 for (int int0 = 0; int0 < this->getBodyParts().size(); int0++) {
 BodyPart bodyPart = this->getBodyParts().get(int0);
 bodyPart.SetBitten(input.get() == 1);
 bodyPart.setScratched(input.get() == 1, false);
 bodyPart.setBandaged(input.get() == 1, 0.0F);
 bodyPart.setBleeding(input.get() == 1);
 bodyPart.setDeepWounded(input.get() == 1);
 bodyPart.SetFakeInfected(input.get() == 1);
 bodyPart.SetInfected(input.get() == 1);
 bodyPart.SetHealth(input.getFloat());
 if (WorldVersion >= 37 && WorldVersion <= 43) {
 input.getInt();
 }

 if (WorldVersion >= 44) {
 if (bodyPart.bandaged()) {
 bodyPart.setBandageLife(input.getFloat());
 }

 bodyPart.setInfectedWound(input.get() == 1);
 if (bodyPart.isInfectedWound()) {
 bodyPart.setWoundInfectionLevel(input.getFloat());
 }

 bodyPart.setBiteTime(input.getFloat());
 bodyPart.setScratchTime(input.getFloat());
 bodyPart.setBleedingTime(input.getFloat());
 bodyPart.setAlcoholLevel(input.getFloat());
 bodyPart.setAdditionalPain(input.getFloat());
 bodyPart.setDeepWoundTime(input.getFloat());
 bodyPart.setHaveGlass(input.get() == 1);
 bodyPart.setGetBandageXp(input.get() == 1);
 if (WorldVersion >= 48) {
 bodyPart.setStitched(input.get() == 1);
 bodyPart.setStitchTime(input.getFloat());
 }

 bodyPart.setGetStitchXp(input.get() == 1);
 bodyPart.setGetSplintXp(input.get() == 1);
 bodyPart.setFractureTime(input.getFloat());
 bodyPart.setSplint(input.get() == 1, 0.0F);
 if (bodyPart.isSplint()) {
 bodyPart.setSplintFactor(input.getFloat());
 }

 bodyPart.setHaveBullet(input.get() == 1, 0);
 bodyPart.setBurnTime(input.getFloat());
 bodyPart.setNeedBurnWash(input.get() == 1);
 bodyPart.setLastTimeBurnWash(input.getFloat());
 bodyPart.setSplintItem(GameWindow.ReadString(input);
 bodyPart.setBandageType(GameWindow.ReadString(input);
 bodyPart.setCutTime(input.getFloat());
 if (WorldVersion >= 153) {
 bodyPart.setWetness(input.getFloat());
 }

 if (WorldVersion >= 167) {
 bodyPart.setStiffness(input.getFloat());
 }
 }
 }

 this->setBodyPartsLastState();
 this->setInfectionLevel(input.getFloat());
 this->setFakeInfectionLevel(input.getFloat());
 this->setWetness(input.getFloat());
 this->setCatchACold(input.getFloat());
 this->setHasACold(input.get() == 1);
 this->setColdStrength(input.getFloat());
 this->setUnhappynessLevel(input.getFloat());
 this->setBoredomLevel(input.getFloat());
 this->setFoodSicknessLevel(input.getFloat());
 this->PoisonLevel = input.getFloat();
 float float0 = input.getFloat();
 this->setTemperature(float0);
 this->setReduceFakeInfection(input.get() == 1);
 this->setHealthFromFoodTimer(input.getFloat());
 this->painReduction = input.getFloat();
 this->coldReduction = input.getFloat();
 this->InfectionTime = input.getFloat();
 this->InfectionMortalityDuration = input.getFloat();
 this->ColdDamageStage = input.getFloat();
 this->calculateOverallHealth();
 if (WorldVersion >= 153 && input.get() == 1) {
 if (this->thermoregulator != nullptr) {
 this->thermoregulator.load(input, WorldVersion);
 } else {
 Thermoregulator thermoregulatorx = new Thermoregulator(this);
 thermoregulatorx.load(input, WorldVersion);
 DebugLog.log("Couldnt load Thermoregulator, == nullptr");
 }
 }
 }

 void save(ByteBuffer output) {
 for (int int0 = 0; int0 < this->getBodyParts().size(); int0++) {
 BodyPart bodyPart = this->getBodyParts().get(int0);
 output.put((byte)(bodyPart.bitten() ? 1 : 0);
 output.put((byte)(bodyPart.scratched() ? 1 : 0);
 output.put((byte)(bodyPart.bandaged() ? 1 : 0);
 output.put((byte)(bodyPart.bleeding() ? 1 : 0);
 output.put((byte)(bodyPart.deepWounded() ? 1 : 0);
 output.put((byte)(bodyPart.IsFakeInfected() ? 1 : 0);
 output.put((byte)(bodyPart.IsInfected() ? 1 : 0);
 output.putFloat(bodyPart.getHealth());
 if (bodyPart.bandaged()) {
 output.putFloat(bodyPart.getBandageLife());
 }

 output.put((byte)(bodyPart.isInfectedWound() ? 1 : 0);
 if (bodyPart.isInfectedWound()) {
 output.putFloat(bodyPart.getWoundInfectionLevel());
 }

 output.putFloat(bodyPart.getBiteTime());
 output.putFloat(bodyPart.getScratchTime());
 output.putFloat(bodyPart.getBleedingTime());
 output.putFloat(bodyPart.getAlcoholLevel());
 output.putFloat(bodyPart.getAdditionalPain());
 output.putFloat(bodyPart.getDeepWoundTime());
 output.put((byte)(bodyPart.haveGlass() ? 1 : 0);
 output.put((byte)(bodyPart.isGetBandageXp() ? 1 : 0);
 output.put((byte)(bodyPart.stitched() ? 1 : 0);
 output.putFloat(bodyPart.getStitchTime());
 output.put((byte)(bodyPart.isGetStitchXp() ? 1 : 0);
 output.put((byte)(bodyPart.isGetSplintXp() ? 1 : 0);
 output.putFloat(bodyPart.getFractureTime());
 output.put((byte)(bodyPart.isSplint() ? 1 : 0);
 if (bodyPart.isSplint()) {
 output.putFloat(bodyPart.getSplintFactor());
 }

 output.put((byte)(bodyPart.haveBullet() ? 1 : 0);
 output.putFloat(bodyPart.getBurnTime());
 output.put((byte)(bodyPart.isNeedBurnWash() ? 1 : 0);
 output.putFloat(bodyPart.getLastTimeBurnWash());
 GameWindow.WriteString(output, bodyPart.getSplintItem());
 GameWindow.WriteString(output, bodyPart.getBandageType());
 output.putFloat(bodyPart.getCutTime());
 output.putFloat(bodyPart.getWetness());
 output.putFloat(bodyPart.getStiffness());
 }

 output.putFloat(this->InfectionLevel);
 output.putFloat(this->getFakeInfectionLevel());
 output.putFloat(this->getWetness());
 output.putFloat(this->getCatchACold());
 output.put((byte)(this->isHasACold() ? 1 : 0);
 output.putFloat(this->getColdStrength());
 output.putFloat(this->getUnhappynessLevel());
 output.putFloat(this->getBoredomLevel());
 output.putFloat(this->getFoodSicknessLevel());
 output.putFloat(this->PoisonLevel);
 output.putFloat(this->Temperature);
 output.put((byte)(this->isReduceFakeInfection() ? 1 : 0);
 output.putFloat(this->HealthFromFoodTimer);
 output.putFloat(this->painReduction);
 output.putFloat(this->coldReduction);
 output.putFloat(this->InfectionTime);
 output.putFloat(this->InfectionMortalityDuration);
 output.putFloat(this->ColdDamageStage);
 output.put((byte)(this->thermoregulator != nullptr ? 1 : 0);
 if (this->thermoregulator != nullptr) {
 this->thermoregulator.save(output);
 }
 }

 bool IsFakeInfected() {
 return this->isIsFakeInfected();
 }

 void OnFire(bool OnFire) {
 this->setIsOnFire(OnFire);
 }

 bool IsOnFire() {
 return this->isIsOnFire();
 }

 bool WasBurntToDeath() {
 return this->isBurntToDeath();
 }

 void IncreasePanicFloat(float delta) {
 float float0 = 1.0F;
 if (this->getParentChar().getBetaEffect() > 0.0F) {
 float0 -= this->getParentChar().getBetaDelta();
 if (float0 > 1.0F) {
 float0 = 1.0F;
 }

 if (float0 < 0.0F) {
 float0 = 0.0F;
 }
 }

 if (this->getParentChar().getCharacterTraits().Cowardly.isSet()) {
 float0 *= 2.0F;
 }

 if (this->getParentChar().getCharacterTraits().Brave.isSet()) {
 float0 *= 0.3F;
 }

 if (this->getParentChar().getCharacterTraits().Desensitized.isSet()) {
 float0 = 0.0F;
 }

 Stats stats = this->ParentChar.getStats();
 stats.Panic = stats.Panic + this->getPanicIncreaseValueFrame() * delta * float0;
 if (this->getParentChar().getStats().Panic > 100.0F) {
 this->ParentChar.getStats().Panic = 100.0F;
 }
 }

 void IncreasePanic(int NumNewZombiesSeen) {
 if (this->getParentChar().getVehicle() != nullptr) {
 NumNewZombiesSeen /= 2;
 }

 float float0 = 1.0F;
 if (this->getParentChar().getBetaEffect() > 0.0F) {
 float0 -= this->getParentChar().getBetaDelta();
 if (float0 > 1.0F) {
 float0 = 1.0F;
 }

 if (float0 < 0.0F) {
 float0 = 0.0F;
 }
 }

 if (this->getParentChar().getCharacterTraits().Cowardly.isSet()) {
 float0 *= 2.0F;
 }

 if (this->getParentChar().getCharacterTraits().Brave.isSet()) {
 float0 *= 0.3F;
 }

 if (this->getParentChar().getCharacterTraits().Desensitized.isSet()) {
 float0 = 0.0F;
 }

 Stats stats = this->ParentChar.getStats();
 stats.Panic = stats.Panic + this->getPanicIncreaseValue() * NumNewZombiesSeen * float0;
 if (this->getParentChar().getStats().Panic > 100.0F) {
 this->ParentChar.getStats().Panic = 100.0F;
 }
 }

 void ReducePanic() {
 if (!(this->ParentChar.getStats().Panic <= 0.0F) {
 float float0 = this->getPanicReductionValue() * (GameTime.getInstance().getMultiplier() / 1.6F);
 int int0 = (int)Math.floor(new Double(GameTime.instance.getNightsSurvived()) / 30.0);
 if (int0 > 5) {
 int0 = 5;
 }

 float0 += this->getPanicReductionValue() * int0;
 if (this->ParentChar.isAsleep()) {
 float0 *= 2.0F;
 }

 this->ParentChar.getStats().Panic -= float0;
 if (this->getParentChar().getStats().Panic < 0.0F) {
 this->ParentChar.getStats().Panic = 0.0F;
 }
 }
 }

 void UpdatePanicState() {
 int int0 = this->getParentChar().getStats().NumVisibleZombies;
 if (int0 > this->getOldNumZombiesVisible()) {
 this->IncreasePanic(int0 - this->getOldNumZombiesVisible());
 } else {
 this->ReducePanic();
 }

 this->setOldNumZombiesVisible(int0);
 }

 void JustDrankBooze(Food food, float percentage) {
 float float0 = 1.0F;
 if (this->getParentChar().Traits.HeavyDrinker.isSet()) {
 float0 = 0.3F;
 }

 if (this->getParentChar().Traits.LightDrinker.isSet()) {
 float0 = 4.0F;
 }

 if (food.getBaseHunger() != 0.0F) {
 percentage = food.getHungChange() * percentage / food.getBaseHunger() * 2.0F;
 }

 float0 *= percentage;
 if (food.getName().toLowerCase().contains("beer") || food.hasTag("LowAlcohol")) {
 float0 *= 0.25F;
 }

 if (this->getParentChar().getStats().hunger > 0.8) {
 float0 = (float)(float0 * 1.25);
 } else if (this->getParentChar().getStats().hunger > 0.6) {
 float0 = (float)(float0 * 1.1);
 }

 Stats stats = this->ParentChar.getStats();
 stats.Drunkenness = stats.Drunkenness + this->getDrunkIncreaseValue() * float0;
 if (this->getParentChar().getStats().Drunkenness > 100.0F) {
 this->ParentChar.getStats().Drunkenness = 100.0F;
 }

 this->getParentChar().SleepingTablet(0.02F * percentage);
 this->getParentChar().BetaAntiDepress(0.4F * percentage);
 this->getParentChar().BetaBlockers(0.2F * percentage);
 this->getParentChar().PainMeds(0.2F * percentage);
 }

 void JustTookPill(InventoryItem Pill) {
 if ("PillsBeta" == Pill.getType())) {
 if (this->getParentChar() != nullptr && this->getParentChar().getStats().Drunkenness > 10.0F) {
 this->getParentChar().BetaBlockers(0.15F);
 } else {
 this->getParentChar().BetaBlockers(0.3F);
 }

 Pill.Use();
 } else if ("PillsAntiDep" == Pill.getType())) {
 if (this->getParentChar() != nullptr && this->getParentChar().getStats().Drunkenness > 10.0F) {
 this->getParentChar().BetaAntiDepress(0.15F);
 } else {
 this->getParentChar().BetaAntiDepress(0.3F);
 }

 Pill.Use();
 } else if ("PillsSleepingTablets" == Pill.getType())) {
 Pill.Use();
 this->getParentChar().SleepingTablet(0.1F);
 if (this->getParentChar() instanceof IsoPlayer) {
 ((IsoPlayer)this->getParentChar()).setSleepingPillsTaken(((IsoPlayer)this->getParentChar()).getSleepingPillsTaken() + 1);
 }
 } else if ("Pills" == Pill.getType())) {
 Pill.Use();
 if (this->getParentChar() != nullptr && this->getParentChar().getStats().Drunkenness > 10.0F) {
 this->getParentChar().PainMeds(0.15F);
 } else {
 this->getParentChar().PainMeds(0.45F);
 }
 } else if ("PillsVitamins" == Pill.getType())) {
 Pill.Use();
 if (this->getParentChar() != nullptr && this->getParentChar().getStats().Drunkenness > 10.0F) {
 Stats stats0 = this->getParentChar().getStats();
 stats0.fatigue = stats0.fatigue + Pill.getFatigueChange() / 2.0F;
 } else {
 Stats stats1 = this->getParentChar().getStats();
 stats1.fatigue = stats1.fatigue + Pill.getFatigueChange();
 }
 }
 }

 void JustAteFood(Food NewFood, float percentage) {
 if (NewFood.getPoisonPower() > 0) {
 float float0 = NewFood.getPoisonPower() * percentage;
 if (this->getParentChar().Traits.IronGut.isSet()) {
 float0 /= 2.0F;
 }

 if (this->getParentChar().Traits.WeakStomach.isSet()) {
 float0 *= 2.0F;
 }

 this->PoisonLevel += float0;
 Stats stats = this->ParentChar.getStats();
 stats.Pain = stats.Pain + NewFood.getPoisonPower() * percentage / 6.0F;
 }

 if (NewFood.isTaintedWater()) {
 this->PoisonLevel += 20.0F * percentage;
 this->ParentChar.getStats().Pain += 10.0F * percentage / 6.0F;
 }

 if (NewFood.getReduceInfectionPower() > 0.0F) {
 this->getParentChar().setReduceInfectionPower(NewFood.getReduceInfectionPower());
 }

 this->setBoredomLevel(this->getBoredomLevel() + NewFood.getBoredomChange() * percentage);
 if (this->getBoredomLevel() < 0.0F) {
 this->setBoredomLevel(0.0F);
 }

 this->setUnhappynessLevel(this->getUnhappynessLevel() + NewFood.getUnhappyChange() * percentage);
 if (this->getUnhappynessLevel() < 0.0F) {
 this->setUnhappynessLevel(0.0F);
 }

 if (NewFood.isAlcoholic()) {
 this->JustDrankBooze(NewFood, percentage);
 }

 if (this->getParentChar().getStats().hunger <= 0.0F) {
 float float1 = Math.abs(NewFood.getHungerChange()) * percentage;
 this->setHealthFromFoodTimer((int)(this->getHealthFromFoodTimer() + float1 * this->getHealthFromFoodTimeByHunger()));
 if (NewFood.isCooked()) {
 this->setHealthFromFoodTimer((int)(this->getHealthFromFoodTimer() + float1 * this->getHealthFromFoodTimeByHunger()));
 }

 if (this->getHealthFromFoodTimer() > 11000.0F) {
 this->setHealthFromFoodTimer(11000.0F);
 }
 }

 if (!"Tutorial" == Core.getInstance().getGameMode())) {
 if (!NewFood.isCooked() && NewFood.isbDangerousUncooked()) {
 this->setHealthFromFoodTimer(0.0F);
 uint8_t byte0 = 75;
 if (NewFood.hasTag("Egg")) {
 byte0 = 5;
 }

 if (this->getParentChar().Traits.IronGut.isSet()) {
 byte0 /= 2;
 if (NewFood.hasTag("Egg")) {
 byte0 = 0;
 }
 }

 if (this->getParentChar().Traits.WeakStomach.isSet()) {
 byte0 *= 2;
 }

 if (byte0 > 0 && Rand.Next(100) < byte0 && !this->isInfected()) {
 this->PoisonLevel += 15.0F * percentage;
 }
 }

 if (NewFood.getAge() >= NewFood.getOffAgeMax()) {
 float float2 = NewFood.getAge() - NewFood.getOffAgeMax();
 if (float2 == 0.0F) {
 float2 = 1.0F;
 }

 if (float2 > 5.0F) {
 float2 = 5.0F;
 }

 int int0;
 if (NewFood.getOffAgeMax() > NewFood.getOffAge()) {
 int0 = (int)(float2 / (NewFood.getOffAgeMax() - NewFood.getOffAge()) * 100.0F);
 } else {
 int0 = 100;
 }

 if (this->getParentChar().Traits.IronGut.isSet()) {
 int0 /= 2;
 }

 if (this->getParentChar().Traits.WeakStomach.isSet()) {
 int0 *= 2;
 }

 if (Rand.Next(100) < int0 && !this->isInfected()) {
 this->PoisonLevel = this->PoisonLevel + 5.0F * Math.abs(NewFood.getHungChange() * 10.0F) * percentage;
 }
 }
 }
 }

 void JustAteFood(Food NewFood) {
 this->JustAteFood(NewFood, 100.0F);
 }

 float getHealthFromFoodTimeByHunger() {
 return 13000.0F;
 }

 void JustReadSomething(Literature lit) {
 this->setBoredomLevel(this->getBoredomLevel() + lit.getBoredomChange());
 if (this->getBoredomLevel() < 0.0F) {
 this->setBoredomLevel(0.0F);
 }

 this->setUnhappynessLevel(this->getUnhappynessLevel() + lit.getUnhappyChange());
 if (this->getUnhappynessLevel() < 0.0F) {
 this->setUnhappynessLevel(0.0F);
 }
 }

 void JustTookPainMeds() {
 Stats stats = this->ParentChar.getStats();
 stats.Pain = stats.Pain - this->getPainReductionFromMeds();
 if (this->getParentChar().getStats().Pain < 0.0F) {
 this->ParentChar.getStats().Pain = 0.0F;
 }
 }

 void UpdateWetness() {
 IsoGridSquare square = this->getParentChar().getCurrentSquare();
 BaseVehicle vehicle = this->getParentChar().getVehicle();
 IsoGameCharacter character = this->getParentChar();
 bool boolean0 = square == nullptr || !square.isInARoom() && !square.haveRoof;
 if (vehicle != nullptr && vehicle.hasRoof(vehicle.getSeat(this->getParentChar()))) {
 boolean0 = false;
 }

 ClothingWetness clothingWetness = this->getParentChar().getClothingWetness();
 float float0 = 0.0F;
 float float1 = 0.0F;
 float float2 = 0.0F;
 if (vehicle != nullptr && ClimateManager.getInstance().isRaining()) {
 VehiclePart part = vehicle.getPartById("Windshield");
 if (part != nullptr) {
 VehicleWindow vehicleWindow = part.getWindow();
 if (vehicleWindow != nullptr && vehicleWindow.isDestroyed()) {
 float float3 = ClimateManager.getInstance().getRainIntensity();
 float3 *= float3;
 float3 *= vehicle.getCurrentSpeedKmHour() / 50.0F;
 if (float3 < 0.1F) {
 float3 = 0.0F;
 }

 if (float3 > 1.0F) {
 float3 = 1.0F;
 }

 float2 = float3 * 3.0F;
 float0 = float3;
 }
 }
 }

 if (boolean0 && character.isAsleep() && character.getBed() != nullptr && "Tent" == character.getBed().getName())) {
 boolean0 = false;
 }

 if (boolean0 && ClimateManager.getInstance().isRaining()) {
 float float4 = ClimateManager.getInstance().getRainIntensity();
 if (float4 < 0.1) {
 float4 = 0.0F;
 }

 float0 = float4;
 } else if (!boolean0 || !ClimateManager.getInstance().isRaining()) {
 float float5 = ClimateManager.getInstance().getAirTemperatureForCharacter(this->getParentChar());
 float float6 = 0.1F;
 if (float5 > 5.0F) {
 float6 += (float5 - 5.0F) / 10.0F;
 }

 float6 -= float2;
 if (float6 < 0.0F) {
 float6 = 0.0F;
 }

 float1 = float6;
 }

 if (clothingWetness != nullptr) {
 clothingWetness.updateWetness(float0, float1);
 }

 float float7 = 0.0F;
 if (this->BodyParts.size() > 0) {
 for (int int0 = 0; int0 < this->BodyParts.size(); int0++) {
 float7 += this->BodyParts.get(int0).getWetness();
 }

 float7 /= this->BodyParts.size();
 }

 this->Wetness = PZMath.clamp(float7, 0.0F, 100.0F);
 float float8 = 0.0F;
 if (this->thermoregulator != nullptr) {
 float8 = this->thermoregulator.getCatchAColdDelta();
 }

 if (!this->isHasACold() && float8 > 0.1F) {
 if (this->getParentChar().Traits.ProneToIllness.isSet()) {
 float8 *= 1.7F;
 }

 if (this->getParentChar().Traits.Resilient.isSet()) {
 float8 *= 0.45F;
 }

 if (this->getParentChar().Traits.Outdoorsman.isSet()) {
 float8 *= 0.1F;
 }

 this->setCatchACold(this->getCatchACold() + (float)ZomboidGlobals.CatchAColdIncreaseRate * float8 * GameTime.instance.getMultiplier());
 if (this->getCatchACold() >= 100.0F) {
 this->setCatchACold(0.0F);
 this->setHasACold(true);
 this->setColdStrength(20.0F);
 this->setTimeToSneezeOrCough(0);
 }
 }

 if (float8 <= 0.1F) {
 this->setCatchACold(this->getCatchACold() - (float)ZomboidGlobals.CatchAColdDecreaseRate);
 if (this->getCatchACold() <= 0.0F) {
 this->setCatchACold(0.0F);
 }
 }
 }

 void TriggerSneezeCough() {
 if (this->getSneezeCoughActive() <= 0) {
 if (Rand.Next(100) > 50) {
 this->setSneezeCoughActive(1);
 } else {
 this->setSneezeCoughActive(2);
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.HasACold) == 2) {
 this->setSneezeCoughActive(1);
 }

 this->setSneezeCoughTime(this->getSneezeCoughDelay());
 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.HasACold) == 2) {
 this->setTimeToSneezeOrCough(this->getMildColdSneezeTimerMin() + Rand.Next(this->getMildColdSneezeTimerMax() - this->getMildColdSneezeTimerMin()));
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.HasACold) == 3) {
 this->setTimeToSneezeOrCough(this->getColdSneezeTimerMin() + Rand.Next(this->getColdSneezeTimerMax() - this->getColdSneezeTimerMin()));
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.HasACold) == 4) {
 this->setTimeToSneezeOrCough(
 this->getNastyColdSneezeTimerMin() + Rand.Next(this->getNastyColdSneezeTimerMax() - this->getNastyColdSneezeTimerMin())
 );
 }

 bool boolean0 = false;
 if (this->getParentChar().getPrimaryHandItem() == nullptr
 || !this->getParentChar().getPrimaryHandItem().getType() == "Tissue")
 && !this->getParentChar().getPrimaryHandItem().getType() == "ToiletPaper")) {
 if (this->getParentChar().getSecondaryHandItem() != nullptr
 && (
 this->getParentChar().getSecondaryHandItem().getType() == "Tissue")
 || this->getParentChar().getSecondaryHandItem().getType() == "ToiletPaper")
 )
 && ((Drainable)this->getParentChar().getSecondaryHandItem()).getUsedDelta() > 0.0F) {
 ((Drainable)this->getParentChar().getSecondaryHandItem())
 .setUsedDelta(((Drainable)this->getParentChar().getSecondaryHandItem()).getUsedDelta() - 0.1F);
 if (((Drainable)this->getParentChar().getSecondaryHandItem()).getUsedDelta() <= 0.0F) {
 this->getParentChar().getSecondaryHandItem().Use();
 }

 boolean0 = true;
 }
 } else if (((Drainable)this->getParentChar().getPrimaryHandItem()).getUsedDelta() > 0.0F) {
 ((Drainable)this->getParentChar().getPrimaryHandItem())
 .setUsedDelta(((Drainable)this->getParentChar().getPrimaryHandItem()).getUsedDelta() - 0.1F);
 if (((Drainable)this->getParentChar().getPrimaryHandItem()).getUsedDelta() <= 0.0F) {
 this->getParentChar().getPrimaryHandItem().Use();
 }

 boolean0 = true;
 }

 if (boolean0) {
 this->setSneezeCoughActive(this->getSneezeCoughActive() + 2);
 } else {
 uint8_t byte0 = 20;
 uint8_t byte1 = 20;
 if (this->getSneezeCoughActive() == 1) {
 byte0 = 20;
 byte1 = 25;
 }

 if (this->getSneezeCoughActive() == 2) {
 byte0 = 35;
 byte1 = 40;
 }

 WorldSoundManager.instance
 .addSound(
 this->getParentChar(),
 (int)this->getParentChar().getX(),
 (int)this->getParentChar().getY(),
 (int)this->getParentChar().getZ(),
 byte0,
 byte1,
 true
 );
 }
 }
 }

 int IsSneezingCoughing() {
 return this->getSneezeCoughActive();
 }

 void UpdateCold() {
 if (this->isHasACold()) {
 bool boolean0 = true;
 IsoGridSquare square = this->getParentChar().getCurrentSquare();
 if (square.empty()
 || !square.isInARoom()
 || this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Wet) > 0
 || this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Hypothermia) >= 1
 || this->getParentChar().getStats().fatigue > 0.5F
 || this->getParentChar().getStats().hunger > 0.25F
 || this->getParentChar().getStats().thirst > 0.25F) {
 boolean0 = false;
 }

 if (this->getColdReduction() > 0.0F) {
 boolean0 = true;
 this->setColdReduction(this->getColdReduction() - 0.005F * GameTime.instance.getMultiplier());
 if (this->getColdReduction() < 0.0F) {
 this->setColdReduction(0.0F);
 }
 }

 if (boolean0) {
 float float0 = 1.0F;
 if (this->getParentChar().Traits.ProneToIllness.isSet()) {
 float0 = 0.5F;
 }

 if (this->getParentChar().Traits.Resilient.isSet()) {
 float0 = 1.5F;
 }

 this->setColdStrength(this->getColdStrength() - this->getColdProgressionRate() * float0 * GameTime.instance.getMultiplier());
 if (this->getColdReduction() > 0.0F) {
 this->setColdStrength(this->getColdStrength() - this->getColdProgressionRate() * float0 * GameTime.instance.getMultiplier());
 }

 if (this->getColdStrength() < 0.0F) {
 this->setColdStrength(0.0F);
 this->setHasACold(false);
 this->setCatchACold(0.0F);
 }
 } else {
 float float1 = 1.0F;
 if (this->getParentChar().Traits.ProneToIllness.isSet()) {
 float1 = 1.2F;
 }

 if (this->getParentChar().Traits.Resilient.isSet()) {
 float1 = 0.8F;
 }

 this->setColdStrength(this->getColdStrength() + this->getColdProgressionRate() * float1 * GameTime.instance.getMultiplier());
 if (this->getColdStrength() > 100.0F) {
 this->setColdStrength(100.0F);
 }
 }

 if (this->getSneezeCoughTime() > 0) {
 this->setSneezeCoughTime(this->getSneezeCoughTime() - 1);
 if (this->getSneezeCoughTime() == 0) {
 this->setSneezeCoughActive(0);
 }
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.HasACold) > 1
 && this->getTimeToSneezeOrCough() >= 0
 && !this->ParentChar.IsSpeaking()) {
 this->setTimeToSneezeOrCough(this->getTimeToSneezeOrCough() - 1);
 if (this->getTimeToSneezeOrCough() <= 0) {
 this->TriggerSneezeCough();
 }
 }
 }
 }

 float getColdStrength() {
 return this->isHasACold() ? this->ColdStrength : 0.0F;
 }

 float getWetness() {
 return this->Wetness;
 }

 void AddDamage(BodyPartType BodyPart, float Val) {
 this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).AddDamage(Val);
 }

 void AddGeneralHealth(float Val) {
 int int0 = 0;

 for (int int1 = 0; int1 < BodyPartType.ToIndex(BodyPartType.MAX); int1++) {
 if (this->getBodyParts().get(int1).getHealth() < 100.0F) {
 int0++;
 }
 }

 if (int0 > 0) {
 float float0 = Val / int0;

 for (int int2 = 0; int2 < BodyPartType.ToIndex(BodyPartType.MAX); int2++) {
 if (this->getBodyParts().get(int2).getHealth() < 100.0F) {
 this->getBodyParts().get(int2).AddHealth(float0);
 }
 }
 }
 }

 void ReduceGeneralHealth(float Val) {
 if (this->getOverallBodyHealth() <= 10.0F) {
 this->getParentChar().forceAwake();
 }

 if (!(Val <= 0.0F) {
 float float0 = Val / BodyPartType.ToIndex(BodyPartType.MAX);

 for (int int0 = 0; int0 < BodyPartType.ToIndex(BodyPartType.MAX); int0++) {
 this->getBodyParts().get(int0).ReduceHealth(float0 / BodyPartType.getDamageModifyer(int0);
 }
 }
 }

 void AddDamage(int BodyPartIndex, float val) {
 this->getBodyParts().get(BodyPartIndex).AddDamage(val);
 }

 void splatBloodFloorBig() {
 this->getParentChar().splatBloodFloorBig();
 this->getParentChar().splatBloodFloorBig();
 this->getParentChar().splatBloodFloorBig();
 }

 /**
 * When hit by another player in MP
 */
 void DamageFromWeapon(HandWeapon weapon) {
 if (GameServer.bServer) {
 if (weapon != nullptr) {
 this->getParentChar().sendObjectChange("DamageFromWeapon", new Object[]{"weapon", weapon.getFullType()});
 }
 } else if (!(this->getParentChar() instanceof IsoPlayer) || ((IsoPlayer)this->getParentChar()).isLocalPlayer()) {
 int int0 = 0;
 uint8_t byte0 = 1;
 bool boolean0 = true;
 int0 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.MAX);
 if (DebugOptions.instance.MultiplayerTorsoHit.getValue()) {
 int0 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Torso_Upper), BodyPartType.ToIndex(BodyPartType.Head);
 }

 bool boolean1 = false;
 bool boolean2 = false;
 bool boolean3 = false;
 bool boolean4 = true;
 bool boolean5 = true;
 if (weapon.getCategories().contains("Blunt") || weapon.getCategories().contains("SmallBlunt")) {
 boolean5 = false;
 byte0 = 0;
 boolean1 = true;
 } else if (!weapon.isAimedFirearm()) {
 byte0 = 1;
 boolean2 = true;
 } else {
 boolean3 = true;
 byte0 = 2;
 }

 BodyPart bodyPart = this->getBodyPart(BodyPartType.FromIndex(int0);
 float float0 = this->getParentChar().getBodyPartClothingDefense(bodyPart.getIndex(), boolean2, boolean3);
 if (Rand.Next(100) < float0) {
 boolean0 = false;
 this->getParentChar().addHoleFromZombieAttacks(BloodBodyPartType.FromIndex(int0), false);
 }

 if (boolean0) {
 this->getParentChar().addHole(BloodBodyPartType.FromIndex(int0);
 this->getParentChar().splatBloodFloorBig();
 this->getParentChar().splatBloodFloorBig();
 this->getParentChar().splatBloodFloorBig();
 if (boolean2) {
 if (Rand.NextBool(6) {
 bodyPart.generateDeepWound();
 } else if (Rand.NextBool(3) {
 bodyPart.setCut(true);
 } else {
 bodyPart.setScratched(true, true);
 }
 } else if (boolean1) {
 if (Rand.NextBool(4) {
 bodyPart.setCut(true);
 } else {
 bodyPart.setScratched(true, true);
 }
 } else if (boolean3) {
 bodyPart.setHaveBullet(true, 0);
 }

 float float1 = Rand.Next(weapon.getMinDamage(), weapon.getMaxDamage()) * 15.0F;
 if (int0 == BodyPartType.ToIndex(BodyPartType.Head) {
 float1 *= 4.0F;
 }

 if (int0 == BodyPartType.ToIndex(BodyPartType.Neck) {
 float1 *= 4.0F;
 }

 if (int0 == BodyPartType.ToIndex(BodyPartType.Torso_Upper) {
 float1 *= 2.0F;
 }

 if (GameClient.bClient) {
 if (weapon.isRanged()) {
 float1 = (float)(float1 * ServerOptions.getInstance().PVPFirearmDamageModifier.getValue());
 } else {
 float1 = (float)(float1 * ServerOptions.getInstance().PVPMeleeDamageModifier.getValue());
 }
 }

 this->AddDamage(int0, float1);
 switch (byte0) {
 case 0:
 Stats stats0 = this->ParentChar.getStats();
 stats0.Pain = stats0.Pain + this->getInitialThumpPain() * BodyPartType.getPainModifyer(int0);
 break;
 case 1:
 Stats stats1 = this->ParentChar.getStats();
 stats1.Pain = stats1.Pain + this->getInitialScratchPain() * BodyPartType.getPainModifyer(int0);
 break;
 case 2:
 Stats stats2 = this->ParentChar.getStats();
 stats2.Pain = stats2.Pain + this->getInitialBitePain() * BodyPartType.getPainModifyer(int0);
 }

 if (this->getParentChar().getStats().Pain > 100.0F) {
 this->ParentChar.getStats().Pain = 100.0F;
 }

 if (this->ParentChar instanceof IsoPlayer && GameClient.bClient && ((IsoPlayer)this->ParentChar).isLocalPlayer()) {
 IsoPlayer player = (IsoPlayer)this->ParentChar;
 player.updateMovementRates();
 GameClient.sendPlayerInjuries(player);
 GameClient.sendPlayerDamage(player);
 }
 }
 }
 }

 /**
 * This gonna decide the strength of the damage you'll get. Getting surrounded can also trigger an instant death animation.
 */
 bool AddRandomDamageFromZombie(IsoZombie zombie, const std::string& hitReaction) {
 if (StringUtils.isNullOrEmpty(hitReaction) {
 hitReaction = "Bite";
 }

 this->getParentChar().setVariable("hitpvp", false);
 if (GameServer.bServer) {
 this->getParentChar().sendObjectChange("AddRandomDamageFromZombie", new Object[]{"zombie", zombie.OnlineID});
 return true;
 } else {
 uint8_t byte0 = 0;
 int int0 = 0;
 int int1 = 15 + this->getParentChar().getMeleeCombatMod();
 int int2 = 85;
 int int3 = 65;
 std::string string = this->getParentChar().testDotSide(zombie);
 bool boolean0 = string.equals(behindStr);
 bool boolean1 = string.equals(leftStr) || string.equals(rightStr);
 int int4 = this->getParentChar().getSurroundingAttackingZombies();
 int4 = Math.max(int4, 1);
 int1 -= (int4 - 1) * 10;
 int2 -= (int4 - 1) * 30;
 int3 -= (int4 - 1) * 15;
 uint8_t byte1 = 3;
 if (SandboxOptions.instance.Lore.Strength.getValue() == 1) {
 byte1 = 2;
 }

 if (SandboxOptions.instance.Lore.Strength.getValue() == 3) {
 byte1 = 6;
 }

 if (this->ParentChar.Traits.ThickSkinned.isSet()) {
 int1 = (int)(int1 * 1.3);
 }

 if (this->ParentChar.Traits.ThinSkinned.isSet()) {
 int1 = (int)(int1 / 1.3);
 }

 if (!"EndDeath" == this->getParentChar().getHitReaction())) {
 if (!this->getParentChar().isGodMod()
 && int4 >= byte1
 && SandboxOptions.instance.Lore.ZombiesDragDown.getValue()
 && !this->getParentChar().isSitOnGround()) {
 int2 = 0;
 int3 = 0;
 int1 = 0;
 this->getParentChar().setHitReaction("EndDeath");
 this->getParentChar().setDeathDragDown(true);
 } else {
 this->getParentChar().setHitReaction(hitReaction);
 }
 }

 if (boolean0) {
 int1 -= 15;
 int2 -= 25;
 int3 -= 35;
 if (SandboxOptions.instance.RearVulnerability.getValue() == 1) {
 int1 += 15;
 int2 += 25;
 int3 += 35;
 }

 if (SandboxOptions.instance.RearVulnerability.getValue() == 2) {
 int1 += 7;
 int2 += 17;
 int3 += 23;
 }

 if (int4 > 2) {
 int2 -= 15;
 int3 -= 15;
 }
 }

 if (boolean1) {
 int1 -= 30;
 int2 -= 7;
 int3 -= 27;
 if (SandboxOptions.instance.RearVulnerability.getValue() == 1) {
 int1 += 30;
 int2 += 7;
 int3 += 27;
 }

 if (SandboxOptions.instance.RearVulnerability.getValue() == 2) {
 int1 += 15;
 int2 += 4;
 int3 += 15;
 }
 }

 if (!zombie.bCrawling) {
 if (Rand.Next(10) == 0) {
 int0 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.Groin) + 1);
 } else {
 int0 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.Neck) + 1);
 }

 float float0 = 10.0F * int4;
 if (boolean0) {
 float0 += 5.0F;
 }

 if (boolean1) {
 float0 += 2.0F;
 }

 if (boolean0 && Rand.Next(100) < float0) {
 int0 = BodyPartType.ToIndex(BodyPartType.Neck);
 }

 if (int0 == BodyPartType.ToIndex(BodyPartType.Head) || int0 == BodyPartType.ToIndex(BodyPartType.Neck) {
 uint8_t byte2 = 70;
 if (boolean0) {
 byte2 = 90;
 }

 if (boolean1) {
 byte2 = 80;
 }

 if (Rand.Next(100) > byte2) {
 bool boolean2 = false;

 while (!boolean2) {
 boolean2 = true;
 int0 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Torso_Lower) + 1);
 if (int0 == BodyPartType.ToIndex(BodyPartType.Head)
 || int0 == BodyPartType.ToIndex(BodyPartType.Neck)
 || int0 == BodyPartType.ToIndex(BodyPartType.Groin) {
 boolean2 = false;
 }
 }
 }
 }
 } else {
 if (Rand.Next(2) != 0) {
 return false;
 }

 if (Rand.Next(10) == 0) {
 int0 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Groin), BodyPartType.ToIndex(BodyPartType.MAX);
 } else {
 int0 = Rand.Next(BodyPartType.ToIndex(BodyPartType.UpperLeg_L), BodyPartType.ToIndex(BodyPartType.MAX);
 }
 }

 if (zombie.inactive) {
 int1 += 20;
 int2 += 20;
 int3 += 20;
 }

 float float1 = Rand.Next(1000) / 1000.0F;
 float1 *= Rand.Next(10) + 10;
 if (GameServer.bServer && this->ParentChar instanceof IsoPlayer || Core.bDebug && this->ParentChar instanceof IsoPlayer) {
 DebugLog.log(
 DebugType.Combat,
 "zombie did "
 + float1
 + " dmg to "
 + ((IsoPlayer)this->ParentChar).getDisplayName()
 + " on body part "
 + BodyPartType.getDisplayName(BodyPartType.FromIndex(int0)
 );
 }

 bool boolean3 = false;
 bool boolean4 = true;
 if (Rand.Next(100) > int1) {
 zombie.scratch = true;
 this->getParentChar().helmetFall(int0 == BodyPartType.ToIndex(BodyPartType.Neck) || int0 == BodyPartType.ToIndex(BodyPartType.Head);
 if (Rand.Next(100) > int3) {
 zombie.scratch = false;
 zombie.laceration = true;
 }

 if (Rand.Next(100) > int2) {
 zombie.scratch = false;
 zombie.laceration = false;
 boolean4 = false;
 }

 if (zombie.scratch) {
 float float2 = this->getParentChar().getBodyPartClothingDefense(int0, false, false);
 zombie.parameterZombieState.setState(ParameterZombieState.State.AttackScratch);
 if (this->getHealth() > 0.0F) {
 this->getParentChar().getEmitter().playSoundImpl("ZombieScratch", (IsoObject)nullptr);
 }

 if (Rand.Next(100) < float2) {
 this->getParentChar().addHoleFromZombieAttacks(BloodBodyPartType.FromIndex(int0), boolean4);
 return false;
 }

 bool boolean5 = this->getParentChar().addHole(BloodBodyPartType.FromIndex(int0), true);
 if (boolean5) {
 this->getParentChar().getEmitter().playSoundImpl("ZombieRipClothing", (IsoObject)nullptr);
 }

 boolean3 = true;
 this->AddDamage(int0, float1);
 this->SetScratched(int0, true);
 this->getParentChar().addBlood(BloodBodyPartType.FromIndex(int0), true, false, true);
 byte0 = 1;
 if (GameServer.bServer && this->ParentChar instanceof IsoPlayer) {
 DebugLog.log(DebugType.Combat, "zombie scratched " + ((IsoPlayer)this->ParentChar).username);
 }
 } else if (zombie.laceration) {
 float float3 = this->getParentChar().getBodyPartClothingDefense(int0, false, false);
 zombie.parameterZombieState.setState(ParameterZombieState.State.AttackLacerate);
 if (this->getHealth() > 0.0F) {
 this->getParentChar().getEmitter().playSoundImpl("ZombieScratch", (IsoObject)nullptr);
 }

 if (Rand.Next(100) < float3) {
 this->getParentChar().addHoleFromZombieAttacks(BloodBodyPartType.FromIndex(int0), boolean4);
 return false;
 }

 bool boolean6 = this->getParentChar().addHole(BloodBodyPartType.FromIndex(int0), true);
 if (boolean6) {
 this->getParentChar().getEmitter().playSoundImpl("ZombieRipClothing", (IsoObject)nullptr);
 }

 boolean3 = true;
 this->AddDamage(int0, float1);
 this->SetCut(int0, true);
 this->getParentChar().addBlood(BloodBodyPartType.FromIndex(int0), true, false, true);
 byte0 = 1;
 if (GameServer.bServer && this->ParentChar instanceof IsoPlayer) {
 DebugLog.log(DebugType.Combat, "zombie laceration " + ((IsoPlayer)this->ParentChar).username);
 }
 } else {
 float float4 = this->getParentChar().getBodyPartClothingDefense(int0, true, false);
 zombie.parameterZombieState.setState(ParameterZombieState.State.AttackBite);
 if (this->getHealth() > 0.0F) {
 this->getParentChar().getEmitter().playSoundImpl("ZombieBite", (IsoObject)nullptr);
 }

 if (Rand.Next(100) < float4) {
 this->getParentChar().addHoleFromZombieAttacks(BloodBodyPartType.FromIndex(int0), boolean4);
 return false;
 }

 bool boolean7 = this->getParentChar().addHole(BloodBodyPartType.FromIndex(int0), true);
 if (boolean7) {
 this->getParentChar().getEmitter().playSoundImpl("ZombieRipClothing", (IsoObject)nullptr);
 }

 boolean3 = true;
 this->AddDamage(int0, float1);
 this->SetBitten(int0, true);
 if (int0 == BodyPartType.ToIndex(BodyPartType.Neck) {
 this->getParentChar().addBlood(BloodBodyPartType.FromIndex(int0), false, true, true);
 this->getParentChar().addBlood(BloodBodyPartType.FromIndex(int0), false, true, true);
 this->getParentChar().addBlood(BloodBodyPartType.Torso_Upper, false, true, false);
 }

 this->getParentChar().addBlood(BloodBodyPartType.FromIndex(int0), false, true, true);
 if (GameServer.bServer && this->ParentChar instanceof IsoPlayer) {
 DebugLog.log(DebugType.Combat, "zombie bite " + ((IsoPlayer)this->ParentChar).username);
 }

 byte0 = 2;
 this->getParentChar().splatBloodFloorBig();
 this->getParentChar().splatBloodFloorBig();
 this->getParentChar().splatBloodFloorBig();
 }
 }

 if (!boolean3) {
 this->getParentChar().addHoleFromZombieAttacks(BloodBodyPartType.FromIndex(int0), boolean4);
 }

 switch (byte0) {
 case 0:
 Stats stats0 = this->ParentChar.getStats();
 stats0.Pain = stats0.Pain + this->getInitialThumpPain() * BodyPartType.getPainModifyer(int0);
 break;
 case 1:
 Stats stats1 = this->ParentChar.getStats();
 stats1.Pain = stats1.Pain + this->getInitialScratchPain() * BodyPartType.getPainModifyer(int0);
 break;
 case 2:
 Stats stats2 = this->ParentChar.getStats();
 stats2.Pain = stats2.Pain + this->getInitialBitePain() * BodyPartType.getPainModifyer(int0);
 }

 if (this->getParentChar().getStats().Pain > 100.0F) {
 this->ParentChar.getStats().Pain = 100.0F;
 }

 if (this->ParentChar instanceof IsoPlayer && GameClient.bClient && ((IsoPlayer)this->ParentChar).isLocalPlayer()) {
 IsoPlayer player = (IsoPlayer)this->ParentChar;
 player.updateMovementRates();
 GameClient.sendPlayerInjuries(player);
 GameClient.sendPlayerDamage(player);
 }

 return true;
 }
 }

 bool doesBodyPartHaveInjury(BodyPartType part) {
 return this->getBodyParts().get(BodyPartType.ToIndex(part).HasInjury();
 }

 /**
 * Returns TRUE if either body part is injured. ie. A OR B
 */
 bool doBodyPartsHaveInjuries(BodyPartType partA, BodyPartType partB) {
 return this->doesBodyPartHaveInjury(partA) || this->doesBodyPartHaveInjury(partB);
 }

 /**
 * Returns TRUE if the specified body part's bleeding time is greater than 0.
 */
 bool isBodyPartBleeding(BodyPartType part) {
 return this->getBodyPart(part).getBleedingTime() > 0.0F;
 }

 /**
 * Returns TRUE if either body part is bleeding. ie. A OR B
 */
 bool areBodyPartsBleeding(BodyPartType partA, BodyPartType partB) {
 return this->isBodyPartBleeding(partA) || this->isBodyPartBleeding(partB);
 }

 void DrawUntexturedQuad(int X, int Y, int Width, int Height, float r, float g, float b, float a) {
 SpriteRenderer.instance.renderi(nullptr, X, Y, Width, Height, r, g, b, a, nullptr);
 }

 float getBodyPartHealth(BodyPartType BodyPart) {
 return this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).getHealth();
 }

 float getBodyPartHealth(int BodyPartIndex) {
 return this->getBodyParts().get(BodyPartIndex).getHealth();
 }

 std::string getBodyPartName(BodyPartType BodyPart) {
 return BodyPartType.ToString(BodyPart);
 }

 std::string getBodyPartName(int BodyPartIndex) {
 return BodyPartType.ToString(BodyPartType.FromIndex(BodyPartIndex);
 }

 float getHealth() {
 return this->getOverallBodyHealth();
 }

 float getInfectionLevel() {
 return this->InfectionLevel;
 }

 float getApparentInfectionLevel() {
 float float0 = this->getFakeInfectionLevel() > this->InfectionLevel ? this->getFakeInfectionLevel() : this->InfectionLevel;
 return this->getFoodSicknessLevel() > float0 ? this->getFoodSicknessLevel() : float0;
 }

 int getNumPartsBleeding() {
 int int0 = 0;

 for (int int1 = 0; int1 < BodyPartType.ToIndex(BodyPartType.MAX); int1++) {
 if (this->getBodyParts().get(int1).bleeding()) {
 int0++;
 }
 }

 return int0;
 }

 int getNumPartsScratched() {
 int int0 = 0;

 for (int int1 = 0; int1 < BodyPartType.ToIndex(BodyPartType.MAX); int1++) {
 if (this->getBodyParts().get(int1).scratched()) {
 int0++;
 }
 }

 return int0;
 }

 int getNumPartsBitten() {
 int int0 = 0;

 for (int int1 = 0; int1 < BodyPartType.ToIndex(BodyPartType.MAX); int1++) {
 if (this->getBodyParts().get(int1).bitten()) {
 int0++;
 }
 }

 return int0;
 }

 bool HasInjury() {
 for (int int0 = 0; int0 < BodyPartType.ToIndex(BodyPartType.MAX); int0++) {
 if (this->getBodyParts().get(int0).HasInjury()) {
 return true;
 }
 }

 return false;
 }

 bool IsBandaged(BodyPartType BodyPart) {
 return this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).bandaged();
 }

 bool IsDeepWounded(BodyPartType BodyPart) {
 return this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).deepWounded();
 }

 bool IsBandaged(int BodyPartIndex) {
 return this->getBodyParts().get(BodyPartIndex).bandaged();
 }

 bool IsBitten(BodyPartType BodyPart) {
 return this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).bitten();
 }

 bool IsBitten(int BodyPartIndex) {
 return this->getBodyParts().get(BodyPartIndex).bitten();
 }

 bool IsBleeding(BodyPartType BodyPart) {
 return this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).bleeding();
 }

 bool IsBleeding(int BodyPartIndex) {
 return this->getBodyParts().get(BodyPartIndex).bleeding();
 }

 bool IsBleedingStemmed(BodyPartType BodyPart) {
 return this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).IsBleedingStemmed();
 }

 bool IsBleedingStemmed(int BodyPartIndex) {
 return this->getBodyParts().get(BodyPartIndex).IsBleedingStemmed();
 }

 bool IsCortorised(BodyPartType BodyPart) {
 return this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).IsCortorised();
 }

 bool IsCortorised(int BodyPartIndex) {
 return this->getBodyParts().get(BodyPartIndex).IsCortorised();
 }

 bool IsInfected() {
 return this->IsInfected;
 }

 bool IsInfected(BodyPartType BodyPart) {
 return this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).IsInfected();
 }

 bool IsInfected(int BodyPartIndex) {
 return this->getBodyParts().get(BodyPartIndex).IsInfected();
 }

 bool IsFakeInfected(int BodyPartIndex) {
 return this->getBodyParts().get(BodyPartIndex).IsFakeInfected();
 }

 void DisableFakeInfection(int BodyPartIndex) {
 this->getBodyParts().get(BodyPartIndex).DisableFakeInfection();
 }

 bool IsScratched(BodyPartType BodyPart) {
 return this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).scratched();
 }

 bool IsCut(BodyPartType BodyPart) {
 return this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).getCutTime() > 0.0F;
 }

 bool IsScratched(int BodyPartIndex) {
 return this->getBodyParts().get(BodyPartIndex).scratched();
 }

 bool IsStitched(BodyPartType BodyPart) {
 return this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).stitched();
 }

 bool IsStitched(int BodyPartIndex) {
 return this->getBodyParts().get(BodyPartIndex).stitched();
 }

 bool IsWounded(BodyPartType BodyPart) {
 return this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).deepWounded();
 }

 bool IsWounded(int BodyPartIndex) {
 return this->getBodyParts().get(BodyPartIndex).deepWounded();
 }

 void RestoreToFullHealth() {
 for (int int0 = 0; int0 < BodyPartType.ToIndex(BodyPartType.MAX); int0++) {
 this->getBodyParts().get(int0).RestoreToFullHealth();
 }

 if (this->getParentChar() != nullptr && this->getParentChar().getStats() != nullptr) {
 this->getParentChar().getStats().resetStats();
 }

 this->setInfected(false);
 this->setIsFakeInfected(false);
 this->setOverallBodyHealth(100.0F);
 this->setInfectionLevel(0.0F);
 this->setFakeInfectionLevel(0.0F);
 this->setBoredomLevel(0.0F);
 this->setWetness(0.0F);
 this->setCatchACold(0.0F);
 this->setHasACold(false);
 this->setColdStrength(0.0F);
 this->setSneezeCoughActive(0);
 this->setSneezeCoughTime(0);
 this->setTemperature(37.0F);
 this->setUnhappynessLevel(0.0F);
 this->PoisonLevel = 0.0F;
 this->setFoodSicknessLevel(0.0F);
 this->Temperature = 37.0F;
 this->lastTemperature = this->Temperature;
 this->setInfectionTime(-1.0F);
 this->setInfectionMortalityDuration(-1.0F);
 if (this->thermoregulator != nullptr) {
 this->thermoregulator.reset();
 }
 }

 void SetBandaged(int BodyPartIndex, bool Bandaged, float bandageLife, bool isAlcoholic, const std::string& bandageType) {
 this->getBodyParts().get(BodyPartIndex).setBandaged(Bandaged, bandageLife, isAlcoholic, bandageType);
 }

 void SetBitten(BodyPartType BodyPart, bool Bitten) {
 this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).SetBitten(Bitten);
 }

 void SetBitten(int BodyPartIndex, bool Bitten) {
 this->getBodyParts().get(BodyPartIndex).SetBitten(Bitten);
 }

 void SetBitten(int BodyPartIndex, bool Bitten, bool Infected) {
 this->getBodyParts().get(BodyPartIndex).SetBitten(Bitten, Infected);
 }

 void SetBleeding(BodyPartType BodyPart, bool Bleeding) {
 this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).setBleeding(Bleeding);
 }

 void SetBleeding(int BodyPartIndex, bool Bleeding) {
 this->getBodyParts().get(BodyPartIndex).setBleeding(Bleeding);
 }

 void SetBleedingStemmed(BodyPartType BodyPart, bool BleedingStemmed) {
 this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).SetBleedingStemmed(BleedingStemmed);
 }

 void SetBleedingStemmed(int BodyPartIndex, bool BleedingStemmed) {
 this->getBodyParts().get(BodyPartIndex).SetBleedingStemmed(BleedingStemmed);
 }

 void SetCortorised(BodyPartType BodyPart, bool Cortorised) {
 this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).SetCortorised(Cortorised);
 }

 void SetCortorised(int BodyPartIndex, bool Cortorised) {
 this->getBodyParts().get(BodyPartIndex).SetCortorised(Cortorised);
 }

 BodyPart setScratchedWindow() {
 int int0 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.ForeArm_R) + 1);
 this->getBodyPart(BodyPartType.FromIndex(int0).AddDamage(10.0F);
 this->getBodyPart(BodyPartType.FromIndex(int0).SetScratchedWindow(true);
 return this->getBodyPart(BodyPartType.FromIndex(int0);
 }

 void SetScratched(BodyPartType BodyPart, bool Scratched) {
 this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).setScratched(Scratched, false);
 }

 void SetScratched(int BodyPartIndex, bool Scratched) {
 this->getBodyParts().get(BodyPartIndex).setScratched(Scratched, false);
 }

 void SetScratchedFromWeapon(int BodyPartIndex, bool Scratched) {
 this->getBodyParts().get(BodyPartIndex).SetScratchedWeapon(Scratched);
 }

 void SetCut(int BodyPartIndex, bool Cut) {
 this->getBodyParts().get(BodyPartIndex).setCut(Cut, false);
 }

 void SetWounded(BodyPartType BodyPart, bool Wounded) {
 this->getBodyParts().get(BodyPartType.ToIndex(BodyPart).setDeepWounded(Wounded);
 }

 void SetWounded(int BodyPartIndex, bool Wounded) {
 this->getBodyParts().get(BodyPartIndex).setDeepWounded(Wounded);
 }

 void ShowDebugInfo() {
 if (this->getDamageModCount() > 0) {
 this->setDamageModCount(this->getDamageModCount() - 1);
 }
 }

 void UpdateBoredom() {
 if (!(this->getParentChar() instanceof IsoSurvivor) {
 if (!(this->getParentChar() instanceof IsoPlayer) || !((IsoPlayer)this->getParentChar()).Asleep) {
 if (this->getParentChar().getCurrentSquare().isInARoom()) {
 if (!this->getParentChar().isReading()) {
 this->setBoredomLevel((float)(this->getBoredomLevel() + ZomboidGlobals.BoredomIncreaseRate * GameTime.instance.getMultiplier()));
 } else {
 this->setBoredomLevel((float)(this->getBoredomLevel() + ZomboidGlobals.BoredomIncreaseRate / 5.0 * GameTime.instance.getMultiplier()));
 }

 if (this->getParentChar().IsSpeaking() && !this->getParentChar().callOut) {
 this->setBoredomLevel((float)(this->getBoredomLevel() - ZomboidGlobals.BoredomDecreaseRate * GameTime.instance.getMultiplier()));
 }

 if (this->getParentChar().getNumSurvivorsInVicinity() > 0) {
 this->setBoredomLevel((float)(this->getBoredomLevel() - ZomboidGlobals.BoredomDecreaseRate * 0.1F * GameTime.instance.getMultiplier()));
 }
 } else if (this->getParentChar().getVehicle() != nullptr) {
 float float0 = this->getParentChar().getVehicle().getCurrentSpeedKmHour();
 if (Math.abs(float0) <= 0.1F) {
 if (this->getParentChar().isReading()) {
 this->setBoredomLevel((float)(this->getBoredomLevel() + ZomboidGlobals.BoredomIncreaseRate / 5.0 * GameTime.instance.getMultiplier()));
 } else {
 this->setBoredomLevel((float)(this->getBoredomLevel() + ZomboidGlobals.BoredomIncreaseRate * GameTime.instance.getMultiplier()));
 }
 } else {
 this->setBoredomLevel((float)(this->getBoredomLevel() - ZomboidGlobals.BoredomDecreaseRate * 0.5 * GameTime.instance.getMultiplier()));
 }
 } else {
 this->setBoredomLevel((float)(this->getBoredomLevel() - ZomboidGlobals.BoredomDecreaseRate * 0.1F * GameTime.instance.getMultiplier()));
 }

 if (this->getParentChar().getStats().Drunkenness > 20.0F) {
 this->setBoredomLevel((float)(this->getBoredomLevel() - ZomboidGlobals.BoredomDecreaseRate * 2.0 * GameTime.instance.getMultiplier()));
 }

 if (this->getParentChar().getStats().Panic > 5.0F) {
 this->setBoredomLevel(0.0F);
 }

 if (this->getBoredomLevel() > 100.0F) {
 this->setBoredomLevel(100.0F);
 }

 if (this->getBoredomLevel() < 0.0F) {
 this->setBoredomLevel(0.0F);
 }

 if (this->getUnhappynessLevel() > 100.0F) {
 this->setUnhappynessLevel(100.0F);
 }

 if (this->getUnhappynessLevel() < 0.0F) {
 this->setUnhappynessLevel(0.0F);
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Bored) > 1 && !this->getParentChar().isReading()) {
 this->setUnhappynessLevel(
 (float)(
 this->getUnhappynessLevel()
 + ZomboidGlobals.UnhappinessIncrease
 * this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Bored)
 * GameTime.instance.getMultiplier()
 )
 );
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Stress) > 1 && !this->getParentChar().isReading()) {
 this->setUnhappynessLevel(
 (float)(
 this->getUnhappynessLevel()
 + ZomboidGlobals.UnhappinessIncrease
 / 2.0
 * this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Stress)
 * GameTime.instance.getMultiplier()
 )
 );
 }

 if (this->getParentChar().Traits.Smoker.isSet()) {
 this->getParentChar().setTimeSinceLastSmoke(this->getParentChar().getTimeSinceLastSmoke() + 1.0E-4F * GameTime.instance.getMultiplier());
 if (this->getParentChar().getTimeSinceLastSmoke() > 1.0F) {
 double double0 = Math.floor(this->getParentChar().getTimeSinceLastSmoke() / 10.0F) + 1.0;
 if (double0 > 10.0) {
 double0 = 10.0;
 }

 this->getParentChar()
 .getStats()
 .setStressFromCigarettes(
 (float)(
 this->getParentChar().getStats().getStressFromCigarettes()
 + ZomboidGlobals.StressFromBiteOrScratch / 8.0 * double0 * GameTime.instance.getMultiplier()
 )
 );
 }
 }
 }
 }
 }

 float getUnhappynessLevel() {
 return this->UnhappynessLevel;
 }

 float getBoredomLevel() {
 return this->BoredomLevel;
 }

 void UpdateStrength() {
 if (this->getParentChar() == this->getParentChar()) {
 int int0 = 0;
 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 2) {
 int0++;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 3) {
 int0 += 2;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 4) {
 int0 += 2;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 2) {
 int0++;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 3) {
 int0 += 2;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 4) {
 int0 += 2;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) == 2) {
 int0++;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) == 3) {
 int0 += 2;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) == 4) {
 int0 += 3;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Bleeding) == 2) {
 int0++;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Bleeding) == 3) {
 int0++;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Bleeding) == 4) {
 int0++;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Injured) == 2) {
 int0++;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Injured) == 3) {
 int0 += 2;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Injured) == 4) {
 int0 += 3;
 }

 this->getParentChar().setMaxWeight((int)(this->getParentChar().getMaxWeightBase() * this->getParentChar().getWeightMod()) - int0);
 if (this->getParentChar().getMaxWeight() < 0) {
 this->getParentChar().setMaxWeight(0);
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.FoodEaten) > 0) {
 this->getParentChar().setMaxWeight(this->getParentChar().getMaxWeight() + 2);
 }

 if (this->getParentChar() instanceof IsoPlayer) {
 this->getParentChar().setMaxWeight((int)(this->getParentChar().getMaxWeight() * ((IsoPlayer)this->getParentChar()).getMaxWeightDelta()));
 }
 }
 }

 float pickMortalityDuration() {
 float float0 = 1.0F;
 if (this->getParentChar().Traits.Resilient.isSet()) {
 float0 = 1.25F;
 }

 if (this->getParentChar().Traits.ProneToIllness.isSet()) {
 float0 = 0.75F;
 }

 switch (SandboxOptions.instance.Lore.Mortality.getValue()) {
 case 1:
 return 0.0F;
 case 2:
 return Rand.Next(0.0F, 30.0F) / 3600.0F * float0;
 case 3:
 return Rand.Next(0.5F, 1.0F) / 60.0F * float0;
 case 4:
 return Rand.Next(3.0F, 12.0F) * float0;
 case 5:
 return Rand.Next(2.0F, 3.0F) * 24.0F * float0;
 case 6:
 return Rand.Next(1.0F, 2.0F) * 7.0F * 24.0F * float0;
 case 7:
 return -1.0F;
 default:
 return -1.0F;
 }
 }

 void Update() {
 if (!(this->getParentChar() instanceof IsoZombie) {
 if (GameServer.bServer) {
 this->RestoreToFullHealth();
 uint8_t byte0 = ((IsoPlayer)this->getParentChar()).bleedingLevel;
 if (byte0 > 0) {
 float float0 = 1.0F / byte0 * 200.0F * GameTime.instance.getInvMultiplier();
 if (Rand.Next((int)float0) < float0 * 0.3F) {
 this->getParentChar().splatBloodFloor();
 }

 if (Rand.Next((int)float0) == 0) {
 this->getParentChar().splatBloodFloor();
 }
 }
 } else if (GameClient.bClient && this->getParentChar() instanceof IsoPlayer && ((IsoPlayer)this->getParentChar()).bRemote) {
 if (this->getParentChar().isAlive()) {
 this->RestoreToFullHealth();
 uint8_t byte1 = ((IsoPlayer)this->getParentChar()).bleedingLevel;
 if (byte1 > 0) {
 float float1 = 1.0F / byte1 * 200.0F * GameTime.instance.getInvMultiplier();
 if (Rand.Next((int)float1) < float1 * 0.3F) {
 this->getParentChar().splatBloodFloor();
 }

 if (Rand.Next((int)float1) == 0) {
 this->getParentChar().splatBloodFloor();
 }
 }
 }
 } else if (this->getParentChar().isGodMod()) {
 this->RestoreToFullHealth();
 ((IsoPlayer)this->getParentChar()).bleedingLevel = 0;
 } else if (this->getParentChar().isInvincible()) {
 this->setOverallBodyHealth(100.0F);

 for (int int0 = 0; int0 < BodyPartType.MAX.index(); int0++) {
 this->getBodyPart(BodyPartType.FromIndex(int0).SetHealth(100.0F);
 }
 } else {
 float float2 = this->ParentChar.getStats().Pain;
 int int1 = this->getNumPartsBleeding() * 2;
 int1 += this->getNumPartsScratched();
 int1 += this->getNumPartsBitten() * 6;
 if (this->getHealth() >= 60.0F && int1 <= 3) {
 int1 = 0;
 }

 ((IsoPlayer)this->getParentChar()).bleedingLevel = (byte)int1;
 if (int1 > 0) {
 float float3 = 1.0F / int1 * 200.0F * GameTime.instance.getInvMultiplier();
 if (Rand.Next((int)float3) < float3 * 0.3F) {
 this->getParentChar().splatBloodFloor();
 }

 if (Rand.Next((int)float3) == 0) {
 this->getParentChar().splatBloodFloor();
 }
 }

 if (this->thermoregulator != nullptr) {
 this->thermoregulator.update();
 }

 this->UpdateWetness();
 this->UpdateCold();
 this->UpdateBoredom();
 this->UpdateStrength();
 this->UpdatePanicState();
 this->UpdateTemperatureState();
 this->UpdateIllness();
 if (this->getOverallBodyHealth() != 0.0F) {
 if (this->PoisonLevel == 0.0F && this->getFoodSicknessLevel() > 0.0F) {
 this->setFoodSicknessLevel(
 this->getFoodSicknessLevel() - (float)(ZomboidGlobals.FoodSicknessDecrease * GameTime.instance.getMultiplier())
 );
 }

 if (!this->isInfected()) {
 for (int int2 = 0; int2 < BodyPartType.ToIndex(BodyPartType.MAX); int2++) {
 if (this->IsInfected(int2) {
 this->setInfected(true);
 if (this->IsFakeInfected(int2) {
 this->DisableFakeInfection(int2);
 this->setInfectionLevel(this->getFakeInfectionLevel());
 this->setFakeInfectionLevel(0.0F);
 this->setIsFakeInfected(false);
 this->setReduceFakeInfection(false);
 }
 }
 }

 if (this->isInfected() && this->getInfectionTime() < 0.0F && SandboxOptions.instance.Lore.Mortality.getValue() != 7) {
 this->setInfectionTime(this->getCurrentTimeForInfection());
 this->setInfectionMortalityDuration(this->pickMortalityDuration());
 }
 }

 if (!this->isInfected() && !this->isIsFakeInfected()) {
 for (int int3 = 0; int3 < BodyPartType.ToIndex(BodyPartType.MAX); int3++) {
 if (this->IsFakeInfected(int3) {
 this->setIsFakeInfected(true);
 break;
 }
 }
 }

 if (this->isIsFakeInfected() && !this->isReduceFakeInfection() && this->getParentChar().getReduceInfectionPower() == 0.0F) {
 this->setFakeInfectionLevel(this->getFakeInfectionLevel() + this->getInfectionGrowthRate() * GameTime.instance.getMultiplier());
 if (this->getFakeInfectionLevel() > 100.0F) {
 this->setFakeInfectionLevel(100.0F);
 this->setReduceFakeInfection(true);
 }
 }

 Stats stats = this->ParentChar.getStats();
 stats.Drunkenness = stats.Drunkenness - this->getDrunkReductionValue() * GameTime.instance.getMultiplier();
 if (this->getParentChar().getStats().Drunkenness < 0.0F) {
 this->ParentChar.getStats().Drunkenness = 0.0F;
 }

 float float4 = 0.0F;
 if (this->getHealthFromFoodTimer() > 0.0F) {
 float4 += this->getHealthFromFood() * GameTime.instance.getMultiplier();
 this->setHealthFromFoodTimer(this->getHealthFromFoodTimer() - 1.0F * GameTime.instance.getMultiplier());
 }

 uint8_t byte2 = 0;
 if (this->getParentChar() == this->getParentChar()
 && (
 this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 2
 || this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) == 2
 || this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 2
 )) {
 byte2 = 1;
 }

 if (this->getParentChar() == this->getParentChar()
 && (
 this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 3
 || this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) == 3
 || this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 3
 )) {
 byte2 = 2;
 }

 if (this->getParentChar() == this->getParentChar()
 && (
 this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 4
 || this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 4
 )) {
 byte2 = 3;
 }

 if (this->getParentChar().isAsleep()) {
 byte2 = -1;
 }

 switch (byte2) {
 case 0:
 float4 += this->getStandardHealthAddition() * GameTime.instance.getMultiplier();
 break;
 case 1:
 float4 += this->getReducedHealthAddition() * GameTime.instance.getMultiplier();
 break;
 case 2:
 float4 += this->getSeverlyReducedHealthAddition() * GameTime.instance.getMultiplier();
 break;
 case 3:
 float4 += 0.0F;
 }

 if (this->getParentChar().isAsleep()) {
 if (GameClient.bClient) {
 float4 += 15.0F * GameTime.instance.getGameWorldSecondsSinceLastUpdate() / 3600.0F;
 } else {
 float4 += this->getSleepingHealthAddition() * GameTime.instance.getMultiplier();
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 4
 || this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 4) {
 float4 = 0.0F;
 }
 }

 this->AddGeneralHealth(float4);
 float4 = 0.0F;
 float float5 = 0.0F;
 float float6 = 0.0F;
 float float7 = 0.0F;
 float float8 = 0.0F;
 float float9 = 0.0F;
 float float10 = 0.0F;
 if (this->PoisonLevel > 0.0F) {
 if (this->PoisonLevel > 10.0F && this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) >= 1) {
 float5 = 0.0035F * Math.min(this->PoisonLevel / 10.0F, 3.0F) * GameTime.instance.getMultiplier();
 float4 += float5;
 }

 float float11 = 0.0F;
 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.FoodEaten) > 0) {
 float11 = 1.5E-4F * this->getParentChar().getMoodles().getMoodleLevel(MoodleType.FoodEaten);
 }

 this->PoisonLevel = (float)(this->PoisonLevel - (float11 + ZomboidGlobals.PoisonLevelDecrease * GameTime.instance.getMultiplier()));
 if (this->PoisonLevel < 0.0F) {
 this->PoisonLevel = 0.0F;
 }

 this->setFoodSicknessLevel(
 this->getFoodSicknessLevel()
 + this->getInfectionGrowthRate() * (2 + Math.round(this->PoisonLevel / 10.0F) * GameTime.instance.getMultiplier()
 );
 if (this->getFoodSicknessLevel() > 100.0F) {
 this->setFoodSicknessLevel(100.0F);
 }
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Hungry) == 4) {
 float6 = this->getHealthReductionFromSevereBadMoodles() / 50.0F * GameTime.instance.getMultiplier();
 float4 += float6;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Sick) == 4 && this->FoodSicknessLevel > this->InfectionLevel) {
 float7 = this->getHealthReductionFromSevereBadMoodles() * GameTime.instance.getMultiplier();
 float4 += float7;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Bleeding) == 4) {
 float8 = this->getHealthReductionFromSevereBadMoodles() * GameTime.instance.getMultiplier();
 float4 += float8;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.Thirst) == 4) {
 float9 = this->getHealthReductionFromSevereBadMoodles() / 10.0F * GameTime.instance.getMultiplier();
 float4 += float9;
 }

 if (this->getParentChar().getMoodles().getMoodleLevel(MoodleType.HeavyLoad) > 2
 && this->getParentChar().getVehicle() == nullptr
 && !this->getParentChar().isAsleep()
 && !this->getParentChar().isSitOnGround()
 && this->getThermoregulator().getMetabolicTarget() != Metabolics.SeatedResting.getMet()
 && this->getHealth() > 75.0F
 && Rand.Next(Rand.AdjustForFramerate(10) == 0) {
 float10 = this->getHealthReductionFromSevereBadMoodles()
 / ((5 - this->getParentChar().getMoodles().getMoodleLevel(MoodleType.HeavyLoad) / 10.0F)
 * GameTime.instance.getMultiplier();
 float4 += float10;
 }

 this->ReduceGeneralHealth(float4);
 IsoGameCharacter character = this->getParentChar();
 if (float5 > 0.0F) {
 LuaEventManager.triggerEvent("OnPlayerGetDamage", character, "POISON", float5);
 }

 if (float6 > 0.0F) {
 LuaEventManager.triggerEvent("OnPlayerGetDamage", character, "HUNGRY", float6);
 }

 if (float7 > 0.0F) {
 LuaEventManager.triggerEvent("OnPlayerGetDamage", character, "SICK", float7);
 }

 if (float8 > 0.0F) {
 LuaEventManager.triggerEvent("OnPlayerGetDamage", character, "BLEEDING", float8);
 }

 if (float9 > 0.0F) {
 LuaEventManager.triggerEvent("OnPlayerGetDamage", character, "THIRST", float9);
 }

 if (float10 > 0.0F) {
 LuaEventManager.triggerEvent("OnPlayerGetDamage", character, "HEAVYLOAD", float10);
 }

 if (this->ParentChar.getPainEffect() > 0.0F) {
 stats = this->ParentChar.getStats();
 stats.Pain = stats.Pain - 0.023333333F * (GameTime.getInstance().getMultiplier() / 1.6F);
 this->ParentChar.setPainEffect(this->ParentChar.getPainEffect() - GameTime.getInstance().getMultiplier() / 1.6F);
 } else {
 this->ParentChar.setPainDelta(0.0F);
 float4 = 0.0F;

 for (int int4 = 0; int4 < BodyPartType.ToIndex(BodyPartType.MAX); int4++) {
 float4 += this->getBodyParts().get(int4).getPain() * BodyPartType.getPainModifyer(int4);
 }

 float4 -= this->getPainReduction();
 if (float4 > this->ParentChar.getStats().Pain) {
 stats = this->ParentChar.getStats();
 stats.Pain = stats.Pain + (float4 - this->ParentChar.getStats().Pain) / 500.0F;
 } else {
 this->ParentChar.getStats().Pain = float4;
 }
 }

 this->setPainReduction(this->getPainReduction() - 0.005F * GameTime.getInstance().getMultiplier());
 if (this->getPainReduction() < 0.0F) {
 this->setPainReduction(0.0F);
 }

 if (this->getParentChar().getStats().Pain > 100.0F) {
 this->ParentChar.getStats().Pain = 100.0F;
 }

 if (this->isInfected()) {
 int int5 = SandboxOptions.instance.Lore.Mortality.getValue();
 if (int5 == 1) {
 this->ReduceGeneralHealth(110.0F);
 LuaEventManager.triggerEvent("OnPlayerGetDamage", this->ParentChar, "INFECTION", 110);
 this->setInfectionLevel(100.0F);
 } else if (int5 != 7) {
 float float12 = this->getCurrentTimeForInfection();
 if (this->InfectionMortalityDuration < 0.0F) {
 this->InfectionMortalityDuration = this->pickMortalityDuration();
 }

 if (this->InfectionTime < 0.0F) {
 this->InfectionTime = float12;
 }

 if (this->InfectionTime > float12) {
 this->InfectionTime = float12;
 }

 float6 = (float12 - this->InfectionTime) / this->InfectionMortalityDuration;
 float6 = Math.min(float6, 1.0F);
 this->setInfectionLevel(float6 * 100.0F);
 if (float6 == 1.0F) {
 this->ReduceGeneralHealth(110.0F);
 LuaEventManager.triggerEvent("OnPlayerGetDamage", this->ParentChar, "INFECTION", 110);
 } else {
 float6 *= float6;
 float6 *= float6;
 float7 = (1.0F - float6) * 100.0F;
 float8 = this->getOverallBodyHealth() - float7;
 if (float8 > 0.0F && float7 <= 99.0F) {
 this->ReduceGeneralHealth(float8);
 LuaEventManager.triggerEvent("OnPlayerGetDamage", this->ParentChar, "INFECTION", float8);
 }
 }
 }
 }

 for (int int6 = 0; int6 < BodyPartType.ToIndex(BodyPartType.MAX); int6++) {
 this->getBodyParts().get(int6).DamageUpdate();
 }

 this->calculateOverallHealth();
 if (this->getOverallBodyHealth() <= 0.0F) {
 if (GameClient.bClient && this->getParentChar() instanceof IsoPlayer && !((IsoPlayer)this->getParentChar()).bRemote) {
 GameClient.sendPlayerDamage((IsoPlayer)this->getParentChar());
 }

 if (this->isIsOnFire()) {
 this->setBurntToDeath(true);

 for (int int7 = 0; int7 < BodyPartType.ToIndex(BodyPartType.MAX); int7++) {
 this->getBodyParts().get(int7).SetHealth(Rand.Next(90);
 }
 } else {
 this->setBurntToDeath(false);
 }
 }

 if (this->isReduceFakeInfection() && this->getOverallBodyHealth() > 0.0F) {
 this->setFakeInfectionLevel(this->getFakeInfectionLevel() - this->getInfectionGrowthRate() * GameTime.instance.getMultiplier() * 2.0F);
 }

 if (this->getParentChar().getReduceInfectionPower() > 0.0F && this->getOverallBodyHealth() > 0.0F) {
 this->setFakeInfectionLevel(this->getFakeInfectionLevel() - this->getInfectionGrowthRate() * GameTime.instance.getMultiplier());
 this->getParentChar()
 .setReduceInfectionPower(
 this->getParentChar().getReduceInfectionPower() - this->getInfectionGrowthRate() * GameTime.instance.getMultiplier()
 );
 if (this->getParentChar().getReduceInfectionPower() < 0.0F) {
 this->getParentChar().setReduceInfectionPower(0.0F);
 }
 }

 if (this->getFakeInfectionLevel() <= 0.0F) {
 for (int int8 = 0; int8 < BodyPartType.ToIndex(BodyPartType.MAX); int8++) {
 this->getBodyParts().get(int8).SetFakeInfected(false);
 }

 this->setIsFakeInfected(false);
 this->setFakeInfectionLevel(0.0F);
 this->setReduceFakeInfection(false);
 }

 if (float2 == this->ParentChar.getStats().Pain) {
 stats = this->ParentChar.getStats();
 stats.Pain = (float)(stats.Pain - 0.25 * (GameTime.getInstance().getMultiplier() / 1.6F);
 }

 if (this->ParentChar.getStats().Pain < 0.0F) {
 this->ParentChar.getStats().Pain = 0.0F;
 }
 }
 }
 }
 }

 void calculateOverallHealth() {
 float float0 = 0.0F;

 for (int int0 = 0; int0 < BodyPartType.ToIndex(BodyPartType.MAX); int0++) {
 BodyPart bodyPart = this->getBodyParts().get(int0);
 float0 += (100.0F - bodyPart.getHealth()) * BodyPartType.getDamageModifyer(int0);
 }

 float0 += this->getDamageFromPills();
 if (float0 > 100.0F) {
 float0 = 100.0F;
 }

 this->setOverallBodyHealth(100.0F - float0);
 }

 static float getSicknessFromCorpsesRate(int corpseCount) {
 if (SandboxOptions.instance.DecayingCorpseHealthImpact.getValue() == 1) {
 return 0.0F;
 } else if (corpseCount > 5) {
 float float0 = (float)ZomboidGlobals.FoodSicknessDecrease * 0.07F;
 switch (SandboxOptions.instance.DecayingCorpseHealthImpact.getValue()) {
 case 2:
 float0 = (float)ZomboidGlobals.FoodSicknessDecrease * 0.01F;
 break;
 case 4:
 float0 = (float)ZomboidGlobals.FoodSicknessDecrease * 0.11F;
 }

 int int0 = Math.min(corpseCount - 5, 20);
 return float0 * int0;
 } else {
 return 0.0F;
 }
 }

 void UpdateIllness() {
 if (SandboxOptions.instance.DecayingCorpseHealthImpact.getValue() != 1) {
 int int0 = FliesSound.instance.getCorpseCount(this->getParentChar());
 float float0 = getSicknessFromCorpsesRate(int0);
 if (float0 > 0.0F) {
 this->setFoodSicknessLevel(this->getFoodSicknessLevel() + float0 * GameTime.getInstance().getMultiplier());
 }
 }
 }

 void UpdateTemperatureState() {
 float float0 = 0.06F;
 if (this->getParentChar() instanceof IsoPlayer) {
 if (this->ColdDamageStage > 0.0F) {
 float float1 = 100.0F - this->ColdDamageStage * 100.0F;
 if (this->OverallBodyHealth > float1) {
 this->ReduceGeneralHealth(this->OverallBodyHealth - float1);
 }
 }

 ((IsoPlayer)this->getParentChar()).setMoveSpeed(float0);
 }
 }

 float getDamageFromPills() {
 if (this->getParentChar() instanceof IsoPlayer) {
 IsoPlayer player = (IsoPlayer)this->getParentChar();
 if (player.getSleepingPillsTaken() == 10) {
 return 40.0F;
 }

 if (player.getSleepingPillsTaken() == 11) {
 return 80.0F;
 }

 if (player.getSleepingPillsTaken() >= 12) {
 return 100.0F;
 }
 }

 return 0.0F;
 }

 bool UseBandageOnMostNeededPart() {
 uint8_t byte0 = 0;
 BodyPart bodyPart = nullptr;

 for (int int0 = 0; int0 < this->getBodyParts().size(); int0++) {
 uint8_t byte1 = 0;
 if (!this->getBodyParts().get(int0).bandaged()) {
 if (this->getBodyParts().get(int0).bleeding()) {
 byte1 += 100;
 }

 if (this->getBodyParts().get(int0).scratched()) {
 byte1 += 50;
 }

 if (this->getBodyParts().get(int0).bitten()) {
 byte1 += 50;
 }

 if (byte1 > byte0) {
 byte0 = byte1;
 bodyPart = this->getBodyParts().get(int0);
 }
 }
 }

 if (byte0 > 0 && bodyPart != nullptr) {
 bodyPart.setBandaged(true, 10.0F);
 return true;
 } else {
 return false;
 }
 }

 /**
 * @return the BodyParts
 */
 public ArrayList<BodyPart> getBodyParts() {
 return this->BodyParts;
 }

 /**
 * @return the DamageModCount
 */
 int getDamageModCount() {
 return this->DamageModCount;
 }

 /**
 * 
 * @param _DamageModCount the DamageModCount to set
 */
 void setDamageModCount(int _DamageModCount) {
 this->DamageModCount = _DamageModCount;
 }

 /**
 * @return the InfectionGrowthRate
 */
 float getInfectionGrowthRate() {
 return this->InfectionGrowthRate;
 }

 /**
 * 
 * @param _InfectionGrowthRate the InfectionGrowthRate to set
 */
 void setInfectionGrowthRate(float _InfectionGrowthRate) {
 this->InfectionGrowthRate = _InfectionGrowthRate;
 }

 /**
 * 
 * @param _InfectionLevel the InfectionLevel to set
 */
 void setInfectionLevel(float _InfectionLevel) {
 this->InfectionLevel = _InfectionLevel;
 }

 bool isInfected() {
 return this->IsInfected;
 }

 void setInfected(bool infected) {
 this->IsInfected = infected;
 }

 float getInfectionTime() {
 return this->InfectionTime;
 }

 void setInfectionTime(float worldHours) {
 this->InfectionTime = worldHours;
 }

 float getInfectionMortalityDuration() {
 return this->InfectionMortalityDuration;
 }

 void setInfectionMortalityDuration(float worldHours) {
 this->InfectionMortalityDuration = worldHours;
 }

 float getCurrentTimeForInfection() {
 return this->getParentChar() instanceof IsoPlayer
 ? (float)((IsoPlayer)this->getParentChar()).getHoursSurvived()
 : (float)GameTime.getInstance().getWorldAgeHours();
 }

 /**
 * @return the inf
 */
 bool isInf() {
 return this->IsInfected;
 }

 /**
 * 
 * @param inf the inf to set
 */
 void setInf(bool inf) {
 this->IsInfected = inf;
 }

 /**
 * @return the FakeInfectionLevel
 */
 float getFakeInfectionLevel() {
 return this->FakeInfectionLevel;
 }

 /**
 * 
 * @param _FakeInfectionLevel the FakeInfectionLevel to set
 */
 void setFakeInfectionLevel(float _FakeInfectionLevel) {
 this->FakeInfectionLevel = _FakeInfectionLevel;
 }

 /**
 * @return the IsFakeInfected
 */
 bool isIsFakeInfected() {
 return this->IsFakeInfected;
 }

 /**
 * 
 * @param _IsFakeInfected the IsFakeInfected to set
 */
 void setIsFakeInfected(bool _IsFakeInfected) {
 this->IsFakeInfected = _IsFakeInfected;
 this->getBodyParts().get(0).SetFakeInfected(_IsFakeInfected);
 }

 /**
 * @return the OverallBodyHealth
 */
 float getOverallBodyHealth() {
 return this->OverallBodyHealth;
 }

 /**
 * 
 * @param _OverallBodyHealth the OverallBodyHealth to set
 */
 void setOverallBodyHealth(float _OverallBodyHealth) {
 this->OverallBodyHealth = _OverallBodyHealth;
 }

 /**
 * @return the StandardHealthAddition
 */
 float getStandardHealthAddition() {
 return this->StandardHealthAddition;
 }

 /**
 * 
 * @param _StandardHealthAddition the StandardHealthAddition to set
 */
 void setStandardHealthAddition(float _StandardHealthAddition) {
 this->StandardHealthAddition = _StandardHealthAddition;
 }

 /**
 * @return the ReducedHealthAddition
 */
 float getReducedHealthAddition() {
 return this->ReducedHealthAddition;
 }

 /**
 * 
 * @param _ReducedHealthAddition the ReducedHealthAddition to set
 */
 void setReducedHealthAddition(float _ReducedHealthAddition) {
 this->ReducedHealthAddition = _ReducedHealthAddition;
 }

 /**
 * @return the SeverlyReducedHealthAddition
 */
 float getSeverlyReducedHealthAddition() {
 return this->SeverlyReducedHealthAddition;
 }

 /**
 * 
 * @param _SeverlyReducedHealthAddition the SeverlyReducedHealthAddition to set
 */
 void setSeverlyReducedHealthAddition(float _SeverlyReducedHealthAddition) {
 this->SeverlyReducedHealthAddition = _SeverlyReducedHealthAddition;
 }

 /**
 * @return the SleepingHealthAddition
 */
 float getSleepingHealthAddition() {
 return this->SleepingHealthAddition;
 }

 /**
 * 
 * @param _SleepingHealthAddition the SleepingHealthAddition to set
 */
 void setSleepingHealthAddition(float _SleepingHealthAddition) {
 this->SleepingHealthAddition = _SleepingHealthAddition;
 }

 /**
 * @return the HealthFromFood
 */
 float getHealthFromFood() {
 return this->HealthFromFood;
 }

 /**
 * 
 * @param _HealthFromFood the HealthFromFood to set
 */
 void setHealthFromFood(float _HealthFromFood) {
 this->HealthFromFood = _HealthFromFood;
 }

 /**
 * @return the HealthReductionFromSevereBadMoodles
 */
 float getHealthReductionFromSevereBadMoodles() {
 return this->HealthReductionFromSevereBadMoodles;
 }

 /**
 * 
 * @param _HealthReductionFromSevereBadMoodles the HealthReductionFromSevereBadMoodles to set
 */
 void setHealthReductionFromSevereBadMoodles(float _HealthReductionFromSevereBadMoodles) {
 this->HealthReductionFromSevereBadMoodles = _HealthReductionFromSevereBadMoodles;
 }

 /**
 * @return the StandardHealthFromFoodTime
 */
 int getStandardHealthFromFoodTime() {
 return this->StandardHealthFromFoodTime;
 }

 /**
 * 
 * @param _StandardHealthFromFoodTime the StandardHealthFromFoodTime to set
 */
 void setStandardHealthFromFoodTime(int _StandardHealthFromFoodTime) {
 this->StandardHealthFromFoodTime = _StandardHealthFromFoodTime;
 }

 /**
 * @return the HealthFromFoodTimer
 */
 float getHealthFromFoodTimer() {
 return this->HealthFromFoodTimer;
 }

 /**
 * 
 * @param _HealthFromFoodTimer the HealthFromFoodTimer to set
 */
 void setHealthFromFoodTimer(float _HealthFromFoodTimer) {
 this->HealthFromFoodTimer = _HealthFromFoodTimer;
 }

 /**
 * 
 * @param _BoredomLevel the BoredomLevel to set
 */
 void setBoredomLevel(float _BoredomLevel) {
 this->BoredomLevel = _BoredomLevel;
 }

 /**
 * @return the BoredomDecreaseFromReading
 */
 float getBoredomDecreaseFromReading() {
 return this->BoredomDecreaseFromReading;
 }

 /**
 * 
 * @param _BoredomDecreaseFromReading the BoredomDecreaseFromReading to set
 */
 void setBoredomDecreaseFromReading(float _BoredomDecreaseFromReading) {
 this->BoredomDecreaseFromReading = _BoredomDecreaseFromReading;
 }

 /**
 * @return the InitialThumpPain
 */
 float getInitialThumpPain() {
 return this->InitialThumpPain;
 }

 /**
 * 
 * @param _InitialThumpPain the InitialThumpPain to set
 */
 void setInitialThumpPain(float _InitialThumpPain) {
 this->InitialThumpPain = _InitialThumpPain;
 }

 /**
 * @return the InitialScratchPain
 */
 float getInitialScratchPain() {
 return this->InitialScratchPain;
 }

 /**
 * 
 * @param _InitialScratchPain the InitialScratchPain to set
 */
 void setInitialScratchPain(float _InitialScratchPain) {
 this->InitialScratchPain = _InitialScratchPain;
 }

 /**
 * @return the InitialBitePain
 */
 float getInitialBitePain() {
 return this->InitialBitePain;
 }

 /**
 * 
 * @param _InitialBitePain the InitialBitePain to set
 */
 void setInitialBitePain(float _InitialBitePain) {
 this->InitialBitePain = _InitialBitePain;
 }

 /**
 * @return the InitialWoundPain
 */
 float getInitialWoundPain() {
 return this->InitialWoundPain;
 }

 /**
 * 
 * @param _InitialWoundPain the InitialWoundPain to set
 */
 void setInitialWoundPain(float _InitialWoundPain) {
 this->InitialWoundPain = _InitialWoundPain;
 }

 /**
 * @return the ContinualPainIncrease
 */
 float getContinualPainIncrease() {
 return this->ContinualPainIncrease;
 }

 /**
 * 
 * @param _ContinualPainIncrease the ContinualPainIncrease to set
 */
 void setContinualPainIncrease(float _ContinualPainIncrease) {
 this->ContinualPainIncrease = _ContinualPainIncrease;
 }

 /**
 * @return the PainReductionFromMeds
 */
 float getPainReductionFromMeds() {
 return this->PainReductionFromMeds;
 }

 /**
 * 
 * @param _PainReductionFromMeds the PainReductionFromMeds to set
 */
 void setPainReductionFromMeds(float _PainReductionFromMeds) {
 this->PainReductionFromMeds = _PainReductionFromMeds;
 }

 /**
 * @return the StandardPainReductionWhenWell
 */
 float getStandardPainReductionWhenWell() {
 return this->StandardPainReductionWhenWell;
 }

 /**
 * 
 * @param _StandardPainReductionWhenWell the StandardPainReductionWhenWell to set
 */
 void setStandardPainReductionWhenWell(float _StandardPainReductionWhenWell) {
 this->StandardPainReductionWhenWell = _StandardPainReductionWhenWell;
 }

 /**
 * @return the OldNumZombiesVisible
 */
 int getOldNumZombiesVisible() {
 return this->OldNumZombiesVisible;
 }

 /**
 * 
 * @param _OldNumZombiesVisible the OldNumZombiesVisible to set
 */
 void setOldNumZombiesVisible(int _OldNumZombiesVisible) {
 this->OldNumZombiesVisible = _OldNumZombiesVisible;
 }

 /**
 * @return the CurrentNumZombiesVisible
 */
 int getCurrentNumZombiesVisible() {
 return this->CurrentNumZombiesVisible;
 }

 /**
 * 
 * @param _CurrentNumZombiesVisible the CurrentNumZombiesVisible to set
 */
 void setCurrentNumZombiesVisible(int _CurrentNumZombiesVisible) {
 this->CurrentNumZombiesVisible = _CurrentNumZombiesVisible;
 }

 /**
 * @return the PanicIncreaseValue
 */
 float getPanicIncreaseValue() {
 return this->PanicIncreaseValue;
 }

 float getPanicIncreaseValueFrame() {
 return this->PanicIncreaseValueFrame;
 }

 /**
 * 
 * @param _PanicIncreaseValue the PanicIncreaseValue to set
 */
 void setPanicIncreaseValue(float _PanicIncreaseValue) {
 this->PanicIncreaseValue = _PanicIncreaseValue;
 }

 /**
 * @return the PanicReductionValue
 */
 float getPanicReductionValue() {
 return this->PanicReductionValue;
 }

 /**
 * 
 * @param _PanicReductionValue the PanicReductionValue to set
 */
 void setPanicReductionValue(float _PanicReductionValue) {
 this->PanicReductionValue = _PanicReductionValue;
 }

 /**
 * @return the DrunkIncreaseValue
 */
 float getDrunkIncreaseValue() {
 return this->DrunkIncreaseValue;
 }

 /**
 * 
 * @param _DrunkIncreaseValue the DrunkIncreaseValue to set
 */
 void setDrunkIncreaseValue(float _DrunkIncreaseValue) {
 this->DrunkIncreaseValue = _DrunkIncreaseValue;
 }

 /**
 * @return the DrunkReductionValue
 */
 float getDrunkReductionValue() {
 return this->DrunkReductionValue;
 }

 /**
 * 
 * @param _DrunkReductionValue the DrunkReductionValue to set
 */
 void setDrunkReductionValue(float _DrunkReductionValue) {
 this->DrunkReductionValue = _DrunkReductionValue;
 }

 /**
 * @return the IsOnFire
 */
 bool isIsOnFire() {
 return this->IsOnFire;
 }

 /**
 * 
 * @param _IsOnFire the IsOnFire to set
 */
 void setIsOnFire(bool _IsOnFire) {
 this->IsOnFire = _IsOnFire;
 }

 /**
 * @return the BurntToDeath
 */
 bool isBurntToDeath() {
 return this->BurntToDeath;
 }

 /**
 * 
 * @param _BurntToDeath the BurntToDeath to set
 */
 void setBurntToDeath(bool _BurntToDeath) {
 this->BurntToDeath = _BurntToDeath;
 }

 /**
 * 
 * @param _Wetness the Wetness to set
 */
 void setWetness(float _Wetness) {
 float float0 = 0.0F;
 if (this->BodyParts.size() > 0) {
 for (int int0 = 0; int0 < this->BodyParts.size(); int0++) {
 BodyPart bodyPart = this->BodyParts.get(int0);
 bodyPart.setWetness(_Wetness);
 float0 += bodyPart.getWetness();
 }

 float0 /= this->BodyParts.size();
 }

 this->Wetness = PZMath.clamp(float0, 0.0F, 100.0F);
 }

 /**
 * @return the CatchACold
 */
 float getCatchACold() {
 return this->CatchACold;
 }

 /**
 * 
 * @param _CatchACold the CatchACold to set
 */
 void setCatchACold(float _CatchACold) {
 this->CatchACold = _CatchACold;
 }

 /**
 * @return the HasACold
 */
 bool isHasACold() {
 return this->HasACold;
 }

 /**
 * 
 * @param _HasACold the HasACold to set
 */
 void setHasACold(bool _HasACold) {
 this->HasACold = _HasACold;
 }

 /**
 * 
 * @param _ColdStrength the ColdStrength to set
 */
 void setColdStrength(float _ColdStrength) {
 this->ColdStrength = _ColdStrength;
 }

 /**
 * @return the ColdProgressionRate
 */
 float getColdProgressionRate() {
 return this->ColdProgressionRate;
 }

 /**
 * 
 * @param _ColdProgressionRate the ColdProgressionRate to set
 */
 void setColdProgressionRate(float _ColdProgressionRate) {
 this->ColdProgressionRate = _ColdProgressionRate;
 }

 /**
 * @return the TimeToSneezeOrCough
 */
 int getTimeToSneezeOrCough() {
 return this->TimeToSneezeOrCough;
 }

 /**
 * 
 * @param _TimeToSneezeOrCough the TimeToSneezeOrCough to set
 */
 void setTimeToSneezeOrCough(int _TimeToSneezeOrCough) {
 this->TimeToSneezeOrCough = _TimeToSneezeOrCough;
 }

 /**
 * @return the MildColdSneezeTimerMin
 */
 int getMildColdSneezeTimerMin() {
 return this->MildColdSneezeTimerMin;
 }

 /**
 * 
 * @param _MildColdSneezeTimerMin the MildColdSneezeTimerMin to set
 */
 void setMildColdSneezeTimerMin(int _MildColdSneezeTimerMin) {
 this->MildColdSneezeTimerMin = _MildColdSneezeTimerMin;
 }

 /**
 * @return the MildColdSneezeTimerMax
 */
 int getMildColdSneezeTimerMax() {
 return this->MildColdSneezeTimerMax;
 }

 /**
 * 
 * @param _MildColdSneezeTimerMax the MildColdSneezeTimerMax to set
 */
 void setMildColdSneezeTimerMax(int _MildColdSneezeTimerMax) {
 this->MildColdSneezeTimerMax = _MildColdSneezeTimerMax;
 }

 /**
 * @return the ColdSneezeTimerMin
 */
 int getColdSneezeTimerMin() {
 return this->ColdSneezeTimerMin;
 }

 /**
 * 
 * @param _ColdSneezeTimerMin the ColdSneezeTimerMin to set
 */
 void setColdSneezeTimerMin(int _ColdSneezeTimerMin) {
 this->ColdSneezeTimerMin = _ColdSneezeTimerMin;
 }

 /**
 * @return the ColdSneezeTimerMax
 */
 int getColdSneezeTimerMax() {
 return this->ColdSneezeTimerMax;
 }

 /**
 * 
 * @param _ColdSneezeTimerMax the ColdSneezeTimerMax to set
 */
 void setColdSneezeTimerMax(int _ColdSneezeTimerMax) {
 this->ColdSneezeTimerMax = _ColdSneezeTimerMax;
 }

 /**
 * @return the NastyColdSneezeTimerMin
 */
 int getNastyColdSneezeTimerMin() {
 return this->NastyColdSneezeTimerMin;
 }

 /**
 * 
 * @param _NastyColdSneezeTimerMin the NastyColdSneezeTimerMin to set
 */
 void setNastyColdSneezeTimerMin(int _NastyColdSneezeTimerMin) {
 this->NastyColdSneezeTimerMin = _NastyColdSneezeTimerMin;
 }

 /**
 * @return the NastyColdSneezeTimerMax
 */
 int getNastyColdSneezeTimerMax() {
 return this->NastyColdSneezeTimerMax;
 }

 /**
 * 
 * @param _NastyColdSneezeTimerMax the NastyColdSneezeTimerMax to set
 */
 void setNastyColdSneezeTimerMax(int _NastyColdSneezeTimerMax) {
 this->NastyColdSneezeTimerMax = _NastyColdSneezeTimerMax;
 }

 /**
 * @return the SneezeCoughActive
 */
 int getSneezeCoughActive() {
 return this->SneezeCoughActive;
 }

 /**
 * 
 * @param _SneezeCoughActive the SneezeCoughActive to set
 */
 void setSneezeCoughActive(int _SneezeCoughActive) {
 this->SneezeCoughActive = _SneezeCoughActive;
 }

 /**
 * @return the SneezeCoughTime
 */
 int getSneezeCoughTime() {
 return this->SneezeCoughTime;
 }

 /**
 * 
 * @param _SneezeCoughTime the SneezeCoughTime to set
 */
 void setSneezeCoughTime(int _SneezeCoughTime) {
 this->SneezeCoughTime = _SneezeCoughTime;
 }

 /**
 * @return the SneezeCoughDelay
 */
 int getSneezeCoughDelay() {
 return this->SneezeCoughDelay;
 }

 /**
 * 
 * @param _SneezeCoughDelay the SneezeCoughDelay to set
 */
 void setSneezeCoughDelay(int _SneezeCoughDelay) {
 this->SneezeCoughDelay = _SneezeCoughDelay;
 }

 /**
 * 
 * @param _UnhappynessLevel the UnhappynessLevel to set
 */
 void setUnhappynessLevel(float _UnhappynessLevel) {
 this->UnhappynessLevel = _UnhappynessLevel;
 }

 /**
 * @return the ParentChar
 */
 IsoGameCharacter getParentChar() {
 return this->ParentChar;
 }

 /**
 * 
 * @param _ParentChar the ParentChar to set
 */
 void setParentChar(IsoGameCharacter _ParentChar) {
 this->ParentChar = _ParentChar;
 }

 /**
 * @return the body temperature (updated by lua)
 */
 float getTemperature() {
 return this->Temperature;
 }

 void setTemperature(float t) {
 this->lastTemperature = this->Temperature;
 this->Temperature = t;
 }

 float getTemperatureChangeTick() {
 return this->Temperature - this->lastTemperature;
 }

 void setPoisonLevel(float poisonLevel) {
 this->PoisonLevel = poisonLevel;
 }

 float getPoisonLevel() {
 return this->PoisonLevel;
 }

 float getFoodSicknessLevel() {
 return this->FoodSicknessLevel;
 }

 void setFoodSicknessLevel(float foodSicknessLevel) {
 this->FoodSicknessLevel = Math.max(foodSicknessLevel, 0.0F);
 }

 bool isReduceFakeInfection() {
 return this->reduceFakeInfection;
 }

 void setReduceFakeInfection(bool _reduceFakeInfection) {
 this->reduceFakeInfection = _reduceFakeInfection;
 }

 void AddRandomDamage() {
 BodyPart bodyPart = this->getBodyParts().get(Rand.Next(this->getBodyParts().size()));
 switch (Rand.Next(4) {
 case 0:
 bodyPart.generateDeepWound();
 if (Rand.Next(4) == 0) {
 bodyPart.setInfectedWound(true);
 }
 break;
 case 1:
 bodyPart.generateDeepShardWound();
 if (Rand.Next(4) == 0) {
 bodyPart.setInfectedWound(true);
 }
 break;
 case 2:
 bodyPart.setFractureTime(Rand.Next(30, 50);
 break;
 case 3:
 bodyPart.setBurnTime(Rand.Next(30, 50);
 }
 }

 float getPainReduction() {
 return this->painReduction;
 }

 void setPainReduction(float _painReduction) {
 this->painReduction = _painReduction;
 }

 float getColdReduction() {
 return this->coldReduction;
 }

 void setColdReduction(float _coldReduction) {
 this->coldReduction = _coldReduction;
 }

 int getRemotePainLevel() {
 return this->RemotePainLevel;
 }

 void setRemotePainLevel(int painLevel) {
 this->RemotePainLevel = painLevel;
 }

 float getColdDamageStage() {
 return this->ColdDamageStage;
 }

 void setColdDamageStage(float coldDamageStage) {
 this->ColdDamageStage = coldDamageStage;
 }

 Thermoregulator getThermoregulator() {
 return this->thermoregulator;
 }

 void decreaseBodyWetness(float amount) {
 float float0 = 0.0F;
 if (this->BodyParts.size() > 0) {
 for (int int0 = 0; int0 < this->BodyParts.size(); int0++) {
 BodyPart bodyPart = this->BodyParts.get(int0);
 bodyPart.setWetness(bodyPart.getWetness() - amount);
 float0 += bodyPart.getWetness();
 }

 float0 /= this->BodyParts.size();
 }

 this->Wetness = PZMath.clamp(float0, 0.0F, 100.0F);
 }

 void increaseBodyWetness(float amount) {
 float float0 = 0.0F;
 if (this->BodyParts.size() > 0) {
 for (int int0 = 0; int0 < this->BodyParts.size(); int0++) {
 BodyPart bodyPart = this->BodyParts.get(int0);
 bodyPart.setWetness(bodyPart.getWetness() + amount);
 float0 += bodyPart.getWetness();
 }

 float0 /= this->BodyParts.size();
 }

 this->Wetness = PZMath.clamp(float0, 0.0F, 100.0F);
 }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
