#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/ai/states/ClimbOverFenceState.h"
#include "zombie/ai/states/ClimbThroughWindowState.h"
#include "zombie/ai/states/SwipeStatePlayer.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <filesystem>

namespace zombie {
namespace characters {
namespace BodyDamage {


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

    public Nutrition(IsoPlayer var1) {
      this.parent = var1;
      if (this.isFemale) {
         this.setWeight(60.0);
      } else {
         this.setWeight(80.0);
      }

      this.setCalories(800.0F);
   }

    void update() {
      if (!GameServer.bServer) {
         if (SandboxOptions.instance.Nutrition.getValue()) {
            if (this.parent != nullptr && !this.parent.isDead()) {
               if (!GameClient.bClient || this.parent.isLocalPlayer()) {
                  this.setCarbohydrates(
                     this.getCarbohydrates()
                        - (this.isFemale ? this.carbohydratesDecreraseFemale : this.carbohydratesDecreraseMale)
                           * GameTime.getInstance().getGameWorldSecondsSinceLastUpdate()
                  );
                  this.setLipids(
                     this.getLipids()
                        - (this.isFemale ? this.lipidsDecreraseFemale : this.lipidsDecreraseMale) * GameTime.getInstance().getGameWorldSecondsSinceLastUpdate()
                  );
                  this.setProteins(
                     this.getProteins()
                        - (this.isFemale ? this.proteinsDecreraseFemale : this.proteinsDecreraseMale)
                           * GameTime.getInstance().getGameWorldSecondsSinceLastUpdate()
                  );
                  this.updateCalories();
                  this.updateWeight();
               }
            }
         }
      }
   }

    void updateCalories() {
    float var1 = 1.0F;
      if (!this.parent.getCharacterActions().empty()) {
         var1 = ((BaseAction)this.parent.getCharacterActions().get(0)).caloriesModifier;
      }

      if (this.parent.isCurrentState(SwipeStatePlayer.instance())
         || this.parent.isCurrentState(ClimbOverFenceState.instance())
         || this.parent.isCurrentState(ClimbThroughWindowState.instance())) {
         var1 = 8.0F;
      }

    float var2 = 1.0F;
      if (this.parent.getBodyDamage() != nullptr && this.parent.getBodyDamage().getThermoregulator() != nullptr) {
         var2 = (float)this.parent.getBodyDamage().getThermoregulator().getEnergyMultiplier();
      }

    float var3 = (float)(this.getWeight() / 80.0);
      if (this.parent.IsRunning() && this.parent.isPlayerMoving()) {
         var1 = 1.0F;
         this.setCalories(
            this.getCalories()
               - (this.isFemale ? this.caloriesDecreraseFemaleExercise : this.caloriesDecreaseMaleExercise)
                  * var1
                  * var3
                  * GameTime.getInstance().getGameWorldSecondsSinceLastUpdate()
         );
      } else if (this.parent.isSprinting() && this.parent.isPlayerMoving()) {
         var1 = 1.3F;
         this.setCalories(
            this.getCalories()
               - (this.isFemale ? this.caloriesDecreraseFemaleExercise : this.caloriesDecreaseMaleExercise)
                  * var1
                  * var3
                  * GameTime.getInstance().getGameWorldSecondsSinceLastUpdate()
         );
      } else if (this.parent.isPlayerMoving()) {
         var1 = 0.6F;
         this.setCalories(
            this.getCalories()
               - (this.isFemale ? this.caloriesDecreraseFemaleExercise : this.caloriesDecreaseMaleExercise)
                  * var1
                  * var3
                  * GameTime.getInstance().getGameWorldSecondsSinceLastUpdate()
         );
      } else if (this.parent.isAsleep()) {
         this.setCalories(
            this.getCalories()
               - (this.isFemale ? this.caloriesDecreraseFemaleSleeping : this.caloriesDecreaseMaleSleeping)
                  * var1
                  * var2
                  * var3
                  * GameTime.getInstance().getGameWorldSecondsSinceLastUpdate()
         );
      } else {
         this.setCalories(
            this.getCalories()
               - (this.isFemale ? this.caloriesDecreraseFemaleNormal : this.caloriesDecreaseMaleNormal)
                  * var1
                  * var2
                  * var3
                  * GameTime.getInstance().getGameWorldSecondsSinceLastUpdate()
         );
      }

      if (this.getCalories() > this.caloriesMax) {
         this.caloriesMax = this.getCalories();
      }

      if (this.getCalories() < this.caloriesMin) {
         this.caloriesMin = this.getCalories();
      }
   }

    void updateWeight() {
      this.setIncWeight(false);
      this.setIncWeightLot(false);
      this.setDecWeight(false);
    float var1 = this.caloriesToGainWeightMale;
    float var2 = this.caloriesToGainWeightMaxMale;
    float var3 = 0.0F;
      if (this.isFemale) {
         var1 = this.caloriesToGainWeightFemale;
         var2 = this.caloriesToGainWeightMaxFemale;
      }

    float var4 = (float)((this.getWeight() - 80.0) * 40.0);
      var1 = 1600.0F + var4;
      var3 = (float)((this.getWeight() - 70.0) * 30.0);
      if (var3 > 0.0F) {
         var3 = 0.0F;
      }

      if (this.getCalories() > var1) {
         this.setIncWeight(true);
    float var5 = this.getCalories() / var2;
         if (var5 > 1.0F) {
            var5 = 1.0F;
         }

    float var6 = this.weightGain;
         if (this.getCarbohydrates() > 700.0F || this.getLipids() > 700.0F) {
            var6 *= 3.0F;
            this.setIncWeightLot(true);
         } else if (this.getCarbohydrates() > 400.0F || this.getLipids() > 400.0F) {
            var6 *= 2.0F;
            this.setIncWeightLot(true);
         }

         this.setWeight(this.getWeight() + var6 * var5 * GameTime.getInstance().getGameWorldSecondsSinceLastUpdate());
      } else if (this.getCalories() < var3) {
         this.setDecWeight(true);
    float var10 = Math.abs(this.getCalories()) / this.caloriesDecreaseMax;
         if (var10 > 1.0F) {
            var10 = 1.0F;
         }

         this.setWeight(this.getWeight() - this.weightLoss * var10 * GameTime.getInstance().getGameWorldSecondsSinceLastUpdate());
      }

      this.updatedWeight++;
      if (this.updatedWeight >= 2000) {
         this.applyTraitFromWeight();
         this.updatedWeight = 0;
      }

      if (GameClient.bClient) {
         this.syncWeightTimer++;
         if (this.syncWeightTimer >= 5000) {
            GameClient.sendWeight(this.parent);
            this.syncWeightTimer = 0;
         }
      }
   }

    void syncWeight() {
      GameClient.sendWeight(this.parent);
   }

    void save(ByteBuffer var1) {
      var1.putFloat(this.getCalories());
      var1.putFloat(this.getProteins());
      var1.putFloat(this.getLipids());
      var1.putFloat(this.getCarbohydrates());
      var1.putFloat((float)this.getWeight());
   }

    void load(ByteBuffer var1) {
      this.setCalories(var1.getFloat());
      this.setProteins(var1.getFloat());
      this.setLipids(var1.getFloat());
      this.setCarbohydrates(var1.getFloat());
      this.setWeight(var1.getFloat());
   }

    void applyWeightFromTraits() {
      if (this.parent.getTraits() != nullptr && !this.parent.getTraits().empty()) {
         if (this.parent.Traits.Emaciated.isSet()) {
            this.setWeight(50.0);
         }

         if (this.parent.Traits.VeryUnderweight.isSet()) {
            this.setWeight(60.0);
         }

         if (this.parent.Traits.Underweight.isSet()) {
            this.setWeight(70.0);
         }

         if (this.parent.Traits.Overweight.isSet()) {
            this.setWeight(95.0);
         }

         if (this.parent.Traits.Obese.isSet()) {
            this.setWeight(105.0);
         }
      }
   }

    void applyTraitFromWeight() {
      this.parent.getTraits().remove("Underweight");
      this.parent.getTraits().remove("Very Underweight");
      this.parent.getTraits().remove("Emaciated");
      this.parent.getTraits().remove("Overweight");
      this.parent.getTraits().remove("Obese");
      if (this.getWeight() >= 100.0) {
         this.parent.getTraits().push_back("Obese");
      }

      if (this.getWeight() >= 85.0 && this.getWeight() < 100.0) {
         this.parent.getTraits().push_back("Overweight");
      }

      if (this.getWeight() > 65.0 && this.getWeight() <= 75.0) {
         this.parent.getTraits().push_back("Underweight");
      }

      if (this.getWeight() > 50.0 && this.getWeight() <= 65.0) {
         this.parent.getTraits().push_back("Very Underweight");
      }

      if (this.getWeight() <= 50.0) {
         this.parent.getTraits().push_back("Emaciated");
      }
   }

    bool characterHaveWeightTrouble() {
      return this.parent.Traits.Emaciated.isSet()
         || this.parent.Traits.Obese.isSet()
         || this.parent.Traits.VeryUnderweight.isSet()
         || this.parent.Traits.Underweight.isSet()
         || this.parent.Traits.Overweight.isSet();
   }

    bool canAddFitnessXp() {
      if (this.parent.getPerkLevel(Perks.Fitness) >= 9 && this.characterHaveWeightTrouble()) {
    return false;
      } else {
         return this.parent.getPerkLevel(Perks.Fitness) < 6
            ? true
            : !this.parent.Traits.Emaciated.isSet() && !this.parent.Traits.Obese.isSet() && !this.parent.Traits.VeryUnderweight.isSet();
      }
   }

    float getCarbohydrates() {
      return this.carbohydrates;
   }

    void setCarbohydrates(float var1) {
      if (var1 < -500.0F) {
         var1 = -500.0F;
      }

      if (var1 > 1000.0F) {
         var1 = 1000.0F;
      }

      this.carbohydrates = var1;
   }

    float getProteins() {
      return this.proteins;
   }

    void setProteins(float var1) {
      if (var1 < -500.0F) {
         var1 = -500.0F;
      }

      if (var1 > 1000.0F) {
         var1 = 1000.0F;
      }

      this.proteins = var1;
   }

    float getCalories() {
      return this.calories;
   }

    void setCalories(float var1) {
      if (var1 < -2200.0F) {
         var1 = -2200.0F;
      }

      if (var1 > 3700.0F) {
         var1 = 3700.0F;
      }

      this.calories = var1;
   }

    float getLipids() {
      return this.lipids;
   }

    void setLipids(float var1) {
      if (var1 < -500.0F) {
         var1 = -500.0F;
      }

      if (var1 > 1000.0F) {
         var1 = 1000.0F;
      }

      this.lipids = var1;
   }

    double getWeight() {
      return this.weight;
   }

    void setWeight(double var1) {
      if (var1 < 35.0) {
         var1 = 35.0;
    float var3 = this.parent.getBodyDamage().getHealthReductionFromSevereBadMoodles() * GameTime.instance.getMultiplier();
         this.parent.getBodyDamage().ReduceGeneralHealth(var3);
         LuaEventManager.triggerEvent("OnPlayerGetDamage", this.parent, "LOWWEIGHT", var3);
      }

      this.weight = var1;
   }

    bool isIncWeight() {
      return this.incWeight;
   }

    void setIncWeight(bool var1) {
      this.incWeight = var1;
   }

    bool isIncWeightLot() {
      return this.incWeightLot;
   }

    void setIncWeightLot(bool var1) {
      this.incWeightLot = var1;
   }

    bool isDecWeight() {
      return this.decWeight;
   }

    void setDecWeight(bool var1) {
      this.decWeight = var1;
   }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
