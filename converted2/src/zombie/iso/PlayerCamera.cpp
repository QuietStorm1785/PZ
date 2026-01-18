#include "zombie/iso/PlayerCamera.h"

namespace zombie {
namespace iso {

public
PlayerCamera::PlayerCamera(int _playerIndex) {
  // TODO: Implement PlayerCamera
  return nullptr;
}

void PlayerCamera::center() {
  // TODO: Implement center
}

void PlayerCamera::update() {
  // TODO: Implement update
}

void PlayerCamera::returnToCenter(float float0) {
  // TODO: Implement returnToCenter
}

float PlayerCamera::getOffX() {
  // TODO: Implement getOffX
  return 0;
}

float PlayerCamera::getOffY() {
  // TODO: Implement getOffY
  return 0;
}

float PlayerCamera::getTOffX() {
  // TODO: Implement getTOffX
  return 0;
}

float PlayerCamera::getTOffY() {
  // TODO: Implement getTOffY
  return 0;
}

float PlayerCamera::getLastOffX() {
  // TODO: Implement getLastOffX
  return 0;
}

float PlayerCamera::getLastOffY() {
  // TODO: Implement getLastOffY
  return 0;
}

float PlayerCamera::XToIso(float screenX, float screenY, float floor) {
  // TODO: Implement XToIso
  return 0;
}

float PlayerCamera::YToIso(float screenX, float screenY, float floor) {
  // TODO: Implement YToIso
  return 0;
}

float PlayerCamera::YToScreenExact(float objectX, float objectY, float objectZ,
                                   int screenZ) {
  // TODO: Implement YToScreenExact
  return 0;
}

float PlayerCamera::XToScreenExact(float objectX, float objectY, float objectZ,
                                   int screenZ) {
  // TODO: Implement XToScreenExact
  return 0;
}

void PlayerCamera::copyFrom(PlayerCamera other) {
  // TODO: Implement copyFrom
}

void PlayerCamera::initFromIsoCamera(int _playerIndex) {
  // TODO: Implement initFromIsoCamera
}

} // namespace iso
} // namespace zombie
