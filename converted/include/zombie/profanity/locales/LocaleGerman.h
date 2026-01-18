#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/profanity/Phonizer.h"
#include <algorithm>

namespace zombie {
namespace profanity {
namespace locales {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LocaleGerman : public LocaleEnglish {
public:
 public LocaleGerman(const std::string& string) {
 super(string);
 }

 void Init() {
 this->storeVowelsAmount = 3;
 super.Init();
 this->addPhonizer(new Phonizer("ringelS", "(?<ringelS>\u00c3\u0178)") {
 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->getName()) != nullptr) {
 matcher.appendReplacement(stringBuffer, "S");
 }
 }
 });
 }
}
} // namespace locales
} // namespace profanity
} // namespace zombie
