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

/**
 * Created by LEMMYATI on 03/01/14.
 */
class SkinningData {
public:
public
 HashMap<String, AnimationClip> AnimationClips;
public
 List<Matrix4f> BindPose;
public
 List<Matrix4f> InverseBindPose;
public
 List<Matrix4f> BoneOffset = std::make_unique<ArrayList<>>();
public
 List<Integer> SkeletonHierarchy;
public
 HashMap<String, Integer> BoneIndices;
 SkinningBoneHierarchy m_boneHieararchy = nullptr;

public
 SkinningData(HashMap<String, AnimationClip> animationClips,
 List<Matrix4f> bindPose, List<Matrix4f> inverseBindPose,
 List<Matrix4f> skinOffset, List<Integer> skeletonHierarchy,
 HashMap<String, Integer> boneIndices) {
 this->AnimationClips = animationClips;
 this->BindPose = bindPose;
 this->InverseBindPose = inverseBindPose;
 this->SkeletonHierarchy = skeletonHierarchy;

 for (int int0 = 0; int0 < skeletonHierarchy.size(); int0++) {
 Matrix4f matrix4f = (Matrix4f)skinOffset.get(int0);
 this->BoneOffset.add(matrix4f);
 }

 this->BoneIndices = boneIndices;
 }

 void validateBoneHierarchy() {
 if (this->m_boneHieararchy.empty()) {
 this->m_boneHieararchy = std::make_unique<SkinningBoneHierarchy>();
 this->m_boneHieararchy.buildBoneHiearchy(this);
 }
 }

 int numBones() { return this->SkeletonHierarchy.size(); }

 int numRootBones() { return this->getBoneHieararchy().numRootBones(); }

 int getParentBoneIdx(int boneIdx) {
 return this->SkeletonHierarchy.get(boneIdx);
 }

 SkinningBone getBoneAt(int boneIdx) {
 return this->getBoneHieararchy().getBoneAt(boneIdx);
 }

 SkinningBone getBone(const std::string &boneName) {
 int integer = this->BoneIndices.get(boneName);
 return integer = = nullptr ? nullptr : this->getBoneAt(integer);
 }

 SkinningBone getRootBoneAt(int idx) {
 return this->getBoneHieararchy().getRootBoneAt(idx);
 }

 SkinningBoneHierarchy getBoneHieararchy() {
 this->validateBoneHierarchy();
 return this->m_boneHieararchy;
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
