#include "zombie/core/skinnedmodel/visual/HumanVisual.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace visual {

public
HumanVisual::HumanVisual(IHumanVisual _owner) {
 // TODO: Implement HumanVisual
 return nullptr;
}

bool HumanVisual::isFemale() {
 // TODO: Implement isFemale
 return false;
}

bool HumanVisual::isZombie() {
 // TODO: Implement isZombie
 return false;
}

bool HumanVisual::isSkeleton() {
 // TODO: Implement isSkeleton
 return false;
}

void HumanVisual::setSkinColor(ImmutableColor color) {
 // TODO: Implement setSkinColor
}

ImmutableColor HumanVisual::getSkinColor() {
 // TODO: Implement getSkinColor
 return nullptr;
}

void HumanVisual::setBodyHairIndex(int index) {
 // TODO: Implement setBodyHairIndex
}

int HumanVisual::getBodyHairIndex() {
 // TODO: Implement getBodyHairIndex
 return 0;
}

void HumanVisual::setSkinTextureIndex(int index) {
 // TODO: Implement setSkinTextureIndex
}

int HumanVisual::getSkinTextureIndex() {
 // TODO: Implement getSkinTextureIndex
 return 0;
}

void HumanVisual::setSkinTextureName(const std::string &textureName) {
 // TODO: Implement setSkinTextureName
}

float HumanVisual::lerp(float start, float __end__, float delta) {
 // TODO: Implement lerp
 return 0;
}

int HumanVisual::pickRandomZombieRotStage() {
 // TODO: Implement pickRandomZombieRotStage
 return 0;
}

std::string HumanVisual::getSkinTexture() {
 // TODO: Implement getSkinTexture
 return "";
}

void HumanVisual::setHairColor(ImmutableColor color) {
 // TODO: Implement setHairColor
}

ImmutableColor HumanVisual::getHairColor() {
 // TODO: Implement getHairColor
 return nullptr;
}

void HumanVisual::setBeardColor(ImmutableColor color) {
 // TODO: Implement setBeardColor
}

ImmutableColor HumanVisual::getBeardColor() {
 // TODO: Implement getBeardColor
 return nullptr;
}

void HumanVisual::setNaturalHairColor(ImmutableColor color) {
 // TODO: Implement setNaturalHairColor
}

ImmutableColor HumanVisual::getNaturalHairColor() {
 // TODO: Implement getNaturalHairColor
 return nullptr;
}

void HumanVisual::setNaturalBeardColor(ImmutableColor color) {
 // TODO: Implement setNaturalBeardColor
}

ImmutableColor HumanVisual::getNaturalBeardColor() {
 // TODO: Implement getNaturalBeardColor
 return nullptr;
}

void HumanVisual::setHairModel(const std::string &model) {
 // TODO: Implement setHairModel
}

std::string HumanVisual::getHairModel() {
 // TODO: Implement getHairModel
 return "";
}

void HumanVisual::setBeardModel(const std::string &model) {
 // TODO: Implement setBeardModel
}

std::string HumanVisual::getBeardModel() {
 // TODO: Implement getBeardModel
 return "";
}

void HumanVisual::setBlood(BloodBodyPartType bodyPartType, float amount) {
 // TODO: Implement setBlood
}

float HumanVisual::getBlood(BloodBodyPartType bodyPartType) {
 // TODO: Implement getBlood
 return 0;
}

void HumanVisual::setDirt(BloodBodyPartType bodyPartType, float amount) {
 // TODO: Implement setDirt
}

float HumanVisual::getDirt(BloodBodyPartType bodyPartType) {
 // TODO: Implement getDirt
 return 0;
}

void HumanVisual::setHole(BloodBodyPartType bodyPartType) {
 // TODO: Implement setHole
}

float HumanVisual::getHole(BloodBodyPartType bodyPartType) {
 // TODO: Implement getHole
 return 0;
}

void HumanVisual::removeBlood() {
 // TODO: Implement removeBlood
}

void HumanVisual::removeDirt() {
 // TODO: Implement removeDirt
}

void HumanVisual::randomBlood() {
 // TODO: Implement randomBlood
}

void HumanVisual::randomDirt() {
 // TODO: Implement randomDirt
}

float HumanVisual::getTotalBlood() {
 // TODO: Implement getTotalBlood
 return 0;
}

void HumanVisual::clear() {
 // TODO: Implement clear
}

void HumanVisual::copyFrom(BaseVisual other_) {
 // TODO: Implement copyFrom
}

void HumanVisual::save(ByteBuffer output) {
 // TODO: Implement save
}

void HumanVisual::load(ByteBuffer input, int WorldVersion) {
 // TODO: Implement load
}

Model HumanVisual::getModel() {
 // TODO: Implement getModel
 return nullptr;
}

ModelScript HumanVisual::getModelScript() {
 // TODO: Implement getModelScript
 return nullptr;
}

CharacterMask HumanVisual::GetMask(ItemVisuals itemVisuals) {
 // TODO: Implement GetMask
 return nullptr;
}

void HumanVisual::synchWithOutfit(Outfit _outfit) {
 // TODO: Implement synchWithOutfit
}

void HumanVisual::dressInNamedOutfit(const std::string &outfitName,
 ItemVisuals itemVisuals) {
 // TODO: Implement dressInNamedOutfit
}

void HumanVisual::dressInClothingItem(const std::string &itemGUID,
 ItemVisuals itemVisuals) {
 // TODO: Implement dressInClothingItem
}

void HumanVisual::dressInClothingItem(const std::string &itemGUID,
 ItemVisuals itemVisuals,
 bool clearCurrentVisuals) {
 // TODO: Implement dressInClothingItem
}

void HumanVisual::dressInOutfit(Outfit outfitx, ItemVisuals itemVisuals) {
 // TODO: Implement dressInOutfit
}

ItemVisuals HumanVisual::getBodyVisuals() {
 // TODO: Implement getBodyVisuals
 return nullptr;
}

ItemVisual HumanVisual::addBodyVisual(const std::string &clothingItemName) {
 // TODO: Implement addBodyVisual
 return nullptr;
}

ItemVisual HumanVisual::addBodyVisualFromItemType(const std::string &itemType) {
 // TODO: Implement addBodyVisualFromItemType
 return nullptr;
}

ItemVisual HumanVisual::addBodyVisualFromClothingItemName(
 const std::string &clothingItemName) {
 // TODO: Implement addBodyVisualFromClothingItemName
 return nullptr;
}

ItemVisual
HumanVisual::removeBodyVisualFromItemType(const std::string &itemType) {
 // TODO: Implement removeBodyVisualFromItemType
 return nullptr;
}

bool HumanVisual::hasBodyVisualFromItemType(const std::string &itemType) {
 // TODO: Implement hasBodyVisualFromItemType
 return false;
}

void HumanVisual::getItemVisualLocations(ItemVisuals itemVisuals,
 ArrayList<String> arrayList) {
 // TODO: Implement getItemVisualLocations
}

ItemVisual HumanVisual::addClothingItem(ItemVisuals itemVisuals,
 Item scriptItem) {
 // TODO: Implement addClothingItem
 return nullptr;
}

ItemVisual HumanVisual::addClothingItem(
 ItemVisuals itemVisuals, ArrayList<String> arrayList,
 const std::string &string0, ClothingItemReference clothingItemReference) {
 // TODO: Implement addClothingItem
 return nullptr;
}

Outfit HumanVisual::getOutfit() {
 // TODO: Implement getOutfit
 return nullptr;
}

void HumanVisual::setOutfit(Outfit _outfit) {
 // TODO: Implement setOutfit
}

std::string HumanVisual::getNonAttachedHair() {
 // TODO: Implement getNonAttachedHair
 return "";
}

void HumanVisual::setNonAttachedHair(const std::string &_nonAttachedHair) {
 // TODO: Implement setNonAttachedHair
}

void HumanVisual::setForceModel(Model model) {
 // TODO: Implement setForceModel
}

void HumanVisual::setForceModelScript(const std::string &modelScript) {
 // TODO: Implement setForceModelScript
}

StringBuilder HumanVisual::toString(ImmutableColor immutableColor,
 StringBuilder stringBuilder) {
 // TODO: Implement toString
 return nullptr;
}

ImmutableColor HumanVisual::colorFromString(const std::string &string) {
 // TODO: Implement colorFromString
 return nullptr;
}

std::string HumanVisual::getLastStandString() {
 // TODO: Implement getLastStandString
 return "";
}

bool HumanVisual::loadLastStandString(const std::string &saveStr) {
 // TODO: Implement loadLastStandString
 return false;
}

} // namespace visual
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
