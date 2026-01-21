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

void AnimationTrack::get(int var1, Vector3f var2, Quaternion var3, Vector3f var4) {
    // TODO: Implement get
}

Keyframe AnimationTrack::getDeferredMovementFrameAt(int var1, float var2, Keyframe var3) {
    // TODO: Implement getDeferredMovementFrameAt
    return nullptr;
}

KeyframeSpan AnimationTrack::getKeyframeSpan(int var1, float var2, KeyframeSpan var3) {
    // TODO: Implement getKeyframeSpan
    return nullptr;
}

void AnimationTrack::removeListener(IAnimListener var1) {
    // TODO: Implement removeListener
}

void AnimationTrack::Update(float var1) {
    // TODO: Implement Update
}

void AnimationTrack::UpdateKeyframes(float var1) {
    // TODO: Implement UpdateKeyframes
}

void AnimationTrack::updateKeyframesInternal(float var1) {
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

void AnimationTrack::appendDeferredValues(DeferredMotionData var1, float var2, float var3) {
    // TODO: Implement appendDeferredValues
}

float AnimationTrack::getDeferredTwistRotation(Quaternion var1) {
    // TODO: Implement getDeferredTwistRotation
    return 0;
}

Vector2 AnimationTrack::getDeferredMovement(Vector3f var1, Vector2 var2) {
    // TODO: Implement getDeferredMovement
    return nullptr;
}

Vector3f AnimationTrack::getCurrentDeferredCounterPosition(Vector3f var1) {
    // TODO: Implement getCurrentDeferredCounterPosition
    return nullptr;
}

float AnimationTrack::getCurrentDeferredRotation() {
    // TODO: Implement getCurrentDeferredRotation
    return 0;
}

Vector3f AnimationTrack::getCurrentDeferredPosition(Vector3f var1) {
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

float AnimationTrack::getReversibleTimeValue(float var1) {
    // TODO: Implement getReversibleTimeValue
    return 0;
}

void AnimationTrack::TickCurrentTime(float var1) {
    // TODO: Implement TickCurrentTime
}

void AnimationTrack::tickCurrentTimeInternal(float var1) {
    // TODO: Implement tickCurrentTimeInternal
}

float AnimationTrack::getDuration() {
    // TODO: Implement getDuration
    return 0;
}

void AnimationTrack::invokeListeners(Consumer<IAnimListener> var1) {
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

Vector2 AnimationTrack::getDeferredMovementDiff(Vector2 var1) {
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

void AnimationTrack::addListener(IAnimListener var1) {
    // TODO: Implement addListener
}

void AnimationTrack::startClip(AnimationClip var1, bool var2) {
    // TODO: Implement startClip
}

AnimationTrack AnimationTrack::reset() {
    // TODO: Implement reset
    return nullptr;
}

void AnimationTrack::setBoneWeights(List<AnimBoneWeight> var1) {
    // TODO: Implement setBoneWeights
}

void AnimationTrack::initBoneWeights(SkinningData var1) {
    // TODO: Implement initBoneWeights
}

void AnimationTrack::initWeightBinding(SkinningData var1, AnimBoneWeight var2) {
    // TODO: Implement initWeightBinding
}

void AnimationTrack::assignBoneWeight(float var1, int var2) {
    // TODO: Implement assignBoneWeight
}

float AnimationTrack::getBoneWeight(int var1) {
    // TODO: Implement getBoneWeight
    return 0;
}

float AnimationTrack::getDeferredBoneWeight() {
    // TODO: Implement getDeferredBoneWeight
    return 0;
}

void AnimationTrack::setLayerIdx(int var1) {
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

void AnimationTrack::setDeferredBone(SkinningBone var1, BoneAxis var2) {
    // TODO: Implement setDeferredBone
}

void AnimationTrack::setUseDeferredRotation(bool var1) {
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

void AnimationTrack::setCurrentTimeValue(float var1) {
    // TODO: Implement setCurrentTimeValue
}

float AnimationTrack::getPreviousTimeValue() {
    // TODO: Implement getPreviousTimeValue
    return 0;
}

void AnimationTrack::setPreviousTimeValue(float var1) {
    // TODO: Implement setPreviousTimeValue
}

void AnimationTrack::rewind(float var1) {
    // TODO: Implement rewind
}

void AnimationTrack::scaledRewind(float var1) {
    // TODO: Implement scaledRewind
}

void AnimationTrack::scaledAdvance(float var1) {
    // TODO: Implement scaledAdvance
}

void AnimationTrack::advance(float var1) {
    // TODO: Implement advance
}

void AnimationTrack::advanceFraction(float var1) {
    // TODO: Implement advanceFraction
}

void AnimationTrack::moveCurrentTimeValueTo(float var1) {
    // TODO: Implement moveCurrentTimeValueTo
}

void AnimationTrack::moveCurrentTimeValueToFraction(float var1) {
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

AnimationTrack AnimationTrack::createClone(AnimationTrack var0, Supplier<AnimationTrack> var1) {
    // TODO: Implement createClone
    return nullptr;
}

} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
