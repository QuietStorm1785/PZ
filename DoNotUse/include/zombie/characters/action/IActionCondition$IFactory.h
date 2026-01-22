#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/w3c/dom/Element.h"

namespace zombie {
namespace characters {
namespace action {


class IActionCondition {
public:
    virtual ~IActionCondition() = default;
    IActionCondition create(Element var1);
}
} // namespace action
} // namespace characters
} // namespace zombie
