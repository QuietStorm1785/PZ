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

class IAnimationVariableSlot {
public:
    virtual ~IAnimationVariableSlot() = default;
    std::string getKey();

    std::string getValueString();

    float getValueFloat();

    bool getValueBool();

    void setValue(const std::string& var1);

    void setValue(float var1);

    void setValue(bool var1);

    AnimationVariableType getType();

    bool canConvertFrom(const std::string& var1);

    void clear();

   default boolean isReadOnly() {
    return false;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
