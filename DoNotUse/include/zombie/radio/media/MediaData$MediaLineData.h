#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"
#include "zombie/core/Translator.h"

namespace zombie {
namespace radio {
namespace media {


class MediaData {
public:
    const std::string text;
    const Color color;
    const std::string codes;

   public MediaData$MediaLineData(std::string var1, float var2, float var3, float var4, std::string var5) {
      this.text = var1;
      this.codes = var5;
      if (var2 == 0.0F && var3 == 0.0F && var4 == 0.0F) {
         var2 = 1.0F;
         var3 = 1.0F;
         var4 = 1.0F;
      }

      this.color = std::make_shared<Color>(var2, var3, var4);
   }

    std::string getTranslatedText() {
      return Translator.getText(this.text);
   }

    Color getColor() {
      return this.color;
   }

    float getR() {
      return this.color.r;
   }

    float getG() {
      return this.color.g;
   }

    float getB() {
      return this.color.b;
   }

    std::string getCodes() {
      return this.codes;
   }

    std::string getTextGuid() {
      return this.text;
   }
}
} // namespace media
} // namespace radio
} // namespace zombie
