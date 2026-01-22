#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/packets/hit/IMovable.h"

namespace zombie {
namespace characters {


class NetworkCharacterAI {
public:
    static const int checkDelay = 5000;
    static const int checkInterval = 1000;
    const UpdateLimit updateLimit = std::make_shared<UpdateLimit>(5000L);
    const Vector2 position = std::make_shared<Vector2>();
    bool isInVehicle;
    float speed;

   private NetworkCharacterAI$SpeedChecker() {
   }

    float getSpeed() {
      return this.speed;
   }

    bool isVehicle() {
      return this.isInVehicle;
   }

    void set(float var1, float var2, bool var3) {
      if (this.updateLimit.Check()) {
         if (5000L == this.updateLimit.getDelay()) {
            this.updateLimit.Reset(1000L);
            this.position.set(0.0F, 0.0F);
            this.speed = 0.0F;
         }

         this.isInVehicle = var3;
         if (this.position.getLength() != 0.0F) {
            this.speed = IsoUtils.DistanceTo(this.position.x, this.position.y, var1, var2);
         }

         this.position.set(var1, var2);
      }
   }

    void reset() {
      this.updateLimit.Reset(5000L);
      this.isInVehicle = false;
      this.position.set(0.0F, 0.0F);
      this.speed = 0.0F;
   }

    std::string getDescription() {
      return "SpeedChecker: speed=" + this.speed + " x=" + this.position.x + " y=" + this.position.y + " vehicle=" + this.isInVehicle;
   }
}
} // namespace characters
} // namespace zombie
