#include <cstdint>
#include <string>
#include "zombie\iso\objects/IsoCurtain.h"

namespace zombie {
namespace iso {
namespace objects {

void IsoCurtain::removeSheet(IsoGameCharacter var1) {
    // TODO: Implement removeSheet
}

public IsoCurtain::IsoCurtain(IsoCell var1, IsoGridSquare var2, IsoSprite var3, bool var4, bool var5) {
    // TODO: Implement IsoCurtain
    return nullptr;
}

public IsoCurtain::IsoCurtain(IsoCell var1, IsoGridSquare var2, const std::string& var3, bool var4) {
    // TODO: Implement IsoCurtain
    return nullptr;
}

public IsoCurtain::IsoCurtain(IsoCell var1) {
    // TODO: Implement IsoCurtain
    return nullptr;
}

std::string IsoCurtain::getObjectName() {
    // TODO: Implement getObjectName
    return "";
}

Vector2 IsoCurtain::getFacingPosition(Vector2 var1) {
    // TODO: Implement getFacingPosition
    return nullptr;
}

void IsoCurtain::load(ByteBuffer var1, int var2, bool var3) {
    // TODO: Implement load
}

void IsoCurtain::save(ByteBuffer var1, bool var2) {
    // TODO: Implement save
}

bool IsoCurtain::getNorth() {
    // TODO: Implement getNorth
    return false;
}

bool IsoCurtain::IsOpen() {
    // TODO: Implement IsOpen
    return false;
}

bool IsoCurtain::onMouseLeftClick(int var1, int var2) {
    // TODO: Implement onMouseLeftClick
    return false;
}

bool IsoCurtain::canInteractWith(IsoGameCharacter var1) {
    // TODO: Implement canInteractWith
    return false;
}

IsoGridSquare IsoCurtain::getOppositeSquare() {
    // TODO: Implement getOppositeSquare
    return nullptr;
}

bool IsoCurtain::isAdjacentToSquare(IsoGridSquare var1, IsoGridSquare var2) {
    // TODO: Implement isAdjacentToSquare
    return false;
}

bool IsoCurtain::isAdjacentToSquare(IsoGridSquare var1) {
    // TODO: Implement isAdjacentToSquare
    return false;
}

VisionResult IsoCurtain::TestVision(IsoGridSquare var1, IsoGridSquare var2) {
    // TODO: Implement TestVision
    return nullptr;
}

void IsoCurtain::ToggleDoor(IsoGameCharacter var1) {
    // TODO: Implement ToggleDoor
}

void IsoCurtain::ToggleDoorSilent() {
    // TODO: Implement ToggleDoorSilent
}

void IsoCurtain::render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
    // TODO: Implement render
}

void IsoCurtain::syncIsoObjectSend(ByteBufferWriter var1) {
    // TODO: Implement syncIsoObjectSend
}

void IsoCurtain::syncIsoObject(bool var1, uint8_t var2, UdpConnection var3, ByteBuffer var4) {
    // TODO: Implement syncIsoObject
}

void IsoCurtain::syncIsoObject(bool var1, uint8_t var2, UdpConnection var3) {
    // TODO: Implement syncIsoObject
}

IsoObject IsoCurtain::getObjectAttachedTo() {
    // TODO: Implement getObjectAttachedTo
    return nullptr;
}

std::string IsoCurtain::getSoundPrefix() {
    // TODO: Implement getSoundPrefix
    return "";
}

bool IsoCurtain::isSheet(IsoObject var0) {
    // TODO: Implement isSheet
    return false;
}

} // namespace objects
} // namespace iso
} // namespace zombie
