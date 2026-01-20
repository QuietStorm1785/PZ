#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace istack {

class Pool {
public:
    virtual ~Pool() = default;
    T take();

    void recycle(@NotNull T);
}
} // namespace istack
} // namespace sun
} // namespace com
