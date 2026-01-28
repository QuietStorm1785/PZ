#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/vec3.hpp>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace vehicles {


class BaseVehicle {
public:
    static const float speedCap = 10.0F;
    const Vector3f velocity = std::make_shared<Vector3f>();
    const Vector2 collision = std::make_shared<Vector2>();
    float dot;
    float vehicleImpulse;
    float vehicleSpeed;
    const Vector3f targetImpulse = std::make_shared<Vector3f>();
    bool isVehicleHitFromFront;
    bool isTargetHitFromBehind;
    int vehicleDamage;
    float hitSpeed;

    void calc(IsoGameCharacter var1, BaseVehicle var2) {
      var2.getLinearVelocity(this.velocity);
      this.velocity.y = 0.0F;
      if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
         this.vehicleSpeed = Math.min(this.velocity.length(), 10.0F);
         this.hitSpeed = this.vehicleSpeed + var2.getClientForce() / var2.getFudgedMass();
      } else {
         this.vehicleSpeed = (float)Math.sqrt(this.velocity.x * this.velocity.x + this.velocity.z * this.velocity.z);
         if (var1.isOnFloor()) {
            this.hitSpeed = Math.max(this.vehicleSpeed * 6.0F, 5.0F);
         } else {
            this.hitSpeed = Math.max(this.vehicleSpeed * 2.0F, 5.0F);
         }
      }

      this.targetImpulse.set(var2.x - var1.x, 0.0F, var2.y - var1.y);
      this.targetImpulse.normalize();
      this.velocity.normalize();
      this.dot = this.velocity.dot(this.targetImpulse);
      this.targetImpulse.normalize();
      this.targetImpulse.mul(3.0F * this.vehicleSpeed / 10.0F);
      this.targetImpulse.set(this.targetImpulse.x, this.targetImpulse.y, this.targetImpulse.z);
      this.vehicleImpulse = var2.getFudgedMass() * 7.0F * this.vehicleSpeed / 10.0F * Math.abs(this.dot);
      this.isTargetHitFromBehind = "BEHIND" == var1.testDotSide(var2));
   }
}
} // namespace vehicles
} // namespace zombie
