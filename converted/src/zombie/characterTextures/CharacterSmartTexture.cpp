#include "zombie/characterTextures/CharacterSmartTexture.h"

namespace zombie {
namespace characterTextures {

void CharacterSmartTexture::setBlood(BloodBodyPartType bodyPart,
                                     float intensity) {
  // TODO: Implement setBlood
}

void CharacterSmartTexture::setDirt(BloodBodyPartType bodyPart,
                                    float intensity) {
  // TODO: Implement setDirt
}

void CharacterSmartTexture::removeBlood() {
  // TODO: Implement removeBlood
}

void CharacterSmartTexture::removeBlood(BloodBodyPartType bodyPart) {
  // TODO: Implement removeBlood
}

float CharacterSmartTexture::addBlood(BloodBodyPartType bodyPart,
                                      float intensity, IsoGameCharacter chr) {
  // TODO: Implement addBlood
  return 0;
}

float CharacterSmartTexture::addDirt(BloodBodyPartType bodyPart,
                                     float intensity, IsoGameCharacter chr) {
  // TODO: Implement addDirt
  return 0;
}

void CharacterSmartTexture::addShirtDecal(const std::string &dec) {
  // TODO: Implement addShirtDecal
}

} // namespace characterTextures
} // namespace zombie
