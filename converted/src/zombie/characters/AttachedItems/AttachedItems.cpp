#include "zombie/characters/AttachedItems/AttachedItems.h"

namespace zombie {
namespace characters {
namespace AttachedItems {

public AttachedItems::AttachedItems(AttachedLocationGroup _group) {
 // TODO: Implement AttachedItems
 return nullptr;
}

public AttachedItems::AttachedItems(AttachedItems other) {
 // TODO: Implement AttachedItems
 return nullptr;
}

void AttachedItems::copyFrom(AttachedItems other) {
 // TODO: Implement copyFrom
}

AttachedLocationGroup AttachedItems::getGroup() {
 // TODO: Implement getGroup
 return nullptr;
}

AttachedItem AttachedItems::get(int index) {
 // TODO: Implement get
 return nullptr;
}

void AttachedItems::setItem(const std::string& location, InventoryItem item) {
 // TODO: Implement setItem
}

InventoryItem AttachedItems::getItem(const std::string& location) {
 // TODO: Implement getItem
 return nullptr;
}

InventoryItem AttachedItems::getItemByIndex(int index) {
 // TODO: Implement getItemByIndex
 return nullptr;
}

void AttachedItems::remove(InventoryItem item) {
 // TODO: Implement remove
}

void AttachedItems::clear() {
 // TODO: Implement clear
}

std::string AttachedItems::getLocation(InventoryItem item) {
 // TODO: Implement getLocation
 return "";
}

bool AttachedItems::contains(InventoryItem item) {
 // TODO: Implement contains
 return false;
}

int AttachedItems::size() {
 // TODO: Implement size
 return 0;
}

bool AttachedItems::isEmpty() {
 // TODO: Implement isEmpty
 return false;
}

void AttachedItems::forEach(Consumer<AttachedItem> c) {
 // TODO: Implement forEach
}

int AttachedItems::indexOf(const std::string& string) {
 // TODO: Implement indexOf
 return 0;
}

int AttachedItems::indexOf(InventoryItem item) {
 // TODO: Implement indexOf
 return 0;
}

} // namespace AttachedItems
} // namespace characters
} // namespace zombie
