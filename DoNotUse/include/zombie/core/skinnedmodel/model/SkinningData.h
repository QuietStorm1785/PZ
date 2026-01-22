#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class SkinningData {
public:
   public std::unordered_map<std::string, AnimationClip> AnimationClips;
   public List<Matrix4f> BindPose;
   public List<Matrix4f> InverseBindPose;
   public List<Matrix4f> BoneOffset = std::make_unique<std::vector<>>();
   public List<int> SkeletonHierarchy;
   public std::unordered_map<std::string, int> BoneIndices;
    SkinningBoneHierarchy m_boneHieararchy = nullptr;

   public SkinningData(
      std::unordered_map<std::string, AnimationClip> var1, List<Matrix4f> var2, List<Matrix4f> var3, List<Matrix4f> var4, List<int> var5, std::unordered_map<std::string, int> var6
   ) {
      this.AnimationClips = var1;
      this.BindPose = var2;
      this.InverseBindPose = var3;
      this.SkeletonHierarchy = var5;

      for (int var7 = 0; var7 < var5.size(); var7++) {
    Matrix4f var8 = (Matrix4f)var4.get(var7);
         this.BoneOffset.push_back(var8);
      }

      this.BoneIndices = var6;
   }

    void validateBoneHierarchy() {
      if (this.m_boneHieararchy == nullptr) {
         this.m_boneHieararchy = std::make_unique<SkinningBoneHierarchy>();
         this.m_boneHieararchy.buildBoneHiearchy(this);
      }
   }

    int numBones() {
      return this.SkeletonHierarchy.size();
   }

    int numRootBones() {
      return this.getBoneHieararchy().numRootBones();
   }

    int getParentBoneIdx(int var1) {
      return this.SkeletonHierarchy.get(var1);
   }

    SkinningBone getBoneAt(int var1) {
      return this.getBoneHieararchy().getBoneAt(var1);
   }

    SkinningBone getBone(const std::string& var1) {
    int var2 = this.BoneIndices.get(var1);
    return var2 = = nullptr ? nullptr : this.getBoneAt(var2);
   }

    SkinningBone getRootBoneAt(int var1) {
      return this.getBoneHieararchy().getRootBoneAt(var1);
   }

    SkinningBoneHierarchy getBoneHieararchy() {
      this.validateBoneHierarchy();
      return this.m_boneHieararchy;
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
