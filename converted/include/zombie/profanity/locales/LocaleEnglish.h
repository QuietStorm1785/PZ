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


class LocaleEnglish : public Locale {
public:
 public LocaleEnglish(const std::string& string) {
 super(string);
 }

 void Init() {
 this->storeVowelsAmount = 3;
 this->addFilterRawWord("ass");
 this->addPhonizer(new Phonizer("strt", "(?<strt>^(?:KN|GN|PN|AE|WR)") {
 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->getName()) != nullptr) {
 matcher.appendReplacement(stringBuffer, matcher.group(this->getName()).toString().substring(1, 2);
 }
 }
 });
 this->addPhonizer(new Phonizer("dropY", "(?<dropY>(?<=M)B$)") {
 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->getName()) != nullptr) {
 matcher.appendReplacement(stringBuffer, "");
 }
 }
 });
 this->addPhonizer(new Phonizer("dropB", "(?<dropB>(?<=M)B$)") {
 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->getName()) != nullptr) {
 matcher.appendReplacement(stringBuffer, "");
 }
 }
 });
 this->addPhonizer(new Phonizer("z", "(?<z>Z)") {
 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->getName()) != nullptr) {
 matcher.appendReplacement(stringBuffer, "S");
 }
 }
 });
 this->addPhonizer(new Phonizer("ck", "(?<ck>CK)") {
 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->getName()) != nullptr) {
 matcher.appendReplacement(stringBuffer, "K");
 }
 }
 });
 this->addPhonizer(new Phonizer("q", "(?<q>Q)") {
 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->getName()) != nullptr) {
 matcher.appendReplacement(stringBuffer, "K");
 }
 }
 });
 this->addPhonizer(new Phonizer("v", "(?<v>V)") {
 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->getName()) != nullptr) {
 matcher.appendReplacement(stringBuffer, "F");
 }
 }
 });
 this->addPhonizer(new Phonizer("xS", "(?<xS>^X)") {
 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->getName()) != nullptr) {
 matcher.appendReplacement(stringBuffer, "S");
 }
 }
 });
 this->addPhonizer(new Phonizer("xKS", "(?<xKS>(?<=\\w)X)") {
 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->getName()) != nullptr) {
 matcher.appendReplacement(stringBuffer, "KS");
 }
 }
 });
 this->addPhonizer(new Phonizer("ph", "(?<ph>PH)") {
 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->getName()) != nullptr) {
 matcher.appendReplacement(stringBuffer, "F");
 }
 }
 });
 this->addPhonizer(new Phonizer("c", "(?<c>C(?=[AUOIE]))") {
 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->getName()) != nullptr) {
 matcher.appendReplacement(stringBuffer, "K");
 }
 }
 });
 }
}
} // namespace locales
} // namespace profanity
} // namespace zombie
