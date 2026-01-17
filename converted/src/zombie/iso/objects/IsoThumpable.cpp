#include "zombie/iso/objects/IsoThumpable.h"

namespace zombie {
namespace iso {
namespace objects {

KahluaTable IsoThumpable::getModData() {
  // TODO: Implement getModData
  return nullptr;
}

void IsoThumpable::setModData(KahluaTable _modData) {
  // TODO: Implement setModData
}

bool IsoThumpable::hasModData() {
  // TODO: Implement hasModData
  return false;
}

bool IsoThumpable::isCanPassThrough() {
  // TODO: Implement isCanPassThrough
  return false;
}

void IsoThumpable::setCanPassThrough(bool pCanPassThrough) {
  // TODO: Implement setCanPassThrough
}

bool IsoThumpable::isBlockAllTheSquare() {
  // TODO: Implement isBlockAllTheSquare
  return false;
}

void IsoThumpable::setBlockAllTheSquare(bool _blockAllTheSquare) {
  // TODO: Implement setBlockAllTheSquare
}

void IsoThumpable::setIsDismantable(bool _dismantable) {
  // TODO: Implement setIsDismantable
}

bool IsoThumpable::isDismantable() {
  // TODO: Implement isDismantable
  return false;
}

float IsoThumpable::getCrossSpeed() {
  // TODO: Implement getCrossSpeed
  return 0;
}

void IsoThumpable::setCrossSpeed(float pCrossSpeed) {
  // TODO: Implement setCrossSpeed
}

void IsoThumpable::setIsFloor(bool pIsFloor) {
  // TODO: Implement setIsFloor
}

bool IsoThumpable::isCorner() {
  // TODO: Implement isCorner
  return false;
}

bool IsoThumpable::isFloor() {
  // TODO: Implement isFloor
  return false;
}

void IsoThumpable::setIsContainer(bool pIsContainer) {
  // TODO: Implement setIsContainer
}

void IsoThumpable::setIsStairs(bool pStairs) {
  // TODO: Implement setIsStairs
}

bool IsoThumpable::isStairs() {
  // TODO: Implement isStairs
  return false;
}

bool IsoThumpable::isWindow() {
  // TODO: Implement isWindow
  return false;
}

std::string IsoThumpable::getObjectName() {
  // TODO: Implement getObjectName
  return "";
}

public
IsoThumpable::IsoThumpable(IsoCell cell) {
  // TODO: Implement IsoThumpable
  return nullptr;
}

void IsoThumpable::setCorner(bool pCorner) {
  // TODO: Implement setCorner
}

void IsoThumpable::setCanBarricade(bool pCanBarricade) {
  // TODO: Implement setCanBarricade
}

bool IsoThumpable::getCanBarricade() {
  // TODO: Implement getCanBarricade
  return false;
}

void IsoThumpable::setHealth(int health) {
  // TODO: Implement setHealth
}

int IsoThumpable::getHealth() {
  // TODO: Implement getHealth
  return 0;
}

void IsoThumpable::setMaxHealth(int maxHealth) {
  // TODO: Implement setMaxHealth
}

int IsoThumpable::getMaxHealth() {
  // TODO: Implement getMaxHealth
  return 0;
}

void IsoThumpable::setThumpDmg(int pThumpDmg) {
  // TODO: Implement setThumpDmg
}

int IsoThumpable::getThumpDmg() {
  // TODO: Implement getThumpDmg
  return 0;
}

void IsoThumpable::setBreakSound(const std::string &pBreakSound) {
  // TODO: Implement setBreakSound
}

std::string IsoThumpable::getBreakSound() {
  // TODO: Implement getBreakSound
  return "";
}

bool IsoThumpable::isDoor() {
  // TODO: Implement isDoor
  return false;
}

bool IsoThumpable::getNorth() {
  // TODO: Implement getNorth
  return false;
}

Vector2 IsoThumpable::getFacingPosition(Vector2 pos) {
  // TODO: Implement getFacingPosition
  return nullptr;
}

bool IsoThumpable::isDoorFrame() {
  // TODO: Implement isDoorFrame
  return false;
}

void IsoThumpable::setIsDoor(bool pIsDoor) {
  // TODO: Implement setIsDoor
}

void IsoThumpable::setIsDoorFrame(bool pIsDoorFrame) {
  // TODO: Implement setIsDoorFrame
}

void IsoThumpable::setSprite(const std::string &sprite) {
  // TODO: Implement setSprite
}

void IsoThumpable::setSpriteFromName(const std::string &name) {
  // TODO: Implement setSpriteFromName
}

void IsoThumpable::setClosedSprite(IsoSprite sprite) {
  // TODO: Implement setClosedSprite
}

void IsoThumpable::setOpenSprite(IsoSprite sprite) {
  // TODO: Implement setOpenSprite
}

public
IsoThumpable::IsoThumpable(IsoCell cell, IsoGridSquare gridSquare,
                           const std::string &_closedSprite,
                           const std::string &_openSprite, bool _north,
                           KahluaTable _table) {
  // TODO: Implement IsoThumpable
  return nullptr;
}

public
IsoThumpable::IsoThumpable(IsoCell cell, IsoGridSquare gridSquare,
                           const std::string &sprite, bool _north,
                           KahluaTable _table) {
  // TODO: Implement IsoThumpable
  return nullptr;
}

void IsoThumpable::load(ByteBuffer input, int WorldVersion,
                        bool IS_DEBUG_SAVE) {
  // TODO: Implement load
}

void IsoThumpable::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
  // TODO: Implement save
}

bool IsoThumpable::isDestroyed() {
  // TODO: Implement isDestroyed
  return false;
}

bool IsoThumpable::IsOpen() {
  // TODO: Implement IsOpen
  return false;
}

bool IsoThumpable::IsStrengthenedByPushedItems() {
  // TODO: Implement IsStrengthenedByPushedItems
  return false;
}

bool IsoThumpable::onMouseLeftClick(int x, int y) {
  // TODO: Implement onMouseLeftClick
  return false;
}

bool IsoThumpable::TestPathfindCollide(IsoMovingObject obj, IsoGridSquare from,
                                       IsoGridSquare to) {
  // TODO: Implement TestPathfindCollide
  return false;
}

bool IsoThumpable::TestCollide(IsoMovingObject obj, IsoGridSquare from,
                               IsoGridSquare to) {
  // TODO: Implement TestCollide
  return false;
}

void IsoThumpable::Thump(IsoMovingObject thumper) {
  // TODO: Implement Thump
}

Thumpable IsoThumpable::getThumpableFor(IsoGameCharacter chr) {
  // TODO: Implement getThumpableFor
  return nullptr;
}

float IsoThumpable::getThumpCondition() {
  // TODO: Implement getThumpCondition
  return 0;
}

void IsoThumpable::WeaponHit(IsoGameCharacter owner, HandWeapon weapon) {
  // TODO: Implement WeaponHit
}

IsoGridSquare IsoThumpable::getOtherSideOfDoor(IsoGameCharacter chr) {
  // TODO: Implement getOtherSideOfDoor
  return nullptr;
}

void IsoThumpable::ToggleDoorActual(IsoGameCharacter chr) {
  // TODO: Implement ToggleDoorActual
}

void IsoThumpable::ToggleDoor(IsoGameCharacter chr) {
  // TODO: Implement ToggleDoor
}

void IsoThumpable::ToggleDoorSilent() {
  // TODO: Implement ToggleDoorSilent
}

bool IsoThumpable::isObstructed() {
  // TODO: Implement isObstructed
  return false;
}

bool IsoThumpable::haveSheetRope() {
  // TODO: Implement haveSheetRope
  return false;
}

int IsoThumpable::countAddSheetRope() {
  // TODO: Implement countAddSheetRope
  return 0;
}

bool IsoThumpable::canAddSheetRope() {
  // TODO: Implement canAddSheetRope
  return false;
}

bool IsoThumpable::addSheetRope(IsoPlayer player, const std::string &itemType) {
  // TODO: Implement addSheetRope
  return false;
}

bool IsoThumpable::removeSheetRope(IsoPlayer player) {
  // TODO: Implement removeSheetRope
  return false;
}

InventoryItem IsoThumpable::insertNewFuel(InventoryItem item,
                                          IsoGameCharacter chr) {
  // TODO: Implement insertNewFuel
  return nullptr;
}

InventoryItem IsoThumpable::removeCurrentFuel(IsoGameCharacter chr) {
  // TODO: Implement removeCurrentFuel
  return nullptr;
}

int IsoThumpable::calcLightSourceX() {
  // TODO: Implement calcLightSourceX
  return 0;
}

int IsoThumpable::calcLightSourceY() {
  // TODO: Implement calcLightSourceY
  return 0;
}

void IsoThumpable::update() {
  // TODO: Implement update
}

new IsoThumpable::IsoLightSource() {
  // TODO: Implement IsoLightSource
  return nullptr;
}

new IsoThumpable::IsoLightSource() {
  // TODO: Implement IsoLightSource
  return nullptr;
}

void IsoThumpable::Damage(int int0) {
  // TODO: Implement Damage
}

void IsoThumpable::destroy() {
  // TODO: Implement destroy
}

IsoBarricade IsoThumpable::getBarricadeOnSameSquare() {
  // TODO: Implement getBarricadeOnSameSquare
  return nullptr;
}

IsoBarricade IsoThumpable::getBarricadeOnOppositeSquare() {
  // TODO: Implement getBarricadeOnOppositeSquare
  return nullptr;
}

bool IsoThumpable::isBarricaded() {
  // TODO: Implement isBarricaded
  return false;
}

bool IsoThumpable::isBarricadeAllowed() {
  // TODO: Implement isBarricadeAllowed
  return false;
}

IsoBarricade IsoThumpable::getBarricadeForCharacter(IsoGameCharacter chr) {
  // TODO: Implement getBarricadeForCharacter
  return nullptr;
}

IsoBarricade IsoThumpable::getBarricadeOppositeCharacter(IsoGameCharacter chr) {
  // TODO: Implement getBarricadeOppositeCharacter
  return nullptr;
}

void IsoThumpable::setIsDoor(bool pIsDoor) {
  // TODO: Implement setIsDoor
}

KahluaTable IsoThumpable::getTable() {
  // TODO: Implement getTable
  return nullptr;
}

void IsoThumpable::setTable(KahluaTable _table) {
  // TODO: Implement setTable
}

bool IsoThumpable::canBePlastered() {
  // TODO: Implement canBePlastered
  return false;
}

void IsoThumpable::setCanBePlastered(bool _canBePlastered) {
  // TODO: Implement setCanBePlastered
}

bool IsoThumpable::isPaintable() {
  // TODO: Implement isPaintable
  return false;
}

void IsoThumpable::setPaintable(bool _paintable) {
  // TODO: Implement setPaintable
}

bool IsoThumpable::isLocked() {
  // TODO: Implement isLocked
  return false;
}

void IsoThumpable::setIsLocked(bool lock) {
  // TODO: Implement setIsLocked
}

bool IsoThumpable::isThumpable() {
  // TODO: Implement isThumpable
  return false;
}

void IsoThumpable::setIsThumpable(bool thumpable) {
  // TODO: Implement setIsThumpable
}

void IsoThumpable::setIsHoppable(bool _isHoppable) {
  // TODO: Implement setIsHoppable
}

IsoSprite IsoThumpable::getOpenSprite() {
  // TODO: Implement getOpenSprite
  return nullptr;
}

bool IsoThumpable::isHoppable() {
  // TODO: Implement isHoppable
  return false;
}

void IsoThumpable::setHoppable(bool _isHoppable) {
  // TODO: Implement setHoppable
}

int IsoThumpable::getLightSourceRadius() {
  // TODO: Implement getLightSourceRadius
  return 0;
}

void IsoThumpable::setLightSourceRadius(int _lightSourceRadius) {
  // TODO: Implement setLightSourceRadius
}

int IsoThumpable::getLightSourceXOffset() {
  // TODO: Implement getLightSourceXOffset
  return 0;
}

void IsoThumpable::setLightSourceXOffset(int _lightSourceXOffset) {
  // TODO: Implement setLightSourceXOffset
}

int IsoThumpable::getLightSourceYOffset() {
  // TODO: Implement getLightSourceYOffset
  return 0;
}

void IsoThumpable::setLightSourceYOffset(int _lightSourceYOffset) {
  // TODO: Implement setLightSourceYOffset
}

int IsoThumpable::getLightSourceLife() {
  // TODO: Implement getLightSourceLife
  return 0;
}

void IsoThumpable::setLightSourceLife(int _lightSourceLife) {
  // TODO: Implement setLightSourceLife
}

bool IsoThumpable::isLightSourceOn() {
  // TODO: Implement isLightSourceOn
  return false;
}

void IsoThumpable::setLightSourceOn(bool _lightSourceOn) {
  // TODO: Implement setLightSourceOn
}

IsoLightSource IsoThumpable::getLightSource() {
  // TODO: Implement getLightSource
  return nullptr;
}

void IsoThumpable::setLightSource(IsoLightSource _lightSource) {
  // TODO: Implement setLightSource
}

void IsoThumpable::toggleLightSource(bool toggle) {
  // TODO: Implement toggleLightSource
}

std::string IsoThumpable::getLightSourceFuel() {
  // TODO: Implement getLightSourceFuel
  return "";
}

void IsoThumpable::setLightSourceFuel(const std::string &_lightSourceFuel) {
  // TODO: Implement setLightSourceFuel
}

float IsoThumpable::getLifeLeft() {
  // TODO: Implement getLifeLeft
  return 0;
}

void IsoThumpable::setLifeLeft(float _lifeLeft) {
  // TODO: Implement setLifeLeft
}

float IsoThumpable::getLifeDelta() {
  // TODO: Implement getLifeDelta
  return 0;
}

void IsoThumpable::setLifeDelta(float _lifeDelta) {
  // TODO: Implement setLifeDelta
}

bool IsoThumpable::haveFuel() {
  // TODO: Implement haveFuel
  return false;
}

void IsoThumpable::setHaveFuel(bool _haveFuel) {
  // TODO: Implement setHaveFuel
}

void IsoThumpable::syncIsoObjectSend(ByteBufferWriter b) {
  // TODO: Implement syncIsoObjectSend
}

void IsoThumpable::syncIsoObject(bool bRemote, uint8_t val,
                                 UdpConnection source, ByteBuffer bb) {
  // TODO: Implement syncIsoObject
}

void IsoThumpable::addToWorld() {
  // TODO: Implement addToWorld
}

void IsoThumpable::removeFromWorld() {
  // TODO: Implement removeFromWorld
}

void IsoThumpable::saveChange(const std::string &change, KahluaTable tbl,
                              ByteBuffer bb) {
  // TODO: Implement saveChange
}

void IsoThumpable::loadChange(const std::string &change, ByteBuffer bb) {
  // TODO: Implement loadChange
}

IsoCurtain IsoThumpable::HasCurtains() {
  // TODO: Implement HasCurtains
  return nullptr;
}

IsoGridSquare IsoThumpable::getInsideSquare() {
  // TODO: Implement getInsideSquare
  return nullptr;
}

IsoGridSquare IsoThumpable::getOppositeSquare() {
  // TODO: Implement getOppositeSquare
  return nullptr;
}

bool IsoThumpable::isAdjacentToSquare(IsoGridSquare square2) {
  // TODO: Implement isAdjacentToSquare
  return false;
}

IsoGridSquare IsoThumpable::getAddSheetSquare(IsoGameCharacter chr) {
  // TODO: Implement getAddSheetSquare
  return nullptr;
}

void IsoThumpable::addSheet(IsoGameCharacter chr) {
  // TODO: Implement addSheet
}

IsoGridSquare IsoThumpable::getIndoorSquare() {
  // TODO: Implement getIndoorSquare
  return nullptr;
}

int IsoThumpable::getKeyId() {
  // TODO: Implement getKeyId
  return 0;
}

void IsoThumpable::setKeyId(int _keyId, bool doNetwork) {
  // TODO: Implement setKeyId
}

void IsoThumpable::setKeyId(int _keyId) {
  // TODO: Implement setKeyId
}

bool IsoThumpable::isLockedByKey() {
  // TODO: Implement isLockedByKey
  return false;
}

void IsoThumpable::setLockedByKey(bool _lockedByKey) {
  // TODO: Implement setLockedByKey
}

bool IsoThumpable::isLockedByPadlock() {
  // TODO: Implement isLockedByPadlock
  return false;
}

void IsoThumpable::syncIsoThumpable() {
  // TODO: Implement syncIsoThumpable
}

void IsoThumpable::setLockedByPadlock(bool _lockedByPadlock) {
  // TODO: Implement setLockedByPadlock
}

bool IsoThumpable::canBeLockByPadlock() {
  // TODO: Implement canBeLockByPadlock
  return false;
}

void IsoThumpable::setCanBeLockByPadlock(bool _canBeLockByPadlock) {
  // TODO: Implement setCanBeLockByPadlock
}

int IsoThumpable::getLockedByCode() {
  // TODO: Implement getLockedByCode
  return 0;
}

void IsoThumpable::setLockedByCode(int _lockedByCode) {
  // TODO: Implement setLockedByCode
}

bool IsoThumpable::isLockedToCharacter(IsoGameCharacter chr) {
  // TODO: Implement isLockedToCharacter
  return false;
}

bool IsoThumpable::canClimbOver(IsoGameCharacter chr) {
  // TODO: Implement canClimbOver
  return false;
}

bool IsoThumpable::canClimbThrough(IsoGameCharacter chr) {
  // TODO: Implement canClimbThrough
  return false;
}

std::string IsoThumpable::getThumpSound() {
  // TODO: Implement getThumpSound
  return "";
}

void IsoThumpable::setThumpSound(const std::string &_thumpSound) {
  // TODO: Implement setThumpSound
}

IsoObject IsoThumpable::getRenderEffectMaster() {
  // TODO: Implement getRenderEffectMaster
  return nullptr;
}

IsoDirections IsoThumpable::getSpriteEdge(bool ignoreOpen) {
  // TODO: Implement getSpriteEdge
  return nullptr;
}

std::string IsoThumpable::getSoundPrefix() {
  // TODO: Implement getSoundPrefix
  return "";
}

void IsoThumpable::playDoorSound(
    BaseCharacterSoundEmitter baseCharacterSoundEmitter,
    const std::string &string) {
  // TODO: Implement playDoorSound
}

} // namespace objects
} // namespace iso
} // namespace zombie
