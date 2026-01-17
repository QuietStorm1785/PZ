#include "zombie/inventory/types/Moveable.h"

namespace zombie {
namespace inventory {
namespace types {

public
Moveable::Moveable(const std::string &module, const std::string &name,
                   const std::string &type, const std::string &tex) {
  // TODO: Implement Moveable
  return nullptr;
}

public
Moveable::Moveable(const std::string &module, const std::string &name,
                   const std::string &type, Item item) {
  // TODO: Implement Moveable
  return nullptr;
}

std::string Moveable::getName() {
  // TODO: Implement getName
  return "";
}

std::string Moveable::getDisplayName() {
  // TODO: Implement getDisplayName
  return "";
}

bool Moveable::CanBeDroppedOnFloor() {
  // TODO: Implement CanBeDroppedOnFloor
  return false;
}

std::string Moveable::getMovableFullName() {
  // TODO: Implement getMovableFullName
  return "";
}

std::string Moveable::getCustomNameFull() {
  // TODO: Implement getCustomNameFull
  return "";
}

bool Moveable::isMultiGridAnchor() {
  // TODO: Implement isMultiGridAnchor
  return false;
}

IsoSpriteGrid Moveable::getSpriteGrid() {
  // TODO: Implement getSpriteGrid
  return nullptr;
}

std::string Moveable::getWorldSprite() {
  // TODO: Implement getWorldSprite
  return "";
}

bool Moveable::ReadFromWorldSprite(const std::string &sprite) {
  // TODO: Implement ReadFromWorldSprite
  return false;
}

bool Moveable::isLight() {
  // TODO: Implement isLight
  return false;
}

void Moveable::setLight(bool _isLight) {
  // TODO: Implement setLight
}

bool Moveable::isLightUseBattery() {
  // TODO: Implement isLightUseBattery
  return false;
}

void Moveable::setLightUseBattery(bool _lightUseBattery) {
  // TODO: Implement setLightUseBattery
}

bool Moveable::isLightHasBattery() {
  // TODO: Implement isLightHasBattery
  return false;
}

void Moveable::setLightHasBattery(bool _lightHasBattery) {
  // TODO: Implement setLightHasBattery
}

std::string Moveable::getLightBulbItem() {
  // TODO: Implement getLightBulbItem
  return "";
}

void Moveable::setLightBulbItem(const std::string &_lightBulbItem) {
  // TODO: Implement setLightBulbItem
}

float Moveable::getLightPower() {
  // TODO: Implement getLightPower
  return 0;
}

void Moveable::setLightPower(float _lightPower) {
  // TODO: Implement setLightPower
}

float Moveable::getLightDelta() {
  // TODO: Implement getLightDelta
  return 0;
}

void Moveable::setLightDelta(float _lightDelta) {
  // TODO: Implement setLightDelta
}

float Moveable::getLightR() {
  // TODO: Implement getLightR
  return 0;
}

void Moveable::setLightR(float _lightR) {
  // TODO: Implement setLightR
}

float Moveable::getLightG() {
  // TODO: Implement getLightG
  return 0;
}

void Moveable::setLightG(float _lightG) {
  // TODO: Implement setLightG
}

float Moveable::getLightB() {
  // TODO: Implement getLightB
  return 0;
}

void Moveable::setLightB(float _lightB) {
  // TODO: Implement setLightB
}

int Moveable::getSaveType() {
  // TODO: Implement getSaveType
  return 0;
}

void Moveable::save(ByteBuffer output, bool net) {
  // TODO: Implement save
}

void Moveable::load(ByteBuffer input, int WorldVersion) {
  // TODO: Implement load
}

void Moveable::setWorldSprite(const std::string &WorldSprite) {
  // TODO: Implement setWorldSprite
}

} // namespace types
} // namespace inventory
} // namespace zombie
