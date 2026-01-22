#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {
namespace action {

class IActionStateChanged {
public:
    virtual ~IActionStateChanged() = default;
    void actionStateChanged(ActionContext var1);
}
} // namespace action
} // namespace characters
} // namespace zombie
