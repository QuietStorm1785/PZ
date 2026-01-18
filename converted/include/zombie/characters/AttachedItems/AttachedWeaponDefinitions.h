#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/population/Outfit.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace characters {
namespace AttachedItems {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AttachedWeaponDefinitions {
public:
 static const AttachedWeaponDefinitions instance = new AttachedWeaponDefinitions();
 bool m_dirty = true;
 int m_chanceOfAttachedWeapon;
 public ArrayList<AttachedWeaponDefinition> m_definitions = std::make_unique<ArrayList<>>();
 public ArrayList<AttachedWeaponCustomOutfit> m_outfitDefinitions = std::make_unique<ArrayList<>>();

 void checkDirty() {
 if (this->m_dirty) {
 this->m_dirty = false;
 this->init();
 }
 }

 void addRandomAttachedWeapon(IsoZombie zombie0) {
 if (!"Tutorial" == Core.getInstance().getGameMode())) {
 this->checkDirty();
 if (!this->m_definitions.empty()) {
 std::vector arrayList = AttachedWeaponDefinitions.L_addRandomAttachedWeapon.definitions;
 arrayList.clear();
 int int0 = 1;
 AttachedWeaponCustomOutfit attachedWeaponCustomOutfit = nullptr;
 Outfit outfit = zombie0.getHumanVisual().getOutfit();
 if (outfit != nullptr) {
 for (int int1 = 0; int1 < this->m_outfitDefinitions.size(); int1++) {
 attachedWeaponCustomOutfit = this->m_outfitDefinitions.get(int1);
 if (attachedWeaponCustomOutfit.outfit == outfit.m_Name) && OutfitRNG.Next(100) < attachedWeaponCustomOutfit.chance) {
 arrayList.addAll(attachedWeaponCustomOutfit.weapons);
 int0 = attachedWeaponCustomOutfit.maxitem > -1 ? attachedWeaponCustomOutfit.maxitem : 1;
 break;
 }

 attachedWeaponCustomOutfit = nullptr;
 }
 }

 if (arrayList.empty()) {
 if (OutfitRNG.Next(100) > this->m_chanceOfAttachedWeapon) {
 return;
 }

 arrayList.addAll(this->m_definitions);
 }

 while (int0 > 0) {
 AttachedWeaponDefinition attachedWeaponDefinition = this->pickRandomInList(arrayList, zombie0);
 if (attachedWeaponDefinition == nullptr) {
 return;
 }

 arrayList.remove(attachedWeaponDefinition);
 int0--;
 this->addAttachedWeapon(attachedWeaponDefinition, zombie0);
 if (attachedWeaponCustomOutfit != nullptr && OutfitRNG.Next(100) >= attachedWeaponCustomOutfit.chance) {
 return;
 }
 }
 }
 }
 }

 void addAttachedWeapon(AttachedWeaponDefinition attachedWeaponDefinition, IsoZombie zombie0) {
 std::string string = OutfitRNG.pickRandom(attachedWeaponDefinition.weapons);
 InventoryItem item0 = InventoryItemFactory.CreateItem(string);
 if (item0 != nullptr) {
 if (item0 instanceof HandWeapon) {
 ((HandWeapon)item0).randomizeBullets();
 }

 item0.setCondition(OutfitRNG.Next(Math.max(2, item0.getConditionMax() - 5), item0.getConditionMax()));
 zombie0.setAttachedItem(OutfitRNG.pickRandom(attachedWeaponDefinition.weaponLocation), item0);
 if (attachedWeaponDefinition.ensureItem != nullptr && !this->outfitHasItem(zombie0, attachedWeaponDefinition.ensureItem) {
 Item item1 = ScriptManager.instance.FindItem(attachedWeaponDefinition.ensureItem);
 if (item1 != nullptr && item1.getClothingItemAsset() != nullptr) {
 zombie0.getHumanVisual().addClothingItem(zombie0.getItemVisuals(), item1);
 } else {
 zombie0.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem(attachedWeaponDefinition.ensureItem);
 }
 }

 if (!attachedWeaponDefinition.bloodLocations.empty()) {
 for (int int0 = 0; int0 < attachedWeaponDefinition.bloodLocations.size(); int0++) {
 BloodBodyPartType bloodBodyPartType = attachedWeaponDefinition.bloodLocations.get(int0);
 zombie0.addBlood(bloodBodyPartType, true, true, true);
 zombie0.addBlood(bloodBodyPartType, true, true, true);
 zombie0.addBlood(bloodBodyPartType, true, true, true);
 if (attachedWeaponDefinition.addHoles) {
 zombie0.addHole(bloodBodyPartType);
 zombie0.addHole(bloodBodyPartType);
 zombie0.addHole(bloodBodyPartType);
 zombie0.addHole(bloodBodyPartType);
 }
 }
 }
 }
 }

 AttachedWeaponDefinition pickRandomInList(ArrayList<AttachedWeaponDefinition> arrayList1, IsoZombie zombie0) {
 AttachedWeaponDefinition attachedWeaponDefinition0 = nullptr;
 int int0 = 0;
 std::vector arrayList0 = AttachedWeaponDefinitions.L_addRandomAttachedWeapon.possibilities;
 arrayList0.clear();

 for (int int1 = 0; int1 < arrayList1.size(); int1++) {
 AttachedWeaponDefinition attachedWeaponDefinition1 = (AttachedWeaponDefinition)arrayList1.get(int1);
 if (attachedWeaponDefinition1.daySurvived > 0) {
 if (IsoWorld.instance.getWorldAgeDays() > attachedWeaponDefinition1.daySurvived) {
 int0 += attachedWeaponDefinition1.chance;
 arrayList0.add(attachedWeaponDefinition1);
 }
 } else if (!attachedWeaponDefinition1.outfit.empty()) {
 if (zombie0.getHumanVisual().getOutfit() != nullptr && attachedWeaponDefinition1.outfit.contains(zombie0.getHumanVisual().getOutfit().m_Name) {
 int0 += attachedWeaponDefinition1.chance;
 arrayList0.add(attachedWeaponDefinition1);
 }
 } else {
 int0 += attachedWeaponDefinition1.chance;
 arrayList0.add(attachedWeaponDefinition1);
 }
 }

 int int2 = OutfitRNG.Next(int0);
 int int3 = 0;

 for (int int4 = 0; int4 < arrayList0.size(); int4++) {
 AttachedWeaponDefinition attachedWeaponDefinition2 = (AttachedWeaponDefinition)arrayList0.get(int4);
 int3 += attachedWeaponDefinition2.chance;
 if (int2 < int3) {
 attachedWeaponDefinition0 = attachedWeaponDefinition2;
 break;
 }
 }

 return attachedWeaponDefinition0;
 }

 bool outfitHasItem(IsoZombie zombie0, const std::string& string) {
 assert string.contains(".");

 ItemVisuals itemVisuals = zombie0.getItemVisuals();

 for (int int0 = 0; int0 < itemVisuals.size(); int0++) {
 ItemVisual itemVisual = itemVisuals.get(int0);
 if (StringUtils == itemVisual.getItemType(), string) {
 return true;
 }

 if ("Base.HolsterSimple" == string) && StringUtils == itemVisual.getItemType(), "Base.HolsterDouble")) {
 return true;
 }

 if ("Base.HolsterDouble" == string) && StringUtils == itemVisual.getItemType(), "Base.HolsterSimple")) {
 return true;
 }
 }

 return false;
 }

 void init() {
 this->m_definitions.clear();
 this->m_outfitDefinitions.clear();
 KahluaTableImpl kahluaTableImpl0 = (KahluaTableImpl)LuaManager.env.rawget("AttachedWeaponDefinitions");
 if (kahluaTableImpl0 != nullptr) {
 this->m_chanceOfAttachedWeapon = kahluaTableImpl0.rawgetInt("chanceOfAttachedWeapon");

 for (Entry entry0 : kahluaTableImpl0.delegate.entrySet()) {
 if (entry0.getValue() instanceof KahluaTableImpl) {
 KahluaTableImpl kahluaTableImpl1 = (KahluaTableImpl)entry0.getValue();
 if ("attachedWeaponCustomOutfit" == entry0.getKey())) {
 KahluaTableImpl kahluaTableImpl2 = (KahluaTableImpl)entry0.getValue();

 for (Entry entry1 : kahluaTableImpl2.delegate.entrySet()) {
 AttachedWeaponCustomOutfit attachedWeaponCustomOutfit = this->initOutfit((String)entry1.getKey(), (KahluaTableImpl)entry1.getValue());
 if (attachedWeaponCustomOutfit != nullptr) {
 this->m_outfitDefinitions.add(attachedWeaponCustomOutfit);
 }
 }
 } else {
 AttachedWeaponDefinition attachedWeaponDefinition = this->init((String)entry0.getKey(), kahluaTableImpl1);
 if (attachedWeaponDefinition != nullptr) {
 this->m_definitions.add(attachedWeaponDefinition);
 }
 }
 }
 }

 Collections.sort(
 this->m_definitions,
 (attachedWeaponDefinition1, attachedWeaponDefinition0) -> attachedWeaponDefinition1.id.compareTo(attachedWeaponDefinition0.id)
 );
 }
 }

 AttachedWeaponCustomOutfit initOutfit(const std::string& string, KahluaTableImpl kahluaTableImpl0) {
 AttachedWeaponCustomOutfit attachedWeaponCustomOutfit = new AttachedWeaponCustomOutfit();
 attachedWeaponCustomOutfit.outfit = string;
 attachedWeaponCustomOutfit.chance = kahluaTableImpl0.rawgetInt("chance");
 attachedWeaponCustomOutfit.maxitem = kahluaTableImpl0.rawgetInt("maxitem");
 KahluaTableImpl kahluaTableImpl1 = (KahluaTableImpl)kahluaTableImpl0.rawget("weapons");

 for (Entry entry : kahluaTableImpl1.delegate.entrySet()) {
 KahluaTableImpl kahluaTableImpl2 = (KahluaTableImpl)entry.getValue();
 AttachedWeaponDefinition attachedWeaponDefinition = this->init(kahluaTableImpl2.rawgetStr("id"), kahluaTableImpl2);
 if (attachedWeaponDefinition != nullptr) {
 attachedWeaponCustomOutfit.weapons.add(attachedWeaponDefinition);
 }
 }

 return attachedWeaponCustomOutfit;
 }

 AttachedWeaponDefinition init(const std::string& string, KahluaTableImpl kahluaTableImpl0) {
 AttachedWeaponDefinition attachedWeaponDefinition = new AttachedWeaponDefinition();
 attachedWeaponDefinition.id = string;
 attachedWeaponDefinition.chance = kahluaTableImpl0.rawgetInt("chance");
 this->tableToArrayList(kahluaTableImpl0, "outfit", attachedWeaponDefinition.outfit);
 this->tableToArrayList(kahluaTableImpl0, "weaponLocation", attachedWeaponDefinition.weaponLocation);
 KahluaTableImpl kahluaTableImpl1 = (KahluaTableImpl)kahluaTableImpl0.rawget("bloodLocations");
 if (kahluaTableImpl1 != nullptr) {
 KahluaTableIterator kahluaTableIterator = kahluaTableImpl1.iterator();

 while (kahluaTableIterator.advance()) {
 BloodBodyPartType bloodBodyPartType = BloodBodyPartType.FromString(kahluaTableIterator.getValue().toString());
 if (bloodBodyPartType != BloodBodyPartType.MAX) {
 attachedWeaponDefinition.bloodLocations.add(bloodBodyPartType);
 }
 }
 }

 attachedWeaponDefinition.addHoles = kahluaTableImpl0.rawgetBool("addHoles");
 attachedWeaponDefinition.daySurvived = kahluaTableImpl0.rawgetInt("daySurvived");
 attachedWeaponDefinition.ensureItem = kahluaTableImpl0.rawgetStr("ensureItem");
 this->tableToArrayList(kahluaTableImpl0, "weapons", attachedWeaponDefinition.weapons);
 Collections.sort(attachedWeaponDefinition.weaponLocation);
 Collections.sort(attachedWeaponDefinition.bloodLocations);
 Collections.sort(attachedWeaponDefinition.weapons);
 return attachedWeaponDefinition;
 }

 void tableToArrayList(KahluaTable table, const std::string& string, ArrayList<String> arrayList) {
 KahluaTableImpl kahluaTableImpl = (KahluaTableImpl)table.rawget(string);
 if (kahluaTableImpl != nullptr) {
 int int0 = 1;

 for (int int1 = kahluaTableImpl.len(); int0 <= int1; int0++) {
 void* object = kahluaTableImpl.rawget(int0);
 if (object != nullptr) {
 arrayList.add(object.toString());
 }
 }
 }
 }

 private static class L_addRandomAttachedWeapon {
 static ArrayList<AttachedWeaponDefinition> possibilities = std::make_unique<ArrayList<>>();
 static ArrayList<AttachedWeaponDefinition> definitions = std::make_unique<ArrayList<>>();
 }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
