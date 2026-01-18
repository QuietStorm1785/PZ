#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ai/states/PlayerFallDownState.h"
#include "zombie/ai/states/PlayerKnockedDown.h"
#include "zombie/ai/states/PlayerOnGroundState.h"
#include "zombie/ai/states/ZombieFallDownState.h"
#include "zombie/ai/states/ZombieOnGroundState.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameServer.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PolygonalMap2.h"

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class HitReactionNetworkAI {
public:
 static const float G = 2.0F;
 static const float DURATION = 600.0F;
 const Vector2 startPosition = new Vector2();
 const Vector2 finalPosition = new Vector2();
 uint8_t finalPositionZ = 0;
 const Vector2 startDirection = new Vector2();
 const Vector2 finalDirection = new Vector2();
 float startAngle;
 float finalAngle;
 const IsoGameCharacter character;
 long startTime;

 public HitReactionNetworkAI(IsoGameCharacter _character) {
 this->character = _character;
 this->startTime = 0L;
 }

 bool isSetup() {
 return this->finalPosition.x != 0.0F && this->finalPosition.y != 0.0F;
 }

 bool isStarted() {
 return this->startTime > 0L;
 }

 void start() {
 if (this->isSetup() && !this->isStarted()) {
 this->startTime = GameTime.getServerTimeMills();
 if (this->startPosition.x != this->character.x || this->startPosition.y != this->character.y) {
 DebugLog.Multiplayer.warn("HitReaction start shifted");
 }

 DebugLog.Damage
 .trace(
 "id=%d: %s / %s => %s", this->character.getOnlineID(), this->getActualDescription(), this->getStartDescription(), this->getFinalDescription()
 );
 }
 }

 void finish() {
 if (this->startTime != 0L) {
 DebugLog.Damage
 .trace(
 "id=%d: %s / %s => %s", this->character.getOnlineID(), this->getActualDescription(), this->getStartDescription(), this->getFinalDescription()
 );
 }

 this->startTime = 0L;
 this->setup(0.0F, 0.0F, (byte)0, 0.0F);
 }

 void setup(float dropPositionX, float dropPositionY, uint8_t dropPositionZ, float angle) {
 this->startPosition.set(this->character.x, this->character.y);
 this->finalPosition.set(dropPositionX, dropPositionY);
 this->finalPositionZ = dropPositionZ;
 this->startDirection.set(this->character.getForwardDirection());
 this->startAngle = this->character.getAnimAngleRadians();
 Vector2 vector = new Vector2().set(this->finalPosition.x - this->startPosition.x, this->finalPosition.y - this->startPosition.y);
 if (angle == nullptr) {
 vector.normalize();
 angle = vector.dot(this->character.getForwardDirection());
 PZMath.lerp(this->finalDirection, vector, this->character.getForwardDirection(), Math.abs(angle);
 IsoMovingObject.getVectorFromDirection(this->finalDirection, IsoDirections.fromAngle(this->finalDirection);
 } else {
 this->finalDirection.setLengthAndDirection(angle, 1.0F);
 }

 this->finalAngle = angle;
 if (this->isSetup()) {
 DebugLog.Damage
 .trace(
 "id=%d: %s / %s => %s", this->character.getOnlineID(), this->getActualDescription(), this->getStartDescription(), this->getFinalDescription()
 );
 }
 }

 void moveInternal(float float0, float float1, float float2, float float3) {
 this->character.nx = float0;
 this->character.ny = float1;
 this->character.setDir(IsoDirections.fromAngle(float2, float3);
 this->character.setForwardDirection(float2, float3);
 this->character.getAnimationPlayer().SetForceDir(this->character.getForwardDirection());
 }

 void moveFinal() {
 this->moveInternal(this->finalPosition.x, this->finalPosition.y, this->finalDirection.x, this->finalDirection.y);
 this->character.lx = this->character.nx = this->character.x = this->finalPosition.x;
 this->character.ly = this->character.ny = this->character.y = this->finalPosition.y;
 this->character
 .setCurrent(
 IsoWorld.instance.CurrentCell.getGridSquare((double)((int)this->finalPosition.x), (double)((int)this->finalPosition.y), (double)this->character.z)
 );
 DebugLog.Damage
 .trace("id=%d: %s / %s => %s", this->character.getOnlineID(), this->getActualDescription(), this->getStartDescription(), this->getFinalDescription());
 }

 void move() {
 if (this->finalPositionZ != (byte)this->character.z) {
 DebugLog.Damage
 .trace("HitReaction interrupt id=%d: z-final:%d z-current=%d", this->character.getOnlineID(), this->finalPositionZ, (byte)this->character.z);
 this->finish();
 } else {
 float float0 = Math.min(1.0F, Math.max(0.0F, (float)(GameTime.getServerTimeMills() - this->startTime) / 600.0F);
 if (this->startPosition.x == this->finalPosition.x && this->startPosition.y == this->finalPosition.y) {
 float0 = 1.0F;
 }

 if (float0 < 1.0F) {
 float0 = (PZMath.gain(float0 * 0.5F + 0.5F, 2.0F) - 0.5F) * 2.0F;
 this->moveInternal(
 PZMath.lerp(this->startPosition.x, this->finalPosition.x, float0),
 PZMath.lerp(this->startPosition.y, this->finalPosition.y, float0),
 PZMath.lerp(this->startDirection.x, this->finalDirection.x, float0),
 PZMath.lerp(this->startDirection.y, this->finalDirection.y, float0)
 );
 } else {
 this->moveFinal();
 this->finish();
 }
 }
 }

 bool isDoSkipMovement() {
 if (this->character instanceof IsoZombie) {
 return this->character.isCurrentState(ZombieFallDownState.instance()) || this->character.isCurrentState(ZombieOnGroundState.instance());
 } else {
 return !(this->character instanceof IsoPlayer)
 ? false
 : this->character.isCurrentState(PlayerFallDownState.instance())
 || this->character.isCurrentState(PlayerKnockedDown.instance())
 || this->character.isCurrentState(PlayerOnGroundState.instance());
 }
 }

 std::string getStartDescription() {
 return String.format(
 "start=[ pos=( %f ; %f ) dir=( %f ; %f ) angle=%f ]",
 this->startPosition.x,
 this->startPosition.y,
 this->startDirection.x,
 this->startDirection.y,
 this->startAngle
 );
 }

 std::string getFinalDescription() {
 return String.format(
 "final=[ pos=( %f ; %f ) dir=( %f ; %f ) angle=%f ]",
 this->finalPosition.x,
 this->finalPosition.y,
 this->finalDirection.x,
 this->finalDirection.y,
 this->finalAngle
 );
 }

 std::string getActualDescription() {
 return String.format(
 "actual=[ pos=( %f ; %f ) dir=( %f ; %f ) angle=%f ]",
 this->character.x,
 this->character.y,
 this->character.getForwardDirection().getX(),
 this->character.getForwardDirection().getY(),
 this->character.getAnimAngleRadians()
 );
 }

 std::string getDescription() {
 return String.format(
 "start=%d | (x=%f,y=%f;a=%f;l=%f)",
 this->startTime,
 this->finalPosition.x,
 this->finalPosition.y,
 this->finalAngle,
 IsoUtils.DistanceTo(this->startPosition.x, this->startPosition.y, this->finalPosition.x, this->finalPosition.y)
 );
 }

 static void CalcHitReactionWeapon(IsoGameCharacter wielder, IsoGameCharacter target, HandWeapon weapon) {
 HitReactionNetworkAI hitReactionNetworkAI = target.getHitReactionNetworkAI();
 if (target.isOnFloor()) {
 hitReactionNetworkAI.setup(target.x, target.y, (byte)target.z, target.getAnimAngleRadians());
 } else {
 Vector2 vector = new Vector2();
 float float0 = target.calcHitDir(wielder, weapon, vector);
 if (target instanceof IsoPlayer) {
 vector.x = (vector.x + target.x + ((IsoPlayer)target).networkAI.targetX) * 0.5F;
 vector.y = (vector.y + target.y + ((IsoPlayer)target).networkAI.targetY) * 0.5F;
 } else {
 vector.x = vector.x + target.x;
 vector.y = vector.y + target.y;
 }

 vector.x = PZMath.roundFromEdges(vector.x);
 vector.y = PZMath.roundFromEdges(vector.y);
 if (PolygonalMap2.instance.lineClearCollide(target.x, target.y, vector.x, vector.y, (int)target.z, nullptr, false, true) {
 vector.x = target.x;
 vector.y = target.y;
 }

 hitReactionNetworkAI.setup(vector.x, vector.y, (byte)target.z, float0);
 }

 if (hitReactionNetworkAI.isSetup()) {
 hitReactionNetworkAI.start();
 }
 }

 static void CalcHitReactionVehicle(IsoGameCharacter target, BaseVehicle vehicle) {
 HitReactionNetworkAI hitReactionNetworkAI = target.getHitReactionNetworkAI();
 if (!hitReactionNetworkAI.isStarted()) {
 if (target.isOnFloor()) {
 hitReactionNetworkAI.setup(target.x, target.y, (byte)target.z, target.getAnimAngleRadians());
 } else {
 Vector2 vector = new Vector2();
 target.calcHitDir(vector);
 if (target instanceof IsoPlayer) {
 vector.x = (vector.x + target.x + ((IsoPlayer)target).networkAI.targetX) * 0.5F;
 vector.y = (vector.y + target.y + ((IsoPlayer)target).networkAI.targetY) * 0.5F;
 } else {
 vector.x = vector.x + target.x;
 vector.y = vector.y + target.y;
 }

 vector.x = PZMath.roundFromEdges(vector.x);
 vector.y = PZMath.roundFromEdges(vector.y);
 if (PolygonalMap2.instance.lineClearCollide(target.x, target.y, vector.x, vector.y, (int)target.z, vehicle, false, true) {
 vector.x = target.x;
 vector.y = target.y;
 }

 hitReactionNetworkAI.setup(vector.x, vector.y, (byte)target.z, nullptr);
 }
 }

 if (hitReactionNetworkAI.isSetup()) {
 hitReactionNetworkAI.start();
 }
 }

 void process(float dropPositionX, float dropPositionY, float dropPositionZ, float dropDirection) {
 this->setup(dropPositionX, dropPositionY, (byte)dropPositionZ, dropDirection);
 this->start();
 if (GameServer.bServer) {
 this->moveFinal();
 this->finish();
 }
 }
}
} // namespace characters
} // namespace zombie
