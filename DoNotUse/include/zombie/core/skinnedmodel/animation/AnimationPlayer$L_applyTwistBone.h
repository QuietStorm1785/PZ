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


class AnimationPlayer {
public:
    static const Matrix4f twistParentBoneTrans = std::make_shared<Matrix4f>();
    static const Matrix4f twistParentBoneTransInv = std::make_shared<Matrix4f>();
    static const Matrix4f twistBoneTrans = std::make_shared<Matrix4f>();
    static const Quaternion twistBoneRot = std::make_shared<Quaternion>();
    static const Quaternion twistBoneTargetRot = std::make_shared<Quaternion>();
    static const Matrix4f twistRotDiffTrans = std::make_shared<Matrix4f>();
    static const Vector3f twistRotDiffTransAxis = std::make_shared<Vector3f>(0.0F, 1.0F, 0.0F);
    static const Matrix4f twistBoneTargetTrans = std::make_shared<Matrix4f>();
    static const Quaternion twistBoneNewRot = std::make_shared<Quaternion>();
    static const Vector3f twistBonePos = std::make_shared<Vector3f>();
    static const Vector3f twistBoneScale = std::make_shared<Vector3f>();
    static const Matrix4f twistBoneNewTrans = std::make_shared<Matrix4f>();

   private AnimationPlayer$L_applyTwistBone() {
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
