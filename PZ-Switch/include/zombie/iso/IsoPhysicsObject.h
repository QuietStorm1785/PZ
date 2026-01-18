#pragma once
#include "zombie/core/PerformanceSettings.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoPhysicsObject : public IsoMovingObject {
public:
 float speedMod = 1.0F;
 float velX = 0.0F;
 float velY = 0.0F;
 float velZ = 0.0F;
 float terminalVelocity = -0.05F;

public
 IsoPhysicsObject(IsoCell cell) {
 super(cell);
 this->solid = false;
 this->shootable = false;
 }

 void collideGround() {}

 void collideWall() {}

 void update() {
 IsoGridSquare square = this->getCurrentSquare();
 super.update();
 if (this->isCollidedThisFrame()) {
 if (this->isCollidedN() || this->isCollidedS()) {
 this->velY = -this->velY;
 this->velY *= 0.5F;
 this->collideWall();
 }

 if (this->isCollidedE() || this->isCollidedW()) {
 this->velX = -this->velX;
 this->velX *= 0.5F;
 this->collideWall();
 }
 }

 int int0 = GameServer.bServer ? 10 : PerformanceSettings.getLockFPS();
 float float0 = 30.0F / int0;
 float float1 = 0.1F * this->speedMod * float0;
 float1 = 1.0F - float1;
 this->velX *= float1;
 this->velY *= float1;
 this->velZ -= 0.005F * float0;
 if (this->velZ < this->terminalVelocity) {
 this->velZ = this->terminalVelocity;
 }

 this->setNx(this->getNx() + this->velX * this->speedMod * 0.3F * float0);
 this->setNy(this->getNy() + this->velY * this->speedMod * 0.3F * float0);
 float float2 = this->getZ();
 this->setZ(this->getZ() + this->velZ * 0.4F * float0);
 if (this->getZ() < 0.0F) {
 this->setZ(0.0F);
 this->velZ = -this->velZ * 0.5F;
 this->collideGround();
 }

 if (this->getCurrentSquare() != nullptr && (int)this->getZ() < (int)float2 &&
 (square != nullptr && square.TreatAsSolidFloor() ||
 this->getCurrentSquare().TreatAsSolidFloor())) {
 this->setZ((int)float2);
 this->velZ = -this->velZ * 0.5F;
 this->collideGround();
 }

 if (Math.abs(this->velX) < 1.0E-4F) {
 this->velX = 0.0F;
 }

 if (Math.abs(this->velY) < 1.0E-4F) {
 this->velY = 0.0F;
 }

 if (this->velX + this->velY == 0.0F) {
 this->sprite.Animate = false;
 }

 this->sx = this->sy = 0.0F;
 }

 float getGlobalMovementMod(bool bDoNoises) { return 1.0F; }
}
} // namespace iso
} // namespace zombie
