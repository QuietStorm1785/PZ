#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace debug {
namespace options {

class IDebugOption {
public:
    virtual ~IDebugOption() = default;
    std::string getName();

    IDebugOptionGroup getParent();

    void setParent(IDebugOptionGroup var1);
}
} // namespace options
} // namespace debug
} // namespace zombie
