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

class AnimationVariableSlotCallback {
public:
    virtual ~AnimationVariableSlotCallback() = default;
    void call(VariableType var1);
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
