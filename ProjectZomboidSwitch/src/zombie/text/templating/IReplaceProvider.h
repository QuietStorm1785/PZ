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

class IReplaceProvider {
public:
    virtual ~IReplaceProvider() = default;
    bool hasReplacer(const std::string& var1);

    IReplace getReplacer(const std::string& var1);
}
} // namespace templating
} // namespace text
} // namespace zombie
