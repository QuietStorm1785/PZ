#include "zombie/iso/objects/IsoClothingWasher.h"

namespace zombie {
namespace iso {
namespace objects {

public
IsoClothingWasher::IsoClothingWasher(IsoCell cell) {
 // TODO: Implement IsoClothingWasher
 return nullptr;
}

public
IsoClothingWasher::IsoClothingWasher(IsoCell cell, IsoGridSquare sq,
 IsoSprite gid) {
 // TODO: Implement IsoClothingWasher
 return nullptr;
}

std::string IsoClothingWasher::getObjectName() {
 // TODO: Implement getObjectName
 return "";
}

void IsoClothingWasher::load(ByteBuffer input, int WorldVersion,
 bool IS_DEBUG_SAVE) {
 // TODO: Implement load
}

void IsoClothingWasher::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 // TODO: Implement save
}

void IsoClothingWasher::update() {
 // TODO: Implement update
}

void IsoClothingWasher::addToWorld() {
 // TODO: Implement addToWorld
}

void IsoClothingWasher::removeFromWorld() {
 // TODO: Implement removeFromWorld
}

void IsoClothingWasher::saveChange(const std::string &change, KahluaTable tbl,
 ByteBuffer bb) {
 // TODO: Implement saveChange
}

void IsoClothingWasher::loadChange(const std::string &change, ByteBuffer bb) {
 // TODO: Implement loadChange
}

bool IsoClothingWasher::isItemAllowedInContainer(ItemContainer container,
 InventoryItem item) {
 // TODO: Implement isItemAllowedInContainer
 return false;
}

bool IsoClothingWasher::isRemoveItemAllowedFromContainer(
 ItemContainer container, InventoryItem item) {
 // TODO: Implement isRemoveItemAllowedFromContainer
 return false;
}

bool IsoClothingWasher::isActivated() {
 // TODO: Implement isActivated
 return false;
}

void IsoClothingWasher::setActivated(bool activated) {
 // TODO: Implement setActivated
}

} // namespace objects
} // namespace iso
} // namespace zombie
