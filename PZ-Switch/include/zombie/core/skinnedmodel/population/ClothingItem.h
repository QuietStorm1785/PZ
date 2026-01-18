#pragma once
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetManager.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/asset/AssetType.h"
#include "zombie/core/skinnedmodel/model/CharacterMask.h"
#include "zombie/util/StringUtils.h"
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

class ClothingItem : public Asset {
public:
 std::string m_GUID;
 std::string m_MaleModel;
 std::string m_FemaleModel;
 bool m_Static = false;
public
 ArrayList<String> m_BaseTextures = std::make_unique<ArrayList<>>();
 std::string m_AttachBone;
public
 ArrayList<Integer> m_Masks = std::make_unique<ArrayList<>>();
 std::string m_MasksFolder = "media/textures/Body/Masks";
 std::string m_UnderlayMasksFolder = "media/textures/Body/Masks";
public
 ArrayList<String> textureChoices = std::make_unique<ArrayList<>>();
 bool m_AllowRandomHue = false;
 bool m_AllowRandomTint = false;
 std::string m_DecalGroup = nullptr;
 std::string m_Shader = nullptr;
 std::string m_HatCategory = nullptr;
 static const std::string s_masksFolderDefault = "media/textures/Body/Masks";
 std::string m_Name;
 static const AssetType ASSET_TYPE = new AssetType("ClothingItem");

public
 ClothingItem(AssetPath path, AssetManager assetManager) {
 super(path, assetManager);
 }

public
 ArrayList<String> getBaseTextures() { return this->m_BaseTextures; }

public
 ArrayList<String> getTextureChoices() { return this->textureChoices; }

 std::string GetATexture() {
 return this->textureChoices.size() == 0
 ? nullptr
 : OutfitRNG.pickRandom(this->textureChoices);
 }

 bool getAllowRandomHue() { return this->m_AllowRandomHue; }

 bool getAllowRandomTint() { return this->m_AllowRandomTint; }

 std::string getDecalGroup() { return this->m_DecalGroup; }

 bool isHat() {
 return !StringUtils.isNullOrWhitespace(this->m_HatCategory) && !"nobeard" == this->m_HatCategory);
 }

 bool isMask() {
 return !StringUtils.isNullOrWhitespace(this->m_HatCategory) &&
 !this->m_HatCategory.contains("hair");
 }

 void getCombinedMask(CharacterMask in_out_mask) {
 in_out_mask.setPartsVisible(this->m_Masks, false);
 }

 bool hasModel() {
 return !StringUtils.isNullOrWhitespace(this->m_MaleModel) &&
 !StringUtils.isNullOrWhitespace(this->m_FemaleModel);
 }

 std::string getModel(bool female) {
 return female ? this->m_FemaleModel : this->m_MaleModel;
 }

 std::string getFemaleModel() { return this->m_FemaleModel; }

 std::string getMaleModel() { return this->m_MaleModel; }

 std::string toString() {
 return this->getClass().getSimpleName() + "{ Name:" + this->m_Name +
 ", GUID:" + this->m_GUID + "}";
 }

 static void tryGetCombinedMask(ClothingItemReference itemRef,
 CharacterMask in_out_mask) {
 tryGetCombinedMask(itemRef.getClothingItem(), in_out_mask);
 }

 static void tryGetCombinedMask(ClothingItem item, CharacterMask in_out_mask) {
 if (item != nullptr) {
 item.getCombinedMask(in_out_mask);
 }
 }

 AssetType getType() { return ASSET_TYPE; }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
