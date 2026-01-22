#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {

class UInt4 {
public:
    int X;
    int Y;
    int Z;
    int W;

    public UInt4(int var1, int var2, int var3, int var4) {
      this.X = var1;
      this.Y = var2;
      this.Z = var3;
      this.W = var4;
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
