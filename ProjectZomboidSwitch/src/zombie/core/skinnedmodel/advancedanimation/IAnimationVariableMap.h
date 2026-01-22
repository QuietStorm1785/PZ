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

class IAnimationVariableMap {
public:
    virtual ~IAnimationVariableMap() = default;
    IAnimationVariableSlot getOrCreateVariable(const std::string& var1);

    void setVariable(IAnimationVariableSlot var1);

    void setVariable(const std::string& var1, const std::string& var2);

    void setVariable(const std::string& var1, bool var2);

    void setVariable(const std::string& var1, float var2);

    void clearVariable(const std::string& var1);

    void clearVariables();
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
