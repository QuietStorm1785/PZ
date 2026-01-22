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
    float steering;
    bool forward;
    bool backward;
    bool brake;
    bool shift;
    bool wasUsingParkingBrakes;
    long forceBrake = 0L;

    void reset() {
      this.steering = 0.0F;
      this.forward = false;
      this.backward = false;
      this.brake = false;
      this.shift = false;
      this.wasUsingParkingBrakes = false;
      this.forceBrake = 0L;
   }
}
} // namespace physics
} // namespace core
} // namespace zombie
