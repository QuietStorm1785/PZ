#include "zombie/characters/WornItems/WornItems.h"

namespace zombie {
namespace characters {
namespace WornItems {

public WornItems::WornItems(BodyLocationGroup _group) {
 // TODO: Implement WornItems
 return nullptr;
}

public WornItems::WornItems(WornItems other) {
 // TODO: Implement WornItems
 return nullptr;
}

void WornItems::copyFrom(WornItems other) {
 // TODO: Implement copyFrom
}

BodyLocationGroup WornItems::getBodyLocationGroup() {
 // TODO: Implement getBodyLocationGroup
 return nullptr;
}

WornItem WornItems::get(int index) {
 // TODO: Implement get
 return nullptr;
}

void WornItems::setItem(const std::string& location, InventoryItem item) {
 // TODO: Implement setItem
}

InventoryItem WornItems::getItem(const std::string& location) {
 // TODO: Implement getItem
 return nullptr;
}

InventoryItem WornItems::getItemByIndex(int index) {
 // TODO: Implement getItemByIndex
 return nullptr;
}

void WornItems::remove(InventoryItem item) {
 // TODO: Implement remove
}

void WornItems::clear() {
 // TODO: Implement clear
}

std::string WornItems::getLocation(InventoryItem item) {
 // TODO: Implement getLocation
 return "";
}

bool WornItems::contains(InventoryItem item) {
 // TODO: Implement contains
 return false;
}

int WornItems::size() {
 // TODO: Implement size
 return 0;
}

bool WornItems::isEmpty() {
 // TODO: Implement isEmpty
 return false;
}

void WornItems::forEach(Consumer<WornItem> c) {
 // TODO: Implement forEach
}

void WornItems::setFromItemVisuals(ItemVisuals itemVisuals) {
 // TODO: Implement setFromItemVisuals
}

void WornItems::getItemVisuals(ItemVisuals itemVisuals) {
 // TODO: Implement getItemVisuals
}

void WornItems::addItemsToItemContainer(ItemContainer container) {
 // TODO: Implement addItemsToItemContainer
}

int WornItems::indexOf(const std::string& string) {
 // TODO: Implement indexOf
 return 0;
}

int WornItems::indexOf(InventoryItem item) {
 // TODO: Implement indexOf
 return 0;
}

} // namespace WornItems
} // namespace characters
} // namespace zombie
