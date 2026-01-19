#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sixlegs {
namespace png {

class TextChunkImpl {
:
    const std::string keyword;
    const std::string text;
    const std::string language;
    const std::string translated;
    const int type;

     TextChunkImpl(std::string_view var1, std::string_view var2, std::string_view var3, std::string_view var4, int var5) {
      this.keyword = var1;
      this.text = var2;
      this.language = var3;
      this.translated = var4;
      this.type = var5;
   }

    std::string getKeyword() const {
      return this.keyword;
   }

    std::string getTranslatedKeyword() const {
      return this.translated;
   }

    std::string getLanguage() const {
      return this.language;
   }

    std::string getText() const {
      return this.text;
   }

    int getType() const {
      return this.type;
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
