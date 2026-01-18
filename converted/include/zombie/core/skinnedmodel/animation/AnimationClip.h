#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Quaternion.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Created by LEMMYATI on 03/01/14.
 */
class AnimationClip {
public:
 const std::string Name;
 StaticAnimation staticClip;
 private AnimationClip.KeyframeByBoneIndexElement[] m_KeyFramesByBoneIndex;
 float Duration;
 private List<Keyframe> m_rootMotionKeyframes = std::make_unique<ArrayList<>>();
 private Keyframe[] KeyframeArray;
 static const Quaternion orientation = new Quaternion(-0.07107F, 0.0F, 0.0F, 0.07107F);

 public AnimationClip(float duration, List<Keyframe> keyframes, const std::string& name, bool bKeepLastFrame) {
 this->Duration = duration;
 this->KeyframeArray = keyframes.toArray(new Keyframe[0]);
 this->Name = name;
 this->m_KeyFramesByBoneIndex = new AnimationClip.KeyframeByBoneIndexElement[60];
 std::vector arrayList = new ArrayList();
 int int0 = this->KeyframeArray.length - (bKeepLastFrame ? 0 : 1);

 for (int int1 = 0; int1 < 60; int1++) {
 arrayList.clear();

 for (int int2 = 0; int2 < int0; int2++) {
 Keyframe keyframe = this->KeyframeArray[int2];
 if (keyframe.Bone == int1) {
 arrayList.add(keyframe);
 }
 }

 this->m_KeyFramesByBoneIndex[int1] = new AnimationClip.KeyframeByBoneIndexElement(arrayList);
 }
 }

 public Keyframe[] getBoneFramesAt(int idx) {
 return this->m_KeyFramesByBoneIndex[idx].m_keyframes;
 }

 int getRootMotionFrameCount() {
 return this->m_rootMotionKeyframes.size();
 }

 Keyframe getRootMotionFrameAt(int idx) {
 return this->m_rootMotionKeyframes.get(idx);
 }

 public Keyframe[] getKeyframes() {
 return this->KeyframeArray;
 }

 float getTranslationLength(BoneAxis deferredBoneAxis) {
 float float0 = this->KeyframeArray[this->KeyframeArray.length - 1].Position.x - this->KeyframeArray[0].Position.x;
 float float1;
 if (deferredBoneAxis == BoneAxis.Y) {
 float1 = -this->KeyframeArray[this->KeyframeArray.length - 1].Position.z + this->KeyframeArray[0].Position.z;
 } else {
 float1 = this->KeyframeArray[this->KeyframeArray.length - 1].Position.y - this->KeyframeArray[0].Position.y;
 }

 return (float)Math.sqrt(float0 * float0 + float1 * float1);
 }

 private static class KeyframeByBoneIndexElement {
 Keyframe[] m_keyframes;

 KeyframeByBoneIndexElement(List<Keyframe> list) {
 this->m_keyframes = list.toArray(new Keyframe[0]);
 }
 }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
