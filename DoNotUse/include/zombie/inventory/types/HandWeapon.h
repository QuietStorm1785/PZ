#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/scripting/objects/ModelWeaponPart.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/ui/ObjectTooltip/Layout.h"
#include "zombie/ui/ObjectTooltip/LayoutItem.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeader/HeaderSize.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {


class HandWeapon : public InventoryItem {
public:
    float WeaponLength;
    float SplatSize = 1.0F;
    int ammoPerShoot = 1;
    std::string magazineType = nullptr;
    bool angleFalloff = false;
    bool bCanBarracade = false;
    float doSwingBeforeImpact = 0.0F;
    std::string impactSound = "BaseballBatHit";
    bool knockBackOnNoDeath = true;
    float maxAngle = 1.0F;
    float maxDamage = 1.5F;
    int maxHitCount = 1000;
    float maxRange = 1.0F;
    bool ranged = false;
    float minAngle = 0.5F;
    float minDamage = 0.4F;
    float minimumSwingTime = 0.5F;
    float minRange = 0.0F;
    float noiseFactor = 0.0F;
    std::string otherHandRequire = nullptr;
    bool otherHandUse = false;
    std::string physicsObject = nullptr;
    float pushBackMod = 1.0F;
    bool rangeFalloff = false;
    bool shareDamage = true;
    int soundRadius = 0;
    int soundVolume = 0;
    bool splatBloodOnNoDeath = false;
    int splatNumber = 2;
    std::string swingSound = "BaseballBatSwing";
    float swingTime = 1.0F;
    float toHitModifier = 1.0F;
    bool useEndurance = true;
    bool useSelf = false;
    std::string weaponSprite = nullptr;
    std::string originalWeaponSprite = nullptr;
    float otherBoost = 1.0F;
    int DoorDamage = 1;
    std::string doorHitSound = "BaseballBatHit";
    int ConditionLowerChance = 10000;
    bool MultipleHitConditionAffected = true;
    bool shareEndurance = true;
    bool AlwaysKnockdown = false;
    float EnduranceMod = 1.0F;
    float KnockdownMod = 1.0F;
    bool CantAttackWithLowestEndurance = false;
    bool bIsAimedFirearm = false;
    bool bIsAimedHandWeapon = false;
    std::string RunAnim = "Run";
    std::string IdleAnim = "Idle";
    float HitAngleMod = 0.0F;
    std::string SubCategory = "";
   private std::vector<std::string> Categories = nullptr;
    int AimingPerkCritModifier = 0;
    float AimingPerkRangeModifier = 0.0F;
    float AimingPerkHitChanceModifier = 0.0F;
    int HitChance = 0;
    float AimingPerkMinAngleModifier = 0.0F;
    int RecoilDelay = 0;
    bool PiercingBullets = false;
    float soundGain = 1.0F;
    WeaponPart scope = nullptr;
    WeaponPart canon = nullptr;
    WeaponPart clip = nullptr;
    WeaponPart recoilpad = nullptr;
    WeaponPart sling = nullptr;
    WeaponPart stock = nullptr;
    int ClipSize = 0;
    int reloadTime = 0;
    int aimingTime = 0;
    float minRangeRanged = 0.0F;
    int treeDamage = 0;
    std::string bulletOutSound = nullptr;
    std::string shellFallSound = nullptr;
    int triggerExplosionTimer = 0;
    bool canBePlaced = false;
    int explosionRange = 0;
    int explosionPower = 0;
    int fireRange = 0;
    int firePower = 0;
    int smokeRange = 0;
    int noiseRange = 0;
    float extraDamage = 0.0F;
    int explosionTimer = 0;
    std::string placedSprite = nullptr;
    bool canBeReused = false;
    int sensorRange = 0;
    float critDmgMultiplier = 2.0F;
    float baseSpeed = 1.0F;
    float bloodLevel = 0.0F;
    std::string ammoBox = nullptr;
    std::string insertAmmoStartSound = nullptr;
    std::string insertAmmoSound = nullptr;
    std::string insertAmmoStopSound = nullptr;
    std::string ejectAmmoStartSound = nullptr;
    std::string ejectAmmoSound = nullptr;
    std::string ejectAmmoStopSound = nullptr;
    std::string rackSound = nullptr;
    std::string clickSound = "Stormy9mmClick";
    bool containsClip = false;
    std::string weaponReloadType = "handgun";
    bool rackAfterShoot = false;
    bool roundChambered = false;
    bool bSpentRoundChambered = false;
    int spentRoundCount = 0;
    float jamGunChance = 5.0F;
    bool isJammed = false;
   private std::vector<ModelWeaponPart> modelWeaponPart = nullptr;
    bool haveChamber = true;
    std::string bulletName = nullptr;
    std::string damageCategory = nullptr;
    bool damageMakeHole = false;
    std::string hitFloorSound = "BatOnFloor";
    bool insertAllBulletsReload = false;
    std::string fireMode = nullptr;
   private std::vector<std::string> fireModePossibilities = nullptr;
    int ProjectileCount = 1;
    float aimingMod = 1.0F;
    float CriticalChance = 20.0F;
    std::string hitSound = "BaseballBatHit";

    float getSplatSize() {
      return this.SplatSize;
   }

    bool CanStack(InventoryItem var1) {
    return false;
   }

    std::string getCategory() {
      return this.mainCategory != nullptr ? this.mainCategory : "Weapon";
   }

    public HandWeapon(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      super(var1, var2, var3, var4);
      this.cat = ItemType.Weapon;
   }

    public HandWeapon(const std::string& var1, const std::string& var2, const std::string& var3, Item var4) {
      super(var1, var2, var3, var4);
      this.cat = ItemType.Weapon;
   }

    bool IsWeapon() {
    return true;
   }

    int getSaveType() {
      return Type.Weapon.ordinal();
   }

    float getScore(SurvivorDesc var1) {
    float var2 = 0.0F;
      if (this.getAmmoType() != nullptr && !this.getAmmoType() == "none") && !this.container.contains(this.getAmmoType())) {
         var2 -= 100000.0F;
      }

      if (this.Condition == 0) {
         var2 -= 100000.0F;
      }

      var2 += this.maxDamage * 10.0F;
      var2 += this.maxAngle * 5.0F;
      var2 -= this.minimumSwingTime * 0.1F;
      var2 -= this.swingTime;
      if (var1 != nullptr && var1.getInstance().getThreatLevel() <= 2 && this.soundRadius > 5) {
         if (var2 > 0.0F && this.soundRadius > var2) {
            var2 = 1.0F;
         }

         var2 -= this.soundRadius;
      }

    return var2;
   }

    float getActualWeight() {
    float var1 = this.getScriptItem().getActualWeight();
      var1 += this.getWeaponPartWeightModifier(this.canon);
      var1 += this.getWeaponPartWeightModifier(this.clip);
      var1 += this.getWeaponPartWeightModifier(this.recoilpad);
      var1 += this.getWeaponPartWeightModifier(this.scope);
      var1 += this.getWeaponPartWeightModifier(this.sling);
      return var1 + this.getWeaponPartWeightModifier(this.stock);
   }

    float getWeight() {
      return this.getActualWeight();
   }

    float getContentsWeight() {
    float var1 = 0.0F;
      if (this.haveChamber() && this.isRoundChambered() && !StringUtils.isNullOrWhitespace(this.getAmmoType())) {
    Item var2 = ScriptManager.instance.FindItem(this.getAmmoType());
         if (var2 != nullptr) {
            var1 += var2.getActualWeight();
         }
      }

      if (this.isContainsClip() && !StringUtils.isNullOrWhitespace(this.getMagazineType())) {
    Item var3 = ScriptManager.instance.FindItem(this.getMagazineType());
         if (var3 != nullptr) {
            var1 += var3.getActualWeight();
         }
      }

      return var1 + super.getContentsWeight();
   }

    void DoTooltip(ObjectTooltip var1, Layout var2) {
    float var4 = 1.0F;
    float var5 = 1.0F;
    float var6 = 0.8F;
    float var7 = 1.0F;
    ColorInfo var8 = std::make_shared<ColorInfo>();
    LayoutItem var3 = var2.addItem();
      var3.setLabel(Translator.getText("Tooltip_weapon_Condition") + ":", var4, var5, var6, var7);
    float var9 = (float)this.Condition / this.ConditionMax;
      Core.getInstance().getBadHighlitedColor().interp(Core.getInstance().getGoodHighlitedColor(), var9, var8);
      var3.setProgress(var9, var8.getR(), var8.getG(), var8.getB(), 1.0F);
      if (this.getMaxDamage() > 0.0F) {
         var3 = var2.addItem();
         var3.setLabel(Translator.getText("Tooltip_weapon_Damage") + ":", var4, var5, var6, var7);
         var9 = this.getMaxDamage() + this.getMinDamage();
    float var10 = 5.0F;
    float var11 = var9 / var10;
         Core.getInstance().getBadHighlitedColor().interp(Core.getInstance().getGoodHighlitedColor(), var11, var8);
         var3.setProgress(var11, var8.getR(), var8.getG(), var8.getB(), 1.0F);
      }

      if (this.isRanged()) {
         var3 = var2.addItem();
         var3.setLabel(Translator.getText("Tooltip_weapon_Range") + ":", var4, var5, var6, 1.0F);
         var9 = this.getMaxRange(IsoPlayer.getInstance());
    float var38 = 40.0F;
    float var44 = var9 / var38;
         Core.getInstance().getBadHighlitedColor().interp(Core.getInstance().getGoodHighlitedColor(), var44, var8);
         var3.setProgress(var44, var8.getR(), var8.getG(), var8.getB(), 1.0F);
      }

      if (this.isTwoHandWeapon() && !this.isRequiresEquippedBothHands()) {
         var3 = var2.addItem();
         var3.setLabel(Translator.getText("Tooltip_item_TwoHandWeapon"), var4, var5, var6, var7);
      }

      if (!StringUtils.isNullOrEmpty(this.getFireMode())) {
         var3 = var2.addItem();
         var3.setLabel(Translator.getText("Tooltip_item_FireMode") + ":", var4, var5, var6, var7);
         var3.setValue(Translator.getText("ContextMenu_FireMode_" + this.getFireMode()), 1.0F, 1.0F, 1.0F, 1.0F);
      }

      if (this.CantAttackWithLowestEndurance) {
         var3 = var2.addItem();
         var3.setLabel(
            Translator.getText("Tooltip_weapon_Unusable_at_max_exertion"),
            Core.getInstance().getBadHighlitedColor().getR(),
            Core.getInstance().getBadHighlitedColor().getG(),
            Core.getInstance().getBadHighlitedColor().getB(),
            1.0F
         );
      }

    std::string var37 = this.getAmmoType();
      if (Core.getInstance().isNewReloading()) {
         if (this.getMaxAmmo() > 0) {
    std::string var39 = std::string.valueOf(this.getCurrentAmmoCount());
            if (this.isRoundChambered()) {
               var39 = var39 + "+1";
            }

            var3 = var2.addItem();
            if (this.bulletName == nullptr) {
               if (this.getMagazineType() != nullptr) {
                  this.bulletName = InventoryItemFactory.CreateItem(this.getMagazineType()).getDisplayName();
               } else {
                  this.bulletName = InventoryItemFactory.CreateItem(this.getAmmoType()).getDisplayName();
               }
            }

            var3.setLabel(this.bulletName + ":", 1.0F, 1.0F, 0.8F, 1.0F);
            var3.setValue(var39 + " / " + this.getMaxAmmo(), 1.0F, 1.0F, 1.0F, 1.0F);
         }

         if (this.isJammed()) {
            var3 = var2.addItem();
            var3.setLabel(
               Translator.getText("Tooltip_weapon_Jammed"),
               Core.getInstance().getBadHighlitedColor().getR(),
               Core.getInstance().getBadHighlitedColor().getG(),
               Core.getInstance().getBadHighlitedColor().getB(),
               1.0F
            );
         } else if (this.haveChamber() && !this.isRoundChambered() && this.getCurrentAmmoCount() > 0) {
            var3 = var2.addItem();
    std::string var40 = this.isSpentRoundChambered() ? "Tooltip_weapon_SpentRoundChambered" : "Tooltip_weapon_NoRoundChambered";
            var3.setLabel(
               Translator.getText(var40),
               Core.getInstance().getBadHighlitedColor().getR(),
               Core.getInstance().getBadHighlitedColor().getG(),
               Core.getInstance().getBadHighlitedColor().getB(),
               1.0F
            );
         } else if (this.getSpentRoundCount() > 0) {
            var3 = var2.addItem();
            var3.setLabel(
               Translator.getText("Tooltip_weapon_SpentRounds") + ":",
               Core.getInstance().getBadHighlitedColor().getR(),
               Core.getInstance().getBadHighlitedColor().getG(),
               Core.getInstance().getBadHighlitedColor().getB(),
               1.0F
            );
            var3.setValue(this.getSpentRoundCount() + " / " + this.getMaxAmmo(), 1.0F, 1.0F, 1.0F, 1.0F);
         }

         if (!StringUtils.isNullOrEmpty(this.getMagazineType())) {
            if (this.isContainsClip()) {
               var3 = var2.addItem();
               var3.setLabel(Translator.getText("Tooltip_weapon_ContainsClip"), 1.0F, 1.0F, 0.8F, 1.0F);
            } else {
               var3 = var2.addItem();
               var3.setLabel(Translator.getText("Tooltip_weapon_NoClip"), 1.0F, 1.0F, 0.8F, 1.0F);
            }
         }
      } else {
         if (var37 == nullptr && this.hasModData()) {
    void* var41 = this.getModData().rawget("defaultAmmo");
            if (dynamic_cast<std*>(var41) != nullptr::string) {
               var37 = (std::string)var41;
            }
         }

         if (var37 != nullptr) {
    Item var42 = ScriptManager.instance.FindItem(var37);
            if (var42 == nullptr) {
               var42 = ScriptManager.instance.FindItem(this.getModule() + "." + var37);
            }

            if (var42 != nullptr) {
               var3 = var2.addItem();
               var3.setLabel(Translator.getText("Tooltip_weapon_Ammo") + ":", var4, var5, var6, var7);
               var3.setValue(var42.getDisplayName(), 1.0F, 1.0F, 1.0F, 1.0F);
            }

    void* var45 = this.getModData().rawget("currentCapacity");
    void* var12 = this.getModData().rawget("maxCapacity");
            if (dynamic_cast<double*>(var45) != nullptr && dynamic_cast<double*>(var12) != nullptr) {
    std::string var13 = ((double)var45).intValue() + " / " + ((double)var12).intValue();
    void* var14 = this.getModData().rawget("roundChambered");
               if (dynamic_cast<double*>(var14) != nullptr && ((double)var14).intValue() == 1) {
                  var13 = ((double)var45).intValue() + "+1 / " + ((double)var12).intValue();
               } else {
    void* var15 = this.getModData().rawget("emptyShellChambered");
                  if (dynamic_cast<double*>(var15) != nullptr && ((double)var15).intValue() == 1) {
                     var13 = ((double)var45).intValue() + "+x / " + ((double)var12).intValue();
                  }
               }

               var3 = var2.addItem();
               var3.setLabel(Translator.getText("Tooltip_weapon_AmmoCount") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
               var3.setValue(var13, 1.0F, 1.0F, 1.0F, 1.0F);
            }
         }
      }

    Layout var43 = var1.beginLayout();
      if (this.getStock() != nullptr) {
         var3 = var43.addItem();
         var3.setLabel(Translator.getText("Tooltip_weapon_Stock") + ":", var4, var5, var6, var7);
         var3.setValue(this.getStock().getName(), 1.0F, 1.0F, 1.0F, 1.0F);
      }

      if (this.getSling() != nullptr) {
         var3 = var43.addItem();
         var3.setLabel(Translator.getText("Tooltip_weapon_Sling") + ":", var4, var5, var6, var7);
         var3.setValue(this.getSling().getName(), 1.0F, 1.0F, 1.0F, 1.0F);
      }

      if (this.getScope() != nullptr) {
         var3 = var43.addItem();
         var3.setLabel(Translator.getText("Tooltip_weapon_Scope") + ":", var4, var5, var6, var7);
         var3.setValue(this.getScope().getName(), 1.0F, 1.0F, 1.0F, 1.0F);
      }

      if (this.getCanon() != nullptr) {
         var3 = var43.addItem();
         var3.setLabel(Translator.getText("Tooltip_weapon_Canon") + ":", var4, var5, var6, var7);
         var3.setValue(this.getCanon().getName(), 1.0F, 1.0F, 1.0F, 1.0F);
      }

      if (this.getClip() != nullptr) {
         var3 = var43.addItem();
         var3.setLabel(Translator.getText("Tooltip_weapon_Clip") + ":", var4, var5, var6, var7);
         var3.setValue(this.getClip().getName(), 1.0F, 1.0F, 1.0F, 1.0F);
      }

      if (this.getRecoilpad() != nullptr) {
         var3 = var43.addItem();
         var3.setLabel(Translator.getText("Tooltip_weapon_RecoilPad") + ":", var4, var5, var6, var7);
         var3.setValue(this.getRecoilpad().getName(), 1.0F, 1.0F, 1.0F, 1.0F);
      }

      if (!var43.items.empty()) {
         var2.next = var43;
         var43.nextPadY = var1.getLineSpacing();
      } else {
         var1.endLayout(var43);
      }
   }

    float getDamageMod(IsoGameCharacter var1) {
    int var2 = var1.getPerkLevel(Perks.Blunt);
      if (this.ScriptItem.Categories.contains("Blunt")) {
         if (var2 >= 3 && var2 <= 6) {
            return 1.1F;
         }

         if (var2 >= 7) {
            return 1.2F;
         }
      }

    int var3 = var1.getPerkLevel(Perks.Axe);
      if (this.ScriptItem.Categories.contains("Axe")) {
         if (var3 >= 3 && var3 <= 6) {
            return 1.1F;
         }

         if (var3 >= 7) {
            return 1.2F;
         }
      }

    int var4 = var1.getPerkLevel(Perks.Spear);
      if (this.ScriptItem.Categories.contains("Spear")) {
         if (var4 >= 3 && var4 <= 6) {
            return 1.1F;
         }

         if (var4 >= 7) {
            return 1.2F;
         }
      }

      return 1.0F;
   }

    float getRangeMod(IsoGameCharacter var1) {
    int var2 = var1.getPerkLevel(Perks.Blunt);
      if (this.ScriptItem.Categories.contains("Blunt") && var2 >= 7) {
         return 1.2F;
      } else {
    int var3 = var1.getPerkLevel(Perks.Axe);
         if (this.ScriptItem.Categories.contains("Axe") && var3 >= 7) {
            return 1.2F;
         } else {
    int var4 = var1.getPerkLevel(Perks.Spear);
            return this.ScriptItem.Categories.contains("Spear") && var4 >= 7 ? 1.2F : 1.0F;
         }
      }
   }

    float getFatigueMod(IsoGameCharacter var1) {
    int var2 = var1.getPerkLevel(Perks.Blunt);
      if (this.ScriptItem.Categories.contains("Blunt") && var2 >= 8) {
         return 0.8F;
      } else {
    int var3 = var1.getPerkLevel(Perks.Axe);
         if (this.ScriptItem.Categories.contains("Axe") && var3 >= 8) {
            return 0.8F;
         } else {
    int var4 = var1.getPerkLevel(Perks.Spear);
            return this.ScriptItem.Categories.contains("Spear") && var4 >= 8 ? 0.8F : 1.0F;
         }
      }
   }

    float getKnockbackMod(IsoGameCharacter var1) {
    int var2 = var1.getPerkLevel(Perks.Axe);
      return this.ScriptItem.Categories.contains("Axe") && var2 >= 6 ? 2.0F : 1.0F;
   }

    float getSpeedMod(IsoGameCharacter var1) {
      if (this.ScriptItem.Categories.contains("Blunt")) {
    int var2 = var1.getPerkLevel(Perks.Blunt);
         if (var2 >= 10) {
            return 0.65F;
         }

         if (var2 >= 9) {
            return 0.68F;
         }

         if (var2 >= 8) {
            return 0.71F;
         }

         if (var2 >= 7) {
            return 0.74F;
         }

         if (var2 >= 6) {
            return 0.77F;
         }

         if (var2 >= 5) {
            return 0.8F;
         }

         if (var2 >= 4) {
            return 0.83F;
         }

         if (var2 >= 3) {
            return 0.86F;
         }

         if (var2 >= 2) {
            return 0.9F;
         }

         if (var2 >= 1) {
            return 0.95F;
         }
      }

      if (this.ScriptItem.Categories.contains("Axe")) {
    int var5 = var1.getPerkLevel(Perks.Axe);
    float var3 = 1.0F;
         if (var1.Traits.Axeman.isSet()) {
            var3 = 0.95F;
         }

         if (var5 >= 10) {
            return 0.65F * var3;
         } else if (var5 >= 9) {
            return 0.68F * var3;
         } else if (var5 >= 8) {
            return 0.71F * var3;
         } else if (var5 >= 7) {
            return 0.74F * var3;
         } else if (var5 >= 6) {
            return 0.77F * var3;
         } else if (var5 >= 5) {
            return 0.8F * var3;
         } else if (var5 >= 4) {
            return 0.83F * var3;
         } else if (var5 >= 3) {
            return 0.86F * var3;
         } else if (var5 >= 2) {
            return 0.9F * var3;
         } else {
            return var5 >= 1 ? 0.95F * var3 : 1.0F * var3;
         }
      } else {
         if (this.ScriptItem.Categories.contains("Spear")) {
    int var4 = var1.getPerkLevel(Perks.Spear);
            if (var4 >= 10) {
               return 0.65F;
            }

            if (var4 >= 9) {
               return 0.68F;
            }

            if (var4 >= 8) {
               return 0.71F;
            }

            if (var4 >= 7) {
               return 0.74F;
            }

            if (var4 >= 6) {
               return 0.77F;
            }

            if (var4 >= 5) {
               return 0.8F;
            }

            if (var4 >= 4) {
               return 0.83F;
            }

            if (var4 >= 3) {
               return 0.86F;
            }

            if (var4 >= 2) {
               return 0.9F;
            }

            if (var4 >= 1) {
               return 0.95F;
            }
         }

         return 1.0F;
      }
   }

    float getToHitMod(IsoGameCharacter var1) {
    int var2 = var1.getPerkLevel(Perks.Blunt);
      if (this.ScriptItem.Categories.contains("Blunt")) {
         if (var2 == 1) {
            return 1.2F;
         }

         if (var2 == 2) {
            return 1.3F;
         }

         if (var2 == 3) {
            return 1.4F;
         }

         if (var2 == 4) {
            return 1.5F;
         }

         if (var2 == 5) {
            return 1.6F;
         }

         if (var2 == 6) {
            return 1.7F;
         }

         if (var2 == 7) {
            return 1.8F;
         }

         if (var2 == 8) {
            return 1.9F;
         }

         if (var2 == 9) {
            return 2.0F;
         }

         if (var2 == 10) {
            return 100.0F;
         }
      }

    int var3 = var1.getPerkLevel(Perks.Axe);
      if (this.ScriptItem.Categories.contains("Axe")) {
         if (var3 == 1) {
            return 1.2F;
         }

         if (var3 == 2) {
            return 1.3F;
         }

         if (var3 == 3) {
            return 1.4F;
         }

         if (var3 == 4) {
            return 1.5F;
         }

         if (var3 == 5) {
            return 1.6F;
         }

         if (var3 == 6) {
            return 1.7F;
         }

         if (var3 == 7) {
            return 1.8F;
         }

         if (var3 == 8) {
            return 1.9F;
         }

         if (var3 == 9) {
            return 2.0F;
         }

         if (var3 == 10) {
            return 100.0F;
         }
      }

    int var4 = var1.getPerkLevel(Perks.Spear);
      if (this.ScriptItem.Categories.contains("Spear")) {
         if (var4 == 1) {
            return 1.2F;
         }

         if (var4 == 2) {
            return 1.3F;
         }

         if (var4 == 3) {
            return 1.4F;
         }

         if (var4 == 4) {
            return 1.5F;
         }

         if (var4 == 5) {
            return 1.6F;
         }

         if (var4 == 6) {
            return 1.7F;
         }

         if (var4 == 7) {
            return 1.8F;
         }

         if (var4 == 8) {
            return 1.9F;
         }

         if (var4 == 9) {
            return 2.0F;
         }

         if (var4 == 10) {
            return 100.0F;
         }
      }

      return 1.0F;
   }

    bool isAngleFalloff() {
      return this.angleFalloff;
   }

    void setAngleFalloff(bool var1) {
      this.angleFalloff = var1;
   }

    bool isCanBarracade() {
      return this.bCanBarracade;
   }

    void setCanBarracade(bool var1) {
      this.bCanBarracade = var1;
   }

    float getDoSwingBeforeImpact() {
      return this.doSwingBeforeImpact;
   }

    void setDoSwingBeforeImpact(float var1) {
      this.doSwingBeforeImpact = var1;
   }

    std::string getImpactSound() {
      return this.impactSound;
   }

    void setImpactSound(const std::string& var1) {
      this.impactSound = var1;
   }

    bool isKnockBackOnNoDeath() {
      return this.knockBackOnNoDeath;
   }

    void setKnockBackOnNoDeath(bool var1) {
      this.knockBackOnNoDeath = var1;
   }

    float getMaxAngle() {
      return this.maxAngle;
   }

    void setMaxAngle(float var1) {
      this.maxAngle = var1;
   }

    float getMaxDamage() {
      return this.maxDamage;
   }

    void setMaxDamage(float var1) {
      this.maxDamage = var1;
   }

    int getMaxHitCount() {
      return this.maxHitCount;
   }

    void setMaxHitCount(int var1) {
      this.maxHitCount = var1;
   }

    float getMaxRange() {
      return this.maxRange;
   }

    float getMaxRange(IsoGameCharacter var1) {
      return this.isRanged() ? this.maxRange + this.getAimingPerkRangeModifier() * (var1.getPerkLevel(Perks.Aiming) / 2.0F) : this.maxRange;
   }

    void setMaxRange(float var1) {
      this.maxRange = var1;
   }

    bool isRanged() {
      return this.ranged;
   }

    void setRanged(bool var1) {
      this.ranged = var1;
   }

    float getMinAngle() {
      return this.minAngle;
   }

    void setMinAngle(float var1) {
      this.minAngle = var1;
   }

    float getMinDamage() {
      return this.minDamage;
   }

    void setMinDamage(float var1) {
      this.minDamage = var1;
   }

    float getMinimumSwingTime() {
      return this.minimumSwingTime;
   }

    void setMinimumSwingTime(float var1) {
      this.minimumSwingTime = var1;
   }

    float getMinRange() {
      return this.minRange;
   }

    void setMinRange(float var1) {
      this.minRange = var1;
   }

    float getNoiseFactor() {
      return this.noiseFactor;
   }

    void setNoiseFactor(float var1) {
      this.noiseFactor = var1;
   }

    std::string getOtherHandRequire() {
      return this.otherHandRequire;
   }

    void setOtherHandRequire(const std::string& var1) {
      this.otherHandRequire = var1;
   }

    bool isOtherHandUse() {
      return this.otherHandUse;
   }

    void setOtherHandUse(bool var1) {
      this.otherHandUse = var1;
   }

    std::string getPhysicsObject() {
      return this.physicsObject;
   }

    void setPhysicsObject(const std::string& var1) {
      this.physicsObject = var1;
   }

    float getPushBackMod() {
      return this.pushBackMod;
   }

    void setPushBackMod(float var1) {
      this.pushBackMod = var1;
   }

    bool isRangeFalloff() {
      return this.rangeFalloff;
   }

    void setRangeFalloff(bool var1) {
      this.rangeFalloff = var1;
   }

    bool isShareDamage() {
      return this.shareDamage;
   }

    void setShareDamage(bool var1) {
      this.shareDamage = var1;
   }

    int getSoundRadius() {
      return this.soundRadius;
   }

    void setSoundRadius(int var1) {
      this.soundRadius = var1;
   }

    int getSoundVolume() {
      return this.soundVolume;
   }

    void setSoundVolume(int var1) {
      this.soundVolume = var1;
   }

    bool isSplatBloodOnNoDeath() {
      return this.splatBloodOnNoDeath;
   }

    void setSplatBloodOnNoDeath(bool var1) {
      this.splatBloodOnNoDeath = var1;
   }

    int getSplatNumber() {
      return this.splatNumber;
   }

    void setSplatNumber(int var1) {
      this.splatNumber = var1;
   }

    std::string getSwingSound() {
      return this.swingSound;
   }

    void setSwingSound(const std::string& var1) {
      this.swingSound = var1;
   }

    float getSwingTime() {
      return this.swingTime;
   }

    void setSwingTime(float var1) {
      this.swingTime = var1;
   }

    float getToHitModifier() {
      return this.toHitModifier;
   }

    void setToHitModifier(float var1) {
      this.toHitModifier = var1;
   }

    bool isUseEndurance() {
      return this.useEndurance;
   }

    void setUseEndurance(bool var1) {
      this.useEndurance = var1;
   }

    bool isUseSelf() {
      return this.useSelf;
   }

    void setUseSelf(bool var1) {
      this.useSelf = var1;
   }

    std::string getWeaponSprite() {
      return this.weaponSprite;
   }

    void setWeaponSprite(const std::string& var1) {
      this.weaponSprite = var1;
   }

    float getOtherBoost() {
      return this.otherBoost;
   }

    void setOtherBoost(float var1) {
      this.otherBoost = var1;
   }

    int getDoorDamage() {
      return this.DoorDamage;
   }

    void setDoorDamage(int var1) {
      this.DoorDamage = var1;
   }

    std::string getDoorHitSound() {
      return this.doorHitSound;
   }

    void setDoorHitSound(const std::string& var1) {
      this.doorHitSound = var1;
   }

    int getConditionLowerChance() {
      return this.ConditionLowerChance;
   }

    void setConditionLowerChance(int var1) {
      this.ConditionLowerChance = var1;
   }

    bool isMultipleHitConditionAffected() {
      return this.MultipleHitConditionAffected;
   }

    void setMultipleHitConditionAffected(bool var1) {
      this.MultipleHitConditionAffected = var1;
   }

    bool isShareEndurance() {
      return this.shareEndurance;
   }

    void setShareEndurance(bool var1) {
      this.shareEndurance = var1;
   }

    bool isAlwaysKnockdown() {
      return this.AlwaysKnockdown;
   }

    void setAlwaysKnockdown(bool var1) {
      this.AlwaysKnockdown = var1;
   }

    float getEnduranceMod() {
      return this.EnduranceMod;
   }

    void setEnduranceMod(float var1) {
      this.EnduranceMod = var1;
   }

    float getKnockdownMod() {
      return this.KnockdownMod;
   }

    void setKnockdownMod(float var1) {
      this.KnockdownMod = var1;
   }

    bool isCantAttackWithLowestEndurance() {
      return this.CantAttackWithLowestEndurance;
   }

    void setCantAttackWithLowestEndurance(bool var1) {
      this.CantAttackWithLowestEndurance = var1;
   }

    bool isAimedFirearm() {
      return this.bIsAimedFirearm;
   }

    bool isAimedHandWeapon() {
      return this.bIsAimedHandWeapon;
   }

    int getProjectileCount() {
      return this.ProjectileCount;
   }

    void setProjectileCount(int var1) {
      this.ProjectileCount = var1;
   }

    float getAimingMod() {
      return this.aimingMod;
   }

    bool isAimed() {
      return this.bIsAimedFirearm || this.bIsAimedHandWeapon;
   }

    void setCriticalChance(float var1) {
      this.CriticalChance = var1;
   }

    float getCriticalChance() {
      return this.CriticalChance;
   }

    void setSubCategory(const std::string& var1) {
      this.SubCategory = var1;
   }

    std::string getSubCategory() {
      return this.SubCategory;
   }

    void setZombieHitSound(const std::string& var1) {
      this.hitSound = var1;
   }

    std::string getZombieHitSound() {
      return this.hitSound;
   }

   public std::vector<std::string> getCategories() {
      return this.Categories;
   }

    void setCategories(std::vector<std::string> var1) {
      this.Categories = var1;
   }

    int getAimingPerkCritModifier() {
      return this.AimingPerkCritModifier;
   }

    void setAimingPerkCritModifier(int var1) {
      this.AimingPerkCritModifier = var1;
   }

    float getAimingPerkRangeModifier() {
      return this.AimingPerkRangeModifier;
   }

    void setAimingPerkRangeModifier(float var1) {
      this.AimingPerkRangeModifier = var1;
   }

    int getHitChance() {
      return this.HitChance;
   }

    void setHitChance(int var1) {
      this.HitChance = var1;
   }

    float getAimingPerkHitChanceModifier() {
      return this.AimingPerkHitChanceModifier;
   }

    void setAimingPerkHitChanceModifier(float var1) {
      this.AimingPerkHitChanceModifier = var1;
   }

    float getAimingPerkMinAngleModifier() {
      return this.AimingPerkMinAngleModifier;
   }

    void setAimingPerkMinAngleModifier(float var1) {
      this.AimingPerkMinAngleModifier = var1;
   }

    int getRecoilDelay() {
      return this.RecoilDelay;
   }

    void setRecoilDelay(int var1) {
      this.RecoilDelay = var1;
   }

    bool isPiercingBullets() {
      return this.PiercingBullets;
   }

    void setPiercingBullets(bool var1) {
      this.PiercingBullets = var1;
   }

    float getSoundGain() {
      return this.soundGain;
   }

    void setSoundGain(float var1) {
      this.soundGain = var1;
   }

    WeaponPart getScope() {
      return this.scope;
   }

    void setScope(WeaponPart var1) {
      this.scope = var1;
   }

    WeaponPart getClip() {
      return this.clip;
   }

    void setClip(WeaponPart var1) {
      this.clip = var1;
   }

    WeaponPart getCanon() {
      return this.canon;
   }

    void setCanon(WeaponPart var1) {
      this.canon = var1;
   }

    WeaponPart getRecoilpad() {
      return this.recoilpad;
   }

    void setRecoilpad(WeaponPart var1) {
      this.recoilpad = var1;
   }

    int getClipSize() {
      return this.ClipSize;
   }

    void setClipSize(int var1) {
      this.ClipSize = var1;
      this.getModData().rawset("maxCapacity", BoxedStaticValues.toDouble(var1));
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
    BitHeaderWrite var3 = BitHeader.allocWrite(HeaderSize.int, var1);
      if (this.maxRange != 1.0F) {
         var3.addFlags(1);
         var1.putFloat(this.maxRange);
      }

      if (this.minRangeRanged != 0.0F) {
         var3.addFlags(2);
         var1.putFloat(this.minRangeRanged);
      }

      if (this.ClipSize != 0) {
         var3.addFlags(4);
         var1.putInt(this.ClipSize);
      }

      if (this.minDamage != 0.4F) {
         var3.addFlags(8);
         var1.putFloat(this.minDamage);
      }

      if (this.maxDamage != 1.5F) {
         var3.addFlags(16);
         var1.putFloat(this.maxDamage);
      }

      if (this.RecoilDelay != 0) {
         var3.addFlags(32);
         var1.putInt(this.RecoilDelay);
      }

      if (this.aimingTime != 0) {
         var3.addFlags(64);
         var1.putInt(this.aimingTime);
      }

      if (this.reloadTime != 0) {
         var3.addFlags(128);
         var1.putInt(this.reloadTime);
      }

      if (this.HitChance != 0) {
         var3.addFlags(256);
         var1.putInt(this.HitChance);
      }

      if (this.minAngle != 0.5F) {
         var3.addFlags(512);
         var1.putFloat(this.minAngle);
      }

      if (this.getScope() != nullptr) {
         var3.addFlags(1024);
         var1.putShort(this.getScope().getRegistry_id());
      }

      if (this.getClip() != nullptr) {
         var3.addFlags(2048);
         var1.putShort(this.getClip().getRegistry_id());
      }

      if (this.getRecoilpad() != nullptr) {
         var3.addFlags(4096);
         var1.putShort(this.getRecoilpad().getRegistry_id());
      }

      if (this.getSling() != nullptr) {
         var3.addFlags(8192);
         var1.putShort(this.getSling().getRegistry_id());
      }

      if (this.getStock() != nullptr) {
         var3.addFlags(16384);
         var1.putShort(this.getStock().getRegistry_id());
      }

      if (this.getCanon() != nullptr) {
         var3.addFlags(32768);
         var1.putShort(this.getCanon().getRegistry_id());
      }

      if (this.getExplosionTimer() != 0) {
         var3.addFlags(65536);
         var1.putInt(this.getExplosionTimer());
      }

      if (this.maxAngle != 1.0F) {
         var3.addFlags(131072);
         var1.putFloat(this.maxAngle);
      }

      if (this.bloodLevel != 0.0F) {
         var3.addFlags(262144);
         var1.putFloat(this.bloodLevel);
      }

      if (this.containsClip) {
         var3.addFlags(524288);
      }

      if (this.roundChambered) {
         var3.addFlags(1048576);
      }

      if (this.isJammed) {
         var3.addFlags(2097152);
      }

      if (!StringUtils == this.weaponSprite, this.getScriptItem().getWeaponSprite())) {
         var3.addFlags(4194304);
         GameWindow.WriteString(var1, this.weaponSprite);
      }

      var3.write();
      var3.release();
   }

    void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
      this.maxRange = 1.0F;
      this.minRangeRanged = 0.0F;
      this.ClipSize = 0;
      this.minDamage = 0.4F;
      this.maxDamage = 1.5F;
      this.RecoilDelay = 0;
      this.aimingTime = 0;
      this.reloadTime = 0;
      this.HitChance = 0;
      this.minAngle = 0.5F;
      this.scope = nullptr;
      this.clip = nullptr;
      this.recoilpad = nullptr;
      this.sling = nullptr;
      this.stock = nullptr;
      this.canon = nullptr;
      this.explosionTimer = 0;
      this.maxAngle = 1.0F;
      this.bloodLevel = 0.0F;
      this.containsClip = false;
      this.roundChambered = false;
      this.isJammed = false;
      this.weaponSprite = this.getScriptItem().getWeaponSprite();
    BitHeaderRead var3 = BitHeader.allocRead(HeaderSize.int, var1);
      if (!var3 == 0)) {
         if (var3.hasFlags(1)) {
            this.setMaxRange(var1.getFloat());
         }

         if (var3.hasFlags(2)) {
            this.setMinRangeRanged(var1.getFloat());
         }

         if (var3.hasFlags(4)) {
            this.setClipSize(var1.getInt());
         }

         if (var3.hasFlags(8)) {
            this.setMinDamage(var1.getFloat());
         }

         if (var3.hasFlags(16)) {
            this.setMaxDamage(var1.getFloat());
         }

         if (var3.hasFlags(32)) {
            this.setRecoilDelay(var1.getInt());
         }

         if (var3.hasFlags(64)) {
            this.setAimingTime(var1.getInt());
         }

         if (var3.hasFlags(128)) {
            this.setReloadTime(var1.getInt());
         }

         if (var3.hasFlags(256)) {
            this.setHitChance(var1.getInt());
         }

         if (var3.hasFlags(512)) {
            this.setMinAngle(var1.getFloat());
         }

         if (var3.hasFlags(1024)) {
    InventoryItem var4 = InventoryItemFactory.CreateItem(var1.getShort());
            if (var4 != nullptr && dynamic_cast<WeaponPart*>(var4) != nullptr) {
               this.attachWeaponPart((WeaponPart)var4, false);
            }
         }

         if (var3.hasFlags(2048)) {
    InventoryItem var5 = InventoryItemFactory.CreateItem(var1.getShort());
            if (var5 != nullptr && dynamic_cast<WeaponPart*>(var5) != nullptr) {
               this.attachWeaponPart((WeaponPart)var5, false);
            }
         }

         if (var3.hasFlags(4096)) {
    InventoryItem var6 = InventoryItemFactory.CreateItem(var1.getShort());
            if (var6 != nullptr && dynamic_cast<WeaponPart*>(var6) != nullptr) {
               this.attachWeaponPart((WeaponPart)var6, false);
            }
         }

         if (var3.hasFlags(8192)) {
    InventoryItem var7 = InventoryItemFactory.CreateItem(var1.getShort());
            if (var7 != nullptr && dynamic_cast<WeaponPart*>(var7) != nullptr) {
               this.attachWeaponPart((WeaponPart)var7, false);
            }
         }

         if (var3.hasFlags(16384)) {
    InventoryItem var8 = InventoryItemFactory.CreateItem(var1.getShort());
            if (var8 != nullptr && dynamic_cast<WeaponPart*>(var8) != nullptr) {
               this.attachWeaponPart((WeaponPart)var8, false);
            }
         }

         if (var3.hasFlags(32768)) {
    InventoryItem var9 = InventoryItemFactory.CreateItem(var1.getShort());
            if (var9 != nullptr && dynamic_cast<WeaponPart*>(var9) != nullptr) {
               this.attachWeaponPart((WeaponPart)var9, false);
            }
         }

         if (var3.hasFlags(65536)) {
            this.setExplosionTimer(var1.getInt());
         }

         if (var3.hasFlags(131072)) {
            this.setMaxAngle(var1.getFloat());
         }

         if (var3.hasFlags(262144)) {
            this.setBloodLevel(var1.getFloat());
         }

         this.setContainsClip(var3.hasFlags(524288));
         if (StringUtils.isNullOrWhitespace(this.magazineType)) {
            this.setContainsClip(false);
         }

         this.setRoundChambered(var3.hasFlags(1048576));
         this.setJammed(var3.hasFlags(2097152));
         if (var3.hasFlags(4194304)) {
            this.setWeaponSprite(GameWindow.ReadStringUTF(var1));
         }
      }

      var3.release();
   }

    float getMinRangeRanged() {
      return this.minRangeRanged;
   }

    void setMinRangeRanged(float var1) {
      this.minRangeRanged = var1;
   }

    int getReloadTime() {
      return this.reloadTime;
   }

    void setReloadTime(int var1) {
      this.reloadTime = var1;
   }

    WeaponPart getSling() {
      return this.sling;
   }

    void setSling(WeaponPart var1) {
      this.sling = var1;
   }

    int getAimingTime() {
      return this.aimingTime;
   }

    void setAimingTime(int var1) {
      this.aimingTime = var1;
   }

    WeaponPart getStock() {
      return this.stock;
   }

    void setStock(WeaponPart var1) {
      this.stock = var1;
   }

    int getTreeDamage() {
      return this.treeDamage;
   }

    void setTreeDamage(int var1) {
      this.treeDamage = var1;
   }

    std::string getBulletOutSound() {
      return this.bulletOutSound;
   }

    void setBulletOutSound(const std::string& var1) {
      this.bulletOutSound = var1;
   }

    std::string getShellFallSound() {
      return this.shellFallSound;
   }

    void setShellFallSound(const std::string& var1) {
      this.shellFallSound = var1;
   }

    void addPartToList(const std::string& var1, std::vector<WeaponPart> var2) {
    WeaponPart var3 = this.getWeaponPart(var1);
      if (var3 != nullptr) {
         var2.push_back(var3);
      }
   }

   public std::vector<WeaponPart> getAllWeaponParts() {
      return this.getAllWeaponParts(std::make_unique<std::vector<>>());
   }

   public std::vector<WeaponPart> getAllWeaponParts(std::vector<WeaponPart> var1) {
      var1.clear();
      this.addPartToList("Scope", var1);
      this.addPartToList("Clip", var1);
      this.addPartToList("Sling", var1);
      this.addPartToList("Canon", var1);
      this.addPartToList("Stock", var1);
      this.addPartToList("RecoilPad", var1);
    return var1;
   }

    void setWeaponPart(const std::string& var1, WeaponPart var2) {
      if (var2 == nullptr || var1.equalsIgnoreCase(var2.getPartType())) {
         if ("Scope".equalsIgnoreCase(var1)) {
            this.scope = var2;
         } else if ("Clip".equalsIgnoreCase(var1)) {
            this.clip = var2;
         } else if ("Sling".equalsIgnoreCase(var1)) {
            this.sling = var2;
         } else if ("Canon".equalsIgnoreCase(var1)) {
            this.canon = var2;
         } else if ("Stock".equalsIgnoreCase(var1)) {
            this.stock = var2;
         } else if ("RecoilPad".equalsIgnoreCase(var1)) {
            this.recoilpad = var2;
         } else {
            DebugLog.log("ERROR: unknown WeaponPart type \"" + var1 + "\"");
         }
      }
   }

    WeaponPart getWeaponPart(const std::string& var1) {
      if ("Scope".equalsIgnoreCase(var1)) {
         return this.scope;
      } else if ("Clip".equalsIgnoreCase(var1)) {
         return this.clip;
      } else if ("Sling".equalsIgnoreCase(var1)) {
         return this.sling;
      } else if ("Canon".equalsIgnoreCase(var1)) {
         return this.canon;
      } else if ("Stock".equalsIgnoreCase(var1)) {
         return this.stock;
      } else if ("RecoilPad".equalsIgnoreCase(var1)) {
         return this.recoilpad;
      } else {
         DebugLog.log("ERROR: unknown WeaponPart type \"" + var1 + "\"");
    return nullptr;
      }
   }

    float getWeaponPartWeightModifier(const std::string& var1) {
      return this.getWeaponPartWeightModifier(this.getWeaponPart(var1));
   }

    float getWeaponPartWeightModifier(WeaponPart var1) {
    return var1 = = nullptr ? 0.0F : var1.getWeightModifier();
   }

    void attachWeaponPart(WeaponPart var1) {
      this.attachWeaponPart(var1, true);
   }

    void attachWeaponPart(WeaponPart var1, bool var2) {
      if (var1 != nullptr) {
    WeaponPart var3 = this.getWeaponPart(var1.getPartType());
         if (var3 != nullptr) {
            this.detachWeaponPart(var3);
         }

         this.setWeaponPart(var1.getPartType(), var1);
         if (var2) {
            this.setMaxRange(this.getMaxRange() + var1.getMaxRange());
            this.setMinRangeRanged(this.getMinRangeRanged() + var1.getMinRangeRanged());
            this.setClipSize(this.getClipSize() + var1.getClipSize());
            this.setReloadTime(this.getReloadTime() + var1.getReloadTime());
            this.setRecoilDelay((int)(this.getRecoilDelay() + var1.getRecoilDelay()));
            this.setAimingTime(this.getAimingTime() + var1.getAimingTime());
            this.setHitChance(this.getHitChance() + var1.getHitChance());
            this.setMinAngle(this.getMinAngle() + var1.getAngle());
            this.setMinDamage(this.getMinDamage() + var1.getDamage());
            this.setMaxDamage(this.getMaxDamage() + var1.getDamage());
         }
      }
   }

    void detachWeaponPart(WeaponPart var1) {
      if (var1 != nullptr) {
    WeaponPart var2 = this.getWeaponPart(var1.getPartType());
         if (var2 == var1) {
            this.setWeaponPart(var1.getPartType(), nullptr);
            this.setMaxRange(this.getMaxRange() - var1.getMaxRange());
            this.setMinRangeRanged(this.getMinRangeRanged() - var1.getMinRangeRanged());
            this.setClipSize(this.getClipSize() - var1.getClipSize());
            this.setReloadTime(this.getReloadTime() - var1.getReloadTime());
            this.setRecoilDelay((int)(this.getRecoilDelay() - var1.getRecoilDelay()));
            this.setAimingTime(this.getAimingTime() - var1.getAimingTime());
            this.setHitChance(this.getHitChance() - var1.getHitChance());
            this.setMinAngle(this.getMinAngle() - var1.getAngle());
            this.setMinDamage(this.getMinDamage() - var1.getDamage());
            this.setMaxDamage(this.getMaxDamage() - var1.getDamage());
         }
      }
   }

    int getTriggerExplosionTimer() {
      return this.triggerExplosionTimer;
   }

    void setTriggerExplosionTimer(int var1) {
      this.triggerExplosionTimer = var1;
   }

    bool canBePlaced() {
      return this.canBePlaced;
   }

    void setCanBePlaced(bool var1) {
      this.canBePlaced = var1;
   }

    int getExplosionRange() {
      return this.explosionRange;
   }

    void setExplosionRange(int var1) {
      this.explosionRange = var1;
   }

    int getExplosionPower() {
      return this.explosionPower;
   }

    void setExplosionPower(int var1) {
      this.explosionPower = var1;
   }

    int getFireRange() {
      return this.fireRange;
   }

    void setFireRange(int var1) {
      this.fireRange = var1;
   }

    int getSmokeRange() {
      return this.smokeRange;
   }

    void setSmokeRange(int var1) {
      this.smokeRange = var1;
   }

    int getFirePower() {
      return this.firePower;
   }

    void setFirePower(int var1) {
      this.firePower = var1;
   }

    int getNoiseRange() {
      return this.noiseRange;
   }

    void setNoiseRange(int var1) {
      this.noiseRange = var1;
   }

    int getNoiseDuration() {
      return this.getScriptItem().getNoiseDuration();
   }

    float getExtraDamage() {
      return this.extraDamage;
   }

    void setExtraDamage(float var1) {
      this.extraDamage = var1;
   }

    int getExplosionTimer() {
      return this.explosionTimer;
   }

    void setExplosionTimer(int var1) {
      this.explosionTimer = var1;
   }

    std::string getPlacedSprite() {
      return this.placedSprite;
   }

    void setPlacedSprite(const std::string& var1) {
      this.placedSprite = var1;
   }

    bool canBeReused() {
      return this.canBeReused;
   }

    void setCanBeReused(bool var1) {
      this.canBeReused = var1;
   }

    int getSensorRange() {
      return this.sensorRange;
   }

    void setSensorRange(int var1) {
      this.sensorRange = var1;
   }

    std::string getRunAnim() {
      return this.RunAnim;
   }

    float getCritDmgMultiplier() {
      return this.critDmgMultiplier;
   }

    void setCritDmgMultiplier(float var1) {
      this.critDmgMultiplier = var1;
   }

    std::string getStaticModel() {
      return this.staticModel != nullptr ? this.staticModel : this.weaponSprite;
   }

    float getBaseSpeed() {
      return this.baseSpeed;
   }

    void setBaseSpeed(float var1) {
      this.baseSpeed = var1;
   }

    float getBloodLevel() {
      return this.bloodLevel;
   }

    void setBloodLevel(float var1) {
      this.bloodLevel = Math.max(0.0F, Math.min(1.0F, var1));
   }

    void setWeaponLength(float var1) {
      this.WeaponLength = var1;
   }

    std::string getAmmoBox() {
      return this.ammoBox;
   }

    void setAmmoBox(const std::string& var1) {
      this.ammoBox = var1;
   }

    std::string getMagazineType() {
      return this.magazineType;
   }

    void setMagazineType(const std::string& var1) {
      this.magazineType = var1;
   }

    std::string getEjectAmmoStartSound() {
      return this.getScriptItem().getEjectAmmoStartSound();
   }

    std::string getEjectAmmoSound() {
      return this.getScriptItem().getEjectAmmoSound();
   }

    std::string getEjectAmmoStopSound() {
      return this.getScriptItem().getEjectAmmoStopSound();
   }

    std::string getInsertAmmoStartSound() {
      return this.getScriptItem().getInsertAmmoStartSound();
   }

    std::string getInsertAmmoSound() {
      return this.getScriptItem().getInsertAmmoSound();
   }

    std::string getInsertAmmoStopSound() {
      return this.getScriptItem().getInsertAmmoStopSound();
   }

    std::string getRackSound() {
      return this.rackSound;
   }

    void setRackSound(const std::string& var1) {
      this.rackSound = var1;
   }

    bool isReloadable(IsoGameCharacter var1) {
      return this.isRanged();
   }

    bool isContainsClip() {
      return this.containsClip;
   }

    void setContainsClip(bool var1) {
      this.containsClip = var1;
   }

    InventoryItem getBestMagazine(IsoGameCharacter var1) {
      if (StringUtils.isNullOrEmpty(this.getMagazineType())) {
    return nullptr;
      } else {
         InventoryItem var2 = var1.getInventory()
            .getBestTypeRecurse(this.getMagazineType(), (var0, var1x) -> var0.getCurrentAmmoCount() - var1x.getCurrentAmmoCount());
         return var2 != nullptr && var2.getCurrentAmmoCount() != 0 ? var2 : nullptr;
      }
   }

    std::string getWeaponReloadType() {
      return this.weaponReloadType;
   }

    void setWeaponReloadType(const std::string& var1) {
      this.weaponReloadType = var1;
   }

    bool isRackAfterShoot() {
      return this.rackAfterShoot;
   }

    void setRackAfterShoot(bool var1) {
      this.rackAfterShoot = var1;
   }

    bool isRoundChambered() {
      return this.roundChambered;
   }

    void setRoundChambered(bool var1) {
      this.roundChambered = var1;
   }

    bool isSpentRoundChambered() {
      return this.bSpentRoundChambered;
   }

    void setSpentRoundChambered(bool var1) {
      this.bSpentRoundChambered = var1;
   }

    int getSpentRoundCount() {
      return this.spentRoundCount;
   }

    void setSpentRoundCount(int var1) {
      this.spentRoundCount = PZMath.clamp(var1, 0, this.getMaxAmmo());
   }

    bool isManuallyRemoveSpentRounds() {
      return this.getScriptItem().isManuallyRemoveSpentRounds();
   }

    int getAmmoPerShoot() {
      return this.ammoPerShoot;
   }

    void setAmmoPerShoot(int var1) {
      this.ammoPerShoot = var1;
   }

    float getJamGunChance() {
      return this.jamGunChance;
   }

    void setJamGunChance(float var1) {
      this.jamGunChance = var1;
   }

    bool isJammed() {
      return this.isJammed;
   }

    void setJammed(bool var1) {
      this.isJammed = var1;
   }

    std::string getClickSound() {
      return this.clickSound;
   }

    void setClickSound(const std::string& var1) {
      this.clickSound = var1;
   }

   public std::vector<ModelWeaponPart> getModelWeaponPart() {
      return this.modelWeaponPart;
   }

    void setModelWeaponPart(std::vector<ModelWeaponPart> var1) {
      this.modelWeaponPart = var1;
   }

    std::string getOriginalWeaponSprite() {
      return this.originalWeaponSprite;
   }

    void setOriginalWeaponSprite(const std::string& var1) {
      this.originalWeaponSprite = var1;
   }

    bool haveChamber() {
      return this.haveChamber;
   }

    void setHaveChamber(bool var1) {
      this.haveChamber = var1;
   }

    std::string getDamageCategory() {
      return this.damageCategory;
   }

    void setDamageCategory(const std::string& var1) {
      this.damageCategory = var1;
   }

    bool isDamageMakeHole() {
      return this.damageMakeHole;
   }

    void setDamageMakeHole(bool var1) {
      this.damageMakeHole = var1;
   }

    std::string getHitFloorSound() {
      return this.hitFloorSound;
   }

    void setHitFloorSound(const std::string& var1) {
      this.hitFloorSound = var1;
   }

    bool isInsertAllBulletsReload() {
      return this.insertAllBulletsReload;
   }

    void setInsertAllBulletsReload(bool var1) {
      this.insertAllBulletsReload = var1;
   }

    std::string getFireMode() {
      return this.fireMode;
   }

    void setFireMode(const std::string& var1) {
      this.fireMode = var1;
   }

   public std::vector<std::string> getFireModePossibilities() {
      return this.fireModePossibilities;
   }

    void setFireModePossibilities(std::vector<std::string> var1) {
      this.fireModePossibilities = var1;
   }

    void randomizeBullets() {
      if (this.isRanged() && !Rand.NextBool(4)) {
         this.setCurrentAmmoCount(Rand.Next(this.getMaxAmmo() - 2, this.getMaxAmmo()));
         if (!StringUtils.isNullOrEmpty(this.getMagazineType())) {
            this.setContainsClip(true);
         }

         if (this.haveChamber()) {
            this.setRoundChambered(true);
         }
      }
   }

    float getStopPower() {
      return this.getScriptItem().stopPower;
   }

    bool isInstantExplosion() {
      return this.explosionTimer <= 0 && this.sensorRange <= 0 && this.getRemoteControlID() == -1;
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
