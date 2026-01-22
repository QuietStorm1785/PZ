#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Quaternionf.h"
#include "org/joml/Vector3f.h"
#include "zombie/core/physics/Transform.h"

namespace zombie {
namespace vehicles {


class VehicleManager {
public:
    const Transform transform = std::make_shared<Transform>();
    const Vector3f vector3f = std::make_shared<Vector3f>();
    const Quaternionf quatf = std::make_shared<Quaternionf>();
   const float[] wheelSteer = new float[4];
   const float[] wheelRotation = new float[4];
   const float[] wheelSkidInfo = new float[4];
   const float[] wheelSuspensionLength = new float[4];
}
} // namespace vehicles
} // namespace zombie
