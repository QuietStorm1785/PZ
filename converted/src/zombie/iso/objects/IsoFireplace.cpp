#include "zombie/iso/objects/IsoFireplace.h"

namespace zombie {
namespace iso {
namespace objects {

public IsoFireplace::IsoFireplace(IsoCell cell) {
 // TODO: Implement IsoFireplace
 return nullptr;
}

public IsoFireplace::IsoFireplace(IsoCell cell, IsoGridSquare sq, IsoSprite gid) {
 // TODO: Implement IsoFireplace
 return nullptr;
}

std::string IsoFireplace::getObjectName() {
 // TODO: Implement getObjectName
 return "";
}

Vector2 IsoFireplace::getFacingPosition(Vector2 pos) {
 // TODO: Implement getFacingPosition
 return nullptr;
}

void IsoFireplace::load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 // TODO: Implement load
}

void IsoFireplace::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 // TODO: Implement save
}

void IsoFireplace::setFuelAmount(int units) {
 // TODO: Implement setFuelAmount
}

int IsoFireplace::getFuelAmount() {
 // TODO: Implement getFuelAmount
 return 0;
}

void IsoFireplace::addFuel(int units) {
 // TODO: Implement addFuel
}

int IsoFireplace::useFuel(int amount) {
 // TODO: Implement useFuel
 return 0;
}

bool IsoFireplace::hasFuel() {
 // TODO: Implement hasFuel
 return false;
}

void IsoFireplace::setLit(bool lit) {
 // TODO: Implement setLit
}

bool IsoFireplace::isLit() {
 // TODO: Implement isLit
 return false;
}

bool IsoFireplace::isSmouldering() {
 // TODO: Implement isSmouldering
 return false;
}

void IsoFireplace::extinguish() {
 // TODO: Implement extinguish
}

float IsoFireplace::getTemperature() {
 // TODO: Implement getTemperature
 return 0;
}

void IsoFireplace::updateFuelSprite() {
 // TODO: Implement updateFuelSprite
}

void IsoFireplace::updateFireSprite() {
 // TODO: Implement updateFireSprite
}

int IsoFireplace::calcLightRadius() {
 // TODO: Implement calcLightRadius
 return 0;
}

void IsoFireplace::updateLightSource() {
 // TODO: Implement updateLightSource
}

void IsoFireplace::updateHeatSource() {
 // TODO: Implement updateHeatSource
}

void IsoFireplace::updateSound() {
 // TODO: Implement updateSound
}

void IsoFireplace::update() {
 // TODO: Implement update
}

void IsoFireplace::addToWorld() {
 // TODO: Implement addToWorld
}

void IsoFireplace::removeFromWorld() {
 // TODO: Implement removeFromWorld
}

void IsoFireplace::render(float x, float y, float z, ColorInfo col, bool bDoChild, bool bWallLightingPass, Shader shader) {
 // TODO: Implement render
}

void IsoFireplace::saveChange(const std::string& change, KahluaTable tbl, ByteBuffer bb) {
 // TODO: Implement saveChange
}

void IsoFireplace::loadChange(const std::string& change, ByteBuffer bb) {
 // TODO: Implement loadChange
}

} // namespace objects
} // namespace iso
} // namespace zombie
