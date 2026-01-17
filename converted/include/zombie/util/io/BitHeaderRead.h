#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace io {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BitHeaderRead {
public:
  virtual ~BitHeaderRead() = default;
  int getStartPosition();

  void read();

  bool hasFlags(int var1);

  bool hasFlags(long var1);

  bool equals(int var1);

  bool equals(long var1);

  int getLen();

  void release();
}
} // namespace io
} // namespace util
} // namespace zombie
