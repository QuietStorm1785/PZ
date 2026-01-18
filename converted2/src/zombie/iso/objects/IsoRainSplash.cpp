#include "zombie/iso/objects/IsoRainSplash.h"

namespace zombie {
namespace iso {
namespace objects {

bool IsoRainSplash::Serialize() {
  // TODO: Implement Serialize
  return false;
}

public
IsoRainSplash::IsoRainSplash(IsoCell cell, IsoGridSquare gridSquare) {
  // TODO: Implement IsoRainSplash
  return nullptr;
}

std::string IsoRainSplash::getObjectName() {
  // TODO: Implement getObjectName
  return "";
}

bool IsoRainSplash::HasTooltip() {
  // TODO: Implement HasTooltip
  return false;
}

bool IsoRainSplash::TestCollide(IsoMovingObject obj,
                                IsoGridSquare PassedObjectSquare) {
  // TODO: Implement TestCollide
  return false;
}

void IsoRainSplash::ChangeTintMod(ColorInfo NewTintMod) {
  // TODO: Implement ChangeTintMod
}

void IsoRainSplash::update() {
  // TODO: Implement update
}

void IsoRainSplash::Reset(IsoGridSquare square) {
  // TODO: Implement Reset
}

} // namespace objects
} // namespace iso
} // namespace zombie
