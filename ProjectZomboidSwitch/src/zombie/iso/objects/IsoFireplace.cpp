#include <string>
#include "zombie/iso/objects/IsoFireplace.h"

namespace zombie {
namespace iso {
namespace objects {

public IsoFireplace::IsoFireplace(IsoCell var1) {
    // TODO: Implement IsoFireplace
    return nullptr;
}

public IsoFireplace::IsoFireplace(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
    // TODO: Implement IsoFireplace
    return nullptr;
}

std::string IsoFireplace::getObjectName() {
    // TODO: Implement getObjectName
    return "";
}

Vector2 IsoFireplace::getFacingPosition(Vector2 var1) {
    // TODO: Implement getFacingPosition
    return nullptr;
}

void IsoFireplace::load(ByteBuffer var1, int var2, bool var3) {
    // TODO: Implement load
}

void IsoFireplace::save(ByteBuffer var1, bool var2) {
    // TODO: Implement save
}

void IsoFireplace::setFuelAmount(int var1) {
    // TODO: Implement setFuelAmount
}

int IsoFireplace::getFuelAmount() {
    // TODO: Implement getFuelAmount
    return 0;
}

void IsoFireplace::addFuel(int var1) {
    // TODO: Implement addFuel
}

int IsoFireplace::useFuel(int var1) {
    // TODO: Implement useFuel
    return 0;
}

bool IsoFireplace::hasFuel() {
    // TODO: Implement hasFuel
    return false;
}

void IsoFireplace::setLit(bool var1) {
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

void IsoFireplace::render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
    // TODO: Implement render
}

void IsoFireplace::saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
    // TODO: Implement saveChange
}

void IsoFireplace::loadChange(const std::string& var1, ByteBuffer var2) {
    // TODO: Implement loadChange
}

} // namespace objects
} // namespace iso
} // namespace zombie
