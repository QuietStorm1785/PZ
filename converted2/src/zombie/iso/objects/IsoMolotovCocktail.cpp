#include "zombie/iso/objects/IsoMolotovCocktail.h"

namespace zombie {
namespace iso {
namespace objects {

std::string IsoMolotovCocktail::getObjectName() {
  // TODO: Implement getObjectName
  return "";
}

public
IsoMolotovCocktail::IsoMolotovCocktail(IsoCell cell) {
  // TODO: Implement IsoMolotovCocktail
  return nullptr;
}

public
IsoMolotovCocktail::IsoMolotovCocktail(IsoCell cell, float x, float y, float z,
                                       float xvel, float yvel,
                                       HandWeapon _weapon,
                                       IsoGameCharacter _character) {
  // TODO: Implement IsoMolotovCocktail
  return nullptr;
}

void IsoMolotovCocktail::collideCharacter() {
  // TODO: Implement collideCharacter
}

void IsoMolotovCocktail::collideGround() {
  // TODO: Implement collideGround
}

void IsoMolotovCocktail::collideWall() {
  // TODO: Implement collideWall
}

void IsoMolotovCocktail::update() {
  // TODO: Implement update
}

void IsoMolotovCocktail::render(float x, float y, float z, ColorInfo info,
                                bool bDoAttached, bool bWallLightingPass,
                                Shader shader) {
  // TODO: Implement render
}

void IsoMolotovCocktail::Explode() {
  // TODO: Implement Explode
}

} // namespace objects
} // namespace iso
} // namespace zombie
