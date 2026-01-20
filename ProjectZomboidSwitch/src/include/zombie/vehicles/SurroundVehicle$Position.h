#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "org/joml/Vector3f.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/vehicles/SurroundVehicle/PositionSide.h"

namespace zombie {
namespace vehicles {


class SurroundVehicle {
public:
    const Vector2f posLocal = std::make_shared<Vector2f>();
    const Vector3f posWorld = std::make_shared<Vector3f>();
    const Vector3f posAxis = std::make_shared<Vector3f>();
    PositionSide side;
    IsoZombie zombie;
    float targetX;
    float targetY;
    bool bBlocked;

   private SurroundVehicle$Position() {
   }

    bool isOccupied() {
      return this.zombie != nullptr;
   }

    void checkBlocked(BaseVehicle var1) {
      this.bBlocked = PolygonalMap2.instance.lineClearCollide(this.posWorld.x, this.posWorld.y, this.posAxis.x, this.posAxis.y, (int)var1.z, var1);
      if (!this.bBlocked) {
         this.bBlocked = !PolygonalMap2.instance.canStandAt(this.posWorld.x, this.posWorld.y, (int)var1.z, var1, false, false);
      }
   }
}
} // namespace vehicles
} // namespace zombie
