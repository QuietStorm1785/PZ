#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/BodyDamage/Thermoregulator/ThermalNode.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/network/BodyDamageSync/Updater.h"
#include <filesystem>

namespace zombie {
namespace characters {
namespace BodyDamage {


class BodyPart {
public:
    BodyPartType Type;
    float BiteDamage = 2.1875F;
    float BleedDamage = 0.2857143F;
    float DamageScaler = 0.0057142857F;
    float Health;
    bool bandaged;
    bool bitten;
    bool bleeding;
    bool IsBleedingStemmed;
    bool IsCortorised;
    bool scratched;
    bool stitched;
    bool deepWounded;
    bool IsInfected;
    bool IsFakeInfected;
    const IsoGameCharacter ParentChar;
    float bandageLife = 0.0F;
    float scratchTime = 0.0F;
    float biteTime = 0.0F;
    bool alcoholicBandage = false;
    float stiffness = 0.0F;
    float woundInfectionLevel = 0.0F;
    bool infectedWound = false;
    float ScratchDamage = 0.9375F;
    float CutDamage = 1.875F;
    float WoundDamage = 3.125F;
    float BurnDamage = 3.75F;
    float BulletDamage = 3.125F;
    float FractureDamage = 3.125F;
    float bleedingTime = 0.0F;
    float deepWoundTime = 0.0F;
    bool haveGlass = false;
    float stitchTime = 0.0F;
    float alcoholLevel = 0.0F;
    float additionalPain = 0.0F;
    std::string bandageType = nullptr;
    bool getBandageXp = true;
    bool getStitchXp = true;
    bool getSplintXp = true;
    float fractureTime = 0.0F;
    bool splint = false;
    float splintFactor = 0.0F;
    bool haveBullet = false;
    float burnTime = 0.0F;
    bool needBurnWash = false;
    float lastTimeBurnWash = 0.0F;
    std::string splintItem = nullptr;
    float plantainFactor = 0.0F;
    float comfreyFactor = 0.0F;
    float garlicFactor = 0.0F;
    float cutTime = 0.0F;
    bool cut = false;
    float scratchSpeedModifier = 0.0F;
    float cutSpeedModifier = 0.0F;
    float burnSpeedModifier = 0.0F;
    float deepWoundSpeedModifier = 0.0F;
    float wetness = 0.0F;
    ThermalNode thermalNode;

    public BodyPart(BodyPartType var1, IsoGameCharacter var2) {
      this.Type = var1;
      this.ParentChar = var2;
      if (var1 == BodyPartType.Neck) {
         this.DamageScaler *= 5.0F;
      }

      if (var1 == BodyPartType.Hand_L || var1 == BodyPartType.Hand_R || var1 == BodyPartType.ForeArm_L || var1 == BodyPartType.ForeArm_R) {
         this.scratchSpeedModifier = 85.0F;
         this.cutSpeedModifier = 95.0F;
         this.burnSpeedModifier = 45.0F;
         this.deepWoundSpeedModifier = 60.0F;
      }

      if (var1 == BodyPartType.UpperArm_L || var1 == BodyPartType.UpperArm_R) {
         this.scratchSpeedModifier = 65.0F;
         this.cutSpeedModifier = 75.0F;
         this.burnSpeedModifier = 35.0F;
         this.deepWoundSpeedModifier = 40.0F;
      }

      if (var1 == BodyPartType.UpperLeg_L || var1 == BodyPartType.UpperLeg_R || var1 == BodyPartType.LowerLeg_L || var1 == BodyPartType.LowerLeg_R) {
         this.scratchSpeedModifier = 45.0F;
         this.cutSpeedModifier = 55.0F;
         this.burnSpeedModifier = 15.0F;
         this.deepWoundSpeedModifier = 20.0F;
      }

      if (var1 == BodyPartType.Foot_L || var1 == BodyPartType.Foot_R) {
         this.scratchSpeedModifier = 35.0F;
         this.cutSpeedModifier = 45.0F;
         this.burnSpeedModifier = 10.0F;
         this.deepWoundSpeedModifier = 15.0F;
      }

      if (var1 == BodyPartType.Groin) {
         this.scratchSpeedModifier = 45.0F;
         this.cutSpeedModifier = 55.0F;
         this.burnSpeedModifier = 15.0F;
         this.deepWoundSpeedModifier = 20.0F;
      }

      this.RestoreToFullHealth();
   }

    void AddDamage(float var1) {
      this.Health -= var1;
      if (this.Health < 0.0F) {
         this.Health = 0.0F;
      }
   }

    bool isBandageDirty() {
      return this.getBandageLife() <= 0.0F;
   }

    void DamageUpdate() {
      if (this.getDeepWoundTime() > 0.0F && !this.stitched()) {
         if (this.bandaged()) {
            this.Health = this.Health - this.WoundDamage / 2.0F * this.DamageScaler * GameTime.getInstance().getMultiplier();
         } else {
            this.Health = this.Health - this.WoundDamage * this.DamageScaler * GameTime.getInstance().getMultiplier();
         }
      }

      if (this.getScratchTime() > 0.0F && !this.bandaged()) {
         this.Health = this.Health - this.ScratchDamage * this.DamageScaler * GameTime.getInstance().getMultiplier();
      }

      if (this.getCutTime() > 0.0F && !this.bandaged()) {
         this.Health = this.Health - this.CutDamage * this.DamageScaler * GameTime.getInstance().getMultiplier();
      }

      if (this.getBiteTime() > 0.0F && !this.bandaged()) {
         this.Health = this.Health - this.BiteDamage * this.DamageScaler * GameTime.getInstance().getMultiplier();
      }

      if (this.getBleedingTime() > 0.0F && !this.bandaged()) {
    float var1 = this.BleedDamage * this.DamageScaler * GameTime.getInstance().getMultiplier() * (this.getBleedingTime() / 10.0F);
         this.ParentChar.getBodyDamage().ReduceGeneralHealth(var1);
         LuaEventManager.triggerEvent("OnPlayerGetDamage", this.ParentChar, "BLEEDING", var1);
         if (Rand.NextBool(Rand.AdjustForFramerate(1000))) {
            this.ParentChar.addBlood(BloodBodyPartType.FromIndex(BodyPartType.ToIndex(this.getType())), false, false, true);
         }
      }

      if (this.haveBullet()) {
         if (this.bandaged()) {
            this.Health = this.Health - this.BulletDamage / 2.0F * this.DamageScaler * GameTime.getInstance().getMultiplier();
         } else {
            this.Health = this.Health - this.BulletDamage * this.DamageScaler * GameTime.getInstance().getMultiplier();
         }
      }

      if (this.getBurnTime() > 0.0F && !this.bandaged()) {
         this.Health = this.Health - this.BurnDamage * this.DamageScaler * GameTime.getInstance().getMultiplier();
      }

      if (this.getFractureTime() > 0.0F && !this.isSplint()) {
         this.Health = this.Health - this.FractureDamage * this.DamageScaler * GameTime.getInstance().getMultiplier();
      }

      if (this.getBiteTime() > 0.0F) {
         if (this.bandaged()) {
            this.setBiteTime(this.getBiteTime() - (float)(1.0E-4 * GameTime.getInstance().getMultiplier()));
            this.setBandageLife(this.getBandageLife() - (float)(1.0E-4 * GameTime.getInstance().getMultiplier()));
         } else {
            this.setBiteTime(this.getBiteTime() - (float)(5.0E-6 * GameTime.getInstance().getMultiplier()));
         }
      }

      if (this.getBurnTime() > 0.0F) {
         if (this.bandaged()) {
            this.setBurnTime(this.getBurnTime() - (float)(1.0E-4 * GameTime.getInstance().getMultiplier()));
            this.setBandageLife(this.getBandageLife() - (float)(1.0E-4 * GameTime.getInstance().getMultiplier()));
         } else {
            this.setBurnTime(this.getBurnTime() - (float)(5.0E-6 * GameTime.getInstance().getMultiplier()));
         }

         if (this.getLastTimeBurnWash() - this.getBurnTime() >= 20.0F) {
            this.setLastTimeBurnWash(0.0F);
            this.setNeedBurnWash(true);
         }
      }

      if (this.getBleedingTime() > 0.0F) {
         if (this.bandaged()) {
            this.setBleedingTime(this.getBleedingTime() - (float)(2.0E-4 * GameTime.getInstance().getMultiplier()));
            if (this.getDeepWoundTime() > 0.0F) {
               this.setBandageLife(this.getBandageLife() - (float)(0.005 * GameTime.getInstance().getMultiplier()));
            } else {
               this.setBandageLife(this.getBandageLife() - (float)(3.0E-4 * GameTime.getInstance().getMultiplier()));
            }
         } else {
            this.setBleedingTime(this.getBleedingTime() - (float)(2.0E-5 * GameTime.getInstance().getMultiplier()));
         }

         if (this.getBleedingTime() < 3.0F && this.haveGlass()) {
            this.setBleedingTime(3.0F);
         }

         if (this.getBleedingTime() < 0.0F) {
            this.setBleedingTime(0.0F);
            this.setBleeding(false);
         }
      }

      if (!this.isInfectedWound()
         && !this.IsInfected
         && (!this.alcoholicBandage || !(this.getBandageLife() > 0.0F))
         && (this.getDeepWoundTime() > 0.0F || this.getScratchTime() > 0.0F || this.getCutTime() > 0.0F || this.getStitchTime() > 0.0F)) {
    char var4 = '鱀';
         if (!this.bandaged()) {
            var4 -= 10000;
         } else if (this.getBandageLife() == 0.0F) {
            var4 -= '袸';
         }

         if (this.getScratchTime() > 0.0F) {
            var4 -= 20000;
         }

         if (this.getCutTime() > 0.0F) {
            var4 -= 25000;
         }

         if (this.getDeepWoundTime() > 0.0F) {
            var4 -= 30000;
         }

         if (this.haveGlass()) {
            var4 -= 24000;
         }

         if (this.getBurnTime() > 0.0F) {
            var4 -= 23000;
            if (this.isNeedBurnWash()) {
               var4 -= 7000;
            }
         }

         if (BodyPartType.ToIndex(this.getType()) <= BodyPartType.ToIndex(BodyPartType.Torso_Lower)
            && this.ParentChar.getClothingItem_Torso() instanceof Clothing) {
    Clothing var2 = (Clothing)this.ParentChar.getClothingItem_Torso();
            if (var2.isDirty()) {
               var4 -= 20000;
            }

            if (var2.isBloody()) {
               var4 -= 24000;
            }
         }

         if (BodyPartType.ToIndex(this.getType()) >= BodyPartType.ToIndex(BodyPartType.UpperLeg_L)
            && BodyPartType.ToIndex(this.getType()) <= BodyPartType.ToIndex(BodyPartType.LowerLeg_R)
            && this.ParentChar.getClothingItem_Legs() instanceof Clothing) {
    Clothing var5 = (Clothing)this.ParentChar.getClothingItem_Legs();
            if (var5.isDirty()) {
               var4 -= 20000;
            }

            if (var5.isBloody()) {
               var4 -= 24000;
            }
         }

         if (var4 <= 5000) {
            var4 = 5000;
         }

         if (Rand.Next(Rand.AdjustForFramerate(var4)) == 0) {
            this.setInfectedWound(true);
         }
      } else if (this.isInfectedWound()) {
    bool var3 = false;
         if (this.getAlcoholLevel() > 0.0F) {
            this.setAlcoholLevel(this.getAlcoholLevel() - 2.0E-4F * GameTime.getInstance().getMultiplier());
            this.setWoundInfectionLevel(this.getWoundInfectionLevel() - 2.0E-4F * GameTime.getInstance().getMultiplier());
            if (this.getAlcoholLevel() < 0.0F) {
               this.setAlcoholLevel(0.0F);
            }

            var3 = true;
         }

         if (this.ParentChar.getReduceInfectionPower() > 0.0F) {
            this.setWoundInfectionLevel(this.getWoundInfectionLevel() - 2.0E-4F * GameTime.getInstance().getMultiplier());
            this.ParentChar.setReduceInfectionPower(this.ParentChar.getReduceInfectionPower() - 2.0E-4F * GameTime.getInstance().getMultiplier());
            if (this.ParentChar.getReduceInfectionPower() < 0.0F) {
               this.ParentChar.setReduceInfectionPower(0.0F);
            }

            var3 = true;
         }

         if (this.getGarlicFactor() > 0.0F) {
            this.setWoundInfectionLevel(this.getWoundInfectionLevel() - 2.0E-4F * GameTime.getInstance().getMultiplier());
            this.setGarlicFactor(this.getGarlicFactor() - 8.0E-4F * GameTime.getInstance().getMultiplier());
            var3 = true;
         }

         if (!var3) {
            if (this.IsInfected) {
               this.setWoundInfectionLevel(this.getWoundInfectionLevel() + 2.0E-4F * GameTime.getInstance().getMultiplier());
            } else if (this.haveGlass()) {
               this.setWoundInfectionLevel(this.getWoundInfectionLevel() + 1.0E-4F * GameTime.getInstance().getMultiplier());
            } else {
               this.setWoundInfectionLevel(this.getWoundInfectionLevel() + 1.0E-5F * GameTime.getInstance().getMultiplier());
            }

            if (this.getWoundInfectionLevel() > 10.0F) {
               this.setWoundInfectionLevel(10.0F);
            }
         }
      }

      if (!this.isInfectedWound() && this.getAlcoholLevel() > 0.0F) {
         this.setAlcoholLevel(this.getAlcoholLevel() - 2.0E-4F * GameTime.getInstance().getMultiplier());
         if (this.getAlcoholLevel() < 0.0F) {
            this.setAlcoholLevel(0.0F);
         }
      }

      if (this.isInfectedWound() && this.getBandageLife() > 0.0F) {
         if (this.alcoholicBandage) {
            this.setWoundInfectionLevel(this.getWoundInfectionLevel() - 6.0E-4F * GameTime.getInstance().getMultiplier());
         }

         this.setBandageLife(this.getBandageLife() - (float)(2.0E-4 * GameTime.getInstance().getMultiplier()));
      }

      if (this.getScratchTime() > 0.0F) {
         if (this.bandaged()) {
            this.setScratchTime(this.getScratchTime() - (float)(1.5E-4 * GameTime.getInstance().getMultiplier()));
            this.setBandageLife(this.getBandageLife() - (float)(8.0E-5 * GameTime.getInstance().getMultiplier()));
            if (this.getPlantainFactor() > 0.0F) {
               this.setScratchTime(this.getScratchTime() - (float)(1.0E-4 * GameTime.getInstance().getMultiplier()));
               this.setPlantainFactor(this.getPlantainFactor() - (float)(8.0E-4 * GameTime.getInstance().getMultiplier()));
            }
         } else {
            this.setScratchTime(this.getScratchTime() - (float)(1.0E-5 * GameTime.getInstance().getMultiplier()));
         }

         if (this.getScratchTime() < 0.0F) {
            this.setScratchTime(0.0F);
            this.setGetBandageXp(true);
            this.setGetStitchXp(true);
            this.setScratched(false, false);
            this.setBleeding(false);
            this.setBleedingTime(0.0F);
         }
      }

      if (this.getCutTime() > 0.0F) {
         if (this.bandaged()) {
            this.setCutTime(this.getCutTime() - (float)(5.0E-5 * GameTime.getInstance().getMultiplier()));
            this.setBandageLife(this.getBandageLife() - (float)(1.0E-5 * GameTime.getInstance().getMultiplier()));
            if (this.getPlantainFactor() > 0.0F) {
               this.setCutTime(this.getCutTime() - (float)(5.0E-5 * GameTime.getInstance().getMultiplier()));
               this.setPlantainFactor(this.getPlantainFactor() - (float)(8.0E-4 * GameTime.getInstance().getMultiplier()));
            }
         } else {
            this.setCutTime(this.getCutTime() - (float)(1.0E-6 * GameTime.getInstance().getMultiplier()));
         }

         if (this.getCutTime() < 0.0F) {
            this.setCutTime(0.0F);
            this.setGetBandageXp(true);
            this.setGetStitchXp(true);
            this.setBleeding(false);
            this.setBleedingTime(0.0F);
         }
      }

      if (this.getDeepWoundTime() > 0.0F) {
         if (this.bandaged()) {
            this.setDeepWoundTime(this.getDeepWoundTime() - (float)(2.0E-5 * GameTime.getInstance().getMultiplier()));
            this.setBandageLife(this.getBandageLife() - (float)(1.0E-4 * GameTime.getInstance().getMultiplier()));
            if (this.getPlantainFactor() > 0.0F) {
               this.setDeepWoundTime(this.getDeepWoundTime() - (float)(7.0E-6 * GameTime.getInstance().getMultiplier()));
               this.setPlantainFactor(this.getPlantainFactor() - (float)(8.0E-4 * GameTime.getInstance().getMultiplier()));
               if (this.getPlantainFactor() < 0.0F) {
                  this.setPlantainFactor(0.0F);
               }
            }
         } else {
            this.setDeepWoundTime(this.getDeepWoundTime() - (float)(2.0E-6 * GameTime.getInstance().getMultiplier()));
         }

         if ((this.haveGlass() || !this.bandaged()) && this.getDeepWoundTime() < 3.0F) {
            this.setDeepWoundTime(3.0F);
         }

         if (this.getDeepWoundTime() < 0.0F) {
            this.setGetBandageXp(true);
            this.setGetStitchXp(true);
            this.setDeepWoundTime(0.0F);
            this.setDeepWounded(false);
         }
      }

      if (this.getStitchTime() > 0.0F && this.getStitchTime() < 50.0F) {
         if (this.bandaged()) {
            this.setStitchTime(this.getStitchTime() + (float)(4.0E-4 * GameTime.getInstance().getMultiplier()));
            this.setBandageLife(this.getBandageLife() - (float)(1.0E-4 * GameTime.getInstance().getMultiplier()));
            if (!this.alcoholicBandage && Rand.Next(Rand.AdjustForFramerate(80000)) == 0) {
               this.setInfectedWound(true);
            }

            this.setStitchTime(this.getStitchTime() + (float)(1.0E-4 * GameTime.getInstance().getMultiplier()));
         } else {
            this.setStitchTime(this.getStitchTime() + (float)(2.0E-4 * GameTime.getInstance().getMultiplier()));
            if (Rand.Next(Rand.AdjustForFramerate(20000)) == 0) {
               this.setInfectedWound(true);
            }
         }

         if (this.getStitchTime() > 30.0F) {
            this.setGetStitchXp(true);
         }

         if (this.getStitchTime() > 50.0F) {
            this.setStitchTime(50.0F);
         }
      }

      if (this.getFractureTime() > 0.0F) {
         if (this.getSplintFactor() > 0.0F) {
            this.setFractureTime(this.getFractureTime() - (float)(5.0E-5 * GameTime.getInstance().getMultiplier() * this.getSplintFactor()));
         } else {
            this.setFractureTime(this.getFractureTime() - (float)(5.0E-6 * GameTime.getInstance().getMultiplier()));
         }

         if (this.getComfreyFactor() > 0.0F) {
            this.setFractureTime(this.getFractureTime() - (float)(5.0E-6 * GameTime.getInstance().getMultiplier()));
            this.setComfreyFactor(this.getComfreyFactor() - (float)(5.0E-4 * GameTime.getInstance().getMultiplier()));
         }

         if (this.getFractureTime() < 0.0F) {
            this.setFractureTime(0.0F);
            this.setGetSplintXp(true);
         }
      }

      if (this.getAdditionalPain() > 0.0F) {
         this.setAdditionalPain(this.getAdditionalPain() - (float)(0.005 * GameTime.getInstance().getMultiplier()));
         if (this.getAdditionalPain() < 0.0F) {
            this.setAdditionalPain(0.0F);
         }
      }

      if (this.getStiffness() > 0.0F
         && this.dynamic_cast<IsoPlayer*>(ParentChar) != nullptr
         && ((IsoPlayer)this.ParentChar).getFitness() != nullptr
         && !((IsoPlayer)this.ParentChar).getFitness().onGoingStiffness()) {
         this.setStiffness(this.getStiffness() - (float)(0.002 * GameTime.getInstance().getMultiplier()));
         if (this.getStiffness() < 0.0F) {
            this.setStiffness(0.0F);
         }
      }

      if (this.getBandageLife() < 0.0F) {
         this.setBandageLife(0.0F);
         this.setGetBandageXp(true);
      }

      if ((this.getWoundInfectionLevel() > 0.0F || this.isInfectedWound())
         && this.getBurnTime() <= 0.0F
         && this.getFractureTime() <= 0.0F
         && this.getDeepWoundTime() <= 0.0F
         && this.getScratchTime() <= 0.0F
         && this.getBiteTime() <= 0.0F
         && this.getCutTime() <= 0.0F
         && this.getStitchTime() <= 0.0F) {
         this.setWoundInfectionLevel(0.0F);
      }

      if (this.Health < 0.0F) {
         this.Health = 0.0F;
      }
   }

    float getHealth() {
      return this.Health;
   }

    void SetHealth(float var1) {
      this.Health = var1;
   }

    void AddHealth(float var1) {
      this.Health += var1;
      if (this.Health > 100.0F) {
         this.Health = 100.0F;
      }
   }

    void ReduceHealth(float var1) {
      this.Health -= var1;
      if (this.Health < 0.0F) {
         this.Health = 0.0F;
      }
   }

    bool HasInjury() {
      return this.bitten
         | this.scratched
         | this.deepWounded
         | this.bleeding
         | this.getBiteTime() > 0.0F
         | this.getScratchTime() > 0.0F
         | this.getCutTime() > 0.0F
         | this.getFractureTime() > 0.0F
         | this.haveBullet()
         | this.getBurnTime() > 0.0F;
   }

    bool bandaged() {
      return this.bandaged;
   }

    bool bitten() {
      return this.bitten;
   }

    bool bleeding() {
      return this.bleeding;
   }

    bool IsBleedingStemmed() {
      return this.IsBleedingStemmed;
   }

    bool IsCortorised() {
      return this.IsCortorised;
   }

    bool IsInfected() {
      return this.IsInfected;
   }

    void SetInfected(bool var1) {
      this.IsInfected = var1;
   }

    void SetFakeInfected(bool var1) {
      this.IsFakeInfected = var1;
   }

    bool IsFakeInfected() {
      return this.IsFakeInfected;
   }

    void DisableFakeInfection() {
      this.IsFakeInfected = false;
   }

    bool scratched() {
      return this.scratched;
   }

    bool stitched() {
      return this.stitched;
   }

    bool deepWounded() {
      return this.deepWounded;
   }

    void RestoreToFullHealth() {
      this.Health = 100.0F;
      this.additionalPain = 0.0F;
      this.alcoholicBandage = false;
      this.alcoholLevel = 0.0F;
      this.bleeding = false;
      this.bandaged = false;
      this.bandageLife = 0.0F;
      this.biteTime = 0.0F;
      this.bitten = false;
      this.bleedingTime = 0.0F;
      this.burnTime = 0.0F;
      this.comfreyFactor = 0.0F;
      this.deepWounded = false;
      this.deepWoundTime = 0.0F;
      this.fractureTime = 0.0F;
      this.garlicFactor = 0.0F;
      this.haveBullet = false;
      this.haveGlass = false;
      this.infectedWound = false;
      this.IsBleedingStemmed = false;
      this.IsCortorised = false;
      this.IsFakeInfected = false;
      this.IsInfected = false;
      this.lastTimeBurnWash = 0.0F;
      this.needBurnWash = false;
      this.plantainFactor = 0.0F;
      this.scratched = false;
      this.scratchTime = 0.0F;
      this.splint = false;
      this.splintFactor = 0.0F;
      this.splintItem = nullptr;
      this.stitched = false;
      this.stitchTime = 0.0F;
      this.woundInfectionLevel = 0.0F;
      this.cutTime = 0.0F;
      this.cut = false;
   }

    void setBandaged(bool var1, float var2) {
      this.setBandaged(var1, var2, false, nullptr);
   }

    void setBandaged(bool var1, float var2, bool var3, const std::string& var4) {
      if (var1) {
         if (this.bleeding) {
            this.bleeding = false;
         }

         this.bitten = false;
         this.scratched = false;
         this.cut = false;
         this.alcoholicBandage = var3;
         this.stitched = false;
         this.deepWounded = false;
         this.setBandageType(var4);
         this.setGetBandageXp(false);
      } else {
         if (this.getScratchTime() > 0.0F) {
            this.scratched = true;
         }

         if (this.getCutTime() > 0.0F) {
            this.cut = true;
         }

         if (this.getBleedingTime() > 0.0F) {
            this.bleeding = true;
         }

         if (this.getBiteTime() > 0.0F) {
            this.bitten = true;
         }

         if (this.getStitchTime() > 0.0F) {
            this.stitched = true;
         }

         if (this.getDeepWoundTime() > 0.0F) {
            this.deepWounded = true;
         }
      }

      this.setBandageLife(var2);
      this.bandaged = var1;
   }

    void SetBitten(bool var1) {
      this.bitten = var1;
      if (var1) {
         this.bleeding = true;
         this.IsBleedingStemmed = false;
         this.IsCortorised = false;
         this.bandaged = false;
         this.setInfectedWound(true);
         this.setBiteTime(Rand.Next(50.0F, 80.0F));
         if (this.ParentChar.Traits.FastHealer.isSet()) {
            this.setBiteTime(Rand.Next(30.0F, 50.0F));
         }

         if (this.ParentChar.Traits.SlowHealer.isSet()) {
            this.setBiteTime(Rand.Next(80.0F, 150.0F));
         }
      }

      if (SandboxOptions.instance.Lore.Transmission.getValue() != 4) {
         this.IsInfected = true;
         this.IsFakeInfected = false;
      }

      if (this.IsInfected && SandboxOptions.instance.Lore.Mortality.getValue() == 7) {
         this.IsInfected = false;
         this.IsFakeInfected = true;
      }

      this.generateBleeding();
   }

    void SetBitten(bool var1, bool var2) {
      this.bitten = var1;
      if (SandboxOptions.instance.Lore.Transmission.getValue() == 4) {
         this.IsInfected = false;
         this.IsFakeInfected = false;
         var2 = false;
      }

      if (var1) {
         this.bleeding = true;
         this.IsBleedingStemmed = false;
         this.IsCortorised = false;
         this.bandaged = false;
         if (var2) {
            this.IsInfected = true;
         }

         this.IsFakeInfected = false;
         if (this.IsInfected && SandboxOptions.instance.Lore.Mortality.getValue() == 7) {
            this.IsInfected = false;
            this.IsFakeInfected = true;
         }
      }
   }

    void setBleeding(bool var1) {
      this.bleeding = var1;
   }

    void SetBleedingStemmed(bool var1) {
      if (this.bleeding) {
         this.bleeding = false;
         this.IsBleedingStemmed = true;
      }
   }

    void SetCortorised(bool var1) {
      this.IsCortorised = var1;
      if (var1) {
         this.bleeding = false;
         this.IsBleedingStemmed = false;
         this.deepWounded = false;
         this.bandaged = false;
      }
   }

    void setCut(bool var1) {
      this.setCut(var1, true);
   }

    void setCut(bool var1, bool var2) {
      this.cut = var1;
      if (var1) {
         this.setStitched(false);
         this.setBandaged(false, 0.0F);
    float var3 = Rand.Next(10.0F, 20.0F);
         if (this.ParentChar.Traits.FastHealer.isSet()) {
            var3 = Rand.Next(5.0F, 10.0F);
         }

         if (this.ParentChar.Traits.SlowHealer.isSet()) {
            var3 = Rand.Next(20.0F, 30.0F);
         }

         switch (SandboxOptions.instance.InjurySeverity.getValue()) {
            case 1:
               var3 *= 0.5F;
               break;
            case 3:
               var3 *= 1.5F;
         }

         this.setCutTime(var3);
         this.generateBleeding();
         if (!var2) {
            this.generateZombieInfection(25);
         }
      } else {
         this.setBleeding(false);
      }
   }

    void generateZombieInfection(int var1) {
      if (Rand.Next(100) < var1) {
         this.IsInfected = true;
      }

      if (!this.IsInfected && this.ParentChar.Traits.Hypercondriac.isSet() && Rand.Next(100) < 80) {
         this.IsFakeInfected = true;
      }

      if (SandboxOptions.instance.Lore.Transmission.getValue() == 2 || SandboxOptions.instance.Lore.Transmission.getValue() == 4) {
         this.IsInfected = false;
         this.IsFakeInfected = false;
      }

      if (this.IsInfected && SandboxOptions.instance.Lore.Mortality.getValue() == 7) {
         this.IsInfected = false;
         this.IsFakeInfected = true;
      }
   }

    void setScratched(bool var1, bool var2) {
      this.scratched = var1;
      if (var1) {
         this.setStitched(false);
         this.setBandaged(false, 0.0F);
    float var3 = Rand.Next(7.0F, 15.0F);
         if (this.ParentChar.Traits.FastHealer.isSet()) {
            var3 = Rand.Next(4.0F, 10.0F);
         }

         if (this.ParentChar.Traits.SlowHealer.isSet()) {
            var3 = Rand.Next(15.0F, 25.0F);
         }

         switch (SandboxOptions.instance.InjurySeverity.getValue()) {
            case 1:
               this.scratchTime *= 0.5F;
               break;
            case 3:
               this.scratchTime *= 1.5F;
         }

         this.setScratchTime(var3);
         this.generateBleeding();
         if (!var2) {
            this.generateZombieInfection(7);
         }
      } else {
         this.setBleeding(false);
      }
   }

    void SetScratchedWeapon(bool var1) {
      this.scratched = var1;
      if (var1) {
         this.setStitched(false);
         this.setBandaged(false, 0.0F);
    float var2 = Rand.Next(5.0F, 10.0F);
         if (this.ParentChar.Traits.FastHealer.isSet()) {
            var2 = Rand.Next(1.0F, 5.0F);
         }

         if (this.ParentChar.Traits.SlowHealer.isSet()) {
            var2 = Rand.Next(10.0F, 20.0F);
         }

         switch (SandboxOptions.instance.InjurySeverity.getValue()) {
            case 1:
               this.scratchTime *= 0.5F;
               break;
            case 3:
               this.scratchTime *= 1.5F;
         }

         this.setScratchTime(var2);
         this.generateBleeding();
      }
   }

    void generateDeepWound() {
    float var1 = Rand.Next(15.0F, 20.0F);
      if (this.ParentChar.Traits.FastHealer.isSet()) {
         var1 = Rand.Next(11.0F, 15.0F);
      } else if (this.ParentChar.Traits.SlowHealer.isSet()) {
         var1 = Rand.Next(20.0F, 32.0F);
      }

      switch (SandboxOptions.instance.InjurySeverity.getValue()) {
         case 1:
            var1 *= 0.5F;
            break;
         case 3:
            var1 *= 1.5F;
      }

      this.setDeepWoundTime(var1);
      this.setDeepWounded(true);
      this.generateBleeding();
   }

    void generateDeepShardWound() {
    float var1 = Rand.Next(15.0F, 20.0F);
      if (this.ParentChar.Traits.FastHealer.isSet()) {
         var1 = Rand.Next(11.0F, 15.0F);
      } else if (this.ParentChar.Traits.SlowHealer.isSet()) {
         var1 = Rand.Next(20.0F, 32.0F);
      }

      switch (SandboxOptions.instance.InjurySeverity.getValue()) {
         case 1:
            var1 *= 0.5F;
            break;
         case 3:
            var1 *= 1.5F;
      }

      this.setDeepWoundTime(var1);
      this.setHaveGlass(true);
      this.setDeepWounded(true);
      this.generateBleeding();
   }

    void SetScratchedWindow(bool var1) {
      if (var1) {
         this.setBandaged(false, 0.0F);
         this.setStitched(false);
         if (Rand.Next(7) == 0) {
            this.generateDeepShardWound();
         } else {
            this.scratched = var1;
    float var2 = Rand.Next(12.0F, 20.0F);
            if (this.ParentChar.Traits.FastHealer.isSet()) {
               var2 = Rand.Next(5.0F, 10.0F);
            }

            if (this.ParentChar.Traits.SlowHealer.isSet()) {
               var2 = Rand.Next(20.0F, 30.0F);
            }

            switch (SandboxOptions.instance.InjurySeverity.getValue()) {
               case 1:
                  this.scratchTime *= 0.5F;
                  break;
               case 3:
                  this.scratchTime *= 1.5F;
            }

            this.setScratchTime(var2);
         }

         this.generateBleeding();
      }
   }

    void setStitched(bool var1) {
      if (var1) {
         this.setBleedingTime(0.0F);
         this.setBleeding(false);
         this.setDeepWoundTime(0.0F);
         this.setDeepWounded(false);
         this.setGetStitchXp(false);
      } else if (this.stitched) {
         this.stitched = false;
         if (this.getStitchTime() < 40.0F) {
            this.setDeepWoundTime(Rand.Next(10.0F, this.getStitchTime()));
            this.setBleedingTime(Rand.Next(10.0F, this.getStitchTime()));
            this.setStitchTime(0.0F);
            this.setDeepWounded(true);
         } else {
            this.setScratchTime(Rand.Next(2.0F, this.getStitchTime() - 40.0F));
            this.scratched = true;
            this.setStitchTime(0.0F);
         }
      }

      this.stitched = var1;
   }

    void damageFromFirearm(float var1) {
      this.setHaveBullet(true, 0);
   }

    float getPain() {
    float var1 = 0.0F;
      if (this.getScratchTime() > 0.0F) {
         var1 += this.getScratchTime() * 1.7F;
      }

      if (this.getCutTime() > 0.0F) {
         var1 += this.getCutTime() * 2.5F;
      }

      if (this.getBiteTime() > 0.0F) {
         if (this.bandaged()) {
            var1 += 30.0F;
         } else if (!this.bandaged()) {
            var1 += 50.0F;
         }
      }

      if (this.getDeepWoundTime() > 0.0F) {
         var1 += this.getDeepWoundTime() * 3.7F;
      }

      if (this.getStitchTime() > 0.0F && this.getStitchTime() < 35.0F) {
         if (this.bandaged()) {
            var1 += (35.0F - this.getStitchTime()) / 2.0F;
         } else {
            var1 += 35.0F - this.getStitchTime();
         }
      }

      if (this.getFractureTime() > 0.0F) {
         if (this.getSplintFactor() > 0.0F) {
            var1 += this.getFractureTime() / 2.0F;
         } else {
            var1 += this.getFractureTime();
         }
      }

      if (this.haveBullet()) {
         var1 += 50.0F;
      }

      if (this.haveGlass()) {
         var1 += 10.0F;
      }

      if (this.getBurnTime() > 0.0F) {
         var1 += this.getBurnTime();
      }

      if (this.bandaged()) {
         var1 /= 1.5F;
      }

      if (this.getWoundInfectionLevel() > 0.0F) {
         var1 += this.getWoundInfectionLevel();
      }

      var1 += this.getAdditionalPain(true);
      switch (SandboxOptions.instance.InjurySeverity.getValue()) {
         case 1:
            var1 *= 0.7F;
            break;
         case 3:
            var1 *= 1.3F;
      }

    return var1;
   }

    float getBiteTime() {
      return this.biteTime;
   }

    void setBiteTime(float var1) {
      this.biteTime = var1;
   }

    float getDeepWoundTime() {
      return this.deepWoundTime;
   }

    void setDeepWoundTime(float var1) {
      this.deepWoundTime = var1;
   }

    bool haveGlass() {
      return this.haveGlass;
   }

    void setHaveGlass(bool var1) {
      this.haveGlass = var1;
   }

    float getStitchTime() {
      return this.stitchTime;
   }

    void setStitchTime(float var1) {
      this.stitchTime = var1;
   }

    int getIndex() {
      return BodyPartType.ToIndex(this.Type);
   }

    float getAlcoholLevel() {
      return this.alcoholLevel;
   }

    void setAlcoholLevel(float var1) {
      this.alcoholLevel = var1;
   }

    float getAdditionalPain(bool var1) {
      return var1 ? this.additionalPain + this.stiffness / 3.5F : this.additionalPain;
   }

    float getAdditionalPain() {
      return this.additionalPain;
   }

    void setAdditionalPain(float var1) {
      this.additionalPain = var1;
   }

    std::string getBandageType() {
      return this.bandageType;
   }

    void setBandageType(const std::string& var1) {
      this.bandageType = var1;
   }

    bool isGetBandageXp() {
      return this.getBandageXp;
   }

    void setGetBandageXp(bool var1) {
      this.getBandageXp = var1;
   }

    bool isGetStitchXp() {
      return this.getStitchXp;
   }

    void setGetStitchXp(bool var1) {
      this.getStitchXp = var1;
   }

    float getSplintFactor() {
      return this.splintFactor;
   }

    void setSplintFactor(float var1) {
      this.splintFactor = var1;
   }

    float getFractureTime() {
      return this.fractureTime;
   }

    void setFractureTime(float var1) {
      this.fractureTime = var1;
   }

    bool isGetSplintXp() {
      return this.getSplintXp;
   }

    void setGetSplintXp(bool var1) {
      this.getSplintXp = var1;
   }

    bool isSplint() {
      return this.splint;
   }

    void setSplint(bool var1, float var2) {
      this.splint = var1;
      this.setSplintFactor(var2);
      if (var1) {
         this.setGetSplintXp(false);
      }
   }

    bool haveBullet() {
      return this.haveBullet;
   }

    void setHaveBullet(bool var1, int var2) {
      if (this.haveBullet && !var1) {
    float var3 = Rand.Next(17.0F, 23.0F) - var2 / 2;
         if (this.ParentChar != nullptr && this.ParentChar.Traits != nullptr) {
            if (this.ParentChar.Traits.FastHealer.isSet()) {
               var3 = Rand.Next(12.0F, 18.0F) - var2 / 2;
            } else if (this.ParentChar.Traits.SlowHealer.isSet()) {
               var3 = Rand.Next(22.0F, 28.0F) - var2 / 2;
            }
         }

         switch (SandboxOptions.instance.InjurySeverity.getValue()) {
            case 1:
               var3 *= 0.5F;
               break;
            case 3:
               var3 *= 1.5F;
         }

         this.setDeepWoundTime(var3);
         this.setDeepWounded(true);
         this.haveBullet = false;
         this.generateBleeding();
      } else if (var1) {
         this.haveBullet = true;
         this.generateBleeding();
      }

      this.haveBullet = var1;
   }

    float getBurnTime() {
      return this.burnTime;
   }

    void setBurnTime(float var1) {
      this.burnTime = var1;
   }

    bool isNeedBurnWash() {
      return this.needBurnWash;
   }

    void setNeedBurnWash(bool var1) {
      if (this.needBurnWash && !var1) {
         this.setLastTimeBurnWash(this.getBurnTime());
      }

      this.needBurnWash = var1;
   }

    float getLastTimeBurnWash() {
      return this.lastTimeBurnWash;
   }

    void setLastTimeBurnWash(float var1) {
      this.lastTimeBurnWash = var1;
   }

    bool isInfectedWound() {
      return this.infectedWound;
   }

    void setInfectedWound(bool var1) {
      this.infectedWound = var1;
   }

    BodyPartType getType() {
      return this.Type;
   }

    float getBleedingTime() {
      return this.bleedingTime;
   }

    void setBleedingTime(float var1) {
      this.bleedingTime = var1;
      if (!this.bandaged()) {
         this.setBleeding(var1 > 0.0F);
      }
   }

    bool isDeepWounded() {
      return this.deepWounded;
   }

    void setDeepWounded(bool var1) {
      this.deepWounded = var1;
      if (var1) {
         this.bleeding = true;
         this.IsBleedingStemmed = false;
         this.IsCortorised = false;
         this.bandaged = false;
         this.stitched = false;
      }
   }

    float getBandageLife() {
      return this.bandageLife;
   }

    void setBandageLife(float var1) {
      this.bandageLife = var1;
      if (this.bandageLife <= 0.0F) {
         this.alcoholicBandage = false;
      }
   }

    float getScratchTime() {
      return this.scratchTime;
   }

    void setScratchTime(float var1) {
      var1 = Math.min(100.0F, var1);
      this.scratchTime = var1;
   }

    float getWoundInfectionLevel() {
      return this.woundInfectionLevel;
   }

    void setWoundInfectionLevel(float var1) {
      this.woundInfectionLevel = var1;
      if (this.woundInfectionLevel <= 0.0F) {
         this.setInfectedWound(false);
         if (this.woundInfectionLevel < -2.0F) {
            this.woundInfectionLevel = -2.0F;
         }
      } else {
         this.setInfectedWound(true);
      }
   }

    void setBurned() {
    float var1 = Rand.Next(50.0F, 100.0F);
      switch (SandboxOptions.instance.InjurySeverity.getValue()) {
         case 1:
            var1 *= 0.5F;
            break;
         case 3:
            var1 *= 1.5F;
      }

      this.setBurnTime(var1);
      this.setNeedBurnWash(true);
      this.setLastTimeBurnWash(0.0F);
   }

    std::string getSplintItem() {
      return this.splintItem;
   }

    void setSplintItem(const std::string& var1) {
      this.splintItem = var1;
   }

    float getPlantainFactor() {
      return this.plantainFactor;
   }

    void setPlantainFactor(float var1) {
      this.plantainFactor = PZMath.clamp(var1, 0.0F, 100.0F);
   }

    float getGarlicFactor() {
      return this.garlicFactor;
   }

    void setGarlicFactor(float var1) {
      this.garlicFactor = PZMath.clamp(var1, 0.0F, 100.0F);
   }

    float getComfreyFactor() {
      return this.comfreyFactor;
   }

    void setComfreyFactor(float var1) {
      this.comfreyFactor = PZMath.clamp(var1, 0.0F, 100.0F);
   }

    void sync(BodyPart var1, Updater var2) {
      if (var2.updateField((byte)1, this.Health, var1.Health)) {
         var1.Health = this.Health;
      }

      if (this.bandaged != var1.bandaged) {
         var2.updateField((byte)2, this.bandaged);
         var1.bandaged = this.bandaged;
      }

      if (this.bitten != var1.bitten) {
         var2.updateField((byte)3, this.bitten);
         var1.bitten = this.bitten;
      }

      if (this.bleeding != var1.bleeding) {
         var2.updateField((byte)4, this.bleeding);
         var1.bleeding = this.bleeding;
      }

      if (this.IsBleedingStemmed != var1.IsBleedingStemmed) {
         var2.updateField((byte)5, this.IsBleedingStemmed);
         var1.IsBleedingStemmed = this.IsBleedingStemmed;
      }

      if (this.scratched != var1.scratched) {
         var2.updateField((byte)7, this.scratched);
         var1.scratched = this.scratched;
      }

      if (this.cut != var1.cut) {
         var2.updateField((byte)39, this.cut);
         var1.cut = this.cut;
      }

      if (this.stitched != var1.stitched) {
         var2.updateField((byte)8, this.stitched);
         var1.stitched = this.stitched;
      }

      if (this.deepWounded != var1.deepWounded) {
         var2.updateField((byte)9, this.deepWounded);
         var1.deepWounded = this.deepWounded;
      }

      if (this.IsInfected != var1.IsInfected) {
         var2.updateField((byte)10, this.IsInfected);
         var1.IsInfected = this.IsInfected;
      }

      if (this.IsFakeInfected != var1.IsFakeInfected) {
         var2.updateField((byte)11, this.IsFakeInfected);
         var1.IsFakeInfected = this.IsFakeInfected;
      }

      if (var2.updateField((byte)12, this.bandageLife, var1.bandageLife)) {
         var1.bandageLife = this.bandageLife;
      }

      if (var2.updateField((byte)13, this.scratchTime, var1.scratchTime)) {
         var1.scratchTime = this.scratchTime;
      }

      if (var2.updateField((byte)14, this.biteTime, var1.biteTime)) {
         var1.biteTime = this.biteTime;
      }

      if (this.alcoholicBandage != var1.alcoholicBandage) {
         var2.updateField((byte)15, this.alcoholicBandage);
         var1.alcoholicBandage = this.alcoholicBandage;
      }

      if (var2.updateField((byte)16, this.woundInfectionLevel, var1.woundInfectionLevel)) {
         var1.woundInfectionLevel = this.woundInfectionLevel;
      }

      if (var2.updateField((byte)41, this.stiffness, var1.stiffness)) {
         var1.stiffness = this.stiffness;
      }

      if (this.infectedWound != var1.infectedWound) {
         var2.updateField((byte)17, this.infectedWound);
         var1.infectedWound = this.infectedWound;
      }

      if (var2.updateField((byte)18, this.bleedingTime, var1.bleedingTime)) {
         var1.bleedingTime = this.bleedingTime;
      }

      if (var2.updateField((byte)19, this.deepWoundTime, var1.deepWoundTime)) {
         var1.deepWoundTime = this.deepWoundTime;
      }

      if (var2.updateField((byte)40, this.cutTime, var1.cutTime)) {
         var1.cutTime = this.cutTime;
      }

      if (this.haveGlass != var1.haveGlass) {
         var2.updateField((byte)20, this.haveGlass);
         var1.haveGlass = this.haveGlass;
      }

      if (var2.updateField((byte)21, this.stitchTime, var1.stitchTime)) {
         var1.stitchTime = this.stitchTime;
      }

      if (var2.updateField((byte)22, this.alcoholLevel, var1.alcoholLevel)) {
         var1.alcoholLevel = this.alcoholLevel;
      }

      if (var2.updateField((byte)23, this.additionalPain, var1.additionalPain)) {
         var1.additionalPain = this.additionalPain;
      }

      if (this.bandageType != var1.bandageType) {
         var2.updateField((byte)24, this.bandageType);
         var1.bandageType = this.bandageType;
      }

      if (this.getBandageXp != var1.getBandageXp) {
         var2.updateField((byte)25, this.getBandageXp);
         var1.getBandageXp = this.getBandageXp;
      }

      if (this.getStitchXp != var1.getStitchXp) {
         var2.updateField((byte)26, this.getStitchXp);
         var1.getStitchXp = this.getStitchXp;
      }

      if (this.getSplintXp != var1.getSplintXp) {
         var2.updateField((byte)27, this.getSplintXp);
         var1.getSplintXp = this.getSplintXp;
      }

      if (var2.updateField((byte)28, this.fractureTime, var1.fractureTime)) {
         var1.fractureTime = this.fractureTime;
      }

      if (this.splint != var1.splint) {
         var2.updateField((byte)29, this.splint);
         var1.splint = this.splint;
      }

      if (var2.updateField((byte)30, this.splintFactor, var1.splintFactor)) {
         var1.splintFactor = this.splintFactor;
      }

      if (this.haveBullet != var1.haveBullet) {
         var2.updateField((byte)31, this.haveBullet);
         var1.haveBullet = this.haveBullet;
      }

      if (var2.updateField((byte)32, this.burnTime, var1.burnTime)) {
         var1.burnTime = this.burnTime;
      }

      if (this.needBurnWash != var1.needBurnWash) {
         var2.updateField((byte)33, this.needBurnWash);
         var1.needBurnWash = this.needBurnWash;
      }

      if (var2.updateField((byte)34, this.lastTimeBurnWash, var1.lastTimeBurnWash)) {
         var1.lastTimeBurnWash = this.lastTimeBurnWash;
      }

      if (this.splintItem != var1.splintItem) {
         var2.updateField((byte)35, this.splintItem);
         var1.splintItem = this.splintItem;
      }

      if (var2.updateField((byte)36, this.plantainFactor, var1.plantainFactor)) {
         var1.plantainFactor = this.plantainFactor;
      }

      if (var2.updateField((byte)37, this.comfreyFactor, var1.comfreyFactor)) {
         var1.comfreyFactor = this.comfreyFactor;
      }

      if (var2.updateField((byte)38, this.garlicFactor, var1.garlicFactor)) {
         var1.garlicFactor = this.garlicFactor;
      }
   }

    void sync(ByteBuffer var1, uint8_t var2) {
      switch (var2) {
         case 1:
            this.Health = var1.getFloat();
            break;
         case 2:
            this.bandaged = var1.get() == 1;
            break;
         case 3:
            this.bitten = var1.get() == 1;
            break;
         case 4:
            this.bleeding = var1.get() == 1;
            break;
         case 5:
            this.IsBleedingStemmed = var1.get() == 1;
            break;
         case 6:
            this.IsCortorised = var1.get() == 1;
            break;
         case 7:
            this.scratched = var1.get() == 1;
            break;
         case 8:
            this.stitched = var1.get() == 1;
            break;
         case 9:
            this.deepWounded = var1.get() == 1;
            break;
         case 10:
            this.IsInfected = var1.get() == 1;
            break;
         case 11:
            this.IsFakeInfected = var1.get() == 1;
            break;
         case 12:
            this.bandageLife = var1.getFloat();
            break;
         case 13:
            this.scratchTime = var1.getFloat();
            break;
         case 14:
            this.biteTime = var1.getFloat();
            break;
         case 15:
            this.alcoholicBandage = var1.get() == 1;
            break;
         case 16:
            this.woundInfectionLevel = var1.getFloat();
            break;
         case 17:
            this.infectedWound = var1.get() == 1;
            break;
         case 18:
            this.bleedingTime = var1.getFloat();
            break;
         case 19:
            this.deepWoundTime = var1.getFloat();
            break;
         case 20:
            this.haveGlass = var1.get() == 1;
            break;
         case 21:
            this.stitchTime = var1.getFloat();
            break;
         case 22:
            this.alcoholLevel = var1.getFloat();
            break;
         case 23:
            this.additionalPain = var1.getFloat();
            break;
         case 24:
            this.bandageType = GameWindow.ReadStringUTF(var1);
            break;
         case 25:
            this.getBandageXp = var1.get() == 1;
            break;
         case 26:
            this.getStitchXp = var1.get() == 1;
            break;
         case 27:
            this.getSplintXp = var1.get() == 1;
            break;
         case 28:
            this.fractureTime = var1.getFloat();
            break;
         case 29:
            this.splint = var1.get() == 1;
            break;
         case 30:
            this.splintFactor = var1.getFloat();
            break;
         case 31:
            this.haveBullet = var1.get() == 1;
            break;
         case 32:
            this.burnTime = var1.getFloat();
            break;
         case 33:
            this.needBurnWash = var1.get() == 1;
            break;
         case 34:
            this.lastTimeBurnWash = var1.getFloat();
            break;
         case 35:
            this.splintItem = GameWindow.ReadStringUTF(var1);
            break;
         case 36:
            this.plantainFactor = var1.getFloat();
            break;
         case 37:
            this.comfreyFactor = var1.getFloat();
            break;
         case 38:
            this.garlicFactor = var1.getFloat();
            break;
         case 39:
            this.cut = var1.get() == 1;
            break;
         case 40:
            this.cutTime = var1.getFloat();
            break;
         case 41:
            this.stiffness = var1.getFloat();
      }
   }

    float getCutTime() {
      return this.cutTime;
   }

    void setCutTime(float var1) {
      var1 = Math.min(100.0F, var1);
      this.cutTime = var1;
   }

    bool isCut() {
      return this.cut;
   }

    float getScratchSpeedModifier() {
      return this.scratchSpeedModifier;
   }

    void setScratchSpeedModifier(float var1) {
      this.scratchSpeedModifier = var1;
   }

    float getCutSpeedModifier() {
      return this.cutSpeedModifier;
   }

    void setCutSpeedModifier(float var1) {
      this.cutSpeedModifier = var1;
   }

    float getBurnSpeedModifier() {
      return this.burnSpeedModifier;
   }

    void setBurnSpeedModifier(float var1) {
      this.burnSpeedModifier = var1;
   }

    float getDeepWoundSpeedModifier() {
      return this.deepWoundSpeedModifier;
   }

    void setDeepWoundSpeedModifier(float var1) {
      this.deepWoundSpeedModifier = var1;
   }

    bool isBurnt() {
      return this.getBurnTime() > 0.0F;
   }

    void generateBleeding() {
    float var1 = 0.0F;
      if (this.scratched()) {
         var1 = Rand.Next(this.getScratchTime() * 0.3F, this.getScratchTime() * 0.6F);
      }

      if (this.isCut()) {
         var1 += Rand.Next(this.getCutTime() * 0.7F, this.getCutTime() * 1.0F);
      }

      if (this.isBurnt()) {
         var1 += Rand.Next(this.getBurnTime() * 0.3F, this.getBurnTime() * 0.6F);
      }

      if (this.isDeepWounded()) {
         var1 += Rand.Next(this.getDeepWoundTime() * 0.7F, this.getDeepWoundTime());
      }

      if (this.haveGlass()) {
         var1 += Rand.Next(5.0F, 10.0F);
      }

      if (this.haveBullet()) {
         var1 += Rand.Next(5.0F, 10.0F);
      }

      if (this.bitten()) {
         var1 += Rand.Next(7.5F, 15.0F);
      }

      switch (SandboxOptions.instance.InjurySeverity.getValue()) {
         case 1:
            var1 *= 0.5F;
            break;
         case 3:
            var1 *= 1.5F;
      }

      var1 *= BodyPartType.getBleedingTimeModifyer(BodyPartType.ToIndex(this.getType()));
      this.setBleedingTime(var1);
   }

    float getInnerTemperature() {
      return this.thermalNode != nullptr ? this.thermalNode.getCelcius() : 0.0F;
   }

    float getSkinTemperature() {
      return this.thermalNode != nullptr ? this.thermalNode.getSkinCelcius() : 0.0F;
   }

    float getDistToCore() {
      return this.thermalNode != nullptr ? this.thermalNode.getDistToCore() : BodyPartType.GetDistToCore(this.Type);
   }

    float getSkinSurface() {
      return this.thermalNode != nullptr ? this.thermalNode.getSkinSurface() : BodyPartType.GetSkinSurface(this.Type);
   }

    ThermalNode getThermalNode() {
      return this.thermalNode;
   }

    float getWetness() {
      return this.wetness;
   }

    void setWetness(float var1) {
      this.wetness = PZMath.clamp(var1, 0.0F, 100.0F);
   }

    float getStiffness() {
      return this.stiffness;
   }

    void setStiffness(float var1) {
      this.stiffness = PZMath.clamp(var1, 0.0F, 100.0F);
   }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
