#include "zombie/iso/objects/IsoDoor.h"

namespace zombie {
namespace iso {
namespace objects {

public IsoDoor::IsoDoor(IsoCell cell) {
 // TODO: Implement IsoDoor
 return nullptr;
}

std::string IsoDoor::getObjectName() {
 // TODO: Implement getObjectName
 return "";
}

void IsoDoor::render(float x, float y, float z, ColorInfo info, bool bDoAttached, bool bWallLightingPass, Shader shader) {
 // TODO: Implement render
}

void IsoDoor::checkKeyHighlight(float float1, float float0) {
 // TODO: Implement checkKeyHighlight
}

void IsoDoor::prerender(float float0, float float1, float float2, ColorInfo colorInfo, bool boolean0, bool boolean1, IsoDirections directions) {
 // TODO: Implement prerender
}

void IsoDoor::postrender(float float0, float float1, float float2, ColorInfo colorInfo, bool boolean0, bool boolean1, IsoDirections directions) {
 // TODO: Implement postrender
}

void IsoDoor::prerender1xN(float float0, float float2, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement prerender1xN
}

void IsoDoor::postrender1xN(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement postrender1xN
}

void IsoDoor::prerender1xS(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement prerender1xS
}

void IsoDoor::postrender1xS(float float0, float float2, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement postrender1xS
}

void IsoDoor::prerender1xW(float float2, float float0, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement prerender1xW
}

void IsoDoor::postrender1xW(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement postrender1xW
}

void IsoDoor::prerender1xE(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement prerender1xE
}

void IsoDoor::postrender1xE(float float2, float float0, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement postrender1xE
}

void IsoDoor::prerender2xN(float float0, float float2, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement prerender2xN
}

void IsoDoor::postrender2xN(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement postrender2xN
}

void IsoDoor::prerender2xS(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement prerender2xS
}

void IsoDoor::postrender2xS(float float0, float float2, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement postrender2xS
}

void IsoDoor::prerender2xW(float float2, float float0, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement prerender2xW
}

void IsoDoor::postrender2xW(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement postrender2xW
}

void IsoDoor::prerender2xE(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement prerender2xE
}

void IsoDoor::postrender2xE(float float2, float float0, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 // TODO: Implement postrender2xE
}

IsoDirections IsoDoor::getSpriteEdge(bool ignoreOpen) {
 // TODO: Implement getSpriteEdge
 return nullptr;
}

public IsoDoor::IsoDoor(IsoCell cell, IsoGridSquare gridSquare, IsoSprite _gid, bool _north) {
 // TODO: Implement IsoDoor
 return nullptr;
}

public IsoDoor::IsoDoor(IsoCell cell, IsoGridSquare gridSquare, const std::string& _gid, bool _north) {
 // TODO: Implement IsoDoor
 return nullptr;
}

public IsoDoor::IsoDoor(IsoCell cell, IsoGridSquare gridSquare, const std::string& _gid, bool _north, KahluaTable _table) {
 // TODO: Implement IsoDoor
 return nullptr;
}

void IsoDoor::load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 // TODO: Implement load
}

void IsoDoor::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 // TODO: Implement save
}

void IsoDoor::saveState(ByteBuffer bb) {
 // TODO: Implement saveState
}

void IsoDoor::loadState(ByteBuffer bb) {
 // TODO: Implement loadState
}

bool IsoDoor::isDestroyed() {
 // TODO: Implement isDestroyed
 return false;
}

bool IsoDoor::IsOpen() {
 // TODO: Implement IsOpen
 return false;
}

bool IsoDoor::IsStrengthenedByPushedItems() {
 // TODO: Implement IsStrengthenedByPushedItems
 return false;
}

bool IsoDoor::onMouseLeftClick(int x, int y) {
 // TODO: Implement onMouseLeftClick
 return false;
}

bool IsoDoor::TestPathfindCollide(IsoMovingObject obj, IsoGridSquare from, IsoGridSquare to) {
 // TODO: Implement TestPathfindCollide
 return false;
}

bool IsoDoor::TestCollide(IsoMovingObject obj, IsoGridSquare from, IsoGridSquare to) {
 // TODO: Implement TestCollide
 return false;
}

void IsoDoor::Thump(IsoMovingObject thumper) {
 // TODO: Implement Thump
}

Thumpable IsoDoor::getThumpableFor(IsoGameCharacter chr) {
 // TODO: Implement getThumpableFor
 return nullptr;
}

float IsoDoor::getThumpCondition() {
 // TODO: Implement getThumpCondition
 return 0;
}

void IsoDoor::WeaponHit(IsoGameCharacter owner, HandWeapon weapon) {
 // TODO: Implement WeaponHit
}

void IsoDoor::destroy() {
 // TODO: Implement destroy
}

IsoGridSquare IsoDoor::getOtherSideOfDoor(IsoGameCharacter chr) {
 // TODO: Implement getOtherSideOfDoor
 return nullptr;
}

bool IsoDoor::isExteriorDoor(IsoGameCharacter chr) {
 // TODO: Implement isExteriorDoor
 return false;
}

bool IsoDoor::isExterior() {
 // TODO: Implement isExterior
 return false;
}

bool IsoDoor::isHoppable() {
 // TODO: Implement isHoppable
 return false;
}

bool IsoDoor::canClimbOver(IsoGameCharacter chr) {
 // TODO: Implement canClimbOver
 return false;
}

void IsoDoor::ToggleDoorActual(IsoGameCharacter chr) {
 // TODO: Implement ToggleDoorActual
}

void IsoDoor::syncIsoObjectSend(ByteBufferWriter b) {
 // TODO: Implement syncIsoObjectSend
}

void IsoDoor::syncIsoObject(bool bRemote, uint8_t val, UdpConnection source, ByteBuffer bb) {
 // TODO: Implement syncIsoObject
}

void IsoDoor::ToggleDoor(IsoGameCharacter chr) {
 // TODO: Implement ToggleDoor
}

void IsoDoor::ToggleDoorSilent() {
 // TODO: Implement ToggleDoorSilent
}

void IsoDoor::Damage(int int0) {
 // TODO: Implement Damage
}

IsoBarricade IsoDoor::getBarricadeOnSameSquare() {
 // TODO: Implement getBarricadeOnSameSquare
 return nullptr;
}

IsoBarricade IsoDoor::getBarricadeOnOppositeSquare() {
 // TODO: Implement getBarricadeOnOppositeSquare
 return nullptr;
}

bool IsoDoor::isBarricaded() {
 // TODO: Implement isBarricaded
 return false;
}

bool IsoDoor::isBarricadeAllowed() {
 // TODO: Implement isBarricadeAllowed
 return false;
}

IsoBarricade IsoDoor::getBarricadeForCharacter(IsoGameCharacter chr) {
 // TODO: Implement getBarricadeForCharacter
 return nullptr;
}

IsoBarricade IsoDoor::getBarricadeOppositeCharacter(IsoGameCharacter chr) {
 // TODO: Implement getBarricadeOppositeCharacter
 return nullptr;
}

bool IsoDoor::isLocked() {
 // TODO: Implement isLocked
 return false;
}

void IsoDoor::setLocked(bool bLocked) {
 // TODO: Implement setLocked
}

bool IsoDoor::getNorth() {
 // TODO: Implement getNorth
 return false;
}

Vector2 IsoDoor::getFacingPosition(Vector2 pos) {
 // TODO: Implement getFacingPosition
 return nullptr;
}

Vector2 IsoDoor::getFacingPositionAlt(Vector2 pos) {
 // TODO: Implement getFacingPositionAlt
 return nullptr;
}

void IsoDoor::setIsLocked(bool lock) {
 // TODO: Implement setIsLocked
}

IsoSprite IsoDoor::getOpenSprite() {
 // TODO: Implement getOpenSprite
 return nullptr;
}

void IsoDoor::setOpenSprite(IsoSprite sprite) {
 // TODO: Implement setOpenSprite
}

int IsoDoor::getKeyId() {
 // TODO: Implement getKeyId
 return 0;
}

void IsoDoor::syncDoorKey() {
 // TODO: Implement syncDoorKey
}

void IsoDoor::setKeyId(int keyId) {
 // TODO: Implement setKeyId
}

bool IsoDoor::isLockedByKey() {
 // TODO: Implement isLockedByKey
 return false;
}

void IsoDoor::setLockedByKey(bool _lockedByKey) {
 // TODO: Implement setLockedByKey
}

bool IsoDoor::haveKey() {
 // TODO: Implement haveKey
 return false;
}

void IsoDoor::setHaveKey(bool _haveKey) {
 // TODO: Implement setHaveKey
}

IsoGridSquare IsoDoor::getOppositeSquare() {
 // TODO: Implement getOppositeSquare
 return nullptr;
}

bool IsoDoor::isAdjacentToSquare(IsoGridSquare square2) {
 // TODO: Implement isAdjacentToSquare
 return false;
}

int IsoDoor::checkKeyId() {
 // TODO: Implement checkKeyId
 return 0;
}

void IsoDoor::setHealth(int _Health) {
 // TODO: Implement setHealth
}

void IsoDoor::initCurtainSprites() {
 // TODO: Implement initCurtainSprites
}

IsoDoor IsoDoor::HasCurtains() {
 // TODO: Implement HasCurtains
 return nullptr;
}

bool IsoDoor::isCurtainOpen() {
 // TODO: Implement isCurtainOpen
 return false;
}

void IsoDoor::setCurtainOpen(bool _open) {
 // TODO: Implement setCurtainOpen
}

void IsoDoor::transmitSetCurtainOpen(bool _open) {
 // TODO: Implement transmitSetCurtainOpen
}

void IsoDoor::toggleCurtain() {
 // TODO: Implement toggleCurtain
}

void IsoDoor::addSheet(IsoGameCharacter chr) {
 // TODO: Implement addSheet
}

void IsoDoor::addSheet(bool inside, IsoGameCharacter chr) {
 // TODO: Implement addSheet
}

void IsoDoor::removeSheet(IsoGameCharacter chr) {
 // TODO: Implement removeSheet
}

IsoGridSquare IsoDoor::getAddSheetSquare(IsoGameCharacter chr) {
 // TODO: Implement getAddSheetSquare
 return nullptr;
}

IsoGridSquare IsoDoor::getSheetSquare() {
 // TODO: Implement getSheetSquare
 return nullptr;
}

int IsoDoor::getHealth() {
 // TODO: Implement getHealth
 return 0;
}

int IsoDoor::getMaxHealth() {
 // TODO: Implement getMaxHealth
 return 0;
}

bool IsoDoor::isFacingSheet(IsoGameCharacter chr) {
 // TODO: Implement isFacingSheet
 return false;
}

void IsoDoor::saveChange(const std::string& change, KahluaTable tbl, ByteBuffer bb) {
 // TODO: Implement saveChange
}

void IsoDoor::loadChange(const std::string& change, ByteBuffer bb) {
 // TODO: Implement loadChange
}

void IsoDoor::addRandomBarricades() {
 // TODO: Implement addRandomBarricades
}

bool IsoDoor::isObstructed() {
 // TODO: Implement isObstructed
 return false;
}

return IsoDoor::isDoorObstructed() {
 // TODO: Implement isDoorObstructed
 return nullptr;
}

bool IsoDoor::isDoorObstructed(IsoObject object) {
 // TODO: Implement isDoorObstructed
 return false;
}

void IsoDoor::toggleDoubleDoor(IsoObject oneOfFour, bool doSync) {
 // TODO: Implement toggleDoubleDoor
}

void IsoDoor::toggleDoubleDoorObject(IsoObject object) {
 // TODO: Implement toggleDoubleDoorObject
}

int IsoDoor::getDoubleDoorIndex(IsoObject oneOfFour) {
 // TODO: Implement getDoubleDoorIndex
 return 0;
}

IsoObject IsoDoor::getDoubleDoorObject(IsoObject oneOfFour, int index) {
 // TODO: Implement getDoubleDoorObject
 return nullptr;
}

bool IsoDoor::isDoubleDoorObstructed(IsoObject oneOfFour) {
 // TODO: Implement isDoubleDoorObstructed
 return false;
}

bool IsoDoor::isSomethingTo(IsoGridSquare square1, IsoGridSquare square0) {
 // TODO: Implement isSomethingTo
 return false;
}

bool IsoDoor::hasSomething4x4(int int0, int int1, int int3, int int4, int int2) {
 // TODO: Implement hasSomething4x4
 return false;
}

return IsoDoor::isSomethingTo() {
 // TODO: Implement isSomethingTo
 return nullptr;
}

bool IsoDoor::destroyDoubleDoor(IsoObject oneOfFour) {
 // TODO: Implement destroyDoubleDoor
 return false;
}

int IsoDoor::getGarageDoorIndex(IsoObject oneOfThree) {
 // TODO: Implement getGarageDoorIndex
 return 0;
}

IsoObject IsoDoor::getGarageDoorPrev(IsoObject oneOfThree) {
 // TODO: Implement getGarageDoorPrev
 return nullptr;
}

IsoObject IsoDoor::getGarageDoorNext(IsoObject oneOfThree) {
 // TODO: Implement getGarageDoorNext
 return nullptr;
}

IsoObject IsoDoor::getGarageDoorFirst(IsoObject oneOfThree) {
 // TODO: Implement getGarageDoorFirst
 return nullptr;
}

void IsoDoor::toggleGarageDoorObject(IsoObject object) {
 // TODO: Implement toggleGarageDoorObject
}

void IsoDoor::toggleGarageDoor(IsoObject oneOfThree, bool doSync) {
 // TODO: Implement toggleGarageDoor
}

bool IsoDoor::isGarageDoorObstructed(IsoObject object0) {
 // TODO: Implement isGarageDoorObstructed
 return false;
}

bool IsoDoor::destroyGarageDoor(IsoObject oneOfThree) {
 // TODO: Implement destroyGarageDoor
 return false;
}

IsoObject IsoDoor::getRenderEffectMaster() {
 // TODO: Implement getRenderEffectMaster
 return nullptr;
}

std::string IsoDoor::getThumpSound() {
 // TODO: Implement getThumpSound
 return "";
}

std::string IsoDoor::getSoundPrefix() {
 // TODO: Implement getSoundPrefix
 return "";
}

void IsoDoor::playDoorSound(BaseCharacterSoundEmitter baseCharacterSoundEmitter, const std::string& string) {
 // TODO: Implement playDoorSound
}

} // namespace objects
} // namespace iso
} // namespace zombie
