#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/skinnedmodel/model/ModelInstance/FrameLightBlendStatus.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelInstance {
public:
    FrameLightBlendStatus Stage;
    int id;
    int x;
    int y;
    int z;
    float distSq;
    int radius;
    float r;
    float g;
    float b;
    int flags;
    const Vector3f currentColor = std::make_shared<Vector3f>();
    const Vector3f targetColor = std::make_shared<Vector3f>();
    bool active;
    bool foundThisFrame;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
