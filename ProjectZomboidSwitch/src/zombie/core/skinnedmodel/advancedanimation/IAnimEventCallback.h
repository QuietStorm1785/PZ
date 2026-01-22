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

class IAnimEventCallback {
public:
    virtual ~IAnimEventCallback() = default;
    void OnAnimEvent(AnimLayer var1, AnimEvent var2);
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
