#include <string>
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {

private AnimationPlayer::AnimationPlayer() {
    // TODO: Implement AnimationPlayer
    return nullptr;
}

AnimationPlayer AnimationPlayer::alloc(Model var0) {
    // TODO: Implement alloc
    return nullptr;
}

float AnimationPlayer::lerpBlendWeight(float var0, float var1, float var2) {
    // TODO: Implement lerpBlendWeight
    return 0;
}

void AnimationPlayer::setModel(Model var1) {
    // TODO: Implement setModel
}

Model AnimationPlayer::getModel() {
    // TODO: Implement getModel
    return nullptr;
}

void AnimationPlayer::initSkinningData() {
    // TODO: Implement initSkinningData
}

bool AnimationPlayer::isReady() {
    // TODO: Implement isReady
    return false;
}

bool AnimationPlayer::hasSkinningData() {
    // TODO: Implement hasSkinningData
    return false;
}

void AnimationPlayer::addBoneReparent(const std::string& var1, const std::string& var2) {
    // TODO: Implement addBoneReparent
}

void AnimationPlayer::setTwistBones(std::string... var1) {
    // TODO: Implement setTwistBones
}

void AnimationPlayer::setCounterRotationBone(const std::string& var1) {
    // TODO: Implement setCounterRotationBone
}

AnimationBoneBinding AnimationPlayer::getCounterRotationBone() {
    // TODO: Implement getCounterRotationBone
    return nullptr;
}

void AnimationPlayer::reset() {
    // TODO: Implement reset
}

void AnimationPlayer::onReleased() {
    // TODO: Implement onReleased
}

SkinningData AnimationPlayer::getSkinningData() {
    // TODO: Implement getSkinningData
    return nullptr;
}

int AnimationPlayer::getSkinningBoneIndex(const std::string& var1, int var2) {
    // TODO: Implement getSkinningBoneIndex
    return 0;
}

void AnimationPlayer::resetSkinTransformsInternal() {
    // TODO: Implement resetSkinTransformsInternal
}

Matrix4f AnimationPlayer::GetPropBoneMatrix(int var1) {
    // TODO: Implement GetPropBoneMatrix
    return nullptr;
}

AnimationTrack AnimationPlayer::startClip(AnimationClip var1, bool var2) {
    // TODO: Implement startClip
    return nullptr;
}

void AnimationPlayer::releaseTracks(List<AnimationTrack> var0) {
    // TODO: Implement releaseTracks
}

AnimationTrack AnimationPlayer::play(const std::string& var1, bool var2) {
    // TODO: Implement play
    return nullptr;
}

void AnimationPlayer::Update() {
    // TODO: Implement Update
}

void AnimationPlayer::Update(float var1) {
    // TODO: Implement Update
}

void AnimationPlayer::updateInternal(float var1) {
    // TODO: Implement updateInternal
}

SharedSkeleAnimationTrack AnimationPlayer::determineCurrentSharedSkeleTrack() {
    // TODO: Implement determineCurrentSharedSkeleTrack
    return nullptr;
}

void AnimationPlayer::updateAnimation_NonVisualOnly() {
    // TODO: Implement updateAnimation_NonVisualOnly
}

void AnimationPlayer::setSharedAnimRepo(SharedSkeleAnimationRepository var1) {
    // TODO: Implement setSharedAnimRepo
}

void AnimationPlayer::updateAnimation_SharedSkeleTrack(SharedSkeleAnimationTrack var1, float var2) {
    // TODO: Implement updateAnimation_SharedSkeleTrack
}

void AnimationPlayer::updateAnimation_StandardAnimation() {
    // TODO: Implement updateAnimation_StandardAnimation
}

void AnimationPlayer::copyBoneTransformsFromParentPlayer() {
    // TODO: Implement copyBoneTransformsFromParentPlayer
}

float AnimationPlayer::calculateAnimPlayerAngle(Vector2 var0) {
    // TODO: Implement calculateAnimPlayerAngle
    return 0;
}

void AnimationPlayer::SetDir(Vector2 var1) {
    // TODO: Implement SetDir
}

void AnimationPlayer::SetForceDir(Vector2 var1) {
    // TODO: Implement SetForceDir
}

void AnimationPlayer::UpdateDir(IsoGameCharacter var1) {
    // TODO: Implement UpdateDir
}

void AnimationPlayer::DoAngles() {
    // TODO: Implement DoAngles
}

void AnimationPlayer::doAnglesInternal() {
    // TODO: Implement doAnglesInternal
}

void AnimationPlayer::interpolateBodyAngle(float var1) {
    // TODO: Implement interpolateBodyAngle
}

void AnimationPlayer::interpolateBodyTwist(float var1) {
    // TODO: Implement interpolateBodyTwist
}

void AnimationPlayer::interpolateShoulderTwist(float var1) {
    // TODO: Implement interpolateShoulderTwist
}

void AnimationPlayer::updateTwistBone() {
    // TODO: Implement updateTwistBone
}

void AnimationPlayer::updateTwistBoneInternal() {
    // TODO: Implement updateTwistBoneInternal
}

void AnimationPlayer::applyTwistBone(SkinningBone var1, float var2) {
    // TODO: Implement applyTwistBone
}

void AnimationPlayer::resetBoneModelTransforms() {
    // TODO: Implement resetBoneModelTransforms
}

bool AnimationPlayer::isBoneTransformsNeedFirstFrame() {
    // TODO: Implement isBoneTransformsNeedFirstFrame
    return false;
}

void AnimationPlayer::updateMultiTrackBoneTransforms() {
    // TODO: Implement updateMultiTrackBoneTransforms
}

void AnimationPlayer::updateMultiTrackBoneTransformsInternal() {
    // TODO: Implement updateMultiTrackBoneTransformsInternal
}

void AnimationPlayer::updateLayerBlendWeightings() {
    // TODO: Implement updateLayerBlendWeightings
}

void AnimationPlayer::calculateDeferredMovement() {
    // TODO: Implement calculateDeferredMovement
}

void AnimationPlayer::calculateDeferredMovementInternal() {
    // TODO: Implement calculateDeferredMovementInternal
}

void AnimationPlayer::applyRotationToDeferredMovement(Vector2 var1) {
    // TODO: Implement applyRotationToDeferredMovement
}

void AnimationPlayer::applyBoneReParenting() {
    // TODO: Implement applyBoneReParenting
}

void AnimationPlayer::applyBoneReParentingInternal() {
    // TODO: Implement applyBoneReParentingInternal
}

void AnimationPlayer::updateBoneAnimationTransform(int var1, AnimationBoneBindingPair var2) {
    // TODO: Implement updateBoneAnimationTransform
}

void AnimationPlayer::updateBoneAnimationTransform_Internal(int var1, AnimationBoneBindingPair var2) {
    // TODO: Implement updateBoneAnimationTransform_Internal
}

void AnimationPlayer::getTrackTransform(int var1, AnimationTrack var2, AnimationBoneBindingPair var3, Vector3f var4, Quaternion var5, Vector3f var6) {
    // TODO: Implement getTrackTransform
}

bool AnimationPlayer::isBoneReparented(int var1) {
    // TODO: Implement isBoneReparented
    return false;
}

void AnimationPlayer::updateMultiTrackBoneTransforms_DeferredMovementOnly() {
    // TODO: Implement updateMultiTrackBoneTransforms_DeferredMovementOnly
}

bool AnimationPlayer::isRecording() {
    // TODO: Implement isRecording
    return false;
}

void AnimationPlayer::setRecorder(AnimationPlayerRecorder var1) {
    // TODO: Implement setRecorder
}

AnimationPlayerRecorder AnimationPlayer::getRecorder() {
    // TODO: Implement getRecorder
    return nullptr;
}

void AnimationPlayer::dismember(int var1) {
    // TODO: Implement dismember
}

void AnimationPlayer::updateModelTransforms() {
    // TODO: Implement updateModelTransforms
}

void AnimationPlayer::updateModelTransformsInternal() {
    // TODO: Implement updateModelTransformsInternal
}

Matrix4f AnimationPlayer::getBoneModelTransform(int var1, Matrix4f var2) {
    // TODO: Implement getBoneModelTransform
    return nullptr;
}

Matrix4f AnimationPlayer::getBoneTransform(int var1, Matrix4f var2) {
    // TODO: Implement getBoneTransform
    return nullptr;
}

Matrix4f AnimationPlayer::getUnweightedModelTransform(AnimationTrack var1, int var2, Matrix4f var3) {
    // TODO: Implement getUnweightedModelTransform
    return nullptr;
}

Matrix4f AnimationPlayer::getUnweightedBoneTransform(AnimationTrack var0, int var1, Matrix4f var2) {
    // TODO: Implement getUnweightedBoneTransform
    return nullptr;
}

void AnimationPlayer::UpdateSkinTransforms() {
    // TODO: Implement UpdateSkinTransforms
}

void AnimationPlayer::getDeferredMovement(Vector2 var1) {
    // TODO: Implement getDeferredMovement
}

float AnimationPlayer::getDeferredAngleDelta() {
    // TODO: Implement getDeferredAngleDelta
    return 0;
}

float AnimationPlayer::getDeferredRotationWeight() {
    // TODO: Implement getDeferredRotationWeight
    return 0;
}

AnimationMultiTrack AnimationPlayer::getMultiTrack() {
    // TODO: Implement getMultiTrack
    return nullptr;
}

void AnimationPlayer::setRecording(bool var1) {
    // TODO: Implement setRecording
}

void AnimationPlayer::discardRecording() {
    // TODO: Implement discardRecording
}

float AnimationPlayer::getRenderedAngle() {
    // TODO: Implement getRenderedAngle
    return 0;
}

float AnimationPlayer::getAngle() {
    // TODO: Implement getAngle
    return 0;
}

void AnimationPlayer::setAngle(float var1) {
    // TODO: Implement setAngle
}

void AnimationPlayer::setAngleToTarget() {
    // TODO: Implement setAngleToTarget
}

void AnimationPlayer::setTargetToAngle() {
    // TODO: Implement setTargetToAngle
}

float AnimationPlayer::getTargetAngle() {
    // TODO: Implement getTargetAngle
    return 0;
}

void AnimationPlayer::setTargetAngle(float var1) {
    // TODO: Implement setTargetAngle
}

float AnimationPlayer::getMaxTwistAngle() {
    // TODO: Implement getMaxTwistAngle
    return 0;
}

void AnimationPlayer::setMaxTwistAngle(float var1) {
    // TODO: Implement setMaxTwistAngle
}

float AnimationPlayer::getExcessTwistAngle() {
    // TODO: Implement getExcessTwistAngle
    return 0;
}

float AnimationPlayer::getTwistAngle() {
    // TODO: Implement getTwistAngle
    return 0;
}

float AnimationPlayer::getShoulderTwistAngle() {
    // TODO: Implement getShoulderTwistAngle
    return 0;
}

float AnimationPlayer::getTargetTwistAngle() {
    // TODO: Implement getTargetTwistAngle
    return 0;
}

} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
