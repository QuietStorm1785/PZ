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

class IAnimationVariableSource {
public:
    virtual ~IAnimationVariableSource() = default;
    IAnimationVariableSlot getVariable(AnimationVariableHandle var1);

    IAnimationVariableSlot getVariable(const std::string& var1);

    std::string getVariableString(const std::string& var1);

    float getVariableFloat(const std::string& var1, float var2);

    bool getVariableBoolean(const std::string& var1);

    bool getVariableBoolean(const std::string& var1, bool var2);

   Iterable<IAnimationVariableSlot> getGameVariables();

    bool isVariable(const std::string& var1, const std::string& var2);

    bool containsVariable(const std::string& var1);
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
