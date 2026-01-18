#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/HelperFunctions.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Created by LEMMY on 3/15/2016.
 * @deprecated
 */
class StaticAnimation {
public:
 int framesPerSecond;
 std::string name;
 public Matrix4f[][] Matrices;
 private Matrix4f[] RootMotion;
 AnimationClip Clip;
 int currentKeyframe = 0;
 float currentTimeValue = 0.0F;
 private Keyframe[] Pose;
 private Keyframe[] PrevPose;
 float lastTime = 0.0F;

 public StaticAnimation(AnimationClip clip) {
 this->Clip = clip;
 this->framesPerSecond = PerformanceSettings.BaseStaticAnimFramerate;
 this->Matrices = new Matrix4f[(int)(this->framesPerSecond * this->Clip.Duration)][60];
 this->RootMotion = new Matrix4f[(int)(this->framesPerSecond * this->Clip.Duration)];
 this->Pose = new Keyframe[60];
 this->PrevPose = new Keyframe[60];
 this->Create();
 Arrays.fill(this->Pose, nullptr);
 this->Pose = nullptr;
 Arrays.fill(this->PrevPose, nullptr);
 this->PrevPose = nullptr;
 }

 Keyframe getNextKeyFrame(int int2, int int1, Keyframe keyframe1) {
 Keyframe[] keyframes = this->Clip.getKeyframes();

 for (int int0 = int1; int0 < keyframes.length; int0++) {
 Keyframe keyframe0 = keyframes[int0];
 if (keyframe0.Bone == int2 && keyframe0.Time > this->currentTimeValue && keyframe1 != keyframe0) {
 return keyframe0;
 }
 }

 return nullptr;
 }

 Quaternion getRotation(Quaternion out, int bone) {
 if (this->PrevPose[bone] != nullptr && PerformanceSettings.InterpolateAnims) {
 float float0 = (this->currentTimeValue - this->PrevPose[bone].Time) / (this->Pose[bone].Time - this->PrevPose[bone].Time);
 if (this->Pose[bone].Time - this->PrevPose[bone].Time == 0.0F) {
 float0 = 0.0F;
 }

 return PZMath.slerp(out, this->PrevPose[bone].Rotation, this->Pose[bone].Rotation, float0);
 } else {
 out.set(this->Pose[bone].Rotation);
 return out;
 }
 }

 Vector3f getPosition(Vector3f out, int bone) {
 if (this->PrevPose[bone] != nullptr && PerformanceSettings.InterpolateAnims) {
 float float0 = (this->currentTimeValue - this->PrevPose[bone].Time) / (this->Pose[bone].Time - this->PrevPose[bone].Time);
 if (this->Pose[bone].Time - this->PrevPose[bone].Time == 0.0F) {
 float0 = 0.0F;
 }

 PZMath.lerp(out, this->PrevPose[bone].Position, this->Pose[bone].Position, float0);
 return out;
 } else {
 out.set(this->Pose[bone].Position);
 return out;
 }
 }

 void getPose() {
 Keyframe[] keyframes = this->Clip.getKeyframes();

 for (this->currentKeyframe = 0; this->currentKeyframe < keyframes.length; this->currentKeyframe++) {
 Keyframe keyframe0 = keyframes[this->currentKeyframe];
 if (this->currentKeyframe == keyframes.length - 1 || !(keyframe0.Time <= this->currentTimeValue) {
 if (PerformanceSettings.InterpolateAnims) {
 for (int int0 = 0; int0 < 60; int0++) {
 if (this->Pose[int0] == nullptr || this->currentTimeValue >= this->Pose[int0].Time) {
 Keyframe keyframe1 = this->getNextKeyFrame(int0, this->currentKeyframe, this->Pose[int0]);
 if (keyframe1 != nullptr) {
 this->PrevPose[keyframe1.Bone] = this->Pose[keyframe1.Bone];
 this->Pose[keyframe1.Bone] = keyframe1;
 } else {
 this->PrevPose[int0] = nullptr;
 }
 }
 }
 }
 break;
 }

 if (keyframe0.Bone >= 0) {
 this->Pose[keyframe0.Bone] = keyframe0;
 }

 this->lastTime = keyframe0.Time;
 }
 }

 void Create() {
 float float0 = this->Matrices.length;
 double double0 = (double)this->Clip.Duration / float0;
 double double1 = 0.0;
 int int0 = 0;

 for (Matrix4f matrix4f0 = std::make_unique<Matrix4f>(); int0 < float0; int0++) {
 this->currentTimeValue = (float)double1;
 this->getPose();

 for (int int1 = 0; int1 < 60; int1++) {
 if (this->Pose[int1] == nullptr) {
 this->Matrices[int0][int1] = matrix4f0;
 } else {
 Quaternion quaternion = new Quaternion();
 this->getRotation(quaternion, int1);
 Vector3f vector3f = new Vector3f();
 this->getPosition(vector3f, int1);
 Matrix4f matrix4f1 = HelperFunctions.CreateFromQuaternionPositionScale(vector3f, quaternion, new Vector3f(1.0F, 1.0F, 1.0F), new Matrix4f());
 this->Matrices[int0][int1] = matrix4f1;
 }
 }

 double1 += double0;
 }
 }

 Keyframe interpolate(List<Keyframe> frames, float time) {
 int int0 = 0;
 Keyframe keyframe0 = nullptr;
 void* object = nullptr;

 while (int0 < frames.size()) {
 Keyframe keyframe1 = (Keyframe)frames.get(int0);
 if (keyframe1.Time > time && keyframe0.Time <= time) {
 Quaternion quaternion = new Quaternion();
 Vector3f vector3f = new Vector3f();
 float float0 = (time - keyframe0.Time) / (keyframe1.Time - keyframe0.Time);
 PZMath.slerp(quaternion, keyframe0.Rotation, keyframe1.Rotation, float0);
 PZMath.lerp(vector3f, keyframe0.Position, keyframe1.Position, float0);
 Keyframe keyframe2 = new Keyframe();
 keyframe2.Position = vector3f;
 keyframe2.Rotation = quaternion;
 keyframe2.Scale = new Vector3f(1.0F, 1.0F, 1.0F);
 keyframe2.Time = keyframe0.Time + (keyframe1.Time - keyframe0.Time) * float0;
 return keyframe2;
 }

 int0++;
 keyframe0 = keyframe1;
 }

 return (Keyframe)frames.get(frames.size() - 1);
 }

 void interpolate(List<Keyframe> frames) {
 if (!frames.empty()) {
 if (!((Keyframe)frames.get(0).Position == ((Keyframe)frames.get(frames.size() - 1).Position) {
 float float0 = this->Matrices.length + 1;
 double double0 = (double)this->Clip.Duration / float0;
 double double1 = 0.0;
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < float0 - 1.0F; double1 += double0) {
 Keyframe keyframe = this->interpolate(frames, (float)double1);
 arrayList.add(keyframe);
 int0++;
 }

 frames.clear();
 frames.addAll(arrayList);
 }
 }
 }

 void doRootMotion(List<Keyframe> frames) {
 float float0 = this->Matrices.length;
 if (frames.size() > 3) {
 for (int int0 = 0; int0 < float0 && int0 < frames.size(); int0++) {
 Keyframe keyframe = (Keyframe)frames.get(int0);
 Quaternion quaternion = keyframe.Rotation;
 Vector3f vector3f = keyframe.Position;
 Matrix4f matrix4f = HelperFunctions.CreateFromQuaternionPositionScale(vector3f, quaternion, keyframe.Scale, new Matrix4f());
 this->RootMotion[int0] = matrix4f;
 }
 }
 }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
