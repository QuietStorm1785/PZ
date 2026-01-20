#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace textures {

class TexturePackPage {
public:
    int w;
    int h;
    int x;
    int y;
    int ox;
    int oy;
    int fx;
    int fy;
    std::string name;

   public TexturePackPage$SubTextureInfo(int var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, std::string var9) {
      this.x = var1;
      this.y = var2;
      this.w = var3;
      this.h = var4;
      this.ox = var5;
      this.oy = var6;
      this.fx = var7;
      this.fy = var8;
      this.name = var9;
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
