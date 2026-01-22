#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexArray.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class ModelTxt {
public:
    bool bStatic;
    bool bReverse;
    VertexArray vertices;
   int[] elements;
   std::unordered_map<std::string, int> boneIndices = std::make_unique<std::unordered_map<>>();
   std::vector<int> SkeletonHierarchy = std::make_unique<std::vector<>>();
   std::vector<Matrix4f> bindPose = std::make_unique<std::vector<>>();
   std::vector<Matrix4f> skinOffsetMatrices = std::make_unique<std::vector<>>();
   std::vector<Matrix4f> invBindPose = std::make_unique<std::vector<>>();
   std::unordered_map<std::string, AnimationClip> clips = std::make_unique<std::unordered_map<>>();
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
