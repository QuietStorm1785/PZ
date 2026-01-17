#include "zombie/characters/Safety.h"

namespace zombie {
namespace characters {

public
Safety::Safety() {
  // TODO: Implement Safety
  return nullptr;
}

public
Safety::Safety(IsoGameCharacter _character) {
  // TODO: Implement Safety
  return nullptr;
}

void Safety::copyFrom(Safety other) {
  // TODO: Implement copyFrom
}

void *Safety::getCharacter() {
  // TODO: Implement getCharacter
  return nullptr;
}

bool Safety::isEnabled() {
  // TODO: Implement isEnabled
  return false;
}

void Safety::setEnabled(bool _enabled) {
  // TODO: Implement setEnabled
}

bool Safety::isLast() {
  // TODO: Implement isLast
  return false;
}

void Safety::setLast(bool _last) {
  // TODO: Implement setLast
}

float Safety::getCooldown() {
  // TODO: Implement getCooldown
  return 0;
}

void Safety::setCooldown(float _cooldown) {
  // TODO: Implement setCooldown
}

float Safety::getToggle() {
  // TODO: Implement getToggle
  return 0;
}

void Safety::setToggle(float _toggle) {
  // TODO: Implement setToggle
}

bool Safety::isToggleAllowed() {
  // TODO: Implement isToggleAllowed
  return false;
}

void Safety::toggleSafety() {
  // TODO: Implement toggleSafety
}

void Safety::load(ByteBuffer input, int WorldVersion) {
  // TODO: Implement load
}

void Safety::save(ByteBuffer output) {
  // TODO: Implement save
}

std::string Safety::getDescription() {
  // TODO: Implement getDescription
  return "";
}

} // namespace characters
} // namespace zombie
