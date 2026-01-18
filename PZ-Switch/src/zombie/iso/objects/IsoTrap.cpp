#include "zombie/iso/objects/IsoTrap.h"

namespace zombie {
namespace iso {
namespace objects {

public
IsoTrap::IsoTrap(IsoCell cell) {
 // TODO: Implement IsoTrap
 return nullptr;
}

public
IsoTrap::IsoTrap(HandWeapon _weapon, IsoCell cell, IsoGridSquare sq) {
 // TODO: Implement IsoTrap
 return nullptr;
}

void IsoTrap::initSprite(HandWeapon weaponx) {
 // TODO: Implement initSprite
}

void IsoTrap::update() {
 // TODO: Implement update
}

void IsoTrap::updateSounds() {
 // TODO: Implement updateSounds
}

void IsoTrap::render(float x, float y, float z, ColorInfo col, bool bDoChild,
 bool bWallLightingPass, Shader shader) {
 // TODO: Implement render
}

void IsoTrap::triggerExplosion(bool sensor) {
 // TODO: Implement triggerExplosion
}

BaseSoundEmitter IsoTrap::getOrCreateEmitter() {
 // TODO: Implement getOrCreateEmitter
 return nullptr;
}

void IsoTrap::playExplosionSound() {
 // TODO: Implement playExplosionSound
}

void IsoTrap::load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 // TODO: Implement load
}

void IsoTrap::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 // TODO: Implement save
}

void IsoTrap::addToWorld() {
 // TODO: Implement addToWorld
}

void IsoTrap::removeFromWorld() {
 // TODO: Implement removeFromWorld
}

int IsoTrap::getTimerBeforeExplosion() {
 // TODO: Implement getTimerBeforeExplosion
 return 0;
}

void IsoTrap::setTimerBeforeExplosion(int _timerBeforeExplosion) {
 // TODO: Implement setTimerBeforeExplosion
}

int IsoTrap::getSensorRange() {
 // TODO: Implement getSensorRange
 return 0;
}

void IsoTrap::setSensorRange(int _sensorRange) {
 // TODO: Implement setSensorRange
}

int IsoTrap::getFireRange() {
 // TODO: Implement getFireRange
 return 0;
}

void IsoTrap::setFireRange(int _fireRange) {
 // TODO: Implement setFireRange
}

int IsoTrap::getFirePower() {
 // TODO: Implement getFirePower
 return 0;
}

void IsoTrap::setFirePower(int _firePower) {
 // TODO: Implement setFirePower
}

int IsoTrap::getExplosionPower() {
 // TODO: Implement getExplosionPower
 return 0;
}

void IsoTrap::setExplosionPower(int _explosionPower) {
 // TODO: Implement setExplosionPower
}

int IsoTrap::getNoiseDuration() {
 // TODO: Implement getNoiseDuration
 return 0;
}

void IsoTrap::setNoiseDuration(int _noiseDuration) {
 // TODO: Implement setNoiseDuration
}

int IsoTrap::getNoiseRange() {
 // TODO: Implement getNoiseRange
 return 0;
}

void IsoTrap::setNoiseRange(int _noiseRange) {
 // TODO: Implement setNoiseRange
}

int IsoTrap::getExplosionRange() {
 // TODO: Implement getExplosionRange
 return 0;
}

void IsoTrap::setExplosionRange(int _explosionRange) {
 // TODO: Implement setExplosionRange
}

int IsoTrap::getSmokeRange() {
 // TODO: Implement getSmokeRange
 return 0;
}

void IsoTrap::setSmokeRange(int _smokeRange) {
 // TODO: Implement setSmokeRange
}

float IsoTrap::getExtraDamage() {
 // TODO: Implement getExtraDamage
 return 0;
}

void IsoTrap::setExtraDamage(float _extraDamage) {
 // TODO: Implement setExtraDamage
}

std::string IsoTrap::getObjectName() {
 // TODO: Implement getObjectName
 return "";
}

int IsoTrap::getRemoteControlID() {
 // TODO: Implement getRemoteControlID
 return 0;
}

void IsoTrap::setRemoteControlID(int _remoteControlID) {
 // TODO: Implement setRemoteControlID
}

std::string IsoTrap::getCountDownSound() {
 // TODO: Implement getCountDownSound
 return "";
}

void IsoTrap::setCountDownSound(const std::string &sound) {
 // TODO: Implement setCountDownSound
}

std::string IsoTrap::getExplosionSound() {
 // TODO: Implement getExplosionSound
 return "";
}

void IsoTrap::setExplosionSound(const std::string &_explosionSound) {
 // TODO: Implement setExplosionSound
}

InventoryItem IsoTrap::getItem() {
 // TODO: Implement getItem
 return nullptr;
}

void IsoTrap::triggerRemote(IsoPlayer player, int remoteID, int range) {
 // TODO: Implement triggerRemote
}

bool IsoTrap::isInstantExplosion() {
 // TODO: Implement isInstantExplosion
 return false;
}

} // namespace objects
} // namespace iso
} // namespace zombie
