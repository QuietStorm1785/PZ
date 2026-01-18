#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BitMatrix {
public:
  static bool Is(int int3, int int2, int int1, int int0) {
    return (1 << (int2 + 1) * 9 + (int1 + 1) * 3 + int0 + 1 & int3) ==
           1 << (int2 + 1) * 9 + (int1 + 1) * 3 + int0 + 1;
  }

  static int Set(int int0, int int3, int int2, int int1, bool boolean0) {
    if (boolean0) {
      int0 |= 1 << (int3 + 1) * 9 + (int2 + 1) * 3 + int1 + 1;
    } else {
      int0 &= ~(1 << (int3 + 1) * 9 + (int2 + 1) * 3 + int1 + 1);
    }

    return int0;
  }
}
} // namespace zombie
