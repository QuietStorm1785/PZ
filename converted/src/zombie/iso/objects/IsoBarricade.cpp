#include "zombie/iso/objects/IsoBarricade.h"

namespace zombie {
namespace iso {
namespace objects {

public IsoBarricade::IsoBarricade(IsoCell cell) {
 // TODO: Implement IsoBarricade
 return nullptr;
}

public IsoBarricade::IsoBarricade(IsoCell cell, IsoGridSquare gridSquare, IsoDirections dir) {
 // TODO: Implement IsoBarricade
 return nullptr;
}

std::string IsoBarricade::getObjectName() {
 // TODO: Implement getObjectName
 return "";
}

void IsoBarricade::addPlank(IsoGameCharacter chr, InventoryItem plank) {
 // TODO: Implement addPlank
}

InventoryItem IsoBarricade::removePlank(IsoGameCharacter chr) {
 // TODO: Implement removePlank
 return nullptr;
}

int IsoBarricade::getNumPlanks() {
 // TODO: Implement getNumPlanks
 return 0;
}

bool IsoBarricade::canAddPlank() {
 // TODO: Implement canAddPlank
 return false;
}

void IsoBarricade::addMetalBar(IsoGameCharacter chr, InventoryItem metalBar) {
 // TODO: Implement addMetalBar
}

InventoryItem IsoBarricade::removeMetalBar(IsoGameCharacter chr) {
 // TODO: Implement removeMetalBar
 return nullptr;
}

void IsoBarricade::addMetal(IsoGameCharacter chr, InventoryItem metal) {
 // TODO: Implement addMetal
}

bool IsoBarricade::isMetalBar() {
 // TODO: Implement isMetalBar
 return false;
}

InventoryItem IsoBarricade::removeMetal(IsoGameCharacter chr) {
 // TODO: Implement removeMetal
 return nullptr;
}

bool IsoBarricade::isMetal() {
 // TODO: Implement isMetal
 return false;
}

bool IsoBarricade::isBlockVision() {
 // TODO: Implement isBlockVision
 return false;
}

void IsoBarricade::chooseSprite() {
 // TODO: Implement chooseSprite
}

bool IsoBarricade::isDestroyed() {
 // TODO: Implement isDestroyed
 return false;
}

bool IsoBarricade::TestCollide(IsoMovingObject obj, IsoGridSquare from, IsoGridSquare to) {
 // TODO: Implement TestCollide
 return false;
}

void IsoBarricade::Thump(IsoMovingObject thumper) {
 // TODO: Implement Thump
}

Thumpable IsoBarricade::getThumpableFor(IsoGameCharacter chr) {
 // TODO: Implement getThumpableFor
 return nullptr;
}

Vector2 IsoBarricade::getFacingPosition(Vector2 pos) {
 // TODO: Implement getFacingPosition
 return nullptr;
}

void IsoBarricade::WeaponHit(IsoGameCharacter owner, HandWeapon weapon) {
 // TODO: Implement WeaponHit
}

void IsoBarricade::DamageBarricade(int amount) {
 // TODO: Implement DamageBarricade
}

void IsoBarricade::Damage(int amount) {
 // TODO: Implement Damage
}

float IsoBarricade::getThumpCondition() {
 // TODO: Implement getThumpCondition
 return 0;
}

void IsoBarricade::load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 // TODO: Implement load
}

void IsoBarricade::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 // TODO: Implement save
}

void IsoBarricade::saveChange(const std::string& change, KahluaTable tbl, ByteBuffer bb) {
 // TODO: Implement saveChange
}

void IsoBarricade::loadChange(const std::string& change, ByteBuffer bb) {
 // TODO: Implement loadChange
}

BarricadeAble IsoBarricade::getBarricadedObject() {
 // TODO: Implement getBarricadedObject
 return nullptr;
}

void IsoBarricade::render(float x, float y, float z, ColorInfo col, bool bDoAttached, bool bWallLightingPass, Shader shader) {
 // TODO: Implement render
}

IsoBarricade IsoBarricade::GetBarricadeOnSquare(IsoGridSquare square, IsoDirections dir) {
 // TODO: Implement GetBarricadeOnSquare
 return nullptr;
}

IsoBarricade IsoBarricade::GetBarricadeForCharacter(BarricadeAble obj, IsoGameCharacter chr) {
 // TODO: Implement GetBarricadeForCharacter
 return nullptr;
}

return IsoBarricade::GetBarricadeOnSquare() {
 // TODO: Implement GetBarricadeOnSquare
 return nullptr;
}

return IsoBarricade::GetBarricadeOnSquare() {
 // TODO: Implement GetBarricadeOnSquare
 return nullptr;
}

return IsoBarricade::GetBarricadeOnSquare() {
 // TODO: Implement GetBarricadeOnSquare
 return nullptr;
}

IsoBarricade IsoBarricade::GetBarricadeOppositeCharacter(BarricadeAble obj, IsoGameCharacter chr) {
 // TODO: Implement GetBarricadeOppositeCharacter
 return nullptr;
}

return IsoBarricade::GetBarricadeOnSquare() {
 // TODO: Implement GetBarricadeOnSquare
 return nullptr;
}

return IsoBarricade::GetBarricadeOnSquare() {
 // TODO: Implement GetBarricadeOnSquare
 return nullptr;
}

return IsoBarricade::GetBarricadeOnSquare() {
 // TODO: Implement GetBarricadeOnSquare
 return nullptr;
}

IsoBarricade IsoBarricade::AddBarricadeToObject(BarricadeAble to, bool addOpposite) {
 // TODO: Implement AddBarricadeToObject
 return nullptr;
}

IsoBarricade IsoBarricade::AddBarricadeToObject(BarricadeAble to, IsoGameCharacter chr) {
 // TODO: Implement AddBarricadeToObject
 return nullptr;
}

return IsoBarricade::AddBarricadeToObject() {
 // TODO: Implement AddBarricadeToObject
 return nullptr;
}

return IsoBarricade::AddBarricadeToObject() {
 // TODO: Implement AddBarricadeToObject
 return nullptr;
}

} // namespace objects
} // namespace iso
} // namespace zombie
