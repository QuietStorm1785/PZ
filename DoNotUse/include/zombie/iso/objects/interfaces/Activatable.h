#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace objects {
namespace interfaces {

class Activatable {
public:
    virtual ~Activatable() = default;
    bool Activated();

    void Toggle();

    std::string getActivatableType();
}
} // namespace interfaces
} // namespace objects
} // namespace iso
} // namespace zombie
