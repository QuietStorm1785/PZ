#include "zombie/inventory/types/KeyRing.h"

namespace zombie {
namespace inventory {
namespace types {

public
KeyRing::KeyRing(const std::string &module, const std::string &name,
                 const std::string &type, const std::string &tex) {
  // TODO: Implement KeyRing
  return nullptr;
}

int KeyRing::getSaveType() {
  // TODO: Implement getSaveType
  return 0;
}

void KeyRing::addKey(Key key) {
  // TODO: Implement addKey
}

bool KeyRing::containsKeyId(int keyId) {
  // TODO: Implement containsKeyId
  return false;
}

std::string KeyRing::getCategory() {
  // TODO: Implement getCategory
  return "";
}

void KeyRing::setKeys(ArrayList<Key> _keys) {
  // TODO: Implement setKeys
}

} // namespace types
} // namespace inventory
} // namespace zombie
