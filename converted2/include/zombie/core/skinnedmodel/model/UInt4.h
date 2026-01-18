#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by LEMMYATI on 03/01/14.
 */
class UInt4 {
public:
  int X;
  int Y;
  int Z;
  int W;

public
  UInt4(int x, int y, int z, int w) {
    this.X = x;
    this.Y = y;
    this.Z = z;
    this.W = w;
  }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
