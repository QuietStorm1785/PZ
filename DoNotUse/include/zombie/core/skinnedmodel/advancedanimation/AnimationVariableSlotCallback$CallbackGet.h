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
    VariableType call();
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
