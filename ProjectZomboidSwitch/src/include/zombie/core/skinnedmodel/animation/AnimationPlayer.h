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
#include "zombie/GameProfiler.h"
#include "zombie/GameTime.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/math/Vector3.h"
#include "zombie/core/skinnedmodel/HelperFunctions.h"
#include "zombie/core/skinnedmodel/advancedanimation/AdvancedAnimator.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer/L_applyTwistBone.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer/L_getBoneModelTransform.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer/L_getTrackTransform.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer/L_getUnweightedBoneTransform.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer/L_getUnweightedModelTransform.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer/L_setTwistBones.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer/L_updateBoneAnimationTransform.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer/SkinTransformData.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer/updateMultiTrackBoneTransforms_DeferredMovementOnly.h"
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
#include "zombie/util/list/PZArrayUtil/Comparators.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationPlayer : public PooledObject {
public:
    Model model;
    const Matrix4f propTransforms = std::make_shared<Matrix4f>();
    bool m_boneTransformsNeedFirstFrame = true;
   private TwistableBoneTransform[] m_boneTransforms;
   public Matrix4f[] modelTransforms;
    SkinTransformData m_skinTransformData = nullptr;
    SkinTransformData m_skinTransformDataPool = nullptr;
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
    const Vector2 m_lastSetDir = std::make_shared<Vector2>();
   private const std::vector<AnimationBoneBindingPair> m_reparentedBoneBindings = std::make_unique<std::vector<>>();
   private const List<AnimationBoneBinding> m_twistBones = std::make_unique<std::vector<>>();
    AnimationBoneBinding m_counterRotationBone = nullptr;
   public const std::vector<int> dismembered = std::make_unique<std::vector<>>();
    const float m_minimumValidAnimWeight = 0.001F;
    const int m_animBlendIndexCacheSize = 32;
   private const int[] m_animBlendIndices = new int[32];
   private const float[] m_animBlendWeights = new float[32];
   private const int[] m_animBlendLayers = new int[32];
   private const int[] m_animBlendPriorities = new int[32];
    const int m_maxLayers = 4;
   private const int[] m_layerBlendCounts = new int[4];
   private const float[] m_layerWeightTotals = new float[4];
    int m_totalAnimBlendCount = 0;
    AnimationPlayer parentPlayer;
    const Vector2 m_deferredMovement = std::make_shared<Vector2>();
    float m_deferredRotationWeight = 0.0F;
    float m_deferredAngleDelta = 0.0F;
    AnimationPlayerRecorder m_recorder = nullptr;
   private static const AnimationTrack[] tempTracks = new AnimationTrack[0];
    static const Vector2 tempo = std::make_shared<Vector2>();
   private static const Pool<AnimationPlayer> s_pool = std::make_shared<Pool>(AnimationPlayer::new);
    const AnimationMultiTrack m_multiTrack = std::make_shared<AnimationMultiTrack>();

    private AnimationPlayer() {
   }

    static AnimationPlayer alloc(Model var0) {
    AnimationPlayer var1 = (AnimationPlayer)s_pool.alloc();
      var1.setModel(var0);
    return var1;
   }

    static float lerpBlendWeight(float var0, float var1, float var2) {
      if (PZMath.equal(var0, var1, 1.0E-4F)) {
    return var1;
      } else {
    float var3 = 1.0F / var2;
    float var4 = GameTime.getInstance().getTimeDelta();
    float var5 = var1 - var0;
    float var6 = PZMath.sign(var5);
    float var7 = var0 + var6 * var3 * var4;
    float var8 = var1 - var7;
    float var9 = PZMath.sign(var8);
         if (var9 != var6) {
            var7 = var1;
         }

    return var7;
      }
   }

    void setModel(Model var1) {
      Objects.requireNonNull(var1);
      if (var1 != this.model) {
         this.model = var1;
         this.initSkinningData();
      }
   }

    Model getModel() {
      return this.model;
   }

    void initSkinningData() {
      if (this.model.isReady()) {
    SkinningData var1 = (SkinningData)this.model.Tag;
         if (var1 != nullptr) {
            if (this.m_skinningData != var1) {
               if (this.m_skinningData != nullptr) {
                  this.m_skinningData = nullptr;
                  this.m_multiTrack.reset();
               }

               this.m_skinningData = var1;
               Lambda.forEachFrom(PZArrayUtil::forEach, this.m_reparentedBoneBindings, this.m_skinningData, AnimationBoneBindingPair::setSkinningData);
               Lambda.forEachFrom(PZArrayUtil::forEach, this.m_twistBones, this.m_skinningData, AnimationBoneBinding::setSkinningData);
               if (this.m_counterRotationBone != nullptr) {
                  this.m_counterRotationBone.setSkinningData(this.m_skinningData);
               }

    int var2 = var1.numBones();
               this.modelTransforms = (Matrix4f[])PZArrayUtil.newInstance(Matrix4f.class, this.modelTransforms, var2, Matrix4f::new);
               this.m_boneTransforms = (TwistableBoneTransform[])PZArrayUtil.newInstance(TwistableBoneTransform.class, this.m_boneTransforms, var2);

               for (int var3 = 0; var3 < var2; var3++) {
                  if (this.m_boneTransforms[var3] == nullptr) {
                     this.m_boneTransforms[var3] = TwistableBoneTransform.alloc();
                  }

                  this.m_boneTransforms[var3].setIdentity();
               }

               this.m_boneTransformsNeedFirstFrame = true;
            }
         }
      }
   }

    bool isReady() {
      this.initSkinningData();
      return this.hasSkinningData();
   }

    bool hasSkinningData() {
      return this.m_skinningData != nullptr;
   }

    void addBoneReparent(const std::string& var1, const std::string& var2) {
      if (!PZArrayUtil.contains(this.m_reparentedBoneBindings, Lambda.predicate(var1, var2, AnimationBoneBindingPair::matches))) {
    AnimationBoneBindingPair var3 = std::make_shared<AnimationBoneBindingPair>(var1, var2);
         var3.setSkinningData(this.m_skinningData);
         this.m_reparentedBoneBindings.push_back(var3);
      }
   }

    void setTwistBones(std::string... var1) {
    std::vector var2 = L_setTwistBones.boneNames;
      PZArrayUtil.listConvert(this.m_twistBones, var2, var0 -> var0.boneName);
      if (!PZArrayUtil.sequenceEqual(var1, var2, Comparators::equalsIgnoreCase)) {
         this.m_twistBones.clear();
         Lambda.forEachFrom(PZArrayUtil::forEach, var1, this, (var0, var1x) -> {
    AnimationBoneBinding var2x = std::make_shared<AnimationBoneBinding>((std::string)var0);
            var2x.setSkinningData(var1x.m_skinningData);
            var1x.m_twistBones.push_back(var2x);
         });
      }
   }

    void setCounterRotationBone(const std::string& var1) {
      if (this.m_counterRotationBone != nullptr && StringUtils == this.m_counterRotationBone.boneName, var1)) {
      }

      this.m_counterRotationBone = std::make_shared<AnimationBoneBinding>(var1);
      this.m_counterRotationBone.setSkinningData(this.m_skinningData);
   }

    AnimationBoneBinding getCounterRotationBone() {
      return this.m_counterRotationBone;
   }

    void reset() {
      this.m_multiTrack.reset();
   }

    void onReleased() {
      this.model = nullptr;
      this.m_skinningData = nullptr;
      this.propTransforms.setIdentity();
      this.m_boneTransformsNeedFirstFrame = true;
      IPooledObject.tryReleaseAndBlank(this.m_boneTransforms);
      PZArrayUtil.forEach(this.modelTransforms, Matrix::setIdentity);
      this.resetSkinTransforms();
      this.setAngle(0.0F);
      this.setTargetAngle(0.0F);
      this.m_twistAngle = 0.0F;
      this.m_shoulderTwistAngle = 0.0F;
      this.m_targetTwistAngle = 0.0F;
      this.m_maxTwistAngle = PZMath.degToRad(70.0F);
      this.m_excessTwist = 0.0F;
      this.angleStepDelta = 1.0F;
      this.angleTwistDelta = 1.0F;
      this.bDoBlending = true;
      this.bUpdateBones = true;
      this.m_lastSetDir.set(0.0F, 0.0F);
      this.m_reparentedBoneBindings.clear();
      this.m_twistBones.clear();
      this.m_counterRotationBone = nullptr;
      this.dismembered.clear();
      Arrays.fill(this.m_animBlendIndices, 0);
      Arrays.fill(this.m_animBlendWeights, 0.0F);
      Arrays.fill(this.m_animBlendLayers, 0);
      Arrays.fill(this.m_layerBlendCounts, 0);
      Arrays.fill(this.m_layerWeightTotals, 0.0F);
      this.m_totalAnimBlendCount = 0;
      this.parentPlayer = nullptr;
      this.m_deferredMovement.set(0.0F, 0.0F);
      this.m_deferredRotationWeight = 0.0F;
      this.m_deferredAngleDelta = 0.0F;
      this.m_recorder = nullptr;
      this.m_multiTrack.reset();
   }

    SkinningData getSkinningData() {
      return this.m_skinningData;
   }

   public std::unordered_map<std::string, int> getSkinningBoneIndices() {
      return this.m_skinningData != nullptr ? this.m_skinningData.BoneIndices : nullptr;
   }

    int getSkinningBoneIndex(const std::string& var1, int var2) {
    std::unordered_map var3 = this.getSkinningBoneIndices();
      return var3 != nullptr ? (int)var3.get(var1) : var2;
   }

   private /* synchronized - TODO: add std::mutex */ SkinTransformData getSkinTransformData(SkinningData var1) {
      for (SkinTransformData var2 = this.m_skinTransformData; var2 != nullptr; var2 = var2.m_next) {
         if (var1 == var2.m_skinnedTo) {
    return var2;
         }
      }

    SkinTransformData var3;
      if (this.m_skinTransformDataPool != nullptr) {
         var3 = this.m_skinTransformDataPool;
         var3.setSkinnedTo(var1);
         var3.dirty = true;
         this.m_skinTransformDataPool = this.m_skinTransformDataPool.m_next;
      } else {
         var3 = SkinTransformData.alloc(var1);
      }

      var3.m_next = this.m_skinTransformData;
      this.m_skinTransformData = var3;
    return var3;
   }

   private /* synchronized - TODO: add std::mutex */ void resetSkinTransforms() {
      GameProfiler.getInstance().invokeAndMeasure("resetSkinTransforms", this, AnimationPlayer::resetSkinTransformsInternal);
   }

    void resetSkinTransformsInternal() {
      if (this.m_skinTransformDataPool != nullptr) {
    SkinTransformData var1 = this.m_skinTransformDataPool;

         while (var1.m_next != nullptr) {
            var1 = var1.m_next;
         }

         var1.m_next = this.m_skinTransformData;
      } else {
         this.m_skinTransformDataPool = this.m_skinTransformData;
      }

      this.m_skinTransformData = nullptr;
   }

    Matrix4f GetPropBoneMatrix(int var1) {
      this.propTransforms.load(this.modelTransforms[var1]);
      return this.propTransforms;
   }

    AnimationTrack startClip(AnimationClip var1, bool var2) {
      if (var1 == nullptr) {
         throw NullPointerException("Supplied clip is nullptr.");
      } else {
    AnimationTrack var3 = AnimationTrack.alloc();
         var3.startClip(var1, var2);
         var3.name = var1.Name;
         var3.IsPlaying = true;
         this.m_multiTrack.addTrack(var3);
    return var3;
      }
   }

    static void releaseTracks(List<AnimationTrack> var0) {
      AnimationTrack[] var1 = var0.toArray(tempTracks);
      PZArrayUtil.forEach(var1, PooledObject::release);
   }

    AnimationTrack play(const std::string& var1, bool var2) {
      if (this.m_skinningData == nullptr) {
    return nullptr;
      } else {
    AnimationClip var3 = (AnimationClip)this.m_skinningData.AnimationClips.get(var1);
         if (var3 == nullptr) {
            DebugLog.General.warn("Anim Clip not found: %s", new Object[]{var1});
    return nullptr;
         } else {
            return this.startClip(var3, var2);
         }
      }
   }

    void Update() {
      this.Update(GameTime.instance.getTimeDelta());
   }

    void Update(float var1) {
      MPStatistic.getInstance().AnimationPlayerUpdate.Start();
      GameProfiler.getInstance().invokeAndMeasure("AnimationPlayer.Update", this, var1, AnimationPlayer::updateInternal);
      MPStatistic.getInstance().AnimationPlayerUpdate.End();
   }

    void updateInternal(float var1) {
      if (this.isReady()) {
         this.m_multiTrack.Update(var1);
         if (!this.bUpdateBones) {
            this.updateAnimation_NonVisualOnly();
         } else if (this.m_multiTrack.getTrackCount() > 0) {
    SharedSkeleAnimationTrack var2 = this.determineCurrentSharedSkeleTrack();
            if (var2 != nullptr) {
    float var3 = this.m_multiTrack.getTrackAt(0).getCurrentTime();
               this.updateAnimation_SharedSkeleTrack(var2, var3);
            } else {
               this.updateAnimation_StandardAnimation();
            }
         }
      }
   }

    SharedSkeleAnimationTrack determineCurrentSharedSkeleTrack() {
      if (this.m_sharedSkeleAnimationRepo == nullptr) {
    return nullptr;
      } else if (this.bDoBlending) {
    return nullptr;
      } else if (!DebugOptions.instance.Animation.SharedSkeles.Enabled.getValue()) {
    return nullptr;
      } else if (this.m_multiTrack.getTrackCount() != 1) {
    return nullptr;
      } else if (!PZMath.equal(this.m_twistAngle, 0.0F, 114.59155F)) {
    return nullptr;
      } else if (this.parentPlayer != nullptr) {
    return nullptr;
      } else {
    AnimationTrack var1 = this.m_multiTrack.getTrackAt(0);
    float var2 = var1.blendFieldWeight;
         if (!PZMath.equal(var2, 0.0F, 0.1F)) {
    return nullptr;
         } else {
    AnimationClip var3 = var1.getClip();
            if (var3 == this.m_currentSharedTrackClip) {
               return this.m_currentSharedTrack;
            } else {
    SharedSkeleAnimationTrack var4 = this.m_sharedSkeleAnimationRepo.getTrack(var3);
               if (var4 == nullptr) {
                  DebugLog.Animation.debugln("Caching SharedSkeleAnimationTrack: %s", var1.name);
                  var4 = std::make_unique<SharedSkeleAnimationTrack>();
    ModelTransformSampler var5 = ModelTransformSampler.alloc(this, var1);

                  try {
                     var4.set(var5, 5.0F);
                  } finally {
                     var5.release();
                  }

                  this.m_sharedSkeleAnimationRepo.setTrack(var3, var4);
               }

               this.m_currentSharedTrackClip = var3;
               this.m_currentSharedTrack = var4;
    return var4;
            }
         }
      }
   }

    void updateAnimation_NonVisualOnly() {
      this.updateMultiTrackBoneTransforms_DeferredMovementOnly();
      this.DoAngles();
      this.calculateDeferredMovement();
   }

    void setSharedAnimRepo(SharedSkeleAnimationRepository var1) {
      this.m_sharedSkeleAnimationRepo = var1;
   }

    void updateAnimation_SharedSkeleTrack(SharedSkeleAnimationTrack var1, float var2) {
      this.updateMultiTrackBoneTransforms_DeferredMovementOnly();
      this.DoAngles();
      this.calculateDeferredMovement();
      var1.moveToTime(var2);

      for (int var3 = 0; var3 < this.modelTransforms.length; var3++) {
         var1.getBoneMatrix(var3, this.modelTransforms[var3]);
      }

      this.UpdateSkinTransforms();
   }

    void updateAnimation_StandardAnimation() {
      if (this.parentPlayer == nullptr) {
         this.updateMultiTrackBoneTransforms();
      } else {
         this.copyBoneTransformsFromParentPlayer();
      }

      this.DoAngles();
      this.calculateDeferredMovement();
      this.updateTwistBone();
      this.applyBoneReParenting();
      this.updateModelTransforms();
      this.UpdateSkinTransforms();
   }

    void copyBoneTransformsFromParentPlayer() {
      this.m_boneTransformsNeedFirstFrame = false;

      for (int var1 = 0; var1 < this.m_boneTransforms.length; var1++) {
         this.m_boneTransforms[var1].set(this.parentPlayer.m_boneTransforms[var1]);
      }
   }

    static float calculateAnimPlayerAngle(Vector2 var0) {
      return var0.getDirection();
   }

    void SetDir(Vector2 var1) {
      if (this.m_lastSetDir.x != var1.x || this.m_lastSetDir.y != var1.y) {
         this.setTargetAngle(calculateAnimPlayerAngle(var1));
         this.m_targetTwistAngle = PZMath.getClosestAngle(this.m_angle, this.m_targetAngle);
    float var2 = PZMath.clamp(this.m_targetTwistAngle, -this.m_maxTwistAngle, this.m_maxTwistAngle);
         this.m_excessTwist = PZMath.getClosestAngle(var2, this.m_targetTwistAngle);
         this.m_lastSetDir.set(var1);
      }
   }

    void SetForceDir(Vector2 var1) {
      this.setTargetAngle(calculateAnimPlayerAngle(var1));
      this.setAngleToTarget();
      this.m_targetTwistAngle = 0.0F;
      this.m_lastSetDir.set(var1);
   }

    void UpdateDir(IsoGameCharacter var1) {
      if (var1 != nullptr) {
         this.SetDir(var1.getForwardDirection());
      }
   }

    void DoAngles() {
      GameProfiler.getInstance().invokeAndMeasure("AnimationPlayer.doAngles", this, AnimationPlayer::doAnglesInternal);
   }

    void doAnglesInternal() {
    float var1 = 0.15F * GameTime.instance.getMultiplier();
      this.interpolateBodyAngle(var1);
      this.interpolateBodyTwist(var1);
      this.interpolateShoulderTwist(var1);
   }

    void interpolateBodyAngle(float var1) {
    float var2 = PZMath.getClosestAngle(this.m_angle, this.m_targetAngle);
      if (PZMath.equal(var2, 0.0F, 0.001F)) {
         this.setAngleToTarget();
         this.m_targetTwistAngle = 0.0F;
      } else {
    float var3 = PZMath.sign(var2);
    float var4 = var1 * var3 * this.angleStepDelta;
    float var5;
         if (DebugOptions.instance.char.Debug.Animate.DeferredRotationOnly.getValue()) {
            var5 = this.m_deferredAngleDelta;
         } else if (this.m_deferredRotationWeight > 0.0F) {
            var5 = this.m_deferredAngleDelta;
         } else {
            var5 = var4;
         }

    float var6 = PZMath.sign(var5);
    float var7 = this.m_angle;
    float var8 = var7 + var5;
    float var9 = PZMath.getClosestAngle(var8, this.m_targetAngle);
    float var10 = PZMath.sign(var9);
         if (var10 != var3 && var6 == var3) {
            this.setAngleToTarget();
            this.m_targetTwistAngle = 0.0F;
         } else {
            this.setAngle(var8);
            this.m_targetTwistAngle = var9;
         }
      }
   }

    void interpolateBodyTwist(float var1) {
    float var2 = PZMath.wrap(this.m_targetTwistAngle, (float) -Math.PI, (float) Math.PI);
    float var3 = PZMath.clamp(var2, -this.m_maxTwistAngle, this.m_maxTwistAngle);
      this.m_excessTwist = PZMath.getClosestAngle(var3, var2);
    float var4 = PZMath.getClosestAngle(this.m_twistAngle, var3);
      if (PZMath.equal(var4, 0.0F, 0.001F)) {
         this.m_twistAngle = var3;
      } else {
    float var5 = PZMath.sign(var4);
    float var6 = var1 * var5 * this.angleTwistDelta;
    float var7 = this.m_twistAngle;
    float var8 = var7 + var6;
    float var9 = PZMath.getClosestAngle(var8, var3);
    float var10 = PZMath.sign(var9);
         if (var10 == var5) {
            this.m_twistAngle = var8;
         } else {
            this.m_twistAngle = var3;
         }
      }
   }

    void interpolateShoulderTwist(float var1) {
    float var2 = PZMath.wrap(this.m_twistAngle, (float) -Math.PI, (float) Math.PI);
    float var3 = PZMath.getClosestAngle(this.m_shoulderTwistAngle, var2);
      if (PZMath.equal(var3, 0.0F, 0.001F)) {
         this.m_shoulderTwistAngle = var2;
      } else {
    float var4 = PZMath.sign(var3);
    float var5 = var1 * var4 * this.angleTwistDelta * 0.55F;
    float var6 = this.m_shoulderTwistAngle;
    float var7 = var6 + var5;
    float var8 = PZMath.getClosestAngle(var7, var2);
    float var9 = PZMath.sign(var8);
         if (var9 == var4) {
            this.m_shoulderTwistAngle = var7;
         } else {
            this.m_shoulderTwistAngle = var2;
         }
      }
   }

    void updateTwistBone() {
      GameProfiler.getInstance().invokeAndMeasure("updateTwistBone", this, AnimationPlayer::updateTwistBoneInternal);
   }

    void updateTwistBoneInternal() {
      if (!this.m_twistBones.empty()) {
    float var1 = PZMath.degToRad(1.0F);
         if (!PZMath.equal(this.m_twistAngle, 0.0F, var1)) {
            if (!DebugOptions.instance.char.Debug.Animate.NoBoneTwists.getValue()) {
    int var2 = this.m_twistBones.size();
    int var3 = var2 - 1;
    float var4 = -this.m_shoulderTwistAngle;
    float var5 = var4 / var3;

               for (int var6 = 0; var6 < var3; var6++) {
    SkinningBone var7 = this.m_twistBones.get(var6).getBone();
                  this.applyTwistBone(var7, var5);
               }

    float var9 = -this.m_twistAngle;
    float var10 = PZMath.getClosestAngle(var4, var9);
               if (PZMath.abs(var10) > 1.0E-4F) {
    SkinningBone var8 = this.m_twistBones.get(var3).getBone();
                  this.applyTwistBone(var8, var10);
               }
            }
         }
      }
   }

    void applyTwistBone(SkinningBone var1, float var2) {
      if (var1 != nullptr) {
    int var3 = var1.Index;
    int var4 = var1.Parent.Index;
    Matrix4f var5 = this.getBoneModelTransform(var4, L_applyTwistBone.twistParentBoneTrans);
    Matrix4f var6 = Matrix4f.invert(var5, L_applyTwistBone.twistParentBoneTransInv);
         if (var6 != nullptr) {
    Matrix4f var7 = this.getBoneModelTransform(var3, L_applyTwistBone.twistBoneTrans);
    Quaternion var8 = L_applyTwistBone.twistBoneTargetRot;
    Matrix4f var9 = L_applyTwistBone.twistRotDiffTrans;
            var9.setIdentity();
            L_applyTwistBone.twistRotDiffTransAxis.set(0.0F, 1.0F, 0.0F);
    float var10 = PZMath.getClosestAngle(this.m_boneTransforms[var3].Twist, var2);
            this.m_boneTransforms[var3].Twist = var2;
            var9.rotate(var10, L_applyTwistBone.twistRotDiffTransAxis);
    Matrix4f var11 = L_applyTwistBone.twistBoneTargetTrans;
            Matrix4f.mul(var7, var9, var11);
            HelperFunctions.getRotation(var11, var8);
    Quaternion var13 = L_applyTwistBone.twistBoneNewRot;
            var13.set(var8);
    Vector3f var14 = HelperFunctions.getPosition(var7, L_applyTwistBone.twistBonePos);
    Vector3f var15 = L_applyTwistBone.twistBoneScale;
            var15.set(1.0F, 1.0F, 1.0F);
    Matrix4f var12 = L_applyTwistBone.twistBoneNewTrans;
            HelperFunctions.CreateFromQuaternionPositionScale(var14, var13, var15, var12);
            this.m_boneTransforms[var3].mul(var12, var6);
         }
      }
   }

    void resetBoneModelTransforms() {
      if (this.m_skinningData != nullptr && this.modelTransforms != nullptr) {
         this.m_boneTransformsNeedFirstFrame = true;
    int var1 = this.m_boneTransforms.length;

         for (int var2 = 0; var2 < var1; var2++) {
            this.m_boneTransforms[var2].BlendWeight = 0.0F;
            this.m_boneTransforms[var2].setIdentity();
            this.modelTransforms[var2].setIdentity();
         }
      }
   }

    bool isBoneTransformsNeedFirstFrame() {
      return this.m_boneTransformsNeedFirstFrame;
   }

    void updateMultiTrackBoneTransforms() {
      GameProfiler.getInstance().invokeAndMeasure("updateMultiTrackBoneTransforms", this, AnimationPlayer::updateMultiTrackBoneTransformsInternal);
   }

    void updateMultiTrackBoneTransformsInternal() {
      for (int var1 = 0; var1 < this.modelTransforms.length; var1++) {
         this.modelTransforms[var1].setIdentity();
      }

      this.updateLayerBlendWeightings();
      if (this.m_totalAnimBlendCount != 0) {
         if (this.isRecording()) {
            this.m_recorder.logAnimWeights(this.m_multiTrack.getTracks(), this.m_animBlendIndices, this.m_animBlendWeights, this.m_deferredMovement);
         }

         for (int var2 = 0; var2 < this.m_boneTransforms.length; var2++) {
            if (!this.isBoneReparented(var2)) {
               this.updateBoneAnimationTransform(var2, nullptr);
            }
         }

         this.m_boneTransformsNeedFirstFrame = false;
      }
   }

    void updateLayerBlendWeightings() {
    std::vector var1 = this.m_multiTrack.getTracks();
    int var2 = var1.size();
      PZArrayUtil.arraySet(this.m_animBlendIndices, -1);
      PZArrayUtil.arraySet(this.m_animBlendWeights, 0.0F);
      PZArrayUtil.arraySet(this.m_animBlendLayers, -1);
      PZArrayUtil.arraySet(this.m_animBlendPriorities, 0);

      for (int var3 = 0; var3 < var2; var3++) {
    AnimationTrack var4 = (AnimationTrack)var1.get(var3);
    float var5 = var4.BlendDelta;
    int var6 = var4.getLayerIdx();
    int var7 = var4.getPriority();
         if (var6 >= 0 && var6 < 4) {
            if (!(var5 < 0.001F) && (var6 <= 0 || !var4.isFinished())) {
    int var8 = -1;

               for (int var9 = 0; var9 < this.m_animBlendIndices.length; var9++) {
                  if (this.m_animBlendIndices[var9] == -1) {
                     var8 = var9;
                     break;
                  }

                  if (var6 <= this.m_animBlendLayers[var9]) {
                     if (var6 < this.m_animBlendLayers[var9]) {
                        var8 = var9;
                        break;
                     }

                     if (var7 <= this.m_animBlendPriorities[var9]) {
                        if (var7 < this.m_animBlendPriorities[var9]) {
                           var8 = var9;
                           break;
                        }

                        if (var5 < this.m_animBlendWeights[var9]) {
                           var8 = var9;
                           break;
                        }
                     }
                  }
               }

               if (var8 < 0) {
                  DebugLog.General
                     .error(
                        "Buffer overflow. Insufficient anim blends in cache. More than %d animations are being blended at once. Will be truncated to %d.",
                        new Object[]{this.m_animBlendIndices.length, this.m_animBlendIndices.length}
                     );
               } else {
                  PZArrayUtil.insertAt(this.m_animBlendIndices, var8, var3);
                  PZArrayUtil.insertAt(this.m_animBlendWeights, var8, var5);
                  PZArrayUtil.insertAt(this.m_animBlendLayers, var8, var6);
                  PZArrayUtil.insertAt(this.m_animBlendPriorities, var8, var7);
               }
            }
         } else {
            DebugLog.General.error("Layer index is out of range: %d. Range: 0 - %d", new Object[]{var6, 3});
         }
      }

      PZArrayUtil.arraySet(this.m_layerBlendCounts, 0);
      PZArrayUtil.arraySet(this.m_layerWeightTotals, 0.0F);
      this.m_totalAnimBlendCount = 0;

      for (int var10 = 0; var10 < this.m_animBlendIndices.length && this.m_animBlendIndices[var10] >= 0; var10++) {
    int var12 = this.m_animBlendLayers[var10];
         this.m_layerWeightTotals[var12] = this.m_layerWeightTotals[var12] + this.m_animBlendWeights[var10];
         this.m_layerBlendCounts[var12]++;
         this.m_totalAnimBlendCount++;
      }

      if (this.m_totalAnimBlendCount != 0) {
         if (this.m_boneTransformsNeedFirstFrame) {
    int var11 = this.m_animBlendLayers[0];
    int var13 = this.m_layerBlendCounts[0];
    float var14 = this.m_layerWeightTotals[0];
            if (var14 < 1.0F) {
               for (int var15 = 0; var15 < this.m_totalAnimBlendCount; var15++) {
    int var16 = this.m_animBlendLayers[var15];
                  if (var16 != var11) {
                     break;
                  }

                  if (var14 > 0.0F) {
                     this.m_animBlendWeights[var15] = this.m_animBlendWeights[var15] / var14;
                  } else {
                     this.m_animBlendWeights[var15] = 1.0F / var13;
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
    std::vector var1 = this.m_multiTrack.getTracks();
      this.m_deferredMovement.set(0.0F, 0.0F);
      this.m_deferredAngleDelta = 0.0F;
      this.m_deferredRotationWeight = 0.0F;
    float var2 = 1.0F;

      for (int var3 = this.m_totalAnimBlendCount - 1; var3 >= 0 && !(var2 <= 0.001F); var3--) {
    int var4 = this.m_animBlendIndices[var3];
    AnimationTrack var5 = (AnimationTrack)var1.get(var4);
         if (!var5.isFinished()) {
    float var6 = var5.getDeferredBoneWeight();
            if (!(var6 <= 0.001F)) {
    float var7 = this.m_animBlendWeights[var3] * var6;
               if (!(var7 <= 0.001F)) {
    float var8 = PZMath.clamp(var7, 0.0F, var2);
                  var2 -= var7;
                  var2 = org.joml.Math.max(0.0F, var2);
                  Vector2.addScaled(this.m_deferredMovement, var5.getDeferredMovementDiff(tempo), var8, this.m_deferredMovement);
                  if (var5.getUseDeferredRotation()) {
                     this.m_deferredAngleDelta = this.m_deferredAngleDelta + var5.getDeferredRotationDiff() * var8;
                     this.m_deferredRotationWeight += var8;
                  }
               }
            }
         }
      }

      this.applyRotationToDeferredMovement(this.m_deferredMovement);
      this.m_deferredMovement.x = this.m_deferredMovement.x * AdvancedAnimator.s_MotionScale;
      this.m_deferredMovement.y = this.m_deferredMovement.y * AdvancedAnimator.s_MotionScale;
      this.m_deferredAngleDelta = this.m_deferredAngleDelta * AdvancedAnimator.s_RotationScale;
   }

    void applyRotationToDeferredMovement(Vector2 var1) {
    float var2 = var1.normalize();
    float var3 = this.getRenderedAngle();
      var1.rotate(var3);
      var1.setLength(-var2);
   }

    void applyBoneReParenting() {
      GameProfiler.getInstance().invokeAndMeasure("applyBoneReParenting", this, AnimationPlayer::applyBoneReParentingInternal);
   }

    void applyBoneReParentingInternal() {
    int var1 = 0;

      for (int var2 = this.m_reparentedBoneBindings.size(); var1 < var2; var1++) {
    AnimationBoneBindingPair var3 = this.m_reparentedBoneBindings.get(var1);
         if (!var3.isValid()) {
            DebugLog.Animation.warn("Animation binding pair is not valid: %s", new Object[]{var3});
         } else {
            this.updateBoneAnimationTransform(var3.getBoneIdxA(), var3);
         }
      }
   }

    void updateBoneAnimationTransform(int var1, AnimationBoneBindingPair var2) {
      this.updateBoneAnimationTransform_Internal(var1, var2);
   }

    void updateBoneAnimationTransform_Internal(int var1, AnimationBoneBindingPair var2) {
    std::vector var3 = this.m_multiTrack.getTracks();
    Vector3f var4 = L_updateBoneAnimationTransform.pos;
    Quaternion var5 = L_updateBoneAnimationTransform.rot;
    Vector3f var6 = L_updateBoneAnimationTransform.scale;
    Keyframe var7 = L_updateBoneAnimationTransform.key;
    int var8 = this.m_totalAnimBlendCount;
    AnimationBoneBinding var9 = this.m_counterRotationBone;
    bool var10 = var9 != nullptr && var9.getBone() != nullptr && var9.getBone().Index == var1;
      var7.setIdentity();
    float var11 = 0.0F;
    bool var12 = true;
    float var13 = 1.0F;

      for (int var14 = var8 - 1; var14 >= 0 && var13 > 0.0F && !(var13 <= 0.001F); var14--) {
    int var15 = this.m_animBlendIndices[var14];
    AnimationTrack var16 = (AnimationTrack)var3.get(var15);
    float var17 = var16.getBoneWeight(var1);
         if (!(var17 <= 0.001F)) {
    float var18 = this.m_animBlendWeights[var14] * var17;
            if (!(var18 <= 0.001F)) {
    float var19 = PZMath.clamp(var18, 0.0F, var13);
               var13 -= var18;
               var13 = org.joml.Math.max(0.0F, var13);
               this.getTrackTransform(var1, var16, var2, var4, var5, var6);
               if (var10 && var16.getUseDeferredRotation()) {
                  if (DebugOptions.instance.char.Debug.Animate.ZeroCounterRotationBone.getValue()) {
    Vector3f var20 = L_updateBoneAnimationTransform.rotAxis;
    Matrix4f var21 = L_updateBoneAnimationTransform.rotMat;
                     var21.setIdentity();
                     var20.set(0.0F, 1.0F, 0.0F);
                     var21.rotate((float) (-Math.PI / 2), var20);
                     var20.set(1.0F, 0.0F, 0.0F);
                     var21.rotate((float) (-Math.PI / 2), var20);
                     HelperFunctions.getRotation(var21, var5);
                  } else {
    Vector3f var23 = HelperFunctions.ToEulerAngles(var5, L_updateBoneAnimationTransform.rotEulers);
                     HelperFunctions.ToQuaternion(var23.x, var23.y, (float) (Math.PI / 2), var5);
                  }
               }

    bool var24 = var16.getDeferredMovementBoneIdx() == var1;
               if (var24) {
    Vector3f var25 = var16.getCurrentDeferredCounterPosition(L_updateBoneAnimationTransform.deferredPos);
                  var4.x = var4.x + var25.x;
                  var4.y = var4.y + var25.y;
                  var4.z = var4.z + var25.z;
               }

               if (var12) {
                  Vector3.setScaled(var4, var19, var7.Position);
                  var7.Rotation.set(var5);
                  var11 = var19;
                  var12 = false;
               } else {
    float var26 = var19 / (var19 + var11);
                  var11 += var19;
                  Vector3.addScaled(var7.Position, var4, var19, var7.Position);
                  PZMath.slerp(var7.Rotation, var7.Rotation, var5, var26);
               }
            }
         }
      }

      if (var13 > 0.0F && !this.m_boneTransformsNeedFirstFrame) {
         this.m_boneTransforms[var1].getPRS(var4, var5, var6);
         Vector3.addScaled(var7.Position, var4, var13, var7.Position);
         PZMath.slerp(var7.Rotation, var5, var7.Rotation, var11);
         PZMath.lerp(var7.Scale, var6, var7.Scale, var11);
      }

      this.m_boneTransforms[var1].set(var7.Position, var7.Rotation, var7.Scale);
      this.m_boneTransforms[var1].BlendWeight = var11;
      this.m_boneTransforms[var1].Twist *= 1.0F - var11;
   }

    void getTrackTransform(int var1, AnimationTrack var2, AnimationBoneBindingPair var3, Vector3f var4, Quaternion var5, Vector3f var6) {
      if (var3 == nullptr) {
         var2.get(var1, var4, var5, var6);
      } else {
    Matrix4f var7 = L_getTrackTransform.result;
    SkinningBone var8 = var3.getBoneA();
    Matrix4f var9 = getUnweightedBoneTransform(var2, var8.Index, L_getTrackTransform.Pa);
    SkinningBone var10 = var8.Parent;
    SkinningBone var11 = var3.getBoneB();
    Matrix4f var12 = this.getBoneModelTransform(var10.Index, L_getTrackTransform.mA);
    Matrix4f var13 = Matrix4f.invert(var12, L_getTrackTransform.mAinv);
    Matrix4f var14 = this.getBoneModelTransform(var11.Index, L_getTrackTransform.mB);
    Matrix4f var15 = this.getUnweightedModelTransform(var2, var10.Index, L_getTrackTransform.umA);
    Matrix4f var16 = this.getUnweightedModelTransform(var2, var11.Index, L_getTrackTransform.umB);
    Matrix4f var17 = Matrix4f.invert(var16, L_getTrackTransform.umBinv);
         Matrix4f.mul(var9, var15, var7);
         Matrix4f.mul(var7, var17, var7);
         Matrix4f.mul(var7, var14, var7);
         Matrix4f.mul(var7, var13, var7);
         HelperFunctions.getPosition(var7, var4);
         HelperFunctions.getRotation(var7, var5);
         var6.set(1.0F, 1.0F, 1.0F);
      }
   }

    bool isBoneReparented(int var1) {
      return PZArrayUtil.contains(this.m_reparentedBoneBindings, Lambda.predicate(var1, (var0, var1x) -> var0.getBoneIdxA() == var1x));
   }

    void updateMultiTrackBoneTransforms_DeferredMovementOnly() {
      this.m_deferredMovement.set(0.0F, 0.0F);
      if (this.parentPlayer == nullptr) {
         this.updateLayerBlendWeightings();
         if (this.m_totalAnimBlendCount != 0) {
            int[] var1 = updateMultiTrackBoneTransforms_DeferredMovementOnly.boneIndices;
    int var2 = 0;
    std::vector var3 = this.m_multiTrack.getTracks();
    int var4 = var3.size();

            for (int var5 = 0; var5 < var4; var5++) {
    AnimationTrack var6 = (AnimationTrack)var3.get(var5);
    int var7 = var6.getDeferredMovementBoneIdx();
               if (var7 != -1 && !PZArrayUtil.contains(var1, var2, var7)) {
                  var1[var2++] = var7;
               }
            }

            for (int var8 = 0; var8 < var2; var8++) {
               this.updateBoneAnimationTransform(var1[var8], nullptr);
            }
         }
      }
   }

    bool isRecording() {
      return this.m_recorder != nullptr && this.m_recorder.isRecording();
   }

    void setRecorder(AnimationPlayerRecorder var1) {
      this.m_recorder = var1;
   }

    AnimationPlayerRecorder getRecorder() {
      return this.m_recorder;
   }

    void dismember(int var1) {
      this.dismembered.push_back(var1);
   }

    void updateModelTransforms() {
      GameProfiler.getInstance().invokeAndMeasure("updateModelTransforms", this, AnimationPlayer::updateModelTransformsInternal);
   }

    void updateModelTransformsInternal() {
      this.m_boneTransforms[0].getMatrix(this.modelTransforms[0]);

      for (int var1 = 1; var1 < this.modelTransforms.length; var1++) {
    SkinningBone var2 = this.m_skinningData.getBoneAt(var1);
    SkinningBone var3 = var2.Parent;
         BoneTransform.mul(this.m_boneTransforms[var2.Index], this.modelTransforms[var3.Index], this.modelTransforms[var2.Index]);
      }
   }

    Matrix4f getBoneModelTransform(int var1, Matrix4f var2) {
    Matrix4f var3 = L_getBoneModelTransform.boneTransform;
      var2.setIdentity();
    SkinningBone var4 = this.m_skinningData.getBoneAt(var1);

      for (SkinningBone var5 = var4; var5 != nullptr; var5 = var5.Parent) {
         this.getBoneTransform(var5.Index, var3);
         Matrix4f.mul(var2, var3, var2);
      }

    return var2;
   }

    Matrix4f getBoneTransform(int var1, Matrix4f var2) {
      this.m_boneTransforms[var1].getMatrix(var2);
    return var2;
   }

    Matrix4f getUnweightedModelTransform(AnimationTrack var1, int var2, Matrix4f var3) {
    Matrix4f var4 = L_getUnweightedModelTransform.boneTransform;
      var4.setIdentity();
      var3.setIdentity();
    SkinningBone var5 = this.m_skinningData.getBoneAt(var2);

      for (SkinningBone var6 = var5; var6 != nullptr; var6 = var6.Parent) {
         getUnweightedBoneTransform(var1, var6.Index, var4);
         Matrix4f.mul(var3, var4, var3);
      }

    return var3;
   }

    static Matrix4f getUnweightedBoneTransform(AnimationTrack var0, int var1, Matrix4f var2) {
    Vector3f var3 = L_getUnweightedBoneTransform.pos;
    Quaternion var4 = L_getUnweightedBoneTransform.rot;
    Vector3f var5 = L_getUnweightedBoneTransform.scale;
      var0.get(var1, var3, var4, var5);
      HelperFunctions.CreateFromQuaternionPositionScale(var3, var4, var5, var2);
    return var2;
   }

    void UpdateSkinTransforms() {
      this.resetSkinTransforms();
   }

   public Matrix4f[] getSkinTransforms(SkinningData var1) {
      if (var1 == nullptr) {
         return this.modelTransforms;
      } else {
    SkinTransformData var2 = this.getSkinTransformData(var1);
         Matrix4f[] var3 = var2.transforms;
         if (var2.dirty) {
            for (int var4 = 0; var4 < this.modelTransforms.length; var4++) {
               if (var1.BoneOffset != nullptr && var1.BoneOffset.get(var4) != nullptr) {
                  Matrix4f.mul((Matrix4f)var1.BoneOffset.get(var4), this.modelTransforms[var4], var3[var4]);
               } else {
                  var3[var4].setIdentity();
               }
            }

            var2.dirty = false;
         }

    return var3;
      }
   }

    void getDeferredMovement(Vector2 var1) {
      var1.set(this.m_deferredMovement);
   }

    float getDeferredAngleDelta() {
      return this.m_deferredAngleDelta;
   }

    float getDeferredRotationWeight() {
      return this.m_deferredRotationWeight;
   }

    AnimationMultiTrack getMultiTrack() {
      return this.m_multiTrack;
   }

    void setRecording(bool var1) {
      this.m_recorder.setRecording(var1);
   }

    void discardRecording() {
      if (this.m_recorder != nullptr) {
         this.m_recorder.discardRecording();
      }
   }

    float getRenderedAngle() {
      return this.m_angle + (float) (Math.PI / 2);
   }

    float getAngle() {
      return this.m_angle;
   }

    void setAngle(float var1) {
      this.m_angle = var1;
   }

    void setAngleToTarget() {
      this.setAngle(this.getTargetAngle());
   }

    void setTargetToAngle() {
    float var1 = this.getAngle();
      this.setTargetAngle(var1);
   }

    float getTargetAngle() {
      return this.m_targetAngle;
   }

    void setTargetAngle(float var1) {
      this.m_targetAngle = var1;
   }

    float getMaxTwistAngle() {
      return this.m_maxTwistAngle;
   }

    void setMaxTwistAngle(float var1) {
      this.m_maxTwistAngle = var1;
   }

    float getExcessTwistAngle() {
      return this.m_excessTwist;
   }

    float getTwistAngle() {
      return this.m_twistAngle;
   }

    float getShoulderTwistAngle() {
      return this.m_shoulderTwistAngle;
   }

    float getTargetTwistAngle() {
      return this.m_targetTwistAngle;
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
