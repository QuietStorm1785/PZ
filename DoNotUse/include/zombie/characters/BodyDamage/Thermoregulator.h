#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/BloodClothingType.h"
#include "zombie/characters/BodyDamage/Thermoregulator/1.h"
#include "zombie/characters/BodyDamage/Thermoregulator/Multiplier.h"
#include "zombie/characters/BodyDamage/Thermoregulator/ThermalNode.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/Stats.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/WeaponType.h"
#include "zombie/iso/weather/ClimateManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace characters {
namespace BodyDamage {


class Thermoregulator {
public:
    static const bool DISABLE_ENERGY_MULTIPLIER = false;
    const BodyDamage bodyDamage;
    const IsoGameCharacter character;
    const IsoPlayer player;
    const Stats stats;
    const Nutrition nutrition;
    const ClimateManager climate;
    static const ItemVisuals itemVisuals = std::make_shared<ItemVisuals>();
    static const ItemVisuals itemVisualsCache = std::make_shared<ItemVisuals>();
   private static const std::vector<BloodBodyPartType> coveredParts = std::make_unique<std::vector<>>();
    static float SIMULATION_MULTIPLIER = 1.0F;
    float setPoint = 37.0F;
    float metabolicRate = Metabolics.Default.getMet();
    float metabolicRateReal = this.metabolicRate;
    float metabolicTarget = Metabolics.Default.getMet();
    double fluidsMultiplier = 1.0;
    double energyMultiplier = 1.0;
    double fatigueMultiplier = 1.0;
    float bodyHeatDelta = 0.0F;
    float coreHeatDelta = 0.0F;
    bool thermalChevronUp = true;
    ThermalNode core;
   private ThermalNode[] nodes;
    float totalHeatRaw = 0.0F;
    float totalHeat = 0.0F;
    float primTotal = 0.0F;
    float secTotal = 0.0F;
    float externalAirTemperature = 27.0F;
    float airTemperature;
    float airAndWindTemp;
    float rateOfChangeCounter = 0.0F;
    float coreCelciusCache = 37.0F;
    float coreRateOfChange = 0.0F;
    float thermalDamage = 0.0F;
    float damageCounter = 0.0F;

    public Thermoregulator(BodyDamage var1) {
      this.bodyDamage = var1;
      this.character = var1.getParentChar();
      this.stats = this.character.getStats();
      if (this.dynamic_cast<IsoPlayer*>(character) != nullptr) {
         this.player = (IsoPlayer)this.character;
         this.nutrition = ((IsoPlayer)this.character).getNutrition();
      } else {
         this.player = nullptr;
         this.nutrition = nullptr;
      }

      this.climate = ClimateManager.getInstance();
      this.initNodes();
   }

    static void setSimulationMultiplier(float var0) {
      SIMULATION_MULTIPLIER = var0;
   }

    void save(ByteBuffer var1) {
      var1.putFloat(this.setPoint);
      var1.putFloat(this.metabolicRate);
      var1.putFloat(this.metabolicTarget);
      var1.putFloat(this.bodyHeatDelta);
      var1.putFloat(this.coreHeatDelta);
      var1.putFloat(this.thermalDamage);
      var1.putFloat(this.damageCounter);
      var1.putInt(this.nodes.length);

      for (int var3 = 0; var3 < this.nodes.length; var3++) {
    ThermalNode var2 = this.nodes[var3];
         var1.putInt(BodyPartType.ToIndex(var2.bodyPartType));
         var1.putFloat(var2.celcius);
         var1.putFloat(var2.skinCelcius);
         var1.putFloat(var2.heatDelta);
         var1.putFloat(var2.primaryDelta);
         var1.putFloat(var2.secondaryDelta);
      }
   }

    void load(ByteBuffer var1, int var2) {
      this.setPoint = var1.getFloat();
      this.metabolicRate = var1.getFloat();
      this.metabolicTarget = var1.getFloat();
      this.bodyHeatDelta = var1.getFloat();
      this.coreHeatDelta = var1.getFloat();
      this.thermalDamage = var1.getFloat();
      this.damageCounter = var1.getFloat();
    int var3 = var1.getInt();

      for (int var5 = 0; var5 < var3; var5++) {
    int var6 = var1.getInt();
    float var7 = var1.getFloat();
    float var8 = var1.getFloat();
    float var9 = var1.getFloat();
    float var10 = var1.getFloat();
    float var11 = var1.getFloat();
    ThermalNode var4 = this.getNodeForType(BodyPartType.FromIndex(var6));
         if (var4 != nullptr) {
            var4.celcius = var7;
            var4.skinCelcius = var8;
            var4.heatDelta = var9;
            var4.primaryDelta = var10;
            var4.secondaryDelta = var11;
         } else {
            DebugLog.log("Couldnt load node: " + BodyPartType.ToString(BodyPartType.FromIndex(var6)));
         }
      }
   }

    void reset() {
      this.setPoint = 37.0F;
      this.metabolicRate = Metabolics.Default.getMet();
      this.metabolicTarget = this.metabolicRate;
      this.core.celcius = 37.0F;
      this.bodyHeatDelta = 0.0F;
      this.coreHeatDelta = 0.0F;
      this.thermalDamage = 0.0F;

      for (int var2 = 0; var2 < this.nodes.length; var2++) {
    ThermalNode var1 = this.nodes[var2];
         if (var1 != this.core) {
            var1.celcius = 35.0F;
         }

         var1.primaryDelta = 0.0F;
         var1.secondaryDelta = 0.0F;
         var1.skinCelcius = 33.0F;
         var1.heatDelta = 0.0F;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void initNodes() {
    std::vector var1 = new std::vector();

      for (int var2 = 0; var2 < this.bodyDamage.getBodyParts().size(); var2++) {
    BodyPart var3 = (BodyPart)this.bodyDamage.getBodyParts().get(var2);
    ThermalNode var4 = nullptr;
         switch (1.$SwitchMap$zombie$characters$BodyDamage$BodyPartType[var3.getType().ordinal()]) {
            case 1:
               var4 = std::make_shared<ThermalNode>(this, true, 37.0F, var3, 0.25F);
               this.core = var4;
               break;
            case 2:
               var4 = std::make_shared<ThermalNode>(this, 37.0F, var3, 1.0F);
               break;
            case 3:
               var4 = std::make_shared<ThermalNode>(this, 37.0F, var3, 0.5F);
               break;
            case 4:
               var4 = std::make_shared<ThermalNode>(this, 37.0F, var3, 0.25F);
               break;
            case 5:
               var4 = std::make_shared<ThermalNode>(this, 37.0F, var3, 0.5F);
               break;
            case 6:
            case 7:
               var4 = std::make_shared<ThermalNode>(this, 37.0F, var3, 0.5F);
               break;
            case 8:
            case 9:
               var4 = std::make_shared<ThermalNode>(this, 37.0F, var3, 0.5F);
               break;
            case 10:
            case 11:
               var4 = std::make_shared<ThermalNode>(this, 37.0F, var3, 0.5F);
               break;
            case 12:
            case 13:
               var4 = std::make_shared<ThermalNode>(this, 37.0F, var3, 0.25F);
               break;
            case 14:
            case 15:
               var4 = std::make_shared<ThermalNode>(this, 37.0F, var3, 0.25F);
               break;
            case 16:
            case 17:
               var4 = std::make_shared<ThermalNode>(this, 37.0F, var3, 1.0F);
               break;
            default:
               DebugLog.log("Warning: couldnt init thermal node for body part '" + ((BodyPart)this.bodyDamage.getBodyParts().get(var2)).getType() + "'.");
         }

         if (var4 != nullptr) {
            var3.thermalNode = var4;
            var1.push_back(var4);
         }
      }

      this.nodes = new ThermalNode[var1.size()];
      var1.toArray(this.nodes);

      for (int var7 = 0; var7 < this.nodes.length; var7++) {
    ThermalNode var8 = this.nodes[var7];
    BodyPartType var9 = BodyPartContacts.getParent(var8.bodyPartType);
         if (var9 != nullptr) {
            var8.upstream = this.getNodeForType(var9);
         }

         BodyPartType[] var5 = BodyPartContacts.getChildren(var8.bodyPartType);
         if (var5 != nullptr && var5.length > 0) {
            var8.downstream = new ThermalNode[var5.length];

            for (int var6 = 0; var6 < var5.length; var6++) {
               var8.downstream[var6] = this.getNodeForType(var5[var6]);
            }
         }
      }

      this.core.celcius = this.setPoint;
   }

    int getNodeSize() {
      return this.nodes.length;
   }

    ThermalNode getNode(int var1) {
      return this.nodes[var1];
   }

    ThermalNode getNodeForType(BodyPartType var1) {
      for (int var2 = 0; var2 < this.nodes.length; var2++) {
         if (this.nodes[var2].bodyPartType == var1) {
            return this.nodes[var2];
         }
      }

    return nullptr;
   }

    ThermalNode getNodeForBloodType(BloodBodyPartType var1) {
      for (int var2 = 0; var2 < this.nodes.length; var2++) {
         if (this.nodes[var2].bloodBPT == var1) {
            return this.nodes[var2];
         }
      }

    return nullptr;
   }

    float getBodyHeatDelta() {
      return this.bodyHeatDelta;
   }

    double getFluidsMultiplier() {
      return this.fluidsMultiplier;
   }

    double getEnergyMultiplier() {
      return this.energyMultiplier;
   }

    double getFatigueMultiplier() {
      return this.fatigueMultiplier;
   }

    float getMovementModifier() {
    float var1 = 1.0F;
      if (this.player != nullptr) {
    int var2 = this.player.getMoodles().getMoodleLevel(MoodleType.Hypothermia);
         if (var2 == 2) {
            var1 = 0.66F;
         } else if (var2 == 3) {
            var1 = 0.33F;
         } else if (var2 == 4) {
            var1 = 0.0F;
         }

         var2 = this.player.getMoodles().getMoodleLevel(MoodleType.Hyperthermia);
         if (var2 == 2) {
            var1 = 0.66F;
         } else if (var2 == 3) {
            var1 = 0.33F;
         } else if (var2 == 4) {
            var1 = 0.0F;
         }
      }

    return var1;
   }

    float getCombatModifier() {
    float var1 = 1.0F;
      if (this.player != nullptr) {
    int var2 = this.player.getMoodles().getMoodleLevel(MoodleType.Hypothermia);
         if (var2 == 2) {
            var1 = 0.66F;
         } else if (var2 == 3) {
            var1 = 0.33F;
         } else if (var2 == 4) {
            var1 = 0.1F;
         }

         var2 = this.player.getMoodles().getMoodleLevel(MoodleType.Hyperthermia);
         if (var2 == 2) {
            var1 = 0.66F;
         } else if (var2 == 3) {
            var1 = 0.33F;
         } else if (var2 == 4) {
            var1 = 0.1F;
         }
      }

    return var1;
   }

    float getCoreTemperature() {
      return this.core.celcius;
   }

    float getHeatGeneration() {
      return this.metabolicRateReal;
   }

    float getMetabolicRate() {
      return this.metabolicRate;
   }

    float getMetabolicTarget() {
      return this.metabolicTarget;
   }

    float getMetabolicRateReal() {
      return this.metabolicRateReal;
   }

    float getSetPoint() {
      return this.setPoint;
   }

    float getCoreHeatDelta() {
      return this.coreHeatDelta;
   }

    float getCoreRateOfChange() {
      return this.coreRateOfChange;
   }

    float getExternalAirTemperature() {
      return this.externalAirTemperature;
   }

    float getCoreTemperatureUI() {
    float var1 = PZMath.clamp(this.core.celcius, 20.0F, 42.0F);
      if (var1 < 37.0F) {
         var1 = (var1 - 20.0F) / 17.0F * 0.5F;
      } else {
         var1 = 0.5F + (var1 - 37.0F) / 5.0F * 0.5F;
      }

    return var1;
   }

    float getHeatGenerationUI() {
    float var1 = PZMath.clamp(this.metabolicRateReal, 0.0F, Metabolics.MAX.getMet());
      if (var1 < Metabolics.Default.getMet()) {
         var1 = var1 / Metabolics.Default.getMet() * 0.5F;
      } else {
         var1 = 0.5F + (var1 - Metabolics.Default.getMet()) / (Metabolics.MAX.getMet() - Metabolics.Default.getMet()) * 0.5F;
      }

    return var1;
   }

    bool thermalChevronUp() {
      return this.thermalChevronUp;
   }

    int thermalChevronCount() {
      if (this.coreRateOfChange > 0.01F) {
    return 3;
      } else if (this.coreRateOfChange > 0.001F) {
    return 2;
      } else {
         return this.coreRateOfChange > 1.0E-4F ? 1 : 0;
      }
   }

    float getCatchAColdDelta() {
    float var1 = 0.0F;
      if (this.player.getMoodles().getMoodleLevel(MoodleType.Hypothermia) < 1) {
    return var1;
      } else {
         for (int var3 = 0; var3 < this.nodes.length; var3++) {
    ThermalNode var2 = this.nodes[var3];
    float var4 = 0.0F;
            if (var2.skinCelcius < 33.0F) {
               var4 = (var2.skinCelcius - 20.0F) / 13.0F;
               var4 = 1.0F - var4;
               var4 *= var4;
            }

    float var5 = 0.25F * var4 * var2.skinSurface;
            if (var2.bodyWetness > 0.0F) {
               var5 *= 1.0F + var2.bodyWetness * 1.0F;
            }

            if (var2.clothingWetness > 0.5F) {
               var5 *= 1.0F + (var2.clothingWetness - 0.5F) * 2.0F;
            }

            if (var2.bodyPartType == BodyPartType.Neck) {
               var5 *= 8.0F;
            } else if (var2.bodyPartType == BodyPartType.Torso_Upper) {
               var5 *= 16.0F;
            } else if (var2.bodyPartType == BodyPartType.Head) {
               var5 *= 4.0F;
            }

            var1 += var5;
         }

         if (this.player.getMoodles().getMoodleLevel(MoodleType.Hypothermia) > 1) {
            var1 *= this.player.getMoodles().getMoodleLevel(MoodleType.Hypothermia);
         }

    return var1;
      }
   }

    float getTimedActionTimeModifier() {
    float var1 = 1.0F;

      for (int var4 = 0; var4 < this.nodes.length; var4++) {
    ThermalNode var3 = this.nodes[var4];
    float var5 = 0.0F;
         if (var3.skinCelcius < 33.0F) {
            var5 = (var3.skinCelcius - 20.0F) / 13.0F;
            var5 = 1.0F - var5;
            var5 *= var5;
         }

    float var2 = 0.25F * var5 * var3.skinSurface;
         if (var3.bodyPartType == BodyPartType.Hand_R || var3.bodyPartType == BodyPartType.Hand_L) {
            var1 += 0.3F * var2;
         } else if (var3.bodyPartType == BodyPartType.ForeArm_R || var3.bodyPartType == BodyPartType.ForeArm_L) {
            var1 += 0.15F * var2;
         } else if (var3.bodyPartType == BodyPartType.UpperArm_R || var3.bodyPartType == BodyPartType.UpperArm_L) {
            var1 += 0.1F * var2;
         }
      }

    return var1;
   }

    static float getSkinCelciusMin() {
      return 20.0F;
   }

    static float getSkinCelciusFavorable() {
      return 33.0F;
   }

    static float getSkinCelciusMax() {
      return 42.0F;
   }

    void setMetabolicTarget(Metabolics var1) {
      this.setMetabolicTarget(var1.getMet());
   }

    void setMetabolicTarget(float var1) {
      if (!(var1 < 0.0F) && !(var1 < this.metabolicTarget)) {
         this.metabolicTarget = var1;
         if (this.metabolicTarget > Metabolics.MAX.getMet()) {
            this.metabolicTarget = Metabolics.MAX.getMet();
         }
      }
   }

    void updateCoreRateOfChange() {
      this.rateOfChangeCounter = this.rateOfChangeCounter + GameTime.instance.getMultiplier();
      if (this.rateOfChangeCounter > 100.0F) {
         this.rateOfChangeCounter = 0.0F;
         this.coreRateOfChange = this.core.celcius - this.coreCelciusCache;
         this.thermalChevronUp = this.coreRateOfChange >= 0.0F;
         this.coreRateOfChange = PZMath.abs(this.coreRateOfChange);
         this.coreCelciusCache = this.core.celcius;
      }
   }

    float getSimulationMultiplier() {
    return SIMULATION_MULTIPLIER;
   }

    float getDefaultMultiplier() {
      return this.getSimulationMultiplier(Multiplier.Default);
   }

    float getMetabolicRateIncMultiplier() {
      return this.getSimulationMultiplier(Multiplier.MetabolicRateInc);
   }

    float getMetabolicRateDecMultiplier() {
      return this.getSimulationMultiplier(Multiplier.MetabolicRateDec);
   }

    float getBodyHeatMultiplier() {
      return this.getSimulationMultiplier(Multiplier.BodyHeat);
   }

    float getCoreHeatExpandMultiplier() {
      return this.getSimulationMultiplier(Multiplier.CoreHeatExpand);
   }

    float getCoreHeatContractMultiplier() {
      return this.getSimulationMultiplier(Multiplier.CoreHeatContract);
   }

    float getSkinCelciusMultiplier() {
      return this.getSimulationMultiplier(Multiplier.SkinCelcius);
   }

    float getTemperatureAir() {
      return this.climate.getAirTemperatureForCharacter(this.character, false);
   }

    float getTemperatureAirAndWind() {
      return this.climate.getAirTemperatureForCharacter(this.character, true);
   }

    float getDbg_totalHeatRaw() {
      return this.totalHeatRaw;
   }

    float getDbg_totalHeat() {
      return this.totalHeat;
   }

    float getCoreCelcius() {
      return this.core != nullptr ? this.core.celcius : 0.0F;
   }

    float getDbg_primTotal() {
      return this.primTotal;
   }

    float getDbg_secTotal() {
      return this.secTotal;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    float getSimulationMultiplier(Multiplier var1) {
    float var2 = GameTime.instance.getMultiplier();
      switch (1.$SwitchMap$zombie$characters$BodyDamage$Thermoregulator$Multiplier[var1.ordinal()]) {
         case 1:
            var2 *= 0.001F;
            break;
         case 2:
            var2 *= 4.0E-4F;
            break;
         case 3:
            var2 *= 2.5E-4F;
            break;
         case 4:
            var2 *= 5.0E-5F;
            break;
         case 5:
            var2 *= 5.0E-4F;
            break;
         case 6:
         case 7:
            var2 *= 0.0025F;
            break;
         case 8:
            var2 *= 0.005F;
            break;
         case 9:
            var2 *= 5.0E-4F;
            break;
         case 10:
            var2 *= 2.5E-4F;
         case 11:
      }

      return var2 * SIMULATION_MULTIPLIER;
   }

    float getThermalDamage() {
      return this.thermalDamage;
   }

    void updateThermalDamage(float var1) {
      this.damageCounter = this.damageCounter + GameTime.instance.getRealworldSecondsSinceLastUpdate();
      if (this.damageCounter > 1.0F) {
         this.damageCounter = 0.0F;
         if (this.player.getMoodles().getMoodleLevel(MoodleType.Hypothermia) == 4 && var1 < 0.0F && this.core.celcius - this.coreCelciusCache <= 0.0F) {
    float var4 = (this.core.celcius - 20.0F) / 5.0F;
            var4 = 1.0F - var4;
    float var7 = 120.0F;
            var7 += 480.0F * var4;
            this.thermalDamage = this.thermalDamage + 1.0F / var7 * PZMath.clamp_01(PZMath.abs(var1) / 10.0F);
         } else if (this.player.getMoodles().getMoodleLevel(MoodleType.Hyperthermia) == 4 && var1 > 37.0F && this.core.celcius - this.coreCelciusCache >= 0.0F) {
    float var2 = (this.core.celcius - 41.0F) / 1.0F;
    float var3 = 120.0F;
            var3 += 480.0F * var2;
            this.thermalDamage = this.thermalDamage + 1.0F / var3 * PZMath.clamp_01((var1 - 37.0F) / 8.0F);
            this.thermalDamage = Math.min(this.thermalDamage, 0.3F);
         } else {
            this.thermalDamage -= 0.011111111F;
         }

         this.thermalDamage = PZMath.clamp_01(this.thermalDamage);
      }

      this.player.getBodyDamage().ColdDamageStage = this.thermalDamage;
   }

    void update() {
      this.airTemperature = this.climate.getAirTemperatureForCharacter(this.character, false);
      this.airAndWindTemp = this.climate.getAirTemperatureForCharacter(this.character, true);
      this.externalAirTemperature = this.airTemperature;
      this.updateSetPoint();
      this.updateCoreRateOfChange();
      this.updateMetabolicRate();
      this.updateClothing();
      this.updateNodesHeatDelta();
      this.updateHeatDeltas();
      this.updateNodes();
      this.updateBodyMultipliers();
      this.updateThermalDamage(this.airAndWindTemp);
   }

    float getSicknessValue() {
      return this.stats.getSickness();
   }

    void updateSetPoint() {
      this.setPoint = 37.0F;
      if (this.stats.getSickness() > 0.0F) {
    float var1 = 2.0F;
         this.setPoint = this.setPoint + this.stats.getSickness() * var1;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void updateMetabolicRate() {
      this.setMetabolicTarget(Metabolics.Default.getMet());
      if (this.player != nullptr) {
         if (this.player.isAttacking()) {
    WeaponType var1 = WeaponType.getWeaponType(this.player);
            switch (1.$SwitchMap$zombie$inventory$types$WeaponType[var1.ordinal()]) {
               case 1:
                  this.setMetabolicTarget(Metabolics.MediumWork);
                  break;
               case 2:
                  this.setMetabolicTarget(Metabolics.HeavyWork);
                  break;
               case 3:
                  this.setMetabolicTarget(Metabolics.MediumWork);
                  break;
               case 4:
                  this.setMetabolicTarget(Metabolics.Running15kmh);
                  break;
               case 5:
                  this.setMetabolicTarget(Metabolics.LightWork);
                  break;
               case 6:
                  this.setMetabolicTarget(Metabolics.MediumWork);
                  break;
               case 7:
                  this.setMetabolicTarget(Metabolics.UsingTools);
                  break;
               case 8:
                  this.setMetabolicTarget(Metabolics.LightWork);
                  break;
               case 9:
                  this.setMetabolicTarget(Metabolics.MediumWork);
                  break;
               case 10:
                  this.setMetabolicTarget(Metabolics.Running15kmh);
            }
         }

         if (this.player.isPlayerMoving()) {
            if (this.player.isSprinting()) {
               this.setMetabolicTarget(Metabolics.Running15kmh);
            } else if (this.player.isRunning()) {
               this.setMetabolicTarget(Metabolics.Running10kmh);
            } else if (this.player.isSneaking()) {
               this.setMetabolicTarget(Metabolics.Walking2kmh);
            } else if (this.player.CurrentSpeed > 0.0F) {
               this.setMetabolicTarget(Metabolics.Walking5kmh);
            }
         }
      }

    float var5 = PZMath.clamp_01(1.0F - this.stats.getEndurance()) * Metabolics.DefaultExercise.getMet();
      this.setMetabolicTarget(var5 * this.getEnergy());
    float var2 = PZMath.clamp_01(this.player.getInventory().getCapacityWeight() / this.player.getMaxWeight());
    float var3 = 1.0F + var2 * var2 * 0.35F;
      this.setMetabolicTarget(this.metabolicTarget * var3);
      if (!PZMath.equal(this.metabolicRate, this.metabolicTarget)) {
    float var4 = this.metabolicTarget - this.metabolicRate;
         if (this.metabolicTarget > this.metabolicRate) {
            this.metabolicRate = this.metabolicRate + var4 * this.getSimulationMultiplier(Multiplier.MetabolicRateInc);
         } else {
            this.metabolicRate = this.metabolicRate + var4 * this.getSimulationMultiplier(Multiplier.MetabolicRateDec);
         }
      }

    float var6 = 1.0F;
      if (this.player.getMoodles().getMoodleLevel(MoodleType.Hypothermia) >= 1) {
         var6 = this.getMovementModifier();
      }

      this.metabolicRateReal = this.metabolicRate * (0.2F + 0.8F * this.getEnergy() * var6);
      this.metabolicTarget = -1.0F;
   }

    void updateNodesHeatDelta() {
    float var1 = PZMath.clamp_01((float)((this.player.getNutrition().getWeight() / 75.0 - 0.5) * 0.666F));
      var1 = (var1 - 0.5F) * 2.0F;
    float var2 = this.stats.getFitness();
    float var3 = 1.0F;
      if (this.airAndWindTemp > this.setPoint - 2.0F) {
         if (this.airTemperature < this.setPoint + 2.0F) {
            var3 = (this.airTemperature - (this.setPoint - 2.0F)) / 4.0F;
            var3 = 1.0F - var3;
         } else {
            var3 = 0.0F;
         }
      }

    float var4 = 1.0F;
      if (this.climate.getHumidity() > 0.5F) {
    float var5 = (this.climate.getHumidity() - 0.5F) * 2.0F;
         var4 -= var5;
      }

    float var15 = 1.0F;
      if (this.core.celcius < 37.0F) {
         var15 = (this.core.celcius - 20.0F) / 17.0F;
         var15 *= var15;
      }

    float var6 = 0.0F;

      for (int var8 = 0; var8 < this.nodes.length; var8++) {
    ThermalNode var7 = this.nodes[var8];
         var7.calculateInsulation();
    float var9 = this.airTemperature;
         if (this.airAndWindTemp < this.airTemperature) {
            var9 -= (this.airTemperature - this.airAndWindTemp) / (1.0F + var7.windresist);
         }

    float var10 = var9 - var7.skinCelcius;
         if (var10 <= 0.0F) {
            var10 *= 1.0F + 0.75F * var7.bodyWetness;
         } else {
            var10 /= 1.0F + 3.0F * var7.bodyWetness;
         }

         var10 *= 0.3F;
         var10 /= 1.0F + var7.insulation;
         var7.heatDelta = var10 * var7.skinSurface;
         if (var7.primaryDelta > 0.0F) {
    float var12 = 0.2F + 0.8F * this.getBodyFluids();
    float var11 = Metabolics.Default.getMet() * var7.primaryDelta * var7.skinSurface / (1.0F + var7.insulation);
            var11 *= var12 * (0.1F + 0.9F * var3);
            var11 *= var4;
            var11 *= 1.0F - 0.2F * var1;
            var11 *= 1.0F + 0.2F * var2;
            var7.heatDelta -= var11;
         } else {
    float var39 = 0.2F + 0.8F * this.getEnergy();
    float var26 = Metabolics.Default.getMet() * PZMath.abs(var7.primaryDelta) * var7.skinSurface;
            var26 *= var39;
            var26 *= 1.0F + 0.2F * var1;
            var26 *= 1.0F + 0.2F * var2;
            var7.heatDelta += var26;
         }

         if (var7.secondaryDelta > 0.0F) {
    float var40 = 0.1F + 0.9F * this.getBodyFluids();
    float var30 = Metabolics.MAX.getMet() * 0.75F * var7.secondaryDelta * var7.skinSurface / (1.0F + var7.insulation);
            var30 *= var40;
            var30 *= 0.85F + 0.15F * var4;
            var30 *= 1.0F - 0.2F * var1;
            var30 *= 1.0F + 0.2F * var2;
            var7.heatDelta -= var30;
         } else {
    float var41 = 0.1F + 0.9F * this.getEnergy();
    float var35 = Metabolics.Default.getMet() * PZMath.abs(var7.secondaryDelta) * var7.skinSurface;
            var35 *= var41;
            var35 *= 1.0F + 0.2F * var1;
            var35 *= 1.0F + 0.2F * var2;
            var7.heatDelta += var35;
         }

         var6 += var7.heatDelta;
      }

      this.totalHeatRaw = var6;
      var6 += this.metabolicRateReal;
      this.totalHeat = var6;
   }

    void updateHeatDeltas() {
      this.coreHeatDelta = this.totalHeat * this.getSimulationMultiplier(Multiplier.BodyHeat);
      if (this.coreHeatDelta < 0.0F) {
         if (this.core.celcius > this.setPoint) {
            this.coreHeatDelta = this.coreHeatDelta * (1.0F + (this.core.celcius - this.setPoint) / 2.0F);
         }
      } else if (this.core.celcius < this.setPoint) {
         this.coreHeatDelta = this.coreHeatDelta * (1.0F + (this.setPoint - this.core.celcius) / 4.0F);
      }

      this.core.celcius = this.core.celcius + this.coreHeatDelta;
      this.core.celcius = PZMath.clamp(this.core.celcius, 20.0F, 42.0F);
      this.bodyDamage.setTemperature(this.core.celcius);
      this.bodyHeatDelta = 0.0F;
      if (this.core.celcius > this.setPoint) {
         this.bodyHeatDelta = this.core.celcius - this.setPoint;
      } else if (this.core.celcius < this.setPoint) {
         this.bodyHeatDelta = this.core.celcius - this.setPoint;
      }

      if (this.bodyHeatDelta < 0.0F) {
    float var1 = PZMath.abs(this.bodyHeatDelta);
         if (var1 <= 1.0F) {
            this.bodyHeatDelta *= 0.8F;
         } else {
            var1 = PZMath.clamp(var1, 1.0F, 11.0F) - 1.0F;
            var1 /= 10.0F;
            this.bodyHeatDelta = -0.8F + -0.2F * var1;
         }
      }

      this.bodyHeatDelta = PZMath.clamp(this.bodyHeatDelta, -1.0F, 1.0F);
   }

    void updateNodes() {
    float var2 = 0.0F;
    float var3 = 0.0F;

      for (int var4 = 0; var4 < this.nodes.length; var4++) {
    ThermalNode var1 = this.nodes[var4];
    float var5 = 1.0F + var1.insulation;
    float var6 = this.metabolicRateReal / Metabolics.MAX.getMet();
         var6 *= var6;
         if (this.bodyHeatDelta < 0.0F) {
    float var7 = var1.distToCore;
            var1.primaryDelta = this.bodyHeatDelta * (1.0F + var7);
         } else {
            var1.primaryDelta = this.bodyHeatDelta * (1.0F + (1.0F - var1.distToCore));
         }

         var1.primaryDelta = PZMath.clamp(var1.primaryDelta, -1.0F, 1.0F);
         var1.secondaryDelta = var1.primaryDelta * PZMath.abs(var1.primaryDelta) * PZMath.abs(var1.primaryDelta);
         var2 += var1.primaryDelta * var1.skinSurface;
         var3 += var1.secondaryDelta * var1.skinSurface;
         if (this.stats.getDrunkenness() > 0.0F) {
            var1.primaryDelta = var1.primaryDelta + this.stats.getDrunkenness() * 0.02F;
         }

         var1.primaryDelta = PZMath.clamp(var1.primaryDelta, -1.0F, 1.0F);
    float var14 = this.core.celcius - 20.0F;
    float var8 = this.core.celcius;
         if (var14 < this.airTemperature) {
            if (this.airTemperature < 33.0F) {
               var14 = this.airTemperature;
            } else {
    float var9 = 0.4F + 0.6F * (1.0F - var1.distToCore);
    float var10 = (this.airTemperature - 33.0F) / 6.0F;
               var14 = 33.0F;
               var14 += 4.0F * var10 * var9;
               var14 = PZMath.clamp(var14, 33.0F, this.airTemperature);
               if (var14 > var8) {
                  var14 = var8 - 0.25F;
               }
            }
         }

    float var17 = this.core.celcius - 4.0F;
         if (var1.primaryDelta < 0.0F) {
    float var20 = 0.4F + 0.6F * var1.distToCore;
    float var11 = var17 - 12.0F * var20 / var5;
            var17 = PZMath.c_lerp(var17, var11, PZMath.abs(var1.primaryDelta));
         } else {
    float var21 = 0.4F + 0.6F * (1.0F - var1.distToCore);
    float var12 = 4.0F * var21;
            var12 *= Math.max(var5 * 0.5F * var21, 1.0F);
    float var23 = Math.min(var17 + var12, var8);
            var17 = PZMath.c_lerp(var17, var23, var1.primaryDelta);
         }

         var17 = PZMath.clamp(var17, var14, var8);
    float var22 = var17 - var1.skinCelcius;
    float var24 = this.getSimulationMultiplier(Multiplier.SkinCelcius);
         if (var22 < 0.0F && var1.skinCelcius > 33.0F) {
            var24 *= 3.0F;
         } else if (var22 > 0.0F && var1.skinCelcius < 33.0F) {
            var24 *= 3.0F;
         }

         if (var24 > 1.0F) {
            var24 = 1.0F;
         }

         var1.skinCelcius += var22 * var24;
         if (var1 != this.core) {
            if (var1.skinCelcius >= this.core.celcius) {
               var1.celcius = this.core.celcius;
            } else {
               var1.celcius = PZMath.lerp(var1.skinCelcius, this.core.celcius, 0.5F);
            }
         }
      }

      this.primTotal = var2;
      this.secTotal = var3;
   }

    void updateBodyMultipliers() {
      this.energyMultiplier = 1.0;
      this.fluidsMultiplier = 1.0;
      this.fatigueMultiplier = 1.0;
    float var1 = PZMath.abs(this.primTotal);
      var1 *= var1;
      if (this.primTotal < 0.0F) {
         this.energyMultiplier += 0.05F * var1;
         this.fatigueMultiplier += 0.25F * var1;
      } else if (this.primTotal > 0.0F) {
         this.fluidsMultiplier += 0.25F * var1;
         this.fatigueMultiplier += 0.25F * var1;
      }

      var1 = PZMath.abs(this.secTotal);
      var1 *= var1;
      if (this.secTotal < 0.0F) {
         this.energyMultiplier += 0.1F * var1;
         this.fatigueMultiplier += 0.75F * var1;
      } else if (this.secTotal > 0.0F) {
         this.fluidsMultiplier += 3.75F * var1;
         this.fatigueMultiplier += 1.75F * var1;
      }
   }

    void updateClothing() {
      this.character.getItemVisuals(itemVisuals);
    bool var1 = itemVisuals.size() != itemVisualsCache.size();
      if (!var1) {
         for (int var2 = 0; var2 < itemVisuals.size(); var2++) {
            if (var2 >= itemVisualsCache.size() || itemVisuals.get(var2) != itemVisualsCache.get(var2)) {
               var1 = true;
               break;
            }
         }
      }

      if (var1) {
         for (int var10 = 0; var10 < this.nodes.length; var10++) {
            this.nodes[var10].clothing.clear();
         }

         itemVisualsCache.clear();

         for (int var11 = 0; var11 < itemVisuals.size(); var11++) {
    ItemVisual var3 = (ItemVisual)itemVisuals.get(var11);
    InventoryItem var4 = var3.getInventoryItem();
            itemVisualsCache.push_back(var3);
            if (dynamic_cast<Clothing*>(var4) != nullptr var5 && (var5.getInsulation() > 0.0F || var5.getWindresistance() > 0.0F)) {
    bool var6 = false;
    std::vector var7 = var4.getBloodClothingType();
               if (var7 != nullptr) {
                  coveredParts.clear();
                  BloodClothingType.getCoveredParts(var7, coveredParts);

                  for (int var8 = 0; var8 < coveredParts.size(); var8++) {
    BloodBodyPartType var9 = coveredParts.get(var8);
                     if (var9.index() >= 0 && var9.index() < this.nodes.length) {
                        var6 = true;
                        this.nodes[var9.index()].clothing.push_back(var5);
                     }
                  }
               }

               if (!var6 && var5.getBodyLocation() != nullptr) {
    std::string var12 = var5.getBodyLocation().toLowerCase();
                  switch (var12) {
                     case "hat":
                     case "mask":
                        this.nodes[BodyPartType.ToIndex(BodyPartType.Head)].clothing.push_back(var5);
                  }
               }
            }
         }
      }
   }

    float getEnergy() {
    float var1 = 1.0F - (0.4F * this.stats.getHunger() + 0.6F * this.stats.getHunger() * this.stats.getHunger());
    float var2 = 1.0F - (0.4F * this.stats.getFatigue() + 0.6F * this.stats.getFatigue() * this.stats.getFatigue());
      return 0.6F * var1 + 0.4F * var2;
   }

    float getBodyFluids() {
      return 1.0F - this.stats.getThirst();
   }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
