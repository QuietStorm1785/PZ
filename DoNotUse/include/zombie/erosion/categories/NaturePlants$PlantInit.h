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

class NaturePlants {
public:
    std::string name;
    bool hasFlower;
    float bloomstart;
    float bloomend;

   public NaturePlants$PlantInit(NaturePlants var1, std::string var2, boolean var3, float var4, float var5) {
      this.this$0 = var1;
      this.name = var2;
      this.hasFlower = var3;
      this.bloomstart = var4;
      this.bloomend = var5;
   }
}
} // namespace categories
} // namespace erosion
} // namespace zombie
