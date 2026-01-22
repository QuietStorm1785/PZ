#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class SkinningBoneHierarchy {
public:
    bool m_boneHieararchyValid = false;
   private SkinningBone[] m_allBones = nullptr;
   private SkinningBone[] m_rootBones = nullptr;

    bool isValid() {
      return this.m_boneHieararchyValid;
   }

    void buildBoneHiearchy(SkinningData var1) {
      this.m_rootBones = new SkinningBone[0];
      this.m_allBones = new SkinningBone[var1.numBones()];
      PZArrayUtil.arrayPopulate(this.m_allBones, SkinningBone::new);

      for (Entry var3 : var1.BoneIndices.entrySet()) {
    int var4 = (int)var3.getValue();
    std::string var5 = (std::string)var3.getKey();
    SkinningBone var6 = this.m_allBones[var4];
         var6.Index = var4;
         var6.Name = var5;
         var6.Children = new SkinningBone[0];
      }

      for (int var7 = 0; var7 < var1.numBones(); var7++) {
    SkinningBone var8 = this.m_allBones[var7];
    int var9 = var1.getParentBoneIdx(var7);
         if (var9 > -1) {
            var8.Parent = this.m_allBones[var9];
            var8.Parent.Children = (SkinningBone[])PZArrayUtil.push_back(var8.Parent.Children, var8);
         } else {
            this.m_rootBones = (SkinningBone[])PZArrayUtil.push_back(this.m_rootBones, var8);
         }
      }

      this.m_boneHieararchyValid = true;
   }

    int numRootBones() {
      return this.m_rootBones.length;
   }

    SkinningBone getBoneAt(int var1) {
      return this.m_allBones[var1];
   }

    SkinningBone getRootBoneAt(int var1) {
      return this.m_rootBones[var1];
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
