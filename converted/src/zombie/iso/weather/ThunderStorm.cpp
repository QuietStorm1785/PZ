#include "zombie/iso/weather/ThunderStorm.h"

namespace zombie {
namespace iso {
namespace weather {

public
ThunderStorm::ThunderStorm(ClimateManager climmgr) {
  // TODO: Implement ThunderStorm
  return nullptr;
}

bool ThunderStorm::HasActiveThunderClouds() {
  // TODO: Implement HasActiveThunderClouds
  return false;
}

void ThunderStorm::noise(const std::string &s) {
  // TODO: Implement noise
}

void ThunderStorm::stopAllClouds() {
  // TODO: Implement stopAllClouds
}

void ThunderStorm::stopCloud(int id) {
  // TODO: Implement stopCloud
}

float ThunderStorm::addToAngle(float float0, float float1) {
  // TODO: Implement addToAngle
  return 0;
}

int ThunderStorm::getMapDiagonal() {
  // TODO: Implement getMapDiagonal
  return 0;
}

void ThunderStorm::startThunderCloud(float str, float angle, float radius,
                                     float eventFreq, float thunderRatio,
                                     double duration, bool targetRandomPlayer) {
  // TODO: Implement startThunderCloud
}

void ThunderStorm::update(double currentTime) {
  // TODO: Implement update
}

void ThunderStorm::applyLightningForPlayer(
    RenderSettings.PlayerRenderSettings renderSettings, int plrIndex,
    IsoPlayer player) {
  // TODO: Implement applyLightningForPlayer
}

bool ThunderStorm::isModifyingNight() {
  // TODO: Implement isModifyingNight
  return false;
}

void ThunderStorm::triggerThunderEvent(int x, int y, bool doStrike,
                                       bool doLightning, bool doRumble) {
  // TODO: Implement triggerThunderEvent
}

void ThunderStorm::writeNetThunderEvent(ByteBuffer output) {
  // TODO: Implement writeNetThunderEvent
}

void ThunderStorm::readNetThunderEvent(ByteBuffer input) {
  // TODO: Implement readNetThunderEvent
}

void ThunderStorm::enqueueThunderEvent(int x, int y, bool doStrike,
                                       bool doLightning, bool doRumble) {
  // TODO: Implement enqueueThunderEvent
}

int ThunderStorm::GetDistance(int int2, int int0, int int3, int int1) {
  // TODO: Implement GetDistance
  return 0;
}

void ThunderStorm::save(DataOutputStream output) {
  // TODO: Implement save
}

void ThunderStorm::load(DataInputStream input) {
  // TODO: Implement load
}

int ThunderStorm::getCurrentX() {
  // TODO: Implement getCurrentX
  return 0;
}

int ThunderStorm::getCurrentY() {
  // TODO: Implement getCurrentY
  return 0;
}

float ThunderStorm::getRadius() {
  // TODO: Implement getRadius
  return 0;
}

bool ThunderStorm::isRunning() {
  // TODO: Implement isRunning
  return false;
}

float ThunderStorm::getStrength() {
  // TODO: Implement getStrength
  return 0;
}

double ThunderStorm::lifeTime() {
  // TODO: Implement lifeTime
  return 0;
}

void ThunderStorm::setCenter(int centerX, int centerY, float _angle) {
  // TODO: Implement setCenter
}

} // namespace weather
} // namespace iso
} // namespace zombie
