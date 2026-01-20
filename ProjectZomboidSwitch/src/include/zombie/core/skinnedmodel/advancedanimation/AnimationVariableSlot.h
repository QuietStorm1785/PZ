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

class AnimationVariableSlot {
public:
    const std::string m_key;

    protected AnimationVariableSlot(const std::string& var1) {
      this.m_key = var1.toLowerCase().trim();
   }

    std::string getKey() {
      return this.m_key;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
