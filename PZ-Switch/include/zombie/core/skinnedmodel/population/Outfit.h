#pragma once
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "zombie/characters/HairOutfitDefinitions.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/skinnedmodel/model/CharacterMask.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Outfit {
public:
 std::string m_Name = "Outfit";
 bool m_Top = true;
 bool m_Pants = true;
public
 ArrayList<String> m_TopTextures = std::make_unique<ArrayList<>>();
public
 ArrayList<String> m_PantsTextures = std::make_unique<ArrayList<>>();
public
 ArrayList<ClothingItemReference> m_items =
 std::make_unique<ArrayList<>>();
 bool m_AllowPantsHue = true;
 bool m_AllowPantsTint = false;
 bool m_AllowTopTint = true;
 bool m_AllowTShirtDecal = true;
 std::string m_modID;
 bool m_Immutable = false;
public
 Outfit.RandomData RandomData = new Outfit.RandomData();

 void setModID(const std::string &modID) {
 this->m_modID = modID;

 for (ClothingItemReference clothingItemReference : this->m_items) {
 clothingItemReference.setModID(modID);
 }
 }

 void AddItem(ClothingItemReference item) { this->m_items.add(item); }

 void Randomize() {
 if (this->m_Immutable) {
 throw RuntimeException("trying to randomize an immutable Outfit");
 } else {
 for (int int0 = 0; int0 < this->m_items.size(); int0++) {
 ClothingItemReference clothingItemReference = this->m_items.get(int0);
 clothingItemReference.randomize();
 }

 this->RandomData.m_hairColor =
 HairOutfitDefinitions.instance.getRandomHaircutColor(this->m_Name);
 this->RandomData.m_femaleHairName =
 HairStyles.instance.getRandomFemaleStyle(this->m_Name);
 this->RandomData.m_maleHairName =
 HairStyles.instance.getRandomMaleStyle(this->m_Name);
 this->RandomData.m_beardName =
 BeardStyles.instance.getRandomStyle(this->m_Name);
 this->RandomData.m_topTint = OutfitRNG.randomImmutableColor();
 this->RandomData.m_pantsTint = OutfitRNG.randomImmutableColor();
 if (OutfitRNG.Next(4) == 0) {
 this->RandomData.m_pantsHue = OutfitRNG.Next(200) / 100.0F - 1.0F;
 } else {
 this->RandomData.m_pantsHue = 0.0F;
 }

 this->RandomData.m_hasTop = OutfitRNG.Next(16) != 0;
 this->RandomData.m_hasTShirt = OutfitRNG.Next(2) == 0;
 this->RandomData.m_hasTShirtDecal = OutfitRNG.Next(4) == 0;
 if (this->m_Top) {
 this->RandomData.m_hasTop = true;
 }

 this->RandomData.m_topTexture = OutfitRNG.pickRandom(this->m_TopTextures);
 this->RandomData.m_pantsTexture =
 OutfitRNG.pickRandom(this->m_PantsTextures);
 }
 }

 void randomizeItem(const std::string &itemGuid) {
 ClothingItemReference clothingItemReference = PZArrayUtil.find(
 this->m_items,
 clothingItemReferencex->clothingItemReferencex.itemGUID.equals(
 itemGuid);
 if (clothingItemReference != nullptr) {
 clothingItemReference.randomize();
 } else {
 DebugLog.Clothing.println(
 "Outfit.randomizeItem> Could not find itemGuid: " + itemGuid);
 }
 }

 CharacterMask GetMask() {
 CharacterMask characterMask = new CharacterMask();

 for (int int0 = 0; int0 < this->m_items.size(); int0++) {
 ClothingItemReference clothingItemReference = this->m_items.get(int0);
 if (clothingItemReference.RandomData.m_Active) {
 ClothingItem.tryGetCombinedMask(clothingItemReference, characterMask);
 }
 }

 return characterMask;
 }

 bool containsItemGuid(const std::string &itemGuid) {
 bool boolean0 = false;

 for (int int0 = 0; int0 < this->m_items.size(); int0++) {
 ClothingItemReference clothingItemReference = this->m_items.get(int0);
 if (clothingItemReference.itemGUID == itemGuid) {
 boolean0 = true;
 break;
 }
 }

 return boolean0;
 }

 ClothingItemReference findItemByGUID(const std::string &itemGuid) {
 for (int int0 = 0; int0 < this->m_items.size(); int0++) {
 ClothingItemReference clothingItemReference = this->m_items.get(int0);
 if (clothingItemReference.itemGUID == itemGuid) {
 return clothingItemReference;
 }
 }

 return nullptr;
 }

 Outfit clone() {
 try {
 Outfit outfit0 = new Outfit();
 outfit0.m_Name = this->m_Name;
 outfit0.m_Top = this->m_Top;
 outfit0.m_Pants = this->m_Pants;
 outfit0.m_PantsTextures.addAll(this->m_PantsTextures);
 outfit0.m_TopTextures.addAll(this->m_TopTextures);
 PZArrayUtil.copy(outfit0.m_items, this->m_items,
 ClothingItemReference::clone);
 outfit0.m_AllowPantsHue = this->m_AllowPantsHue;
 outfit0.m_AllowPantsTint = this->m_AllowPantsTint;
 outfit0.m_AllowTopTint = this->m_AllowTopTint;
 outfit0.m_AllowTShirtDecal = this->m_AllowTShirtDecal;
 return outfit0;
 } catch (CloneNotSupportedException cloneNotSupportedException) {
 throw RuntimeException("Outfit clone failed.",
 cloneNotSupportedException);
 }
 }

 ClothingItemReference findHat() {
 for (ClothingItemReference clothingItemReference : this->m_items) {
 if (clothingItemReference.RandomData.m_Active) {
 ClothingItem clothingItem = clothingItemReference.getClothingItem();
 if (clothingItem != nullptr && clothingItem.isHat()) {
 return clothingItemReference;
 }
 }
 }

 return nullptr;
 }

 bool isEmpty() {
 for (int int0 = 0; int0 < this->m_items.size(); int0++) {
 ClothingItemReference clothingItemReference0 = this->m_items.get(int0);
 ClothingItem clothingItem = OutfitManager.instance.getClothingItem(
 clothingItemReference0.itemGUID);
 if (clothingItem != nullptr && clothingItem.empty()) {
 return true;
 }

 for (int int1 = 0; int1 < clothingItemReference0.subItems.size();
 int1++) {
 ClothingItemReference clothingItemReference1 =
 clothingItemReference0.subItems.get(int1);
 clothingItem = OutfitManager.instance.getClothingItem(
 clothingItemReference1.itemGUID);
 if (clothingItem != nullptr && clothingItem.empty()) {
 return true;
 }
 }
 }

 return false;
 }

 void loadItems() {
 for (int int0 = 0; int0 < this->m_items.size(); int0++) {
 ClothingItemReference clothingItemReference0 = this->m_items.get(int0);
 OutfitManager.instance.getClothingItem(clothingItemReference0.itemGUID);

 for (int int1 = 0; int1 < clothingItemReference0.subItems.size();
 int1++) {
 ClothingItemReference clothingItemReference1 =
 clothingItemReference0.subItems.get(int1);
 OutfitManager.instance.getClothingItem(clothingItemReference1.itemGUID);
 }
 }
 }

public
 static class RandomData {
 ImmutableColor m_hairColor;
 std::string m_maleHairName;
 std::string m_femaleHairName;
 std::string m_beardName;
 ImmutableColor m_topTint;
 ImmutableColor m_pantsTint;
 float m_pantsHue;
 bool m_hasTop;
 bool m_hasTShirt;
 bool m_hasTShirtDecal;
 std::string m_topTexture;
 std::string m_pantsTexture;
 }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
