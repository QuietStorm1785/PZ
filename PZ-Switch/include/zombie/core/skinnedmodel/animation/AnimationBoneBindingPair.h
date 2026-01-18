#pragma once
#include "zombie/core/skinnedmodel/model/SkinningBone.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimationBoneBindingPair {
public:
 const AnimationBoneBinding boneBindingA;
 const AnimationBoneBinding boneBindingB;

public
 AnimationBoneBindingPair(const std::string &string0,
 const std::string &string1) {
 this->boneBindingA = new AnimationBoneBinding(string0);
 this->boneBindingB = new AnimationBoneBinding(string1);
 }

 void setSkinningData(SkinningData skinningData) {
 this->boneBindingA.setSkinningData(skinningData);
 this->boneBindingB.setSkinningData(skinningData);
 }

 SkinningBone getBoneA() { return this->boneBindingA.getBone(); }

 SkinningBone getBoneB() { return this->boneBindingB.getBone(); }

 bool isValid() {
 return this->getBoneA() != nullptr && this->getBoneB() != nullptr;
 }

 bool matches(const std::string &string1, const std::string &string0) {
 return StringUtils.equalsIgnoreCase(this->boneBindingA.boneName, string1) &&
 StringUtils.equalsIgnoreCase(this->boneBindingB.boneName, string0);
 }

 int getBoneIdxA() { return getBoneIdx(); }

 int getBoneIdxB() { return getBoneIdx(); }

 static int getBoneIdx(SkinningBone skinningBone) {
 return skinningBone != nullptr ? skinningBone.Index : -1;
 }

 std::string toString() {
 std::string string = System.lineSeparator();
 return this->getClass().getName() + string + "{" + string +
 "\tboneBindingA:" +
 StringUtils.indent(String.valueOf(this->boneBindingA) + string +
 "\tboneBindingB:" +
 StringUtils.indent(String.valueOf(this->boneBindingB) + string + "}";
 }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
