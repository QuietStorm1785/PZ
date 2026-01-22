#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/HelperFunctions.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimBoneWeight.h"
#include "zombie/core/skinnedmodel/advancedanimation/PooledAnimBoneWeightArray.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack/DeferredMotionData.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack/KeyframeSpan.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack/L_updateDeferredValues.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack/s_performance.h"
#include "zombie/core/skinnedmodel/model/SkinningBone.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledArrayObject.h"
#include "zombie/util/PooledFloatArrayObject.h"
#include "zombie/util/PooledObject.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/lambda/Consumers/Params1/ICallback.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationTrack : public PooledObject {
public:
    bool IsPlaying;
    AnimationClip CurrentClip;
    int priority;
    float currentTimeValue;
    float previousTimeValue;
    bool SyncTrackingEnabled;
    bool reverse;
    bool bLooping;
   private const KeyframeSpan[] m_pose = new KeyframeSpan[60];
    const KeyframeSpan m_deferredPoseSpan = std::make_shared<KeyframeSpan>();
    float SpeedDelta;
    float BlendDelta;
    float blendFieldWeight;
    std::string name;
    float earlyBlendOutTime;
    bool triggerOnNonLoopedAnimFadeOutEvent;
    int m_layerIdx;
   private PooledArrayObject<AnimBoneWeight> m_boneWeightBindings;
    PooledFloatArrayObject m_boneWeights;
   private const std::vector<IAnimListener> listeners = std::make_unique<std::vector<>>();
   private const std::vector<IAnimListener> listenersInvoking = std::make_unique<std::vector<>>();
    SkinningBone m_deferredBone;
    BoneAxis m_deferredBoneAxis;
    bool m_useDeferredRotation;
    const DeferredMotionData m_deferredMotion = std::make_shared<DeferredMotionData>();
   private static const Pool<AnimationTrack> s_pool = std::make_shared<Pool>(AnimationTrack::new);

    static AnimationTrack alloc() {
      return (AnimationTrack)s_pool.alloc();
   }

    protected AnimationTrack() {
      PZArrayUtil.arrayPopulate(this.m_pose, KeyframeSpan::new);
      this.resetInternal();
   }

    AnimationTrack resetInternal() {
      this.IsPlaying = false;
      this.CurrentClip = nullptr;
      this.priority = 0;
      this.currentTimeValue = 0.0F;
      this.previousTimeValue = 0.0F;
      this.SyncTrackingEnabled = true;
      this.reverse = false;
      this.bLooping = false;
      PZArrayUtil.forEach(this.m_pose, KeyframeSpan::clear);
      this.m_deferredPoseSpan.clear();
      this.SpeedDelta = 1.0F;
      this.BlendDelta = 0.0F;
      this.blendFieldWeight = 0.0F;
      this.name = "!Empty!";
      this.earlyBlendOutTime = 0.0F;
      this.triggerOnNonLoopedAnimFadeOutEvent = false;
      this.m_layerIdx = -1;
      Pool.tryRelease(this.m_boneWeightBindings);
      this.m_boneWeightBindings = nullptr;
      Pool.tryRelease(this.m_boneWeights);
      this.m_boneWeights = nullptr;
      this.listeners.clear();
      this.listenersInvoking.clear();
      this.m_deferredBone = nullptr;
      this.m_deferredBoneAxis = BoneAxis.Y;
      this.m_useDeferredRotation = false;
      this.m_deferredMotion.reset();
    return this;
   }

    void get(int var1, Vector3f var2, Quaternion var3, Vector3f var4) {
      this.m_pose[var1].lerp(this.getCurrentTime(), var2, var3, var4);
   }

    Keyframe getDeferredMovementFrameAt(int var1, float var2, Keyframe var3) {
    KeyframeSpan var4 = this.getKeyframeSpan(var1, var2, this.m_deferredPoseSpan);
      return var4.lerp(var2, var3);
   }

    KeyframeSpan getKeyframeSpan(int var1, float var2, KeyframeSpan var3) {
      if (!var3.isBone(var1)) {
         var3.clear();
      }

      Keyframe[] var4 = this.CurrentClip.getBoneFramesAt(var1);
      if (var4.length == 0) {
         var3.clear();
    return var3;
      } else if (var3.containsTime(var2)) {
    return var3;
      } else {
    Keyframe var5 = var4[var4.length - 1];
         if (var2 >= var5.Time) {
            var3.fromIdx = var4.length - 2;
            var3.toIdx = var4.length - 1;
            var3.from = var4[var3.fromIdx];
            var3.to = var4[var3.toIdx];
    return var3;
         } else {
    Keyframe var6 = var4[0];
            if (var2 <= var6.Time) {
               var3.clear();
               var3.toIdx = 0;
               var3.to = var6;
    return var3;
            } else {
    int var7 = 0;
               if (var3.isSpan() && var3.to.Time <= var2) {
                  var7 = var3.toIdx;
               }

               var3.clear();

               for (int var8 = var7; var8 < var4.length - 1; var8++) {
    Keyframe var9 = var4[var8];
    Keyframe var10 = var4[var8 + 1];
                  if (var9.Time <= var2 && var2 <= var10.Time) {
                     var3.fromIdx = var8;
                     var3.toIdx = var8 + 1;
                     var3.from = var9;
                     var3.to = var10;
                     break;
                  }
               }

    return var3;
            }
         }
      }
   }

    void removeListener(IAnimListener var1) {
      this.listeners.remove(var1);
   }

    void Update(float var1) {
      try {
         this.UpdateKeyframes(var1);
      } catch (Exception var3) {
         var3.printStackTrace();
      }
   }

    void UpdateKeyframes(float var1) {
      s_performance.updateKeyframes.invokeAndMeasure(this, var1, AnimationTrack::updateKeyframesInternal);
   }

    void updateKeyframesInternal(float var1) {
      if (this.CurrentClip == nullptr) {
         throw RuntimeException("AnimationPlayer.Update was called before startClip");
      } else {
         if (var1 > 0.0F) {
            this.TickCurrentTime(var1);
         }

         if (!GameServer.bServer || ServerGUI.isCreated()) {
            this.updatePose();
         }

         this.updateDeferredValues();
      }
   }

    void updatePose() {
      s_performance.updatePose.invokeAndMeasure(this, AnimationTrack::updatePoseInternal);
   }

    void updatePoseInternal() {
    float var1 = this.getCurrentTime();

      for (int var2 = 0; var2 < 60; var2++) {
         this.getKeyframeSpan(var2, var1, this.m_pose[var2]);
      }
   }

    void updateDeferredValues() {
      s_performance.updateDeferredValues.invokeAndMeasure(this, AnimationTrack::updateDeferredValuesInternal);
   }

    void updateDeferredValuesInternal() {
      if (this.m_deferredBone != nullptr) {
    DeferredMotionData var1 = this.m_deferredMotion;
         var1.m_deferredRotationDiff = 0.0F;
         var1.m_deferredMovementDiff.set(0.0F, 0.0F);
         var1.m_counterRotatedMovementDiff.set(0.0F, 0.0F);
    float var2 = this.getReversibleTimeValue(this.previousTimeValue);
    float var3 = this.getReversibleTimeValue(this.currentTimeValue);
         if (this.isLooping() && var2 > var3) {
    float var4 = this.getDuration();
            this.appendDeferredValues(var1, var2, var4);
            var2 = 0.0F;
         }

         this.appendDeferredValues(var1, var2, var3);
      }
   }

    void appendDeferredValues(DeferredMotionData var1, float var2, float var3) {
    Keyframe var4 = this.getDeferredMovementFrameAt(this.m_deferredBone.Index, var2, L_updateDeferredValues.prevKeyFrame);
    Keyframe var5 = this.getDeferredMovementFrameAt(this.m_deferredBone.Index, var3, L_updateDeferredValues.keyFrame);
      if (!GameServer.bServer) {
         var1.m_prevDeferredRotation = this.getDeferredTwistRotation(var4.Rotation);
         var1.m_targetDeferredRotationQ.set(var5.Rotation);
         var1.m_targetDeferredRotation = this.getDeferredTwistRotation(var5.Rotation);
    float var6 = PZMath.getClosestAngle(var1.m_prevDeferredRotation, var1.m_targetDeferredRotation);
         var1.m_deferredRotationDiff += var6;
      }

      this.getDeferredMovement(var4.Position, var1.m_prevDeferredMovement);
      var1.m_targetDeferredPosition.set(var5.Position);
      this.getDeferredMovement(var5.Position, var1.m_targetDeferredMovement);
      Vector2 var9 = L_updateDeferredValues.diff
         .set(var1.m_targetDeferredMovement.x - var1.m_prevDeferredMovement.x, var1.m_targetDeferredMovement.y - var1.m_prevDeferredMovement.y);
    Vector2 var7 = L_updateDeferredValues.crDiff.set(var9);
      if (this.getUseDeferredRotation()) {
    float var8 = var7.normalize();
         var7.rotate(-(var1.m_targetDeferredRotation + (float) (Math.PI / 2)));
         var7.scale(-var8);
      }

      var1.m_deferredMovementDiff.x = var1.m_deferredMovementDiff.x + var9.x;
      var1.m_deferredMovementDiff.y = var1.m_deferredMovementDiff.y + var9.y;
      var1.m_counterRotatedMovementDiff.x = var1.m_counterRotatedMovementDiff.x + var7.x;
      var1.m_counterRotatedMovementDiff.y = var1.m_counterRotatedMovementDiff.y + var7.y;
   }

    float getDeferredTwistRotation(Quaternion var1) {
      if (this.m_deferredBoneAxis == BoneAxis.Z) {
         return HelperFunctions.getRotationZ(var1);
      } else if (this.m_deferredBoneAxis == BoneAxis.Y) {
         return HelperFunctions.getRotationY(var1);
      } else {
         DebugLog.Animation.error("BoneAxis unhandled: %s", new Object[]{std::string.valueOf(this.m_deferredBoneAxis)});
         return 0.0F;
      }
   }

    Vector2 getDeferredMovement(Vector3f var1, Vector2 var2) {
      if (this.m_deferredBoneAxis == BoneAxis.Y) {
         var2.set(var1.x, -var1.z);
      } else {
         var2.set(var1.x, var1.y);
      }

    return var2;
   }

    Vector3f getCurrentDeferredCounterPosition(Vector3f var1) {
      this.getCurrentDeferredPosition(var1);
      if (this.m_deferredBoneAxis == BoneAxis.Y) {
         var1.set(-var1.x, 0.0F, var1.z);
      } else {
         var1.set(-var1.x, -var1.y, 0.0F);
      }

    return var1;
   }

    float getCurrentDeferredRotation() {
      return this.m_deferredMotion.m_targetDeferredRotation;
   }

    Vector3f getCurrentDeferredPosition(Vector3f var1) {
      var1.set(this.m_deferredMotion.m_targetDeferredPosition);
    return var1;
   }

    int getDeferredMovementBoneIdx() {
      return this.m_deferredBone != nullptr ? this.m_deferredBone.Index : -1;
   }

    float getCurrentTime() {
      return this.getReversibleTimeValue(this.currentTimeValue);
   }

    float getPreviousTime() {
      return this.getReversibleTimeValue(this.previousTimeValue);
   }

    float getReversibleTimeValue(float var1) {
      return this.reverse ? this.getDuration() - var1 : var1;
   }

    void TickCurrentTime(float var1) {
      s_performance.tickCurrentTime.invokeAndMeasure(this, var1, AnimationTrack::tickCurrentTimeInternal);
   }

    void tickCurrentTimeInternal(float var1) {
      var1 *= this.SpeedDelta;
      if (!this.IsPlaying) {
         var1 = 0.0F;
      }

    float var2 = this.getDuration();
      this.previousTimeValue = this.currentTimeValue;
      this.currentTimeValue += var1;
      if (this.bLooping) {
         if (this.previousTimeValue == 0.0F && this.currentTimeValue > 0.0F) {
            this.invokeOnAnimStartedEvent();
         }

         if (this.currentTimeValue >= var2) {
            this.invokeOnLoopedAnimEvent();
            this.currentTimeValue %= var2;
            this.invokeOnAnimStartedEvent();
         }
      } else {
         if (this.currentTimeValue < 0.0F) {
            this.currentTimeValue = 0.0F;
         }

         if (this.previousTimeValue == 0.0F && this.currentTimeValue > 0.0F) {
            this.invokeOnAnimStartedEvent();
         }

         if (this.triggerOnNonLoopedAnimFadeOutEvent) {
    float var3 = var2 - this.earlyBlendOutTime;
            if (this.previousTimeValue < var3 && var3 <= this.currentTimeValue) {
               this.invokeOnNonLoopedAnimFadeOutEvent();
            }
         }

         if (this.currentTimeValue > var2) {
            this.currentTimeValue = var2;
         }

         if (this.previousTimeValue < var2 && this.currentTimeValue >= var2) {
            this.invokeOnLoopedAnimEvent();
            this.invokeOnNonLoopedAnimFinishedEvent();
         }
      }
   }

    float getDuration() {
      return this.hasClip() ? this.CurrentClip.Duration : 0.0F;
   }

    void invokeListeners(Consumer<IAnimListener> var1) {
      if (!this.listeners.empty()) {
         this.listenersInvoking.clear();
         this.listenersInvoking.addAll(this.listeners);

         for (int var2 = 0; var2 < this.listenersInvoking.size(); var2++) {
    IAnimListener var3 = this.listenersInvoking.get(var2);
            var1.accept(var3);
         }
      }
   }

   private <T1> void invokeListeners(T1 var1, ICallback<IAnimListener, T1> var2) {
      Lambda.capture(this, var1, var2, (var0, var1x, var2x, var3) -> var1x.invokeListeners(var0.consumer(var2x, var3)));
   }

    void invokeOnAnimStartedEvent() {
      this.invokeListeners(this, IAnimListener::onAnimStarted);
   }

    void invokeOnLoopedAnimEvent() {
      this.invokeListeners(this, IAnimListener::onLoopedAnim);
   }

    void invokeOnNonLoopedAnimFadeOutEvent() {
      this.invokeListeners(this, IAnimListener::onNonLoopedAnimFadeOut);
   }

    void invokeOnNonLoopedAnimFinishedEvent() {
      this.invokeListeners(this, IAnimListener::onNonLoopedAnimFinished);
   }

    void onReleased() {
      if (!this.listeners.empty()) {
         this.listenersInvoking.clear();
         this.listenersInvoking.addAll(this.listeners);

         for (int var1 = 0; var1 < this.listenersInvoking.size(); var1++) {
    IAnimListener var2 = this.listenersInvoking.get(var1);
            var2.onTrackDestroyed(this);
         }

         this.listeners.clear();
         this.listenersInvoking.clear();
      }

      this.reset();
   }

    Vector2 getDeferredMovementDiff(Vector2 var1) {
      var1.set(this.m_deferredMotion.m_counterRotatedMovementDiff);
    return var1;
   }

    float getDeferredRotationDiff() {
      return this.m_deferredMotion.m_deferredRotationDiff;
   }

    float getClampedBlendDelta() {
      return PZMath.clamp(this.BlendDelta, 0.0F, 1.0F);
   }

    void addListener(IAnimListener var1) {
      this.listeners.push_back(var1);
   }

    void startClip(AnimationClip var1, bool var2) {
      if (var1 == nullptr) {
         throw NullPointerException("Supplied clip is nullptr.");
      } else {
         this.reset();
         this.IsPlaying = true;
         this.bLooping = var2;
         this.CurrentClip = var1;
      }
   }

    AnimationTrack reset() {
      return this.resetInternal();
   }

    void setBoneWeights(List<AnimBoneWeight> var1) {
      this.m_boneWeightBindings = PooledAnimBoneWeightArray.toArray(var1);
      this.m_boneWeights = nullptr;
   }

    void initBoneWeights(SkinningData var1) {
      if (!this.hasBoneMask()) {
         if (this.m_boneWeightBindings != nullptr) {
            if (this.m_boneWeightBindings.empty()) {
               this.m_boneWeights = PooledFloatArrayObject.alloc(0);
            } else {
               this.m_boneWeights = PooledFloatArrayObject.alloc(var1.numBones());
               PZArrayUtil.arraySet(this.m_boneWeights.array(), 0.0F);

               for (int var2 = 0; var2 < this.m_boneWeightBindings.length(); var2++) {
    AnimBoneWeight var3 = (AnimBoneWeight)this.m_boneWeightBindings.get(var2);
                  this.initWeightBinding(var1, var3);
               }
            }
         }
      }
   }

    void initWeightBinding(SkinningData var1, AnimBoneWeight var2) {
      if (var2 != nullptr && !StringUtils.isNullOrEmpty(var2.boneName)) {
    std::string var3 = var2.boneName;
    SkinningBone var4 = var1.getBone(var3);
         if (var4 == nullptr) {
            DebugLog.Animation.error("Bone not found: %s", new Object[]{var3});
         } else {
    float var5 = var2.weight;
            this.assignBoneWeight(var5, var4.Index);
            if (var2.includeDescendants) {
               Lambda.forEach(var4::forEachDescendant, this, var5, (var0, var1x, var2x) -> var1x.assignBoneWeight(var2x, var0.Index));
            }
         }
      }
   }

    void assignBoneWeight(float var1, int var2) {
      if (!this.hasBoneMask()) {
         throw NullPointerException("Bone weights array not initialized.");
      } else {
    float var3 = this.m_boneWeights.get(var2);
         this.m_boneWeights.set(var2, Math.max(var1, var3));
      }
   }

    float getBoneWeight(int var1) {
      if (!this.hasBoneMask()) {
         return 1.0F;
      } else {
         return DebugOptions.instance.char.Debug.Animate.NoBoneMasks.getValue() ? 1.0F : PZArrayUtil.getOrDefault(this.m_boneWeights.array(), var1, 0.0F);
      }
   }

    float getDeferredBoneWeight() {
      return this.m_deferredBone == nullptr ? 0.0F : this.getBoneWeight(this.m_deferredBone.Index);
   }

    void setLayerIdx(int var1) {
      this.m_layerIdx = var1;
   }

    int getLayerIdx() {
      return this.m_layerIdx;
   }

    bool hasBoneMask() {
      return this.m_boneWeights != nullptr;
   }

    bool isLooping() {
      return this.bLooping;
   }

    void setDeferredBone(SkinningBone var1, BoneAxis var2) {
      this.m_deferredBone = var1;
      this.m_deferredBoneAxis = var2;
   }

    void setUseDeferredRotation(bool var1) {
      this.m_useDeferredRotation = var1;
   }

    bool getUseDeferredRotation() {
      return this.m_useDeferredRotation;
   }

    bool isFinished() {
      return !this.bLooping && this.getDuration() > 0.0F && this.currentTimeValue >= this.getDuration();
   }

    float getCurrentTimeValue() {
      return this.currentTimeValue;
   }

    void setCurrentTimeValue(float var1) {
      this.currentTimeValue = var1;
   }

    float getPreviousTimeValue() {
      return this.previousTimeValue;
   }

    void setPreviousTimeValue(float var1) {
      this.previousTimeValue = var1;
   }

    void rewind(float var1) {
      this.advance(-var1);
   }

    void scaledRewind(float var1) {
      this.scaledAdvance(-var1);
   }

    void scaledAdvance(float var1) {
      this.advance(var1 * this.SpeedDelta);
   }

    void advance(float var1) {
      this.currentTimeValue = PZMath.wrap(this.currentTimeValue + var1, 0.0F, this.getDuration());
      this.previousTimeValue = PZMath.wrap(this.previousTimeValue + var1, 0.0F, this.getDuration());
   }

    void advanceFraction(float var1) {
      this.advance(this.getDuration() * var1);
   }

    void moveCurrentTimeValueTo(float var1) {
    float var2 = var1 - this.currentTimeValue;
      this.advance(var2);
   }

    void moveCurrentTimeValueToFraction(float var1) {
    float var2 = this.getDuration() * var1;
      this.moveCurrentTimeValueTo(var2);
   }

    float getCurrentTimeFraction() {
      return this.hasClip() ? this.currentTimeValue / this.getDuration() : 0.0F;
   }

    bool hasClip() {
      return this.CurrentClip != nullptr;
   }

    AnimationClip getClip() {
      return this.CurrentClip;
   }

    int getPriority() {
      return this.priority;
   }

    static AnimationTrack createClone(AnimationTrack var0, Supplier<AnimationTrack> var1) {
    AnimationTrack var2 = (AnimationTrack)var1.get();
      var2.IsPlaying = var0.IsPlaying;
      var2.CurrentClip = var0.CurrentClip;
      var2.priority = var0.priority;
      var2.currentTimeValue = var0.currentTimeValue;
      var2.previousTimeValue = var0.previousTimeValue;
      var2.SyncTrackingEnabled = var0.SyncTrackingEnabled;
      var2.reverse = var0.reverse;
      var2.bLooping = var0.bLooping;
      var2.SpeedDelta = var0.SpeedDelta;
      var2.BlendDelta = var0.BlendDelta;
      var2.blendFieldWeight = var0.blendFieldWeight;
      var2.name = var0.name;
      var2.earlyBlendOutTime = var0.earlyBlendOutTime;
      var2.triggerOnNonLoopedAnimFadeOutEvent = var0.triggerOnNonLoopedAnimFadeOutEvent;
      var2.m_layerIdx = var0.m_layerIdx;
      var2.m_boneWeightBindings = PooledAnimBoneWeightArray.toArray(var0.m_boneWeightBindings);
      var2.m_boneWeights = PooledFloatArrayObject.toArray(var0.m_boneWeights);
      var2.m_deferredBone = var0.m_deferredBone;
      var2.m_deferredBoneAxis = var0.m_deferredBoneAxis;
      var2.m_useDeferredRotation = var0.m_useDeferredRotation;
    return var2;
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
