#include "zombie/iso/objects/interfaces/BarricadeAble.h"

namespace zombie {
namespace iso {
namespace objects {
namespace interfaces {

bool BarricadeAble::isBarricaded() {
  // TODO: Implement isBarricaded
  return false;
}

bool BarricadeAble::isBarricadeAllowed() {
  // TODO: Implement isBarricadeAllowed
  return false;
}

IsoBarricade BarricadeAble::getBarricadeOnSameSquare() {
  // TODO: Implement getBarricadeOnSameSquare
  return nullptr;
}

IsoBarricade BarricadeAble::getBarricadeOnOppositeSquare() {
  // TODO: Implement getBarricadeOnOppositeSquare
  return nullptr;
}

IsoBarricade BarricadeAble::getBarricadeForCharacter(IsoGameCharacter chr) {
  // TODO: Implement getBarricadeForCharacter
  return nullptr;
}

IsoBarricade
BarricadeAble::getBarricadeOppositeCharacter(IsoGameCharacter chr) {
  // TODO: Implement getBarricadeOppositeCharacter
  return nullptr;
}

IsoGridSquare BarricadeAble::getSquare() {
  // TODO: Implement getSquare
  return nullptr;
}

IsoGridSquare BarricadeAble::getOppositeSquare() {
  // TODO: Implement getOppositeSquare
  return nullptr;
}

bool BarricadeAble::getNorth() {
  // TODO: Implement getNorth
  return false;
}

} // namespace interfaces
} // namespace objects
} // namespace iso
} // namespace zombie
