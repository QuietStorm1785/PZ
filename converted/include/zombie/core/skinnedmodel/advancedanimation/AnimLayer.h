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
#include "zombie/core/skinnedmodel/animation/AnimationMultiTrack.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/core/skinnedmodel/animation/BoneAxis.h"
#include "zombie/core/skinnedmodel/animation/IAnimListener.h"
#include "zombie/core/skinnedmodel/animation/debug/AnimationPlayerRecorder.h"
#include "zombie/core/skinnedmodel/model/SkinningBone.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AnimLayer {
public:
 const AnimLayer m_parentLayer;
 const IAnimatable m_Character;
 AnimState m_State = nullptr;
 AnimNode m_CurrentNode = nullptr;
 IAnimEventCallback m_AnimEventsCallback;
 LiveAnimNode m_currentSyncNode;
 AnimationTrack m_currentSyncTrack;
 private List<AnimNode> m_reusableAnimNodes = std::make_unique<ArrayList<>>();
 private List<LiveAnimNode> m_liveAnimNodes = std::make_unique<ArrayList<>>();
 static const AnimEvent s_activeAnimLoopedEvent = new AnimEvent();
 static const AnimEvent s_activeNonLoopedAnimFadeOutEvent = new AnimEvent();
 static const AnimEvent s_activeAnimFinishingEvent = new AnimEvent();
 static const AnimEvent s_activeNonLoopedAnimFinishedEvent = new AnimEvent();

 public AnimLayer(IAnimatable character, IAnimEventCallback animEventsCallback) {
 this(nullptr, character, animEventsCallback);
 }

 public AnimLayer(AnimLayer parentLayer, IAnimatable character, IAnimEventCallback animEventsCallback) {
 this->m_parentLayer = parentLayer;
 this->m_Character = character;
 this->m_AnimEventsCallback = animEventsCallback;
 }

 std::string getCurrentStateName() {
 return this->m_State.empty() ? nullptr : this->m_State.m_Name;
 }

 bool hasState() {
 return this->m_State != nullptr;
 }

 bool isStateless() {
 return this->m_State.empty();
 }

 bool isSubLayer() {
 return this->m_parentLayer != nullptr;
 }

 bool isCurrentState(const std::string& stateName) {
 return this->m_State != nullptr && StringUtils == this->m_State.m_Name, stateName);
 }

 AnimationMultiTrack getAnimationTrack() {
 if (this->m_Character.empty()) {
 return nullptr;
 } else {
 AnimationPlayer animationPlayer = this->m_Character.getAnimationPlayer();
 return animationPlayer = = nullptr ? nullptr : animationPlayer.getMultiTrack();
 }
 }

 IAnimationVariableSource getVariableSource() {
 return this->m_Character;
 }

 LiveAnimNode getCurrentSyncNode() {
 return this->m_currentSyncNode;
 }

 AnimationTrack getCurrentSyncTrack() {
 return this->m_currentSyncTrack;
 }

 void onAnimStarted(AnimationTrack track) {
 }

 void onLoopedAnim(AnimationTrack track) {
 this->invokeAnimEvent(track, s_activeAnimLoopedEvent, false);
 }

 void onNonLoopedAnimFadeOut(AnimationTrack track) {
 this->invokeAnimEvent(track, s_activeAnimFinishingEvent, true);
 this->invokeAnimEvent(track, s_activeNonLoopedAnimFadeOutEvent, true);
 }

 void onNonLoopedAnimFinished(AnimationTrack track) {
 this->invokeAnimEvent(track, s_activeAnimFinishingEvent, false);
 this->invokeAnimEvent(track, s_activeNonLoopedAnimFinishedEvent, true);
 }

 void onTrackDestroyed(AnimationTrack track) {
 }

 void invokeAnimEvent(AnimationTrack animationTrack, AnimEvent animEvent, bool boolean0) {
 if (this->m_AnimEventsCallback != nullptr) {
 int int0 = 0;

 for (int int1 = this->m_liveAnimNodes.size(); int0 < int1; int0++) {
 LiveAnimNode liveAnimNode = this->m_liveAnimNodes.get(int0);
 if ((!liveAnimNode.m_TransitioningOut || boolean0)
 && liveAnimNode.getSourceNode().m_State == this->m_State
 && liveAnimNode.m_AnimationTracks.contains(animationTrack) {
 this->invokeAnimEvent(animEvent);
 break;
 }
 }
 }
 }

 void invokeAnimEvent(AnimEvent animEvent) {
 if (this->m_AnimEventsCallback.empty()) {
 DebugLog.Animation.warn("invokeAnimEvent. No listener. %s", animEvent.toDetailsString());
 } else {
 this->m_AnimEventsCallback.OnAnimEvent(this, animEvent);
 }
 }

 std::string GetDebugString() {
 std::string string0 = this->m_Character.getAdvancedAnimator().animSet.m_Name;
 if (this->m_State != nullptr) {
 string0 = string0 + "/" + this->m_State.m_Name;
 if (this->m_CurrentNode != nullptr) {
 string0 = string0 + "/" + this->m_CurrentNode.m_Name + ": " + this->m_CurrentNode.m_AnimName;
 }
 }

 std::string string1 = "State: " + string0;

 for (LiveAnimNode liveAnimNode : this->m_liveAnimNodes) {
 string1 = string1 + "\n Node: " + liveAnimNode.getSourceNode().m_Name;
 }

 AnimationMultiTrack animationMultiTrack = this->getAnimationTrack();
 if (animationMultiTrack != nullptr) {
 string1 = string1 + "\n AnimTrack:";

 for (AnimationTrack animationTrack : animationMultiTrack.getTracks()) {
 string1 = string1 + "\n Anim: " + animationTrack.name + " Weight: " + animationTrack.BlendDelta;
 }
 }

 return string1;
 }

 void Reset() {
 AnimationMultiTrack animationMultiTrack = this->getAnimationTrack();

 for (int int0 = this->m_liveAnimNodes.size() - 1; int0 >= 0; int0--) {
 LiveAnimNode liveAnimNode = this->m_liveAnimNodes.get(int0);
 liveAnimNode.setActive(false);
 if (animationMultiTrack != nullptr) {
 animationMultiTrack.removeTracks(liveAnimNode.m_AnimationTracks);
 }

 this->m_liveAnimNodes.remove(int0).release();
 }

 this->m_State = nullptr;
 }

 bool TransitionTo(AnimState newState, bool force) {
 AnimationMultiTrack animationMultiTrack = this->getAnimationTrack();
 if (animationMultiTrack.empty()) {
 if (this->m_Character.empty()) {
 DebugLog.General.error("AnimationTrack is nullptr. Character is nullptr.");
 this->m_State = nullptr;
 return false;
 } else if (this->m_Character.getAnimationPlayer() == nullptr) {
 DebugLog.General.error("AnimationTrack is nullptr. Character ModelInstance.AnimPlayer is nullptr.");
 this->m_State = nullptr;
 return false;
 } else {
 DebugLog.General.error("AnimationTrack is nullptr. Unknown reason.");
 return false;
 }
 } else if (newState == this->m_State && !force) {
 return true;
 } else {
 if (DebugOptions.instance.Animation.AnimLayer.LogStateChanges.getValue()) {
 std::string string0 = this->m_parentLayer == nullptr ? "" : AnimState.getStateName(this->m_parentLayer.m_State) + " | ";
 std::string string1 = String.format("State: %s%s => %s", string0, AnimState.getStateName(this->m_State), AnimState.getStateName(newState);
 DebugLog.General.debugln(string1);
 if (this->m_Character instanceof IsoGameCharacter) {
 ((IsoGameCharacter)this->m_Character).setSayLine(string1);
 }
 }

 this->m_State = newState;

 for (int int0 = 0; int0 < this->m_liveAnimNodes.size(); int0++) {
 LiveAnimNode liveAnimNode = this->m_liveAnimNodes.get(int0);
 liveAnimNode.m_TransitioningOut = true;
 }

 return true;
 }
 }

 void Update() {
 GameProfiler.getInstance().invokeAndMeasure("AnimLayer.Update", this, AnimLayer::updateInternal);
 }

 void updateInternal() {
 float float0 = GameTime.instance.getTimeDelta();
 this->removeFadedOutNodes();
 this->updateNodeActiveFlags();
 LiveAnimNode liveAnimNode0 = this->getHighestLiveNode();
 this->m_currentSyncNode = liveAnimNode0;
 this->m_currentSyncTrack = nullptr;
 if (liveAnimNode0 != nullptr) {
 int int0 = 0;

 for (int int1 = this->m_liveAnimNodes.size(); int0 < int1; int0++) {
 LiveAnimNode liveAnimNode1 = this->m_liveAnimNodes.get(int0);
 liveAnimNode1.update(float0);
 }

 IAnimatable iAnimatable = this->m_Character;
 this->updateMaximumTwist(iAnimatable);
 boolean boolean0 = DebugOptions.instance.Animation.AnimLayer.AllowAnimNodeOverride.getValue()
 && iAnimatable.getVariableBoolean("dbgForceAnim")
 && iAnimatable.getVariableBoolean("dbgForceAnimScalars");
 std::string string0 = boolean0 ? iAnimatable.getVariableString("dbgForceAnimNodeName") : nullptr;
 AnimationTrack animationTrack0 = this->findSyncTrack(liveAnimNode0);
 this->m_currentSyncTrack = animationTrack0;
 float float1 = animationTrack0 != nullptr ? animationTrack0.getCurrentTimeFraction() : -1.0F;
 int int2 = 0;

 for (int int3 = this->m_liveAnimNodes.size(); int2 < int3; int2++) {
 LiveAnimNode liveAnimNode2 = this->m_liveAnimNodes.get(int2);
 float float2 = 1.0F;
 int int4 = 0;

 for (int int5 = liveAnimNode2.getPlayingTrackCount(); int4 < int5; int4++) {
 AnimationTrack animationTrack1 = liveAnimNode2.getPlayingTrackAt(int4);
 if (animationTrack1.IsPlaying) {
 if (animationTrack0 != nullptr && animationTrack1.SyncTrackingEnabled && animationTrack1.isLooping() && animationTrack1 != animationTrack0
 )
 {
 animationTrack1.moveCurrentTimeValueToFraction(float1);
 }

 if (animationTrack1.name == liveAnimNode2.getSourceNode().m_AnimName) {
 float2 = animationTrack1.getDuration();
 liveAnimNode2.m_NodeAnimTime = animationTrack1.getCurrentTimeValue();
 }
 }
 }

 if (this->m_AnimEventsCallback != nullptr && liveAnimNode2.getSourceNode().m_Events.size() > 0) {
 float float3 = liveAnimNode2.m_NodeAnimTime / float2;
 float float4 = liveAnimNode2.m_PrevNodeAnimTime / float2;
 std::vector list = liveAnimNode2.getSourceNode().m_Events;
 int int6 = 0;

 for (int int7 = list.size(); int6 < int7; int6++) {
 AnimEvent animEvent = (AnimEvent)list.get(int6);
 if (animEvent.m_Time == AnimEvent.AnimEventTime.Percentage) {
 float float5 = animEvent.m_TimePc;
 if (float4 < float5 && float5 <= float3) {
 this->invokeAnimEvent(animEvent);
 } else {
 if (!liveAnimNode2.isLooped() && float3 < float5) {
 break;
 }

 if (liveAnimNode2.isLooped() && float4 > float3) {
 if (float4 < float5 && float5 <= float3 + 1.0F) {
 this->invokeAnimEvent(animEvent);
 } else if (float4 > float5 && float5 <= float3) {
 this->invokeAnimEvent(animEvent);
 }
 }
 }
 }
 }
 }

 if (liveAnimNode2.getPlayingTrackCount() != 0) {
 bool boolean1 = boolean0 && StringUtils.equalsIgnoreCase(liveAnimNode2.getSourceNode().m_Name, string0);
 std::string string1 = boolean1 ? "dbgForceScalar" : liveAnimNode2.getSourceNode().m_Scalar;
 std::string string2 = boolean1 ? "dbgForceScalar2" : liveAnimNode2.getSourceNode().m_Scalar2;
 float float6 = liveAnimNode2.getTransitionInWeight();
 liveAnimNode2.setTransitionInBlendDelta(float6);
 if (liveAnimNode2.m_AnimationTracks.size() > 1) {
 float6 = iAnimatable.getVariableFloat(string1, 0.0F);
 float float7 = iAnimatable.getVariableFloat(string2, 0.0F);
 this->applyBlendField(liveAnimNode2, float6, float7);
 } else if (!liveAnimNode2.m_AnimationTracks.empty()) {
 float6 = liveAnimNode2.getWeight();
 float float8 = iAnimatable.getVariableFloat(string1, 1.0F);
 liveAnimNode2.m_AnimationTracks.get(0).BlendDelta = float6 * Math.abs(float8);
 }
 }
 }

 if (this->isRecording()) {
 this->logBlendWeights();
 this->logCurrentState();
 }
 }
 }

 void updateMaximumTwist(IAnimationVariableSource iAnimationVariableSource) {
 IAnimationVariableSlot iAnimationVariableSlot = iAnimationVariableSource.getVariable("maxTwist");
 if (iAnimationVariableSlot != nullptr) {
 float float0 = iAnimationVariableSlot.getValueFloat();
 float float1 = 0.0F;
 float float2 = 1.0F;

 for (int int0 = this->m_liveAnimNodes.size() - 1; int0 >= 0; int0--) {
 LiveAnimNode liveAnimNode = this->m_liveAnimNodes.get(int0);
 float float3 = liveAnimNode.getWeight();
 if (float2 <= 0.0F) {
 break;
 }

 float float4 = PZMath.clamp(float3, 0.0F, float2);
 float2 -= float4;
 float float5 = PZMath.clamp(liveAnimNode.getSourceNode().m_maxTorsoTwist, 0.0F, 70.0F);
 float1 += float5 * float4;
 }

 if (float2 > 0.0F) {
 float1 += float0 * float2;
 }

 iAnimationVariableSlot.setValue(float1);
 }
 }

 void updateNodeActiveFlags() {
 for (int int0 = 0; int0 < this->m_liveAnimNodes.size(); int0++) {
 LiveAnimNode liveAnimNode = this->m_liveAnimNodes.get(int0);
 liveAnimNode.setActive(false);
 }

 AnimState animState = this->m_State;
 IAnimatable iAnimatable = this->m_Character;
 if (animState != nullptr && !iAnimatable.getVariableBoolean("AnimLocked")) {
 std::vector list = animState.getAnimNodes(iAnimatable, this->m_reusableAnimNodes);
 int int1 = 0;

 for (int int2 = list.size(); int1 < int2; int1++) {
 AnimNode animNode = (AnimNode)list.get(int1);
 this->getOrCreateLiveNode(animNode);
 }
 }

 this->updateNewNodeTransitions();
 }

 void updateNewNodeTransitions() {
 GameProfiler.getInstance().invokeAndMeasure("updateNewNodeTransitions", this, AnimLayer::updateNewNodeTransitionsInternal);
 }

 void updateNewNodeTransitionsInternal() {
 IAnimatable iAnimatable = this->m_Character;
 int int0 = 0;

 for (int int1 = this->m_liveAnimNodes.size(); int0 < int1; int0++) {
 LiveAnimNode liveAnimNode0 = this->m_liveAnimNodes.get(int0);
 if (liveAnimNode0.isNew() && liveAnimNode0.wasActivated()) {
 LiveAnimNode liveAnimNode1 = this->findTransitionToNewNode(liveAnimNode0, false);
 if (liveAnimNode1 != nullptr) {
 AnimTransition animTransition = liveAnimNode1.findTransitionTo(iAnimatable, liveAnimNode0.getName());
 float float0 = animTransition.m_speedScale;
 if (float0 == Float.POSITIVE_INFINITY) {
 float0 = liveAnimNode0.getSpeedScale(this->m_Character);
 }

 AnimationTrack animationTrack = nullptr;
 if (!StringUtils.isNullOrWhitespace(animTransition.m_AnimName) {
 AnimLayer.StartAnimTrackParameters startAnimTrackParameters = AnimLayer.StartAnimTrackParameters.alloc();
 startAnimTrackParameters.subLayerBoneWeights = liveAnimNode1.getSubStateBoneWeights();
 startAnimTrackParameters.speedScale = float0;
 startAnimTrackParameters.deferredBoneName = liveAnimNode1.getDeferredBoneName();
 startAnimTrackParameters.deferredBoneAxis = liveAnimNode1.getDeferredBoneAxis();
 startAnimTrackParameters.priority = liveAnimNode1.getPriority();
 animationTrack = this->startAnimTrack(animTransition.m_AnimName, startAnimTrackParameters);
 startAnimTrackParameters.release();
 if (animationTrack.empty()) {
 if (DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation
 .println(
 " TransitionTo failed to play transition track: %s -> %s -> %s",
 liveAnimNode1.getName(),
 animTransition.m_AnimName,
 liveAnimNode0.getName()
 );
 }
 continue;
 }

 if (DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation
 .println(" TransitionTo found: %s -> %s -> %s", liveAnimNode1.getName(), animTransition.m_AnimName, liveAnimNode0.getName());
 }
 } else if (DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation.println(" TransitionTo found: %s -> <no anim> -> %s", liveAnimNode1.getName(), liveAnimNode0.getName());
 }

 liveAnimNode0.startTransitionIn(liveAnimNode1, animTransition, animationTrack);
 liveAnimNode1.setTransitionOut(animTransition);
 }
 }
 }
 }

 LiveAnimNode findTransitionToNewNode(LiveAnimNode newNode, bool isSubNode) {
 LiveAnimNode liveAnimNode0 = nullptr;
 int int0 = 0;

 for (int int1 = this->m_liveAnimNodes.size(); int0 < int1; int0++) {
 LiveAnimNode liveAnimNode1 = this->m_liveAnimNodes.get(int0);
 if (liveAnimNode1 != newNode && (isSubNode || liveAnimNode1.wasDeactivated())) {
 AnimNode animNode = liveAnimNode1.getSourceNode();
 AnimTransition animTransition = animNode.findTransitionTo(this->m_Character, newNode.getName());
 if (animTransition != nullptr) {
 liveAnimNode0 = liveAnimNode1;
 break;
 }
 }
 }

 if (liveAnimNode0.empty() && this->isSubLayer()) {
 liveAnimNode0 = this->m_parentLayer.findTransitionToNewNode(newNode, true);
 }

 return liveAnimNode0;
 }

 void removeFadedOutNodes() {
 for (int int0 = this->m_liveAnimNodes.size() - 1; int0 >= 0; int0--) {
 LiveAnimNode liveAnimNode = this->m_liveAnimNodes.get(int0);
 if (!liveAnimNode.isActive()
 && (!liveAnimNode.isTransitioningIn() || !(liveAnimNode.getTransitionInWeight() > 0.01F)
 && !(liveAnimNode.getWeight() > 0.01F) {
 this->removeLiveNodeAt(int0);
 }
 }
 }

 void render() {
 IAnimatable iAnimatable = this->m_Character;
 boolean boolean0 = DebugOptions.instance.Animation.AnimLayer.AllowAnimNodeOverride.getValue()
 && iAnimatable.getVariableBoolean("dbgForceAnim")
 && iAnimatable.getVariableBoolean("dbgForceAnimScalars");
 std::string string0 = boolean0 ? iAnimatable.getVariableString("dbgForceAnimNodeName") : nullptr;
 int int0 = 0;

 for (int int1 = this->m_liveAnimNodes.size(); int0 < int1; int0++) {
 LiveAnimNode liveAnimNode = this->m_liveAnimNodes.get(int0);
 if (liveAnimNode.m_AnimationTracks.size() > 1) {
 bool boolean1 = boolean0 && StringUtils.equalsIgnoreCase(liveAnimNode.getSourceNode().m_Name, string0);
 std::string string1 = boolean1 ? "dbgForceScalar" : liveAnimNode.getSourceNode().m_Scalar;
 std::string string2 = boolean1 ? "dbgForceScalar2" : liveAnimNode.getSourceNode().m_Scalar2;
 float float0 = iAnimatable.getVariableFloat(string1, 0.0F);
 float float1 = iAnimatable.getVariableFloat(string2, 0.0F);
 if (liveAnimNode.isActive()) {
 liveAnimNode.getSourceNode().m_picker.render(float0, float1);
 }
 }
 }
 }

 void logBlendWeights() {
 AnimationPlayerRecorder animationPlayerRecorder = this->m_Character.getAnimationPlayer().getRecorder();
 int int0 = 0;

 for (int int1 = this->m_liveAnimNodes.size(); int0 < int1; int0++) {
 LiveAnimNode liveAnimNode = this->m_liveAnimNodes.get(int0);
 animationPlayerRecorder.logAnimNode(liveAnimNode);
 }
 }

 void logCurrentState() {
 AnimationPlayerRecorder animationPlayerRecorder = this->m_Character.getAnimationPlayer().getRecorder();
 animationPlayerRecorder.logAnimState(this->m_State);
 }

 void removeLiveNodeAt(int int0) {
 LiveAnimNode liveAnimNode = this->m_liveAnimNodes.get(int0);
 AnimationMultiTrack animationMultiTrack = this->getAnimationTrack();
 animationMultiTrack.removeTracks(liveAnimNode.m_AnimationTracks);
 animationMultiTrack.removeTrack(liveAnimNode.getTransitionInTrack());
 this->m_liveAnimNodes.remove(int0).release();
 }

 void applyBlendField(LiveAnimNode liveAnimNode, float float0, float float1) {
 if (liveAnimNode.isActive()) {
 AnimNode animNode = liveAnimNode.getSourceNode();
 Anim2DBlendPicker anim2DBlendPicker = animNode.m_picker;
 Anim2DBlendPicker.PickResults pickResults = anim2DBlendPicker.Pick(float0, float1);
 Anim2DBlend anim2DBlend0 = pickResults.node1;
 Anim2DBlend anim2DBlend1 = pickResults.node2;
 Anim2DBlend anim2DBlend2 = pickResults.node3;
 if (Float.isNaN(pickResults.scale1) {
 pickResults.scale1 = 0.5F;
 }

 if (Float.isNaN(pickResults.scale2) {
 pickResults.scale2 = 0.5F;
 }

 if (Float.isNaN(pickResults.scale3) {
 pickResults.scale3 = 0.5F;
 }

 float float2 = pickResults.scale1;
 float float3 = pickResults.scale2;
 float float4 = pickResults.scale3;

 for (int int0 = 0; int0 < liveAnimNode.m_AnimationTracks.size(); int0++) {
 Anim2DBlend anim2DBlend3 = animNode.m_2DBlends.get(int0);
 AnimationTrack animationTrack0 = liveAnimNode.m_AnimationTracks.get(int0);
 if (anim2DBlend3 == anim2DBlend0) {
 animationTrack0.blendFieldWeight = AnimationPlayer.lerpBlendWeight(animationTrack0.blendFieldWeight, float2, 0.15F);
 } else if (anim2DBlend3 == anim2DBlend1) {
 animationTrack0.blendFieldWeight = AnimationPlayer.lerpBlendWeight(animationTrack0.blendFieldWeight, float3, 0.15F);
 } else if (anim2DBlend3 == anim2DBlend2) {
 animationTrack0.blendFieldWeight = AnimationPlayer.lerpBlendWeight(animationTrack0.blendFieldWeight, float4, 0.15F);
 } else {
 animationTrack0.blendFieldWeight = AnimationPlayer.lerpBlendWeight(animationTrack0.blendFieldWeight, 0.0F, 0.15F);
 }

 if (animationTrack0.blendFieldWeight < 1.0E-4F) {
 animationTrack0.blendFieldWeight = 0.0F;
 }

 animationTrack0.blendFieldWeight = PZMath.clamp(animationTrack0.blendFieldWeight, 0.0F, 1.0F);
 }
 }

 float float5 = liveAnimNode.getWeight();

 for (int int1 = 0; int1 < liveAnimNode.m_AnimationTracks.size(); int1++) {
 AnimationTrack animationTrack1 = liveAnimNode.m_AnimationTracks.get(int1);
 animationTrack1.BlendDelta = animationTrack1.blendFieldWeight * float5;
 }
 }

 void getOrCreateLiveNode(AnimNode animNode) {
 LiveAnimNode liveAnimNode = this->findLiveNode(animNode);
 if (liveAnimNode != nullptr) {
 liveAnimNode.setActive(true);
 } else {
 liveAnimNode = LiveAnimNode.alloc(this, animNode, this->getDepth());
 if (animNode.m_2DBlends.size() > 0) {
 int int0 = 0;

 for (int int1 = animNode.m_2DBlends.size(); int0 < int1; int0++) {
 Anim2DBlend anim2DBlend = animNode.m_2DBlends.get(int0);
 this->startAnimTrack(anim2DBlend.m_AnimName, liveAnimNode);
 }
 } else {
 this->startAnimTrack(animNode.m_AnimName, liveAnimNode);
 }

 liveAnimNode.setActive(true);
 this->m_liveAnimNodes.add(liveAnimNode);
 }
 }

 LiveAnimNode findLiveNode(AnimNode animNode) {
 LiveAnimNode liveAnimNode0 = nullptr;
 int int0 = 0;

 for (int int1 = this->m_liveAnimNodes.size(); int0 < int1; int0++) {
 LiveAnimNode liveAnimNode1 = this->m_liveAnimNodes.get(int0);
 if (!liveAnimNode1.m_TransitioningOut) {
 if (liveAnimNode1.getSourceNode() == animNode) {
 liveAnimNode0 = liveAnimNode1;
 break;
 }

 if (liveAnimNode1.getSourceNode().m_State == animNode.m_State && liveAnimNode1.getSourceNode().m_Name == animNode.m_Name) {
 liveAnimNode0 = liveAnimNode1;
 break;
 }
 }
 }

 return liveAnimNode0;
 }

 void startAnimTrack(const std::string& string, LiveAnimNode liveAnimNode) {
 AnimNode animNode = liveAnimNode.getSourceNode();
 float float0 = animNode.getSpeedScale(this->m_Character);
 float float1 = Rand.Next(0.0F, 1.0F);
 float float2 = animNode.m_SpeedScaleRandomMultiplierMin;
 float float3 = animNode.m_SpeedScaleRandomMultiplierMax;
 float float4 = PZMath.lerp(float2, float3, float1);
 AnimLayer.StartAnimTrackParameters startAnimTrackParameters = AnimLayer.StartAnimTrackParameters.alloc();
 startAnimTrackParameters.subLayerBoneWeights = animNode.m_SubStateBoneWeights;
 startAnimTrackParameters.syncTrackingEnabled = animNode.m_SyncTrackingEnabled;
 startAnimTrackParameters.speedScale = float0 * float4;
 startAnimTrackParameters.initialWeight = liveAnimNode.getWeight();
 startAnimTrackParameters.isLooped = liveAnimNode.isLooped();
 startAnimTrackParameters.isReversed = animNode.m_AnimReverse;
 startAnimTrackParameters.deferredBoneName = animNode.getDeferredBoneName();
 startAnimTrackParameters.deferredBoneAxis = animNode.getDeferredBoneAxis();
 startAnimTrackParameters.useDeferredRotation = animNode.m_useDeferedRotation;
 startAnimTrackParameters.priority = animNode.getPriority();
 AnimationTrack animationTrack = this->startAnimTrack(string, startAnimTrackParameters);
 startAnimTrackParameters.release();
 if (animationTrack != nullptr) {
 animationTrack.addListener(liveAnimNode);
 liveAnimNode.addMainTrack(animationTrack);
 }
 }

 AnimationTrack startAnimTrack(const std::string& string, AnimLayer.StartAnimTrackParameters startAnimTrackParameters) {
 AnimationPlayer animationPlayer = this->m_Character.getAnimationPlayer();
 if (!animationPlayer.isReady()) {
 return nullptr;
 } else {
 AnimationTrack animationTrack = animationPlayer.play(string, startAnimTrackParameters.isLooped);
 if (animationTrack.empty()) {
 return nullptr;
 } else {
 SkinningData skinningData = animationPlayer.getSkinningData();
 if (this->isSubLayer()) {
 animationTrack.setBoneWeights(startAnimTrackParameters.subLayerBoneWeights);
 animationTrack.initBoneWeights(skinningData);
 } else {
 animationTrack.setBoneWeights(nullptr);
 }

 SkinningBone skinningBone = skinningData.getBone(startAnimTrackParameters.deferredBoneName);
 if (skinningBone.empty()) {
 DebugLog.Animation.error("Deferred bone not found: \"%s\"", startAnimTrackParameters.deferredBoneName);
 }

 animationTrack.SpeedDelta = startAnimTrackParameters.speedScale;
 animationTrack.SyncTrackingEnabled = startAnimTrackParameters.syncTrackingEnabled;
 animationTrack.setDeferredBone(skinningBone, startAnimTrackParameters.deferredBoneAxis);
 animationTrack.setUseDeferredRotation(startAnimTrackParameters.useDeferredRotation);
 animationTrack.BlendDelta = startAnimTrackParameters.initialWeight;
 animationTrack.setLayerIdx(this->getDepth());
 animationTrack.reverse = startAnimTrackParameters.isReversed;
 animationTrack.priority = startAnimTrackParameters.priority;
 animationTrack.addListener(this);
 return animationTrack;
 }
 }
 }

 /**
 * The layer's depth, how many layer ancestors (parent, grandparent, great-grandparent, etc) does this layer have.
 */
 int getDepth() {
 return this->m_parentLayer != nullptr ? this->m_parentLayer.getDepth() + 1 : 0;
 }

 LiveAnimNode getHighestLiveNode() {
 if (this->m_liveAnimNodes.empty()) {
 return nullptr;
 } else {
 LiveAnimNode liveAnimNode0 = this->m_liveAnimNodes.get(0);

 for (int int0 = this->m_liveAnimNodes.size() - 1; int0 >= 0; int0--) {
 LiveAnimNode liveAnimNode1 = this->m_liveAnimNodes.get(int0);
 if (liveAnimNode1.getWeight() > liveAnimNode0.getWeight()) {
 liveAnimNode0 = liveAnimNode1;
 }
 }

 return liveAnimNode0;
 }
 }

 AnimationTrack findSyncTrack(LiveAnimNode liveAnimNode) {
 AnimationTrack animationTrack0 = nullptr;
 if (this->m_parentLayer != nullptr) {
 animationTrack0 = this->m_parentLayer.getCurrentSyncTrack();
 if (animationTrack0 != nullptr) {
 return animationTrack0;
 }
 }

 int int0 = 0;

 for (int int1 = liveAnimNode.getPlayingTrackCount(); int0 < int1; int0++) {
 AnimationTrack animationTrack1 = liveAnimNode.getPlayingTrackAt(int0);
 if (animationTrack1.SyncTrackingEnabled
 && animationTrack1.hasClip()
 && (animationTrack0.empty() || animationTrack1.BlendDelta > animationTrack0.BlendDelta) {
 animationTrack0 = animationTrack1;
 }
 }

 return animationTrack0;
 }

 std::string getDebugNodeName() {
 std::string string = this->m_Character.getAdvancedAnimator().animSet.m_Name;
 if (this->m_State != nullptr) {
 string = string + "/" + this->m_State.m_Name;
 if (this->m_CurrentNode != nullptr) {
 string = string + "/" + this->m_CurrentNode.m_Name + ": " + this->m_CurrentNode.m_AnimName;
 } else if (!this->m_liveAnimNodes.empty()) {
 for (int int0 = 0; int0 < this->m_liveAnimNodes.size(); int0++) {
 LiveAnimNode liveAnimNode = this->m_liveAnimNodes.get(int0);
 if (this->m_State.m_Nodes.contains(liveAnimNode.getSourceNode())) {
 string = string + "/" + liveAnimNode.getName();
 break;
 }
 }
 }
 }

 return string;
 }

 public List<LiveAnimNode> getLiveAnimNodes() {
 return this->m_liveAnimNodes;
 }

 bool isRecording() {
 return this->m_Character.getAdvancedAnimator().isRecording();
 }

 static {
 s_activeAnimLoopedEvent.m_TimePc = 1.0F;
 s_activeAnimLoopedEvent.m_EventName = "ActiveAnimLooped";
 s_activeNonLoopedAnimFadeOutEvent.m_TimePc = 1.0F;
 s_activeNonLoopedAnimFadeOutEvent.m_EventName = "NonLoopedAnimFadeOut";
 s_activeAnimFinishingEvent.m_Time = AnimEvent.AnimEventTime.End;
 s_activeAnimFinishingEvent.m_EventName = "ActiveAnimFinishing";
 s_activeNonLoopedAnimFinishedEvent.m_Time = AnimEvent.AnimEventTime.End;
 s_activeNonLoopedAnimFinishedEvent.m_EventName = "ActiveAnimFinished";
 }

 private static class StartAnimTrackParameters extends PooledObject {
 int priority;
 List<AnimBoneWeight> subLayerBoneWeights;
 bool syncTrackingEnabled;
 float speedScale;
 float initialWeight;
 bool isLooped;
 bool isReversed;
 std::string deferredBoneName;
 BoneAxis deferredBoneAxis;
 bool useDeferredRotation;
 private static Pool<AnimLayer.StartAnimTrackParameters> s_pool = new Pool<>(AnimLayer.StartAnimTrackParameters::new);

 void reset() {
 this->priority = 0;
 this->subLayerBoneWeights = nullptr;
 this->syncTrackingEnabled = false;
 this->speedScale = 1.0F;
 this->initialWeight = 0.0F;
 this->isLooped = false;
 this->isReversed = false;
 this->deferredBoneName = nullptr;
 this->deferredBoneAxis = BoneAxis.Y;
 this->useDeferredRotation = false;
 }

 void onReleased() {
 this->reset();
 }

 protected StartAnimTrackParameters() {
 }

 public static AnimLayer.StartAnimTrackParameters alloc() {
 return s_pool.alloc();
 }
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
