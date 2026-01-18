#include "zombie/core/skinnedmodel/visual/ItemVisual.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace visual {

public
ItemVisual::ItemVisual() {
  // TODO: Implement ItemVisual
  return nullptr;
}

public
ItemVisual::ItemVisual(ItemVisual other) {
  // TODO: Implement ItemVisual
  return nullptr;
}

void ItemVisual::setItemType(const std::string &fullType) {
  // TODO: Implement setItemType
}

std::string ItemVisual::getItemType() {
  // TODO: Implement getItemType
  return "";
}

void ItemVisual::setAlternateModelName(const std::string &name) {
  // TODO: Implement setAlternateModelName
}

std::string ItemVisual::getAlternateModelName() {
  // TODO: Implement getAlternateModelName
  return "";
}

std::string ItemVisual::toString() {
  // TODO: Implement toString
  return "";
}

std::string ItemVisual::getClothingItemName() {
  // TODO: Implement getClothingItemName
  return "";
}

void ItemVisual::setClothingItemName(const std::string &name) {
  // TODO: Implement setClothingItemName
}

Item ItemVisual::getScriptItem() {
  // TODO: Implement getScriptItem
  return nullptr;
}

ClothingItem ItemVisual::getClothingItem() {
  // TODO: Implement getClothingItem
  return nullptr;
}

void ItemVisual::getClothingItemCombinedMask(CharacterMask in_out_mask) {
  // TODO: Implement getClothingItemCombinedMask
}

void ItemVisual::setHue(float hue) {
  // TODO: Implement setHue
}

float ItemVisual::getHue(ClothingItem clothingItem) {
  // TODO: Implement getHue
  return 0;
}

void ItemVisual::setTint(ImmutableColor tint) {
  // TODO: Implement setTint
}

ImmutableColor ItemVisual::getTint(ClothingItem clothingItem) {
  // TODO: Implement getTint
  return nullptr;
}

ImmutableColor ItemVisual::getTint() {
  // TODO: Implement getTint
  return nullptr;
}

std::string ItemVisual::getBaseTexture(ClothingItem clothingItem) {
  // TODO: Implement getBaseTexture
  return "";
}

std::string ItemVisual::getTextureChoice(ClothingItem clothingItem) {
  // TODO: Implement getTextureChoice
  return "";
}

void ItemVisual::setDecal(const std::string &decalName) {
  // TODO: Implement setDecal
}

std::string ItemVisual::getDecal(ClothingItem clothingItem) {
  // TODO: Implement getDecal
  return "";
}

void ItemVisual::pickUninitializedValues(ClothingItem clothingItem) {
  // TODO: Implement pickUninitializedValues
}

void ItemVisual::synchWithOutfit(ClothingItemReference itemRef) {
  // TODO: Implement synchWithOutfit
}

void ItemVisual::clear() {
  // TODO: Implement clear
}

void ItemVisual::copyFrom(ItemVisual other) {
  // TODO: Implement copyFrom
}

void ItemVisual::save(ByteBuffer output) {
  // TODO: Implement save
}

void ItemVisual::load(ByteBuffer input, int WorldVersion) {
  // TODO: Implement load
}

void ItemVisual::setDenimPatch(BloodBodyPartType bodyPartType) {
  // TODO: Implement setDenimPatch
}

float ItemVisual::getDenimPatch(BloodBodyPartType bodyPartType) {
  // TODO: Implement getDenimPatch
  return 0;
}

void ItemVisual::setLeatherPatch(BloodBodyPartType bodyPartType) {
  // TODO: Implement setLeatherPatch
}

float ItemVisual::getLeatherPatch(BloodBodyPartType bodyPartType) {
  // TODO: Implement getLeatherPatch
  return 0;
}

void ItemVisual::setBasicPatch(BloodBodyPartType bodyPartType) {
  // TODO: Implement setBasicPatch
}

float ItemVisual::getBasicPatch(BloodBodyPartType bodyPartType) {
  // TODO: Implement getBasicPatch
  return 0;
}

int ItemVisual::getBasicPatchesNumber() {
  // TODO: Implement getBasicPatchesNumber
  return 0;
}

void ItemVisual::setHole(BloodBodyPartType bodyPartType) {
  // TODO: Implement setHole
}

float ItemVisual::getHole(BloodBodyPartType bodyPartType) {
  // TODO: Implement getHole
  return 0;
}

int ItemVisual::getHolesNumber() {
  // TODO: Implement getHolesNumber
  return 0;
}

void ItemVisual::setBlood(BloodBodyPartType bodyPartType, float amount) {
  // TODO: Implement setBlood
}

float ItemVisual::getBlood(BloodBodyPartType bodyPartType) {
  // TODO: Implement getBlood
  return 0;
}

float ItemVisual::getDirt(BloodBodyPartType bodyPartType) {
  // TODO: Implement getDirt
  return 0;
}

void ItemVisual::setDirt(BloodBodyPartType bodyPartType, float amount) {
  // TODO: Implement setDirt
}

void ItemVisual::copyBlood(ItemVisual other) {
  // TODO: Implement copyBlood
}

void ItemVisual::copyDirt(ItemVisual other) {
  // TODO: Implement copyDirt
}

void ItemVisual::copyHoles(ItemVisual other) {
  // TODO: Implement copyHoles
}

void ItemVisual::copyPatches(ItemVisual other) {
  // TODO: Implement copyPatches
}

void ItemVisual::removeHole(int bodyPartIndex) {
  // TODO: Implement removeHole
}

void ItemVisual::removePatch(int bodyPartIndex) {
  // TODO: Implement removePatch
}

void ItemVisual::removeBlood() {
  // TODO: Implement removeBlood
}

void ItemVisual::removeDirt() {
  // TODO: Implement removeDirt
}

float ItemVisual::getTotalBlood() {
  // TODO: Implement getTotalBlood
  return 0;
}

InventoryItem ItemVisual::getInventoryItem() {
  // TODO: Implement getInventoryItem
  return nullptr;
}

void ItemVisual::setInventoryItem(InventoryItem _inventoryItem) {
  // TODO: Implement setInventoryItem
}

void ItemVisual::setBaseTexture(int baseTexture) {
  // TODO: Implement setBaseTexture
}

int ItemVisual::getBaseTexture() {
  // TODO: Implement getBaseTexture
  return 0;
}

void ItemVisual::setTextureChoice(int TextureChoice) {
  // TODO: Implement setTextureChoice
}

int ItemVisual::getTextureChoice() {
  // TODO: Implement getTextureChoice
  return 0;
}

StringBuilder ItemVisual::toString(ImmutableColor immutableColor,
                                   StringBuilder stringBuilder) {
  // TODO: Implement toString
  return nullptr;
}

ImmutableColor ItemVisual::colorFromString(const std::string &string) {
  // TODO: Implement colorFromString
  return nullptr;
}

std::string ItemVisual::getLastStandString() {
  // TODO: Implement getLastStandString
  return "";
}

InventoryItem ItemVisual::createLastStandItem(const std::string &saveStr) {
  // TODO: Implement createLastStandItem
  return nullptr;
}

} // namespace visual
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
