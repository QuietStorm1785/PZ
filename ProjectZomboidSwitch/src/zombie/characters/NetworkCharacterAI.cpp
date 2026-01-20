#include <string>
#include "zombie\characters/NetworkCharacterAI.h"

namespace zombie {
namespace characters {

public NetworkCharacterAI::NetworkCharacterAI(IsoGameCharacter var1) {
    // TODO: Implement NetworkCharacterAI
    return nullptr;
}

void NetworkCharacterAI::reset() {
    // TODO: Implement reset
}

void NetworkCharacterAI::setLocal(bool var1) {
    // TODO: Implement setLocal
}

bool NetworkCharacterAI::wasLocal() {
    // TODO: Implement wasLocal
    return false;
}

NetworkTeleportDebug NetworkCharacterAI::getTeleportDebug() {
    // TODO: Implement getTeleportDebug
    return nullptr;
}

void NetworkCharacterAI::clearTeleportDebug() {
    // TODO: Implement clearTeleportDebug
}

void NetworkCharacterAI::setTeleportDebug(NetworkTeleportDebug var1) {
    // TODO: Implement setTeleportDebug
}

void NetworkCharacterAI::addTeleportData(int var1, const std::string& var2) {
    // TODO: Implement addTeleportData
}

void NetworkCharacterAI::processDeadBody() {
    // TODO: Implement processDeadBody
}

void NetworkCharacterAI::setDeadBody(DeadCharacterPacket var1) {
    // TODO: Implement setDeadBody
}

bool NetworkCharacterAI::isSetDeadBody() {
    // TODO: Implement isSetDeadBody
    return false;
}

void NetworkCharacterAI::setPerformingAction(const std::string& var1) {
    // TODO: Implement setPerformingAction
}

std::string NetworkCharacterAI::getPerformingAction() {
    // TODO: Implement getPerformingAction
    return "";
}

void NetworkCharacterAI::setAction(BaseAction var1) {
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

void NetworkCharacterAI::setOverride(bool var1, const std::string& var2, const std::string& var3) {
    // TODO: Implement setOverride
}

void NetworkCharacterAI::processVehicleHit() {
    // TODO: Implement processVehicleHit
}

void NetworkCharacterAI::setVehicleHit(VehicleHitPacket var1) {
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

void NetworkCharacterAI::setNoCollision(long var1) {
    // TODO: Implement setNoCollision
}

bool NetworkCharacterAI::checkPosition(UdpConnection var1, IsoGameCharacter var2, float var3, float var4) {
    // TODO: Implement checkPosition
    return false;
}

void NetworkCharacterAI::resetSpeedLimiter() {
    // TODO: Implement resetSpeedLimiter
}

} // namespace characters
} // namespace zombie
