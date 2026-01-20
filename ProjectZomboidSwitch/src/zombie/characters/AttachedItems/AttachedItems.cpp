#include <string>
#include "zombie\characters\AttachedItems/AttachedItems.h"

namespace zombie {
namespace characters {
namespace AttachedItems {

public AttachedItems::AttachedItems(AttachedLocationGroup var1) {
    // TODO: Implement AttachedItems
    return nullptr;
}

public AttachedItems::AttachedItems(AttachedItems var1) {
    // TODO: Implement AttachedItems
    return nullptr;
}

void AttachedItems::copyFrom(AttachedItems var1) {
    // TODO: Implement copyFrom
}

AttachedLocationGroup AttachedItems::getGroup() {
    // TODO: Implement getGroup
    return nullptr;
}

AttachedItem AttachedItems::get(int var1) {
    // TODO: Implement get
    return nullptr;
}

void AttachedItems::setItem(const std::string& var1, InventoryItem var2) {
    // TODO: Implement setItem
}

InventoryItem AttachedItems::getItem(const std::string& var1) {
    // TODO: Implement getItem
    return nullptr;
}

InventoryItem AttachedItems::getItemByIndex(int var1) {
    // TODO: Implement getItemByIndex
    return nullptr;
}

void AttachedItems::remove(InventoryItem var1) {
    // TODO: Implement remove
}

void AttachedItems::clear() {
    // TODO: Implement clear
}

std::string AttachedItems::getLocation(InventoryItem var1) {
    // TODO: Implement getLocation
    return "";
}

bool AttachedItems::contains(InventoryItem var1) {
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

void AttachedItems::forEach(Consumer<AttachedItem> var1) {
    // TODO: Implement forEach
}

int AttachedItems::indexOf(const std::string& var1) {
    // TODO: Implement indexOf
    return 0;
}

int AttachedItems::indexOf(InventoryItem var1) {
    // TODO: Implement indexOf
    return 0;
}

} // namespace AttachedItems
} // namespace characters
} // namespace zombie
