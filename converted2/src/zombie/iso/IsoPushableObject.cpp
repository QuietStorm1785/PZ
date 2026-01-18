#include "zombie/iso/IsoPushableObject.h"

namespace zombie {
namespace iso {

public
IsoPushableObject::IsoPushableObject(IsoCell cell) {
  // TODO: Implement IsoPushableObject
  return nullptr;
}

public
IsoPushableObject::IsoPushableObject(IsoCell cell, int x, int y, int z) {
  // TODO: Implement IsoPushableObject
  return nullptr;
}

public
IsoPushableObject::IsoPushableObject(IsoCell cell, IsoGridSquare square,
                                     IsoSprite spr) {
  // TODO: Implement IsoPushableObject
  return nullptr;
}

std::string IsoPushableObject::getObjectName() {
  // TODO: Implement getObjectName
  return "";
}

void IsoPushableObject::update() {
  // TODO: Implement update
}

void IsoPushableObject::load(ByteBuffer input, int WorldVersion,
                             bool IS_DEBUG_SAVE) {
  // TODO: Implement load
}

void IsoPushableObject::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
  // TODO: Implement save
}

float IsoPushableObject::getWeight(float x, float y) {
  // TODO: Implement getWeight
  return 0;
}

bool IsoPushableObject::Serialize() {
  // TODO: Implement Serialize
  return false;
}

void IsoPushableObject::DoCollideNorS() {
  // TODO: Implement DoCollideNorS
}

void IsoPushableObject::DoCollideWorE() {
  // TODO: Implement DoCollideWorE
}

} // namespace iso
} // namespace zombie
