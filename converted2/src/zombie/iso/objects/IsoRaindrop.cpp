#include "zombie/iso/objects/IsoRaindrop.h"

namespace zombie {
namespace iso {
namespace objects {

bool IsoRaindrop::Serialize() {
  // TODO: Implement Serialize
  return false;
}

public
IsoRaindrop::IsoRaindrop(IsoCell cell, IsoGridSquare gridSquare, bool CanSee) {
  // TODO: Implement IsoRaindrop
  return nullptr;
}

bool IsoRaindrop::HasTooltip() {
  // TODO: Implement HasTooltip
  return false;
}

std::string IsoRaindrop::getObjectName() {
  // TODO: Implement getObjectName
  return "";
}

bool IsoRaindrop::TestCollide(IsoMovingObject obj,
                              IsoGridSquare PassedObjectSquare) {
  // TODO: Implement TestCollide
  return false;
}

void IsoRaindrop::ChangeTintMod(ColorInfo NewTintMod) {
  // TODO: Implement ChangeTintMod
}

void IsoRaindrop::update() {
  // TODO: Implement update
}

void IsoRaindrop::Reset(IsoGridSquare square, bool boolean0) {
  // TODO: Implement Reset
}

} // namespace objects
} // namespace iso
} // namespace zombie
