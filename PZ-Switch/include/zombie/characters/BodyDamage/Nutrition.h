#pragma once
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/ai/states/ClimbOverFenceState.h"
#include "zombie/ai/states/ClimbThroughWindowState.h"
#include "zombie/ai/states/SwipeStatePlayer.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace BodyDamage {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Nutrition {
public:
 IsoPlayer parent;
 float carbohydrates = 0.0F;
 float lipids = 0.0F;
 float proteins = 0.0F;
 float calories = 0.0F;
 float carbohydratesDecreraseFemale = 0.0032F;
 float carbohydratesDecreraseMale = 0.0035F;
 float lipidsDecreraseFemale = 7.0E-4F;
 float lipidsDecreraseMale = 0.00113F;
 float proteinsDecreraseFemale = 7.0E-4F;
 float proteinsDecreraseMale = 8.6E-4F;
 float caloriesDecreraseFemaleNormal = 0.016F;
 float caloriesDecreaseMaleNormal = 0.016F;
 float caloriesDecreraseFemaleExercise = 0.13F;
 float caloriesDecreaseMaleExercise = 0.13F;
 float caloriesDecreraseFemaleSleeping = 0.003F;
 float caloriesDecreaseMaleSleeping = 0.003F;
 int caloriesToGainWeightMale = 1100;
 int caloriesToGainWeightMaxMale = 4000;
 int caloriesToGainWeightFemale = 1000;
 int caloriesToGainWeightMaxFemale = 3000;
 int caloriesDecreaseMax = 2500;
 float weightGain = 1.3E-5F;
 float weightLoss = 8.5E-6F;
 double weight = 60.0;
 int updatedWeight = 0;
 bool isFemale = false;
 int syncWeightTimer = 0;
 float caloriesMax = 0.0F;
 float caloriesMin = 0.0F;
 bool incWeight = false;
 bool incWeightLot = false;
 bool decWeight = false;

public
 Nutrition(IsoPlayer _parent) {
 this->parent = _parent;
 if (this->isFemale) {
 this->setWeight(60.0);
 } else {
 this->setWeight(80.0);
 }

 this->setCalories(800.0F);
 }

 void update() {
 if (!GameServer.bServer) {
 if (SandboxOptions.instance.Nutrition.getValue()) {
 if (this->parent != nullptr && !this->parent.isDead()) {
 if (!GameClient.bClient || this->parent.isLocalPlayer()) {
 this->setCarbohydrates(
 this->getCarbohydrates() -
 (this->isFemale ? this->carbohydratesDecreraseFemale
 : this->carbohydratesDecreraseMale) *
 GameTime.getInstance()
 .getGameWorldSecondsSinceLastUpdate());
 this->setLipids(this->getLipids() -
 (this->isFemale ? this->lipidsDecreraseFemale
 : this->lipidsDecreraseMale) *
 GameTime.getInstance()
 .getGameWorldSecondsSinceLastUpdate());
 this->setProteins(this->getProteins() -
 (this->isFemale ? this->proteinsDecreraseFemale
 : this->proteinsDecreraseMale) *
 GameTime.getInstance()
 .getGameWorldSecondsSinceLastUpdate());
 this->updateCalories();
 this->updateWeight();
 }
 }
 }
 }
 }

 void updateCalories() {
 float float0 = 1.0F;
 if (!this->parent.getCharacterActions().empty()) {
 float0 = this->parent.getCharacterActions().get(0).caloriesModifier;
 }

 if (this->parent.isCurrentState(SwipeStatePlayer.instance()) ||
 this->parent.isCurrentState(ClimbOverFenceState.instance()) ||
 this->parent.isCurrentState(ClimbThroughWindowState.instance())) {
 float0 = 8.0F;
 }

 float float1 = 1.0F;
 if (this->parent.getBodyDamage() != nullptr &&
 this->parent.getBodyDamage().getThermoregulator() != nullptr) {
 float1 = (float)this->parent.getBodyDamage()
 .getThermoregulator()
 .getEnergyMultiplier();
 }

 float float2 = (float)(this->getWeight() / 80.0);
 if (this->parent.IsRunning() && this->parent.isPlayerMoving()) {
 float0 = 1.0F;
 this->setCalories(
 this->getCalories() -
 (this->isFemale ? this->caloriesDecreraseFemaleExercise
 : this->caloriesDecreaseMaleExercise) *
 float0 * float2 *
 GameTime.getInstance().getGameWorldSecondsSinceLastUpdate());
 } else if (this->parent.isSprinting() && this->parent.isPlayerMoving()) {
 float0 = 1.3F;
 this->setCalories(
 this->getCalories() -
 (this->isFemale ? this->caloriesDecreraseFemaleExercise
 : this->caloriesDecreaseMaleExercise) *
 float0 * float2 *
 GameTime.getInstance().getGameWorldSecondsSinceLastUpdate());
 } else if (this->parent.isPlayerMoving()) {
 float0 = 0.6F;
 this->setCalories(
 this->getCalories() -
 (this->isFemale ? this->caloriesDecreraseFemaleExercise
 : this->caloriesDecreaseMaleExercise) *
 float0 * float2 *
 GameTime.getInstance().getGameWorldSecondsSinceLastUpdate());
 } else if (this->parent.isAsleep()) {
 this->setCalories(
 this->getCalories() -
 (this->isFemale ? this->caloriesDecreraseFemaleSleeping
 : this->caloriesDecreaseMaleSleeping) *
 float0 * float1 * float2 *
 GameTime.getInstance().getGameWorldSecondsSinceLastUpdate());
 } else {
 this->setCalories(
 this->getCalories() -
 (this->isFemale ? this->caloriesDecreraseFemaleNormal
 : this->caloriesDecreaseMaleNormal) *
 float0 * float1 * float2 *
 GameTime.getInstance().getGameWorldSecondsSinceLastUpdate());
 }

 if (this->getCalories() > this->caloriesMax) {
 this->caloriesMax = this->getCalories();
 }

 if (this->getCalories() < this->caloriesMin) {
 this->caloriesMin = this->getCalories();
 }
 }

 void updateWeight() {
 this->setIncWeight(false);
 this->setIncWeightLot(false);
 this->setDecWeight(false);
 float float0 = this->caloriesToGainWeightMale;
 float float1 = this->caloriesToGainWeightMaxMale;
 float float2 = 0.0F;
 if (this->isFemale) {
 float0 = this->caloriesToGainWeightFemale;
 float1 = this->caloriesToGainWeightMaxFemale;
 }

 float float3 = (float)((this->getWeight() - 80.0) * 40.0);
 float0 = 1600.0F + float3;
 float2 = (float)((this->getWeight() - 70.0) * 30.0);
 if (float2 > 0.0F) {
 float2 = 0.0F;
 }

 if (this->getCalories() > float0) {
 this->setIncWeight(true);
 float float4 = this->getCalories() / float1;
 if (float4 > 1.0F) {
 float4 = 1.0F;
 }

 float float5 = this->weightGain;
 if (this->getCarbohydrates() > 700.0F || this->getLipids() > 700.0F) {
 float5 *= 3.0F;
 this->setIncWeightLot(true);
 } else if (this->getCarbohydrates() > 400.0F ||
 this->getLipids() > 400.0F) {
 float5 *= 2.0F;
 this->setIncWeightLot(true);
 }

 this->setWeight(
 this->getWeight() +
 float5 * float4 *
 GameTime.getInstance().getGameWorldSecondsSinceLastUpdate());
 } else if (this->getCalories() < float2) {
 this->setDecWeight(true);
 float float6 = Math.abs(this->getCalories()) / this->caloriesDecreaseMax;
 if (float6 > 1.0F) {
 float6 = 1.0F;
 }

 this->setWeight(
 this->getWeight() -
 this->weightLoss * float6 *
 GameTime.getInstance().getGameWorldSecondsSinceLastUpdate());
 }

 this->updatedWeight++;
 if (this->updatedWeight >= 2000) {
 this->applyTraitFromWeight();
 this->updatedWeight = 0;
 }

 if (GameClient.bClient) {
 this->syncWeightTimer++;
 if (this->syncWeightTimer >= 5000) {
 GameClient.sendWeight(this->parent);
 this->syncWeightTimer = 0;
 }
 }
 }

 void syncWeight() { GameClient.sendWeight(this->parent); }

 void save(ByteBuffer output) {
 output.putFloat(this->getCalories());
 output.putFloat(this->getProteins());
 output.putFloat(this->getLipids());
 output.putFloat(this->getCarbohydrates());
 output.putFloat((float)this->getWeight());
 }

 void load(ByteBuffer input) {
 this->setCalories(input.getFloat());
 this->setProteins(input.getFloat());
 this->setLipids(input.getFloat());
 this->setCarbohydrates(input.getFloat());
 this->setWeight(input.getFloat());
 }

 void applyWeightFromTraits() {
 if (this->parent.getTraits() != nullptr &&
 !this->parent.getTraits().empty()) {
 if (this->parent.Traits.Emaciated.isSet()) {
 this->setWeight(50.0);
 }

 if (this->parent.Traits.VeryUnderweight.isSet()) {
 this->setWeight(60.0);
 }

 if (this->parent.Traits.Underweight.isSet()) {
 this->setWeight(70.0);
 }

 if (this->parent.Traits.Overweight.isSet()) {
 this->setWeight(95.0);
 }

 if (this->parent.Traits.Obese.isSet()) {
 this->setWeight(105.0);
 }
 }
 }

 /**
 * > 100 obese 85 to 100 over weight 75 to 85 normal 65 to 75 underweight 50
 * to 65 very underweight <= 50 emaciated
 */
 void applyTraitFromWeight() {
 this->parent.getTraits().remove("Underweight");
 this->parent.getTraits().remove("Very Underweight");
 this->parent.getTraits().remove("Emaciated");
 this->parent.getTraits().remove("Overweight");
 this->parent.getTraits().remove("Obese");
 if (this->getWeight() >= 100.0) {
 this->parent.getTraits().add("Obese");
 }

 if (this->getWeight() >= 85.0 && this->getWeight() < 100.0) {
 this->parent.getTraits().add("Overweight");
 }

 if (this->getWeight() > 65.0 && this->getWeight() <= 75.0) {
 this->parent.getTraits().add("Underweight");
 }

 if (this->getWeight() > 50.0 && this->getWeight() <= 65.0) {
 this->parent.getTraits().add("Very Underweight");
 }

 if (this->getWeight() <= 50.0) {
 this->parent.getTraits().add("Emaciated");
 }
 }

 bool characterHaveWeightTrouble() {
 return this->parent.Traits.Emaciated.isSet() ||
 this->parent.Traits.Obese.isSet() ||
 this->parent.Traits.VeryUnderweight.isSet() ||
 this->parent.Traits.Underweight.isSet() ||
 this->parent.Traits.Overweight.isSet();
 }

 /**
 * You gain xp only if you're in good shape As underweight or overweight you
 * can still be "fit"
 */
 bool canAddFitnessXp() {
 if (this->parent.getPerkLevel(PerkFactory.Perks.Fitness) >= 9 &&
 this->characterHaveWeightTrouble()) {
 return false;
 } else {
 return this->parent.getPerkLevel(PerkFactory.Perks.Fitness) < 6
 ? true
 : !this->parent.Traits.Emaciated.isSet() &&
 !this->parent.Traits.Obese.isSet() &&
 !this->parent.Traits.VeryUnderweight.isSet();
 }
 }

 float getCarbohydrates() { return this->carbohydrates; }

 void setCarbohydrates(float _carbohydrates) {
 if (_carbohydrates < -500.0F) {
 _carbohydrates = -500.0F;
 }

 if (_carbohydrates > 1000.0F) {
 _carbohydrates = 1000.0F;
 }

 this->carbohydrates = _carbohydrates;
 }

 float getProteins() { return this->proteins; }

 void setProteins(float _proteins) {
 if (_proteins < -500.0F) {
 _proteins = -500.0F;
 }

 if (_proteins > 1000.0F) {
 _proteins = 1000.0F;
 }

 this->proteins = _proteins;
 }

 float getCalories() { return this->calories; }

 void setCalories(float _calories) {
 if (_calories < -2200.0F) {
 _calories = -2200.0F;
 }

 if (_calories > 3700.0F) {
 _calories = 3700.0F;
 }

 this->calories = _calories;
 }

 float getLipids() { return this->lipids; }

 void setLipids(float _lipids) {
 if (_lipids < -500.0F) {
 _lipids = -500.0F;
 }

 if (_lipids > 1000.0F) {
 _lipids = 1000.0F;
 }

 this->lipids = _lipids;
 }

 double getWeight() { return this->weight; }

 void setWeight(double _weight) {
 if (_weight < 35.0) {
 _weight = 35.0;
 float float0 =
 this->parent.getBodyDamage().getHealthReductionFromSevereBadMoodles() *
 GameTime.instance.getMultiplier();
 this->parent.getBodyDamage().ReduceGeneralHealth(float0);
 LuaEventManager.triggerEvent("OnPlayerGetDamage", this->parent,
 "LOWWEIGHT", float0);
 }

 this->weight = _weight;
 }

 bool isIncWeight() { return this->incWeight; }

 void setIncWeight(bool _incWeight) { this->incWeight = _incWeight; }

 bool isIncWeightLot() { return this->incWeightLot; }

 void setIncWeightLot(bool _incWeightLot) {
 this->incWeightLot = _incWeightLot;
 }

 bool isDecWeight() { return this->decWeight; }

 void setDecWeight(bool _decWeight) { this->decWeight = _decWeight; }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
