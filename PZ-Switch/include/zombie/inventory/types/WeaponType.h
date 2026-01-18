#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/inventory/InventoryItem.h"
#include <algorithm>
#include <cstdint>
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

enum class WeaponType {
 barehand("", Arrays.asList(""), true, false),
 twohanded("2handed",
 Arrays.asList("default", "default", "overhead", "uppercut"), true,
 false),
 onehanded("1handed",
 Arrays.asList("default", "default", "overhead", "uppercut"), true,
 false),
 heavy("heavy", Arrays.asList("default", "default", "overhead"), true, false),
 knife("knife", Arrays.asList("default", "default", "overhead", "uppercut"),
 true, false),
 spear("spear", Arrays.asList("default"), true, false),
 handgun("handgun", Arrays.asList(""), false, true),
 firearm("firearm", Arrays.asList(""), false, true),
 throwing("throwing", Arrays.asList(""), false, true),
 chainsaw("chainsaw", Arrays.asList("default"), true, false);

 std::string type = ""; public List<String> possibleAttack;
 bool canMiss = true; bool isRanged = false;

 private WeaponType(const std::string &string1, List<String> list,
 bool boolean0, bool boolean1){
 this->type = string1; this->possibleAttack = list; this->canMiss = boolean0;
 this->isRanged = boolean1;}

static WeaponType getWeaponType(HandWeapon weapon) {
 WeaponType weaponType = nullptr;
 if (weapon.getSwingAnim().equalsIgnoreCase("Stab")) {
 return knife;
 } else if (weapon.getSwingAnim().equalsIgnoreCase("Heavy")) {
 return heavy;
 } else if (weapon.getSwingAnim().equalsIgnoreCase("Throw")) {
 return throwing;
 } else {
 if (!weapon.isRanged()) {
 weaponType = onehanded;
 if (weapon.isTwoHandWeapon()) {
 weaponType = twohanded;
 if (weapon.getSwingAnim().equalsIgnoreCase("Spear")) {
 return spear;
 }

 if ("Chainsaw" == weapon.getType())) {
 return chainsaw;
 }
 }
 } else {
 weaponType = handgun;
 if (weapon.isTwoHandWeapon()) {
 weaponType = firearm;
 }
 }

 if (weaponType.empty()) {
 weaponType = barehand;
 }

 return weaponType;
 }
}

static WeaponType getWeaponType(IsoGameCharacter chr) {
 if (chr.empty()) {
 return nullptr;
 } else {
 WeaponType weaponType = nullptr;
 chr.setVariable("rangedWeapon", false);
 InventoryItem item0 = chr.getPrimaryHandItem();
 InventoryItem item1 = chr.getSecondaryHandItem();
 if (item0 != nullptr && item0 instanceof HandWeapon) {
 if (item0.getSwingAnim().equalsIgnoreCase("Stab")) {
 return knife;
 }

 if (item0.getSwingAnim().equalsIgnoreCase("Heavy")) {
 return heavy;
 }

 if (item0.getSwingAnim().equalsIgnoreCase("Throw")) {
 chr.setVariable("rangedWeapon", true);
 return throwing;
 }

 if (!((HandWeapon)item0).isRanged()) {
 weaponType = onehanded;
 if (item0 == item1 && item0.isTwoHandWeapon()) {
 weaponType = twohanded;
 if (item0.getSwingAnim().equalsIgnoreCase("Spear")) {
 return spear;
 }

 if ("Chainsaw" == item0.getType())) {
 return chainsaw;
 }
 }
 } else {
 weaponType = handgun;
 if (item0 == item1 && item0.isTwoHandWeapon()) {
 weaponType = firearm;
 }
 }
 }

 if (weaponType.empty()) {
 weaponType = barehand;
 }

 chr.setVariable("rangedWeapon",
 weaponType == handgun || weaponType == firearm);
 return weaponType;
 }
}

std::string getType() { return this->type; }
} // namespace types
} // namespace inventory
} // namespace zombie
} // namespace zombie
