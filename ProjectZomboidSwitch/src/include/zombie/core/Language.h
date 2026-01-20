#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {

class Language {
public:
    const int index;
    const std::string name;
    const std::string text;
    const std::string charset;
    const std::string base;
    const bool azerty;

   Language(int var1, std::string var2, std::string var3, std::string var4, std::string var5, boolean var6) {
      this.index = var1;
      this.name = var2;
      this.text = var3;
      this.charset = var4;
      this.base = var5;
      this.azerty = var6;
   }

    int index() {
      return this.index;
   }

    std::string name() {
      return this.name;
   }

    std::string text() {
      return this.text;
   }

    std::string charset() {
      return this.charset;
   }

    std::string base() {
      return this.base;
   }

    bool isAzerty() {
      return this.azerty;
   }

    std::string toString() {
      return this.name;
   }

    static Language fromIndex(int var0) {
      return Languages.instance.getByIndex(var0);
   }

    static Language FromString(const std::string& var0) {
    Language var1 = Languages.instance.getByName(var0);
      if (var1 == nullptr) {
         var1 = Languages.instance.getDefaultLanguage();
      }

    return var1;
   }
}
} // namespace core
} // namespace zombie
