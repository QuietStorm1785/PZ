#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sixlegs {
namespace png {

class TextChunkImpl {
public:
    const std::string keyword;
    const std::string text;
    const std::string language;
    const std::string translated;
    const int type;

    public TextChunkImpl(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4, int var5) {
      this.keyword = var1;
      this.text = var2;
      this.language = var3;
      this.translated = var4;
      this.type = var5;
   }

    std::string getKeyword() {
      return this.keyword;
   }

    std::string getTranslatedKeyword() {
      return this.translated;
   }

    std::string getLanguage() {
      return this.language;
   }

    std::string getText() {
      return this.text;
   }

    int getType() {
      return this.type;
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
