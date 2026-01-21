#include <sstream>
#include <string>
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace visual {

public ItemVisual::ItemVisual() {
    // TODO: Implement ItemVisual
    return nullptr;
}

public ItemVisual::ItemVisual(ItemVisual var1) {
    // TODO: Implement ItemVisual
    return nullptr;
}

void ItemVisual::setItemType(const std::string& var1) {
    // TODO: Implement setItemType
}

std::string ItemVisual::getItemType() {
    // TODO: Implement getItemType
    return "";
}

void ItemVisual::setAlternateModelName(const std::string& var1) {
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

void ItemVisual::setClothingItemName(const std::string& var1) {
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

void ItemVisual::getClothingItemCombinedMask(CharacterMask var1) {
    // TODO: Implement getClothingItemCombinedMask
}

void ItemVisual::setHue(float var1) {
    // TODO: Implement setHue
}

float ItemVisual::getHue(ClothingItem var1) {
    // TODO: Implement getHue
    return 0;
}

void ItemVisual::setTint(ImmutableColor var1) {
    // TODO: Implement setTint
}

ImmutableColor ItemVisual::getTint(ClothingItem var1) {
    // TODO: Implement getTint
    return nullptr;
}

ImmutableColor ItemVisual::getTint() {
    // TODO: Implement getTint
    return nullptr;
}

std::string ItemVisual::getBaseTexture(ClothingItem var1) {
    // TODO: Implement getBaseTexture
    return "";
}

std::string ItemVisual::getTextureChoice(ClothingItem var1) {
    // TODO: Implement getTextureChoice
    return "";
}

void ItemVisual::setDecal(const std::string& var1) {
    // TODO: Implement setDecal
}

std::string ItemVisual::getDecal(ClothingItem var1) {
    // TODO: Implement getDecal
    return "";
}

void ItemVisual::pickUninitializedValues(ClothingItem var1) {
    // TODO: Implement pickUninitializedValues
}

void ItemVisual::synchWithOutfit(ClothingItemReference var1) {
    // TODO: Implement synchWithOutfit
}

void ItemVisual::clear() {
    // TODO: Implement clear
}

void ItemVisual::copyFrom(ItemVisual var1) {
    // TODO: Implement copyFrom
}

void ItemVisual::save(ByteBuffer var1) {
    // TODO: Implement save
}

void ItemVisual::load(ByteBuffer var1, int var2) {
    // TODO: Implement load
}

void ItemVisual::setDenimPatch(BloodBodyPartType var1) {
    // TODO: Implement setDenimPatch
}

float ItemVisual::getDenimPatch(BloodBodyPartType var1) {
    // TODO: Implement getDenimPatch
    return 0;
}

void ItemVisual::setLeatherPatch(BloodBodyPartType var1) {
    // TODO: Implement setLeatherPatch
}

float ItemVisual::getLeatherPatch(BloodBodyPartType var1) {
    // TODO: Implement getLeatherPatch
    return 0;
}

void ItemVisual::setBasicPatch(BloodBodyPartType var1) {
    // TODO: Implement setBasicPatch
}

float ItemVisual::getBasicPatch(BloodBodyPartType var1) {
    // TODO: Implement getBasicPatch
    return 0;
}

int ItemVisual::getBasicPatchesNumber() {
    // TODO: Implement getBasicPatchesNumber
    return 0;
}

void ItemVisual::setHole(BloodBodyPartType var1) {
    // TODO: Implement setHole
}

float ItemVisual::getHole(BloodBodyPartType var1) {
    // TODO: Implement getHole
    return 0;
}

int ItemVisual::getHolesNumber() {
    // TODO: Implement getHolesNumber
    return 0;
}

void ItemVisual::setBlood(BloodBodyPartType var1, float var2) {
    // TODO: Implement setBlood
}

float ItemVisual::getBlood(BloodBodyPartType var1) {
    // TODO: Implement getBlood
    return 0;
}

float ItemVisual::getDirt(BloodBodyPartType var1) {
    // TODO: Implement getDirt
    return 0;
}

void ItemVisual::setDirt(BloodBodyPartType var1, float var2) {
    // TODO: Implement setDirt
}

void ItemVisual::copyBlood(ItemVisual var1) {
    // TODO: Implement copyBlood
}

void ItemVisual::copyDirt(ItemVisual var1) {
    // TODO: Implement copyDirt
}

void ItemVisual::copyHoles(ItemVisual var1) {
    // TODO: Implement copyHoles
}

void ItemVisual::copyPatches(ItemVisual var1) {
    // TODO: Implement copyPatches
}

void ItemVisual::removeHole(int var1) {
    // TODO: Implement removeHole
}

void ItemVisual::removePatch(int var1) {
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

void ItemVisual::setInventoryItem(InventoryItem var1) {
    // TODO: Implement setInventoryItem
}

void ItemVisual::setBaseTexture(int var1) {
    // TODO: Implement setBaseTexture
}

int ItemVisual::getBaseTexture() {
    // TODO: Implement getBaseTexture
    return 0;
}

void ItemVisual::setTextureChoice(int var1) {
    // TODO: Implement setTextureChoice
}

int ItemVisual::getTextureChoice() {
    // TODO: Implement getTextureChoice
    return 0;
}

std::stringstream ItemVisual::toString(ImmutableColor var0, std::stringstream var1) {
    // TODO: Implement toString
    return nullptr;
}

ImmutableColor ItemVisual::colorFromString(const std::string& var0) {
    // TODO: Implement colorFromString
    return nullptr;
}

std::string ItemVisual::getLastStandString() {
    // TODO: Implement getLastStandString
    return "";
}

InventoryItem ItemVisual::createLastStandItem(const std::string& var0) {
    // TODO: Implement createLastStandItem
    return nullptr;
}

} // namespace visual
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
