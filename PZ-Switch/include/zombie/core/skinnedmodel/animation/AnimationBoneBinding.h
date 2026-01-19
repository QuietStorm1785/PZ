#pragma once
#include "zombie/core/skinnedmodel/model/SkinningBone.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimationBoneBinding {
public:
 const std::string boneName;
 SkinningBone m_bone = nullptr;
 SkinningData m_skinningData;

public
 AnimationBoneBinding(std::string_view _boneName) {
 this->boneName = _boneName;
 }

 SkinningData getSkinningData() { return this->m_skinningData; }

 void setSkinningData(SkinningData skinningData) {
 if (this->m_skinningData != skinningData) {
 this->m_skinningData = skinningData;
 this->m_bone = nullptr;
 }
 }

 SkinningBone getBone() {
 if (this->m_bone.empty()) {
 this->initBone();
 }

 return this->m_bone;
 }

 void initBone() {
 if (this->m_skinningData.empty()) {
 this->m_bone = nullptr;
 } else {
 this->m_bone = this->m_skinningData.getBone(this->boneName);
 }
 }

 std::string toString() {
 std::string string = System.lineSeparator();
 return this->getClass().getName() + string + "{" + string + "\tboneName:\"" +
 this->boneName + "\"" + string +
 "\tm_bone:" + StringUtils.indent(String.valueOf(this->m_bone) +
 string + "}";
 }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
