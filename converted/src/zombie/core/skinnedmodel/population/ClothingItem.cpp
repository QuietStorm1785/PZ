#include "zombie/core/skinnedmodel/population/ClothingItem.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {

public ClothingItem::ClothingItem(AssetPath path, AssetManager assetManager) {
 // TODO: Implement ClothingItem
 return nullptr;
}

std::string ClothingItem::GetATexture() {
 // TODO: Implement GetATexture
 return "";
}

bool ClothingItem::getAllowRandomHue() {
 // TODO: Implement getAllowRandomHue
 return false;
}

bool ClothingItem::getAllowRandomTint() {
 // TODO: Implement getAllowRandomTint
 return false;
}

std::string ClothingItem::getDecalGroup() {
 // TODO: Implement getDecalGroup
 return "";
}

bool ClothingItem::isHat() {
 // TODO: Implement isHat
 return false;
}

bool ClothingItem::isMask() {
 // TODO: Implement isMask
 return false;
}

void ClothingItem::getCombinedMask(CharacterMask in_out_mask) {
 // TODO: Implement getCombinedMask
}

bool ClothingItem::hasModel() {
 // TODO: Implement hasModel
 return false;
}

std::string ClothingItem::getModel(bool female) {
 // TODO: Implement getModel
 return "";
}

std::string ClothingItem::getFemaleModel() {
 // TODO: Implement getFemaleModel
 return "";
}

std::string ClothingItem::getMaleModel() {
 // TODO: Implement getMaleModel
 return "";
}

std::string ClothingItem::toString() {
 // TODO: Implement toString
 return "";
}

void ClothingItem::tryGetCombinedMask(ClothingItemReference itemRef, CharacterMask in_out_mask) {
 // TODO: Implement tryGetCombinedMask
}

void ClothingItem::tryGetCombinedMask(ClothingItem item, CharacterMask in_out_mask) {
 // TODO: Implement tryGetCombinedMask
}

AssetType ClothingItem::getType() {
 // TODO: Implement getType
 return {};
}

} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
