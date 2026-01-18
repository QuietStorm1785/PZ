#include "zombie/characterTextures/ItemSmartTexture.h"

namespace zombie {
namespace characterTextures {

public
ItemSmartTexture::ItemSmartTexture(const std::string &tex) {
  // TODO: Implement ItemSmartTexture
  return nullptr;
}

public
ItemSmartTexture::ItemSmartTexture(const std::string &tex, float hue) {
  // TODO: Implement ItemSmartTexture
  return nullptr;
}

void ItemSmartTexture::setDenimPatches(BloodBodyPartType bodyPart) {
  // TODO: Implement setDenimPatches
}

void ItemSmartTexture::setLeatherPatches(BloodBodyPartType bodyPart) {
  // TODO: Implement setLeatherPatches
}

void ItemSmartTexture::setBasicPatches(BloodBodyPartType bodyPart) {
  // TODO: Implement setBasicPatches
}

void ItemSmartTexture::setBlood(const std::string &tex,
                                BloodBodyPartType bodyPart, float intensity) {
  // TODO: Implement setBlood
}

void ItemSmartTexture::setBlood(const std::string &tex, const std::string &mask,
                                float intensity, int category) {
  // TODO: Implement setBlood
}

float ItemSmartTexture::addBlood(const std::string &tex,
                                 BloodBodyPartType bodyPart, float intensity) {
  // TODO: Implement addBlood
  return 0;
}

float ItemSmartTexture::addDirt(const std::string &tex,
                                BloodBodyPartType bodyPart, float intensity) {
  // TODO: Implement addDirt
  return 0;
}

float ItemSmartTexture::addBlood(const std::string &tex,
                                 const std::string &mask, float intensity,
                                 int category) {
  // TODO: Implement addBlood
  return 0;
}

float ItemSmartTexture::addDirt(const std::string &tex, const std::string &mask,
                                float intensity, int category) {
  // TODO: Implement addDirt
  return 0;
}

void ItemSmartTexture::removeBlood() {
  // TODO: Implement removeBlood
}

void ItemSmartTexture::removeDirt() {
  // TODO: Implement removeDirt
}

void ItemSmartTexture::removeBlood(BloodBodyPartType bodyPart) {
  // TODO: Implement removeBlood
}

void ItemSmartTexture::removeDirt(BloodBodyPartType bodyPart) {
  // TODO: Implement removeDirt
}

std::string ItemSmartTexture::getTexName() {
  // TODO: Implement getTexName
  return "";
}

} // namespace characterTextures
} // namespace zombie
