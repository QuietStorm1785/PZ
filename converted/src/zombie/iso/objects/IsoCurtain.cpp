#include "zombie/iso/objects/IsoCurtain.h"

namespace zombie {
namespace iso {
namespace objects {

void IsoCurtain::removeSheet(IsoGameCharacter chr) {
 // TODO: Implement removeSheet
}

public IsoCurtain::IsoCurtain(IsoCell cell, IsoGridSquare gridSquare, IsoSprite gid, bool _north, bool spriteclosed) {
 // TODO: Implement IsoCurtain
 return nullptr;
}

public IsoCurtain::IsoCurtain(IsoCell cell, IsoGridSquare gridSquare, const std::string& gid, bool _north) {
 // TODO: Implement IsoCurtain
 return nullptr;
}

public IsoCurtain::IsoCurtain(IsoCell cell) {
 // TODO: Implement IsoCurtain
 return nullptr;
}

std::string IsoCurtain::getObjectName() {
 // TODO: Implement getObjectName
 return "";
}

Vector2 IsoCurtain::getFacingPosition(Vector2 pos) {
 // TODO: Implement getFacingPosition
 return nullptr;
}

void IsoCurtain::load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 // TODO: Implement load
}

void IsoCurtain::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
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

bool IsoCurtain::onMouseLeftClick(int x, int y) {
 // TODO: Implement onMouseLeftClick
 return false;
}

bool IsoCurtain::canInteractWith(IsoGameCharacter chr) {
 // TODO: Implement canInteractWith
 return false;
}

IsoGridSquare IsoCurtain::getOppositeSquare() {
 // TODO: Implement getOppositeSquare
 return nullptr;
}

bool IsoCurtain::isAdjacentToSquare(IsoGridSquare square1, IsoGridSquare square2) {
 // TODO: Implement isAdjacentToSquare
 return false;
}

bool IsoCurtain::isAdjacentToSquare(IsoGridSquare square2) {
 // TODO: Implement isAdjacentToSquare
 return false;
}

void IsoCurtain::ToggleDoor(IsoGameCharacter chr) {
 // TODO: Implement ToggleDoor
}

void IsoCurtain::ToggleDoorSilent() {
 // TODO: Implement ToggleDoorSilent
}

void IsoCurtain::render(float x, float y, float z, ColorInfo col, bool bDoAttached, bool bWallLightingPass, Shader shader) {
 // TODO: Implement render
}

void IsoCurtain::syncIsoObjectSend(ByteBufferWriter b) {
 // TODO: Implement syncIsoObjectSend
}

void IsoCurtain::syncIsoObject(bool bRemote, uint8_t val, UdpConnection source, ByteBuffer bb) {
 // TODO: Implement syncIsoObject
}

void IsoCurtain::syncIsoObject(bool bRemote, uint8_t val, UdpConnection source) {
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

bool IsoCurtain::isSheet(IsoObject curtain) {
 // TODO: Implement isSheet
 return false;
}

} // namespace objects
} // namespace iso
} // namespace zombie
