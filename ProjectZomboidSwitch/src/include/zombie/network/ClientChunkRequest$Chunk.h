#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace zombie {
namespace network {


class ClientChunkRequest {
public:
    int requestNumber;
    int wx;
    int wy;
    long crc;
    ByteBuffer bb;
}
} // namespace network
} // namespace zombie
