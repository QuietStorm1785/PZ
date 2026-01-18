#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaHookManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/states/SwipeStatePlayer.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/packets/hit/AttackVars.h"
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoLivingCharacter : public IsoGameCharacter {
public:
 float useChargeDelta = 0.0F;
 const HandWeapon bareHands;
 bool bDoShove = false;
 bool bCollidedWithPushable = false;
 IsoGameCharacter targetOnGround;

 public IsoLivingCharacter(IsoCell cell, float x, float y, float z) {
 super(cell, x, y, z);
 this->bareHands = (HandWeapon)InventoryItemFactory.CreateItem("Base.BareHands");
 }

 bool isCollidedWithPushableThisFrame() {
 return this->bCollidedWithPushable;
 }

 bool AttemptAttack(float ChargeDelta) {
 void* object = nullptr;
 if (!(this->leftHandItem instanceof HandWeapon weapon) {
 weapon = this->bareHands;
 }

 if (weapon != this->bareHands && this instanceof IsoPlayer) {
 AttackVars attackVars = new AttackVars();
 SwipeStatePlayer.instance().CalcAttackVars(this, attackVars);
 this->setDoShove(attackVars.bDoShove);
 if (LuaHookManager.TriggerHook("Attack", this, ChargeDelta, weapon) {
 return false;
 }
 }

 return this->DoAttack(ChargeDelta);
 }

 bool DoAttack(float ChargeDelta) {
 if (this->isDead()) {
 return false;
 } else {
 if (this->leftHandItem != nullptr) {
 InventoryItem item = this->leftHandItem;
 if (item instanceof HandWeapon) {
 this->useHandWeapon = (HandWeapon)item;
 if (this->useHandWeapon.getCondition() <= 0) {
 return false;
 }

 int int0 = this->Moodles.getMoodleLevel(MoodleType.Endurance);
 if (this->useHandWeapon.isCantAttackWithLowestEndurance() && int0 == 4) {
 return false;
 }

 int int1 = 0;
 if (this->useHandWeapon.isRanged()) {
 int int2 = this->useHandWeapon.getRecoilDelay();
 float float0 = int2 * (1.0F - this->getPerkLevel(PerkFactory.Perks.Aiming) / 30.0F);
 this->setRecoilDelay(float0.intValue());
 }

 if (this instanceof IsoSurvivor && this->useHandWeapon.isRanged() && int1 < this->useHandWeapon.getMaxHitCount()) {
 for (int int3 = 0; int3 < this->getCell().getObjectList().size(); int3++) {
 IsoMovingObject movingObject = this->getCell().getObjectList().get(int3);
 if (movingObject != this
 && movingObject.isShootable()
 && this->IsAttackRange(movingObject.getX(), movingObject.getY(), movingObject.getZ())) {
 float float1 = 1.0F;
 if (float1 > 0.0F) {
 Vector2 vector0 = new Vector2(this->getX(), this->getY());
 Vector2 vector1 = new Vector2(movingObject.getX(), movingObject.getY());
 vector1.x = vector1.x - vector0.x;
 vector1.y = vector1.y - vector0.y;
 bool boolean0 = false;
 if (vector1.x == 0.0F && vector1.y == 0.0F) {
 boolean0 = true;
 }

 Vector2 vector2 = this->getForwardDirection();
 this->DirectionFromVector(vector2);
 vector1.normalize();
 float float2 = vector1.dot(vector2);
 if (boolean0) {
 float2 = 1.0F;
 }

 if (float2 > 1.0F) {
 float2 = 1.0F;
 }

 if (float2 < -1.0F) {
 float2 = -1.0F;
 }

 if (float2 >= this->useHandWeapon.getMinAngle() && float2 <= this->useHandWeapon.getMaxAngle()) {
 int1++;
 }

 if (int1 >= this->useHandWeapon.getMaxHitCount()) {
 break;
 }
 }
 }
 }
 }

 if (UIManager.getPicked() != nullptr) {
 this->attackTargetSquare = UIManager.getPicked().square;
 if (UIManager.getPicked().tile instanceof IsoMovingObject) {
 this->attackTargetSquare = ((IsoMovingObject)UIManager.getPicked().tile).getCurrentSquare();
 }
 }

 if (this->useHandWeapon.getAmmoType() != nullptr && !this->inventory.contains(this->useHandWeapon.getAmmoType())) {
 return false;
 }

 if (this->useHandWeapon.getOtherHandRequire() == nullptr
 || this->rightHandItem != nullptr && this->rightHandItem.getType() == this->useHandWeapon.getOtherHandRequire())) {
 if (!this->useHandWeapon.isRanged()) {
 this->getEmitter().playSound(this->useHandWeapon.getSwingSound(), this);
 WorldSoundManager.instance
 .addSound(
 this,
 (int)this->getX(),
 (int)this->getY(),
 (int)this->getZ(),
 this->useHandWeapon.getSoundRadius(),
 this->useHandWeapon.getSoundVolume()
 );
 }

 this->AttackWasSuperAttack = this->superAttack;
 this->changeState(SwipeStatePlayer.instance());
 if (this->useHandWeapon.getAmmoType() != nullptr) {
 if (this instanceof IsoPlayer) {
 IsoPlayer.getInstance().inventory.RemoveOneOf(this->useHandWeapon.getAmmoType());
 } else {
 this->inventory.RemoveOneOf(this->useHandWeapon.getAmmoType());
 }
 }

 if (this->useHandWeapon.isUseSelf() && this->leftHandItem != nullptr) {
 this->leftHandItem.Use();
 }

 if (this->useHandWeapon.isOtherHandUse() && this->rightHandItem != nullptr) {
 this->rightHandItem.Use();
 }

 return true;
 }

 return false;
 }
 }

 return false;
 }
 }

 bool isDoShove() {
 return this->bDoShove;
 }

 void setDoShove(bool _bDoShove) {
 this->bDoShove = _bDoShove;
 }
}
} // namespace characters
} // namespace zombie
