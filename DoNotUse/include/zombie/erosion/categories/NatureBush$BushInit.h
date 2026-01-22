#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace erosion {
namespace categories {

class NatureBush {
public:
    std::string name;
    float bloomstart;
    float bloomend;
    bool hasFlower;

   public NatureBush$BushInit(NatureBush var1, std::string var2, float var3, float var4, boolean var5) {
      this.this$0 = var1;
      this.name = var2;
      this.bloomstart = var3;
      this.bloomend = var4;
      this.hasFlower = var5;
   }
}
} // namespace categories
} // namespace erosion
} // namespace zombie
