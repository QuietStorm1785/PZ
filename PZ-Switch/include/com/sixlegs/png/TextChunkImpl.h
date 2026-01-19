#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace sixlegs {
namespace png {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TextChunkImpl {
public:
 const std::string keyword;
 const std::string text;
 const std::string language;
 const std::string translated;
 const int type;

public
 TextChunkImpl(std::string_view string0, std::string_view string1,
 std::string_view string2, std::string_view string3,
 int int0) {
 this->keyword = string0;
 this->text = string1;
 this->language = string2;
 this->translated = string3;
 this->type = int0;
 }

 std::string getKeyword() { return this->keyword; }

 std::string getTranslatedKeyword() { return this->translated; }

 std::string getLanguage() { return this->language; }

 std::string getText() { return this->text; }

 int getType() { return this->type; }
}
} // namespace png
} // namespace sixlegs
} // namespace com
