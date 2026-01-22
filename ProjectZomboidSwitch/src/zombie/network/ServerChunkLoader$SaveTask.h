#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class ServerChunkLoader {
public:
    virtual ~ServerChunkLoader() = default;
    void save();

    void release();

    int wx();

    int wy();
}
} // namespace network
} // namespace zombie
