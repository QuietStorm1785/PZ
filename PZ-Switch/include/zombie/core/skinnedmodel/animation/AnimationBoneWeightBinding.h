#pragma once
#include "zombie/core/skinnedmodel/advancedanimation/AnimBoneWeight.h"
#include "zombie/core/skinnedmodel/model/SkinningBone.h"
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
namespace animation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimationBoneWeightBinding : public AnimationBoneBinding {
public:
 float m_weight = 1.0F;
 bool m_includeDescendants = true;

public
 AnimationBoneWeightBinding(AnimBoneWeight animBoneWeight) {
 this(animBoneWeight.boneName, animBoneWeight.weight,
 animBoneWeight.includeDescendants);
 }

public
 AnimationBoneWeightBinding(const std::string &string, float float0,
 bool boolean0) {
 super(string);
 this->m_weight = float0;
 this->m_includeDescendants = boolean0;
 }

 float getWeight() { return this->m_weight; }

 void setWeight(float float0) { this->m_weight = float0; }

 bool getIncludeDescendants() { return this->m_includeDescendants; }

 void setIncludeDescendants(bool boolean0) {
 this->m_includeDescendants = boolean0;
 }

 void forEachDescendant(Consumer<SkinningBone> consumer) {
 if (this->m_includeDescendants) {
 SkinningBone skinningBone = this->getBone();
 if (skinningBone != nullptr) {
 skinningBone.forEachDescendant(consumer);
 }
 }
 }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
