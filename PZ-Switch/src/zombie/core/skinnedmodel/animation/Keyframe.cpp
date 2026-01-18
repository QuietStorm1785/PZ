#include "zombie/core/skinnedmodel/animation/Keyframe.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {

public
Keyframe::Keyframe() {
 // TODO: Implement Keyframe
 return nullptr;
}

public
Keyframe::Keyframe(Vector3f pos, Quaternion rotation, Vector3f scale) {
 // TODO: Implement Keyframe
 return nullptr;
}

void Keyframe::set(Keyframe keyframe) {
 // TODO: Implement set
}

void Keyframe::get(Vector3f out_pos, Quaternion out_rot, Vector3f out_scale) {
 // TODO: Implement get
}

void Keyframe::setScale(Vector3f vector3f) {
 // TODO: Implement setScale
}

void Keyframe::setRotation(Quaternion quaternion) {
 // TODO: Implement setRotation
}

void Keyframe::setPosition(Vector3f vector3f) {
 // TODO: Implement setPosition
}

void Keyframe::clear() {
 // TODO: Implement clear
}

void Keyframe::setIdentity() {
 // TODO: Implement setIdentity
}

void Keyframe::setIdentity(Vector3f out_pos, Quaternion out_rot,
 Vector3f out_scale) {
 // TODO: Implement setIdentity
}

Keyframe Keyframe::lerp(Keyframe a, Keyframe b, float time,
 Keyframe out_result) {
 // TODO: Implement lerp
 return nullptr;
}

void Keyframe::setIfNotNull(Vector3f to, Vector3f val, float default_x,
 float default_y, float default_z) {
 // TODO: Implement setIfNotNull
}

void Keyframe::setIfNotNull(Vector3f to, float x, float y, float z) {
 // TODO: Implement setIfNotNull
}

void Keyframe::setIfNotNull(Quaternion to, Quaternion val) {
 // TODO: Implement setIfNotNull
}

void Keyframe::setIdentityIfNotNull(Quaternion to) {
 // TODO: Implement setIdentityIfNotNull
}

void Keyframe::lerp(Keyframe a, Keyframe b, float time, Vector3f out_pos,
 Quaternion out_rot, Vector3f out_scale) {
 // TODO: Implement lerp
}

} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
