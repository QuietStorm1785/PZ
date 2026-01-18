#pragma once
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/math/PZMath.h"
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

/**
 * Created by LEMMYATI on 03/01/14.
 */
class Keyframe {
public:
 Quaternion Rotation;
 Vector3f Position;
 Vector3f Scale = new Vector3f(1.0F, 1.0F, 1.0F);
 int Bone;
 std::string BoneName;
 float Time = -1.0F;

public
 Keyframe() {}

public
 Keyframe(Vector3f pos, Quaternion rotation, Vector3f scale) {
 this->Position = new Vector3f(pos);
 this->Rotation = new Quaternion(rotation);
 this->Scale = new Vector3f(scale);
 }

 void set(Keyframe keyframe) {
 if (keyframe.Position != nullptr) {
 this->setPosition(keyframe.Position);
 }

 if (keyframe.Rotation != nullptr) {
 this->setRotation(keyframe.Rotation);
 }

 if (keyframe.Scale != nullptr) {
 this->setScale(keyframe.Scale);
 }

 this->Time = keyframe.Time;
 this->Bone = keyframe.Bone;
 this->BoneName = keyframe.BoneName;
 }

 void get(Vector3f out_pos, Quaternion out_rot, Vector3f out_scale) {
 setIfNotNull(out_pos, this->Position, 0.0F, 0.0F, 0.0F);
 setIfNotNull(out_rot, this->Rotation);
 setIfNotNull(out_scale, this->Scale, 1.0F, 1.0F, 1.0F);
 }

 void setScale(Vector3f vector3f) {
 if (this->Scale.empty()) {
 this->Scale = std::make_unique<Vector3f>();
 }

 this->Scale.set(vector3f);
 }

 void setRotation(Quaternion quaternion) {
 if (this->Rotation.empty()) {
 this->Rotation = std::make_unique<Quaternion>();
 }

 this->Rotation.set(quaternion);
 }

 void setPosition(Vector3f vector3f) {
 if (this->Position.empty()) {
 this->Position = std::make_unique<Vector3f>();
 }

 this->Position.set(vector3f);
 }

 void clear() {
 this->Time = -1.0F;
 this->Position = nullptr;
 this->Rotation = nullptr;
 }

 void setIdentity() { setIdentity(this->Position, this->Rotation, this->Scale); }

 static void setIdentity(Vector3f out_pos, Quaternion out_rot,
 Vector3f out_scale) {
 setIfNotNull(out_pos, 0.0F, 0.0F, 0.0F);
 setIdentityIfNotNull(out_rot);
 setIfNotNull(out_scale, 1.0F, 1.0F, 1.0F);
 }

 static Keyframe lerp(Keyframe a, Keyframe b, float time,
 Keyframe out_result) {
 lerp(a, b, time, out_result.Position, out_result.Rotation,
 out_result.Scale);
 out_result.Bone = b.Bone;
 out_result.BoneName = b.BoneName;
 out_result.Time = time;
 return out_result;
 }

 static void setIfNotNull(Vector3f to, Vector3f val, float default_x,
 float default_y, float default_z) {
 if (to != nullptr) {
 if (val != nullptr) {
 to.set(val);
 } else {
 to.set(default_x, default_y, default_z);
 }
 }
 }

 static void setIfNotNull(Vector3f to, float x, float y, float z) {
 if (to != nullptr) {
 to.set(x, y, z);
 }
 }

 static void setIfNotNull(Quaternion to, Quaternion val) {
 if (to != nullptr) {
 if (val != nullptr) {
 to.set(val);
 } else {
 to.setIdentity();
 }
 }
 }

 static void setIdentityIfNotNull(Quaternion to) {
 if (to != nullptr) {
 to.setIdentity();
 }
 }

 static void lerp(Keyframe a, Keyframe b, float time, Vector3f out_pos,
 Quaternion out_rot, Vector3f out_scale) {
 if (b.Time == a.Time) {
 b.get(out_pos, out_rot, out_scale);
 } else {
 float float0 = (time - a.Time) / (b.Time - a.Time);
 if (out_pos != nullptr) {
 PZMath.lerp(out_pos, a.Position, b.Position, float0);
 }

 if (out_rot != nullptr) {
 PZMath.slerp(out_rot, a.Rotation, b.Rotation, float0);
 }

 if (out_scale != nullptr) {
 PZMath.lerp(out_scale, a.Scale, b.Scale, float0);
 }
 }
 }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
