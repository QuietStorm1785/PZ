#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Math.h"
#include "zombie/GameProfiler.h"
#include "zombie/GameTime.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/advancedanimation/Anim2DBlendPicker/PickResults.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent/AnimEventTime.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimLayer/StartAnimTrackParameters.h"
#include "zombie/core/skinnedmodel/animation/AnimationMultiTrack.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/core/skinnedmodel/animation/IAnimListener.h"
#include "zombie/core/skinnedmodel/animation/debug/AnimationPlayerRecorder.h"
#include "zombie/core/skinnedmodel/model/SkinningBone.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimLayer {
public:
    const AnimLayer m_parentLayer;
    const IAnimatable m_Character;
    AnimState m_State = nullptr;
    AnimNode m_CurrentNode = nullptr;
    IAnimEventCallback m_AnimEventsCallback;
    LiveAnimNode m_currentSyncNode;
    AnimationTrack m_currentSyncTrack;
   private const List<AnimNode> m_reusableAnimNodes = std::make_unique<std::vector<>>();
   private const List<LiveAnimNode> m_liveAnimNodes = std::make_unique<std::vector<>>();
    static const AnimEvent s_activeAnimLoopedEvent = std::make_shared<AnimEvent>();
    static const AnimEvent s_activeNonLoopedAnimFadeOutEvent = std::make_shared<AnimEvent>();
    static const AnimEvent s_activeAnimFinishingEvent = std::make_shared<AnimEvent>();
    static const AnimEvent s_activeNonLoopedAnimFinishedEvent = std::make_shared<AnimEvent>();

    public AnimLayer(IAnimatable var1, IAnimEventCallback var2) {
      this(nullptr, var1, var2);
   }

    public AnimLayer(AnimLayer var1, IAnimatable var2, IAnimEventCallback var3) {
      this.m_parentLayer = var1;
      this.m_Character = var2;
      this.m_AnimEventsCallback = var3;
   }

    std::string getCurrentStateName() {
      return this.m_State == nullptr ? nullptr : this.m_State.m_Name;
   }

    bool hasState() {
      return this.m_State != nullptr;
   }

    bool isStateless() {
      return this.m_State == nullptr;
   }

    bool isSubLayer() {
      return this.m_parentLayer != nullptr;
   }

    bool isCurrentState(const std::string& var1) {
      return this.m_State != nullptr && StringUtils == this.m_State.m_Name, var1);
   }

    AnimationMultiTrack getAnimationTrack() {
      if (this.m_Character == nullptr) {
    return nullptr;
      } else {
    AnimationPlayer var1 = this.m_Character.getAnimationPlayer();
    return var1 = = nullptr ? nullptr : var1.getMultiTrack();
      }
   }

    IAnimationVariableSource getVariableSource() {
      return this.m_Character;
   }

    LiveAnimNode getCurrentSyncNode() {
      return this.m_currentSyncNode;
   }

    AnimationTrack getCurrentSyncTrack() {
      return this.m_currentSyncTrack;
   }

    void onAnimStarted(AnimationTrack var1) {
   }

    void onLoopedAnim(AnimationTrack var1) {
      this.invokeAnimEvent(var1, s_activeAnimLoopedEvent, false);
   }

    void onNonLoopedAnimFadeOut(AnimationTrack var1) {
      this.invokeAnimEvent(var1, s_activeAnimFinishingEvent, true);
      this.invokeAnimEvent(var1, s_activeNonLoopedAnimFadeOutEvent, true);
   }

    void onNonLoopedAnimFinished(AnimationTrack var1) {
      this.invokeAnimEvent(var1, s_activeAnimFinishingEvent, false);
      this.invokeAnimEvent(var1, s_activeNonLoopedAnimFinishedEvent, true);
   }

    void onTrackDestroyed(AnimationTrack var1) {
   }

    void invokeAnimEvent(AnimationTrack var1, AnimEvent var2, bool var3) {
      if (this.m_AnimEventsCallback != nullptr) {
    int var4 = 0;

         for (int var5 = this.m_liveAnimNodes.size(); var4 < var5; var4++) {
    LiveAnimNode var6 = this.m_liveAnimNodes.get(var4);
            if ((!var6.m_TransitioningOut || var3) && var6.getSourceNode().m_State == this.m_State && var6.m_AnimationTracks.contains(var1)) {
               this.invokeAnimEvent(var2);
               break;
            }
         }
      }
   }

    void invokeAnimEvent(AnimEvent var1) {
      if (this.m_AnimEventsCallback == nullptr) {
         DebugLog.Animation.warn("invokeAnimEvent. No listener. %s", new Object[]{var1.toDetailsString()});
      } else {
         this.m_AnimEventsCallback.OnAnimEvent(this, var1);
      }
   }

    std::string GetDebugString() {
    std::string var1 = this.m_Character.getAdvancedAnimator().animSet.m_Name;
      if (this.m_State != nullptr) {
         var1 = var1 + "/" + this.m_State.m_Name;
         if (this.m_CurrentNode != nullptr) {
            var1 = var1 + "/" + this.m_CurrentNode.m_Name + ": " + this.m_CurrentNode.m_AnimName;
         }
      }

    std::string var2 = "State: " + var1;

      for (LiveAnimNode var4 : this.m_liveAnimNodes) {
         var2 = var2 + "\n  Node: " + var4.getSourceNode().m_Name;
      }

    AnimationMultiTrack var6 = this.getAnimationTrack();
      if (var6 != nullptr) {
         var2 = var2 + "\n  AnimTrack:";

         for (AnimationTrack var5 : var6.getTracks()) {
            var2 = var2 + "\n    Anim: " + var5.name + " Weight: " + var5.BlendDelta;
         }
      }

    return var2;
   }

    void Reset() {
    AnimationMultiTrack var1 = this.getAnimationTrack();

      for (int var2 = this.m_liveAnimNodes.size() - 1; var2 >= 0; var2--) {
    LiveAnimNode var3 = this.m_liveAnimNodes.get(var2);
         var3.setActive(false);
         if (var1 != nullptr) {
            var1.removeTracks(var3.m_AnimationTracks);
         }

         this.m_liveAnimNodes.remove(var2).release();
      }

      this.m_State = nullptr;
   }

    bool TransitionTo(AnimState var1, bool var2) {
    AnimationMultiTrack var3 = this.getAnimationTrack();
      if (var3 == nullptr) {
         if (this.m_Character == nullptr) {
            DebugLog.General.error("AnimationTrack is nullptr. char is nullptr.");
            this.m_State = nullptr;
    return false;
         } else if (this.m_Character.getAnimationPlayer() == nullptr) {
            DebugLog.General.error("AnimationTrack is nullptr. char ModelInstance.AnimPlayer is nullptr.");
            this.m_State = nullptr;
    return false;
         } else {
            DebugLog.General.error("AnimationTrack is nullptr. Unknown reason.");
    return false;
         }
      } else if (var1 == this.m_State && !var2) {
    return true;
      } else {
         if (DebugOptions.instance.Animation.AnimLayer.LogStateChanges.getValue()) {
    std::string var4 = this.m_parentLayer == nullptr ? "" : AnimState.getStateName(this.m_parentLayer.m_State) + " | ";
    std::string var5 = std::string.format("State: %s%s => %s", var4, AnimState.getStateName(this.m_State), AnimState.getStateName(var1));
            DebugLog.General.debugln(var5);
            if (this.dynamic_cast<IsoGameCharacter*>(m_Character) != nullptr) {
               ((IsoGameCharacter)this.m_Character).setSayLine(var5);
            }
         }

         this.m_State = var1;

         for (int var6 = 0; var6 < this.m_liveAnimNodes.size(); var6++) {
    LiveAnimNode var7 = this.m_liveAnimNodes.get(var6);
            var7.m_TransitioningOut = true;
         }

    return true;
      }
   }

    void Update() {
      GameProfiler.getInstance().invokeAndMeasure("AnimLayer.Update", this, AnimLayer::updateInternal);
   }

    void updateInternal() {
    float var1 = GameTime.instance.getTimeDelta();
      this.removeFadedOutNodes();
      this.updateNodeActiveFlags();
    LiveAnimNode var2 = this.getHighestLiveNode();
      this.m_currentSyncNode = var2;
      this.m_currentSyncTrack = nullptr;
      if (var2 != nullptr) {
    int var3 = 0;

         for (int var4 = this.m_liveAnimNodes.size(); var3 < var4; var3++) {
    LiveAnimNode var5 = this.m_liveAnimNodes.get(var3);
            var5.update(var1);
         }

    IAnimatable var19 = this.m_Character;
         this.updateMaximumTwist(var19);
         boolean var20 = DebugOptions.instance.Animation.AnimLayer.AllowAnimNodeOverride.getValue()
            && var19.getVariableBoolean("dbgForceAnim")
            && var19.getVariableBoolean("dbgForceAnimScalars");
    std::string var21 = var20 ? var19.getVariableString("dbgForceAnimNodeName") : nullptr;
    AnimationTrack var6 = this.findSyncTrack(var2);
         this.m_currentSyncTrack = var6;
    float var7 = var6 != nullptr ? var6.getCurrentTimeFraction() : -1.0F;
    int var8 = 0;

         for (int var9 = this.m_liveAnimNodes.size(); var8 < var9; var8++) {
    LiveAnimNode var10 = this.m_liveAnimNodes.get(var8);
    float var11 = 1.0F;
    int var12 = 0;

            for (int var13 = var10.getPlayingTrackCount(); var12 < var13; var12++) {
    AnimationTrack var14 = var10.getPlayingTrackAt(var12);
               if (var14.IsPlaying) {
                  if (var6 != nullptr && var14.SyncTrackingEnabled && var14.isLooping() && var14 != var6) {
                     var14.moveCurrentTimeValueToFraction(var7);
                  }

                  if (var14.name == var10.getSourceNode().m_AnimName)) {
                     var11 = var14.getDuration();
                     var10.m_NodeAnimTime = var14.getCurrentTimeValue();
                  }
               }
            }

            if (this.m_AnimEventsCallback != nullptr && var10.getSourceNode().m_Events.size() > 0) {
    float var22 = var10.m_NodeAnimTime / var11;
    float var24 = var10.m_PrevNodeAnimTime / var11;
    std::vector var26 = var10.getSourceNode().m_Events;
    int var15 = 0;

               for (int var16 = var26.size(); var15 < var16; var15++) {
    AnimEvent var17 = (AnimEvent)var26.get(var15);
                  if (var17.m_Time == AnimEventTime.Percentage) {
    float var18 = var17.m_TimePc;
                     if (var24 < var18 && var18 <= var22) {
                        this.invokeAnimEvent(var17);
                     } else {
                        if (!var10.isLooped() && var22 < var18) {
                           break;
                        }

                        if (var10.isLooped() && var24 > var22) {
                           if (var24 < var18 && var18 <= var22 + 1.0F) {
                              this.invokeAnimEvent(var17);
                           } else if (var24 > var18 && var18 <= var22) {
                              this.invokeAnimEvent(var17);
                           }
                        }
                     }
                  }
               }
            }

            if (var10.getPlayingTrackCount() != 0) {
    bool var23 = var20 && StringUtils.equalsIgnoreCase(var10.getSourceNode().m_Name, var21);
    std::string var25 = var23 ? "dbgForceScalar" : var10.getSourceNode().m_Scalar;
    std::string var27 = var23 ? "dbgForceScalar2" : var10.getSourceNode().m_Scalar2;
    float var28 = var10.getTransitionInWeight();
               var10.setTransitionInBlendDelta(var28);
               if (var10.m_AnimationTracks.size() > 1) {
                  var28 = var19.getVariableFloat(var25, 0.0F);
    float var31 = var19.getVariableFloat(var27, 0.0F);
                  this.applyBlendField(var10, var28, var31);
               } else if (!var10.m_AnimationTracks.empty()) {
                  var28 = var10.getWeight();
    float var32 = var19.getVariableFloat(var25, 1.0F);
                  ((AnimationTrack)var10.m_AnimationTracks.get(0)).BlendDelta = var28 * Math.abs(var32);
               }
            }
         }

         if (this.isRecording()) {
            this.logBlendWeights();
            this.logCurrentState();
         }
      }
   }

    void updateMaximumTwist(IAnimationVariableSource var1) {
    IAnimationVariableSlot var2 = var1.getVariable("maxTwist");
      if (var2 != nullptr) {
    float var3 = var2.getValueFloat();
    float var4 = 0.0F;
    float var5 = 1.0F;

         for (int var6 = this.m_liveAnimNodes.size() - 1; var6 >= 0; var6--) {
    LiveAnimNode var7 = this.m_liveAnimNodes.get(var6);
    float var8 = var7.getWeight();
            if (var5 <= 0.0F) {
               break;
            }

    float var9 = PZMath.clamp(var8, 0.0F, var5);
            var5 -= var9;
    float var10 = PZMath.clamp(var7.getSourceNode().m_maxTorsoTwist, 0.0F, 70.0F);
            var4 += var10 * var9;
         }

         if (var5 > 0.0F) {
            var4 += var3 * var5;
         }

         var2.setValue(var4);
      }
   }

    void updateNodeActiveFlags() {
      for (int var1 = 0; var1 < this.m_liveAnimNodes.size(); var1++) {
    LiveAnimNode var2 = this.m_liveAnimNodes.get(var1);
         var2.setActive(false);
      }

    AnimState var7 = this.m_State;
    IAnimatable var8 = this.m_Character;
      if (var7 != nullptr && !var8.getVariableBoolean("AnimLocked")) {
    std::vector var3 = var7.getAnimNodes(var8, this.m_reusableAnimNodes);
    int var4 = 0;

         for (int var5 = var3.size(); var4 < var5; var4++) {
    AnimNode var6 = (AnimNode)var3.get(var4);
            this.getOrCreateLiveNode(var6);
         }
      }

      this.updateNewNodeTransitions();
   }

    void updateNewNodeTransitions() {
      GameProfiler.getInstance().invokeAndMeasure("updateNewNodeTransitions", this, AnimLayer::updateNewNodeTransitionsInternal);
   }

    void updateNewNodeTransitionsInternal() {
    IAnimatable var1 = this.m_Character;
    int var2 = 0;

      for (int var3 = this.m_liveAnimNodes.size(); var2 < var3; var2++) {
    LiveAnimNode var4 = this.m_liveAnimNodes.get(var2);
         if (var4.isNew() && var4.wasActivated()) {
    LiveAnimNode var5 = this.findTransitionToNewNode(var4, false);
            if (var5 != nullptr) {
    AnimTransition var6 = var5.findTransitionTo(var1, var4.getName());
    float var7 = var6.m_speedScale;
               if (var7 == float.POSITIVE_INFINITY) {
                  var7 = var4.getSpeedScale(this.m_Character);
               }

    AnimationTrack var8 = nullptr;
               if (!StringUtils.isNullOrWhitespace(var6.m_AnimName)) {
    StartAnimTrackParameters var9 = StartAnimTrackParameters.alloc();
                  var9.subLayerBoneWeights = var5.getSubStateBoneWeights();
                  var9.speedScale = var7;
                  var9.deferredBoneName = var5.getDeferredBoneName();
                  var9.deferredBoneAxis = var5.getDeferredBoneAxis();
                  var9.priority = var5.getPriority();
                  var8 = this.startAnimTrack(var6.m_AnimName, var9);
                  var9.release();
                  if (var8 == nullptr) {
                     if (DebugLog.isEnabled(DebugType.Animation)) {
                        DebugLog.Animation
                           .println("  TransitionTo failed to play transition track: %s -> %s -> %s", var5.getName(), var6.m_AnimName, var4.getName());
                     }
                     continue;
                  }

                  if (DebugLog.isEnabled(DebugType.Animation)) {
                     DebugLog.Animation.println("  TransitionTo found: %s -> %s -> %s", var5.getName(), var6.m_AnimName, var4.getName());
                  }
               } else if (DebugLog.isEnabled(DebugType.Animation)) {
                  DebugLog.Animation.println("  TransitionTo found: %s -> <no anim> -> %s", var5.getName(), var4.getName());
               }

               var4.startTransitionIn(var5, var6, var8);
               var5.setTransitionOut(var6);
            }
         }
      }
   }

    LiveAnimNode findTransitionToNewNode(LiveAnimNode var1, bool var2) {
    LiveAnimNode var3 = nullptr;
    int var4 = 0;

      for (int var5 = this.m_liveAnimNodes.size(); var4 < var5; var4++) {
    LiveAnimNode var6 = this.m_liveAnimNodes.get(var4);
         if (var6 != var1 && (var2 || var6.wasDeactivated())) {
    AnimNode var7 = var6.getSourceNode();
    AnimTransition var8 = var7.findTransitionTo(this.m_Character, var1.getName());
            if (var8 != nullptr) {
               var3 = var6;
               break;
            }
         }
      }

      if (var3 == nullptr && this.isSubLayer()) {
         var3 = this.m_parentLayer.findTransitionToNewNode(var1, true);
      }

    return var3;
   }

    void removeFadedOutNodes() {
      for (int var1 = this.m_liveAnimNodes.size() - 1; var1 >= 0; var1--) {
    LiveAnimNode var2 = this.m_liveAnimNodes.get(var1);
         if (!var2.isActive() && (!var2.isTransitioningIn() || !(var2.getTransitionInWeight() > 0.01F)) && !(var2.getWeight() > 0.01F)) {
            this.removeLiveNodeAt(var1);
         }
      }
   }

    void render() {
    IAnimatable var1 = this.m_Character;
      boolean var2 = DebugOptions.instance.Animation.AnimLayer.AllowAnimNodeOverride.getValue()
         && var1.getVariableBoolean("dbgForceAnim")
         && var1.getVariableBoolean("dbgForceAnimScalars");
    std::string var3 = var2 ? var1.getVariableString("dbgForceAnimNodeName") : nullptr;
    int var4 = 0;

      for (int var5 = this.m_liveAnimNodes.size(); var4 < var5; var4++) {
    LiveAnimNode var6 = this.m_liveAnimNodes.get(var4);
         if (var6.m_AnimationTracks.size() > 1) {
    bool var7 = var2 && StringUtils.equalsIgnoreCase(var6.getSourceNode().m_Name, var3);
    std::string var8 = var7 ? "dbgForceScalar" : var6.getSourceNode().m_Scalar;
    std::string var9 = var7 ? "dbgForceScalar2" : var6.getSourceNode().m_Scalar2;
    float var10 = var1.getVariableFloat(var8, 0.0F);
    float var11 = var1.getVariableFloat(var9, 0.0F);
            if (var6.isActive()) {
               var6.getSourceNode().m_picker.render(var10, var11);
            }
         }
      }
   }

    void logBlendWeights() {
    AnimationPlayerRecorder var1 = this.m_Character.getAnimationPlayer().getRecorder();
    int var2 = 0;

      for (int var3 = this.m_liveAnimNodes.size(); var2 < var3; var2++) {
    LiveAnimNode var4 = this.m_liveAnimNodes.get(var2);
         var1.logAnimNode(var4);
      }
   }

    void logCurrentState() {
    AnimationPlayerRecorder var1 = this.m_Character.getAnimationPlayer().getRecorder();
      var1.logAnimState(this.m_State);
   }

    void removeLiveNodeAt(int var1) {
    LiveAnimNode var2 = this.m_liveAnimNodes.get(var1);
    AnimationMultiTrack var3 = this.getAnimationTrack();
      var3.removeTracks(var2.m_AnimationTracks);
      var3.removeTrack(var2.getTransitionInTrack());
      this.m_liveAnimNodes.remove(var1).release();
   }

    void applyBlendField(LiveAnimNode var1, float var2, float var3) {
      if (var1.isActive()) {
    AnimNode var4 = var1.getSourceNode();
    Anim2DBlendPicker var5 = var4.m_picker;
    PickResults var6 = var5.Pick(var2, var3);
    Anim2DBlend var7 = var6.node1;
    Anim2DBlend var8 = var6.node2;
    Anim2DBlend var9 = var6.node3;
         if (float.isNaN(var6.scale1)) {
            var6.scale1 = 0.5F;
         }

         if (float.isNaN(var6.scale2)) {
            var6.scale2 = 0.5F;
         }

         if (float.isNaN(var6.scale3)) {
            var6.scale3 = 0.5F;
         }

    float var10 = var6.scale1;
    float var11 = var6.scale2;
    float var12 = var6.scale3;

         for (int var13 = 0; var13 < var1.m_AnimationTracks.size(); var13++) {
    Anim2DBlend var14 = (Anim2DBlend)var4.m_2DBlends.get(var13);
    AnimationTrack var15 = (AnimationTrack)var1.m_AnimationTracks.get(var13);
            if (var14 == var7) {
               var15.blendFieldWeight = AnimationPlayer.lerpBlendWeight(var15.blendFieldWeight, var10, 0.15F);
            } else if (var14 == var8) {
               var15.blendFieldWeight = AnimationPlayer.lerpBlendWeight(var15.blendFieldWeight, var11, 0.15F);
            } else if (var14 == var9) {
               var15.blendFieldWeight = AnimationPlayer.lerpBlendWeight(var15.blendFieldWeight, var12, 0.15F);
            } else {
               var15.blendFieldWeight = AnimationPlayer.lerpBlendWeight(var15.blendFieldWeight, 0.0F, 0.15F);
            }

            if (var15.blendFieldWeight < 1.0E-4F) {
               var15.blendFieldWeight = 0.0F;
            }

            var15.blendFieldWeight = PZMath.clamp(var15.blendFieldWeight, 0.0F, 1.0F);
         }
      }

    float var16 = var1.getWeight();

      for (int var17 = 0; var17 < var1.m_AnimationTracks.size(); var17++) {
    AnimationTrack var18 = (AnimationTrack)var1.m_AnimationTracks.get(var17);
         var18.BlendDelta = var18.blendFieldWeight * var16;
      }
   }

    void getOrCreateLiveNode(AnimNode var1) {
    LiveAnimNode var2 = this.findLiveNode(var1);
      if (var2 != nullptr) {
         var2.setActive(true);
      } else {
         var2 = LiveAnimNode.alloc(this, var1, this.getDepth());
         if (var1.m_2DBlends.size() > 0) {
    int var3 = 0;

            for (int var4 = var1.m_2DBlends.size(); var3 < var4; var3++) {
    Anim2DBlend var5 = (Anim2DBlend)var1.m_2DBlends.get(var3);
               this.startAnimTrack(var5.m_AnimName, var2);
            }
         } else {
            this.startAnimTrack(var1.m_AnimName, var2);
         }

         var2.setActive(true);
         this.m_liveAnimNodes.push_back(var2);
      }
   }

    LiveAnimNode findLiveNode(AnimNode var1) {
    LiveAnimNode var2 = nullptr;
    int var3 = 0;

      for (int var4 = this.m_liveAnimNodes.size(); var3 < var4; var3++) {
    LiveAnimNode var5 = this.m_liveAnimNodes.get(var3);
         if (!var5.m_TransitioningOut) {
            if (var5.getSourceNode() == var1) {
               var2 = var5;
               break;
            }

            if (var5.getSourceNode().m_State == var1.m_State && var5.getSourceNode().m_Name == var1.m_Name)) {
               var2 = var5;
               break;
            }
         }
      }

    return var2;
   }

    void startAnimTrack(const std::string& var1, LiveAnimNode var2) {
    AnimNode var3 = var2.getSourceNode();
    float var4 = var3.getSpeedScale(this.m_Character);
    float var5 = Rand.Next(0.0F, 1.0F);
    float var6 = var3.m_SpeedScaleRandomMultiplierMin;
    float var7 = var3.m_SpeedScaleRandomMultiplierMax;
    float var8 = PZMath.lerp(var6, var7, var5);
    StartAnimTrackParameters var9 = StartAnimTrackParameters.alloc();
      var9.subLayerBoneWeights = var3.m_SubStateBoneWeights;
      var9.syncTrackingEnabled = var3.m_SyncTrackingEnabled;
      var9.speedScale = var4 * var8;
      var9.initialWeight = var2.getWeight();
      var9.isLooped = var2.isLooped();
      var9.isReversed = var3.m_AnimReverse;
      var9.deferredBoneName = var3.getDeferredBoneName();
      var9.deferredBoneAxis = var3.getDeferredBoneAxis();
      var9.useDeferredRotation = var3.m_useDeferedRotation;
      var9.priority = var3.getPriority();
    AnimationTrack var10 = this.startAnimTrack(var1, var9);
      var9.release();
      if (var10 != nullptr) {
         var10.addListener(var2);
         var2.addMainTrack(var10);
      }
   }

    AnimationTrack startAnimTrack(const std::string& var1, StartAnimTrackParameters var2) {
    AnimationPlayer var3 = this.m_Character.getAnimationPlayer();
      if (!var3.isReady()) {
    return nullptr;
      } else {
    AnimationTrack var4 = var3.play(var1, var2.isLooped);
         if (var4 == nullptr) {
    return nullptr;
         } else {
    SkinningData var5 = var3.getSkinningData();
            if (this.isSubLayer()) {
               var4.setBoneWeights(var2.subLayerBoneWeights);
               var4.initBoneWeights(var5);
            } else {
               var4.setBoneWeights(nullptr);
            }

    SkinningBone var6 = var5.getBone(var2.deferredBoneName);
            if (var6 == nullptr) {
               DebugLog.Animation.error("Deferred bone not found: \"%s\"", new Object[]{var2.deferredBoneName});
            }

            var4.SpeedDelta = var2.speedScale;
            var4.SyncTrackingEnabled = var2.syncTrackingEnabled;
            var4.setDeferredBone(var6, var2.deferredBoneAxis);
            var4.setUseDeferredRotation(var2.useDeferredRotation);
            var4.BlendDelta = var2.initialWeight;
            var4.setLayerIdx(this.getDepth());
            var4.reverse = var2.isReversed;
            var4.priority = var2.priority;
            var4.addListener(this);
    return var4;
         }
      }
   }

    int getDepth() {
      return this.m_parentLayer != nullptr ? this.m_parentLayer.getDepth() + 1 : 0;
   }

    LiveAnimNode getHighestLiveNode() {
      if (this.m_liveAnimNodes.empty()) {
    return nullptr;
      } else {
    LiveAnimNode var1 = this.m_liveAnimNodes.get(0);

         for (int var2 = this.m_liveAnimNodes.size() - 1; var2 >= 0; var2--) {
    LiveAnimNode var3 = this.m_liveAnimNodes.get(var2);
            if (var3.getWeight() > var1.getWeight()) {
               var1 = var3;
            }
         }

    return var1;
      }
   }

    AnimationTrack findSyncTrack(LiveAnimNode var1) {
    AnimationTrack var2 = nullptr;
      if (this.m_parentLayer != nullptr) {
         var2 = this.m_parentLayer.getCurrentSyncTrack();
         if (var2 != nullptr) {
    return var2;
         }
      }

    int var3 = 0;

      for (int var4 = var1.getPlayingTrackCount(); var3 < var4; var3++) {
    AnimationTrack var5 = var1.getPlayingTrackAt(var3);
         if (var5.SyncTrackingEnabled && var5.hasClip() && (var2 == nullptr || var5.BlendDelta > var2.BlendDelta)) {
            var2 = var5;
         }
      }

    return var2;
   }

    std::string getDebugNodeName() {
    std::string var1 = this.m_Character.getAdvancedAnimator().animSet.m_Name;
      if (this.m_State != nullptr) {
         var1 = var1 + "/" + this.m_State.m_Name;
         if (this.m_CurrentNode != nullptr) {
            var1 = var1 + "/" + this.m_CurrentNode.m_Name + ": " + this.m_CurrentNode.m_AnimName;
         } else if (!this.m_liveAnimNodes.empty()) {
            for (int var2 = 0; var2 < this.m_liveAnimNodes.size(); var2++) {
    LiveAnimNode var3 = this.m_liveAnimNodes.get(var2);
               if (this.m_State.m_Nodes.contains(var3.getSourceNode())) {
                  var1 = var1 + "/" + var3.getName();
                  break;
               }
            }
         }
      }

    return var1;
   }

   public List<LiveAnimNode> getLiveAnimNodes() {
      return this.m_liveAnimNodes;
   }

    bool isRecording() {
      return this.m_Character.getAdvancedAnimator().isRecording();
   }

   static {
      s_activeAnimLoopedEvent.m_TimePc = 1.0F;
      s_activeAnimLoopedEvent.m_EventName = "ActiveAnimLooped";
      s_activeNonLoopedAnimFadeOutEvent.m_TimePc = 1.0F;
      s_activeNonLoopedAnimFadeOutEvent.m_EventName = "NonLoopedAnimFadeOut";
      s_activeAnimFinishingEvent.m_Time = AnimEventTime.End;
      s_activeAnimFinishingEvent.m_EventName = "ActiveAnimFinishing";
      s_activeNonLoopedAnimFinishedEvent.m_Time = AnimEventTime.End;
      s_activeNonLoopedAnimFinishedEvent.m_EventName = "ActiveAnimFinished";
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
