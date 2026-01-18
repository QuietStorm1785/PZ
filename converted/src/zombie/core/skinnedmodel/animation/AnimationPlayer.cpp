#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {

private AnimationPlayer::AnimationPlayer() {
 // TODO: Implement AnimationPlayer
 return nullptr;
}

AnimationPlayer AnimationPlayer::alloc(Model _model) {
 // TODO: Implement alloc
 return nullptr;
}

float AnimationPlayer::lerpBlendWeight(float from, float to, float fadeTimeTo1) {
 // TODO: Implement lerpBlendWeight
 return 0;
}

void AnimationPlayer::setModel(Model _model) {
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

void AnimationPlayer::addBoneReparent(const std::string& boneName, const std::string& newParentBone) {
 // TODO: Implement addBoneReparent
}

void AnimationPlayer::setTwistBones(String... bones) {
 // TODO: Implement setTwistBones
}

void AnimationPlayer::setCounterRotationBone(const std::string& boneName) {
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

int AnimationPlayer::getSkinningBoneIndex(const std::string& boneName, int defaultVal) {
 // TODO: Implement getSkinningBoneIndex
 return 0;
}

void AnimationPlayer::resetSkinTransformsInternal() {
 // TODO: Implement resetSkinTransformsInternal
}

Matrix4f AnimationPlayer::GetPropBoneMatrix(int bone) {
 // TODO: Implement GetPropBoneMatrix
 return nullptr;
}

AnimationTrack AnimationPlayer::startClip(AnimationClip animationClip, bool boolean0) {
 // TODO: Implement startClip
 return nullptr;
}

void AnimationPlayer::releaseTracks(List<AnimationTrack> tracks) {
 // TODO: Implement releaseTracks
}

AnimationTrack AnimationPlayer::play(const std::string& animName, bool looped) {
 // TODO: Implement play
 return nullptr;
}

void AnimationPlayer::Update() {
 // TODO: Implement Update
}

void AnimationPlayer::Update(float deltaT) {
 // TODO: Implement Update
}

void AnimationPlayer::updateInternal(float float0) {
 // TODO: Implement updateInternal
}

SharedSkeleAnimationTrack AnimationPlayer::determineCurrentSharedSkeleTrack() {
 // TODO: Implement determineCurrentSharedSkeleTrack
 return nullptr;
}

void AnimationPlayer::updateAnimation_NonVisualOnly() {
 // TODO: Implement updateAnimation_NonVisualOnly
}

void AnimationPlayer::setSharedAnimRepo(SharedSkeleAnimationRepository repo) {
 // TODO: Implement setSharedAnimRepo
}

void AnimationPlayer::updateAnimation_SharedSkeleTrack(SharedSkeleAnimationTrack sharedSkeleAnimationTrack, float float0) {
 // TODO: Implement updateAnimation_SharedSkeleTrack
}

void AnimationPlayer::updateAnimation_StandardAnimation() {
 // TODO: Implement updateAnimation_StandardAnimation
}

void AnimationPlayer::copyBoneTransformsFromParentPlayer() {
 // TODO: Implement copyBoneTransformsFromParentPlayer
}

float AnimationPlayer::calculateAnimPlayerAngle(Vector2 dir) {
 // TODO: Implement calculateAnimPlayerAngle
 return 0;
}

void AnimationPlayer::SetDir(Vector2 dir) {
 // TODO: Implement SetDir
}

void AnimationPlayer::SetForceDir(Vector2 dir) {
 // TODO: Implement SetForceDir
}

void AnimationPlayer::UpdateDir(IsoGameCharacter character) {
 // TODO: Implement UpdateDir
}

void AnimationPlayer::DoAngles() {
 // TODO: Implement DoAngles
}

void AnimationPlayer::doAnglesInternal() {
 // TODO: Implement doAnglesInternal
}

void AnimationPlayer::interpolateBodyAngle(float float3) {
 // TODO: Implement interpolateBodyAngle
}

void AnimationPlayer::interpolateBodyTwist(float float5) {
 // TODO: Implement interpolateBodyTwist
}

void AnimationPlayer::interpolateShoulderTwist(float float4) {
 // TODO: Implement interpolateShoulderTwist
}

void AnimationPlayer::updateTwistBone() {
 // TODO: Implement updateTwistBone
}

void AnimationPlayer::updateTwistBoneInternal() {
 // TODO: Implement updateTwistBoneInternal
}

void AnimationPlayer::applyTwistBone(SkinningBone skinningBone, float float1) {
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

void AnimationPlayer::applyRotationToDeferredMovement(Vector2 vector) {
 // TODO: Implement applyRotationToDeferredMovement
}

void AnimationPlayer::applyBoneReParenting() {
 // TODO: Implement applyBoneReParenting
}

void AnimationPlayer::applyBoneReParentingInternal() {
 // TODO: Implement applyBoneReParentingInternal
}

void AnimationPlayer::updateBoneAnimationTransform(int int0, AnimationBoneBindingPair animationBoneBindingPair) {
 // TODO: Implement updateBoneAnimationTransform
}

void AnimationPlayer::updateBoneAnimationTransform_Internal(int int1, AnimationBoneBindingPair animationBoneBindingPair) {
 // TODO: Implement updateBoneAnimationTransform_Internal
}

bool AnimationPlayer::isBoneReparented(int boneIdx) {
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

void AnimationPlayer::setRecorder(AnimationPlayerRecorder recorder) {
 // TODO: Implement setRecorder
}

AnimationPlayerRecorder AnimationPlayer::getRecorder() {
 // TODO: Implement getRecorder
 return nullptr;
}

void AnimationPlayer::dismember(int bone) {
 // TODO: Implement dismember
}

void AnimationPlayer::updateModelTransforms() {
 // TODO: Implement updateModelTransforms
}

void AnimationPlayer::updateModelTransformsInternal() {
 // TODO: Implement updateModelTransformsInternal
}

Matrix4f AnimationPlayer::getBoneModelTransform(int boneIdx, Matrix4f out_modelTransform) {
 // TODO: Implement getBoneModelTransform
 return nullptr;
}

Matrix4f AnimationPlayer::getBoneTransform(int boneIdx, Matrix4f out_boneTransform) {
 // TODO: Implement getBoneTransform
 return nullptr;
}

Matrix4f AnimationPlayer::getUnweightedModelTransform(AnimationTrack track, int boneIdx, Matrix4f out_modelTransform) {
 // TODO: Implement getUnweightedModelTransform
 return nullptr;
}

Matrix4f AnimationPlayer::getUnweightedBoneTransform(AnimationTrack track, int boneIdx, Matrix4f out_boneTransform) {
 // TODO: Implement getUnweightedBoneTransform
 return nullptr;
}

void AnimationPlayer::UpdateSkinTransforms() {
 // TODO: Implement UpdateSkinTransforms
}

void AnimationPlayer::getDeferredMovement(Vector2 out_result) {
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

void AnimationPlayer::setRecording(bool val) {
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

void AnimationPlayer::setAngle(float angle) {
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

void AnimationPlayer::setTargetAngle(float targetAngle) {
 // TODO: Implement setTargetAngle
}

float AnimationPlayer::getMaxTwistAngle() {
 // TODO: Implement getMaxTwistAngle
 return 0;
}

void AnimationPlayer::setMaxTwistAngle(float radians) {
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

void AnimationPlayer::setSkinnedTo(SkinningData arg0) {
 // TODO: Implement setSkinnedTo
}

} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
