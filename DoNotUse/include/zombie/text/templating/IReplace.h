#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace text {
namespace templating {

class IReplace {
public:
    virtual ~IReplace() = default;
    std::string getString();
}
} // namespace templating
} // namespace text
} // namespace zombie
