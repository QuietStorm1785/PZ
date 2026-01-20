#include <cstdint>
#include <string>
#include "zombie\iso\objects/IsoWindow.h"

namespace zombie {
namespace iso {
namespace objects {

IsoCurtain IsoWindow::HasCurtains() {
    // TODO: Implement HasCurtains
    return nullptr;
}

IsoGridSquare IsoWindow::getIndoorSquare() {
    // TODO: Implement getIndoorSquare
    return nullptr;
}

IsoGridSquare IsoWindow::getAddSheetSquare(IsoGameCharacter var1) {
    // TODO: Implement getAddSheetSquare
    return nullptr;
}

void IsoWindow::AttackObject(IsoGameCharacter var1) {
    // TODO: Implement AttackObject
}

IsoGridSquare IsoWindow::getInsideSquare() {
    // TODO: Implement getInsideSquare
    return nullptr;
}

IsoGridSquare IsoWindow::getOppositeSquare() {
    // TODO: Implement getOppositeSquare
    return nullptr;
}

bool IsoWindow::isExterior() {
    // TODO: Implement isExterior
    return false;
}

public IsoWindow::IsoWindow(IsoCell var1) {
    // TODO: Implement IsoWindow
    return nullptr;
}

std::string IsoWindow::getObjectName() {
    // TODO: Implement getObjectName
    return "";
}

void IsoWindow::WeaponHit(IsoGameCharacter var1, HandWeapon var2) {
    // TODO: Implement WeaponHit
}

void IsoWindow::smashWindow(bool var1, bool var2) {
    // TODO: Implement smashWindow
}

void IsoWindow::smashWindow(bool var1) {
    // TODO: Implement smashWindow
}

void IsoWindow::smashWindow() {
    // TODO: Implement smashWindow
}

void IsoWindow::addBrokenGlass(IsoMovingObject var1) {
    // TODO: Implement addBrokenGlass
}

void IsoWindow::addBrokenGlass(bool var1) {
    // TODO: Implement addBrokenGlass
}

void IsoWindow::handleAlarm() {
    // TODO: Implement handleAlarm
}

public IsoWindow::IsoWindow(IsoCell var1, IsoGridSquare var2, IsoSprite var3, bool var4) {
    // TODO: Implement IsoWindow
    return nullptr;
}

bool IsoWindow::isDestroyed() {
    // TODO: Implement isDestroyed
    return false;
}

bool IsoWindow::IsOpen() {
    // TODO: Implement IsOpen
    return false;
}

bool IsoWindow::onMouseLeftClick(int var1, int var2) {
    // TODO: Implement onMouseLeftClick
    return false;
}

bool IsoWindow::TestCollide(IsoMovingObject var1, IsoGridSquare var2, IsoGridSquare var3) {
    // TODO: Implement TestCollide
    return false;
}

VisionResult IsoWindow::TestVision(IsoGridSquare var1, IsoGridSquare var2) {
    // TODO: Implement TestVision
    return nullptr;
}

void IsoWindow::Thump(IsoMovingObject var1) {
    // TODO: Implement Thump
}

Thumpable IsoWindow::getThumpableFor(IsoGameCharacter var1) {
    // TODO: Implement getThumpableFor
    return nullptr;
}

float IsoWindow::getThumpCondition() {
    // TODO: Implement getThumpCondition
    return 0;
}

void IsoWindow::load(ByteBuffer var1, int var2, bool var3) {
    // TODO: Implement load
}

void IsoWindow::addToWorld() {
    // TODO: Implement addToWorld
}

void IsoWindow::removeFromWorld() {
    // TODO: Implement removeFromWorld
}

void IsoWindow::save(ByteBuffer var1, bool var2) {
    // TODO: Implement save
}

void IsoWindow::saveState(ByteBuffer var1) {
    // TODO: Implement saveState
}

void IsoWindow::loadState(ByteBuffer var1) {
    // TODO: Implement loadState
}

void IsoWindow::render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
    // TODO: Implement render
}

void IsoWindow::openCloseCurtain(IsoGameCharacter var1) {
    // TODO: Implement openCloseCurtain
}

void IsoWindow::removeSheet(IsoGameCharacter var1) {
    // TODO: Implement removeSheet
}

void IsoWindow::addSheet(IsoGameCharacter var1) {
    // TODO: Implement addSheet
}

void IsoWindow::ToggleWindow(IsoGameCharacter var1) {
    // TODO: Implement ToggleWindow
}

void IsoWindow::syncIsoObjectSend(ByteBufferWriter var1) {
    // TODO: Implement syncIsoObjectSend
}

void IsoWindow::syncIsoObject(bool var1, uint8_t var2, UdpConnection var3, ByteBuffer var4) {
    // TODO: Implement syncIsoObject
}

bool IsoWindow::isTopOfSheetRopeHere(IsoGridSquare var0) {
    // TODO: Implement isTopOfSheetRopeHere
    return false;
}

bool IsoWindow::isTopOfSheetRopeHere(IsoGridSquare var0, bool var1) {
    // TODO: Implement isTopOfSheetRopeHere
    return false;
}

bool IsoWindow::haveSheetRope() {
    // TODO: Implement haveSheetRope
    return false;
}

return IsoWindow::isTopOfSheetRopeHere() {
    // TODO: Implement isTopOfSheetRopeHere
    return nullptr;
}

bool IsoWindow::isSheetRopeHere(IsoGridSquare var0) {
    // TODO: Implement isSheetRopeHere
    return false;
}

bool IsoWindow::canClimbHere(IsoGridSquare var0) {
    // TODO: Implement canClimbHere
    return false;
}

int IsoWindow::countAddSheetRope(IsoGridSquare var0, bool var1) {
    // TODO: Implement countAddSheetRope
    return 0;
}

int IsoWindow::countAddSheetRope() {
    // TODO: Implement countAddSheetRope
    return 0;
}

return IsoWindow::countAddSheetRope() {
    // TODO: Implement countAddSheetRope
    return nullptr;
}

bool IsoWindow::canAddSheetRope(IsoGridSquare var0, bool var1) {
    // TODO: Implement canAddSheetRope
    return false;
}

return IsoWindow::countAddSheetRope() {
    // TODO: Implement countAddSheetRope
    return nullptr;
}

bool IsoWindow::canAddSheetRope() {
    // TODO: Implement canAddSheetRope
    return false;
}

bool IsoWindow::addSheetRope(IsoPlayer var1, const std::string& var2) {
    // TODO: Implement addSheetRope
    return false;
}

bool IsoWindow::addSheetRope(IsoPlayer var0, IsoGridSquare var1, bool var2, const std::string& var3) {
    // TODO: Implement addSheetRope
    return false;
}

bool IsoWindow::removeSheetRope(IsoPlayer var1) {
    // TODO: Implement removeSheetRope
    return false;
}

bool IsoWindow::removeSheetRope(IsoPlayer var0, IsoGridSquare var1, bool var2) {
    // TODO: Implement removeSheetRope
    return false;
}

void IsoWindow::Damage(float var1) {
    // TODO: Implement Damage
}

void IsoWindow::Damage(float var1, bool var2) {
    // TODO: Implement Damage
}

void IsoWindow::Damage(float var1, IsoMovingObject var2) {
    // TODO: Implement Damage
}

bool IsoWindow::isLocked() {
    // TODO: Implement isLocked
    return false;
}

bool IsoWindow::isSmashed() {
    // TODO: Implement isSmashed
    return false;
}

bool IsoWindow::isInvincible() {
    // TODO: Implement isInvincible
    return false;
}

IsoBarricade IsoWindow::getBarricadeOnSameSquare() {
    // TODO: Implement getBarricadeOnSameSquare
    return nullptr;
}

IsoBarricade IsoWindow::getBarricadeOnOppositeSquare() {
    // TODO: Implement getBarricadeOnOppositeSquare
    return nullptr;
}

bool IsoWindow::isBarricaded() {
    // TODO: Implement isBarricaded
    return false;
}

bool IsoWindow::isBarricadeAllowed() {
    // TODO: Implement isBarricadeAllowed
    return false;
}

IsoBarricade IsoWindow::getBarricadeForCharacter(IsoGameCharacter var1) {
    // TODO: Implement getBarricadeForCharacter
    return nullptr;
}

IsoBarricade IsoWindow::getBarricadeOppositeCharacter(IsoGameCharacter var1) {
    // TODO: Implement getBarricadeOppositeCharacter
    return nullptr;
}

bool IsoWindow::getNorth() {
    // TODO: Implement getNorth
    return false;
}

Vector2 IsoWindow::getFacingPosition(Vector2 var1) {
    // TODO: Implement getFacingPosition
    return nullptr;
}

void IsoWindow::setIsLocked(bool var1) {
    // TODO: Implement setIsLocked
}

IsoSprite IsoWindow::getOpenSprite() {
    // TODO: Implement getOpenSprite
    return nullptr;
}

void IsoWindow::setOpenSprite(IsoSprite var1) {
    // TODO: Implement setOpenSprite
}

void IsoWindow::setSmashed(bool var1) {
    // TODO: Implement setSmashed
}

IsoSprite IsoWindow::getSmashedSprite() {
    // TODO: Implement getSmashedSprite
    return nullptr;
}

void IsoWindow::setSmashedSprite(IsoSprite var1) {
    // TODO: Implement setSmashedSprite
}

void IsoWindow::setPermaLocked(bool var1) {
    // TODO: Implement setPermaLocked
}

bool IsoWindow::isPermaLocked() {
    // TODO: Implement isPermaLocked
    return false;
}

bool IsoWindow::canClimbThroughHelper(IsoGameCharacter var0, IsoGridSquare var1, IsoGridSquare var2, bool var3) {
    // TODO: Implement canClimbThroughHelper
    return false;
}

bool IsoWindow::canClimbThrough(IsoGameCharacter var1) {
    // TODO: Implement canClimbThrough
    return false;
}

IsoGameCharacter IsoWindow::getFirstCharacterClimbingThrough() {
    // TODO: Implement getFirstCharacterClimbingThrough
    return nullptr;
}

IsoGameCharacter IsoWindow::getFirstCharacterClimbingThrough(IsoGridSquare var1) {
    // TODO: Implement getFirstCharacterClimbingThrough
    return nullptr;
}

IsoGameCharacter IsoWindow::getFirstCharacterClosing() {
    // TODO: Implement getFirstCharacterClosing
    return nullptr;
}

IsoGameCharacter IsoWindow::getFirstCharacterClosing(IsoGridSquare var1) {
    // TODO: Implement getFirstCharacterClosing
    return nullptr;
}

bool IsoWindow::isGlassRemoved() {
    // TODO: Implement isGlassRemoved
    return false;
}

void IsoWindow::setGlassRemoved(bool var1) {
    // TODO: Implement setGlassRemoved
}

void IsoWindow::removeBrokenGlass() {
    // TODO: Implement removeBrokenGlass
}

IsoBarricade IsoWindow::addBarricadesDebug(int var1, bool var2) {
    // TODO: Implement addBarricadesDebug
    return nullptr;
}

void IsoWindow::addRandomBarricades() {
    // TODO: Implement addRandomBarricades
}

} // namespace objects
} // namespace iso
} // namespace zombie
