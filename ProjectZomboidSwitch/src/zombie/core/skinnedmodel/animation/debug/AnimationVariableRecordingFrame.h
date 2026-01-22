#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/advancedanimation/IAnimationVariableSlot.h"
#include "zombie/core/skinnedmodel/advancedanimation/IAnimationVariableSource.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
namespace debug {


class AnimationVariableRecordingFrame : public GenericNameValueRecordingFrame {
public:
   private std::string[] m_variableValues = new std::string[0];

    public AnimationVariableRecordingFrame(const std::string& var1) {
      super(var1, "_values");
   }

    void logVariables(IAnimationVariableSource var1) {
      for (IAnimationVariableSlot var3 : var1.getGameVariables()) {
         this.logVariable(var3.getKey(), var3.getValueString());
      }
   }

    void onColumnAdded() {
      this.m_variableValues = (std::string[])PZArrayUtil.push_back(this.m_variableValues, nullptr);
   }

    void logVariable(const std::string& var1, const std::string& var2) {
    int var3 = this.getOrCreateColumn(var1);
      if (this.m_variableValues[var3] != nullptr) {
         DebugLog.General.error("Value for %s already set: %f, new value: %f", new Object[]{var1, this.m_variableValues[var3], var2});
      }

      this.m_variableValues[var3] = var2;
   }

    std::string getValueAt(int var1) {
      return this.m_variableValues[var1];
   }

    void reset() {
    int var1 = 0;

      for (int var2 = this.m_variableValues.length; var1 < var2; var1++) {
         this.m_variableValues[var1] = nullptr;
      }
   }
}
} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
