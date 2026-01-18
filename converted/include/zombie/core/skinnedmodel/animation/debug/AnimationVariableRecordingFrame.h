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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AnimationVariableRecordingFrame : public GenericNameValueRecordingFrame {
public:
 private String[] m_variableValues = new String[0];

 public AnimationVariableRecordingFrame(const std::string& fileKey) {
 super(fileKey, "_values");
 }

 void logVariables(IAnimationVariableSource varSource) {
 for (IAnimationVariableSlot iAnimationVariableSlot : varSource.getGameVariables()) {
 this->logVariable(iAnimationVariableSlot.getKey(), iAnimationVariableSlot.getValueString());
 }
 }

 void onColumnAdded() {
 this->m_variableValues = PZArrayUtil.add(this->m_variableValues, nullptr);
 }

 void logVariable(const std::string& name, const std::string& val) {
 int int0 = this->getOrCreateColumn(name);
 if (this->m_variableValues[int0] != nullptr) {
 DebugLog.General.error("Value for %s already set: %f, new value: %f", name, this->m_variableValues[int0], val);
 }

 this->m_variableValues[int0] = val;
 }

 std::string getValueAt(int i) {
 return this->m_variableValues[i];
 }

 void reset() {
 int int0 = 0;

 for (int int1 = this->m_variableValues.length; int0 < int1; int0++) {
 this->m_variableValues[int0] = nullptr;
 }
 }
}
} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
