#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace zombie {
namespace iso {


class SliceY {
public:
    static const ByteBuffer SliceBuffer = ByteBuffer.allocate(10485760);
    static const void* SliceBufferLock = "SliceY SliceBufferLock";
}
} // namespace iso
} // namespace zombie
