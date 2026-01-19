#pragma once
#include "zombie/profanity/Phonizer.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace profanity {
namespace locales {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LocaleGerman : public LocaleEnglish {
public:
public
 LocaleGerman(std::string_view string) { super(string); }

 void Init() {
 this->storeVowelsAmount = 3;
 super.Init();
 this->addPhonizer(new Phonizer("ringelS", "(?<ringelS>\u00c3\u0178)") {
 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->getName()) != nullptr) {
 matcher.appendReplacement(stringBuffer, "S");
 }
}
} // namespace locales
);
} // namespace profanity
} // namespace zombie
} // namespace locales
} // namespace profanity
} // namespace zombie
