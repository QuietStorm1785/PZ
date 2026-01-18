#include "zombie/inventory/types/Key.h"

namespace zombie {
namespace inventory {
namespace types {

public
Key::Key(const std::string &module, const std::string &name,
 const std::string &type, const std::string &tex) {
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

void Key::setHighlightDoors(int playerNum, InventoryItem item) {
 // TODO: Implement setHighlightDoors
}

int Key::getKeyId() {
 // TODO: Implement getKeyId
 return 0;
}

void Key::setKeyId(int _keyId) {
 // TODO: Implement setKeyId
}

std::string Key::getCategory() {
 // TODO: Implement getCategory
 return "";
}

void Key::save(ByteBuffer output, bool net) {
 // TODO: Implement save
}

void Key::load(ByteBuffer input, int WorldVersion) {
 // TODO: Implement load
}

bool Key::isPadlock() {
 // TODO: Implement isPadlock
 return false;
}

void Key::setPadlock(bool _padlock) {
 // TODO: Implement setPadlock
}

int Key::getNumberOfKey() {
 // TODO: Implement getNumberOfKey
 return 0;
}

void Key::setNumberOfKey(int _numberOfKey) {
 // TODO: Implement setNumberOfKey
}

bool Key::isDigitalPadlock() {
 // TODO: Implement isDigitalPadlock
 return false;
}

void Key::setDigitalPadlock(bool _digitalPadlock) {
 // TODO: Implement setDigitalPadlock
}

} // namespace types
} // namespace inventory
} // namespace zombie
