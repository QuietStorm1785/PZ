#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {

AnimationTrack AnimationTrack::alloc() {
 // TODO: Implement alloc
 return nullptr;
}

protected AnimationTrack::AnimationTrack() {
 // TODO: Implement AnimationTrack
 return nullptr;
}

AnimationTrack AnimationTrack::resetInternal() {
 // TODO: Implement resetInternal
 return nullptr;
}

void AnimationTrack::get(int bone, Vector3f out_pos, Quaternion out_rot, Vector3f out_scale) {
 // TODO: Implement get
}

Keyframe AnimationTrack::getDeferredMovementFrameAt(int int0, float float0, Keyframe keyframe) {
 // TODO: Implement getDeferredMovementFrameAt
 return nullptr;
}

void AnimationTrack::removeListener(IAnimListener listener) {
 // TODO: Implement removeListener
}

void AnimationTrack::Update(float time) {
 // TODO: Implement Update
}

void AnimationTrack::UpdateKeyframes(float dt) {
 // TODO: Implement UpdateKeyframes
}

void AnimationTrack::updateKeyframesInternal(float float0) {
 // TODO: Implement updateKeyframesInternal
}

void AnimationTrack::updatePose() {
 // TODO: Implement updatePose
}

void AnimationTrack::updatePoseInternal() {
 // TODO: Implement updatePoseInternal
}

void AnimationTrack::updateDeferredValues() {
 // TODO: Implement updateDeferredValues
}

void AnimationTrack::updateDeferredValuesInternal() {
 // TODO: Implement updateDeferredValuesInternal
}

void AnimationTrack::appendDeferredValues(AnimationTrack.DeferredMotionData deferredMotionData, float float0, float float1) {
 // TODO: Implement appendDeferredValues
}

float AnimationTrack::getDeferredTwistRotation(Quaternion boneRotation) {
 // TODO: Implement getDeferredTwistRotation
 return 0;
}

Vector2 AnimationTrack::getDeferredMovement(Vector3f bonePos, Vector2 out_deferredPos) {
 // TODO: Implement getDeferredMovement
 return nullptr;
}

Vector3f AnimationTrack::getCurrentDeferredCounterPosition(Vector3f out_result) {
 // TODO: Implement getCurrentDeferredCounterPosition
 return nullptr;
}

float AnimationTrack::getCurrentDeferredRotation() {
 // TODO: Implement getCurrentDeferredRotation
 return 0;
}

Vector3f AnimationTrack::getCurrentDeferredPosition(Vector3f out_result) {
 // TODO: Implement getCurrentDeferredPosition
 return nullptr;
}

int AnimationTrack::getDeferredMovementBoneIdx() {
 // TODO: Implement getDeferredMovementBoneIdx
 return 0;
}

float AnimationTrack::getCurrentTime() {
 // TODO: Implement getCurrentTime
 return 0;
}

float AnimationTrack::getPreviousTime() {
 // TODO: Implement getPreviousTime
 return 0;
}

float AnimationTrack::getReversibleTimeValue(float float0) {
 // TODO: Implement getReversibleTimeValue
 return 0;
}

void AnimationTrack::TickCurrentTime(float float0) {
 // TODO: Implement TickCurrentTime
}

void AnimationTrack::tickCurrentTimeInternal(float float0) {
 // TODO: Implement tickCurrentTimeInternal
}

float AnimationTrack::getDuration() {
 // TODO: Implement getDuration
 return 0;
}

void AnimationTrack::invokeListeners(Consumer<IAnimListener> consumer) {
 // TODO: Implement invokeListeners
}

void AnimationTrack::invokeOnAnimStartedEvent() {
 // TODO: Implement invokeOnAnimStartedEvent
}

void AnimationTrack::invokeOnLoopedAnimEvent() {
 // TODO: Implement invokeOnLoopedAnimEvent
}

void AnimationTrack::invokeOnNonLoopedAnimFadeOutEvent() {
 // TODO: Implement invokeOnNonLoopedAnimFadeOutEvent
}

void AnimationTrack::invokeOnNonLoopedAnimFinishedEvent() {
 // TODO: Implement invokeOnNonLoopedAnimFinishedEvent
}

void AnimationTrack::onReleased() {
 // TODO: Implement onReleased
}

Vector2 AnimationTrack::getDeferredMovementDiff(Vector2 out_result) {
 // TODO: Implement getDeferredMovementDiff
 return nullptr;
}

float AnimationTrack::getDeferredRotationDiff() {
 // TODO: Implement getDeferredRotationDiff
 return 0;
}

float AnimationTrack::getClampedBlendDelta() {
 // TODO: Implement getClampedBlendDelta
 return 0;
}

void AnimationTrack::addListener(IAnimListener listener) {
 // TODO: Implement addListener
}

void AnimationTrack::startClip(AnimationClip clip, bool loop) {
 // TODO: Implement startClip
}

AnimationTrack AnimationTrack::reset() {
 // TODO: Implement reset
 return nullptr;
}

void AnimationTrack::setBoneWeights(List<AnimBoneWeight> boneWeights) {
 // TODO: Implement setBoneWeights
}

void AnimationTrack::initBoneWeights(SkinningData skinningData) {
 // TODO: Implement initBoneWeights
}

void AnimationTrack::initWeightBinding(SkinningData skinningData, AnimBoneWeight animBoneWeight) {
 // TODO: Implement initWeightBinding
}

void AnimationTrack::assignBoneWeight(float float1, int int0) {
 // TODO: Implement assignBoneWeight
}

float AnimationTrack::getBoneWeight(int boneIdx) {
 // TODO: Implement getBoneWeight
 return 0;
}

float AnimationTrack::getDeferredBoneWeight() {
 // TODO: Implement getDeferredBoneWeight
 return 0;
}

void AnimationTrack::setLayerIdx(int layerIdx) {
 // TODO: Implement setLayerIdx
}

int AnimationTrack::getLayerIdx() {
 // TODO: Implement getLayerIdx
 return 0;
}

bool AnimationTrack::hasBoneMask() {
 // TODO: Implement hasBoneMask
 return false;
}

bool AnimationTrack::isLooping() {
 // TODO: Implement isLooping
 return false;
}

void AnimationTrack::setDeferredBone(SkinningBone bone, BoneAxis axis) {
 // TODO: Implement setDeferredBone
}

void AnimationTrack::setUseDeferredRotation(bool val) {
 // TODO: Implement setUseDeferredRotation
}

bool AnimationTrack::getUseDeferredRotation() {
 // TODO: Implement getUseDeferredRotation
 return false;
}

bool AnimationTrack::isFinished() {
 // TODO: Implement isFinished
 return false;
}

float AnimationTrack::getCurrentTimeValue() {
 // TODO: Implement getCurrentTimeValue
 return 0;
}

void AnimationTrack::setCurrentTimeValue(float _currentTimeValue) {
 // TODO: Implement setCurrentTimeValue
}

float AnimationTrack::getPreviousTimeValue() {
 // TODO: Implement getPreviousTimeValue
 return 0;
}

void AnimationTrack::setPreviousTimeValue(float _previousTimeValue) {
 // TODO: Implement setPreviousTimeValue
}

void AnimationTrack::rewind(float rewindAmount) {
 // TODO: Implement rewind
}

void AnimationTrack::scaledRewind(float rewindAmount) {
 // TODO: Implement scaledRewind
}

void AnimationTrack::scaledAdvance(float advanceAmount) {
 // TODO: Implement scaledAdvance
}

void AnimationTrack::advance(float advanceAmount) {
 // TODO: Implement advance
}

void AnimationTrack::advanceFraction(float advanceFraction) {
 // TODO: Implement advanceFraction
}

void AnimationTrack::moveCurrentTimeValueTo(float target) {
 // TODO: Implement moveCurrentTimeValueTo
}

void AnimationTrack::moveCurrentTimeValueToFraction(float fraction) {
 // TODO: Implement moveCurrentTimeValueToFraction
}

float AnimationTrack::getCurrentTimeFraction() {
 // TODO: Implement getCurrentTimeFraction
 return 0;
}

bool AnimationTrack::hasClip() {
 // TODO: Implement hasClip
 return false;
}

AnimationClip AnimationTrack::getClip() {
 // TODO: Implement getClip
 return nullptr;
}

int AnimationTrack::getPriority() {
 // TODO: Implement getPriority
 return 0;
}

AnimationTrack AnimationTrack::createClone(AnimationTrack source, Supplier<AnimationTrack> allocator) {
 // TODO: Implement createClone
 return nullptr;
}

void AnimationTrack::reset() {
 // TODO: Implement reset
}

void AnimationTrack::clear() {
 // TODO: Implement clear
}

Keyframe AnimationTrack::lerp(float float0, Keyframe keyframe) {
 // TODO: Implement lerp
 return nullptr;
}

void AnimationTrack::lerp(float float0, Vector3f vector3f0, Quaternion quaternion, Vector3f vector3f1) {
 // TODO: Implement lerp
}

bool AnimationTrack::isSpan() {
 // TODO: Implement isSpan
 return false;
}

bool AnimationTrack::isPost() {
 // TODO: Implement isPost
 return false;
}

bool AnimationTrack::isEmpty() {
 // TODO: Implement isEmpty
 return false;
}

bool AnimationTrack::containsTime(float float0) {
 // TODO: Implement containsTime
 return false;
}

bool AnimationTrack::isBone(int arg0) {
 // TODO: Implement isBone
 return false;
}

} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
