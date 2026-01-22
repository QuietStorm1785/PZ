#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {


class Color {
public:
    static const long serialVersionUID = 1393939L;
    static const Color transparent = std::make_shared<Color>(0.0F, 0.0F, 0.0F, 0.0F);
    static const Color white = std::make_shared<Color>(1.0F, 1.0F, 1.0F, 1.0F);
    static const Color yellow = std::make_shared<Color>(1.0F, 1.0F, 0.0F, 1.0F);
    static const Color red = std::make_shared<Color>(1.0F, 0.0F, 0.0F, 1.0F);
    static const Color purple = std::make_shared<Color>(196.0F, 0.0F, 171.0F);
    static const Color blue = std::make_shared<Color>(0.0F, 0.0F, 1.0F, 1.0F);
    static const Color green = std::make_shared<Color>(0.0F, 1.0F, 0.0F, 1.0F);
    static const Color black = std::make_shared<Color>(0.0F, 0.0F, 0.0F, 1.0F);
    static const Color gray = std::make_shared<Color>(0.5F, 0.5F, 0.5F, 1.0F);
    static const Color cyan = std::make_shared<Color>(0.0F, 1.0F, 1.0F, 1.0F);
    static const Color darkGray = std::make_shared<Color>(0.3F, 0.3F, 0.3F, 1.0F);
    static const Color lightGray = std::make_shared<Color>(0.7F, 0.7F, 0.7F, 1.0F);
    static const Color pink = std::make_shared<Color>(255, 175, 175, 255);
    static const Color orange = std::make_shared<Color>(255, 200, 0, 255);
    static const Color magenta = std::make_shared<Color>(255, 0, 255, 255);
    static const Color darkGreen = std::make_shared<Color>(22, 113, 20, 255);
    static const Color lightGreen = std::make_shared<Color>(55, 148, 53, 255);
    float a = 1.0F;
    float b;
    float g;
    float r;

    float getR() {
      return this.r;
   }

    float getG() {
      return this.g;
   }

    float getB() {
      return this.b;
   }

    public Color() {
   }

    public Color(Color var1) {
      if (var1 == nullptr) {
         this.r = 0.0F;
         this.g = 0.0F;
         this.b = 0.0F;
         this.a = 1.0F;
      } else {
         this.r = var1.r;
         this.g = var1.g;
         this.b = var1.b;
         this.a = var1.a;
      }
   }

    public Color(float var1, float var2, float var3) {
      this.r = var1;
      this.g = var2;
      this.b = var3;
      this.a = 1.0F;
   }

    public Color(float var1, float var2, float var3, float var4) {
      this.r = PZMath.clamp(var1, 0.0F, 1.0F);
      this.g = PZMath.clamp(var2, 0.0F, 1.0F);
      this.b = PZMath.clamp(var3, 0.0F, 1.0F);
      this.a = PZMath.clamp(var4, 0.0F, 1.0F);
   }

    public Color(Color var1, Color var2, float var3) {
    float var4 = (var2.r - var1.r) * var3;
    float var5 = (var2.g - var1.g) * var3;
    float var6 = (var2.b - var1.b) * var3;
    float var7 = (var2.a - var1.a) * var3;
      this.r = var1.r + var4;
      this.g = var1.g + var5;
      this.b = var1.b + var6;
      this.a = var1.a + var7;
   }

    void setColor(Color var1, Color var2, float var3) {
    float var4 = (var2.r - var1.r) * var3;
    float var5 = (var2.g - var1.g) * var3;
    float var6 = (var2.b - var1.b) * var3;
    float var7 = (var2.a - var1.a) * var3;
      this.r = var1.r + var4;
      this.g = var1.g + var5;
      this.b = var1.b + var6;
      this.a = var1.a + var7;
   }

    public Color(int var1, int var2, int var3) {
      this.r = var1 / 255.0F;
      this.g = var2 / 255.0F;
      this.b = var3 / 255.0F;
      this.a = 1.0F;
   }

    public Color(int var1, int var2, int var3, int var4) {
      this.r = var1 / 255.0F;
      this.g = var2 / 255.0F;
      this.b = var3 / 255.0F;
      this.a = var4 / 255.0F;
   }

    public Color(int var1) {
    int var2 = (var1 & 0xFF0000) >> 16;
    int var3 = (var1 & 0xFF00) >> 8;
    int var4 = var1 & 0xFF;
    int var5 = (var1 & 0xFF000000) >> 24;
      if (var5 < 0) {
         var5 += 256;
      }

      if (var5 == 0) {
         var5 = 255;
      }

      this.r = var4 / 255.0F;
      this.g = var3 / 255.0F;
      this.b = var2 / 255.0F;
      this.a = var5 / 255.0F;
   }

    void fromColor(int var1) {
    int var2 = (var1 & 0xFF0000) >> 16;
    int var3 = (var1 & 0xFF00) >> 8;
    int var4 = var1 & 0xFF;
    int var5 = (var1 & 0xFF000000) >> 24;
      if (var5 < 0) {
         var5 += 256;
      }

      if (var5 == 0) {
         var5 = 255;
      }

      this.r = var4 / 255.0F;
      this.g = var3 / 255.0F;
      this.b = var2 / 255.0F;
      this.a = var5 / 255.0F;
   }

    void setABGR(int var1) {
      abgrToColor(var1, this);
   }

    static Color abgrToColor(int var0, Color var1) {
    int var2 = var0 >> 24 & 0xFF;
    int var3 = var0 >> 16 & 0xFF;
    int var4 = var0 >> 8 & 0xFF;
    int var5 = var0 & 0xFF;
    float var6 = 0.003921569F * var5;
    float var7 = 0.003921569F * var4;
    float var8 = 0.003921569F * var3;
    float var9 = 0.003921569F * var2;
      var1.r = var6;
      var1.g = var7;
      var1.b = var8;
      var1.a = var9;
    return var1;
   }

    static int colorToABGR(Color var0) {
    return colorToABGR();
   }

    static int colorToABGR(float var0, float var1, float var2, float var3) {
      var0 = PZMath.clamp(var0, 0.0F, 1.0F);
      var1 = PZMath.clamp(var1, 0.0F, 1.0F);
      var2 = PZMath.clamp(var2, 0.0F, 1.0F);
      var3 = PZMath.clamp(var3, 0.0F, 1.0F);
    int var4 = (int)(var0 * 255.0F);
    int var5 = (int)(var1 * 255.0F);
    int var6 = (int)(var2 * 255.0F);
    int var7 = (int)(var3 * 255.0F);
      return (var7 & 0xFF) << 24 | (var6 & 0xFF) << 16 | (var5 & 0xFF) << 8 | var4 & 0xFF;
   }

    static int multiplyABGR(int var0, int var1) {
    float var2 = getRedChannelFromABGR(var0);
    float var3 = getGreenChannelFromABGR(var0);
    float var4 = getBlueChannelFromABGR(var0);
    float var5 = getAlphaChannelFromABGR(var0);
    float var6 = getRedChannelFromABGR(var1);
    float var7 = getGreenChannelFromABGR(var1);
    float var8 = getBlueChannelFromABGR(var1);
    float var9 = getAlphaChannelFromABGR(var1);
    return colorToABGR(var2 *, var3 *, var4 *, var5 *);
   }

    static int multiplyBGR(int var0, int var1) {
    float var2 = getRedChannelFromABGR(var0);
    float var3 = getGreenChannelFromABGR(var0);
    float var4 = getBlueChannelFromABGR(var0);
    float var5 = getAlphaChannelFromABGR(var0);
    float var6 = getRedChannelFromABGR(var1);
    float var7 = getGreenChannelFromABGR(var1);
    float var8 = getBlueChannelFromABGR(var1);
    return colorToABGR(var2 *, var3 *, var4 *);
   }

    static int blendBGR(int var0, int var1) {
    float var2 = getRedChannelFromABGR(var0);
    float var3 = getGreenChannelFromABGR(var0);
    float var4 = getBlueChannelFromABGR(var0);
    float var5 = getAlphaChannelFromABGR(var0);
    float var6 = getRedChannelFromABGR(var1);
    float var7 = getGreenChannelFromABGR(var1);
    float var8 = getBlueChannelFromABGR(var1);
    float var9 = getAlphaChannelFromABGR(var1);
    return colorToABGR(var2 *);
   }

    static int blendABGR(int var0, int var1) {
    float var2 = getRedChannelFromABGR(var0);
    float var3 = getGreenChannelFromABGR(var0);
    float var4 = getBlueChannelFromABGR(var0);
    float var5 = getAlphaChannelFromABGR(var0);
    float var6 = getRedChannelFromABGR(var1);
    float var7 = getGreenChannelFromABGR(var1);
    float var8 = getBlueChannelFromABGR(var1);
    float var9 = getAlphaChannelFromABGR(var1);
      return colorToABGR(
         var2 * (1.0F - var9) + var6 * var9, var3 * (1.0F - var9) + var7 * var9, var4 * (1.0F - var9) + var8 * var9, var5 * (1.0F - var9) + var9 * var9
      );
   }

    static int tintABGR(int var0, int var1) {
    float var2 = getRedChannelFromABGR(var1);
    float var3 = getGreenChannelFromABGR(var1);
    float var4 = getBlueChannelFromABGR(var1);
    float var5 = getAlphaChannelFromABGR(var1);
    float var6 = getRedChannelFromABGR(var0);
    float var7 = getGreenChannelFromABGR(var0);
    float var8 = getBlueChannelFromABGR(var0);
    float var9 = getAlphaChannelFromABGR(var0);
    return colorToABGR(var2 *);
   }

    static int lerpABGR(int var0, int var1, float var2) {
    float var3 = getRedChannelFromABGR(var0);
    float var4 = getGreenChannelFromABGR(var0);
    float var5 = getBlueChannelFromABGR(var0);
    float var6 = getAlphaChannelFromABGR(var0);
    float var7 = getRedChannelFromABGR(var1);
    float var8 = getGreenChannelFromABGR(var1);
    float var9 = getBlueChannelFromABGR(var1);
    float var10 = getAlphaChannelFromABGR(var1);
      return colorToABGR(
         var3 * (1.0F - var2) + var7 * var2, var4 * (1.0F - var2) + var8 * var2, var5 * (1.0F - var2) + var9 * var2, var6 * (1.0F - var2) + var10 * var2
      );
   }

    static float getAlphaChannelFromABGR(int var0) {
    int var1 = var0 >> 24 & 0xFF;
      return 0.003921569F * var1;
   }

    static float getBlueChannelFromABGR(int var0) {
    int var1 = var0 >> 16 & 0xFF;
      return 0.003921569F * var1;
   }

    static float getGreenChannelFromABGR(int var0) {
    int var1 = var0 >> 8 & 0xFF;
      return 0.003921569F * var1;
   }

    static float getRedChannelFromABGR(int var0) {
    int var1 = var0 & 0xFF;
      return 0.003921569F * var1;
   }

    static int setAlphaChannelToABGR(int var0, float var1) {
      var1 = PZMath.clamp(var1, 0.0F, 1.0F);
    int var2 = (int)(var1 * 255.0F);
      return (var2 & 0xFF) << 24 | var0 & 16777215;
   }

    static int setBlueChannelToABGR(int var0, float var1) {
      var1 = PZMath.clamp(var1, 0.0F, 1.0F);
    int var2 = (int)(var1 * 255.0F);
      return (var2 & 0xFF) << 16 | var0 & -16711681;
   }

    static int setGreenChannelToABGR(int var0, float var1) {
      var1 = PZMath.clamp(var1, 0.0F, 1.0F);
    int var2 = (int)(var1 * 255.0F);
      return (var2 & 0xFF) << 8 | var0 & -65281;
   }

    static int setRedChannelToABGR(int var0, float var1) {
      var1 = PZMath.clamp(var1, 0.0F, 1.0F);
    int var2 = (int)(var1 * 255.0F);
      return var2 & 0xFF | var0 & -256;
   }

    static Color random() {
      return Colors.GetRandomColor();
   }

    static Color decode(const std::string& var0) {
      return std::make_shared<Color>(int.decode(var0));
   }

    void add(Color var1) {
      this.r = this.r + var1.r;
      this.g = this.g + var1.g;
      this.b = this.b + var1.b;
      this.a = this.a + var1.a;
   }

    Color addToCopy(Color var1) {
    Color var2 = std::make_shared<Color>(this.r, this.g, this.b, this.a);
      var2.r = var2.r + var1.r;
      var2.g = var2.g + var1.g;
      var2.b = var2.b + var1.b;
      var2.a = var2.a + var1.a;
    return var2;
   }

    Color brighter() {
      return this.brighter(0.2F);
   }

    Color brighter(float var1) {
      this.r = this.r += var1;
      this.g = this.g += var1;
      this.b = this.b += var1;
    return this;
   }

    Color darker() {
      return this.darker(0.5F);
   }

    Color darker(float var1) {
      this.r = this.r -= var1;
      this.g = this.g -= var1;
      this.b = this.b -= var1;
    return this;
   }

    bool equals(void* var1) {
      return !(dynamic_cast<Color*>(var1) != nullptr var2) ? false : var2.r == this.r && var2.g == this.g && var2.b == this.b && var2.a == this.a;
   }

    Color set(Color var1) {
      this.r = var1.r;
      this.g = var1.g;
      this.b = var1.b;
      this.a = var1.a;
    return this;
   }

    Color set(float var1, float var2, float var3) {
      this.r = var1;
      this.g = var2;
      this.b = var3;
      this.a = 1.0F;
    return this;
   }

    Color set(float var1, float var2, float var3, float var4) {
      this.r = var1;
      this.g = var2;
      this.b = var3;
      this.a = var4;
    return this;
   }

    int getAlpha() {
      return (int)(this.a * 255.0F);
   }

    float getAlphaFloat() {
      return this.a;
   }

    float getRedFloat() {
      return this.r;
   }

    float getGreenFloat() {
      return this.g;
   }

    float getBlueFloat() {
      return this.b;
   }

    int getAlphaByte() {
      return (int)(this.a * 255.0F);
   }

    int getBlue() {
      return (int)(this.b * 255.0F);
   }

    int getBlueByte() {
      return (int)(this.b * 255.0F);
   }

    int getGreen() {
      return (int)(this.g * 255.0F);
   }

    int getGreenByte() {
      return (int)(this.g * 255.0F);
   }

    int getRed() {
      return (int)(this.r * 255.0F);
   }

    int getRedByte() {
      return (int)(this.r * 255.0F);
   }

    int hashCode() {
      return (int)(this.r + this.g + this.b + this.a) * 255;
   }

    Color multiply(Color var1) {
      return std::make_shared<Color>(this.r * var1.r, this.g * var1.g, this.b * var1.b, this.a * var1.a);
   }

    Color scale(float var1) {
      this.r *= var1;
      this.g *= var1;
      this.b *= var1;
      this.a *= var1;
    return this;
   }

    Color scaleCopy(float var1) {
    Color var2 = std::make_shared<Color>(this.r, this.g, this.b, this.a);
      var2.r *= var1;
      var2.g *= var1;
      var2.b *= var1;
      var2.a *= var1;
    return var2;
   }

    std::string toString() {
      return "Color (" + this.r + "," + this.g + "," + this.b + "," + this.a + ")";
   }

    void interp(Color var1, float var2, Color var3) {
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

    void changeHSBValue(float var1, float var2, float var3) {
      float[] var4 = java.awt.Color.RGBtoHSB(this.getRedByte(), this.getGreenByte(), this.getBlueByte(), nullptr);
    int var5 = java.awt.Color.HSBtoRGB(var4[0] * var1, var4[1] * var2, var4[2] * var3);
      this.r = (var5 >> 16 & 0xFF) / 255.0F;
      this.g = (var5 >> 8 & 0xFF) / 255.0F;
      this.b = (var5 & 0xFF) / 255.0F;
   }

    static Color HSBtoRGB(float var0, float var1, float var2, Color var3) {
    int var4 = 0;
    int var5 = 0;
    int var6 = 0;
      if (var1 == 0.0F) {
         var4 = var5 = var6 = (int)(var2 * 255.0F + 0.5F);
      } else {
    float var7 = (var0 - (float)Math.floor(var0)) * 6.0F;
    float var8 = var7 - (float)Math.floor(var7);
    float var9 = var2 * (1.0F - var1);
    float var10 = var2 * (1.0F - var1 * var8);
    float var11 = var2 * (1.0F - var1 * (1.0F - var8));
         switch ((int)var7) {
            case 0:
               var4 = (int)(var2 * 255.0F + 0.5F);
               var5 = (int)(var11 * 255.0F + 0.5F);
               var6 = (int)(var9 * 255.0F + 0.5F);
               break;
            case 1:
               var4 = (int)(var10 * 255.0F + 0.5F);
               var5 = (int)(var2 * 255.0F + 0.5F);
               var6 = (int)(var9 * 255.0F + 0.5F);
               break;
            case 2:
               var4 = (int)(var9 * 255.0F + 0.5F);
               var5 = (int)(var2 * 255.0F + 0.5F);
               var6 = (int)(var11 * 255.0F + 0.5F);
               break;
            case 3:
               var4 = (int)(var9 * 255.0F + 0.5F);
               var5 = (int)(var10 * 255.0F + 0.5F);
               var6 = (int)(var2 * 255.0F + 0.5F);
               break;
            case 4:
               var4 = (int)(var11 * 255.0F + 0.5F);
               var5 = (int)(var9 * 255.0F + 0.5F);
               var6 = (int)(var2 * 255.0F + 0.5F);
               break;
            case 5:
               var4 = (int)(var2 * 255.0F + 0.5F);
               var5 = (int)(var9 * 255.0F + 0.5F);
               var6 = (int)(var10 * 255.0F + 0.5F);
         }
      }

      return var3.set(var4 / 255.0F, var5 / 255.0F, var6 / 255.0F);
   }

    static Color HSBtoRGB(float var0, float var1, float var2) {
    return HSBtoRGB(std::make_shared<Color>();
   }
}
} // namespace core
} // namespace zombie
