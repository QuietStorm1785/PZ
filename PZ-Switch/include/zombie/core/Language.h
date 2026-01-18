#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Language {
public:
 const int index;
 const std::string name;
 const std::string text;
 const std::string charset;
 const std::string base;
 const bool azerty;

 Language(int int0, String string0, String string1, String string2,
 String string3, boolean boolean0) {
 this->index = int0;
 this->name = string0;
 this->text = string1;
 this->charset = string2;
 this->base = string3;
 this->azerty = boolean0;
 }

 int index() { return this->index; }

 std::string name() { return this->name; }

 std::string text() { return this->text; }

 std::string charset() { return this->charset; }

 std::string base() { return this->base; }

 bool isAzerty() { return this->azerty; }

 std::string toString() { return this->name; }

 static Language fromIndex(int _index) {
 return Languages.instance.getByIndex(_index);
 }

 static Language FromString(const std::string &str) {
 Language language = Languages.instance.getByName(str);
 if (language.empty()) {
 language = Languages.instance.getDefaultLanguage();
 }

 return language;
 }
}
} // namespace core
} // namespace zombie
