#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"
#include "zombie/core/ImmutableColor.h"

namespace zombie {
namespace core {
namespace textures {


class ColorInfo {
public:
    float a = 1.0F;
    float b = 1.0F;
    float g = 1.0F;
    float r = 1.0F;

    public ColorInfo() {
      this.r = 1.0F;
      this.g = 1.0F;
      this.b = 1.0F;
      this.a = 1.0F;
   }

    public ColorInfo(float var1, float var2, float var3, float var4) {
      this.r = var1;
      this.g = var2;
      this.b = var3;
      this.a = var4;
   }

    ColorInfo set(ColorInfo var1) {
      this.r = var1.r;
      this.g = var1.g;
      this.b = var1.b;
      this.a = var1.a;
    return this;
   }

    ColorInfo set(float var1, float var2, float var3, float var4) {
      this.r = var1;
      this.g = var2;
      this.b = var3;
      this.a = var4;
    return this;
   }

    float getR() {
      return this.r;
   }

    float getG() {
      return this.g;
   }

    float getB() {
      return this.b;
   }

    Color toColor() {
      return std::make_shared<Color>(this.r, this.g, this.b, this.a);
   }

    ImmutableColor toImmutableColor() {
      return std::make_shared<ImmutableColor>(this.r, this.g, this.b, this.a);
   }

    float getA() {
      return this.a;
   }

    void desaturate(float var1) {
    float var2 = this.r * 0.3086F + this.g * 0.6094F + this.b * 0.082F;
      this.r = var2 * var1 + this.r * (1.0F - var1);
      this.g = var2 * var1 + this.g * (1.0F - var1);
      this.b = var2 * var1 + this.b * (1.0F - var1);
   }

    void interp(ColorInfo var1, float var2, ColorInfo var3) {
    float var4 = var1.r - this.r;
    float var5 = var1.g - this.g;
    float var6 = var1.b - this.b;
    float var7 = var1.a - this.a;
      var4 *= var2;
      var5 *= var2;
      var6 *= var2;
      var7 *= var2;
      var3.r = this.r + var4;
      var3.g = this.g + var5;
      var3.b = this.b + var6;
      var3.a = this.a + var7;
   }

    std::string toString() {
      return "Color (" + this.r + "," + this.g + "," + this.b + "," + this.a + ")";
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
