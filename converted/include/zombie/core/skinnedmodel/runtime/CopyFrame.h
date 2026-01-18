#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/animation/Keyframe.h"
#include "zombie/scripting/ScriptParser.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace runtime {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class CopyFrame {
public:
 int m_frame;
 int m_FPS = 30;
 std::string m_source;
 int m_sourceFrame;
 int m_sourceFPS = 30;

 void parse(ScriptParser.Block block) {
 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("source".equalsIgnoreCase(string0) {
 this->m_source = string1;
 } else if ("frame".equalsIgnoreCase(string0) {
 this->m_frame = PZMath.tryParseInt(string1, 1);
 } else if ("sourceFrame".equalsIgnoreCase(string0) {
 this->m_sourceFrame = PZMath.tryParseInt(string1, 1);
 }
 }
 }

 void exec(List<Keyframe> list) {
 AnimationClip animationClip = ModelManager.instance.getAnimationClip(this->m_source);

 for (int int0 = 0; int0 < 60; int0++) {
 Keyframe[] keyframes = animationClip.getBoneFramesAt(int0);
 if (keyframes.length != 0) {
 Keyframe keyframe0 = keyframes[0];
 Keyframe keyframe1 = new Keyframe();
 keyframe1.Bone = keyframe0.Bone;
 keyframe1.BoneName = keyframe0.BoneName;
 keyframe1.Time = (float)(this->m_frame - 1) / this->m_FPS;
 keyframe1.Position = KeyframeUtil.GetKeyFramePosition(keyframes, (float)(this->m_sourceFrame - 1) / this->m_sourceFPS, animationClip.Duration);
 keyframe1.Rotation = KeyframeUtil.GetKeyFrameRotation(keyframes, (float)(this->m_sourceFrame - 1) / this->m_sourceFPS, animationClip.Duration);
 keyframe1.Scale = keyframe0.Scale;
 list.add(keyframe1);
 }
 }
 }
}
} // namespace runtime
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
