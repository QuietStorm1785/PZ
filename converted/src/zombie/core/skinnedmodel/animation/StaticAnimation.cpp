#include "zombie/core/skinnedmodel/animation/StaticAnimation.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {

public
StaticAnimation::StaticAnimation(AnimationClip clip) {
  // TODO: Implement StaticAnimation
  return nullptr;
}

Keyframe StaticAnimation::getNextKeyFrame(int int2, int int1,
                                          Keyframe keyframe1) {
  // TODO: Implement getNextKeyFrame
  return nullptr;
}

Quaternion StaticAnimation::getRotation(Quaternion out, int bone) {
  // TODO: Implement getRotation
  return nullptr;
}

Vector3f StaticAnimation::getPosition(Vector3f out, int bone) {
  // TODO: Implement getPosition
  return nullptr;
}

void StaticAnimation::getPose() {
  // TODO: Implement getPose
}

void StaticAnimation::Create() {
  // TODO: Implement Create
}

Keyframe StaticAnimation::interpolate(List<Keyframe> frames, float time) {
  // TODO: Implement interpolate
  return nullptr;
}

void StaticAnimation::interpolate(List<Keyframe> frames) {
  // TODO: Implement interpolate
}

void StaticAnimation::doRootMotion(List<Keyframe> frames) {
  // TODO: Implement doRootMotion
}

} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
