#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace interfaces {

class IDestroyable {
public:
    virtual ~IDestroyable() = default;
    void destroy();

    bool isDestroyed();
}
} // namespace interfaces
} // namespace zombie
