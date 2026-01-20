#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/BaseVehicle/ModelInfo.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class VehicleSubModelInstance : public ModelInstance {
public:
    ModelInfo modelInfo;
    int degrees = 0;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
