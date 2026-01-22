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

class AnimationVariableHandle {
public:
    std::string m_name = nullptr;
    int m_varIndex = -1;

   AnimationVariableHandle() {
   }

    static AnimationVariableHandle alloc(const std::string& var0) {
      return AnimationVariableHandlePool.getOrCreate(var0);
   }

    std::string getVariableName() {
      return this.m_name;
   }

    int getVariableIndex() {
      return this.m_varIndex;
   }

    void setVariableName(const std::string& var1) {
      this.m_name = var1;
   }

    void setVariableIndex(int var1) {
      this.m_varIndex = var1;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
