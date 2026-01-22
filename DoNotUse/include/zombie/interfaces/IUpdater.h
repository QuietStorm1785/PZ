#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace interfaces {

class IUpdater {
public:
    virtual ~IUpdater() = default;
    void render();

    void renderlast();

    void update();
}
} // namespace interfaces
} // namespace zombie
