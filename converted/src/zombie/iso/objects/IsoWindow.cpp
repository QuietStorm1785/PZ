#include "zombie/iso/objects/IsoWindow.h"

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

IsoGridSquare IsoWindow::getAddSheetSquare(IsoGameCharacter chr) {
 // TODO: Implement getAddSheetSquare
 return nullptr;
}

void IsoWindow::AttackObject(IsoGameCharacter owner) {
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

public IsoWindow::IsoWindow(IsoCell cell) {
 // TODO: Implement IsoWindow
 return nullptr;
}

std::string IsoWindow::getObjectName() {
 // TODO: Implement getObjectName
 return "";
}

void IsoWindow::WeaponHit(IsoGameCharacter owner, HandWeapon weapon) {
 // TODO: Implement WeaponHit
}

void IsoWindow::smashWindow(bool bRemote, bool doAlarm) {
 // TODO: Implement smashWindow
}

void IsoWindow::smashWindow(bool bRemote) {
 // TODO: Implement smashWindow
}

void IsoWindow::smashWindow() {
 // TODO: Implement smashWindow
}

void IsoWindow::addBrokenGlass(IsoMovingObject chr) {
 // TODO: Implement addBrokenGlass
}

void IsoWindow::addBrokenGlass(bool onOppositeSquare) {
 // TODO: Implement addBrokenGlass
}

void IsoWindow::handleAlarm() {
 // TODO: Implement handleAlarm
}

public IsoWindow::IsoWindow(IsoCell cell, IsoGridSquare gridSquare, IsoSprite gid, bool _north) {
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

bool IsoWindow::onMouseLeftClick(int x, int y) {
 // TODO: Implement onMouseLeftClick
 return false;
}

bool IsoWindow::TestCollide(IsoMovingObject obj, IsoGridSquare from, IsoGridSquare to) {
 // TODO: Implement TestCollide
 return false;
}

void IsoWindow::Thump(IsoMovingObject thumper) {
 // TODO: Implement Thump
}

Thumpable IsoWindow::getThumpableFor(IsoGameCharacter chr) {
 // TODO: Implement getThumpableFor
 return nullptr;
}

float IsoWindow::getThumpCondition() {
 // TODO: Implement getThumpCondition
 return 0;
}

void IsoWindow::load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 // TODO: Implement load
}

void IsoWindow::addToWorld() {
 // TODO: Implement addToWorld
}

void IsoWindow::removeFromWorld() {
 // TODO: Implement removeFromWorld
}

void IsoWindow::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 // TODO: Implement save
}

void IsoWindow::saveState(ByteBuffer bb) {
 // TODO: Implement saveState
}

void IsoWindow::loadState(ByteBuffer bb) {
 // TODO: Implement loadState
}

void IsoWindow::render(float x, float y, float z, ColorInfo col, bool bDoAttached, bool bWallLightingPass, Shader shader) {
 // TODO: Implement render
}

void IsoWindow::openCloseCurtain(IsoGameCharacter chr) {
 // TODO: Implement openCloseCurtain
}

void IsoWindow::removeSheet(IsoGameCharacter chr) {
 // TODO: Implement removeSheet
}

void IsoWindow::addSheet(IsoGameCharacter chr) {
 // TODO: Implement addSheet
}

void IsoWindow::ToggleWindow(IsoGameCharacter chr) {
 // TODO: Implement ToggleWindow
}

void IsoWindow::syncIsoObjectSend(ByteBufferWriter b) {
 // TODO: Implement syncIsoObjectSend
}

void IsoWindow::syncIsoObject(bool bRemote, uint8_t val, UdpConnection source, ByteBuffer bb) {
 // TODO: Implement syncIsoObject
}

bool IsoWindow::isTopOfSheetRopeHere(IsoGridSquare sq) {
 // TODO: Implement isTopOfSheetRopeHere
 return false;
}

bool IsoWindow::isTopOfSheetRopeHere(IsoGridSquare sq, bool _north) {
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

bool IsoWindow::isSheetRopeHere(IsoGridSquare sq) {
 // TODO: Implement isSheetRopeHere
 return false;
}

bool IsoWindow::canClimbHere(IsoGridSquare sq) {
 // TODO: Implement canClimbHere
 return false;
}

int IsoWindow::countAddSheetRope(IsoGridSquare sq, bool _north) {
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

bool IsoWindow::canAddSheetRope(IsoGridSquare sq, bool _north) {
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

bool IsoWindow::addSheetRope(IsoPlayer player, const std::string& itemType) {
 // TODO: Implement addSheetRope
 return false;
}

bool IsoWindow::addSheetRope(IsoPlayer player, IsoGridSquare sq, bool _north, const std::string& itemType) {
 // TODO: Implement addSheetRope
 return false;
}

bool IsoWindow::removeSheetRope(IsoPlayer player) {
 // TODO: Implement removeSheetRope
 return false;
}

bool IsoWindow::removeSheetRope(IsoPlayer player, IsoGridSquare square, bool _north) {
 // TODO: Implement removeSheetRope
 return false;
}

void IsoWindow::Damage(float amount) {
 // TODO: Implement Damage
}

void IsoWindow::Damage(float amount, bool isZombie) {
 // TODO: Implement Damage
}

void IsoWindow::Damage(float amount, IsoMovingObject chr) {
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

IsoBarricade IsoWindow::getBarricadeForCharacter(IsoGameCharacter chr) {
 // TODO: Implement getBarricadeForCharacter
 return nullptr;
}

IsoBarricade IsoWindow::getBarricadeOppositeCharacter(IsoGameCharacter chr) {
 // TODO: Implement getBarricadeOppositeCharacter
 return nullptr;
}

bool IsoWindow::getNorth() {
 // TODO: Implement getNorth
 return false;
}

Vector2 IsoWindow::getFacingPosition(Vector2 pos) {
 // TODO: Implement getFacingPosition
 return nullptr;
}

void IsoWindow::setIsLocked(bool lock) {
 // TODO: Implement setIsLocked
}

IsoSprite IsoWindow::getOpenSprite() {
 // TODO: Implement getOpenSprite
 return nullptr;
}

void IsoWindow::setOpenSprite(IsoSprite sprite) {
 // TODO: Implement setOpenSprite
}

void IsoWindow::setSmashed(bool _destroyed) {
 // TODO: Implement setSmashed
}

IsoSprite IsoWindow::getSmashedSprite() {
 // TODO: Implement getSmashedSprite
 return nullptr;
}

void IsoWindow::setSmashedSprite(IsoSprite sprite) {
 // TODO: Implement setSmashedSprite
}

void IsoWindow::setPermaLocked(bool permaLock) {
 // TODO: Implement setPermaLocked
}

bool IsoWindow::isPermaLocked() {
 // TODO: Implement isPermaLocked
 return false;
}

bool IsoWindow::canClimbThroughHelper(IsoGameCharacter chr, IsoGridSquare sq, IsoGridSquare oppositeSq, bool _north) {
 // TODO: Implement canClimbThroughHelper
 return false;
}

bool IsoWindow::canClimbThrough(IsoGameCharacter chr) {
 // TODO: Implement canClimbThrough
 return false;
}

IsoGameCharacter IsoWindow::getFirstCharacterClimbingThrough() {
 // TODO: Implement getFirstCharacterClimbingThrough
 return nullptr;
}

IsoGameCharacter IsoWindow::getFirstCharacterClimbingThrough(IsoGridSquare square) {
 // TODO: Implement getFirstCharacterClimbingThrough
 return nullptr;
}

IsoGameCharacter IsoWindow::getFirstCharacterClosing() {
 // TODO: Implement getFirstCharacterClosing
 return nullptr;
}

IsoGameCharacter IsoWindow::getFirstCharacterClosing(IsoGridSquare square) {
 // TODO: Implement getFirstCharacterClosing
 return nullptr;
}

bool IsoWindow::isGlassRemoved() {
 // TODO: Implement isGlassRemoved
 return false;
}

void IsoWindow::setGlassRemoved(bool removed) {
 // TODO: Implement setGlassRemoved
}

void IsoWindow::removeBrokenGlass() {
 // TODO: Implement removeBrokenGlass
}

IsoBarricade IsoWindow::addBarricadesDebug(int numPlanks, bool metal) {
 // TODO: Implement addBarricadesDebug
 return nullptr;
}

void IsoWindow::addRandomBarricades() {
 // TODO: Implement addRandomBarricades
}

} // namespace objects
} // namespace iso
} // namespace zombie
