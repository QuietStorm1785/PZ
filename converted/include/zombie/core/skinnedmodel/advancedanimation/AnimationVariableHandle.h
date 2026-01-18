#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class AnimationVariableHandle {
public:
 std::string m_name = nullptr;
 int m_varIndex = -1;

 AnimationVariableHandle() {
 }

 static AnimationVariableHandle alloc(const std::string& name) {
 return AnimationVariableHandlePool.getOrCreate(name);
 }

 std::string getVariableName() {
 return this->m_name;
 }

 int getVariableIndex() {
 return this->m_varIndex;
 }

 void setVariableName(const std::string& string) {
 this->m_name = string;
 }

 void setVariableIndex(int int0) {
 this->m_varIndex = int0;
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
