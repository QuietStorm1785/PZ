#pragma once
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SliceY {
public:
  static const ByteBuffer SliceBuffer = ByteBuffer.allocate(10485760);
  static const void *SliceBufferLock = "SliceY SliceBufferLock";
}
} // namespace iso
} // namespace zombie
