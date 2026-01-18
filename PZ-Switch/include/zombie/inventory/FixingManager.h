#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/Rand.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Fixing.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace inventory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FixingManager {
public:
public
 static ArrayList<Fixing> getFixes(InventoryItem item) {
 std::vector arrayList = new ArrayList();
 std::vector list = ScriptManager.instance.getAllFixing(new ArrayList<>());

 for (int int0 = 0; int0 < list.size(); int0++) {
 Fixing fixing = (Fixing)list.get(int0);
 if (fixing.getRequiredItem().contains(item.getType())) {
 arrayList.add(fixing);
 }
 }

 return arrayList;
 }

 static InventoryItem fixItem(InventoryItem brokenItem, IsoGameCharacter chr,
 Fixing fixing, Fixing.Fixer fixer) {
 if (Rand.Next(100) >= getChanceOfFail(brokenItem, chr, fixing, fixer) {
 double double0 = getCondRepaired(brokenItem, chr, fixing, fixer);
 int int0 = brokenItem.getConditionMax() - brokenItem.getCondition();
 double double1 = new Double(int0 * (double0 / 100.0);
 int int1 = (int)Math.round(double1);
 if (int1 == 0) {
 int1 = 1;
 }

 brokenItem.setCondition(brokenItem.getCondition() + int1);
 brokenItem.setHaveBeenRepaired(brokenItem.getHaveBeenRepaired() + 1);
 } else if (brokenItem.getCondition() > 0 && Rand.Next(5) == 0) {
 brokenItem.setCondition(brokenItem.getCondition() - 1);
 chr.getEmitter().playSound("FixingItemFailed");
 }

 useFixer(chr, fixer, brokenItem);
 if (fixing.getGlobalItem() != nullptr) {
 useFixer(chr, fixing.getGlobalItem(), brokenItem);
 }

 addXp(chr, fixer);
 return brokenItem;
 }

 static void addXp(IsoGameCharacter character, Fixing.Fixer fixer) {
 if (fixer.getFixerSkills() != nullptr) {
 for (int int0 = 0; int0 < fixer.getFixerSkills().size(); int0++) {
 Fixing.FixerSkill fixerSkill = fixer.getFixerSkills().get(int0);
 character.getXp().AddXP(
 PerkFactory.Perks.FromString(fixerSkill.getSkillName()),
 (float)Rand.Next(3, 6);
 }
 }
 }

 static void useFixer(IsoGameCharacter chr, Fixing.Fixer fixer,
 InventoryItem brokenItem) {
 int int0 = fixer.getNumberOfUse();

 for (int int1 = 0; int1 < chr.getInventory().getItems().size(); int1++) {
 if (brokenItem != chr.getInventory().getItems().get(int1) {
 InventoryItem item0 = chr.getInventory().getItems().get(int1);
 if (item0 != nullptr && item0.getType() == fixer.getFixerName())) {
 if (item0 instanceof DrainableComboItem) {
 if ("DuctTape" == item0.getType()) || "Scotchtape" == item0.getType())) {
 chr.getEmitter().playSound("FixWithTape");
 }

 int int2 = ((DrainableComboItem)item0).getDrainableUsesInt();
 int int3 = Math.min(int2, int0);

 for (int int4 = 0; int4 < int3; int4++) {
 item0.Use();
 int0--;
 if (!chr.getInventory().getItems().contains(item0) {
 int1--;
 break;
 }
 }
 } else {
 if (item0 instanceof HandWeapon) {
 if (chr.getSecondaryHandItem() == item0) {
 chr.setSecondaryHandItem(nullptr);
 }

 if (chr.getPrimaryHandItem() == item0) {
 chr.setPrimaryHandItem(nullptr);
 }

 HandWeapon weapon = (HandWeapon)item0;
 if (weapon.getScope() != nullptr) {
 chr.getInventory().AddItem(weapon.getScope());
 }

 if (weapon.getClip() != nullptr) {
 chr.getInventory().AddItem(weapon.getClip());
 }

 if (weapon.getSling() != nullptr) {
 chr.getInventory().AddItem(weapon.getSling());
 }

 if (weapon.getStock() != nullptr) {
 chr.getInventory().AddItem(weapon.getStock());
 }

 if (weapon.getCanon() != nullptr) {
 chr.getInventory().AddItem(weapon.getCanon());
 }

 if (weapon.getRecoilpad() != nullptr) {
 chr.getInventory().AddItem(weapon.getRecoilpad());
 }

 int int5 = 0;
 if (weapon.getMagazineType() != nullptr &&
 weapon.isContainsClip()) {
 InventoryItem item1 =
 InventoryItemFactory.CreateItem(weapon.getMagazineType());
 item1.setCurrentAmmoCount(weapon.getCurrentAmmoCount());
 chr.getInventory().AddItem(item1);
 } else if (weapon.getCurrentAmmoCount() > 0) {
 int5 += weapon.getCurrentAmmoCount();
 }

 if (weapon.haveChamber() && weapon.isRoundChambered()) {
 int5++;
 }

 if (int5 > 0) {
 for (int int6 = 0; int6 < int5; int6++) {
 InventoryItem item2 =
 InventoryItemFactory.CreateItem(weapon.getAmmoType());
 chr.getInventory().AddItem(item2);
 }
 }
 }

 chr.getInventory().Remove(item0);
 int1--;
 int0--;
 }
 }

 if (int0 == 0) {
 break;
 }
 }
 }
 }

 static double getChanceOfFail(InventoryItem brokenItem, IsoGameCharacter chr,
 Fixing fixing, Fixing.Fixer fixer) {
 double double0 = 3.0;
 if (fixer.getFixerSkills() != nullptr) {
 for (int int0 = 0; int0 < fixer.getFixerSkills().size(); int0++) {
 if (chr.getPerkLevel(PerkFactory.Perks.FromString(
 fixer.getFixerSkills().get(int0).getSkillName())) <
 fixer.getFixerSkills().get(int0).getSkillLevel()) {
 double0 += (fixer.getFixerSkills().get(int0).getSkillLevel() -
 chr.getPerkLevel(PerkFactory.Perks.FromString(
 fixer.getFixerSkills().get(int0).getSkillName()))) *
 30;
 } else {
 double0 -= (chr.getPerkLevel(PerkFactory.Perks.FromString(
 fixer.getFixerSkills().get(int0).getSkillName())) -
 fixer.getFixerSkills().get(int0).getSkillLevel()) *
 5;
 }
 }
 }

 double0 += brokenItem.getHaveBeenRepaired() * 2;
 if (chr.Traits.Lucky.isSet()) {
 double0 -= 5.0;
 }

 if (chr.Traits.Unlucky.isSet()) {
 double0 += 5.0;
 }

 if (double0 > 100.0) {
 double0 = 100.0;
 }

 if (double0 < 0.0) {
 double0 = 0.0;
 }

 return double0;
 }

 static double getCondRepaired(InventoryItem brokenItem, IsoGameCharacter chr,
 Fixing fixing, Fixing.Fixer fixer) {
 double double0 = 0.0;

 double0 = switch (fixing.getFixers().indexOf(fixer) {
 case 0 -> 50.0 * (1.0 / brokenItem.getHaveBeenRepaired());
 case 1 -> 20.0 * (1.0 / brokenItem.getHaveBeenRepaired());
 default -> 10.0 * (1.0 / brokenItem.getHaveBeenRepaired());
 };
 if (fixer.getFixerSkills() != nullptr) {
 for (int int0 = 0; int0 < fixer.getFixerSkills().size(); int0++) {
 Fixing.FixerSkill fixerSkill = fixer.getFixerSkills().get(int0);
 int int1 = chr.getPerkLevel(PerkFactory.Perks.FromString(fixerSkill.getSkillName()));
 if (int1 > fixerSkill.getSkillLevel()) {
 double0 += Math.min((int1 - fixerSkill.getSkillLevel()) * 5, 25);
 } else {
 double0 -= (fixerSkill.getSkillLevel() - int1) * 15;
 }
 }
 }

 double0 *= fixing.getConditionModifier();
 double0 = Math.max(0.0, double0);
 return Math.min(100.0, double0);
 }
}
} // namespace inventory
} // namespace zombie
