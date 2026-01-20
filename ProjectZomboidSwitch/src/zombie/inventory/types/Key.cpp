#include <string>
#include "zombie\inventory\types/Key.h"

namespace zombie {
namespace inventory {
namespace types {

public Key::Key(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
    // TODO: Implement Key
    return nullptr;
}

int Key::getSaveType() {
    // TODO: Implement getSaveType
    return 0;
}

void Key::takeKeyId() {
    // TODO: Implement takeKeyId
}

void Key::setHighlightDoors(int var0, InventoryItem var1) {
    // TODO: Implement setHighlightDoors
}

int Key::getKeyId() {
    // TODO: Implement getKeyId
    return 0;
}

void Key::setKeyId(int var1) {
    // TODO: Implement setKeyId
}

std::string Key::getCategory() {
    // TODO: Implement getCategory
    return "";
}

void Key::save(ByteBuffer var1, bool var2) {
    // TODO: Implement save
}

void Key::load(ByteBuffer var1, int var2) {
    // TODO: Implement load
}

bool Key::isPadlock() {
    // TODO: Implement isPadlock
    return false;
}

void Key::setPadlock(bool var1) {
    // TODO: Implement setPadlock
}

int Key::getNumberOfKey() {
    // TODO: Implement getNumberOfKey
    return 0;
}

void Key::setNumberOfKey(int var1) {
    // TODO: Implement setNumberOfKey
}

bool Key::isDigitalPadlock() {
    // TODO: Implement isDigitalPadlock
    return false;
}

void Key::setDigitalPadlock(bool var1) {
    // TODO: Implement setDigitalPadlock
}

} // namespace types
} // namespace inventory
} // namespace zombie
