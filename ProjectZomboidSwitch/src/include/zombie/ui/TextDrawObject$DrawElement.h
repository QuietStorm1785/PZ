#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/core/fonts/AngelCodeFont.h"
#include "zombie/core/textures/Texture.h"
#include <algorithm>

namespace zombie {
namespace ui {


class TextDrawObject {
public:
    std::string text = "";
    std::string scrambleText = "";
    float currentScrambleVal = 0.0F;
    UIFont f = UIFont.AutoNormSmall;
    AngelCodeFont font = nullptr;
    float R = 1.0F;
    float G = 1.0F;
    float B = 1.0F;
    int w = 0;
    int h = 0;
    bool isImage = false;
    bool useFont = false;
    bool useColor = false;
    Texture tex = nullptr;
    bool isTextImage = false;
    int charWidth = 0;

   private TextDrawObject$DrawElement() {
   }

    void reset() {
      this.text = "";
      this.scrambleText = "";
      this.f = UIFont.AutoNormSmall;
      this.font = nullptr;
      this.R = 1.0F;
      this.G = 1.0F;
      this.B = 1.0F;
      this.w = 0;
      this.h = 0;
      this.isImage = false;
      this.useFont = false;
      this.useColor = false;
      this.tex = nullptr;
      this.isTextImage = false;
      this.charWidth = 0;
   }

    void addText(const std::string& var1) {
      this.text = this.text + var1;
      this.charWidth = this.text.length();
   }

    void scrambleText(float var1) {
      if (var1 != this.currentScrambleVal) {
         this.currentScrambleVal = var1;
    int var2 = (int)(var1 * 100.0F);
         std::string[] var3 = this.text.split("\\s+");
         this.scrambleText = "";

    for (auto& var7 : var3)    int var8 = Rand.Next(100);
            if (var8 > var2) {
               this.scrambleText = this.scrambleText + var7 + " ";
            } else {
               char[] var9 = new char[var7.length()];
               Arrays.fill(var9, ".".charAt(0));
               this.scrambleText = this.scrambleText + new std::string(var9) + " ";
            }
         }
      }
   }

    void trim() {
      this.text = this.text.trim();
   }

   private TextDrawObject$DrawElement softclone() {
      TextDrawObject$DrawElement var1 = new TextDrawObject$DrawElement();
      if (this.useColor) {
         var1.R = this.R;
         var1.G = this.G;
         var1.B = this.B;
         var1.useColor = this.useColor;
      }

      if (this.useFont) {
         var1.f = this.f;
         var1.font = this.font;
         var1.useFont = this.useFont;
      }

    return var1;
   }
}
} // namespace ui
} // namespace zombie
