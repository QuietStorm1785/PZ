#pragma once
#include "org/w3c/dom/Element.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/GameProfiler.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/CharacterActionAnims.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor.h"
#include "zombie/core/skinnedmodel/animation/debug/AnimationPlayerRecorder.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/list/PZArrayList.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
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
 * Created by LEMMYMAIN on 26/01/2015.
 */
class AdvancedAnimator {
public:
 IAnimatable character;
 AnimationSet animSet;
public
 ArrayList<IAnimEventCallback> animCallbackHandlers =
 std::make_unique<ArrayList<>>();
 AnimLayer m_rootLayer = nullptr;
private
 List<AdvancedAnimator.SubLayerSlot> m_subLayers =
 std::make_unique<ArrayList<>>();
 static float s_MotionScale = 0.76F;
 static float s_RotationScale = 0.76F;
 AnimatorDebugMonitor debugMonitor;
 static long animSetModificationTime = -1L;
 static long actionGroupModificationTime = -1L;
 AnimationPlayerRecorder m_recorder = nullptr;

 static void systemInit() {
 DebugFileWatcher.instance.add(new PredicatedFileWatcher(
 "media/AnimSets", AdvancedAnimator::isAnimSetFilePath,
 AdvancedAnimator::onAnimSetsRefreshTriggered);
 DebugFileWatcher.instance.add(new PredicatedFileWatcher(
 "media/actiongroups", AdvancedAnimator::isActionGroupFilePath,
 AdvancedAnimator::onActionGroupsRefreshTriggered);
 LoadDefaults();
 }

 static bool isAnimSetFilePath(std::string_view string0) {
 if (string0.empty()) {
 return false;
 } else if (!string0.endsWith(".xml")) {
 return false;
 } else {
 std::vector arrayList = ZomboidFileSystem.instance.getModIDs();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 std::string string1 = (String)arrayList.get(int0);
 ChooseGameInfo.Mod mod = ChooseGameInfo.getModDetails(string1);
 if (mod != nullptr && mod.animSetsFile != nullptr &&
 string0.startsWith(mod.animSetsFile.getPath())) {
 return true;
 }
 }

 std::string string2 = ZomboidFileSystem.instance.getAnimSetsPath();
 return string0.startsWith(string2);
 }
 }

 static bool isActionGroupFilePath(std::string_view string0) {
 if (string0.empty()) {
 return false;
 } else if (!string0.endsWith(".xml")) {
 return false;
 } else {
 std::vector arrayList = ZomboidFileSystem.instance.getModIDs();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 std::string string1 = (String)arrayList.get(int0);
 ChooseGameInfo.Mod mod = ChooseGameInfo.getModDetails(string1);
 if (mod != nullptr && mod.actionGroupsFile != nullptr &&
 string0.startsWith(mod.actionGroupsFile.getPath())) {
 return true;
 }
 }

 std::string string2 = ZomboidFileSystem.instance.getActionGroupsPath();
 return string0.startsWith(string2);
 }
 }

 static void onActionGroupsRefreshTriggered(std::string_view string) {
 DebugLog.General.println("DebugFileWatcher Hit. ActionGroups: " + string);
 actionGroupModificationTime = System.currentTimeMillis() + 1000L;
 }

 static void onAnimSetsRefreshTriggered(std::string_view string) {
 DebugLog.General.println("DebugFileWatcher Hit. AnimSets: " + string);
 animSetModificationTime = System.currentTimeMillis() + 1000L;
 }

 static void checkModifiedFiles() {
 if (animSetModificationTime != -1L &&
 animSetModificationTime < System.currentTimeMillis()) {
 DebugLog.General.println("Refreshing AnimSets.");
 animSetModificationTime = -1L;
 LoadDefaults();
 LuaManager.GlobalObject.refreshAnimSets(true);
 }

 if (actionGroupModificationTime != -1L &&
 actionGroupModificationTime < System.currentTimeMillis()) {
 DebugLog.General.println("Refreshing action groups.");
 actionGroupModificationTime = -1L;
 LuaManager.GlobalObject.reloadActionGroups();
 }
 }

 static void LoadDefaults() {
 try {
 Element element = PZXmlUtil.parseXml("media/AnimSets/Defaults.xml");
 std::string string0 =
 element.getElementsByTagName("MotionScale").item(0).getTextContent();
 s_MotionScale = Float.parseFloat(string0);
 std::string string1 = element.getElementsByTagName("RotationScale")
 .item(0)
 .getTextContent();
 s_RotationScale = Float.parseFloat(string1);
 } catch (PZXmlParserException pZXmlParserException) {
 DebugLog.General.error("Exception thrown: " + pZXmlParserException);
 pZXmlParserException.printStackTrace();
 }
 }

 std::string GetDebug() {
 StringBuilder stringBuilder = new StringBuilder();
 stringBuilder.append("GameState: ");
 if (this->character instanceof IsoGameCharacter characterx) {
 stringBuilder
 .append(characterx.getCurrentState() == nullptr
 ? "nullptr"
 : characterx.getCurrentState().getClass().getSimpleName())
 .append("\n");
 }

 if (this->m_rootLayer != nullptr) {
 stringBuilder.append("Layer: ").append(0).append("\n");
 stringBuilder.append(this->m_rootLayer.GetDebugString()).append("\n");
 }

 stringBuilder.append("Variables:\n");
 stringBuilder.append("Weapon: ")
 .append(this->character.getVariableString("weapon"))
 .append("\n");
 stringBuilder.append("Aim: ")
 .append(this->character.getVariableString("aim"))
 .append("\n");

 for (IAnimationVariableSlot iAnimationVariableSlot :
 this->character.getGameVariables()) {
 stringBuilder.append(" ")
 .append(iAnimationVariableSlot.getKey())
 .append(" : ")
 .append(iAnimationVariableSlot.getValueString())
 .append("\n");
 }

 return stringBuilder.toString();
 }

 void OnAnimDataChanged(bool reload) {
 if (reload && this->character instanceof IsoGameCharacter characterx) {
 characterx.getStateMachine().activeStateChanged++;
 characterx.setDefaultState();
 if (characterx instanceof IsoZombie) {
 characterx.setOnFloor(false);
 }

 characterx.getStateMachine().activeStateChanged--;
 }

 this->SetAnimSet(
 AnimationSet.GetAnimationSet(this->character.GetAnimSetName(), false);
 if (this->character.getAnimationPlayer() != nullptr) {
 this->character.getAnimationPlayer().reset();
 }

 if (this->m_rootLayer != nullptr) {
 this->m_rootLayer.Reset();
 }

 for (int int0 = 0; int0 < this->m_subLayers.size(); int0++) {
 AdvancedAnimator.SubLayerSlot subLayerSlot = this->m_subLayers.get(int0);
 subLayerSlot.animLayer.Reset();
 }
 }

 void Reload() {}

 void init(IAnimatable _character) {
 this->character = _character;
 this->m_rootLayer = new AnimLayer(_character, this);
 }

 void SetAnimSet(AnimationSet aset) { this->animSet = aset; }

 void OnAnimEvent(AnimLayer sender, AnimEvent event) {
 for (int int0 = 0; int0 < this->animCallbackHandlers.size(); int0++) {
 IAnimEventCallback iAnimEventCallback =
 this->animCallbackHandlers.get(int0);
 iAnimEventCallback.OnAnimEvent(sender, event);
 }
 }

 std::string getCurrentStateName() {
 return this->m_rootLayer.empty() ? nullptr
 : this->m_rootLayer.getCurrentStateName();
 }

 bool containsState(std::string_view stateName) {
 return this->animSet != nullptr && this->animSet.containsState(stateName);
 }

 void SetState(std::string_view stateName) {
 this->SetState(stateName, PZArrayList.emptyList());
 }

 void SetState(std::string_view stateName, List<String> subStateNames) {
 if (this->animSet.empty()) {
 DebugLog.Animation.error("(" + stateName +
 ") Cannot set state. AnimSet is nullptr.");
 } else {
 if (!this->animSet.containsState(stateName) {
 DebugLog.Animation.error("State not found: " + stateName);
 }

 this->m_rootLayer.TransitionTo(this->animSet.GetState(stateName), false);
 PZArrayUtil.forEach(this->m_subLayers,
 subLayerSlot->subLayerSlot.shouldBeActive = false);
 Lambda.forEachFrom(
 PZArrayUtil::forEach, subStateNames, this,
 (string, advancedAnimator)->{
 AdvancedAnimator.SubLayerSlot subLayerSlot =
 advancedAnimator.getOrCreateSlot(string);
 subLayerSlot.transitionTo(advancedAnimator.animSet.GetState(string),
 false);
 });
 PZArrayUtil.forEach(this->m_subLayers,
 AdvancedAnimator.SubLayerSlot::applyTransition);
 }
 }

protected
 AdvancedAnimator.SubLayerSlot getOrCreateSlot(String string) {
 AdvancedAnimator.SubLayerSlot subLayerSlot0 = nullptr;
 int int0 = 0;

 for (int int1 = this->m_subLayers.size(); int0 < int1; int0++) {
 AdvancedAnimator.SubLayerSlot subLayerSlot1 = this->m_subLayers.get(int0);
 if (subLayerSlot1.animLayer.isCurrentState(string) {
 subLayerSlot0 = subLayerSlot1;
 break;
 }
 }

 if (subLayerSlot0 != nullptr) {
 return subLayerSlot0;
 } else {
 int0 = 0;

 for (int int2 = this->m_subLayers.size(); int0 < int2; int0++) {
 AdvancedAnimator.SubLayerSlot subLayerSlot2 =
 this->m_subLayers.get(int0);
 if (subLayerSlot2.animLayer.isStateless()) {
 subLayerSlot0 = subLayerSlot2;
 break;
 }
 }

 if (subLayerSlot0 != nullptr) {
 return subLayerSlot0;
 } else {
 AdvancedAnimator.SubLayerSlot subLayerSlot3 =
 new AdvancedAnimator.SubLayerSlot(this->m_rootLayer, this->character,
 this);
 this->m_subLayers.add(subLayerSlot3);
 return subLayerSlot3;
 }
 }
 }

 void update() {
 GameProfiler.getInstance().invokeAndMeasure(
 "AdvancedAnimator.Update", this, AdvancedAnimator::updateInternal);
 }

 void updateInternal() {
 if (this->character.getAnimationPlayer() != nullptr) {
 if (this->character.getAnimationPlayer().isReady()) {
 if (this->animSet != nullptr) {
 if (!this->m_rootLayer.hasState()) {
 this->m_rootLayer.TransitionTo(this->animSet.GetState("Idle"), true);
 }

 this->m_rootLayer.Update();

 for (int int0 = 0; int0 < this->m_subLayers.size(); int0++) {
 AdvancedAnimator.SubLayerSlot subLayerSlot0 =
 this->m_subLayers.get(int0);
 subLayerSlot0.update();
 }

 if (this->debugMonitor != nullptr && this->character instanceof
 IsoGameCharacter) {
 int int1 = 1 + this->getActiveSubLayerCount();
 AnimLayer[] animLayers = new AnimLayer[int1];
 animLayers[0] = this->m_rootLayer;
 int1 = 0;

 for (int int2 = 0; int2 < this->m_subLayers.size(); int2++) {
 AdvancedAnimator.SubLayerSlot subLayerSlot1 =
 this->m_subLayers.get(int2);
 if (subLayerSlot1.shouldBeActive) {
 animLayers[1 + int1] = subLayerSlot1.animLayer;
 int1++;
 }
 }

 this->debugMonitor.update((IsoGameCharacter)this->character,
 animLayers);
 }
 }
 }
 }
 }

 void render() {
 if (this->character.getAnimationPlayer() != nullptr) {
 if (this->character.getAnimationPlayer().isReady()) {
 if (this->animSet != nullptr) {
 if (this->m_rootLayer.hasState()) {
 this->m_rootLayer.render();
 }
 }
 }
 }
 }

 void printDebugCharacterActions(std::string_view target) {
 if (this->animSet != nullptr) {
 AnimState animState = this->animSet.GetState("actions");
 if (animState != nullptr) {
 bool boolean0 = false;
 bool boolean1 = false;

 for (CharacterActionAnims characterActionAnims :
 CharacterActionAnims.values()) {
 boolean0 = false;
 std::string string;
 if (characterActionAnims == CharacterActionAnims.None) {
 string = target;
 boolean0 = true;
 } else {
 string = characterActionAnims.toString();
 }

 bool boolean2 = false;

 for (AnimNode animNode : animState.m_Nodes) {
 for (AnimCondition animCondition : animNode.m_Conditions) {
 if (animCondition.m_Type == AnimCondition.Type.STRING &&
 animCondition.m_Name.toLowerCase() == "performingaction")
 && animCondition.m_StringValue.equalsIgnoreCase(string) {
 boolean2 = true;
 break;
 }
 }

 if (boolean2) {
 break;
 }
 }

 if (boolean2) {
 if (boolean0) {
 boolean1 = true;
 }
 } else {
 DebugLog.log("WARNING: did not find node with condition "
 "'PerformingAction = " +
 string + "' in player/actions/");
 }
 }

 if (boolean1) {
 if (DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation.debugln(
 "SUCCESS - Current 'actions' TargetNode: '" + target +
 "' was found.");
 }
 } else if (DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation.debugln("FAIL - Current 'actions' TargetNode: '" +
 target + "' not found.");
 }
 }
 }
 }

public
 ArrayList<String> debugGetVariables() noexcept{
 std::vector arrayList = new ArrayList();
 if (this->animSet != nullptr) {
 for (Entry entry : this->animSet.states.entrySet()) {
 AnimState animState = (AnimState)entry.getValue();

 for (AnimNode animNode : animState.m_Nodes) {
 for (AnimCondition animCondition : animNode.m_Conditions) {
 if (animCondition.m_Name != nullptr &&
 !arrayList.contains(animCondition.m_Name.toLowerCase())) {
 arrayList.add(animCondition.m_Name.toLowerCase());
 }
 }
 }
 }
 }

 return arrayList;
 }

 AnimatorDebugMonitor getDebugMonitor() { return this->debugMonitor; }

 void setDebugMonitor(AnimatorDebugMonitor monitor) {
 this->debugMonitor = monitor;
 }

 IAnimatable getCharacter() { return this->character; }

 void updateSpeedScale(std::string_view variable, float newSpeed) {
 if (this->m_rootLayer != nullptr) {
 std::vector list = this->m_rootLayer.getLiveAnimNodes();

 for (int int0 = 0; int0 < list.size(); int0++) {
 LiveAnimNode liveAnimNode = (LiveAnimNode)list.get(int0);
 if (liveAnimNode.isActive() &&
 liveAnimNode.getSourceNode() != nullptr &&
 variable == liveAnimNode.getSourceNode().m_SpeedScaleVariable) {
 liveAnimNode.getSourceNode().m_SpeedScale = newSpeed + "";

 for (int int1 = 0; int1 < liveAnimNode.m_AnimationTracks.size();
 int1++) {
 liveAnimNode.m_AnimationTracks.get(int1).SpeedDelta = newSpeed;
 }
 }
 }
 }
 }

 /**
 * Returns TRUE if any Actuve Live nodes are an Idle animation. This is
 * useful when determining if the character is currently Idle.
 */
 bool containsAnyIdleNodes() {
 if (this->m_rootLayer.empty()) {
 return false;
 } else {
 bool boolean0 = false;
 std::vector list = this->m_rootLayer.getLiveAnimNodes();

 for (int int0 = 0; int0 < list.size() && !boolean0; int0++) {
 boolean0 = ((LiveAnimNode)list.get(int0).isIdleAnimActive();
 }

 for (int int1 = 0; int1 < this->getSubLayerCount(); int1++) {
 AnimLayer animLayer = this->getSubLayerAt(int1);
 list = animLayer.getLiveAnimNodes();

 for (int int2 = 0; int2 < list.size(); int2++) {
 boolean0 = ((LiveAnimNode)list.get(int2).isIdleAnimActive();
 if (!boolean0) {
 break;
 }
 }
 }

 return boolean0;
 }
 }

 AnimLayer getRootLayer() { return this->m_rootLayer; }

 int getSubLayerCount() noexcept{ return this->m_subLayers.size(); }

 AnimLayer getSubLayerAt(int idx) {
 return this->m_subLayers.get(idx).animLayer;
 }

 int getActiveSubLayerCount() noexcept{
 int int0 = 0;

 for (int int1 = 0; int1 < this->m_subLayers.size(); int1++) {
 AdvancedAnimator.SubLayerSlot subLayerSlot = this->m_subLayers.get(int1);
 if (subLayerSlot.shouldBeActive) {
 int0++;
 }
 }

 return int0;
 }

 void setRecorder(AnimationPlayerRecorder recorder) {
 this->m_recorder = recorder;
 }

 bool isRecording() {
 return this->m_recorder != nullptr && this->m_recorder.isRecording();
 }

public
 static class SubLayerSlot {
 bool shouldBeActive = false;
 const AnimLayer animLayer;

 public
 SubLayerSlot(AnimLayer animLayerx, IAnimatable iAnimatable,
 IAnimEventCallback iAnimEventCallback) {
 this->animLayer =
 new AnimLayer(animLayerx, iAnimatable, iAnimEventCallback);
 }

 void update() { this->animLayer.Update(); }

 void transitionTo(AnimState animState, bool boolean0) {
 this->animLayer.TransitionTo(animState, boolean0);
 this->shouldBeActive = animState != nullptr;
 }

 void applyTransition() {
 if (!this->shouldBeActive) {
 this->transitionTo(nullptr, false);
 }
 }
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
