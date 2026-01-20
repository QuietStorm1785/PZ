#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent/AnimEventTime.h"
#include "zombie/core/skinnedmodel/advancedanimation/LiveAnimNode/TransitionIn.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/core/skinnedmodel/animation/BoneAxis.h"
#include "zombie/core/skinnedmodel/animation/IAnimListener.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class LiveAnimNode : public PooledObject {
public:
    AnimNode m_sourceNode;
    AnimLayer m_animLayer;
    bool m_active;
    bool m_wasActive;
    bool m_TransitioningOut;
    float m_Weight;
    float m_RawWeight;
    bool m_isNew;
    int m_layerIdx;
    const TransitionIn m_transitionIn = std::make_shared<TransitionIn>();
   const List<AnimationTrack> m_AnimationTracks = std::make_unique<std::vector<>>();
    float m_NodeAnimTime;
    float m_PrevNodeAnimTime;
    bool m_blendingIn;
    bool m_blendingOut;
    AnimTransition m_transitionOut;
   private static const Pool<LiveAnimNode> s_pool = std::make_shared<Pool>(LiveAnimNode::new);

    protected LiveAnimNode() {
   }

    static LiveAnimNode alloc(AnimLayer var0, AnimNode var1, int var2) {
    LiveAnimNode var3 = (LiveAnimNode)s_pool.alloc();
      var3.reset();
      var3.m_sourceNode = var1;
      var3.m_animLayer = var0;
      var3.m_layerIdx = var2;
    return var3;
   }

    void reset() {
      this.m_sourceNode = nullptr;
      this.m_animLayer = nullptr;
      this.m_active = false;
      this.m_wasActive = false;
      this.m_TransitioningOut = false;
      this.m_Weight = 0.0F;
      this.m_RawWeight = 0.0F;
      this.m_isNew = true;
      this.m_layerIdx = -1;
      this.m_transitionIn.reset();
      this.m_AnimationTracks.clear();
      this.m_NodeAnimTime = 0.0F;
      this.m_PrevNodeAnimTime = 0.0F;
      this.m_blendingIn = false;
      this.m_blendingOut = false;
      this.m_transitionOut = nullptr;
   }

    void onReleased() {
      this.reset();
   }

    std::string getName() {
      return this.m_sourceNode.m_Name;
   }

    bool isTransitioningIn() {
      return this.m_transitionIn.m_active && this.m_transitionIn.m_track != nullptr;
   }

    void startTransitionIn(LiveAnimNode var1, AnimTransition var2, AnimationTrack var3) {
      this.startTransitionIn(var1.getSourceNode(), var2, var3);
   }

    void startTransitionIn(AnimNode var1, AnimTransition var2, AnimationTrack var3) {
      this.m_transitionIn.m_active = var3 != nullptr;
      this.m_transitionIn.m_transitionedFrom = var1.m_Name;
      this.m_transitionIn.m_data = var2;
      this.m_transitionIn.m_track = var3;
      this.m_transitionIn.m_weight = 0.0F;
      this.m_transitionIn.m_rawWeight = 0.0F;
      this.m_transitionIn.m_blendingIn = true;
      this.m_transitionIn.m_blendingOut = false;
      this.m_transitionIn.m_time = 0.0F;
      if (this.m_transitionIn.m_track != nullptr) {
         this.m_transitionIn.m_track.addListener(this);
      }

      this.setMainTracksPlaying(false);
   }

    void setTransitionOut(AnimTransition var1) {
      this.m_transitionOut = var1;
   }

    void update(float var1) {
      this.m_isNew = false;
      if (this.m_active != this.m_wasActive) {
         this.m_blendingIn = this.m_active;
         this.m_blendingOut = !this.m_active;
         if (this.m_transitionIn.m_active) {
            this.m_transitionIn.m_blendingIn = this.m_active;
            this.m_transitionIn.m_blendingOut = !this.m_active;
         }

         this.m_wasActive = this.m_active;
      }

    bool var2 = this.isMainAnimActive();
      if (this.isTransitioningIn()) {
         this.updateTransitioningIn(var1);
      }

    bool var3 = this.isMainAnimActive();
      if (var3) {
         if (this.m_blendingOut && this.m_sourceNode.m_StopAnimOnExit) {
            this.setMainTracksPlaying(false);
         } else {
            this.setMainTracksPlaying(true);
         }
      } else {
         this.setMainTracksPlaying(false);
      }

      if (var3) {
    bool var4 = !var2;
         if (var4 && this.isLooped()) {
    float var5 = this.getMainInitialRewindTime();
            PZArrayUtil.forEach(this.m_AnimationTracks, Lambda.consumer(var5, AnimationTrack::scaledRewind));
         }

         if (this.m_blendingIn) {
            this.updateBlendingIn(var1);
         } else if (this.m_blendingOut) {
            this.updateBlendingOut(var1);
         }

         this.m_PrevNodeAnimTime = this.m_NodeAnimTime;
         this.m_NodeAnimTime += var1;
         if (!this.m_transitionIn.m_active && this.m_transitionIn.m_track != nullptr && this.m_transitionIn.m_track.BlendDelta <= 0.0F) {
            this.m_animLayer.getAnimationTrack().removeTrack(this.m_transitionIn.m_track);
            this.m_transitionIn.reset();
         }
      }
   }

    void updateTransitioningIn(float var1) {
    float var2 = this.m_transitionIn.m_track.SpeedDelta;
    float var3 = this.m_transitionIn.m_track.getDuration();
      this.m_transitionIn.m_time = this.m_transitionIn.m_track.getCurrentTimeValue();
      if (this.m_transitionIn.m_time >= var3) {
         this.m_transitionIn.m_active = false;
         this.m_transitionIn.m_weight = 0.0F;
      } else {
         if (!this.m_transitionIn.m_blendingOut) {
    bool var4 = AnimCondition.pass(this.m_animLayer.getVariableSource(), this.m_transitionIn.m_data.m_Conditions);
            if (!var4) {
               this.m_transitionIn.m_blendingIn = false;
               this.m_transitionIn.m_blendingOut = true;
            }
         }

    float var8 = this.getTransitionInBlendOutTime() * var2;
         if (this.m_transitionIn.m_time >= var3 - var8) {
            this.m_transitionIn.m_blendingIn = false;
            this.m_transitionIn.m_blendingOut = true;
         }

         if (this.m_transitionIn.m_blendingIn) {
    float var5 = this.getTransitionInBlendInTime() * var2;
    float var6 = this.incrementBlendTime(this.m_transitionIn.m_rawWeight, var5, var1 * var2);
    float var7 = PZMath.clamp(var6 / var5, 0.0F, 1.0F);
            this.m_transitionIn.m_rawWeight = var7;
            this.m_transitionIn.m_weight = PZMath.lerpFunc_EaseOutInQuad(var7);
            this.m_transitionIn.m_blendingIn = var6 < var5;
            this.m_transitionIn.m_active = var6 < var3;
         }

         if (this.m_transitionIn.m_blendingOut) {
    float var9 = this.getTransitionInBlendOutTime() * var2;
    float var10 = this.incrementBlendTime(1.0F - this.m_transitionIn.m_rawWeight, var9, var1 * var2);
    float var11 = PZMath.clamp(1.0F - var10 / var9, 0.0F, 1.0F);
            this.m_transitionIn.m_rawWeight = var11;
            this.m_transitionIn.m_weight = PZMath.lerpFunc_EaseOutInQuad(var11);
            this.m_transitionIn.m_blendingOut = var10 < var9;
            this.m_transitionIn.m_active = this.m_transitionIn.m_blendingOut;
         }
      }
   }

    void addMainTrack(AnimationTrack var1) {
      if (!this.isLooped() && !this.m_sourceNode.m_StopAnimOnExit && this.m_sourceNode.m_EarlyTransitionOut) {
    float var2 = this.getBlendOutTime();
         if (var2 > 0.0F && float.isFinite(var2)) {
            var1.earlyBlendOutTime = var2;
            var1.triggerOnNonLoopedAnimFadeOutEvent = true;
         }
      }

      this.m_AnimationTracks.push_back(var1);
   }

    void setMainTracksPlaying(bool var1) {
      Lambda.forEachFrom(PZArrayUtil::forEach, this.m_AnimationTracks, var1, (var0, var1x) -> var0.IsPlaying = var1x);
   }

    void updateBlendingIn(float var1) {
    float var2 = this.getBlendInTime();
      if (var2 <= 0.0F) {
         this.m_Weight = 1.0F;
         this.m_RawWeight = 1.0F;
         this.m_blendingIn = false;
      } else {
    float var3 = this.incrementBlendTime(this.m_RawWeight, var2, var1);
    float var4 = PZMath.clamp(var3 / var2, 0.0F, 1.0F);
         this.m_RawWeight = var4;
         this.m_Weight = PZMath.lerpFunc_EaseOutInQuad(var4);
         this.m_blendingIn = var3 < var2;
      }
   }

    void updateBlendingOut(float var1) {
    float var2 = this.getBlendOutTime();
      if (var2 <= 0.0F) {
         this.m_Weight = 0.0F;
         this.m_RawWeight = 0.0F;
         this.m_blendingOut = false;
      } else {
    float var3 = this.incrementBlendTime(1.0F - this.m_RawWeight, var2, var1);
    float var4 = PZMath.clamp(1.0F - var3 / var2, 0.0F, 1.0F);
         this.m_RawWeight = var4;
         this.m_Weight = PZMath.lerpFunc_EaseOutInQuad(var4);
         this.m_blendingOut = var3 < var2;
      }
   }

    float incrementBlendTime(float var1, float var2, float var3) {
    float var4 = var1 * var2;
      return var4 + var3;
   }

    float getTransitionInBlendInTime() {
      return this.m_transitionIn.m_data != nullptr && this.m_transitionIn.m_data.m_blendInTime != float.POSITIVE_INFINITY
         ? this.m_transitionIn.m_data.m_blendInTime
         : 0.0F;
   }

    float getMainInitialRewindTime() {
    float var1 = 0.0F;
      if (this.m_sourceNode.m_randomAdvanceFraction > 0.0F) {
    float var2 = Rand.Next(0.0F, this.m_sourceNode.m_randomAdvanceFraction);
         var1 = var2 * this.getMaxDuration();
      }

      if (this.m_transitionIn.m_data == nullptr) {
         return 0.0F - var1;
      } else {
    float var4 = this.getTransitionInBlendOutTime();
    float var3 = this.m_transitionIn.m_data.m_SyncAdjustTime;
         return this.m_transitionIn.m_track != nullptr ? var4 - var3 : var4 - var3 - var1;
      }
   }

    float getMaxDuration() {
    float var1 = 0.0F;
    int var2 = 0;

      for (int var3 = this.m_AnimationTracks.size(); var2 < var3; var2++) {
    AnimationTrack var4 = this.m_AnimationTracks.get(var2);
    float var5 = var4.getDuration();
         var1 = PZMath.max(var5, var1);
      }

    return var1;
   }

    float getTransitionInBlendOutTime() {
      return this.getBlendInTime();
   }

    float getBlendInTime() {
      if (this.m_transitionIn.m_data == nullptr) {
         return this.m_sourceNode.m_BlendTime;
      } else if (this.m_transitionIn.m_track != nullptr && this.m_transitionIn.m_data.m_blendOutTime != float.POSITIVE_INFINITY) {
         return this.m_transitionIn.m_data.m_blendOutTime;
      } else {
         if (this.m_transitionIn.m_track == nullptr) {
            if (this.m_transitionIn.m_data.m_blendInTime != float.POSITIVE_INFINITY) {
               return this.m_transitionIn.m_data.m_blendInTime;
            }

            if (this.m_transitionIn.m_data.m_blendOutTime != float.POSITIVE_INFINITY) {
               return this.m_transitionIn.m_data.m_blendOutTime;
            }
         }

         return this.m_sourceNode.m_BlendTime;
      }
   }

    float getBlendOutTime() {
      if (this.m_transitionOut == nullptr) {
         return this.m_sourceNode.getBlendOutTime();
      } else if (!StringUtils.isNullOrWhitespace(this.m_transitionOut.m_AnimName) && this.m_transitionOut.m_blendInTime != float.POSITIVE_INFINITY) {
         return this.m_transitionOut.m_blendInTime;
      } else {
         if (StringUtils.isNullOrWhitespace(this.m_transitionOut.m_AnimName)) {
            if (this.m_transitionOut.m_blendOutTime != float.POSITIVE_INFINITY) {
               return this.m_transitionOut.m_blendOutTime;
            }

            if (this.m_transitionOut.m_blendInTime != float.POSITIVE_INFINITY) {
               return this.m_transitionOut.m_blendInTime;
            }
         }

         return this.m_sourceNode.getBlendOutTime();
      }
   }

    void onAnimStarted(AnimationTrack var1) {
      this.invokeAnimStartTimeEvent();
   }

    void onLoopedAnim(AnimationTrack var1) {
      if (!this.m_TransitioningOut) {
         this.invokeAnimEndTimeEvent();
      }
   }

    void onNonLoopedAnimFadeOut(AnimationTrack var1) {
      if (DebugOptions.instance.Animation.AllowEarlyTransitionOut.getValue()) {
         this.invokeAnimEndTimeEvent();
         this.m_TransitioningOut = true;
      }
   }

    void onNonLoopedAnimFinished(AnimationTrack var1) {
      if (!this.m_TransitioningOut) {
         this.invokeAnimEndTimeEvent();
      }
   }

    void onTrackDestroyed(AnimationTrack var1) {
      this.m_AnimationTracks.remove(var1);
      if (this.m_transitionIn.m_track == var1) {
         this.m_transitionIn.m_track = nullptr;
         this.m_transitionIn.m_active = false;
         this.m_transitionIn.m_weight = 0.0F;
         this.setMainTracksPlaying(true);
      }
   }

    void invokeAnimStartTimeEvent() {
      this.invokeAnimTimeEvent(AnimEventTime.Start);
   }

    void invokeAnimEndTimeEvent() {
      this.invokeAnimTimeEvent(AnimEventTime.End);
   }

    void invokeAnimTimeEvent(AnimEventTime var1) {
    std::vector var2 = this.getSourceNode().m_Events;
    int var3 = 0;

      for (int var4 = var2.size(); var3 < var4; var3++) {
    AnimEvent var5 = (AnimEvent)var2.get(var3);
         if (var5.m_Time == var1) {
            this.m_animLayer.invokeAnimEvent(var5);
         }
      }
   }

    AnimNode getSourceNode() {
      return this.m_sourceNode;
   }

    bool isIdleAnimActive() {
      return this.m_active && this.m_sourceNode.isIdleAnim();
   }

    bool isActive() {
      return this.m_active;
   }

    void setActive(bool var1) {
      this.m_active = var1;
   }

    bool isLooped() {
      return this.m_sourceNode.m_Looped;
   }

    float getWeight() {
      return this.m_Weight;
   }

    float getTransitionInWeight() {
      return this.m_transitionIn.m_weight;
   }

    bool wasActivated() {
      return this.m_active != this.m_wasActive && this.m_active;
   }

    bool wasDeactivated() {
      return this.m_active != this.m_wasActive && this.m_wasActive;
   }

    bool isNew() {
      return this.m_isNew;
   }

    int getPlayingTrackCount() {
    int var1 = 0;
      if (this.isMainAnimActive()) {
         var1 += this.m_AnimationTracks.size();
      }

      if (this.isTransitioningIn()) {
         var1++;
      }

    return var1;
   }

    bool isMainAnimActive() {
      return !this.isTransitioningIn() || this.m_transitionIn.m_blendingOut;
   }

    AnimationTrack getPlayingTrackAt(int var1) {
    int var2 = this.getPlayingTrackCount();
      if (var1 < 0 || var1 >= var2) {
         throw IndexOutOfBoundsException("TrackIdx out of bounds 0 - " + this.getPlayingTrackCount());
      } else {
         return this.isTransitioningIn() && var1 == var2 - 1 ? this.m_transitionIn.m_track : this.m_AnimationTracks.get(var1);
      }
   }

    std::string getTransitionFrom() {
      return this.m_transitionIn.m_transitionedFrom;
   }

    void setTransitionInBlendDelta(float var1) {
      if (this.m_transitionIn.m_track != nullptr) {
         this.m_transitionIn.m_track.BlendDelta = var1;
      }
   }

    AnimationTrack getTransitionInTrack() {
      return this.m_transitionIn.m_track;
   }

    int getTransitionLayerIdx() {
      return this.m_transitionIn.m_track != nullptr ? this.m_transitionIn.m_track.getLayerIdx() : -1;
   }

    int getLayerIdx() {
      return this.m_layerIdx;
   }

    int getPriority() {
      return this.m_sourceNode.getPriority();
   }

    std::string getDeferredBoneName() {
      return this.m_sourceNode.getDeferredBoneName();
   }

    BoneAxis getDeferredBoneAxis() {
      return this.m_sourceNode.getDeferredBoneAxis();
   }

   public List<AnimBoneWeight> getSubStateBoneWeights() {
      return this.m_sourceNode.m_SubStateBoneWeights;
   }

    AnimTransition findTransitionTo(IAnimationVariableSource var1, const std::string& var2) {
      return this.m_sourceNode.findTransitionTo(var1, var2);
   }

    float getSpeedScale(IAnimationVariableSource var1) {
      return this.m_sourceNode.getSpeedScale(var1);
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
