#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class ModelTransformSampler {
public:
    static const Vector3f pos = std::make_shared<Vector3f>();
    static const Quaternion rot = std::make_shared<Quaternion>();
    static const Vector3f scale = std::make_shared<Vector3f>();
    static const Keyframe key = std::make_shared<Keyframe>(std::make_shared<Vector3f>(0.0F, 0.0F, 0.0F), std::make_shared<Quaternion>(0.0F, 0.0F, 0.0F, 1.0F), std::make_shared<Vector3f>(1.0F, 1.0F, 1.0F));
    static const Vector3f rotAxis = std::make_shared<Vector3f>();
    static const Matrix4f rotMat = std::make_shared<Matrix4f>();
    static const Vector3f rotEulers = std::make_shared<Vector3f>();
    static const Vector3f deferredPos = std::make_shared<Vector3f>();
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
