#include "zombie/characters/NetworkCharacterAI.h"

namespace zombie {
namespace characters {

bool NetworkCharacterAI::removeEldestEntry(String > var1) {
  // TODO: Implement removeEldestEntry
  return false;
}

public
NetworkCharacterAI::NetworkCharacterAI(IsoGameCharacter _character) {
  // TODO: Implement NetworkCharacterAI
  return nullptr;
}

void NetworkCharacterAI::reset() {
  // TODO: Implement reset
}

void NetworkCharacterAI::setLocal(bool _wasLocal) {
  // TODO: Implement setLocal
}

bool NetworkCharacterAI::wasLocal() {
  // TODO: Implement wasLocal
  return false;
}

void NetworkCharacterAI::clearTeleportDebug() {
  // TODO: Implement clearTeleportDebug
}

void NetworkCharacterAI::setTeleportDebug(
    NetworkTeleport.NetworkTeleportDebug _teleportDebug) {
  // TODO: Implement setTeleportDebug
}

void NetworkCharacterAI::addTeleportData(int time,
                                         const std::string &prediction) {
  // TODO: Implement addTeleportData
}

void NetworkCharacterAI::processDeadBody() {
  // TODO: Implement processDeadBody
}

void NetworkCharacterAI::setDeadBody(DeadCharacterPacket packet) {
  // TODO: Implement setDeadBody
}

bool NetworkCharacterAI::isSetDeadBody() {
  // TODO: Implement isSetDeadBody
  return false;
}

void NetworkCharacterAI::setPerformingAction(const std::string &animation) {
  // TODO: Implement setPerformingAction
}

std::string NetworkCharacterAI::getPerformingAction() {
  // TODO: Implement getPerformingAction
  return "";
}

void NetworkCharacterAI::setAction(BaseAction _action) {
  // TODO: Implement setAction
}

BaseAction NetworkCharacterAI::getAction() {
  // TODO: Implement getAction
  return nullptr;
}

void NetworkCharacterAI::startAction() {
  // TODO: Implement startAction
}

void NetworkCharacterAI::stopAction() {
  // TODO: Implement stopAction
}

void NetworkCharacterAI::setOverride(bool override,
                                     const std::string &primaryHandModel,
                                     const std::string &secondaryHandModel) {
  // TODO: Implement setOverride
}

void NetworkCharacterAI::processVehicleHit() {
  // TODO: Implement processVehicleHit
}

void NetworkCharacterAI::setVehicleHit(VehicleHitPacket packet) {
  // TODO: Implement setVehicleHit
}

bool NetworkCharacterAI::isSetVehicleHit() {
  // TODO: Implement isSetVehicleHit
  return false;
}

void NetworkCharacterAI::resetVehicleHitTimeout() {
  // TODO: Implement resetVehicleHitTimeout
}

bool NetworkCharacterAI::isVehicleHitTimeout() {
  // TODO: Implement isVehicleHitTimeout
  return false;
}

void NetworkCharacterAI::updateHitVehicle() {
  // TODO: Implement updateHitVehicle
}

bool NetworkCharacterAI::isCollisionEnabled() {
  // TODO: Implement isCollisionEnabled
  return false;
}

bool NetworkCharacterAI::isNoCollisionTimeout() {
  // TODO: Implement isNoCollisionTimeout
  return false;
}

void NetworkCharacterAI::setNoCollision(long interval) {
  // TODO: Implement setNoCollision
}

bool NetworkCharacterAI::checkPosition(UdpConnection connection,
                                       IsoGameCharacter _character, float x,
                                       float y) {
  // TODO: Implement checkPosition
  return false;
}

void NetworkCharacterAI::resetSpeedLimiter() {
  // TODO: Implement resetSpeedLimiter
}

float NetworkCharacterAI::getSpeed() {
  // TODO: Implement getSpeed
  return 0;
}

bool NetworkCharacterAI::isVehicle() {
  // TODO: Implement isVehicle
  return false;
}

void NetworkCharacterAI::set(float arg0, float arg1, bool arg2) {
  // TODO: Implement set
}

void NetworkCharacterAI::reset() {
  // TODO: Implement reset
}

std::string NetworkCharacterAI::getDescription() {
  // TODO: Implement getDescription
  return "";
}

} // namespace characters
} // namespace zombie
