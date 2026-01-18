#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/ai/StateMachine.h"
#include "zombie/characters/action/ActionState.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimState.h"
#include "zombie/iso/Vector3.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
namespace debug {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AnimationNodeRecordingFrame : public GenericNameWeightRecordingFrame {
public:
 std::string m_actionStateName;
 private ArrayList<String> m_actionSubStateNames = std::make_unique<ArrayList<>>();
 std::string m_aiStateName;
 std::string m_animStateName;
 private ArrayList<String> m_animSubStateNames = std::make_unique<ArrayList<>>();
 private ArrayList<String> m_aiSubStateNames = std::make_unique<ArrayList<>>();
 const Vector3 m_characterToPlayerDiff = new Vector3();

 public AnimationNodeRecordingFrame(const std::string& fileKey) {
 super(fileKey);
 }

 void logActionState(ActionState state, List<ActionState> childStates) {
 this->m_actionStateName = state != nullptr ? state.getName() : nullptr;
 PZArrayUtil.arrayConvert(this->m_actionSubStateNames, childStates, ActionState::getName);
 }

 void logAIState(State state, List<StateMachine.SubstateSlot> subStates) {
 this->m_aiStateName = state != nullptr ? state.getName() : nullptr;
 PZArrayUtil.arrayConvert(this->m_aiSubStateNames, subStates, substateSlot -> !substateSlot.empty() ? substateSlot.getState().getName() : "");
 }

 void logAnimState(AnimState state) {
 this->m_animStateName = state != nullptr ? state.m_Name : nullptr;
 }

 void logCharacterToPlayerDiff(Vector3 diff) {
 this->m_characterToPlayerDiff.set(diff);
 }

 void writeHeader(StringBuilder logLine) {
 appendCell(logLine, "toPlayer.x");
 appendCell(logLine, "toPlayer.y");
 appendCell(logLine, "actionState");
 appendCell(logLine, "actionState.sub[0]");
 appendCell(logLine, "actionState.sub[1]");
 appendCell(logLine, "aiState");
 appendCell(logLine, "aiState.sub[0]");
 appendCell(logLine, "aiState.sub[1]");
 appendCell(logLine, "animState");
 appendCell(logLine, "animState.sub[0]");
 appendCell(logLine, "animState.sub[1]");
 appendCell(logLine, "nodeWeights.begin");
 super.writeHeader(logLine);
 }

 void writeData(StringBuilder stringBuilder) {
 appendCell(stringBuilder, this->m_characterToPlayerDiff.x);
 appendCell(stringBuilder, this->m_characterToPlayerDiff.y);
 appendCellQuot(stringBuilder, this->m_actionStateName);
 appendCellQuot(stringBuilder, PZArrayUtil.getOrDefault(this->m_actionSubStateNames, 0, ""));
 appendCellQuot(stringBuilder, PZArrayUtil.getOrDefault(this->m_actionSubStateNames, 1, ""));
 appendCellQuot(stringBuilder, this->m_aiStateName);
 appendCellQuot(stringBuilder, PZArrayUtil.getOrDefault(this->m_aiSubStateNames, 0, ""));
 appendCellQuot(stringBuilder, PZArrayUtil.getOrDefault(this->m_aiSubStateNames, 1, ""));
 appendCellQuot(stringBuilder, this->m_animStateName);
 appendCellQuot(stringBuilder, PZArrayUtil.getOrDefault(this->m_animSubStateNames, 0, ""));
 appendCellQuot(stringBuilder, PZArrayUtil.getOrDefault(this->m_animSubStateNames, 1, ""));
 appendCell(stringBuilder);
 super.writeData(stringBuilder);
 }
}
} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
