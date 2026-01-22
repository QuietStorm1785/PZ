#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace core {


class ImmutableColor {
public:
    static const ImmutableColor transparent = std::make_shared<ImmutableColor>(0.0F, 0.0F, 0.0F, 0.0F);
    static const ImmutableColor white = std::make_shared<ImmutableColor>(1.0F, 1.0F, 1.0F, 1.0F);
    static const ImmutableColor yellow = std::make_shared<ImmutableColor>(1.0F, 1.0F, 0.0F, 1.0F);
    static const ImmutableColor red = std::make_shared<ImmutableColor>(1.0F, 0.0F, 0.0F, 1.0F);
    static const ImmutableColor purple = std::make_shared<ImmutableColor>(196.0F, 0.0F, 171.0F);
    static const ImmutableColor blue = std::make_shared<ImmutableColor>(0.0F, 0.0F, 1.0F, 1.0F);
    static const ImmutableColor green = std::make_shared<ImmutableColor>(0.0F, 1.0F, 0.0F, 1.0F);
    static const ImmutableColor black = std::make_shared<ImmutableColor>(0.0F, 0.0F, 0.0F, 1.0F);
    static const ImmutableColor gray = std::make_shared<ImmutableColor>(0.5F, 0.5F, 0.5F, 1.0F);
    static const ImmutableColor cyan = std::make_shared<ImmutableColor>(0.0F, 1.0F, 1.0F, 1.0F);
    static const ImmutableColor darkGray = std::make_shared<ImmutableColor>(0.3F, 0.3F, 0.3F, 1.0F);
    static const ImmutableColor lightGray = std::make_shared<ImmutableColor>(0.7F, 0.7F, 0.7F, 1.0F);
    static const ImmutableColor pink = std::make_shared<ImmutableColor>(255, 175, 175, 255);
    static const ImmutableColor orange = std::make_shared<ImmutableColor>(255, 200, 0, 255);
    static const ImmutableColor magenta = std::make_shared<ImmutableColor>(255, 0, 255, 255);
    static const ImmutableColor darkGreen = std::make_shared<ImmutableColor>(22, 113, 20, 255);
    static const ImmutableColor lightGreen = std::make_shared<ImmutableColor>(55, 148, 53, 255);
    const float a;
    const float b;
    const float g;
    const float r;

    public ImmutableColor(ImmutableColor var1) {
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

    public ImmutableColor(Color var1) {
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

    Color toMutableColor() {
      return std::make_shared<Color>(this.r, this.g, this.b, this.a);
   }

    public ImmutableColor(float var1, float var2, float var3) {
      this.r = PZMath.clamp(var1, 0.0F, 1.0F);
      this.g = PZMath.clamp(var2, 0.0F, 1.0F);
      this.b = PZMath.clamp(var3, 0.0F, 1.0F);
      this.a = 1.0F;
   }

    public ImmutableColor(float var1, float var2, float var3, float var4) {
      this.r = Math.min(var1, 1.0F);
      this.g = Math.min(var2, 1.0F);
      this.b = Math.min(var3, 1.0F);
      this.a = Math.min(var4, 1.0F);
   }

    public ImmutableColor(Color var1, Color var2, float var3) {
    float var4 = (var2.r - var1.r) * var3;
    float var5 = (var2.g - var1.g) * var3;
    float var6 = (var2.b - var1.b) * var3;
    float var7 = (var2.a - var1.a) * var3;
      this.r = var1.r + var4;
      this.g = var1.g + var5;
      this.b = var1.b + var6;
      this.a = var1.a + var7;
   }

    public ImmutableColor(int var1, int var2, int var3) {
      this.r = var1 / 255.0F;
      this.g = var2 / 255.0F;
      this.b = var3 / 255.0F;
      this.a = 1.0F;
   }

    public ImmutableColor(int var1, int var2, int var3, int var4) {
      this.r = var1 / 255.0F;
      this.g = var2 / 255.0F;
      this.b = var3 / 255.0F;
      this.a = var4 / 255.0F;
   }

    public ImmutableColor(int var1) {
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

    static ImmutableColor random() {
    float var0 = Rand.Next(0.0F, 1.0F);
    float var1 = Rand.Next(0.0F, 0.6F);
    float var2 = Rand.Next(0.0F, 0.9F);
    Color var3 = Color.HSBtoRGB(var0, var1, var2);
      return std::make_shared<ImmutableColor>(var3);
   }

    static ImmutableColor decode(const std::string& var0) {
      return std::make_shared<ImmutableColor>(int.decode(var0));
   }

    ImmutableColor add(ImmutableColor var1) {
      return std::make_shared<ImmutableColor>(this.r + var1.r, this.g + var1.g, this.b + var1.b, this.a + var1.a);
   }

    ImmutableColor brighter() {
      return this.brighter(0.2F);
   }

    ImmutableColor brighter(float var1) {
      return std::make_shared<ImmutableColor>(this.r + var1, this.g + var1, this.b + var1);
   }

    ImmutableColor darker() {
      return this.darker(0.5F);
   }

    ImmutableColor darker(float var1) {
      return std::make_shared<ImmutableColor>(this.r - var1, this.g - var1, this.b - var1);
   }

    bool equals(void* var1) {
      return !(dynamic_cast<ImmutableColor*>(var1) != nullptr var2) ? false : var2.r == this.r && var2.g == this.g && var2.b == this.b && var2.a == this.a;
   }

    int getAlphaInt() {
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

    uint8_t getAlphaByte() {
      return (byte)((int)(this.a * 255.0F) & 0xFF);
   }

    int getBlueInt() {
      return (int)(this.b * 255.0F);
   }

    uint8_t getBlueByte() {
      return (byte)((int)(this.b * 255.0F) & 0xFF);
   }

    int getGreenInt() {
      return (int)(this.g * 255.0F);
   }

    uint8_t getGreenByte() {
      return (byte)((int)(this.g * 255.0F) & 0xFF);
   }

    int getRedInt() {
      return (int)(this.r * 255.0F);
   }

    uint8_t getRedByte() {
      return (byte)((int)(this.r * 255.0F) & 0xFF);
   }

    int hashCode() {
      return (int)(this.r + this.g + this.b + this.a) * 255;
   }

    ImmutableColor multiply(Color var1) {
      return std::make_shared<ImmutableColor>(this.r * var1.r, this.g * var1.g, this.b * var1.b, this.a * var1.a);
   }

    ImmutableColor scale(float var1) {
      return std::make_shared<ImmutableColor>(this.r * var1, this.g * var1, this.b * var1, this.a * var1);
   }

    std::string toString() {
      return "ImmutableColor (" + this.r + "," + this.g + "," + this.b + "," + this.a + ")";
   }

    ImmutableColor interp(ImmutableColor var1, float var2) {
    float var3 = var1.r - this.r;
    float var4 = var1.g - this.g;
    float var5 = var1.b - this.b;
    float var6 = var1.a - this.a;
      var3 *= var2;
      var4 *= var2;
      var5 *= var2;
      var6 *= var2;
      return std::make_shared<ImmutableColor>(this.r + var3, this.g + var4, this.b + var5, this.a + var6);
   }

   public static int[] HSBtoRGB(float var0, float var1, float var2) {
    int var3 = 0;
    int var4 = 0;
    int var5 = 0;
      if (var1 == 0.0F) {
         var3 = var4 = var5 = (int)(var2 * 255.0F + 0.5F);
      } else {
    float var6 = (var0 - (float)Math.floor(var0)) * 6.0F;
    float var7 = var6 - (float)Math.floor(var6);
    float var8 = var2 * (1.0F - var1);
    float var9 = var2 * (1.0F - var1 * var7);
    float var10 = var2 * (1.0F - var1 * (1.0F - var7));
         switch ((int)var6) {
            case 0:
               var3 = (int)(var2 * 255.0F + 0.5F);
               var4 = (int)(var10 * 255.0F + 0.5F);
               var5 = (int)(var8 * 255.0F + 0.5F);
               break;
            case 1:
               var3 = (int)(var9 * 255.0F + 0.5F);
               var4 = (int)(var2 * 255.0F + 0.5F);
               var5 = (int)(var8 * 255.0F + 0.5F);
               break;
            case 2:
               var3 = (int)(var8 * 255.0F + 0.5F);
               var4 = (int)(var2 * 255.0F + 0.5F);
               var5 = (int)(var10 * 255.0F + 0.5F);
               break;
            case 3:
               var3 = (int)(var8 * 255.0F + 0.5F);
               var4 = (int)(var9 * 255.0F + 0.5F);
               var5 = (int)(var2 * 255.0F + 0.5F);
               break;
            case 4:
               var3 = (int)(var10 * 255.0F + 0.5F);
               var4 = (int)(var8 * 255.0F + 0.5F);
               var5 = (int)(var2 * 255.0F + 0.5F);
               break;
            case 5:
               var3 = (int)(var2 * 255.0F + 0.5F);
               var4 = (int)(var8 * 255.0F + 0.5F);
               var5 = (int)(var9 * 255.0F + 0.5F);
         }
      }

      return new int[]{var3, var4, var5};
   }
}
} // namespace core
} // namespace zombie
