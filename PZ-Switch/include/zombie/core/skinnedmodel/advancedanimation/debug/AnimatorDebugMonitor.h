#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimLayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/IAnimationVariableSlot.h"
#include "zombie/core/skinnedmodel/advancedanimation/LiveAnimNode.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
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
namespace debug {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimatorDebugMonitor {
public:
private
 static ArrayList<String> knownVariables =
 std::make_unique<ArrayList<>>();
 static bool knownVarsDirty = false;
 std::string currentState = "nullptr";
private
 AnimatorDebugMonitor.MonitoredLayer[] monitoredLayers;
private
 HashMap<String, AnimatorDebugMonitor.MonitoredVar> monitoredVariables =
 std::make_unique<HashMap<>>();
private
 ArrayList<String> customVariables = std::make_unique<ArrayList<>>();
private
 LinkedList<AnimatorDebugMonitor.MonitorLogLine> logLines =
 std::make_unique<LinkedList<>>();
private
 Queue<AnimatorDebugMonitor.MonitorLogLine> logLineQueue =
 std::make_unique<LinkedList<>>();
 bool floatsListDirty = false;
 bool hasFilterChanges = false;
 bool hasLogUpdates = false;
 std::string logString = "";
 static const int maxLogSize = 1028;
 static const int maxOutputLines = 128;
 static const int maxFloatCache = 1024;
private
 ArrayList<Float> floatsOut = std::make_unique<ArrayList<>>();
private
 AnimatorDebugMonitor.MonitoredVar selectedVariable;
 int tickCount = 0;
 bool doTickStamps = false;
 static const int tickStampLength = 10;
 static const Color col_curstate = Colors.Cyan;
 static const Color col_layer_nodename = Colors.CornFlowerBlue;
 static const Color col_layer_activated = Colors.DarkTurquoise;
 static const Color col_layer_deactivated = Colors.Orange;
 static const Color col_track_activated = Colors.SandyBrown;
 static const Color col_track_deactivated = Colors.Salmon;
 static const Color col_node_activated = Colors.Pink;
 static const Color col_node_deactivated = Colors.Plum;
 static const Color col_var_activated = Colors.Chartreuse;
 static const Color col_var_changed = Colors.LimeGreen;
 static const Color col_var_deactivated = Colors.Gold;
 static const std::string TAG_VAR = "[variable]";
 static const std::string TAG_LAYER = "[layer]";
 static const std::string TAG_NODE = "[active_nodes]";
 static const std::string TAG_TRACK = "[anim_tracks]";
private
 boolean[] logFlags = new boolean[AnimatorDebugMonitor.LogType.MAX.value()];

public
 AnimatorDebugMonitor(IsoGameCharacter chr) {
 this->logFlags[AnimatorDebugMonitor.LogType.DEFAULT.value()] = true;

 for (int int0 = 0; int0 < this->logFlags.length; int0++) {
 this->logFlags[int0] = true;
 }

 for (int int1 = 0; int1 < 1024; int1++) {
 this->floatsOut.add(0.0F);
 }

 this->initCustomVars();
 if (chr != nullptr && chr.advancedAnimator != nullptr) {
 for (String string : chr.advancedAnimator.debugGetVariables()) {
 registerVariable(string);
 }
 }
 }

 void initCustomVars() {
 this->addCustomVariable("aim");
 this->addCustomVariable("bdead");
 this->addCustomVariable("bfalling");
 this->addCustomVariable("baimatfloor");
 this->addCustomVariable("battackfrombehind");
 this->addCustomVariable("attacktype");
 this->addCustomVariable("bundervehicle");
 this->addCustomVariable("reanimatetimer");
 this->addCustomVariable("isattacking");
 this->addCustomVariable("canclimbdownrope");
 this->addCustomVariable("frombehind");
 this->addCustomVariable("fallonfront");
 this->addCustomVariable("hashitreaction");
 this->addCustomVariable("hitreaction");
 this->addCustomVariable("collided");
 this->addCustomVariable("collidetype");
 this->addCustomVariable("intrees");
 }

 void addCustomVariable(std::string_view var) {
 std::string string = var.toLowerCase();
 if (!this->customVariables.contains(string) {
 this->customVariables.add(string);
 }

 registerVariable(var);
 }

 void removeCustomVariable(std::string_view var) {
 std::string string = var.toLowerCase();
 this->customVariables.remove(string);
 }

 void setFilter(int index, bool b) {
 if (index >= 0 && index < AnimatorDebugMonitor.LogType.MAX.value()) {
 this->logFlags[index] = b;
 this->hasFilterChanges = true;
 }
 }

 bool getFilter(int index) {
 return index >= 0 && index < AnimatorDebugMonitor.LogType.MAX.value()
 ? this->logFlags[index]
 : false;
 }

 bool isDoTickStamps() { return this->doTickStamps; }

 void setDoTickStamps(bool _doTickStamps) {
 if (this->doTickStamps != _doTickStamps) {
 this->doTickStamps = _doTickStamps;
 this->hasFilterChanges = true;
 }
 }

 void queueLogLine(std::string_view string) {
 this->addLogLine(AnimatorDebugMonitor.LogType.DEFAULT, string, nullptr,
 true);
 }

 void queueLogLine(std::string_view string, Color color) {
 this->addLogLine(AnimatorDebugMonitor.LogType.DEFAULT, string, color, true);
 }

 void queueLogLine(AnimatorDebugMonitor.LogType logType,
 std::string_view string, Color color) {
 this->addLogLine(logType, string, color, true);
 }

 void addLogLine(std::string_view string) {
 this->addLogLine(AnimatorDebugMonitor.LogType.DEFAULT, string, nullptr,
 false);
 }

 void addLogLine(std::string_view string, Color color) {
 this->addLogLine(AnimatorDebugMonitor.LogType.DEFAULT, string, color, false);
 }

 void addLogLine(std::string_view string, Color color, bool boolean0) {
 this->addLogLine(AnimatorDebugMonitor.LogType.DEFAULT, string, color,
 boolean0);
 }

 void addLogLine(AnimatorDebugMonitor.LogType logType,
 std::string_view string, Color color) {
 this->addLogLine(logType, string, color, false);
 }

 void addLogLine(AnimatorDebugMonitor.LogType logType,
 std::string_view string, Color color, bool boolean0) {
 AnimatorDebugMonitor.MonitorLogLine monitorLogLine =
 new AnimatorDebugMonitor.MonitorLogLine();
 monitorLogLine.line = string;
 monitorLogLine.color = color;
 monitorLogLine.type = logType;
 monitorLogLine.tick = this->tickCount;
 if (boolean0) {
 this->logLineQueue.add(monitorLogLine);
 } else {
 this->log(monitorLogLine);
 }
 }

 void log(AnimatorDebugMonitor.MonitorLogLine monitorLogLine) {
 this->logLines.addFirst(monitorLogLine);
 if (this->logLines.size() > 1028) {
 this->logLines.removeLast();
 }

 this->hasLogUpdates = true;
 }

 void processQueue() {
 while (this->logLineQueue.size() > 0) {
 AnimatorDebugMonitor.MonitorLogLine monitorLogLine =
 this->logLineQueue.poll();
 this->log(monitorLogLine);
 }
 }

 void preUpdate() {
 for (Entry entry0 : this->monitoredVariables.entrySet()) {
 ((AnimatorDebugMonitor.MonitoredVar)entry0.getValue()).updated = false;
 }

 for (int int0 = 0; int0 < this->monitoredLayers.length; int0++) {
 AnimatorDebugMonitor.MonitoredLayer monitoredLayer =
 this->monitoredLayers[int0];
 monitoredLayer.updated = false;

 for (Entry entry1 : monitoredLayer.activeNodes.entrySet()) {
 ((AnimatorDebugMonitor.MonitoredNode)entry1.getValue()).updated = false;
 }

 for (Entry entry2 : monitoredLayer.animTracks.entrySet()) {
 ((AnimatorDebugMonitor.MonitoredTrack)entry2.getValue()).updated =
 false;
 }
 }
 }

 void postUpdate() {
 for (Entry entry0 : this->monitoredVariables.entrySet()) {
 if (((AnimatorDebugMonitor.MonitoredVar)entry0.getValue()).active &&
 !((AnimatorDebugMonitor.MonitoredVar)entry0.getValue()).updated) {
 this->addLogLine(
 AnimatorDebugMonitor.LogType.VAR,
 "[variable] : removed -> '" + (String)entry0.getKey() +
 "', last value: '" +
 ((AnimatorDebugMonitor.MonitoredVar)entry0.getValue()).value +
 "'.",
 col_var_deactivated);
 ((AnimatorDebugMonitor.MonitoredVar)entry0.getValue()).active = false;
 }
 }

 for (int int0 = 0; int0 < this->monitoredLayers.length; int0++) {
 AnimatorDebugMonitor.MonitoredLayer monitoredLayer =
 this->monitoredLayers[int0];

 for (Entry entry1 : monitoredLayer.activeNodes.entrySet()) {
 if (((AnimatorDebugMonitor.MonitoredNode)entry1.getValue()).active &&
 !((AnimatorDebugMonitor.MonitoredNode)entry1.getValue()).updated) {
 this->addLogLine(
 AnimatorDebugMonitor.LogType.NODE,
 "[layer][" + monitoredLayer.index +
 "] [active_nodes] : deactivated -> '" +
 ((AnimatorDebugMonitor.MonitoredNode)entry1.getValue()).name +
 "'.",
 col_node_deactivated);
 ((AnimatorDebugMonitor.MonitoredNode)entry1.getValue()).active =
 false;
 }
 }

 for (Entry entry2 : monitoredLayer.animTracks.entrySet()) {
 if (((AnimatorDebugMonitor.MonitoredTrack)entry2.getValue()).active &&
 !((AnimatorDebugMonitor.MonitoredTrack)entry2.getValue()).updated) {
 this->addLogLine(
 AnimatorDebugMonitor.LogType.TRACK,
 "[layer][" + monitoredLayer.index +
 "] [anim_tracks] : deactivated -> '" +
 ((AnimatorDebugMonitor.MonitoredTrack)entry2.getValue())
 .name +
 "'.",
 col_track_deactivated);
 ((AnimatorDebugMonitor.MonitoredTrack)entry2.getValue()).active =
 false;
 }
 }

 if (monitoredLayer.active && !monitoredLayer.updated) {
 this->addLogLine(AnimatorDebugMonitor.LogType.LAYER,
 "[layer][" + int0 +
 "] : deactivated (last animstate: '" +
 monitoredLayer.nodeName + "').",
 col_layer_deactivated);
 monitoredLayer.active = false;
 }
 }
 }

 void update(IsoGameCharacter character, AnimLayer[] animLayers) {
 if (character != nullptr) {
 this->ensureLayers(animLayers);
 this->preUpdate();

 for (IAnimationVariableSlot iAnimationVariableSlot :
 character.getGameVariables()) {
 this->updateVariable(iAnimationVariableSlot.getKey(),
 iAnimationVariableSlot.getValueString());
 }

 for (String string0 : this->customVariables) {
 std::string string1 = character.getVariableString(string0);
 if (string1 != nullptr) {
 this->updateVariable(string0, string1);
 }
 }

 this->updateCurrentState(
 character.getCurrentState() == nullptr
 ? "nullptr"
 : character.getCurrentState().getClass().getSimpleName());

 for (int int0 = 0; int0 < animLayers.length; int0++) {
 if (animLayers[int0] != nullptr) {
 this->updateLayer(int0, animLayers[int0]);
 }
 }

 this->postUpdate();
 this->processQueue();
 this->tickCount++;
 }
 }

 void updateCurrentState(std::string_view string) {
 if (!this->currentState == string) {
 this->queueLogLine("Character.currentState changed from '" +
 this->currentState + "' to: '" + string + "'.",
 col_curstate);
 this->currentState = string;
 }
 }

 void updateLayer(int int0, AnimLayer animLayer) {
 AnimatorDebugMonitor.MonitoredLayer monitoredLayer =
 this->monitoredLayers[int0];
 std::string string = animLayer.getDebugNodeName();
 if (!monitoredLayer.active) {
 monitoredLayer.active = true;
 this->queueLogLine(AnimatorDebugMonitor.LogType.LAYER,
 "[layer][" + int0 + "] activated -> animstate: '" +
 string + "'.",
 col_layer_activated);
 }

 if (!monitoredLayer.nodeName == string) {
 this->queueLogLine(AnimatorDebugMonitor.LogType.LAYER,
 "[layer][" + int0 + "] changed -> animstate from '" +
 monitoredLayer.nodeName + "' to: '" + string +
 "'.",
 col_layer_nodename);
 monitoredLayer.nodeName = string;
 }

 for (LiveAnimNode liveAnimNode : animLayer.getLiveAnimNodes()) {
 this->updateActiveNode(monitoredLayer,
 liveAnimNode.getSourceNode().m_Name);
 }

 if (animLayer.getAnimationTrack() != nullptr) {
 for (AnimationTrack animationTrack :
 animLayer.getAnimationTrack().getTracks()) {
 if (animationTrack.getLayerIdx() == int0) {
 this->updateAnimTrack(monitoredLayer, animationTrack.name,
 animationTrack.BlendDelta);
 }
 }
 }

 monitoredLayer.updated = true;
 }

 void updateActiveNode(AnimatorDebugMonitor.MonitoredLayer monitoredLayer,
 std::string_view string) {
 AnimatorDebugMonitor.MonitoredNode monitoredNode =
 monitoredLayer.activeNodes.get(string);
 if (monitoredNode.empty()) {
 monitoredNode = new AnimatorDebugMonitor.MonitoredNode();
 monitoredNode.name = string;
 monitoredLayer.activeNodes.put(string, monitoredNode);
 }

 if (!monitoredNode.active) {
 monitoredNode.active = true;
 this->queueLogLine(AnimatorDebugMonitor.LogType.NODE,
 "[layer][" + monitoredLayer.index +
 "] [active_nodes] : activated -> '" + string + "'.",
 col_node_activated);
 }

 monitoredNode.updated = true;
 }

 void updateAnimTrack(AnimatorDebugMonitor.MonitoredLayer monitoredLayer,
 std::string_view string, float float0) {
 AnimatorDebugMonitor.MonitoredTrack monitoredTrack =
 monitoredLayer.animTracks.get(string);
 if (monitoredTrack.empty()) {
 monitoredTrack = new AnimatorDebugMonitor.MonitoredTrack();
 monitoredTrack.name = string;
 monitoredTrack.blendDelta = float0;
 monitoredLayer.animTracks.put(string, monitoredTrack);
 }

 if (!monitoredTrack.active) {
 monitoredTrack.active = true;
 this->queueLogLine(AnimatorDebugMonitor.LogType.TRACK,
 "[layer][" + monitoredLayer.index +
 "] [anim_tracks] : activated -> '" + string + "'.",
 col_track_activated);
 }

 if (monitoredTrack.blendDelta != float0) {
 monitoredTrack.blendDelta = float0;
 }

 monitoredTrack.updated = true;
 }

 void updateVariable(std::string_view string0, std::string_view string1) {
 AnimatorDebugMonitor.MonitoredVar monitoredVar =
 this->monitoredVariables.get(string0);
 bool boolean0 = false;
 if (monitoredVar.empty()) {
 monitoredVar = new AnimatorDebugMonitor.MonitoredVar();
 this->monitoredVariables.put(string0, monitoredVar);
 boolean0 = true;
 }

 if (!monitoredVar.active) {
 monitoredVar.active = true;
 monitoredVar.key = string0;
 monitoredVar.value = string1;
 this->queueLogLine(AnimatorDebugMonitor.LogType.VAR,
 "[variable] : added -> '" + string0 + "', value: '" +
 string1 + "'.",
 col_var_activated);
 if (boolean0) {
 registerVariable(string0);
 }
 } else if (string1.empty()) {
 if (monitoredVar.isFloat) {
 monitoredVar.isFloat = false;
 this->floatsListDirty = true;
 }

 monitoredVar.value = nullptr;
 } else if (monitoredVar.value.empty() || !monitoredVar.value == string1) {
 try {
 float float0 = Float.parseFloat(string1);
 monitoredVar.logFloat(float0);
 if (!monitoredVar.isFloat) {
 monitoredVar.isFloat = true;
 this->floatsListDirty = true;
 }
 } catch (NumberFormatException numberFormatException) {
 if (monitoredVar.isFloat) {
 monitoredVar.isFloat = false;
 this->floatsListDirty = true;
 }
 }

 if (!monitoredVar.isFloat) {
 this->queueLogLine(AnimatorDebugMonitor.LogType.VAR,
 "[variable] : updated -> '" + string0 +
 "' changed from '" + monitoredVar.value +
 "' to: '" + string1 + "'.",
 col_var_changed);
 }

 monitoredVar.value = string1;
 }

 monitoredVar.updated = true;
 }

 void buildLogString() {
 ListIterator listIterator = this->logLines.listIterator(0);
 int int0 = 0;
 int int1 = 0;

 while (listIterator.hasNext()) {
 AnimatorDebugMonitor.MonitorLogLine monitorLogLine0 =
 (AnimatorDebugMonitor.MonitorLogLine)listIterator.next();
 int1++;
 if (this->logFlags[monitorLogLine0.type.value()]) {
 if (++int0 >= 128) {
 break;
 }
 }
 }

 if (int1 == 0) {
 this->logString = "";
 } else {
 listIterator = this->logLines.listIterator(int1);
 StringBuilder stringBuilder = new StringBuilder();

 while (listIterator.hasPrevious()) {
 AnimatorDebugMonitor.MonitorLogLine monitorLogLine1 =
 (AnimatorDebugMonitor.MonitorLogLine)listIterator.previous();
 if (this->logFlags[monitorLogLine1.type.value()]) {
 stringBuilder.append(" <TEXT> ");
 if (this->doTickStamps) {
 stringBuilder.append("[");
 stringBuilder.append(String.format("%010d", monitorLogLine1.tick);
 stringBuilder.append("]");
 }

 if (monitorLogLine1.color != nullptr) {
 stringBuilder.append(" <RGB:");
 stringBuilder.append(monitorLogLine1.color.r);
 stringBuilder.append(",");
 stringBuilder.append(monitorLogLine1.color.g);
 stringBuilder.append(",");
 stringBuilder.append(monitorLogLine1.color.b);
 stringBuilder.append("> ");
 }

 stringBuilder.append(monitorLogLine1.line);
 stringBuilder.append(" <LINE> ");
 }
 }

 this->logString = stringBuilder.toString();
 this->hasLogUpdates = false;
 this->hasFilterChanges = false;
 }
 }

 bool IsDirty() { return this->hasLogUpdates || this->hasFilterChanges; }

 std::string getLogString() {
 if (this->hasLogUpdates || this->hasFilterChanges) {
 this->buildLogString();
 }

 return this->logString;
 }

 bool IsDirtyFloatList() { return this->floatsListDirty; }

public
 ArrayList<String> getFloatNames() {
 this->floatsListDirty = false;
 std::vector arrayList = new ArrayList();

 for (Entry entry : this->monitoredVariables.entrySet()) {
 if (((AnimatorDebugMonitor.MonitoredVar)entry.getValue()).isFloat) {
 arrayList.add(
 ((AnimatorDebugMonitor.MonitoredVar)entry.getValue()).key);
 }
 }

 Collections.sort(arrayList);
 return arrayList;
 }

 static bool isKnownVarsDirty() { return knownVarsDirty; }

public
 static List<String> getKnownVariables() {
 knownVarsDirty = false;
 Collections.sort(knownVariables);
 return knownVariables;
 }

 void setSelectedVariable(std::string_view key) {
 if (key.empty()) {
 this->selectedVariable = nullptr;
 } else {
 this->selectedVariable = this->monitoredVariables.get(key);
 }
 }

 std::string getSelectedVariable() {
 return this->selectedVariable != nullptr ? this->selectedVariable.key
 : nullptr;
 }

 float getSelectedVariableFloat() {
 return this->selectedVariable != nullptr ? this->selectedVariable.valFloat
 : 0.0F;
 }

 std::string getSelectedVarMinFloat() {
 return this->selectedVariable != nullptr && this->selectedVariable.isFloat &&
 this->selectedVariable.f_min != -1.0F
 ? this->selectedVariable.f_min + ""
 : "-1.0";
 }

 std::string getSelectedVarMaxFloat() {
 return this->selectedVariable != nullptr && this->selectedVariable.isFloat &&
 this->selectedVariable.f_max != -1.0F
 ? this->selectedVariable.f_max + ""
 : "1.0";
 }

public
 ArrayList<Float> getSelectedVarFloatList() {
 if (this->selectedVariable != nullptr && this->selectedVariable.isFloat) {
 AnimatorDebugMonitor.MonitoredVar monitoredVar = this->selectedVariable;
 int int0 = monitoredVar.f_index - 1;
 if (int0 < 0) {
 int0 = 0;
 }

 float float0 = monitoredVar.f_max - monitoredVar.f_min;

 for (int int1 = 0; int1 < 1024; int1++) {
 float float1 =
 (monitoredVar.f_floats[int0--] - monitoredVar.f_min) / float0;
 this->floatsOut.set(int1, float1);
 if (int0 < 0) {
 int0 = monitoredVar.f_floats.length - 1;
 }
 }

 return this->floatsOut;
 } else {
 return nullptr;
 }
 }

 static void registerVariable(std::string_view key) {
 if (key != nullptr) {
 key = key.toLowerCase();
 if (!knownVariables.contains(key) {
 knownVariables.add(key);
 knownVarsDirty = true;
 }
 }
 }

 void ensureLayers(AnimLayer[] animLayers) {
 int int0 = animLayers.length;
 if (this->monitoredLayers.empty() ||
 this->monitoredLayers.length != int0) {
 this->monitoredLayers = new AnimatorDebugMonitor.MonitoredLayer[int0];

 for (int int1 = 0; int1 < int0; int1++) {
 this->monitoredLayers[int1] =
 new AnimatorDebugMonitor.MonitoredLayer(int1);
 }
 }
 }

private
 static enum LogType {
 DEFAULT(0), LAYER(1), NODE(2), TRACK(3), VAR(4), MAX(5);

 const int val;

 private LogType(int int1){this->val = int1;}

 int value() { return this->val; }
}

class MonitorLogLine {
 std::string line;
 Color color = nullptr;
 AnimatorDebugMonitor.LogType type = AnimatorDebugMonitor.LogType.DEFAULT;
 int tick;
}

class MonitoredLayer {
 int index;
 std::string nodeName = "";
 HashMap<String, AnimatorDebugMonitor.MonitoredNode> activeNodes =
 std::make_unique<HashMap<>>();
 HashMap<String, AnimatorDebugMonitor.MonitoredTrack> animTracks =
 std::make_unique<HashMap<>>();
 bool active = false;
 bool updated = false;

public
 MonitoredLayer(int arg1) { this->index = arg1; }
}

class MonitoredNode {
 std::string name = "";
 bool active = false;
 bool updated = false;
}

class MonitoredTrack {
 std::string name = "";
 float blendDelta;
 bool active = false;
 bool updated = false;
}

class MonitoredVar {
 std::string key = "";
 std::string value = "";
 bool isFloat = false;
 float valFloat;
 bool active = false;
 bool updated = false;
 float[] f_floats;
 int f_index = 0;
 float f_min = -1.0F;
 float f_max = 1.0F;

 void logFloat(float arg0) {
 if (this->f_floats.empty()) {
 this->f_floats = new float[1024];
 }

 if (arg0 != this->valFloat) {
 this->valFloat = arg0;
 this->f_floats[this->f_index++] = arg0;
 if (arg0 < this->f_min) {
 this->f_min = arg0;
 }

 if (arg0 > this->f_max) {
 this->f_max = arg0;
 }

 if (this->f_index >= 1024) {
 this->f_index = 0;
 }
 }
 }
}
} // namespace debug
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
} // namespace zombie
