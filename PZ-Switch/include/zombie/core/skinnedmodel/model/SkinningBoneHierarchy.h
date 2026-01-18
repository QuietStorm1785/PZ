#pragma once
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
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

class SkinningBoneHierarchy {
public:
 bool m_boneHieararchyValid = false;
private
 SkinningBone[] m_allBones = nullptr;
private
 SkinningBone[] m_rootBones = nullptr;

 bool isValid() { return this->m_boneHieararchyValid; }

 void buildBoneHiearchy(SkinningData data) {
 this->m_rootBones = new SkinningBone[0];
 this->m_allBones = new SkinningBone[data.numBones()];
 PZArrayUtil.arrayPopulate(this->m_allBones, SkinningBone::new);

 for (Entry entry : data.BoneIndices.entrySet()) {
 int int0 = (Integer)entry.getValue();
 std::string string = (String)entry.getKey();
 SkinningBone skinningBone0 = this->m_allBones[int0];
 skinningBone0.Index = int0;
 skinningBone0.Name = string;
 skinningBone0.Children = new SkinningBone[0];
 }

 for (int int1 = 0; int1 < data.numBones(); int1++) {
 SkinningBone skinningBone1 = this->m_allBones[int1];
 int int2 = data.getParentBoneIdx(int1);
 if (int2 > -1) {
 skinningBone1.Parent = this->m_allBones[int2];
 skinningBone1.Parent.Children =
 PZArrayUtil.add(skinningBone1.Parent.Children, skinningBone1);
 } else {
 this->m_rootBones = PZArrayUtil.add(this->m_rootBones, skinningBone1);
 }
 }

 this->m_boneHieararchyValid = true;
 }

 int numRootBones() { return this->m_rootBones.length; }

 SkinningBone getBoneAt(int boneIdx) { return this->m_allBones[boneIdx]; }

 SkinningBone getRootBoneAt(int idx) { return this->m_rootBones[idx]; }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
