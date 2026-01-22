#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/ai/StateMachine/SubstateSlot.h"
#include "zombie/characters/action/ActionState.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimState.h"
#include "zombie/iso/Vector3.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
namespace debug {


class AnimationNodeRecordingFrame : public GenericNameWeightRecordingFrame {
public:
    std::string m_actionStateName;
   private const std::vector<std::string> m_actionSubStateNames = std::make_unique<std::vector<>>();
    std::string m_aiStateName;
    std::string m_animStateName;
   private const std::vector<std::string> m_animSubStateNames = std::make_unique<std::vector<>>();
   private const std::vector<std::string> m_aiSubStateNames = std::make_unique<std::vector<>>();
    const Vector3 m_characterToPlayerDiff = std::make_shared<Vector3>();

    public AnimationNodeRecordingFrame(const std::string& var1) {
      super(var1);
   }

    void logActionState(ActionState var1, List<ActionState> var2) {
      this.m_actionStateName = var1 != nullptr ? var1.getName() : nullptr;
      PZArrayUtil.arrayConvert(this.m_actionSubStateNames, var2, ActionState::getName);
   }

    void logAIState(State var1, List<SubstateSlot> var2) {
      this.m_aiStateName = var1 != nullptr ? var1.getName() : nullptr;
      PZArrayUtil.arrayConvert(this.m_aiSubStateNames, var2, var0 -> !var0.empty() ? var0.getState().getName() : "");
   }

    void logAnimState(AnimState var1) {
      this.m_animStateName = var1 != nullptr ? var1.m_Name : nullptr;
   }

    void logCharacterToPlayerDiff(Vector3 var1) {
      this.m_characterToPlayerDiff.set(var1);
   }

    void writeHeader(std::stringstream var1) {
      appendCell(var1, "toPlayer.x");
      appendCell(var1, "toPlayer.y");
      appendCell(var1, "actionState");
      appendCell(var1, "actionState.sub[0]");
      appendCell(var1, "actionState.sub[1]");
      appendCell(var1, "aiState");
      appendCell(var1, "aiState.sub[0]");
      appendCell(var1, "aiState.sub[1]");
      appendCell(var1, "animState");
      appendCell(var1, "animState.sub[0]");
      appendCell(var1, "animState.sub[1]");
      appendCell(var1, "nodeWeights.begin");
      super.writeHeader(var1);
   }

    void writeData(std::stringstream var1) {
      appendCell(var1, this.m_characterToPlayerDiff.x);
      appendCell(var1, this.m_characterToPlayerDiff.y);
      appendCellQuot(var1, this.m_actionStateName);
      appendCellQuot(var1, (std::string)PZArrayUtil.getOrDefault(this.m_actionSubStateNames, 0, ""));
      appendCellQuot(var1, (std::string)PZArrayUtil.getOrDefault(this.m_actionSubStateNames, 1, ""));
      appendCellQuot(var1, this.m_aiStateName);
      appendCellQuot(var1, (std::string)PZArrayUtil.getOrDefault(this.m_aiSubStateNames, 0, ""));
      appendCellQuot(var1, (std::string)PZArrayUtil.getOrDefault(this.m_aiSubStateNames, 1, ""));
      appendCellQuot(var1, this.m_animStateName);
      appendCellQuot(var1, (std::string)PZArrayUtil.getOrDefault(this.m_animSubStateNames, 0, ""));
      appendCellQuot(var1, (std::string)PZArrayUtil.getOrDefault(this.m_animSubStateNames, 1, ""));
      appendCell(var1);
      super.writeData(var1);
   }
}
} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
