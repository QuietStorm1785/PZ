#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace popman {

class ObjectPool {
public:
    virtual ~ObjectPool() = default;
    T allocate();
}
} // namespace popman
} // namespace zombie
