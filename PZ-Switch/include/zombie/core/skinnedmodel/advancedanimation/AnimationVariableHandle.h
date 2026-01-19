#pragma once
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

class AnimationVariableHandle {
public:
 std::string m_name = nullptr;
 int m_varIndex = -1;

 AnimationVariableHandle() {}

 static AnimationVariableHandle alloc(std::string_view name) {
 return AnimationVariableHandlePool.getOrCreate(name);
 }

 std::string getVariableName() { return this->m_name; }

 int getVariableIndex() { return this->m_varIndex; }

 void setVariableName(std::string_view string) { this->m_name = string; }

 void setVariableIndex(int int0) { this->m_varIndex = int0; }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
