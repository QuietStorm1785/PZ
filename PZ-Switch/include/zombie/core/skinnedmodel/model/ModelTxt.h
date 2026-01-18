#pragma once
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ModelTxt {
public:
 bool bStatic;
 bool bReverse;
 VertexBufferObject.VertexArray vertices;
 int[] elements;
 HashMap<String, Integer> boneIndices = std::make_unique<HashMap<>>();
 ArrayList<Integer> SkeletonHierarchy = std::make_unique<ArrayList<>>();
 ArrayList<Matrix4f> bindPose = std::make_unique<ArrayList<>>();
 ArrayList<Matrix4f> skinOffsetMatrices = std::make_unique<ArrayList<>>();
 ArrayList<Matrix4f> invBindPose = std::make_unique<ArrayList<>>();
 HashMap<String, AnimationClip> clips = std::make_unique<HashMap<>>();
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
