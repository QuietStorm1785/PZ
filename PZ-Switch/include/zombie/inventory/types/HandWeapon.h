#pragma once
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/skills/PerkFactory.h"
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
#include "zombie/scripting/objects/ModelWeaponPart.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace inventory {
namespace types {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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
private
 ArrayList<String> Categories = nullptr;
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
private
 ArrayList<ModelWeaponPart> modelWeaponPart = nullptr;
 bool haveChamber = true;
 std::string bulletName = nullptr;
 std::string damageCategory = nullptr;
 bool damageMakeHole = false;
 std::string hitFloorSound = "BatOnFloor";
 bool insertAllBulletsReload = false;
 std::string fireMode = nullptr;
private
 ArrayList<String> fireModePossibilities = nullptr;
 int ProjectileCount = 1;
 float aimingMod = 1.0F;
 float CriticalChance = 20.0F;
 std::string hitSound = "BaseballBatHit";

 float getSplatSize() { return this->SplatSize; }

 bool CanStack(InventoryItem item) { return false; }

 std::string getCategory() {
 return this->mainCategory != nullptr ? this->mainCategory : "Weapon";
 }

public
 HandWeapon(const std::string &module, const std::string &name,
 const std::string &itemType, const std::string &texName) {
 super(module, name, itemType, texName);
 this->cat = ItemType.Weapon;
 }

public
 HandWeapon(const std::string &module, const std::string &name,
 const std::string &itemType, Item item) {
 super(module, name, itemType, item);
 this->cat = ItemType.Weapon;
 }

 bool IsWeapon() { return true; }

 int getSaveType() { return Item.Type.Weapon.ordinal(); }

 float getScore(SurvivorDesc desc) {
 float float0 = 0.0F;
 if (this->getAmmoType() != nullptr && !this->getAmmoType() == "none") && !this->container.contains(this->getAmmoType())) {
 float0 -= 100000.0F;
 }

 if (this->Condition == 0) {
 float0 -= 100000.0F;
 }

 float0 += this->maxDamage * 10.0F;
 float0 += this->maxAngle * 5.0F;
 float0 -= this->minimumSwingTime * 0.1F;
 float0 -= this->swingTime;
 if (desc != nullptr && desc.getInstance().getThreatLevel() <= 2 &&
 this->soundRadius > 5) {
 if (float0 > 0.0F && this->soundRadius > float0) {
 float0 = 1.0F;
 }

 float0 -= this->soundRadius;
 }

 return float0;
 }

 /**
 * @return the ActualWeight
 */
 float getActualWeight() {
 float float0 = this->getScriptItem().getActualWeight();
 float0 += this->getWeaponPartWeightModifier(this->canon);
 float0 += this->getWeaponPartWeightModifier(this->clip);
 float0 += this->getWeaponPartWeightModifier(this->recoilpad);
 float0 += this->getWeaponPartWeightModifier(this->scope);
 float0 += this->getWeaponPartWeightModifier(this->sling);
 return float0 + this->getWeaponPartWeightModifier(this->stock);
 }

 /**
 * @return the Weight
 */
 float getWeight() { return this->getActualWeight(); }

 float getContentsWeight() {
 float float0 = 0.0F;
 if (this->haveChamber() && this->isRoundChambered() &&
 !StringUtils.isNullOrWhitespace(this->getAmmoType())) {
 Item item0 = ScriptManager.instance.FindItem(this->getAmmoType());
 if (item0 != nullptr) {
 float0 += item0.getActualWeight();
 }
 }

 if (this->isContainsClip() &&
 !StringUtils.isNullOrWhitespace(this->getMagazineType())) {
 Item item1 = ScriptManager.instance.FindItem(this->getMagazineType());
 if (item1 != nullptr) {
 float0 += item1.getActualWeight();
 }
 }

 return float0 + super.getContentsWeight();
 }

 void DoTooltip(ObjectTooltip tooltipUI, ObjectTooltip.Layout layout) {
 float float0 = 1.0F;
 float float1 = 1.0F;
 float float2 = 0.8F;
 float float3 = 1.0F;
 ColorInfo colorInfo = new ColorInfo();
 ObjectTooltip.LayoutItem layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_Condition") + ":",
 float0, float1, float2, float3);
 float float4 = (float)this->Condition / this->ConditionMax;
 Core.getInstance().getBadHighlitedColor().interp(
 Core.getInstance().getGoodHighlitedColor(), float4, colorInfo);
 layoutItem.setProgress(float4, colorInfo.getR(), colorInfo.getG(),
 colorInfo.getB(), 1.0F);
 if (this->getMaxDamage() > 0.0F) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_Damage") + ":",
 float0, float1, float2, float3);
 float4 = this->getMaxDamage() + this->getMinDamage();
 float float5 = 5.0F;
 float float6 = float4 / float5;
 Core.getInstance().getBadHighlitedColor().interp(
 Core.getInstance().getGoodHighlitedColor(), float6, colorInfo);
 layoutItem.setProgress(float6, colorInfo.getR(), colorInfo.getG(),
 colorInfo.getB(), 1.0F);
 }

 if (this->isRanged()) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_Range") + ":",
 float0, float1, float2, 1.0F);
 float4 = this->getMaxRange(IsoPlayer.getInstance());
 float float7 = 40.0F;
 float float8 = float4 / float7;
 Core.getInstance().getBadHighlitedColor().interp(
 Core.getInstance().getGoodHighlitedColor(), float8, colorInfo);
 layoutItem.setProgress(float8, colorInfo.getR(), colorInfo.getG(),
 colorInfo.getB(), 1.0F);
 }

 if (this->isTwoHandWeapon() && !this->isRequiresEquippedBothHands()) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_item_TwoHandWeapon"),
 float0, float1, float2, float3);
 }

 if (!StringUtils.isNullOrEmpty(this->getFireMode())) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_item_FireMode") + ":",
 float0, float1, float2, float3);
 layoutItem.setValue(
 Translator.getText("ContextMenu_FireMode_" + this->getFireMode()),
 1.0F, 1.0F, 1.0F, 1.0F);
 }

 if (this->CantAttackWithLowestEndurance) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(
 Translator.getText("Tooltip_weapon_Unusable_at_max_exertion"),
 Core.getInstance().getBadHighlitedColor().getR(),
 Core.getInstance().getBadHighlitedColor().getG(),
 Core.getInstance().getBadHighlitedColor().getB(), 1.0F);
 }

 std::string string0 = this->getAmmoType();
 if (Core.getInstance().isNewReloading()) {
 if (this->getMaxAmmo() > 0) {
 std::string string1 = String.valueOf(this->getCurrentAmmoCount());
 if (this->isRoundChambered()) {
 string1 = string1 + "+1";
 }

 layoutItem = layout.addItem();
 if (this->bulletName.empty()) {
 if (this->getMagazineType() != nullptr) {
 this->bulletName =
 InventoryItemFactory.CreateItem(this->getMagazineType())
 .getDisplayName();
 } else {
 this->bulletName =
 InventoryItemFactory.CreateItem(this->getAmmoType())
 .getDisplayName();
 }
 }

 layoutItem.setLabel(this->bulletName + ":", 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValue(string1 + " / " + this->getMaxAmmo(), 1.0F, 1.0F,
 1.0F, 1.0F);
 }

 if (this->isJammed()) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_Jammed"),
 Core.getInstance().getBadHighlitedColor().getR(),
 Core.getInstance().getBadHighlitedColor().getG(),
 Core.getInstance().getBadHighlitedColor().getB(),
 1.0F);
 } else if (this->haveChamber() && !this->isRoundChambered() &&
 this->getCurrentAmmoCount() > 0) {
 layoutItem = layout.addItem();
 std::string string2 = this->isSpentRoundChambered()
 ? "Tooltip_weapon_SpentRoundChambered"
 : "Tooltip_weapon_NoRoundChambered";
 layoutItem.setLabel(Translator.getText(string2),
 Core.getInstance().getBadHighlitedColor().getR(),
 Core.getInstance().getBadHighlitedColor().getG(),
 Core.getInstance().getBadHighlitedColor().getB(),
 1.0F);
 } else if (this->getSpentRoundCount() > 0) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(
 Translator.getText("Tooltip_weapon_SpentRounds") + ":",
 Core.getInstance().getBadHighlitedColor().getR(),
 Core.getInstance().getBadHighlitedColor().getG(),
 Core.getInstance().getBadHighlitedColor().getB(), 1.0F);
 layoutItem.setValue(this->getSpentRoundCount() + " / " +
 this->getMaxAmmo(),
 1.0F, 1.0F, 1.0F, 1.0F);
 }

 if (!StringUtils.isNullOrEmpty(this->getMagazineType())) {
 if (this->isContainsClip()) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_ContainsClip"),
 1.0F, 1.0F, 0.8F, 1.0F);
 } else {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_NoClip"), 1.0F,
 1.0F, 0.8F, 1.0F);
 }
 }
 } else {
 if (string0.empty() && this->hasModData()) {
 void *object0 = this->getModData().rawget("defaultAmmo");
 if (object0 instanceof String) {
 string0 = (String)object0;
 }
 }

 if (string0 != nullptr) {
 Item item = ScriptManager.instance.FindItem(string0);
 if (item.empty()) {
 item =
 ScriptManager.instance.FindItem(this->getModule() + "." + string0);
 }

 if (item != nullptr) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_Ammo") + ":",
 float0, float1, float2, float3);
 layoutItem.setValue(item.getDisplayName(), 1.0F, 1.0F, 1.0F, 1.0F);
 }

 void *object1 = this->getModData().rawget("currentCapacity");
 void *object2 = this->getModData().rawget("maxCapacity");
 if (object1 instanceof Double && object2 instanceof Double) {
 std::string string3 = ((Double)object1).intValue() + " / " +
 ((Double)object2).intValue();
 void *object3 = this->getModData().rawget("roundChambered");
 if (object3 instanceof Double && ((Double)object3).intValue() == 1) {
 string3 = ((Double)object1).intValue() + "+1 / " +
 ((Double)object2).intValue();
 } else {
 void *object4 = this->getModData().rawget("emptyShellChambered");
 if (object4 instanceof
 Double && ((Double)object4).intValue() == 1) {
 string3 = ((Double)object1).intValue() + "+x / " +
 ((Double)object2).intValue();
 }
 }

 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_AmmoCount") +
 ":",
 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValue(string3, 1.0F, 1.0F, 1.0F, 1.0F);
 }
 }
 }

 ObjectTooltip.Layout _layout = tooltipUI.beginLayout();
 if (this->getStock() != nullptr) {
 layoutItem = _layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_Stock") + ":",
 float0, float1, float2, float3);
 layoutItem.setValue(this->getStock().getName(), 1.0F, 1.0F, 1.0F, 1.0F);
 }

 if (this->getSling() != nullptr) {
 layoutItem = _layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_Sling") + ":",
 float0, float1, float2, float3);
 layoutItem.setValue(this->getSling().getName(), 1.0F, 1.0F, 1.0F, 1.0F);
 }

 if (this->getScope() != nullptr) {
 layoutItem = _layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_Scope") + ":",
 float0, float1, float2, float3);
 layoutItem.setValue(this->getScope().getName(), 1.0F, 1.0F, 1.0F, 1.0F);
 }

 if (this->getCanon() != nullptr) {
 layoutItem = _layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_Canon") + ":",
 float0, float1, float2, float3);
 layoutItem.setValue(this->getCanon().getName(), 1.0F, 1.0F, 1.0F, 1.0F);
 }

 if (this->getClip() != nullptr) {
 layoutItem = _layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_Clip") + ":",
 float0, float1, float2, float3);
 layoutItem.setValue(this->getClip().getName(), 1.0F, 1.0F, 1.0F, 1.0F);
 }

 if (this->getRecoilpad() != nullptr) {
 layoutItem = _layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_RecoilPad") + ":",
 float0, float1, float2, float3);
 layoutItem.setValue(this->getRecoilpad().getName(), 1.0F, 1.0F, 1.0F,
 1.0F);
 }

 if (!_layout.items.empty()) {
 layout.next = _layout;
 _layout.nextPadY = tooltipUI.getLineSpacing();
 } else {
 tooltipUI.endLayout(_layout);
 }
 }

 float getDamageMod(IsoGameCharacter chr) {
 int int0 = chr.getPerkLevel(PerkFactory.Perks.Blunt);
 if (this->ScriptItem.Categories.contains("Blunt")) {
 if (int0 >= 3 && int0 <= 6) {
 return 1.1F;
 }

 if (int0 >= 7) {
 return 1.2F;
 }
 }

 int int1 = chr.getPerkLevel(PerkFactory.Perks.Axe);
 if (this->ScriptItem.Categories.contains("Axe")) {
 if (int1 >= 3 && int1 <= 6) {
 return 1.1F;
 }

 if (int1 >= 7) {
 return 1.2F;
 }
 }

 int int2 = chr.getPerkLevel(PerkFactory.Perks.Spear);
 if (this->ScriptItem.Categories.contains("Spear")) {
 if (int2 >= 3 && int2 <= 6) {
 return 1.1F;
 }

 if (int2 >= 7) {
 return 1.2F;
 }
 }

 return 1.0F;
 }

 float getRangeMod(IsoGameCharacter chr) {
 int int0 = chr.getPerkLevel(PerkFactory.Perks.Blunt);
 if (this->ScriptItem.Categories.contains("Blunt") && int0 >= 7) {
 return 1.2F;
 } else {
 int int1 = chr.getPerkLevel(PerkFactory.Perks.Axe);
 if (this->ScriptItem.Categories.contains("Axe") && int1 >= 7) {
 return 1.2F;
 } else {
 int int2 = chr.getPerkLevel(PerkFactory.Perks.Spear);
 return this->ScriptItem.Categories.contains("Spear") && int2 >= 7 ? 1.2F
 : 1.0F;
 }
 }
 }

 float getFatigueMod(IsoGameCharacter chr) {
 int int0 = chr.getPerkLevel(PerkFactory.Perks.Blunt);
 if (this->ScriptItem.Categories.contains("Blunt") && int0 >= 8) {
 return 0.8F;
 } else {
 int int1 = chr.getPerkLevel(PerkFactory.Perks.Axe);
 if (this->ScriptItem.Categories.contains("Axe") && int1 >= 8) {
 return 0.8F;
 } else {
 int int2 = chr.getPerkLevel(PerkFactory.Perks.Spear);
 return this->ScriptItem.Categories.contains("Spear") && int2 >= 8 ? 0.8F
 : 1.0F;
 }
 }
 }

 float getKnockbackMod(IsoGameCharacter chr) {
 int int0 = chr.getPerkLevel(PerkFactory.Perks.Axe);
 return this->ScriptItem.Categories.contains("Axe") && int0 >= 6 ? 2.0F
 : 1.0F;
 }

 float getSpeedMod(IsoGameCharacter chr) {
 if (this->ScriptItem.Categories.contains("Blunt")) {
 int int0 = chr.getPerkLevel(PerkFactory.Perks.Blunt);
 if (int0 >= 10) {
 return 0.65F;
 }

 if (int0 >= 9) {
 return 0.68F;
 }

 if (int0 >= 8) {
 return 0.71F;
 }

 if (int0 >= 7) {
 return 0.74F;
 }

 if (int0 >= 6) {
 return 0.77F;
 }

 if (int0 >= 5) {
 return 0.8F;
 }

 if (int0 >= 4) {
 return 0.83F;
 }

 if (int0 >= 3) {
 return 0.86F;
 }

 if (int0 >= 2) {
 return 0.9F;
 }

 if (int0 >= 1) {
 return 0.95F;
 }
 }

 if (this->ScriptItem.Categories.contains("Axe")) {
 int int1 = chr.getPerkLevel(PerkFactory.Perks.Axe);
 float float0 = 1.0F;
 if (chr.Traits.Axeman.isSet()) {
 float0 = 0.95F;
 }

 if (int1 >= 10) {
 return 0.65F * float0;
 } else if (int1 >= 9) {
 return 0.68F * float0;
 } else if (int1 >= 8) {
 return 0.71F * float0;
 } else if (int1 >= 7) {
 return 0.74F * float0;
 } else if (int1 >= 6) {
 return 0.77F * float0;
 } else if (int1 >= 5) {
 return 0.8F * float0;
 } else if (int1 >= 4) {
 return 0.83F * float0;
 } else if (int1 >= 3) {
 return 0.86F * float0;
 } else if (int1 >= 2) {
 return 0.9F * float0;
 } else {
 return int1 >= 1 ? 0.95F * float0 : 1.0F * float0;
 }
 } else {
 if (this->ScriptItem.Categories.contains("Spear")) {
 int int2 = chr.getPerkLevel(PerkFactory.Perks.Spear);
 if (int2 >= 10) {
 return 0.65F;
 }

 if (int2 >= 9) {
 return 0.68F;
 }

 if (int2 >= 8) {
 return 0.71F;
 }

 if (int2 >= 7) {
 return 0.74F;
 }

 if (int2 >= 6) {
 return 0.77F;
 }

 if (int2 >= 5) {
 return 0.8F;
 }

 if (int2 >= 4) {
 return 0.83F;
 }

 if (int2 >= 3) {
 return 0.86F;
 }

 if (int2 >= 2) {
 return 0.9F;
 }

 if (int2 >= 1) {
 return 0.95F;
 }
 }

 return 1.0F;
 }
 }

 float getToHitMod(IsoGameCharacter chr) {
 int int0 = chr.getPerkLevel(PerkFactory.Perks.Blunt);
 if (this->ScriptItem.Categories.contains("Blunt")) {
 if (int0 == 1) {
 return 1.2F;
 }

 if (int0 == 2) {
 return 1.3F;
 }

 if (int0 == 3) {
 return 1.4F;
 }

 if (int0 == 4) {
 return 1.5F;
 }

 if (int0 == 5) {
 return 1.6F;
 }

 if (int0 == 6) {
 return 1.7F;
 }

 if (int0 == 7) {
 return 1.8F;
 }

 if (int0 == 8) {
 return 1.9F;
 }

 if (int0 == 9) {
 return 2.0F;
 }

 if (int0 == 10) {
 return 100.0F;
 }
 }

 int int1 = chr.getPerkLevel(PerkFactory.Perks.Axe);
 if (this->ScriptItem.Categories.contains("Axe")) {
 if (int1 == 1) {
 return 1.2F;
 }

 if (int1 == 2) {
 return 1.3F;
 }

 if (int1 == 3) {
 return 1.4F;
 }

 if (int1 == 4) {
 return 1.5F;
 }

 if (int1 == 5) {
 return 1.6F;
 }

 if (int1 == 6) {
 return 1.7F;
 }

 if (int1 == 7) {
 return 1.8F;
 }

 if (int1 == 8) {
 return 1.9F;
 }

 if (int1 == 9) {
 return 2.0F;
 }

 if (int1 == 10) {
 return 100.0F;
 }
 }

 int int2 = chr.getPerkLevel(PerkFactory.Perks.Spear);
 if (this->ScriptItem.Categories.contains("Spear")) {
 if (int2 == 1) {
 return 1.2F;
 }

 if (int2 == 2) {
 return 1.3F;
 }

 if (int2 == 3) {
 return 1.4F;
 }

 if (int2 == 4) {
 return 1.5F;
 }

 if (int2 == 5) {
 return 1.6F;
 }

 if (int2 == 6) {
 return 1.7F;
 }

 if (int2 == 7) {
 return 1.8F;
 }

 if (int2 == 8) {
 return 1.9F;
 }

 if (int2 == 9) {
 return 2.0F;
 }

 if (int2 == 10) {
 return 100.0F;
 }
 }

 return 1.0F;
 }

 /**
 * @return the angleFalloff
 */
 bool isAngleFalloff() { return this->angleFalloff; }

 /**
 *
 * @param _angleFalloff the angleFalloff to set
 */
 void setAngleFalloff(bool _angleFalloff) {
 this->angleFalloff = _angleFalloff;
 }

 /**
 * @return the bCanBarracade
 */
 bool isCanBarracade() { return this->bCanBarracade; }

 /**
 *
 * @param _bCanBarracade the bCanBarracade to set
 */
 void setCanBarracade(bool _bCanBarracade) {
 this->bCanBarracade = _bCanBarracade;
 }

 /**
 * @return the doSwingBeforeImpact
 */
 float getDoSwingBeforeImpact() { return this->doSwingBeforeImpact; }

 /**
 *
 * @param _doSwingBeforeImpact the doSwingBeforeImpact to set
 */
 void setDoSwingBeforeImpact(float _doSwingBeforeImpact) {
 this->doSwingBeforeImpact = _doSwingBeforeImpact;
 }

 /**
 * @return the impactSound
 */
 std::string getImpactSound() { return this->impactSound; }

 /**
 *
 * @param _impactSound the impactSound to set
 */
 void setImpactSound(const std::string &_impactSound) {
 this->impactSound = _impactSound;
 }

 /**
 * @return the knockBackOnNoDeath
 */
 bool isKnockBackOnNoDeath() { return this->knockBackOnNoDeath; }

 /**
 *
 * @param _knockBackOnNoDeath the knockBackOnNoDeath to set
 */
 void setKnockBackOnNoDeath(bool _knockBackOnNoDeath) {
 this->knockBackOnNoDeath = _knockBackOnNoDeath;
 }

 /**
 * @return the maxAngle
 */
 float getMaxAngle() { return this->maxAngle; }

 /**
 *
 * @param _maxAngle the maxAngle to set
 */
 void setMaxAngle(float _maxAngle) { this->maxAngle = _maxAngle; }

 /**
 * @return the maxDamage
 */
 float getMaxDamage() { return this->maxDamage; }

 /**
 *
 * @param _maxDamage the maxDamage to set
 */
 void setMaxDamage(float _maxDamage) { this->maxDamage = _maxDamage; }

 /**
 * @return the maxHitCount
 */
 int getMaxHitCount() { return this->maxHitCount; }

 /**
 *
 * @param _maxHitCount the maxHitCount to set
 */
 void setMaxHitCount(int _maxHitCount) { this->maxHitCount = _maxHitCount; }

 /**
 * @return the maxRange
 */
 float getMaxRange() { return this->maxRange; }

 float getMaxRange(IsoGameCharacter owner) {
 return this->isRanged()
 ? this->maxRange +
 this->getAimingPerkRangeModifier() *
 (owner.getPerkLevel(PerkFactory.Perks.Aiming) / 2.0F)
 : this->maxRange;
 }

 /**
 *
 * @param _maxRange the maxRange to set
 */
 void setMaxRange(float _maxRange) { this->maxRange = _maxRange; }

 /**
 * @return the ranged
 */
 bool isRanged() { return this->ranged; }

 /**
 *
 * @param _ranged the ranged to set
 */
 void setRanged(bool _ranged) { this->ranged = _ranged; }

 /**
 * @return the minAngle
 */
 float getMinAngle() { return this->minAngle; }

 /**
 *
 * @param _minAngle the minAngle to set
 */
 void setMinAngle(float _minAngle) { this->minAngle = _minAngle; }

 /**
 * @return the minDamage
 */
 float getMinDamage() { return this->minDamage; }

 /**
 *
 * @param _minDamage the minDamage to set
 */
 void setMinDamage(float _minDamage) { this->minDamage = _minDamage; }

 /**
 * @return the minimumSwingTime
 */
 float getMinimumSwingTime() { return this->minimumSwingTime; }

 /**
 *
 * @param _minimumSwingTime the minimumSwingTime to set
 */
 void setMinimumSwingTime(float _minimumSwingTime) {
 this->minimumSwingTime = _minimumSwingTime;
 }

 /**
 * @return the minRange
 */
 float getMinRange() { return this->minRange; }

 /**
 *
 * @param _minRange the minRange to set
 */
 void setMinRange(float _minRange) { this->minRange = _minRange; }

 /**
 * @return the noiseFactor
 */
 float getNoiseFactor() { return this->noiseFactor; }

 /**
 *
 * @param _noiseFactor the noiseFactor to set
 */
 void setNoiseFactor(float _noiseFactor) { this->noiseFactor = _noiseFactor; }

 /**
 * @return the otherHandRequire
 */
 std::string getOtherHandRequire() { return this->otherHandRequire; }

 /**
 *
 * @param _otherHandRequire the otherHandRequire to set
 */
 void setOtherHandRequire(const std::string &_otherHandRequire) {
 this->otherHandRequire = _otherHandRequire;
 }

 /**
 * @return the otherHandUse
 */
 bool isOtherHandUse() { return this->otherHandUse; }

 /**
 *
 * @param _otherHandUse the otherHandUse to set
 */
 void setOtherHandUse(bool _otherHandUse) {
 this->otherHandUse = _otherHandUse;
 }

 /**
 * @return the physicsObject
 */
 std::string getPhysicsObject() { return this->physicsObject; }

 /**
 *
 * @param _physicsObject the physicsObject to set
 */
 void setPhysicsObject(const std::string &_physicsObject) {
 this->physicsObject = _physicsObject;
 }

 /**
 * @return the pushBackMod
 */
 float getPushBackMod() { return this->pushBackMod; }

 /**
 *
 * @param _pushBackMod the pushBackMod to set
 */
 void setPushBackMod(float _pushBackMod) { this->pushBackMod = _pushBackMod; }

 /**
 * @return the rangeFalloff
 */
 bool isRangeFalloff() { return this->rangeFalloff; }

 /**
 *
 * @param _rangeFalloff the rangeFalloff to set
 */
 void setRangeFalloff(bool _rangeFalloff) {
 this->rangeFalloff = _rangeFalloff;
 }

 /**
 * @return the shareDamage
 */
 bool isShareDamage() { return this->shareDamage; }

 /**
 *
 * @param _shareDamage the shareDamage to set
 */
 void setShareDamage(bool _shareDamage) { this->shareDamage = _shareDamage; }

 /**
 * @return the soundRadius
 */
 int getSoundRadius() { return this->soundRadius; }

 /**
 *
 * @param _soundRadius the soundRadius to set
 */
 void setSoundRadius(int _soundRadius) { this->soundRadius = _soundRadius; }

 /**
 * @return the soundVolume
 */
 int getSoundVolume() { return this->soundVolume; }

 /**
 *
 * @param _soundVolume the soundVolume to set
 */
 void setSoundVolume(int _soundVolume) { this->soundVolume = _soundVolume; }

 /**
 * @return the splatBloodOnNoDeath
 */
 bool isSplatBloodOnNoDeath() { return this->splatBloodOnNoDeath; }

 /**
 *
 * @param _splatBloodOnNoDeath the splatBloodOnNoDeath to set
 */
 void setSplatBloodOnNoDeath(bool _splatBloodOnNoDeath) {
 this->splatBloodOnNoDeath = _splatBloodOnNoDeath;
 }

 /**
 * @return the splatNumber
 */
 int getSplatNumber() { return this->splatNumber; }

 /**
 *
 * @param _splatNumber the splatNumber to set
 */
 void setSplatNumber(int _splatNumber) { this->splatNumber = _splatNumber; }

 /**
 * @return the swingSound
 */
 std::string getSwingSound() { return this->swingSound; }

 /**
 *
 * @param _swingSound the swingSound to set
 */
 void setSwingSound(const std::string &_swingSound) {
 this->swingSound = _swingSound;
 }

 /**
 * @return the swingTime
 */
 float getSwingTime() { return this->swingTime; }

 /**
 *
 * @param _swingTime the swingTime to set
 */
 void setSwingTime(float _swingTime) { this->swingTime = _swingTime; }

 /**
 * @return the toHitModifier
 */
 float getToHitModifier() { return this->toHitModifier; }

 /**
 *
 * @param _toHitModifier the toHitModifier to set
 */
 void setToHitModifier(float _toHitModifier) {
 this->toHitModifier = _toHitModifier;
 }

 /**
 * @return the useEndurance
 */
 bool isUseEndurance() { return this->useEndurance; }

 /**
 *
 * @param _useEndurance the useEndurance to set
 */
 void setUseEndurance(bool _useEndurance) {
 this->useEndurance = _useEndurance;
 }

 /**
 * @return the useSelf
 */
 bool isUseSelf() { return this->useSelf; }

 /**
 *
 * @param _useSelf the useSelf to set
 */
 void setUseSelf(bool _useSelf) { this->useSelf = _useSelf; }

 /**
 * @return the weaponSprite
 */
 std::string getWeaponSprite() { return this->weaponSprite; }

 /**
 *
 * @param _weaponSprite the weaponSprite to set
 */
 void setWeaponSprite(const std::string &_weaponSprite) {
 this->weaponSprite = _weaponSprite;
 }

 /**
 * @return the otherBoost
 */
 float getOtherBoost() { return this->otherBoost; }

 /**
 *
 * @param _otherBoost the otherBoost to set
 */
 void setOtherBoost(float _otherBoost) { this->otherBoost = _otherBoost; }

 /**
 * @return the DoorDamage
 */
 int getDoorDamage() { return this->DoorDamage; }

 /**
 *
 * @param _DoorDamage the DoorDamage to set
 */
 void setDoorDamage(int _DoorDamage) { this->DoorDamage = _DoorDamage; }

 /**
 * @return the doorHitSound
 */
 std::string getDoorHitSound() { return this->doorHitSound; }

 /**
 *
 * @param _doorHitSound the doorHitSound to set
 */
 void setDoorHitSound(const std::string &_doorHitSound) {
 this->doorHitSound = _doorHitSound;
 }

 /**
 * @return the ConditionLowerChance
 */
 int getConditionLowerChance() { return this->ConditionLowerChance; }

 /**
 *
 * @param _ConditionLowerChance the ConditionLowerChance to set
 */
 void setConditionLowerChance(int _ConditionLowerChance) {
 this->ConditionLowerChance = _ConditionLowerChance;
 }

 /**
 * @return the MultipleHitConditionAffected
 */
 bool isMultipleHitConditionAffected() {
 return this->MultipleHitConditionAffected;
 }

 /**
 *
 * @param _MultipleHitConditionAffected the MultipleHitConditionAffected to
 * set
 */
 void setMultipleHitConditionAffected(bool _MultipleHitConditionAffected) {
 this->MultipleHitConditionAffected = _MultipleHitConditionAffected;
 }

 /**
 * @return the shareEndurance
 */
 bool isShareEndurance() { return this->shareEndurance; }

 /**
 *
 * @param _shareEndurance the shareEndurance to set
 */
 void setShareEndurance(bool _shareEndurance) {
 this->shareEndurance = _shareEndurance;
 }

 /**
 * @return the AlwaysKnockdown
 */
 bool isAlwaysKnockdown() { return this->AlwaysKnockdown; }

 /**
 *
 * @param _AlwaysKnockdown the AlwaysKnockdown to set
 */
 void setAlwaysKnockdown(bool _AlwaysKnockdown) {
 this->AlwaysKnockdown = _AlwaysKnockdown;
 }

 /**
 * @return the EnduranceMod
 */
 float getEnduranceMod() { return this->EnduranceMod; }

 /**
 *
 * @param _EnduranceMod the EnduranceMod to set
 */
 void setEnduranceMod(float _EnduranceMod) {
 this->EnduranceMod = _EnduranceMod;
 }

 /**
 * @return the KnockdownMod
 */
 float getKnockdownMod() { return this->KnockdownMod; }

 /**
 *
 * @param _KnockdownMod the KnockdownMod to set
 */
 void setKnockdownMod(float _KnockdownMod) {
 this->KnockdownMod = _KnockdownMod;
 }

 /**
 * @return the CantAttackWithLowestEndurance
 */
 bool isCantAttackWithLowestEndurance() {
 return this->CantAttackWithLowestEndurance;
 }

 /**
 *
 * @param _CantAttackWithLowestEndurance the CantAttackWithLowestEndurance to
 * set
 */
 void setCantAttackWithLowestEndurance(bool _CantAttackWithLowestEndurance) {
 this->CantAttackWithLowestEndurance = _CantAttackWithLowestEndurance;
 }

 bool isAimedFirearm() { return this->bIsAimedFirearm; }

 bool isAimedHandWeapon() { return this->bIsAimedHandWeapon; }

 int getProjectileCount() { return this->ProjectileCount; }

 void setProjectileCount(int count) { this->ProjectileCount = count; }

 float getAimingMod() { return this->aimingMod; }

 bool isAimed() { return this->bIsAimedFirearm || this->bIsAimedHandWeapon; }

 void setCriticalChance(float criticalChance) {
 this->CriticalChance = criticalChance;
 }

 float getCriticalChance() { return this->CriticalChance; }

 void setSubCategory(const std::string &subcategory) {
 this->SubCategory = subcategory;
 }

 std::string getSubCategory() { return this->SubCategory; }

 void setZombieHitSound(const std::string &_hitSound) {
 this->hitSound = _hitSound;
 }

 std::string getZombieHitSound() { return this->hitSound; }

public
 ArrayList<String> getCategories() { return this->Categories; }

 void setCategories(ArrayList<String> categories) {
 this->Categories = categories;
 }

 int getAimingPerkCritModifier() { return this->AimingPerkCritModifier; }

 void setAimingPerkCritModifier(int aimingPerkCritModifier) {
 this->AimingPerkCritModifier = aimingPerkCritModifier;
 }

 float getAimingPerkRangeModifier() { return this->AimingPerkRangeModifier; }

 void setAimingPerkRangeModifier(float aimingPerkRangeModifier) {
 this->AimingPerkRangeModifier = aimingPerkRangeModifier;
 }

 int getHitChance() { return this->HitChance; }

 void setHitChance(int hitChance) { this->HitChance = hitChance; }

 float getAimingPerkHitChanceModifier() {
 return this->AimingPerkHitChanceModifier;
 }

 void setAimingPerkHitChanceModifier(float aimingPerkHitChanceModifier) {
 this->AimingPerkHitChanceModifier = aimingPerkHitChanceModifier;
 }

 float getAimingPerkMinAngleModifier() {
 return this->AimingPerkMinAngleModifier;
 }

 void setAimingPerkMinAngleModifier(float aimingPerkMinAngleModifier) {
 this->AimingPerkMinAngleModifier = aimingPerkMinAngleModifier;
 }

 int getRecoilDelay() { return this->RecoilDelay; }

 void setRecoilDelay(int recoilDelay) { this->RecoilDelay = recoilDelay; }

 bool isPiercingBullets() { return this->PiercingBullets; }

 void setPiercingBullets(bool piercingBullets) {
 this->PiercingBullets = piercingBullets;
 }

 float getSoundGain() { return this->soundGain; }

 void setSoundGain(float _soundGain) { this->soundGain = _soundGain; }

 WeaponPart getScope() { return this->scope; }

 void setScope(WeaponPart _scope) { this->scope = _scope; }

 WeaponPart getClip() { return this->clip; }

 void setClip(WeaponPart _clip) { this->clip = _clip; }

 WeaponPart getCanon() { return this->canon; }

 void setCanon(WeaponPart _canon) { this->canon = _canon; }

 WeaponPart getRecoilpad() { return this->recoilpad; }

 void setRecoilpad(WeaponPart _recoilpad) { this->recoilpad = _recoilpad; }

 int getClipSize() { return this->ClipSize; }

 void setClipSize(int capacity) {
 this->ClipSize = capacity;
 this->getModData().rawset("maxCapacity",
 BoxedStaticValues.toDouble(capacity);
 }

 void save(ByteBuffer output, bool net) {
 super.save(output, net);
 BitHeaderWrite bitHeaderWrite =
 BitHeader.allocWrite(BitHeader.HeaderSize.Integer, output);
 if (this->maxRange != 1.0F) {
 bitHeaderWrite.addFlags(1);
 output.putFloat(this->maxRange);
 }

 if (this->minRangeRanged != 0.0F) {
 bitHeaderWrite.addFlags(2);
 output.putFloat(this->minRangeRanged);
 }

 if (this->ClipSize != 0) {
 bitHeaderWrite.addFlags(4);
 output.putInt(this->ClipSize);
 }

 if (this->minDamage != 0.4F) {
 bitHeaderWrite.addFlags(8);
 output.putFloat(this->minDamage);
 }

 if (this->maxDamage != 1.5F) {
 bitHeaderWrite.addFlags(16);
 output.putFloat(this->maxDamage);
 }

 if (this->RecoilDelay != 0) {
 bitHeaderWrite.addFlags(32);
 output.putInt(this->RecoilDelay);
 }

 if (this->aimingTime != 0) {
 bitHeaderWrite.addFlags(64);
 output.putInt(this->aimingTime);
 }

 if (this->reloadTime != 0) {
 bitHeaderWrite.addFlags(128);
 output.putInt(this->reloadTime);
 }

 if (this->HitChance != 0) {
 bitHeaderWrite.addFlags(256);
 output.putInt(this->HitChance);
 }

 if (this->minAngle != 0.5F) {
 bitHeaderWrite.addFlags(512);
 output.putFloat(this->minAngle);
 }

 if (this->getScope() != nullptr) {
 bitHeaderWrite.addFlags(1024);
 output.putShort(this->getScope().getRegistry_id());
 }

 if (this->getClip() != nullptr) {
 bitHeaderWrite.addFlags(2048);
 output.putShort(this->getClip().getRegistry_id());
 }

 if (this->getRecoilpad() != nullptr) {
 bitHeaderWrite.addFlags(4096);
 output.putShort(this->getRecoilpad().getRegistry_id());
 }

 if (this->getSling() != nullptr) {
 bitHeaderWrite.addFlags(8192);
 output.putShort(this->getSling().getRegistry_id());
 }

 if (this->getStock() != nullptr) {
 bitHeaderWrite.addFlags(16384);
 output.putShort(this->getStock().getRegistry_id());
 }

 if (this->getCanon() != nullptr) {
 bitHeaderWrite.addFlags(32768);
 output.putShort(this->getCanon().getRegistry_id());
 }

 if (this->getExplosionTimer() != 0) {
 bitHeaderWrite.addFlags(65536);
 output.putInt(this->getExplosionTimer());
 }

 if (this->maxAngle != 1.0F) {
 bitHeaderWrite.addFlags(131072);
 output.putFloat(this->maxAngle);
 }

 if (this->bloodLevel != 0.0F) {
 bitHeaderWrite.addFlags(262144);
 output.putFloat(this->bloodLevel);
 }

 if (this->containsClip) {
 bitHeaderWrite.addFlags(524288);
 }

 if (this->roundChambered) {
 bitHeaderWrite.addFlags(1048576);
 }

 if (this->isJammed) {
 bitHeaderWrite.addFlags(2097152);
 }

 if (!StringUtils == this->weaponSprite,
 this->getScriptItem().getWeaponSprite())) {
 bitHeaderWrite.addFlags(4194304);
 GameWindow.WriteString(output, this->weaponSprite);
 }

 bitHeaderWrite.write();
 bitHeaderWrite.release();
 }

 void load(ByteBuffer input, int WorldVersion) {
 super.load(input, WorldVersion);
 this->maxRange = 1.0F;
 this->minRangeRanged = 0.0F;
 this->ClipSize = 0;
 this->minDamage = 0.4F;
 this->maxDamage = 1.5F;
 this->RecoilDelay = 0;
 this->aimingTime = 0;
 this->reloadTime = 0;
 this->HitChance = 0;
 this->minAngle = 0.5F;
 this->scope = nullptr;
 this->clip = nullptr;
 this->recoilpad = nullptr;
 this->sling = nullptr;
 this->stock = nullptr;
 this->canon = nullptr;
 this->explosionTimer = 0;
 this->maxAngle = 1.0F;
 this->bloodLevel = 0.0F;
 this->containsClip = false;
 this->roundChambered = false;
 this->isJammed = false;
 this->weaponSprite = this->getScriptItem().getWeaponSprite();
 BitHeaderRead bitHeaderRead =
 BitHeader.allocRead(BitHeader.HeaderSize.Integer, input);
 if (!bitHeaderRead == 0) {
 if (bitHeaderRead.hasFlags(1) {
 this->setMaxRange(input.getFloat());
 }

 if (bitHeaderRead.hasFlags(2) {
 this->setMinRangeRanged(input.getFloat());
 }

 if (bitHeaderRead.hasFlags(4) {
 this->setClipSize(input.getInt());
 }

 if (bitHeaderRead.hasFlags(8) {
 this->setMinDamage(input.getFloat());
 }

 if (bitHeaderRead.hasFlags(16) {
 this->setMaxDamage(input.getFloat());
 }

 if (bitHeaderRead.hasFlags(32) {
 this->setRecoilDelay(input.getInt());
 }

 if (bitHeaderRead.hasFlags(64) {
 this->setAimingTime(input.getInt());
 }

 if (bitHeaderRead.hasFlags(128) {
 this->setReloadTime(input.getInt());
 }

 if (bitHeaderRead.hasFlags(256) {
 this->setHitChance(input.getInt());
 }

 if (bitHeaderRead.hasFlags(512) {
 this->setMinAngle(input.getFloat());
 }

 if (bitHeaderRead.hasFlags(1024) {
 InventoryItem item0 =
 InventoryItemFactory.CreateItem(input.getShort());
 if (item0 != nullptr && item0 instanceof WeaponPart) {
 this->attachWeaponPart((WeaponPart)item0, false);
 }
 }

 if (bitHeaderRead.hasFlags(2048) {
 InventoryItem item1 =
 InventoryItemFactory.CreateItem(input.getShort());
 if (item1 != nullptr && item1 instanceof WeaponPart) {
 this->attachWeaponPart((WeaponPart)item1, false);
 }
 }

 if (bitHeaderRead.hasFlags(4096) {
 InventoryItem item2 =
 InventoryItemFactory.CreateItem(input.getShort());
 if (item2 != nullptr && item2 instanceof WeaponPart) {
 this->attachWeaponPart((WeaponPart)item2, false);
 }
 }

 if (bitHeaderRead.hasFlags(8192) {
 InventoryItem item3 =
 InventoryItemFactory.CreateItem(input.getShort());
 if (item3 != nullptr && item3 instanceof WeaponPart) {
 this->attachWeaponPart((WeaponPart)item3, false);
 }
 }

 if (bitHeaderRead.hasFlags(16384) {
 InventoryItem item4 =
 InventoryItemFactory.CreateItem(input.getShort());
 if (item4 != nullptr && item4 instanceof WeaponPart) {
 this->attachWeaponPart((WeaponPart)item4, false);
 }
 }

 if (bitHeaderRead.hasFlags(32768) {
 InventoryItem item5 =
 InventoryItemFactory.CreateItem(input.getShort());
 if (item5 != nullptr && item5 instanceof WeaponPart) {
 this->attachWeaponPart((WeaponPart)item5, false);
 }
 }

 if (bitHeaderRead.hasFlags(65536) {
 this->setExplosionTimer(input.getInt());
 }

 if (bitHeaderRead.hasFlags(131072) {
 this->setMaxAngle(input.getFloat());
 }

 if (bitHeaderRead.hasFlags(262144) {
 this->setBloodLevel(input.getFloat());
 }

 this->setContainsClip(bitHeaderRead.hasFlags(524288);
 if (StringUtils.isNullOrWhitespace(this->magazineType) {
 this->setContainsClip(false);
 }

 this->setRoundChambered(bitHeaderRead.hasFlags(1048576);
 this->setJammed(bitHeaderRead.hasFlags(2097152);
 if (bitHeaderRead.hasFlags(4194304) {
 this->setWeaponSprite(GameWindow.ReadStringUTF(input);
 }
 }

 bitHeaderRead.release();
 }

 float getMinRangeRanged() { return this->minRangeRanged; }

 void setMinRangeRanged(float _minRangeRanged) {
 this->minRangeRanged = _minRangeRanged;
 }

 int getReloadTime() { return this->reloadTime; }

 void setReloadTime(int _reloadTime) { this->reloadTime = _reloadTime; }

 WeaponPart getSling() { return this->sling; }

 void setSling(WeaponPart _sling) { this->sling = _sling; }

 int getAimingTime() { return this->aimingTime; }

 void setAimingTime(int _aimingTime) { this->aimingTime = _aimingTime; }

 WeaponPart getStock() { return this->stock; }

 void setStock(WeaponPart _stock) { this->stock = _stock; }

 int getTreeDamage() { return this->treeDamage; }

 void setTreeDamage(int _treeDamage) { this->treeDamage = _treeDamage; }

 std::string getBulletOutSound() { return this->bulletOutSound; }

 void setBulletOutSound(const std::string &_bulletOutSound) {
 this->bulletOutSound = _bulletOutSound;
 }

 std::string getShellFallSound() { return this->shellFallSound; }

 void setShellFallSound(const std::string &_shellFallSound) {
 this->shellFallSound = _shellFallSound;
 }

 void addPartToList(const std::string &string,
 ArrayList<WeaponPart> arrayList) {
 WeaponPart weaponPart = this->getWeaponPart(string);
 if (weaponPart != nullptr) {
 arrayList.add(weaponPart);
 }
 }

public
 ArrayList<WeaponPart> getAllWeaponParts() {
 return this->getAllWeaponParts(std::make_unique<ArrayList<>>());
 }

public
 ArrayList<WeaponPart> getAllWeaponParts(ArrayList<WeaponPart> result) {
 result.clear();
 this->addPartToList("Scope", result);
 this->addPartToList("Clip", result);
 this->addPartToList("Sling", result);
 this->addPartToList("Canon", result);
 this->addPartToList("Stock", result);
 this->addPartToList("RecoilPad", result);
 return result;
 }

 void setWeaponPart(const std::string &type, WeaponPart part) {
 if (part.empty() || type.equalsIgnoreCase(part.getPartType())) {
 if ("Scope".equalsIgnoreCase(type) {
 this->scope = part;
 } else if ("Clip".equalsIgnoreCase(type) {
 this->clip = part;
 } else if ("Sling".equalsIgnoreCase(type) {
 this->sling = part;
 } else if ("Canon".equalsIgnoreCase(type) {
 this->canon = part;
 } else if ("Stock".equalsIgnoreCase(type) {
 this->stock = part;
 } else if ("RecoilPad".equalsIgnoreCase(type) {
 this->recoilpad = part;
 } else {
 DebugLog.log("ERROR: unknown WeaponPart type \"" + type + "\"");
 }
 }
 }

 WeaponPart getWeaponPart(const std::string &type) {
 if ("Scope".equalsIgnoreCase(type) {
 return this->scope;
 } else if ("Clip".equalsIgnoreCase(type) {
 return this->clip;
 } else if ("Sling".equalsIgnoreCase(type) {
 return this->sling;
 } else if ("Canon".equalsIgnoreCase(type) {
 return this->canon;
 } else if ("Stock".equalsIgnoreCase(type) {
 return this->stock;
 } else if ("RecoilPad".equalsIgnoreCase(type) {
 return this->recoilpad;
 } else {
 DebugLog.log("ERROR: unknown WeaponPart type \"" + type + "\"");
 return nullptr;
 }
 }

 float getWeaponPartWeightModifier(const std::string &type) {
 return this->getWeaponPartWeightModifier(this->getWeaponPart(type);
 }

 float getWeaponPartWeightModifier(WeaponPart part) {
 return part = = nullptr ? 0.0F : part.getWeightModifier();
 }

 void attachWeaponPart(WeaponPart part) { this->attachWeaponPart(part, true); }

 void attachWeaponPart(WeaponPart part, bool doChange) {
 if (part != nullptr) {
 WeaponPart weaponPart = this->getWeaponPart(part.getPartType());
 if (weaponPart != nullptr) {
 this->detachWeaponPart(weaponPart);
 }

 this->setWeaponPart(part.getPartType(), part);
 if (doChange) {
 this->setMaxRange(this->getMaxRange() + part.getMaxRange());
 this->setMinRangeRanged(this->getMinRangeRanged() +
 part.getMinRangeRanged());
 this->setClipSize(this->getClipSize() + part.getClipSize());
 this->setReloadTime(this->getReloadTime() + part.getReloadTime());
 this->setRecoilDelay(
 (int)(this->getRecoilDelay() + part.getRecoilDelay()));
 this->setAimingTime(this->getAimingTime() + part.getAimingTime());
 this->setHitChance(this->getHitChance() + part.getHitChance());
 this->setMinAngle(this->getMinAngle() + part.getAngle());
 this->setMinDamage(this->getMinDamage() + part.getDamage());
 this->setMaxDamage(this->getMaxDamage() + part.getDamage());
 }
 }
 }

 void detachWeaponPart(WeaponPart part) {
 if (part != nullptr) {
 WeaponPart weaponPart = this->getWeaponPart(part.getPartType());
 if (weaponPart == part) {
 this->setWeaponPart(part.getPartType(), nullptr);
 this->setMaxRange(this->getMaxRange() - part.getMaxRange());
 this->setMinRangeRanged(this->getMinRangeRanged() -
 part.getMinRangeRanged());
 this->setClipSize(this->getClipSize() - part.getClipSize());
 this->setReloadTime(this->getReloadTime() - part.getReloadTime());
 this->setRecoilDelay(
 (int)(this->getRecoilDelay() - part.getRecoilDelay()));
 this->setAimingTime(this->getAimingTime() - part.getAimingTime());
 this->setHitChance(this->getHitChance() - part.getHitChance());
 this->setMinAngle(this->getMinAngle() - part.getAngle());
 this->setMinDamage(this->getMinDamage() - part.getDamage());
 this->setMaxDamage(this->getMaxDamage() - part.getDamage());
 }
 }
 }

 int getTriggerExplosionTimer() { return this->triggerExplosionTimer; }

 void setTriggerExplosionTimer(int _triggerExplosionTimer) {
 this->triggerExplosionTimer = _triggerExplosionTimer;
 }

 bool canBePlaced() { return this->canBePlaced; }

 void setCanBePlaced(bool _canBePlaced) { this->canBePlaced = _canBePlaced; }

 int getExplosionRange() { return this->explosionRange; }

 void setExplosionRange(int _explosionRange) {
 this->explosionRange = _explosionRange;
 }

 int getExplosionPower() { return this->explosionPower; }

 void setExplosionPower(int _explosionPower) {
 this->explosionPower = _explosionPower;
 }

 int getFireRange() { return this->fireRange; }

 void setFireRange(int _fireRange) { this->fireRange = _fireRange; }

 int getSmokeRange() { return this->smokeRange; }

 void setSmokeRange(int _smokeRange) { this->smokeRange = _smokeRange; }

 int getFirePower() { return this->firePower; }

 void setFirePower(int _firePower) { this->firePower = _firePower; }

 int getNoiseRange() { return this->noiseRange; }

 void setNoiseRange(int _noiseRange) { this->noiseRange = _noiseRange; }

 int getNoiseDuration() { return this->getScriptItem().getNoiseDuration(); }

 float getExtraDamage() { return this->extraDamage; }

 void setExtraDamage(float _extraDamage) { this->extraDamage = _extraDamage; }

 int getExplosionTimer() { return this->explosionTimer; }

 void setExplosionTimer(int _explosionTimer) {
 this->explosionTimer = _explosionTimer;
 }

 std::string getPlacedSprite() { return this->placedSprite; }

 void setPlacedSprite(const std::string &_placedSprite) {
 this->placedSprite = _placedSprite;
 }

 bool canBeReused() { return this->canBeReused; }

 void setCanBeReused(bool _canBeReused) { this->canBeReused = _canBeReused; }

 int getSensorRange() { return this->sensorRange; }

 void setSensorRange(int _sensorRange) { this->sensorRange = _sensorRange; }

 std::string getRunAnim() { return this->RunAnim; }

 float getCritDmgMultiplier() { return this->critDmgMultiplier; }

 void setCritDmgMultiplier(float _critDmgMultiplier) {
 this->critDmgMultiplier = _critDmgMultiplier;
 }

 std::string getStaticModel() {
 return this->staticModel != nullptr ? this->staticModel : this->weaponSprite;
 }

 float getBaseSpeed() { return this->baseSpeed; }

 void setBaseSpeed(float _baseSpeed) { this->baseSpeed = _baseSpeed; }

 float getBloodLevel() { return this->bloodLevel; }

 void setBloodLevel(float level) {
 this->bloodLevel = Math.max(0.0F, Math.min(1.0F, level);
 }

 void setWeaponLength(float weaponLength) { this->WeaponLength = weaponLength; }

 std::string getAmmoBox() { return this->ammoBox; }

 void setAmmoBox(const std::string &_ammoBox) { this->ammoBox = _ammoBox; }

 std::string getMagazineType() { return this->magazineType; }

 void setMagazineType(const std::string &_magazineType) {
 this->magazineType = _magazineType;
 }

 std::string getEjectAmmoStartSound() {
 return this->getScriptItem().getEjectAmmoStartSound();
 }

 std::string getEjectAmmoSound() {
 return this->getScriptItem().getEjectAmmoSound();
 }

 std::string getEjectAmmoStopSound() {
 return this->getScriptItem().getEjectAmmoStopSound();
 }

 std::string getInsertAmmoStartSound() {
 return this->getScriptItem().getInsertAmmoStartSound();
 }

 std::string getInsertAmmoSound() {
 return this->getScriptItem().getInsertAmmoSound();
 }

 std::string getInsertAmmoStopSound() {
 return this->getScriptItem().getInsertAmmoStopSound();
 }

 std::string getRackSound() { return this->rackSound; }

 void setRackSound(const std::string &_rackSound) {
 this->rackSound = _rackSound;
 }

 bool isReloadable(IsoGameCharacter owner) { return this->isRanged(); }

 bool isContainsClip() { return this->containsClip; }

 void setContainsClip(bool _containsClip) {
 this->containsClip = _containsClip;
 }

 /**
 * Get the magazine with the most bullets in it
 */
 InventoryItem getBestMagazine(IsoGameCharacter owner) {
 if (StringUtils.isNullOrEmpty(this->getMagazineType())) {
 return nullptr;
 } else {
 InventoryItem item = owner.getInventory().getBestTypeRecurse(
 this->getMagazineType(), (item1, item0)->item1.getCurrentAmmoCount() -
 item0.getCurrentAmmoCount());
 return item != nullptr && item.getCurrentAmmoCount() != 0 ? item
 : nullptr;
 }
 }

 std::string getWeaponReloadType() { return this->weaponReloadType; }

 void setWeaponReloadType(const std::string &_weaponReloadType) {
 this->weaponReloadType = _weaponReloadType;
 }

 bool isRackAfterShoot() { return this->rackAfterShoot; }

 void setRackAfterShoot(bool _rackAfterShoot) {
 this->rackAfterShoot = _rackAfterShoot;
 }

 bool isRoundChambered() { return this->roundChambered; }

 void setRoundChambered(bool _roundChambered) {
 this->roundChambered = _roundChambered;
 }

 bool isSpentRoundChambered() { return this->bSpentRoundChambered; }

 void setSpentRoundChambered(bool _roundChambered) {
 this->bSpentRoundChambered = _roundChambered;
 }

 int getSpentRoundCount() { return this->spentRoundCount; }

 void setSpentRoundCount(int count) {
 this->spentRoundCount = PZMath.clamp(count, 0, this->getMaxAmmo());
 }

 bool isManuallyRemoveSpentRounds() {
 return this->getScriptItem().isManuallyRemoveSpentRounds();
 }

 int getAmmoPerShoot() { return this->ammoPerShoot; }

 void setAmmoPerShoot(int _ammoPerShoot) { this->ammoPerShoot = _ammoPerShoot; }

 float getJamGunChance() { return this->jamGunChance; }

 void setJamGunChance(float _jamGunChance) {
 this->jamGunChance = _jamGunChance;
 }

 bool isJammed() { return this->isJammed; }

 void setJammed(bool _isJammed) { this->isJammed = _isJammed; }

 std::string getClickSound() { return this->clickSound; }

 void setClickSound(const std::string &_clickSound) {
 this->clickSound = _clickSound;
 }

public
 ArrayList<ModelWeaponPart> getModelWeaponPart() {
 return this->modelWeaponPart;
 }

 void setModelWeaponPart(ArrayList<ModelWeaponPart> _modelWeaponPart) {
 this->modelWeaponPart = _modelWeaponPart;
 }

 std::string getOriginalWeaponSprite() { return this->originalWeaponSprite; }

 void setOriginalWeaponSprite(const std::string &_originalWeaponSprite) {
 this->originalWeaponSprite = _originalWeaponSprite;
 }

 bool haveChamber() { return this->haveChamber; }

 void setHaveChamber(bool _haveChamber) { this->haveChamber = _haveChamber; }

 std::string getDamageCategory() { return this->damageCategory; }

 void setDamageCategory(const std::string &_damageCategory) {
 this->damageCategory = _damageCategory;
 }

 bool isDamageMakeHole() { return this->damageMakeHole; }

 void setDamageMakeHole(bool _damageMakeHole) {
 this->damageMakeHole = _damageMakeHole;
 }

 std::string getHitFloorSound() { return this->hitFloorSound; }

 void setHitFloorSound(const std::string &_hitFloorSound) {
 this->hitFloorSound = _hitFloorSound;
 }

 bool isInsertAllBulletsReload() { return this->insertAllBulletsReload; }

 void setInsertAllBulletsReload(bool _insertAllBulletsReload) {
 this->insertAllBulletsReload = _insertAllBulletsReload;
 }

 std::string getFireMode() { return this->fireMode; }

 void setFireMode(const std::string &_fireMode) { this->fireMode = _fireMode; }

public
 ArrayList<String> getFireModePossibilities() {
 return this->fireModePossibilities;
 }

 void setFireModePossibilities(ArrayList<String> _fireModePossibilities) {
 this->fireModePossibilities = _fireModePossibilities;
 }

 void randomizeBullets() {
 if (this->isRanged() && !Rand.NextBool(4) {
 this->setCurrentAmmoCount(
 Rand.Next(this->getMaxAmmo() - 2, this->getMaxAmmo()));
 if (!StringUtils.isNullOrEmpty(this->getMagazineType())) {
 this->setContainsClip(true);
 }

 if (this->haveChamber()) {
 this->setRoundChambered(true);
 }
 }
 }

 float getStopPower() { return this->getScriptItem().stopPower; }

 bool isInstantExplosion() {
 return this->explosionTimer <= 0 && this->sensorRange <= 0 &&
 this->getRemoteControlID() == -1;
 }
}
} // namespace types
} // namespace inventory
} // namespace zombie
