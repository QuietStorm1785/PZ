#include "zombie/iso/IsoMovingObject.h"

namespace zombie {
namespace iso {

public
IsoMovingObject::IsoMovingObject(IsoCell cell) {
 // TODO: Implement IsoMovingObject
 return nullptr;
}

public
IsoMovingObject::IsoMovingObject(IsoCell cell, bool bObjectListAdd) {
 // TODO: Implement IsoMovingObject
 return nullptr;
}

public
IsoMovingObject::IsoMovingObject(IsoCell cell, IsoGridSquare square,
 IsoSprite spr, bool bObjectListAdd) {
 // TODO: Implement IsoMovingObject
 return nullptr;
}

public
IsoMovingObject::IsoMovingObject() {
 // TODO: Implement IsoMovingObject
 return nullptr;
}

int IsoMovingObject::getIDCount() {
 // TODO: Implement getIDCount
 return 0;
}

void IsoMovingObject::setIDCount(int aIDCount) {
 // TODO: Implement setIDCount
}

IsoBuilding IsoMovingObject::getBuilding() {
 // TODO: Implement getBuilding
 return nullptr;
}

IWorldRegion IsoMovingObject::getMasterRegion() {
 // TODO: Implement getMasterRegion
 return nullptr;
}

float IsoMovingObject::getWeight() {
 // TODO: Implement getWeight
 return 0;
}

void IsoMovingObject::setWeight(float _weight) {
 // TODO: Implement setWeight
}

float IsoMovingObject::getWeight(float _x, float _y) {
 // TODO: Implement getWeight
 return 0;
}

void IsoMovingObject::onMouseRightClick(int _lx, int _ly) {
 // TODO: Implement onMouseRightClick
}

std::string IsoMovingObject::getObjectName() {
 // TODO: Implement getObjectName
 return "";
}

void IsoMovingObject::onMouseRightReleased() {
 // TODO: Implement onMouseRightReleased
}

void IsoMovingObject::collideWith(IsoObject obj) {
 // TODO: Implement collideWith
}

void IsoMovingObject::doStairs() {
 // TODO: Implement doStairs
}

int IsoMovingObject::getID() {
 // TODO: Implement getID
 return 0;
}

void IsoMovingObject::setID(int _ID) {
 // TODO: Implement setID
}

int IsoMovingObject::getPathFindIndex() {
 // TODO: Implement getPathFindIndex
 return 0;
}

void IsoMovingObject::setPathFindIndex(int _PathFindIndex) {
 // TODO: Implement setPathFindIndex
}

float IsoMovingObject::getScreenX() {
 // TODO: Implement getScreenX
 return 0;
}

float IsoMovingObject::getScreenY() {
 // TODO: Implement getScreenY
 return 0;
}

Thumpable IsoMovingObject::getThumpTarget() {
 // TODO: Implement getThumpTarget
 return nullptr;
}

void IsoMovingObject::setThumpTarget(Thumpable _thumpTarget) {
 // TODO: Implement setThumpTarget
}

Vector2 IsoMovingObject::getVectorFromDirection(Vector2 moveForwardVec) {
 // TODO: Implement getVectorFromDirection
 return nullptr;
}

return IsoMovingObject::getVectorFromDirection() {
 // TODO: Implement getVectorFromDirection
 return nullptr;
}

Vector2 IsoMovingObject::getVectorFromDirection(Vector2 moveForwardVec,
 IsoDirections dir) {
 // TODO: Implement getVectorFromDirection
 return nullptr;
}

Vector3 IsoMovingObject::getPosition(Vector3 out) {
 // TODO: Implement getPosition
 return nullptr;
}

float IsoMovingObject::getX() {
 // TODO: Implement getX
 return 0;
}

void IsoMovingObject::setX(float _x) {
 // TODO: Implement setX
}

float IsoMovingObject::getY() {
 // TODO: Implement getY
 return 0;
}

void IsoMovingObject::setY(float _y) {
 // TODO: Implement setY
}

float IsoMovingObject::getZ() {
 // TODO: Implement getZ
 return 0;
}

void IsoMovingObject::setZ(float _z) {
 // TODO: Implement setZ
}

IsoGridSquare IsoMovingObject::getSquare() {
 // TODO: Implement getSquare
 return nullptr;
}

IsoBuilding IsoMovingObject::getCurrentBuilding() {
 // TODO: Implement getCurrentBuilding
 return nullptr;
}

float IsoMovingObject::Hit(HandWeapon weapon, IsoGameCharacter wielder,
 float damageSplit, bool bIgnoreDamage,
 float modDelta) {
 // TODO: Implement Hit
 return 0;
}

void IsoMovingObject::Move(Vector2 dir) {
 // TODO: Implement Move
}

void IsoMovingObject::MoveUnmodded(Vector2 dir) {
 // TODO: Implement MoveUnmodded
}

bool IsoMovingObject::isCharacter() {
 // TODO: Implement isCharacter
 return false;
}

float IsoMovingObject::DistTo(int _x, int _y) {
 // TODO: Implement DistTo
 return 0;
}

float IsoMovingObject::DistTo(IsoMovingObject other) {
 // TODO: Implement DistTo
 return 0;
}

float IsoMovingObject::DistToProper(IsoObject other) {
 // TODO: Implement DistToProper
 return 0;
}

float IsoMovingObject::DistToSquared(IsoMovingObject other) {
 // TODO: Implement DistToSquared
 return 0;
}

float IsoMovingObject::DistToSquared(float _x, float _y) {
 // TODO: Implement DistToSquared
 return 0;
}

void IsoMovingObject::load(ByteBuffer input, int WorldVersion,
 bool IS_DEBUG_SAVE) {
 // TODO: Implement load
}

void IsoMovingObject::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 // TODO: Implement save
}

void IsoMovingObject::removeFromWorld() {
 // TODO: Implement removeFromWorld
}

void IsoMovingObject::removeFromSquare() {
 // TODO: Implement removeFromSquare
}

IsoGridSquare IsoMovingObject::getFuturWalkedSquare() {
 // TODO: Implement getFuturWalkedSquare
 return nullptr;
}

float IsoMovingObject::getGlobalMovementMod() {
 // TODO: Implement getGlobalMovementMod
 return 0;
}

float IsoMovingObject::getGlobalMovementMod(bool bDoNoises) {
 // TODO: Implement getGlobalMovementMod
 return 0;
}

void IsoMovingObject::doTreeNoises() {
 // TODO: Implement doTreeNoises
}

void IsoMovingObject::postupdate() {
 // TODO: Implement postupdate
}

void IsoMovingObject::ensureOnTile() {
 // TODO: Implement ensureOnTile
}

void IsoMovingObject::preupdate() {
 // TODO: Implement preupdate
}

void IsoMovingObject::renderlast() {
 // TODO: Implement renderlast
}

void IsoMovingObject::spotted(IsoMovingObject other, bool bForced) {
 // TODO: Implement spotted
}

void IsoMovingObject::update() {
 // TODO: Implement update
}

void IsoMovingObject::Collided() {
 // TODO: Implement Collided
}

int IsoMovingObject::compareToY(IsoMovingObject other) {
 // TODO: Implement compareToY
 return 0;
}

float IsoMovingObject::distToNearestCamCharacter() {
 // TODO: Implement distToNearestCamCharacter
 return 0;
}

bool IsoMovingObject::isSolidForSeparate() {
 // TODO: Implement isSolidForSeparate
 return false;
}

bool IsoMovingObject::isPushableForSeparate() {
 // TODO: Implement isPushableForSeparate
 return false;
}

bool IsoMovingObject::isPushedByForSeparate(IsoMovingObject other) {
 // TODO: Implement isPushedByForSeparate
 return false;
}

void IsoMovingObject::separate() {
 // TODO: Implement separate
}

std::string IsoMovingObject::getBumpedType(IsoGameCharacter bumped) {
 // TODO: Implement getBumpedType
 return "";
}

void IsoMovingObject::slideAwayFromWalls() {
 // TODO: Implement slideAwayFromWalls
}

bool IsoMovingObject::DoCollide(int int6) {
 // TODO: Implement DoCollide
 return false;
}

void IsoMovingObject::checkHitHoppable() {
 // TODO: Implement checkHitHoppable
}

void IsoMovingObject::checkBreakHoppable() {
 // TODO: Implement checkBreakHoppable
}

void IsoMovingObject::checkHitWall() {
 // TODO: Implement checkHitWall
}

bool IsoMovingObject::checkVaultOver() {
 // TODO: Implement checkVaultOver
 return false;
}

void IsoMovingObject::setMovingSquareNow() {
 // TODO: Implement setMovingSquareNow
}

IsoGridSquare IsoMovingObject::getFeelerTile(float dist) {
 // TODO: Implement getFeelerTile
 return nullptr;
}

void IsoMovingObject::DoCollideNorS() {
 // TODO: Implement DoCollideNorS
}

void IsoMovingObject::DoCollideWorE() {
 // TODO: Implement DoCollideWorE
}

int IsoMovingObject::getTimeSinceZombieAttack() {
 // TODO: Implement getTimeSinceZombieAttack
 return 0;
}

void IsoMovingObject::setTimeSinceZombieAttack(int _TimeSinceZombieAttack) {
 // TODO: Implement setTimeSinceZombieAttack
}

bool IsoMovingObject::isCollidedE() {
 // TODO: Implement isCollidedE
 return false;
}

void IsoMovingObject::setCollidedE(bool _collidedE) {
 // TODO: Implement setCollidedE
}

bool IsoMovingObject::isCollidedN() {
 // TODO: Implement isCollidedN
 return false;
}

void IsoMovingObject::setCollidedN(bool _collidedN) {
 // TODO: Implement setCollidedN
}

IsoObject IsoMovingObject::getCollidedObject() {
 // TODO: Implement getCollidedObject
 return nullptr;
}

void IsoMovingObject::setCollidedObject(IsoObject _CollidedObject) {
 // TODO: Implement setCollidedObject
}

bool IsoMovingObject::isCollidedS() {
 // TODO: Implement isCollidedS
 return false;
}

void IsoMovingObject::setCollidedS(bool _collidedS) {
 // TODO: Implement setCollidedS
}

bool IsoMovingObject::isCollidedThisFrame() {
 // TODO: Implement isCollidedThisFrame
 return false;
}

void IsoMovingObject::setCollidedThisFrame(bool _collidedThisFrame) {
 // TODO: Implement setCollidedThisFrame
}

bool IsoMovingObject::isCollidedW() {
 // TODO: Implement isCollidedW
 return false;
}

void IsoMovingObject::setCollidedW(bool _collidedW) {
 // TODO: Implement setCollidedW
}

bool IsoMovingObject::isCollidedWithDoor() {
 // TODO: Implement isCollidedWithDoor
 return false;
}

void IsoMovingObject::setCollidedWithDoor(bool _CollidedWithDoor) {
 // TODO: Implement setCollidedWithDoor
}

bool IsoMovingObject::isCollidedWithVehicle() {
 // TODO: Implement isCollidedWithVehicle
 return false;
}

IsoGridSquare IsoMovingObject::getCurrentSquare() {
 // TODO: Implement getCurrentSquare
 return nullptr;
}

void IsoMovingObject::setCurrent(IsoGridSquare _current) {
 // TODO: Implement setCurrent
}

bool IsoMovingObject::isDestroyed() {
 // TODO: Implement isDestroyed
 return false;
}

void IsoMovingObject::setDestroyed(bool _destroyed) {
 // TODO: Implement setDestroyed
}

bool IsoMovingObject::isFirstUpdate() {
 // TODO: Implement isFirstUpdate
 return false;
}

void IsoMovingObject::setFirstUpdate(bool _firstUpdate) {
 // TODO: Implement setFirstUpdate
}

Vector2 IsoMovingObject::getHitDir() {
 // TODO: Implement getHitDir
 return nullptr;
}

void IsoMovingObject::setHitDir(Vector2 _hitDir) {
 // TODO: Implement setHitDir
}

float IsoMovingObject::getImpulsex() {
 // TODO: Implement getImpulsex
 return 0;
}

void IsoMovingObject::setImpulsex(float _impulsex) {
 // TODO: Implement setImpulsex
}

float IsoMovingObject::getImpulsey() {
 // TODO: Implement getImpulsey
 return 0;
}

void IsoMovingObject::setImpulsey(float _impulsey) {
 // TODO: Implement setImpulsey
}

float IsoMovingObject::getLimpulsex() {
 // TODO: Implement getLimpulsex
 return 0;
}

void IsoMovingObject::setLimpulsex(float _limpulsex) {
 // TODO: Implement setLimpulsex
}

float IsoMovingObject::getLimpulsey() {
 // TODO: Implement getLimpulsey
 return 0;
}

void IsoMovingObject::setLimpulsey(float _limpulsey) {
 // TODO: Implement setLimpulsey
}

float IsoMovingObject::getHitForce() {
 // TODO: Implement getHitForce
 return 0;
}

void IsoMovingObject::setHitForce(float _hitForce) {
 // TODO: Implement setHitForce
}

float IsoMovingObject::getHitFromAngle() {
 // TODO: Implement getHitFromAngle
 return 0;
}

void IsoMovingObject::setHitFromAngle(float _hitFromAngle) {
 // TODO: Implement setHitFromAngle
}

IsoGridSquare IsoMovingObject::getLastSquare() {
 // TODO: Implement getLastSquare
 return nullptr;
}

void IsoMovingObject::setLast(IsoGridSquare _last) {
 // TODO: Implement setLast
}

float IsoMovingObject::getLx() {
 // TODO: Implement getLx
 return 0;
}

void IsoMovingObject::setLx(float _lx) {
 // TODO: Implement setLx
}

float IsoMovingObject::getLy() {
 // TODO: Implement getLy
 return 0;
}

void IsoMovingObject::setLy(float _ly) {
 // TODO: Implement setLy
}

float IsoMovingObject::getLz() {
 // TODO: Implement getLz
 return 0;
}

void IsoMovingObject::setLz(float _lz) {
 // TODO: Implement setLz
}

float IsoMovingObject::getNx() {
 // TODO: Implement getNx
 return 0;
}

void IsoMovingObject::setNx(float _nx) {
 // TODO: Implement setNx
}

float IsoMovingObject::getNy() {
 // TODO: Implement getNy
 return 0;
}

void IsoMovingObject::setNy(float _ny) {
 // TODO: Implement setNy
}

bool IsoMovingObject::getNoDamage() {
 // TODO: Implement getNoDamage
 return false;
}

void IsoMovingObject::setNoDamage(bool dmg) {
 // TODO: Implement setNoDamage
}

bool IsoMovingObject::isSolid() {
 // TODO: Implement isSolid
 return false;
}

void IsoMovingObject::setSolid(bool _solid) {
 // TODO: Implement setSolid
}

float IsoMovingObject::getStateEventDelayTimer() {
 // TODO: Implement getStateEventDelayTimer
 return 0;
}

void IsoMovingObject::setStateEventDelayTimer(float _StateEventDelayTimer) {
 // TODO: Implement setStateEventDelayTimer
}

float IsoMovingObject::getWidth() {
 // TODO: Implement getWidth
 return 0;
}

void IsoMovingObject::setWidth(float _width) {
 // TODO: Implement setWidth
}

bool IsoMovingObject::isbAltCollide() {
 // TODO: Implement isbAltCollide
 return false;
}

void IsoMovingObject::setbAltCollide(bool _bAltCollide) {
 // TODO: Implement setbAltCollide
}

bool IsoMovingObject::isShootable() {
 // TODO: Implement isShootable
 return false;
}

void IsoMovingObject::setShootable(bool _shootable) {
 // TODO: Implement setShootable
}

IsoZombie IsoMovingObject::getLastTargettedBy() {
 // TODO: Implement getLastTargettedBy
 return nullptr;
}

void IsoMovingObject::setLastTargettedBy(IsoZombie _lastTargettedBy) {
 // TODO: Implement setLastTargettedBy
}

bool IsoMovingObject::isCollidable() {
 // TODO: Implement isCollidable
 return false;
}

void IsoMovingObject::setCollidable(bool _Collidable) {
 // TODO: Implement setCollidable
}

float IsoMovingObject::getScriptnx() {
 // TODO: Implement getScriptnx
 return 0;
}

void IsoMovingObject::setScriptnx(float _scriptnx) {
 // TODO: Implement setScriptnx
}

float IsoMovingObject::getScriptny() {
 // TODO: Implement getScriptny
 return 0;
}

void IsoMovingObject::setScriptny(float _scriptny) {
 // TODO: Implement setScriptny
}

std::string IsoMovingObject::getScriptModule() {
 // TODO: Implement getScriptModule
 return "";
}

void IsoMovingObject::setScriptModule(const std::string &_ScriptModule) {
 // TODO: Implement setScriptModule
}

Vector2 IsoMovingObject::getMovementLastFrame() {
 // TODO: Implement getMovementLastFrame
 return nullptr;
}

void IsoMovingObject::setMovementLastFrame(Vector2 _movementLastFrame) {
 // TODO: Implement setMovementLastFrame
}

float IsoMovingObject::getFeelersize() {
 // TODO: Implement getFeelersize
 return 0;
}

void IsoMovingObject::setFeelersize(float _feelersize) {
 // TODO: Implement setFeelersize
}

uint8_t IsoMovingObject::canHaveMultipleHits() {
 // TODO: Implement canHaveMultipleHits
 return 0;
}

bool IsoMovingObject::isOnFloor() {
 // TODO: Implement isOnFloor
 return false;
}

void IsoMovingObject::setOnFloor(bool _bOnFloor) {
 // TODO: Implement setOnFloor
}

void IsoMovingObject::Despawn() {
 // TODO: Implement Despawn
}

bool IsoMovingObject::isCloseKilled() {
 // TODO: Implement isCloseKilled
 return false;
}

void IsoMovingObject::setCloseKilled(bool _closeKilled) {
 // TODO: Implement setCloseKilled
}

Vector2 IsoMovingObject::getFacingPosition(Vector2 pos) {
 // TODO: Implement getFacingPosition
 return nullptr;
}

bool IsoMovingObject::isInLoadedArea(int int2, int int1) {
 // TODO: Implement isInLoadedArea
 return false;
}

bool IsoMovingObject::isCollided() {
 // TODO: Implement isCollided
 return false;
}

std::string IsoMovingObject::getCollideType() {
 // TODO: Implement getCollideType
 return "";
}

void IsoMovingObject::setCollideType(const std::string &_collideType) {
 // TODO: Implement setCollideType
}

float IsoMovingObject::getLastCollideTime() {
 // TODO: Implement getLastCollideTime
 return 0;
}

void IsoMovingObject::setLastCollideTime(float _lastCollideTime) {
 // TODO: Implement setLastCollideTime
}

void IsoMovingObject::setEatingZombies(ArrayList<IsoZombie> zeds) {
 // TODO: Implement setEatingZombies
}

bool IsoMovingObject::isEatingOther(IsoMovingObject other) {
 // TODO: Implement isEatingOther
 return false;
}

float IsoMovingObject::getDistanceSq(IsoMovingObject other) {
 // TODO: Implement getDistanceSq
 return 0;
}

void IsoMovingObject::setZombiesDontAttack(bool b) {
 // TODO: Implement setZombiesDontAttack
}

bool IsoMovingObject::isZombiesDontAttack() {
 // TODO: Implement isZombiesDontAttack
 return false;
}

void IsoMovingObject::addSquare(IsoGridSquare square) {
 // TODO: Implement addSquare
}

void IsoMovingObject::update() {
 // TODO: Implement update
}

float IsoMovingObject::getClosestListener(float float5, float float6,
 float float7) {
 // TODO: Implement getClosestListener
 return 0;
}

int IsoMovingObject::getFreeSoundSlot(long long1) {
 // TODO: Implement getFreeSoundSlot
 return 0;
}

} // namespace iso
} // namespace zombie
