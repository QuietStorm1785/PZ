#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace physics {

class CarController {
public:
    int minSpeed;
    int maxSpeed;
    float minRPM;

   CarController$GearInfo(int var1, int var2, float var3) {
      this.minSpeed = var1;
      this.maxSpeed = var2;
      this.minRPM = var3;
   }
}
} // namespace physics
} // namespace core
} // namespace zombie
