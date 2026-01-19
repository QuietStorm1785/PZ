#pragma once
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/core/skinnedmodel/animation/BoneAxis.h"
#include "zombie/core/skinnedmodel/animation/IAnimListener.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * The Live version of an AnimNode The AnimNode represents the data. The
 * LiveAnimNode represents the playback of said data, its blend weights, timing,
 * transitions etc.
 */
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
private
 LiveAnimNode.TransitionIn m_transitionIn =
 new LiveAnimNode.TransitionIn();
 List<AnimationTrack> m_AnimationTracks =
 std::make_unique<ArrayList<>>();
 float m_NodeAnimTime;
 float m_PrevNodeAnimTime;
 bool m_blendingIn;
 bool m_blendingOut;
 AnimTransition m_transitionOut;
private
 static Pool<LiveAnimNode> s_pool = new Pool<>(LiveAnimNode::new);

protected
 LiveAnimNode() {}

 static LiveAnimNode alloc(AnimLayer animLayer, AnimNode sourceNode,
 int layerIdx) {
 LiveAnimNode liveAnimNode = s_pool.alloc();
 liveAnimNode.reset();
 liveAnimNode.m_sourceNode = sourceNode;
 liveAnimNode.m_animLayer = animLayer;
 liveAnimNode.m_layerIdx = layerIdx;
 return liveAnimNode;
 }

 void reset() {
 this->m_sourceNode = nullptr;
 this->m_animLayer = nullptr;
 this->m_active = false;
 this->m_wasActive = false;
 this->m_TransitioningOut = false;
 this->m_Weight = 0.0F;
 this->m_RawWeight = 0.0F;
 this->m_isNew = true;
 this->m_layerIdx = -1;
 this->m_transitionIn.reset();
 this->m_AnimationTracks.clear();
 this->m_NodeAnimTime = 0.0F;
 this->m_PrevNodeAnimTime = 0.0F;
 this->m_blendingIn = false;
 this->m_blendingOut = false;
 this->m_transitionOut = nullptr;
 }

 void onReleased() { this->reset(); }

 std::string getName() { return this->m_sourceNode.m_Name; }

 bool isTransitioningIn() {
 return this->m_transitionIn.m_active &&
 this->m_transitionIn.m_track != nullptr;
 }

 void startTransitionIn(LiveAnimNode transitionFrom,
 AnimTransition transitionIn, AnimationTrack track) {
 this->startTransitionIn(transitionFrom.getSourceNode(), transitionIn, track);
 }

 void startTransitionIn(AnimNode transitionFrom, AnimTransition transitionIn,
 AnimationTrack track) {
 this->m_transitionIn.m_active = track != nullptr;
 this->m_transitionIn.m_transitionedFrom = transitionFrom.m_Name;
 this->m_transitionIn.m_data = transitionIn;
 this->m_transitionIn.m_track = track;
 this->m_transitionIn.m_weight = 0.0F;
 this->m_transitionIn.m_rawWeight = 0.0F;
 this->m_transitionIn.m_blendingIn = true;
 this->m_transitionIn.m_blendingOut = false;
 this->m_transitionIn.m_time = 0.0F;
 if (this->m_transitionIn.m_track != nullptr) {
 this->m_transitionIn.m_track.addListener(this);
 }

 this->setMainTracksPlaying(false);
 }

 void setTransitionOut(AnimTransition transitionOut) {
 this->m_transitionOut = transitionOut;
 }

 void update(float timeDelta) {
 this->m_isNew = false;
 if (this->m_active != this->m_wasActive) {
 this->m_blendingIn = this->m_active;
 this->m_blendingOut = !this->m_active;
 if (this->m_transitionIn.m_active) {
 this->m_transitionIn.m_blendingIn = this->m_active;
 this->m_transitionIn.m_blendingOut = !this->m_active;
 }

 this->m_wasActive = this->m_active;
 }

 bool boolean0 = this->isMainAnimActive();
 if (this->isTransitioningIn()) {
 this->updateTransitioningIn(timeDelta);
 }

 bool boolean1 = this->isMainAnimActive();
 if (boolean1) {
 if (this->m_blendingOut && this->m_sourceNode.m_StopAnimOnExit) {
 this->setMainTracksPlaying(false);
 } else {
 this->setMainTracksPlaying(true);
 }
 } else {
 this->setMainTracksPlaying(false);
 }

 if (boolean1) {
 bool boolean2 = !boolean0;
 if (boolean2 && this->isLooped()) {
 float float0 = this->getMainInitialRewindTime();
 PZArrayUtil.forEach(
 this->m_AnimationTracks,
 Lambda.consumer(float0, AnimationTrack::scaledRewind);
 }

 if (this->m_blendingIn) {
 this->updateBlendingIn(timeDelta);
 } else if (this->m_blendingOut) {
 this->updateBlendingOut(timeDelta);
 }

 this->m_PrevNodeAnimTime = this->m_NodeAnimTime;
 this->m_NodeAnimTime += timeDelta;
 if (!this->m_transitionIn.m_active &&
 this->m_transitionIn.m_track != nullptr &&
 this->m_transitionIn.m_track.BlendDelta <= 0.0F) {
 this->m_animLayer.getAnimationTrack().removeTrack(
 this->m_transitionIn.m_track);
 this->m_transitionIn.reset();
 }
 }
 }

 void updateTransitioningIn(float float5) {
 float float0 = this->m_transitionIn.m_track.SpeedDelta;
 float float1 = this->m_transitionIn.m_track.getDuration();
 this->m_transitionIn.m_time =
 this->m_transitionIn.m_track.getCurrentTimeValue();
 if (this->m_transitionIn.m_time >= float1) {
 this->m_transitionIn.m_active = false;
 this->m_transitionIn.m_weight = 0.0F;
 } else {
 if (!this->m_transitionIn.m_blendingOut) {
 bool boolean0 =
 AnimCondition.pass(this->m_animLayer.getVariableSource(),
 this->m_transitionIn.m_data.m_Conditions);
 if (!boolean0) {
 this->m_transitionIn.m_blendingIn = false;
 this->m_transitionIn.m_blendingOut = true;
 }
 }

 float float2 = this->getTransitionInBlendOutTime() * float0;
 if (this->m_transitionIn.m_time >= float1 - float2) {
 this->m_transitionIn.m_blendingIn = false;
 this->m_transitionIn.m_blendingOut = true;
 }

 if (this->m_transitionIn.m_blendingIn) {
 float float3 = this->getTransitionInBlendInTime() * float0;
 float float4 = this->incrementBlendTime(this->m_transitionIn.m_rawWeight,
 float3, float5 * float0);
 float float6 = PZMath.clamp(float4 / float3, 0.0F, 1.0F);
 this->m_transitionIn.m_rawWeight = float6;
 this->m_transitionIn.m_weight = PZMath.lerpFunc_EaseOutInQuad(float6);
 this->m_transitionIn.m_blendingIn = float4 < float3;
 this->m_transitionIn.m_active = float4 < float1;
 }

 if (this->m_transitionIn.m_blendingOut) {
 float float7 = this->getTransitionInBlendOutTime() * float0;
 float float8 = this->incrementBlendTime(
 1.0F - this->m_transitionIn.m_rawWeight, float7, float5 * float0);
 float float9 = PZMath.clamp(1.0F - float8 / float7, 0.0F, 1.0F);
 this->m_transitionIn.m_rawWeight = float9;
 this->m_transitionIn.m_weight = PZMath.lerpFunc_EaseOutInQuad(float9);
 this->m_transitionIn.m_blendingOut = float8 < float7;
 this->m_transitionIn.m_active = this->m_transitionIn.m_blendingOut;
 }
 }
 }

 void addMainTrack(AnimationTrack track) {
 if (!this->isLooped() && !this->m_sourceNode.m_StopAnimOnExit &&
 this->m_sourceNode.m_EarlyTransitionOut) {
 float float0 = this->getBlendOutTime();
 if (float0 > 0.0F && Float.isFinite(float0) {
 track.earlyBlendOutTime = float0;
 track.triggerOnNonLoopedAnimFadeOutEvent = true;
 }
 }

 this->m_AnimationTracks.add(track);
 }

 void setMainTracksPlaying(bool boolean0) {
 Lambda.forEachFrom(PZArrayUtil::forEach, this->m_AnimationTracks, boolean0,
 (animationTrack, boolean0x)->animationTrack.IsPlaying =
 boolean0x);
 }

 void updateBlendingIn(float float2) {
 float float0 = this->getBlendInTime();
 if (float0 <= 0.0F) {
 this->m_Weight = 1.0F;
 this->m_RawWeight = 1.0F;
 this->m_blendingIn = false;
 } else {
 float float1 = this->incrementBlendTime(this->m_RawWeight, float0, float2);
 float float3 = PZMath.clamp(float1 / float0, 0.0F, 1.0F);
 this->m_RawWeight = float3;
 this->m_Weight = PZMath.lerpFunc_EaseOutInQuad(float3);
 this->m_blendingIn = float1 < float0;
 }
 }

 void updateBlendingOut(float float2) {
 float float0 = this->getBlendOutTime();
 if (float0 <= 0.0F) {
 this->m_Weight = 0.0F;
 this->m_RawWeight = 0.0F;
 this->m_blendingOut = false;
 } else {
 float float1 =
 this->incrementBlendTime(1.0F - this->m_RawWeight, float0, float2);
 float float3 = PZMath.clamp(1.0F - float1 / float0, 0.0F, 1.0F);
 this->m_RawWeight = float3;
 this->m_Weight = PZMath.lerpFunc_EaseOutInQuad(float3);
 this->m_blendingOut = float1 < float0;
 }
 }

 float incrementBlendTime(float float1, float float2, float float3) {
 float float0 = float1 * float2;
 return float0 + float3;
 }

 float getTransitionInBlendInTime() {
 return this->m_transitionIn.m_data != nullptr &&
 this->m_transitionIn.m_data.m_blendInTime !=
 Float.POSITIVE_INFINITY
 ? this->m_transitionIn.m_data.m_blendInTime
 : 0.0F;
 }

 float getMainInitialRewindTime() {
 float float0 = 0.0F;
 if (this->m_sourceNode.m_randomAdvanceFraction > 0.0F) {
 float float1 = Rand.Next(0.0F, this->m_sourceNode.m_randomAdvanceFraction);
 float0 = float1 * this->getMaxDuration();
 }

 if (this->m_transitionIn.m_data.empty()) {
 return 0.0F - float0;
 } else {
 float float2 = this->getTransitionInBlendOutTime();
 float float3 = this->m_transitionIn.m_data.m_SyncAdjustTime;
 return this->m_transitionIn.m_track != nullptr ? float2 - float3
 : float2 - float3 - float0;
 }
 }

 float getMaxDuration() {
 float float0 = 0.0F;
 int int0 = 0;

 for (int int1 = this->m_AnimationTracks.size(); int0 < int1; int0++) {
 AnimationTrack animationTrack = this->m_AnimationTracks.get(int0);
 float float1 = animationTrack.getDuration();
 float0 = PZMath.max(float1, float0);
 }

 return float0;
 }

 float getTransitionInBlendOutTime() { return this->getBlendInTime(); }

 float getBlendInTime() {
 if (this->m_transitionIn.m_data.empty()) {
 return this->m_sourceNode.m_BlendTime;
 } else if (this->m_transitionIn.m_track != nullptr &&
 this->m_transitionIn.m_data.m_blendOutTime !=
 Float.POSITIVE_INFINITY) {
 return this->m_transitionIn.m_data.m_blendOutTime;
 } else {
 if (this->m_transitionIn.m_track.empty()) {
 if (this->m_transitionIn.m_data.m_blendInTime !=
 Float.POSITIVE_INFINITY) {
 return this->m_transitionIn.m_data.m_blendInTime;
 }

 if (this->m_transitionIn.m_data.m_blendOutTime !=
 Float.POSITIVE_INFINITY) {
 return this->m_transitionIn.m_data.m_blendOutTime;
 }
 }

 return this->m_sourceNode.m_BlendTime;
 }
 }

 float getBlendOutTime() {
 if (this->m_transitionOut.empty()) {
 return this->m_sourceNode.getBlendOutTime();
 } else if (!StringUtils.isNullOrWhitespace(
 this->m_transitionOut.m_AnimName) &&
 this->m_transitionOut.m_blendInTime != Float.POSITIVE_INFINITY) {
 return this->m_transitionOut.m_blendInTime;
 } else {
 if (StringUtils.isNullOrWhitespace(this->m_transitionOut.m_AnimName) {
 if (this->m_transitionOut.m_blendOutTime != Float.POSITIVE_INFINITY) {
 return this->m_transitionOut.m_blendOutTime;
 }

 if (this->m_transitionOut.m_blendInTime != Float.POSITIVE_INFINITY) {
 return this->m_transitionOut.m_blendInTime;
 }
 }

 return this->m_sourceNode.getBlendOutTime();
 }
 }

 void onAnimStarted(AnimationTrack track) { this->invokeAnimStartTimeEvent(); }

 void onLoopedAnim(AnimationTrack track) {
 if (!this->m_TransitioningOut) {
 this->invokeAnimEndTimeEvent();
 }
 }

 void onNonLoopedAnimFadeOut(AnimationTrack track) {
 if (DebugOptions.instance.Animation.AllowEarlyTransitionOut.getValue()) {
 this->invokeAnimEndTimeEvent();
 this->m_TransitioningOut = true;
 }
 }

 void onNonLoopedAnimFinished(AnimationTrack track) {
 if (!this->m_TransitioningOut) {
 this->invokeAnimEndTimeEvent();
 }
 }

 void onTrackDestroyed(AnimationTrack track) {
 this->m_AnimationTracks.remove(track);
 if (this->m_transitionIn.m_track == track) {
 this->m_transitionIn.m_track = nullptr;
 this->m_transitionIn.m_active = false;
 this->m_transitionIn.m_weight = 0.0F;
 this->setMainTracksPlaying(true);
 }
 }

 void invokeAnimStartTimeEvent() {
 this->invokeAnimTimeEvent(AnimEvent.AnimEventTime.Start);
 }

 void invokeAnimEndTimeEvent() {
 this->invokeAnimTimeEvent(AnimEvent.AnimEventTime.End);
 }

 void invokeAnimTimeEvent(AnimEvent.AnimEventTime animEventTime) {
 std::vector list = this->getSourceNode().m_Events;
 int int0 = 0;

 for (int int1 = list.size(); int0 < int1; int0++) {
 AnimEvent animEvent = (AnimEvent)list.get(int0);
 if (animEvent.m_Time == animEventTime) {
 this->m_animLayer.invokeAnimEvent(animEvent);
 }
 }
 }

 AnimNode getSourceNode() { return this->m_sourceNode; }

 /**
 * Returns TRUE if this Live node is currently Active, and if the source
 * AnimNode is an Idle animation.
 */
 bool isIdleAnimActive() {
 return this->m_active && this->m_sourceNode.isIdleAnim();
 }

 bool isActive() { return this->m_active; }

 void setActive(bool active) { this->m_active = active; }

 bool isLooped() { return this->m_sourceNode.m_Looped; }

 float getWeight() { return this->m_Weight; }

 float getTransitionInWeight() { return this->m_transitionIn.m_weight; }

 bool wasActivated() {
 return this->m_active != this->m_wasActive && this->m_active;
 }

 bool wasDeactivated() {
 return this->m_active != this->m_wasActive && this->m_wasActive;
 }

 bool isNew() { return this->m_isNew; }

 int getPlayingTrackCount() noexcept{
 int int0 = 0;
 if (this->isMainAnimActive()) {
 int0 += this->m_AnimationTracks.size();
 }

 if (this->isTransitioningIn()) {
 int0++;
 }

 return int0;
 }

 bool isMainAnimActive() {
 return !this->isTransitioningIn() || this->m_transitionIn.m_blendingOut;
 }

 AnimationTrack getPlayingTrackAt(int trackIdx) {
 int int0 = this->getPlayingTrackCount();
 if (trackIdx < 0 || trackIdx >= int0) {
 throw IndexOutOfBoundsException("TrackIdx out of bounds 0 - " +
 this->getPlayingTrackCount());
 } else {
 return this->isTransitioningIn() && trackIdx == int0 - 1
 ? this->m_transitionIn.m_track
 : this->m_AnimationTracks.get(trackIdx);
 }
 }

 std::string getTransitionFrom() {
 return this->m_transitionIn.m_transitionedFrom;
 }

 void setTransitionInBlendDelta(float blendDelta) {
 if (this->m_transitionIn.m_track != nullptr) {
 this->m_transitionIn.m_track.BlendDelta = blendDelta;
 }
 }

 AnimationTrack getTransitionInTrack() { return this->m_transitionIn.m_track; }

 int getTransitionLayerIdx() {
 return this->m_transitionIn.m_track != nullptr
 ? this->m_transitionIn.m_track.getLayerIdx()
 : -1;
 }

 int getLayerIdx() { return this->m_layerIdx; }

 int getPriority() { return this->m_sourceNode.getPriority(); }

 std::string getDeferredBoneName() {
 return this->m_sourceNode.getDeferredBoneName();
 }

 BoneAxis getDeferredBoneAxis() {
 return this->m_sourceNode.getDeferredBoneAxis();
 }

public
 List<AnimBoneWeight> getSubStateBoneWeights() {
 return this->m_sourceNode.m_SubStateBoneWeights;
 }

 AnimTransition findTransitionTo(IAnimationVariableSource varSource,
 std::string_view name) {
 return this->m_sourceNode.findTransitionTo(varSource, name);
 }

 float getSpeedScale(IAnimationVariableSource varSource) {
 return this->m_sourceNode.getSpeedScale(varSource);
 }

private
 static class TransitionIn {
 float m_time;
 std::string m_transitionedFrom;
 bool m_active;
 AnimationTrack m_track;
 AnimTransition m_data;
 float m_weight;
 float m_rawWeight;
 bool m_blendingIn;
 bool m_blendingOut;

 void reset() {
 this->m_time = 0.0F;
 this->m_transitionedFrom = nullptr;
 this->m_active = false;
 this->m_track = nullptr;
 this->m_data = nullptr;
 this->m_weight = 0.0F;
 this->m_rawWeight = 0.0F;
 this->m_blendingIn = false;
 this->m_blendingOut = false;
 }
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
