#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "org/lwjgl/util/vector/Vector4f.h"
#include "zombie/GameProfiler.h"
#include "zombie/GameTime.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/math/Vector3.h"
#include "zombie/core/skinnedmodel/HelperFunctions.h"
#include "zombie/core/skinnedmodel/advancedanimation/AdvancedAnimator.h"
#include "zombie/core/skinnedmodel/animation/debug/AnimationPlayerRecorder.h"
#include "zombie/core/skinnedmodel/animation/sharedskele/SharedSkeleAnimationRepository.h"
#include "zombie/core/skinnedmodel/animation/sharedskele/SharedSkeleAnimationTrack.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/model/SkinningBone.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/MPStatistic.h"
#include "zombie/util/IPooledObject.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Created by LEMMYATI on 03/01/14.
 */
class AnimationPlayer : public PooledObject {
public:
 Model model;
 const Matrix4f propTransforms = new Matrix4f();
 bool m_boneTransformsNeedFirstFrame = true;
 private TwistableBoneTransform[] m_boneTransforms;
 public Matrix4f[] modelTransforms;
 private AnimationPlayer.SkinTransformData m_skinTransformData = nullptr;
 private AnimationPlayer.SkinTransformData m_skinTransformDataPool = nullptr;
 SkinningData m_skinningData;
 SharedSkeleAnimationRepository m_sharedSkeleAnimationRepo = nullptr;
 SharedSkeleAnimationTrack m_currentSharedTrack;
 AnimationClip m_currentSharedTrackClip;
 float m_angle;
 float m_targetAngle;
 float m_twistAngle;
 float m_shoulderTwistAngle;
 float m_targetTwistAngle;
 float m_maxTwistAngle = PZMath.degToRad(70.0F);
 float m_excessTwist = 0.0F;
 static const float angleStepBase = 0.15F;
 float angleStepDelta = 1.0F;
 float angleTwistDelta = 1.0F;
 bool bDoBlending = true;
 bool bUpdateBones = true;
 const Vector2 m_lastSetDir = new Vector2();
 private ArrayList<AnimationBoneBindingPair> m_reparentedBoneBindings = std::make_unique<ArrayList<>>();
 private List<AnimationBoneBinding> m_twistBones = std::make_unique<ArrayList<>>();
 AnimationBoneBinding m_counterRotationBone = nullptr;
 public ArrayList<Integer> dismembered = std::make_unique<ArrayList<>>();
 const float m_minimumValidAnimWeight = 0.001F;
 const int m_animBlendIndexCacheSize = 32;
 private int[] m_animBlendIndices = new int[32];
 private float[] m_animBlendWeights = new float[32];
 private int[] m_animBlendLayers = new int[32];
 private int[] m_animBlendPriorities = new int[32];
 const int m_maxLayers = 4;
 private int[] m_layerBlendCounts = new int[4];
 private float[] m_layerWeightTotals = new float[4];
 int m_totalAnimBlendCount = 0;
 AnimationPlayer parentPlayer;
 const Vector2 m_deferredMovement = new Vector2();
 float m_deferredRotationWeight = 0.0F;
 float m_deferredAngleDelta = 0.0F;
 AnimationPlayerRecorder m_recorder = nullptr;
 private static AnimationTrack[] tempTracks = new AnimationTrack[0];
 static const Vector2 tempo = new Vector2();
 private static Pool<AnimationPlayer> s_pool = new Pool<>(AnimationPlayer::new);
 const AnimationMultiTrack m_multiTrack = new AnimationMultiTrack();

 private AnimationPlayer() {
 }

 static AnimationPlayer alloc(Model _model) {
 AnimationPlayer animationPlayer = s_pool.alloc();
 animationPlayer.setModel(_model);
 return animationPlayer;
 }

 /**
 * 
 * @param from
 * @param to
 * @param fadeTimeTo1 The time to go from 0
 */
 static float lerpBlendWeight(float from, float to, float fadeTimeTo1) {
 if (PZMath.equal(from, to, 1.0E-4F) {
 return to;
 } else {
 float float0 = 1.0F / fadeTimeTo1;
 float float1 = GameTime.getInstance().getTimeDelta();
 float float2 = to - from;
 float float3 = PZMath.sign(float2);
 float float4 = from + float3 * float0 * float1;
 float float5 = to - float4;
 float float6 = PZMath.sign(float5);
 if (float6 != float3) {
 float4 = to;
 }

 return float4;
 }
 }

 void setModel(Model _model) {
 Objects.requireNonNull(_model);
 if (_model != this->model) {
 this->model = _model;
 this->initSkinningData();
 }
 }

 Model getModel() {
 return this->model;
 }

 void initSkinningData() {
 if (this->model.isReady()) {
 SkinningData skinningData = (SkinningData)this->model.Tag;
 if (skinningData != nullptr) {
 if (this->m_skinningData != skinningData) {
 if (this->m_skinningData != nullptr) {
 this->m_skinningData = nullptr;
 this->m_multiTrack.reset();
 }

 this->m_skinningData = skinningData;
 Lambda.forEachFrom(PZArrayUtil::forEach, this->m_reparentedBoneBindings, this->m_skinningData, AnimationBoneBindingPair::setSkinningData);
 Lambda.forEachFrom(PZArrayUtil::forEach, this->m_twistBones, this->m_skinningData, AnimationBoneBinding::setSkinningData);
 if (this->m_counterRotationBone != nullptr) {
 this->m_counterRotationBone.setSkinningData(this->m_skinningData);
 }

 int int0 = skinningData.numBones();
 this->modelTransforms = PZArrayUtil.newInstance(Matrix4f.class, this->modelTransforms, int0, Matrix4f::new);
 this->m_boneTransforms = PZArrayUtil.newInstance(TwistableBoneTransform.class, this->m_boneTransforms, int0);

 for (int int1 = 0; int1 < int0; int1++) {
 if (this->m_boneTransforms[int1] == nullptr) {
 this->m_boneTransforms[int1] = TwistableBoneTransform.alloc();
 }

 this->m_boneTransforms[int1].setIdentity();
 }

 this->m_boneTransformsNeedFirstFrame = true;
 }
 }
 }
 }

 bool isReady() {
 this->initSkinningData();
 return this->hasSkinningData();
 }

 bool hasSkinningData() {
 return this->m_skinningData != nullptr;
 }

 void addBoneReparent(const std::string& boneName, const std::string& newParentBone) {
 if (!PZArrayUtil.contains(this->m_reparentedBoneBindings, Lambda.predicate(boneName, newParentBone, AnimationBoneBindingPair::matches) {
 AnimationBoneBindingPair animationBoneBindingPair = new AnimationBoneBindingPair(boneName, newParentBone);
 animationBoneBindingPair.setSkinningData(this->m_skinningData);
 this->m_reparentedBoneBindings.add(animationBoneBindingPair);
 }
 }

 void setTwistBones(String... bones) {
 std::vector arrayList = AnimationPlayer.L_setTwistBones.boneNames;
 PZArrayUtil.listConvert(this->m_twistBones, arrayList, animationBoneBinding -> animationBoneBinding.boneName);
 if (!PZArrayUtil.sequenceEqual(bones, arrayList, PZArrayUtil.Comparators::equalsIgnoreCase) {
 this->m_twistBones.clear();
 Lambda.forEachFrom(PZArrayUtil::forEach, bones, this, (object, animationPlayer) -> {
 AnimationBoneBinding animationBoneBinding = new AnimationBoneBinding((String)object);
 animationBoneBinding.setSkinningData(animationPlayer.m_skinningData);
 animationPlayer.m_twistBones.add(animationBoneBinding);
 });
 }
 }

 void setCounterRotationBone(const std::string& boneName) {
 if (this->m_counterRotationBone != nullptr && StringUtils == this->m_counterRotationBone.boneName, boneName) {
 }

 this->m_counterRotationBone = new AnimationBoneBinding(boneName);
 this->m_counterRotationBone.setSkinningData(this->m_skinningData);
 }

 AnimationBoneBinding getCounterRotationBone() {
 return this->m_counterRotationBone;
 }

 void reset() {
 this->m_multiTrack.reset();
 }

 void onReleased() {
 this->model = nullptr;
 this->m_skinningData = nullptr;
 this->propTransforms.setIdentity();
 this->m_boneTransformsNeedFirstFrame = true;
 IPooledObject.tryReleaseAndBlank(this->m_boneTransforms);
 PZArrayUtil.forEach(this->modelTransforms, Matrix::setIdentity);
 this->resetSkinTransforms();
 this->setAngle(0.0F);
 this->setTargetAngle(0.0F);
 this->m_twistAngle = 0.0F;
 this->m_shoulderTwistAngle = 0.0F;
 this->m_targetTwistAngle = 0.0F;
 this->m_maxTwistAngle = PZMath.degToRad(70.0F);
 this->m_excessTwist = 0.0F;
 this->angleStepDelta = 1.0F;
 this->angleTwistDelta = 1.0F;
 this->bDoBlending = true;
 this->bUpdateBones = true;
 this->m_lastSetDir.set(0.0F, 0.0F);
 this->m_reparentedBoneBindings.clear();
 this->m_twistBones.clear();
 this->m_counterRotationBone = nullptr;
 this->dismembered.clear();
 Arrays.fill(this->m_animBlendIndices, 0);
 Arrays.fill(this->m_animBlendWeights, 0.0F);
 Arrays.fill(this->m_animBlendLayers, 0);
 Arrays.fill(this->m_layerBlendCounts, 0);
 Arrays.fill(this->m_layerWeightTotals, 0.0F);
 this->m_totalAnimBlendCount = 0;
 this->parentPlayer = nullptr;
 this->m_deferredMovement.set(0.0F, 0.0F);
 this->m_deferredRotationWeight = 0.0F;
 this->m_deferredAngleDelta = 0.0F;
 this->m_recorder = nullptr;
 this->m_multiTrack.reset();
 }

 SkinningData getSkinningData() {
 return this->m_skinningData;
 }

 public HashMap<String, Integer> getSkinningBoneIndices() {
 return this->m_skinningData != nullptr ? this->m_skinningData.BoneIndices : nullptr;
 }

 int getSkinningBoneIndex(const std::string& boneName, int defaultVal) {
 std::unordered_map hashMap = this->getSkinningBoneIndices();
 return hashMap != nullptr ? (Integer)hashMap.get(boneName) : defaultVal;
 }

 private synchronized AnimationPlayer.SkinTransformData getSkinTransformData(SkinningData skinningData) {
 for (AnimationPlayer.SkinTransformData skinTransformData0 = this->m_skinTransformData;
 skinTransformData0 != nullptr;
 skinTransformData0 = skinTransformData0.m_next
 ) {
 if (skinningData == skinTransformData0.m_skinnedTo) {
 return skinTransformData0;
 }
 }

 AnimationPlayer.SkinTransformData skinTransformData1;
 if (this->m_skinTransformDataPool != nullptr) {
 skinTransformData1 = this->m_skinTransformDataPool;
 skinTransformData1.setSkinnedTo(skinningData);
 skinTransformData1.dirty = true;
 this->m_skinTransformDataPool = this->m_skinTransformDataPool.m_next;
 } else {
 skinTransformData1 = AnimationPlayer.SkinTransformData.alloc(skinningData);
 }

 skinTransformData1.m_next = this->m_skinTransformData;
 this->m_skinTransformData = skinTransformData1;
 return skinTransformData1;
 }

 private synchronized void resetSkinTransforms() {
 GameProfiler.getInstance().invokeAndMeasure("resetSkinTransforms", this, AnimationPlayer::resetSkinTransformsInternal);
 }

 void resetSkinTransformsInternal() {
 if (this->m_skinTransformDataPool != nullptr) {
 AnimationPlayer.SkinTransformData skinTransformData = this->m_skinTransformDataPool;

 while (skinTransformData.m_next != nullptr) {
 skinTransformData = skinTransformData.m_next;
 }

 skinTransformData.m_next = this->m_skinTransformData;
 } else {
 this->m_skinTransformDataPool = this->m_skinTransformData;
 }

 this->m_skinTransformData = nullptr;
 }

 Matrix4f GetPropBoneMatrix(int bone) {
 this->propTransforms.load(this->modelTransforms[bone]);
 return this->propTransforms;
 }

 AnimationTrack startClip(AnimationClip animationClip, bool boolean0) {
 if (animationClip == nullptr) {
 throw NullPointerException("Supplied clip is nullptr.");
 } else {
 AnimationTrack animationTrack = AnimationTrack.alloc();
 animationTrack.startClip(animationClip, boolean0);
 animationTrack.name = animationClip.Name;
 animationTrack.IsPlaying = true;
 this->m_multiTrack.addTrack(animationTrack);
 return animationTrack;
 }
 }

 static void releaseTracks(List<AnimationTrack> tracks) {
 AnimationTrack[] animationTracks = tracks.toArray(tempTracks);
 PZArrayUtil.forEach(animationTracks, PooledObject::release);
 }

 AnimationTrack play(const std::string& animName, bool looped) {
 if (this->m_skinningData == nullptr) {
 return nullptr;
 } else {
 AnimationClip animationClip = this->m_skinningData.AnimationClips.get(animName);
 if (animationClip == nullptr) {
 DebugLog.General.warn("Anim Clip not found: %s", animName);
 return nullptr;
 } else {
 return this->startClip(animationClip, looped);
 }
 }
 }

 void Update() {
 this->Update(GameTime.instance.getTimeDelta());
 }

 void Update(float deltaT) {
 MPStatistic.getInstance().AnimationPlayerUpdate.Start();
 GameProfiler.getInstance().invokeAndMeasure("AnimationPlayer.Update", this, deltaT, AnimationPlayer::updateInternal);
 MPStatistic.getInstance().AnimationPlayerUpdate.End();
 }

 void updateInternal(float float0) {
 if (this->isReady()) {
 this->m_multiTrack.Update((float)float0);
 if (!this->bUpdateBones) {
 this->updateAnimation_NonVisualOnly();
 } else if (this->m_multiTrack.getTrackCount() > 0) {
 SharedSkeleAnimationTrack sharedSkeleAnimationTrack = this->determineCurrentSharedSkeleTrack();
 if (sharedSkeleAnimationTrack != nullptr) {
 float float1 = this->m_multiTrack.getTrackAt(0).getCurrentTime();
 this->updateAnimation_SharedSkeleTrack(sharedSkeleAnimationTrack, float1);
 } else {
 this->updateAnimation_StandardAnimation();
 }
 }
 }
 }

 SharedSkeleAnimationTrack determineCurrentSharedSkeleTrack() {
 if (this->m_sharedSkeleAnimationRepo == nullptr) {
 return nullptr;
 } else if (this->bDoBlending) {
 return nullptr;
 } else if (!DebugOptions.instance.Animation.SharedSkeles.Enabled.getValue()) {
 return nullptr;
 } else if (this->m_multiTrack.getTrackCount() != 1) {
 return nullptr;
 } else if (!PZMath.equal(this->m_twistAngle, 0.0F, 114.59155F) {
 return nullptr;
 } else if (this->parentPlayer != nullptr) {
 return nullptr;
 } else {
 AnimationTrack animationTrack = this->m_multiTrack.getTrackAt(0);
 float float0 = animationTrack.blendFieldWeight;
 if (!PZMath.equal(float0, 0.0F, 0.1F) {
 return nullptr;
 } else {
 AnimationClip animationClip = animationTrack.getClip();
 if (animationClip == this->m_currentSharedTrackClip) {
 return this->m_currentSharedTrack;
 } else {
 SharedSkeleAnimationTrack sharedSkeleAnimationTrack = this->m_sharedSkeleAnimationRepo.getTrack(animationClip);
 if (sharedSkeleAnimationTrack == nullptr) {
 DebugLog.Animation.debugln("Caching SharedSkeleAnimationTrack: %s", animationTrack.name);
 sharedSkeleAnimationTrack = std::make_unique<SharedSkeleAnimationTrack>();
 ModelTransformSampler modelTransformSampler = ModelTransformSampler.alloc(this, animationTrack);

 try {
 sharedSkeleAnimationTrack.set(modelTransformSampler, 5.0F);
 } finally {
 modelTransformSampler.release();
 }

 this->m_sharedSkeleAnimationRepo.setTrack(animationClip, sharedSkeleAnimationTrack);
 }

 this->m_currentSharedTrackClip = animationClip;
 this->m_currentSharedTrack = sharedSkeleAnimationTrack;
 return sharedSkeleAnimationTrack;
 }
 }
 }
 }

 void updateAnimation_NonVisualOnly() {
 this->updateMultiTrackBoneTransforms_DeferredMovementOnly();
 this->DoAngles();
 this->calculateDeferredMovement();
 }

 void setSharedAnimRepo(SharedSkeleAnimationRepository repo) {
 this->m_sharedSkeleAnimationRepo = repo;
 }

 void updateAnimation_SharedSkeleTrack(SharedSkeleAnimationTrack sharedSkeleAnimationTrack, float float0) {
 this->updateMultiTrackBoneTransforms_DeferredMovementOnly();
 this->DoAngles();
 this->calculateDeferredMovement();
 sharedSkeleAnimationTrack.moveToTime(float0);

 for (int int0 = 0; int0 < this->modelTransforms.length; int0++) {
 sharedSkeleAnimationTrack.getBoneMatrix(int0, this->modelTransforms[int0]);
 }

 this->UpdateSkinTransforms();
 }

 void updateAnimation_StandardAnimation() {
 if (this->parentPlayer == nullptr) {
 this->updateMultiTrackBoneTransforms();
 } else {
 this->copyBoneTransformsFromParentPlayer();
 }

 this->DoAngles();
 this->calculateDeferredMovement();
 this->updateTwistBone();
 this->applyBoneReParenting();
 this->updateModelTransforms();
 this->UpdateSkinTransforms();
 }

 void copyBoneTransformsFromParentPlayer() {
 this->m_boneTransformsNeedFirstFrame = false;

 for (int int0 = 0; int0 < this->m_boneTransforms.length; int0++) {
 this->m_boneTransforms[int0].set(this->parentPlayer.m_boneTransforms[int0]);
 }
 }

 static float calculateAnimPlayerAngle(Vector2 dir) {
 return dir.getDirection();
 }

 void SetDir(Vector2 dir) {
 if (this->m_lastSetDir.x != dir.x || this->m_lastSetDir.y != dir.y) {
 this->setTargetAngle(calculateAnimPlayerAngle(dir);
 this->m_targetTwistAngle = PZMath.getClosestAngle(this->m_angle, this->m_targetAngle);
 float float0 = PZMath.clamp(this->m_targetTwistAngle, -this->m_maxTwistAngle, this->m_maxTwistAngle);
 this->m_excessTwist = PZMath.getClosestAngle(float0, this->m_targetTwistAngle);
 this->m_lastSetDir.set(dir);
 }
 }

 void SetForceDir(Vector2 dir) {
 this->setTargetAngle(calculateAnimPlayerAngle(dir);
 this->setAngleToTarget();
 this->m_targetTwistAngle = 0.0F;
 this->m_lastSetDir.set(dir);
 }

 void UpdateDir(IsoGameCharacter character) {
 if (character != nullptr) {
 this->SetDir(character.getForwardDirection());
 }
 }

 void DoAngles() {
 GameProfiler.getInstance().invokeAndMeasure("AnimationPlayer.doAngles", this, AnimationPlayer::doAnglesInternal);
 }

 void doAnglesInternal() {
 float float0 = 0.15F * GameTime.instance.getMultiplier();
 this->interpolateBodyAngle(float0);
 this->interpolateBodyTwist(float0);
 this->interpolateShoulderTwist(float0);
 }

 void interpolateBodyAngle(float float3) {
 float float0 = PZMath.getClosestAngle(this->m_angle, this->m_targetAngle);
 if (PZMath.equal(float0, 0.0F, 0.001F) {
 this->setAngleToTarget();
 this->m_targetTwistAngle = 0.0F;
 } else {
 float float1 = PZMath.sign(float0);
 float float2 = float3 * float1 * this->angleStepDelta;
 float float4;
 if (DebugOptions.instance.Character.Debug.Animate.DeferredRotationOnly.getValue()) {
 float4 = this->m_deferredAngleDelta;
 } else if (this->m_deferredRotationWeight > 0.0F) {
 float4 = this->m_deferredAngleDelta;
 } else {
 float4 = float2;
 }

 float float5 = PZMath.sign(float4);
 float float6 = this->m_angle;
 float float7 = float6 + float4;
 float float8 = PZMath.getClosestAngle(float7, this->m_targetAngle);
 float float9 = PZMath.sign(float8);
 if (float9 != float1 && float5 == float1) {
 this->setAngleToTarget();
 this->m_targetTwistAngle = 0.0F;
 } else {
 this->setAngle(float7);
 this->m_targetTwistAngle = float8;
 }
 }
 }

 void interpolateBodyTwist(float float5) {
 float float0 = PZMath.wrap(this->m_targetTwistAngle, (float) -Math.PI, (float) Math.PI);
 float float1 = PZMath.clamp(float0, -this->m_maxTwistAngle, this->m_maxTwistAngle);
 this->m_excessTwist = PZMath.getClosestAngle(float1, float0);
 float float2 = PZMath.getClosestAngle(this->m_twistAngle, float1);
 if (PZMath.equal(float2, 0.0F, 0.001F) {
 this->m_twistAngle = float1;
 } else {
 float float3 = PZMath.sign(float2);
 float float4 = float5 * float3 * this->angleTwistDelta;
 float float6 = this->m_twistAngle;
 float float7 = float6 + float4;
 float float8 = PZMath.getClosestAngle(float7, float1);
 float float9 = PZMath.sign(float8);
 if (float9 == float3) {
 this->m_twistAngle = float7;
 } else {
 this->m_twistAngle = float1;
 }
 }
 }

 void interpolateShoulderTwist(float float4) {
 float float0 = PZMath.wrap(this->m_twistAngle, (float) -Math.PI, (float) Math.PI);
 float float1 = PZMath.getClosestAngle(this->m_shoulderTwistAngle, float0);
 if (PZMath.equal(float1, 0.0F, 0.001F) {
 this->m_shoulderTwistAngle = float0;
 } else {
 float float2 = PZMath.sign(float1);
 float float3 = float4 * float2 * this->angleTwistDelta * 0.55F;
 float float5 = this->m_shoulderTwistAngle;
 float float6 = float5 + float3;
 float float7 = PZMath.getClosestAngle(float6, float0);
 float float8 = PZMath.sign(float7);
 if (float8 == float2) {
 this->m_shoulderTwistAngle = float6;
 } else {
 this->m_shoulderTwistAngle = float0;
 }
 }
 }

 void updateTwistBone() {
 GameProfiler.getInstance().invokeAndMeasure("updateTwistBone", this, AnimationPlayer::updateTwistBoneInternal);
 }

 void updateTwistBoneInternal() {
 if (!this->m_twistBones.empty()) {
 float float0 = PZMath.degToRad(1.0F);
 if (!PZMath.equal(this->m_twistAngle, 0.0F, float0) {
 if (!DebugOptions.instance.Character.Debug.Animate.NoBoneTwists.getValue()) {
 int int0 = this->m_twistBones.size();
 int int1 = int0 - 1;
 float float1 = -this->m_shoulderTwistAngle;
 float float2 = float1 / int1;

 for (int int2 = 0; int2 < int1; int2++) {
 SkinningBone skinningBone0 = this->m_twistBones.get(int2).getBone();
 this->applyTwistBone(skinningBone0, float2);
 }

 float float3 = -this->m_twistAngle;
 float float4 = PZMath.getClosestAngle(float1, float3);
 if (PZMath.abs(float4) > 1.0E-4F) {
 SkinningBone skinningBone1 = this->m_twistBones.get(int1).getBone();
 this->applyTwistBone(skinningBone1, float4);
 }
 }
 }
 }
 }

 void applyTwistBone(SkinningBone skinningBone, float float1) {
 if (skinningBone != nullptr) {
 int int0 = skinningBone.Index;
 int int1 = skinningBone.Parent.Index;
 Matrix4f matrix4f0 = this->getBoneModelTransform(int1, AnimationPlayer.L_applyTwistBone.twistParentBoneTrans);
 Matrix4f matrix4f1 = Matrix4f.invert(matrix4f0, AnimationPlayer.L_applyTwistBone.twistParentBoneTransInv);
 if (matrix4f1 != nullptr) {
 Matrix4f matrix4f2 = this->getBoneModelTransform(int0, AnimationPlayer.L_applyTwistBone.twistBoneTrans);
 Quaternion quaternion0 = AnimationPlayer.L_applyTwistBone.twistBoneTargetRot;
 Matrix4f matrix4f3 = AnimationPlayer.L_applyTwistBone.twistRotDiffTrans;
 matrix4f3.setIdentity();
 AnimationPlayer.L_applyTwistBone.twistRotDiffTransAxis.set(0.0F, 1.0F, 0.0F);
 float float0 = PZMath.getClosestAngle(this->m_boneTransforms[int0].Twist, float1);
 this->m_boneTransforms[int0].Twist = float1;
 matrix4f3.rotate(float0, AnimationPlayer.L_applyTwistBone.twistRotDiffTransAxis);
 Matrix4f matrix4f4 = AnimationPlayer.L_applyTwistBone.twistBoneTargetTrans;
 Matrix4f.mul(matrix4f2, matrix4f3, matrix4f4);
 HelperFunctions.getRotation(matrix4f4, quaternion0);
 Quaternion quaternion1 = AnimationPlayer.L_applyTwistBone.twistBoneNewRot;
 quaternion1.set(quaternion0);
 Vector3f vector3f0 = HelperFunctions.getPosition(matrix4f2, AnimationPlayer.L_applyTwistBone.twistBonePos);
 Vector3f vector3f1 = AnimationPlayer.L_applyTwistBone.twistBoneScale;
 vector3f1.set(1.0F, 1.0F, 1.0F);
 Matrix4f matrix4f5 = AnimationPlayer.L_applyTwistBone.twistBoneNewTrans;
 HelperFunctions.CreateFromQuaternionPositionScale(vector3f0, quaternion1, vector3f1, matrix4f5);
 this->m_boneTransforms[int0].mul(matrix4f5, matrix4f1);
 }
 }
 }

 void resetBoneModelTransforms() {
 if (this->m_skinningData != nullptr && this->modelTransforms != nullptr) {
 this->m_boneTransformsNeedFirstFrame = true;
 int int0 = this->m_boneTransforms.length;

 for (int int1 = 0; int1 < int0; int1++) {
 this->m_boneTransforms[int1].BlendWeight = 0.0F;
 this->m_boneTransforms[int1].setIdentity();
 this->modelTransforms[int1].setIdentity();
 }
 }
 }

 bool isBoneTransformsNeedFirstFrame() {
 return this->m_boneTransformsNeedFirstFrame;
 }

 void updateMultiTrackBoneTransforms() {
 GameProfiler.getInstance().invokeAndMeasure("updateMultiTrackBoneTransforms", this, AnimationPlayer::updateMultiTrackBoneTransformsInternal);
 }

 void updateMultiTrackBoneTransformsInternal() {
 for (int int0 = 0; int0 < this->modelTransforms.length; int0++) {
 this->modelTransforms[int0].setIdentity();
 }

 this->updateLayerBlendWeightings();
 if (this->m_totalAnimBlendCount != 0) {
 if (this->isRecording()) {
 this->m_recorder.logAnimWeights(this->m_multiTrack.getTracks(), this->m_animBlendIndices, this->m_animBlendWeights, this->m_deferredMovement);
 }

 for (int int1 = 0; int1 < this->m_boneTransforms.length; int1++) {
 if (!this->isBoneReparented(int1) {
 this->updateBoneAnimationTransform(int1, nullptr);
 }
 }

 this->m_boneTransformsNeedFirstFrame = false;
 }
 }

 void updateLayerBlendWeightings() {
 std::vector list = this->m_multiTrack.getTracks();
 int int0 = list.size();
 PZArrayUtil.arraySet(this->m_animBlendIndices, -1);
 PZArrayUtil.arraySet(this->m_animBlendWeights, 0.0F);
 PZArrayUtil.arraySet(this->m_animBlendLayers, -1);
 PZArrayUtil.arraySet(this->m_animBlendPriorities, 0);

 for (int int1 = 0; int1 < int0; int1++) {
 AnimationTrack animationTrack = (AnimationTrack)list.get(int1);
 float float0 = animationTrack.BlendDelta;
 int int2 = animationTrack.getLayerIdx();
 int int3 = animationTrack.getPriority();
 if (int2 >= 0 && int2 < 4) {
 if (!(float0 < 0.001F) && (int2 <= 0 || !animationTrack.isFinished())) {
 int int4 = -1;

 for (int int5 = 0; int5 < this->m_animBlendIndices.length; int5++) {
 if (this->m_animBlendIndices[int5] == -1) {
 int4 = int5;
 break;
 }

 if (int2 <= this->m_animBlendLayers[int5]) {
 if (int2 < this->m_animBlendLayers[int5]) {
 int4 = int5;
 break;
 }

 if (int3 <= this->m_animBlendPriorities[int5]) {
 if (int3 < this->m_animBlendPriorities[int5]) {
 int4 = int5;
 break;
 }

 if (float0 < this->m_animBlendWeights[int5]) {
 int4 = int5;
 break;
 }
 }
 }
 }

 if (int4 < 0) {
 DebugLog.General
 .error(
 "Buffer overflow. Insufficient anim blends in cache. More than %d animations are being blended at once. Will be truncated to %d.",
 this->m_animBlendIndices.length,
 this->m_animBlendIndices.length
 );
 } else {
 PZArrayUtil.insertAt(this->m_animBlendIndices, int4, int1);
 PZArrayUtil.insertAt(this->m_animBlendWeights, int4, float0);
 PZArrayUtil.insertAt(this->m_animBlendLayers, int4, int2);
 PZArrayUtil.insertAt(this->m_animBlendPriorities, int4, int3);
 }
 }
 } else {
 DebugLog.General.error("Layer index is out of range: %d. Range: 0 - %d", int2, 3);
 }
 }

 PZArrayUtil.arraySet(this->m_layerBlendCounts, 0);
 PZArrayUtil.arraySet(this->m_layerWeightTotals, 0.0F);
 this->m_totalAnimBlendCount = 0;

 for (int int6 = 0; int6 < this->m_animBlendIndices.length && this->m_animBlendIndices[int6] >= 0; int6++) {
 int int7 = this->m_animBlendLayers[int6];
 this->m_layerWeightTotals[int7] = this->m_layerWeightTotals[int7] + this->m_animBlendWeights[int6];
 this->m_layerBlendCounts[int7]++;
 this->m_totalAnimBlendCount++;
 }

 if (this->m_totalAnimBlendCount != 0) {
 if (this->m_boneTransformsNeedFirstFrame) {
 int int8 = this->m_animBlendLayers[0];
 int int9 = this->m_layerBlendCounts[0];
 float float1 = this->m_layerWeightTotals[0];
 if (float1 < 1.0F) {
 for (int int10 = 0; int10 < this->m_totalAnimBlendCount; int10++) {
 int int11 = this->m_animBlendLayers[int10];
 if (int11 != int8) {
 break;
 }

 if (float1 > 0.0F) {
 this->m_animBlendWeights[int10] = this->m_animBlendWeights[int10] / float1;
 } else {
 this->m_animBlendWeights[int10] = 1.0F / int9;
 }
 }
 }
 }
 }
 }

 void calculateDeferredMovement() {
 GameProfiler.getInstance().invokeAndMeasure("calculateDeferredMovement", this, AnimationPlayer::calculateDeferredMovementInternal);
 }

 void calculateDeferredMovementInternal() {
 std::vector list = this->m_multiTrack.getTracks();
 this->m_deferredMovement.set(0.0F, 0.0F);
 this->m_deferredAngleDelta = 0.0F;
 this->m_deferredRotationWeight = 0.0F;
 float float0 = 1.0F;

 for (int int0 = this->m_totalAnimBlendCount - 1; int0 >= 0 && !(float0 <= 0.001F); int0--) {
 int int1 = this->m_animBlendIndices[int0];
 AnimationTrack animationTrack = (AnimationTrack)list.get(int1);
 if (!animationTrack.isFinished()) {
 float float1 = animationTrack.getDeferredBoneWeight();
 if (!(float1 <= 0.001F) {
 float float2 = this->m_animBlendWeights[int0] * float1;
 if (!(float2 <= 0.001F) {
 float float3 = PZMath.clamp(float2, 0.0F, float0);
 float0 -= float2;
 float0 = org.joml.Math.max(0.0F, float0);
 Vector2.addScaled(this->m_deferredMovement, animationTrack.getDeferredMovementDiff(tempo), float3, this->m_deferredMovement);
 if (animationTrack.getUseDeferredRotation()) {
 this->m_deferredAngleDelta = this->m_deferredAngleDelta + animationTrack.getDeferredRotationDiff() * float3;
 this->m_deferredRotationWeight += float3;
 }
 }
 }
 }
 }

 this->applyRotationToDeferredMovement(this->m_deferredMovement);
 this->m_deferredMovement.x = this->m_deferredMovement.x * AdvancedAnimator.s_MotionScale;
 this->m_deferredMovement.y = this->m_deferredMovement.y * AdvancedAnimator.s_MotionScale;
 this->m_deferredAngleDelta = this->m_deferredAngleDelta * AdvancedAnimator.s_RotationScale;
 }

 void applyRotationToDeferredMovement(Vector2 vector) {
 float float0 = vector.normalize();
 float float1 = this->getRenderedAngle();
 vector.rotate(float1);
 vector.setLength(-float0);
 }

 void applyBoneReParenting() {
 GameProfiler.getInstance().invokeAndMeasure("applyBoneReParenting", this, AnimationPlayer::applyBoneReParentingInternal);
 }

 void applyBoneReParentingInternal() {
 int int0 = 0;

 for (int int1 = this->m_reparentedBoneBindings.size(); int0 < int1; int0++) {
 AnimationBoneBindingPair animationBoneBindingPair = this->m_reparentedBoneBindings.get(int0);
 if (!animationBoneBindingPair.isValid()) {
 DebugLog.Animation.warn("Animation binding pair is not valid: %s", animationBoneBindingPair);
 } else {
 this->updateBoneAnimationTransform(animationBoneBindingPair.getBoneIdxA(), animationBoneBindingPair);
 }
 }
 }

 void updateBoneAnimationTransform(int int0, AnimationBoneBindingPair animationBoneBindingPair) {
 this->updateBoneAnimationTransform_Internal(int0, animationBoneBindingPair);
 }

 void updateBoneAnimationTransform_Internal(int int1, AnimationBoneBindingPair animationBoneBindingPair) {
 std::vector list = this->m_multiTrack.getTracks();
 Vector3f vector3f0 = AnimationPlayer.L_updateBoneAnimationTransform.pos;
 Quaternion quaternion = AnimationPlayer.L_updateBoneAnimationTransform.rot;
 Vector3f vector3f1 = AnimationPlayer.L_updateBoneAnimationTransform.scale;
 Keyframe keyframe = AnimationPlayer.L_updateBoneAnimationTransform.key;
 int int0 = this->m_totalAnimBlendCount;
 AnimationBoneBinding animationBoneBinding = this->m_counterRotationBone;
 bool boolean0 = animationBoneBinding != nullptr && animationBoneBinding.getBone() != nullptr && animationBoneBinding.getBone().Index == int1;
 keyframe.setIdentity();
 float float0 = 0.0F;
 bool boolean1 = true;
 float float1 = 1.0F;

 for (int int2 = int0 - 1; int2 >= 0 && float1 > 0.0F && !(float1 <= 0.001F); int2--) {
 int int3 = this->m_animBlendIndices[int2];
 AnimationTrack animationTrack = (AnimationTrack)list.get(int3);
 float float2 = animationTrack.getBoneWeight(int1);
 if (!(float2 <= 0.001F) {
 float float3 = this->m_animBlendWeights[int2] * float2;
 if (!(float3 <= 0.001F) {
 float float4 = PZMath.clamp(float3, 0.0F, float1);
 float1 -= float3;
 float1 = org.joml.Math.max(0.0F, float1);
 this->getTrackTransform(int1, animationTrack, animationBoneBindingPair, vector3f0, quaternion, vector3f1);
 if (boolean0 && animationTrack.getUseDeferredRotation()) {
 if (DebugOptions.instance.Character.Debug.Animate.ZeroCounterRotationBone.getValue()) {
 Vector3f vector3f2 = AnimationPlayer.L_updateBoneAnimationTransform.rotAxis;
 Matrix4f matrix4f = AnimationPlayer.L_updateBoneAnimationTransform.rotMat;
 matrix4f.setIdentity();
 vector3f2.set(0.0F, 1.0F, 0.0F);
 matrix4f.rotate((float) (-Math.PI / 2), vector3f2);
 vector3f2.set(1.0F, 0.0F, 0.0F);
 matrix4f.rotate((float) (-Math.PI / 2), vector3f2);
 HelperFunctions.getRotation(matrix4f, quaternion);
 } else {
 Vector3f vector3f3 = HelperFunctions.ToEulerAngles(quaternion, AnimationPlayer.L_updateBoneAnimationTransform.rotEulers);
 HelperFunctions.ToQuaternion(vector3f3.x, vector3f3.y, (float) (Math.PI / 2), quaternion);
 }
 }

 bool boolean2 = animationTrack.getDeferredMovementBoneIdx() == int1;
 if (boolean2) {
 Vector3f vector3f4 = animationTrack.getCurrentDeferredCounterPosition(AnimationPlayer.L_updateBoneAnimationTransform.deferredPos);
 vector3f0.x = vector3f0.x + vector3f4.x;
 vector3f0.y = vector3f0.y + vector3f4.y;
 vector3f0.z = vector3f0.z + vector3f4.z;
 }

 if (boolean1) {
 Vector3.setScaled(vector3f0, float4, keyframe.Position);
 keyframe.Rotation.set(quaternion);
 float0 = float4;
 boolean1 = false;
 } else {
 float float5 = float4 / (float4 + float0);
 float0 += float4;
 Vector3.addScaled(keyframe.Position, vector3f0, float4, keyframe.Position);
 PZMath.slerp(keyframe.Rotation, keyframe.Rotation, quaternion, float5);
 }
 }
 }
 }

 if (float1 > 0.0F && !this->m_boneTransformsNeedFirstFrame) {
 this->m_boneTransforms[int1].getPRS(vector3f0, quaternion, vector3f1);
 Vector3.addScaled(keyframe.Position, vector3f0, float1, keyframe.Position);
 PZMath.slerp(keyframe.Rotation, quaternion, keyframe.Rotation, float0);
 PZMath.lerp(keyframe.Scale, vector3f1, keyframe.Scale, float0);
 }

 this->m_boneTransforms[int1].set(keyframe.Position, keyframe.Rotation, keyframe.Scale);
 this->m_boneTransforms[int1].BlendWeight = float0;
 this->m_boneTransforms[int1].Twist *= 1.0F - float0;
 }

 private void getTrackTransform(
 int int0,
 AnimationTrack animationTrack,
 AnimationBoneBindingPair animationBoneBindingPair,
 Vector3f vector3f0,
 Quaternion quaternion,
 Vector3f vector3f1
 ) {
 if (animationBoneBindingPair == nullptr) {
 animationTrack.get(int0, vector3f0, quaternion, vector3f1);
 } else {
 Matrix4f matrix4f0 = AnimationPlayer.L_getTrackTransform.result;
 SkinningBone skinningBone0 = animationBoneBindingPair.getBoneA();
 Matrix4f matrix4f1 = getUnweightedBoneTransform(animationTrack, skinningBone0.Index, AnimationPlayer.L_getTrackTransform.Pa);
 SkinningBone skinningBone1 = skinningBone0.Parent;
 SkinningBone skinningBone2 = animationBoneBindingPair.getBoneB();
 Matrix4f matrix4f2 = this->getBoneModelTransform(skinningBone1.Index, AnimationPlayer.L_getTrackTransform.mA);
 Matrix4f matrix4f3 = Matrix4f.invert(matrix4f2, AnimationPlayer.L_getTrackTransform.mAinv);
 Matrix4f matrix4f4 = this->getBoneModelTransform(skinningBone2.Index, AnimationPlayer.L_getTrackTransform.mB);
 Matrix4f matrix4f5 = this->getUnweightedModelTransform(animationTrack, skinningBone1.Index, AnimationPlayer.L_getTrackTransform.umA);
 Matrix4f matrix4f6 = this->getUnweightedModelTransform(animationTrack, skinningBone2.Index, AnimationPlayer.L_getTrackTransform.umB);
 Matrix4f matrix4f7 = Matrix4f.invert(matrix4f6, AnimationPlayer.L_getTrackTransform.umBinv);
 Matrix4f.mul(matrix4f1, matrix4f5, matrix4f0);
 Matrix4f.mul(matrix4f0, matrix4f7, matrix4f0);
 Matrix4f.mul(matrix4f0, matrix4f4, matrix4f0);
 Matrix4f.mul(matrix4f0, matrix4f3, matrix4f0);
 HelperFunctions.getPosition(matrix4f0, vector3f0);
 HelperFunctions.getRotation(matrix4f0, quaternion);
 vector3f1.set(1.0F, 1.0F, 1.0F);
 }
 }

 bool isBoneReparented(int boneIdx) {
 return PZArrayUtil.contains(
 this->m_reparentedBoneBindings, Lambda.predicate(boneIdx, (animationBoneBindingPair, integer) -> animationBoneBindingPair.getBoneIdxA() == integer)
 );
 }

 void updateMultiTrackBoneTransforms_DeferredMovementOnly() {
 this->m_deferredMovement.set(0.0F, 0.0F);
 if (this->parentPlayer == nullptr) {
 this->updateLayerBlendWeightings();
 if (this->m_totalAnimBlendCount != 0) {
 int[] ints = AnimationPlayer.updateMultiTrackBoneTransforms_DeferredMovementOnly.boneIndices;
 int int0 = 0;
 std::vector list = this->m_multiTrack.getTracks();
 int int1 = list.size();

 for (int int2 = 0; int2 < int1; int2++) {
 AnimationTrack animationTrack = (AnimationTrack)list.get(int2);
 int int3 = animationTrack.getDeferredMovementBoneIdx();
 if (int3 != -1 && !PZArrayUtil.contains(ints, int0, int3) {
 ints[int0++] = int3;
 }
 }

 for (int int4 = 0; int4 < int0; int4++) {
 this->updateBoneAnimationTransform(ints[int4], nullptr);
 }
 }
 }
 }

 bool isRecording() {
 return this->m_recorder != nullptr && this->m_recorder.isRecording();
 }

 void setRecorder(AnimationPlayerRecorder recorder) {
 this->m_recorder = recorder;
 }

 AnimationPlayerRecorder getRecorder() {
 return this->m_recorder;
 }

 void dismember(int bone) {
 this->dismembered.add(bone);
 }

 void updateModelTransforms() {
 GameProfiler.getInstance().invokeAndMeasure("updateModelTransforms", this, AnimationPlayer::updateModelTransformsInternal);
 }

 void updateModelTransformsInternal() {
 this->m_boneTransforms[0].getMatrix(this->modelTransforms[0]);

 for (int int0 = 1; int0 < this->modelTransforms.length; int0++) {
 SkinningBone skinningBone0 = this->m_skinningData.getBoneAt(int0);
 SkinningBone skinningBone1 = skinningBone0.Parent;
 BoneTransform.mul(this->m_boneTransforms[skinningBone0.Index], this->modelTransforms[skinningBone1.Index], this->modelTransforms[skinningBone0.Index]);
 }
 }

 /**
 * Get the bone's transform, in the model space. That is, relative to the model's origin.
 */
 Matrix4f getBoneModelTransform(int boneIdx, Matrix4f out_modelTransform) {
 Matrix4f matrix4f = AnimationPlayer.L_getBoneModelTransform.boneTransform;
 out_modelTransform.setIdentity();
 SkinningBone skinningBone0 = this->m_skinningData.getBoneAt(boneIdx);

 for (SkinningBone skinningBone1 = skinningBone0; skinningBone1 != nullptr; skinningBone1 = skinningBone1.Parent) {
 this->getBoneTransform(skinningBone1.Index, matrix4f);
 Matrix4f.mul(out_modelTransform, matrix4f, out_modelTransform);
 }

 return out_modelTransform;
 }

 /**
 * Get the bone's transform, in its local space. That is, relative to its parent bone.
 */
 Matrix4f getBoneTransform(int boneIdx, Matrix4f out_boneTransform) {
 this->m_boneTransforms[boneIdx].getMatrix(out_boneTransform);
 return out_boneTransform;
 }

 Matrix4f getUnweightedModelTransform(AnimationTrack track, int boneIdx, Matrix4f out_modelTransform) {
 Matrix4f matrix4f = AnimationPlayer.L_getUnweightedModelTransform.boneTransform;
 matrix4f.setIdentity();
 out_modelTransform.setIdentity();
 SkinningBone skinningBone0 = this->m_skinningData.getBoneAt(boneIdx);

 for (SkinningBone skinningBone1 = skinningBone0; skinningBone1 != nullptr; skinningBone1 = skinningBone1.Parent) {
 getUnweightedBoneTransform(track, skinningBone1.Index, matrix4f);
 Matrix4f.mul(out_modelTransform, matrix4f, out_modelTransform);
 }

 return out_modelTransform;
 }

 static Matrix4f getUnweightedBoneTransform(AnimationTrack track, int boneIdx, Matrix4f out_boneTransform) {
 Vector3f vector3f0 = AnimationPlayer.L_getUnweightedBoneTransform.pos;
 Quaternion quaternion = AnimationPlayer.L_getUnweightedBoneTransform.rot;
 Vector3f vector3f1 = AnimationPlayer.L_getUnweightedBoneTransform.scale;
 track.get(boneIdx, vector3f0, quaternion, vector3f1);
 HelperFunctions.CreateFromQuaternionPositionScale(vector3f0, quaternion, vector3f1, out_boneTransform);
 return out_boneTransform;
 }

 void UpdateSkinTransforms() {
 this->resetSkinTransforms();
 }

 public Matrix4f[] getSkinTransforms(SkinningData skinningData) {
 if (skinningData == nullptr) {
 return this->modelTransforms;
 } else {
 AnimationPlayer.SkinTransformData skinTransformData = this->getSkinTransformData(skinningData);
 Matrix4f[] matrix4fs = skinTransformData.transforms;
 if (skinTransformData.dirty) {
 for (int int0 = 0; int0 < this->modelTransforms.length; int0++) {
 if (skinningData.BoneOffset != nullptr && skinningData.BoneOffset.get(int0) != nullptr) {
 Matrix4f.mul(skinningData.BoneOffset.get(int0), this->modelTransforms[int0], matrix4fs[int0]);
 } else {
 matrix4fs[int0].setIdentity();
 }
 }

 skinTransformData.dirty = false;
 }

 return matrix4fs;
 }
 }

 void getDeferredMovement(Vector2 out_result) {
 out_result.set(this->m_deferredMovement);
 }

 float getDeferredAngleDelta() {
 return this->m_deferredAngleDelta;
 }

 float getDeferredRotationWeight() {
 return this->m_deferredRotationWeight;
 }

 AnimationMultiTrack getMultiTrack() {
 return this->m_multiTrack;
 }

 void setRecording(bool val) {
 this->m_recorder.setRecording(val);
 }

 void discardRecording() {
 if (this->m_recorder != nullptr) {
 this->m_recorder.discardRecording();
 }
 }

 float getRenderedAngle() {
 return this->m_angle + (float) (Math.PI / 2);
 }

 float getAngle() {
 return this->m_angle;
 }

 void setAngle(float angle) {
 this->m_angle = angle;
 }

 void setAngleToTarget() {
 this->setAngle(this->getTargetAngle());
 }

 void setTargetToAngle() {
 float float0 = this->getAngle();
 this->setTargetAngle(float0);
 }

 float getTargetAngle() {
 return this->m_targetAngle;
 }

 void setTargetAngle(float targetAngle) {
 this->m_targetAngle = targetAngle;
 }

 /**
 * Returns the maximum twist angle, in radians.
 */
 float getMaxTwistAngle() {
 return this->m_maxTwistAngle;
 }

 /**
 * Set the maximum twist angle, in radians
 */
 void setMaxTwistAngle(float radians) {
 this->m_maxTwistAngle = radians;
 }

 float getExcessTwistAngle() {
 return this->m_excessTwist;
 }

 float getTwistAngle() {
 return this->m_twistAngle;
 }

 float getShoulderTwistAngle() {
 return this->m_shoulderTwistAngle;
 }

 /**
 * The lookAt bearing, in radians. The difference between angle and targetAngle. The twist target, not clamped at all. All twists aim for this target, and are clamped by maxTwist.
 */
 float getTargetTwistAngle() {
 return this->m_targetTwistAngle;
 }

 private static class L_applyTwistBone {
 static const Matrix4f twistParentBoneTrans = new Matrix4f();
 static const Matrix4f twistParentBoneTransInv = new Matrix4f();
 static const Matrix4f twistBoneTrans = new Matrix4f();
 static const Quaternion twistBoneRot = new Quaternion();
 static const Quaternion twistBoneTargetRot = new Quaternion();
 static const Matrix4f twistRotDiffTrans = new Matrix4f();
 static const Vector3f twistRotDiffTransAxis = new Vector3f(0.0F, 1.0F, 0.0F);
 static const Matrix4f twistBoneTargetTrans = new Matrix4f();
 static const Quaternion twistBoneNewRot = new Quaternion();
 static const Vector3f twistBonePos = new Vector3f();
 static const Vector3f twistBoneScale = new Vector3f();
 static const Matrix4f twistBoneNewTrans = new Matrix4f();
 }

 private static class L_getBoneModelTransform {
 static const Matrix4f boneTransform = new Matrix4f();
 }

 private static class L_getTrackTransform {
 static const Matrix4f Pa = new Matrix4f();
 static const Matrix4f mA = new Matrix4f();
 static const Matrix4f mB = new Matrix4f();
 static const Matrix4f umA = new Matrix4f();
 static const Matrix4f umB = new Matrix4f();
 static const Matrix4f mAinv = new Matrix4f();
 static const Matrix4f umBinv = new Matrix4f();
 static const Matrix4f result = new Matrix4f();
 }

 private static class L_getUnweightedBoneTransform {
 static const Vector3f pos = new Vector3f();
 static const Quaternion rot = new Quaternion();
 static const Vector3f scale = new Vector3f();
 }

 private static class L_getUnweightedModelTransform {
 static const Matrix4f boneTransform = new Matrix4f();
 }

 private static class L_setTwistBones {
 static ArrayList<String> boneNames = std::make_unique<ArrayList<>>();
 }

 private static class L_updateBoneAnimationTransform {
 static const Quaternion rot = new Quaternion();
 static const Vector3f pos = new Vector3f();
 static const Vector3f scale = new Vector3f();
 static const Keyframe key = new Keyframe(new Vector3f(0.0F, 0.0F, 0.0F), new Quaternion(0.0F, 0.0F, 0.0F, 1.0F), new Vector3f(1.0F, 1.0F, 1.0F);
 static const Matrix4f boneMat = new Matrix4f();
 static const Matrix4f rotMat = new Matrix4f();
 static const Vector3f rotAxis = new Vector3f(1.0F, 0.0F, 0.0F);
 static const Quaternion crRot = new Quaternion();
 static const Vector4f crRotAA = new Vector4f();
 static const Matrix4f crMat = new Matrix4f();
 static const Vector3f rotEulers = new Vector3f();
 static const Vector3f deferredPos = new Vector3f();
 }

 private static class SkinTransformData extends PooledObject {
 public Matrix4f[] transforms;
 SkinningData m_skinnedTo;
 bool dirty;
 private AnimationPlayer.SkinTransformData m_next;
 private static Pool<AnimationPlayer.SkinTransformData> s_pool = new Pool<>(AnimationPlayer.SkinTransformData::new);

 void setSkinnedTo(SkinningData arg0) {
 if (this->m_skinnedTo != arg0) {
 this->dirty = true;
 this->m_skinnedTo = arg0;
 this->transforms = PZArrayUtil.newInstance(Matrix4f.class, this->transforms, arg0.numBones(), Matrix4f::new);
 }
 }

 public static AnimationPlayer.SkinTransformData alloc(SkinningData arg0) {
 AnimationPlayer.SkinTransformData skinTransformData = s_pool.alloc();
 skinTransformData.setSkinnedTo(arg0);
 skinTransformData.dirty = true;
 return skinTransformData;
 }
 }

 private static class updateMultiTrackBoneTransforms_DeferredMovementOnly {
 static int[] boneIndices = new int[60];
 }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
