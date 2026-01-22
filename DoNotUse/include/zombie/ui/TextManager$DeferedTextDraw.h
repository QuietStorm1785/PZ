#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ui {

class TextManager {
public:
    double x;
    double y;
    UIFont font;
    std::string str;
    double r;
    double g;
    double b;
    double a;

   public TextManager$DeferedTextDraw(UIFont var1, double var2, double var4, std::string var6, double var7, double var9, double var11, double var13) {
      this.font = var1;
      this.x = var2;
      this.y = var4;
      this.str = var6;
      this.r = var7;
      this.g = var9;
      this.b = var11;
      this.a = var13;
   }
}
} // namespace ui
} // namespace zombie
