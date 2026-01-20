#include <string>
#include "zombie\iso\objects/IsoBarricade.h"

namespace zombie {
namespace iso {
namespace objects {

public IsoBarricade::IsoBarricade(IsoCell var1) {
    // TODO: Implement IsoBarricade
    return nullptr;
}

public IsoBarricade::IsoBarricade(IsoCell var1, IsoGridSquare var2, IsoDirections var3) {
    // TODO: Implement IsoBarricade
    return nullptr;
}

std::string IsoBarricade::getObjectName() {
    // TODO: Implement getObjectName
    return "";
}

void IsoBarricade::addPlank(IsoGameCharacter var1, InventoryItem var2) {
    // TODO: Implement addPlank
}

InventoryItem IsoBarricade::removePlank(IsoGameCharacter var1) {
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

void IsoBarricade::addMetalBar(IsoGameCharacter var1, InventoryItem var2) {
    // TODO: Implement addMetalBar
}

InventoryItem IsoBarricade::removeMetalBar(IsoGameCharacter var1) {
    // TODO: Implement removeMetalBar
    return nullptr;
}

void IsoBarricade::addMetal(IsoGameCharacter var1, InventoryItem var2) {
    // TODO: Implement addMetal
}

bool IsoBarricade::isMetalBar() {
    // TODO: Implement isMetalBar
    return false;
}

InventoryItem IsoBarricade::removeMetal(IsoGameCharacter var1) {
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

bool IsoBarricade::TestCollide(IsoMovingObject var1, IsoGridSquare var2, IsoGridSquare var3) {
    // TODO: Implement TestCollide
    return false;
}

VisionResult IsoBarricade::TestVision(IsoGridSquare var1, IsoGridSquare var2) {
    // TODO: Implement TestVision
    return nullptr;
}

void IsoBarricade::Thump(IsoMovingObject var1) {
    // TODO: Implement Thump
}

Thumpable IsoBarricade::getThumpableFor(IsoGameCharacter var1) {
    // TODO: Implement getThumpableFor
    return nullptr;
}

Vector2 IsoBarricade::getFacingPosition(Vector2 var1) {
    // TODO: Implement getFacingPosition
    return nullptr;
}

void IsoBarricade::WeaponHit(IsoGameCharacter var1, HandWeapon var2) {
    // TODO: Implement WeaponHit
}

void IsoBarricade::DamageBarricade(int var1) {
    // TODO: Implement DamageBarricade
}

void IsoBarricade::Damage(int var1) {
    // TODO: Implement Damage
}

float IsoBarricade::getThumpCondition() {
    // TODO: Implement getThumpCondition
    return 0;
}

void IsoBarricade::load(ByteBuffer var1, int var2, bool var3) {
    // TODO: Implement load
}

void IsoBarricade::save(ByteBuffer var1, bool var2) {
    // TODO: Implement save
}

void IsoBarricade::saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
    // TODO: Implement saveChange
}

void IsoBarricade::loadChange(const std::string& var1, ByteBuffer var2) {
    // TODO: Implement loadChange
}

BarricadeAble IsoBarricade::getBarricadedObject() {
    // TODO: Implement getBarricadedObject
    return nullptr;
}

void IsoBarricade::render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
    // TODO: Implement render
}

IsoBarricade IsoBarricade::GetBarricadeOnSquare(IsoGridSquare var0, IsoDirections var1) {
    // TODO: Implement GetBarricadeOnSquare
    return nullptr;
}

IsoBarricade IsoBarricade::GetBarricadeForCharacter(BarricadeAble var0, IsoGameCharacter var1) {
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

IsoBarricade IsoBarricade::GetBarricadeOppositeCharacter(BarricadeAble var0, IsoGameCharacter var1) {
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

IsoBarricade IsoBarricade::AddBarricadeToObject(BarricadeAble var0, bool var1) {
    // TODO: Implement AddBarricadeToObject
    return nullptr;
}

IsoBarricade IsoBarricade::AddBarricadeToObject(BarricadeAble var0, IsoGameCharacter var1) {
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
