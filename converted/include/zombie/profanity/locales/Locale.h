#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/profanity/Phonizer.h"
#include "zombie/profanity/ProfanityFilter.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace profanity {
namespace locales {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Locale {
public:
 std::string id;
 int storeVowelsAmount = 3;
 std::string phoneticRules = "";
 protected Map<String, Phonizer> phonizers = std::make_unique<HashMap<>>();
 protected Map<String, String> filterWords = std::make_unique<HashMap<>>();
 protected List<String> filterWordsRaw = std::make_unique<ArrayList<>>();
 protected List<String> filterContains = std::make_unique<ArrayList<>>();
 protected ArrayList<String> whitelistWords = std::make_unique<ArrayList<>>();
 Pattern pattern;
 Pattern preProcessLeet = Pattern.compile("(?<leet>[\\$@34701])\\k<leet>*|(?<nonWord>[^A-Z\\s\\$@34701]+)");
 Pattern preProcessDoubles = Pattern.compile("(?<doublechar>[A-Z])\\k<doublechar>+");
 Pattern preProcessVowels = Pattern.compile("(?<vowel>[AOUIE])");

 protected Locale(const std::string& string) {
 this->id = string;
 this->Init();
 this->finalizeData();
 this->loadFilterWords();
 this->loadFilterContains();
 this->loadWhiteListWords();
 ProfanityFilter.printDebug("Done init locale: " + this->id);
 }

 std::string getID() {
 return this->id;
 }

 std::string getPhoneticRules() {
 return this->phoneticRules;
 }

 int getFilterWordsCount() {
 return this->filterWords.size();
 }

 protected void Init();

 void addWhiteListWord(const std::string& string) {
 string = string.toUpperCase().trim();
 if (!this->whitelistWords.contains(string) {
 this->whitelistWords.add(string);
 }
 }

 void removeWhiteListWord(const std::string& string) {
 string = string.toUpperCase().trim();
 if (this->whitelistWords.contains(string) {
 this->whitelistWords.remove(string);
 }
 }

 bool isWhiteListedWord(const std::string& string) {
 return this->whitelistWords.contains(string.toUpperCase().trim());
 }

 void addFilterWord(const std::string& string1) {
 std::string string0 = this->phonizeWord(string1);
 if (string0.length() > 2) {
 std::string string2 = "";
 if (this->filterWords.containsKey(string0) {
 string2 = string2 + this->filterWords.get(string0) + ",";
 }

 ProfanityFilter.printDebug("Adding word: " + string1 + ", Phonized: " + string0);
 this->filterWords.put(string0, string2 + string1.toLowerCase());
 } else {
 ProfanityFilter.printDebug("Refusing word: " + string1 + ", Phonized: " + string0 + ", nullptr or phonized < 2 characters");
 }
 }

 void removeFilterWord(const std::string& string1) {
 std::string string0 = this->phonizeWord(string1);
 if (this->filterWords.containsKey(string0) {
 this->filterWords.remove(string0);
 }
 }

 void addFilterContains(const std::string& string) {
 if (string != nullptr && !string.empty() && !this->filterContains.contains(string.toUpperCase())) {
 this->filterContains.add(string.toUpperCase());
 }
 }

 void removeFilterContains(const std::string& string) {
 this->filterContains.remove(string.toUpperCase());
 }

 void addFilterRawWord(const std::string& string) {
 if (string != nullptr && !string.empty() && !this->filterWordsRaw.contains(string.toUpperCase())) {
 this->filterWordsRaw.add(string.toUpperCase());
 }
 }

 void removeFilterWordRaw(const std::string& string) {
 this->filterWordsRaw.remove(string.toUpperCase());
 }

 std::string repeatString(int int0, char char0) {
 char[] chars = new char[int0];
 Arrays.fill(chars, char0);
 return new String(chars);
 }

 bool containsIgnoreCase(const std::string& string1, const std::string& string0) {
 if (string1 != nullptr && string0 != nullptr) {
 int int0 = string0.length();
 if (int0 == 0) {
 return true;
 } else {
 for (int int1 = string1.length() - int0; int1 >= 0; int1--) {
 if (string1.regionMatches(true, int1, string0, 0, int0) {
 return true;
 }
 }

 return false;
 }
 } else {
 return false;
 }
 }

 std::string filterWord(const std::string& string) {
 return this->filterWord(string, false);
 }

 std::string filterWord(const std::string& string0, bool boolean0) {
 if (this->isWhiteListedWord(string0) {
 return string0;
 } else {
 std::string string1 = this->phonizeWord(string0);
 if (this->filterWords.containsKey(string1) {
 return new String(new char[string0.length()]).replace('\u0000', '*');
 } else {
 if (this->filterWordsRaw.size() > 0) {
 for (int int0 = 0; int0 < this->filterWordsRaw.size(); int0++) {
 if (string0.equalsIgnoreCase(this->filterWordsRaw.get(int0) {
 return new String(new char[string0.length()]).replace('\u0000', '*');
 }
 }
 }

 if (boolean0) {
 for (int int1 = 0; int1 < this->filterContains.size(); int1++) {
 std::string string2 = this->filterContains.get(int1);
 if (this->containsIgnoreCase(string0, string2) {
 string0 = string0.replaceAll("(?i)" + Pattern.quote(string2), this->repeatString(string2.length(), '*'));
 }
 }
 }

 return string0;
 }
 }
 }

 std::string validateWord(const std::string& string0, bool boolean0) {
 if (this->isWhiteListedWord(string0) {
 return nullptr;
 } else {
 std::string string1 = this->phonizeWord(string0);
 if (this->filterWords.containsKey(string1) {
 return string0;
 } else {
 if (this->filterWordsRaw.size() > 0) {
 for (int int0 = 0; int0 < this->filterWordsRaw.size(); int0++) {
 if (string0.equalsIgnoreCase(this->filterWordsRaw.get(int0) {
 return string0;
 }
 }
 }

 if (boolean0) {
 for (int int1 = 0; int1 < this->filterContains.size(); int1++) {
 std::string string2 = this->filterContains.get(int1);
 if (this->containsIgnoreCase(string0, string2) {
 return string2.toLowerCase();
 }
 }
 }

 return nullptr;
 }
 }
 }

 std::string returnMatchSetForWord(const std::string& string1) {
 std::string string0 = this->phonizeWord(string1);
 return this->filterWords.containsKey(string0) ? this->filterWords.get(string0) : nullptr;
 }

 std::string returnPhonizedWord(const std::string& string) {
 return this->phonizeWord(string);
 }

 std::string phonizeWord(const std::string& string) {
 string = string.toUpperCase().trim();
 if (this->whitelistWords.contains(string) {
 return string;
 } else {
 string = this->preProcessWord(string);
 if (this->phonizers.size() <= 0) {
 return string;
 } else {
 Matcher matcher = this->pattern.matcher(string);
 StringBuffer stringBuffer = new StringBuffer();

 while (matcher.find()) {
 for (Entry entry : this->phonizers.entrySet()) {
 if (matcher.group((String)entry.getKey()) != nullptr) {
 ((Phonizer)entry.getValue()).execute(matcher, stringBuffer);
 break;
 }
 }
 }

 matcher.appendTail(stringBuffer);
 return stringBuffer.toString();
 }
 }
 }

 std::string preProcessWord(const std::string& string0) {
 Matcher matcher = this->preProcessLeet.matcher(string0);
 StringBuffer stringBuffer = new StringBuffer();

 while (matcher.find()) {
 if (matcher.group("leet") != nullptr) {
 std::string string1 = matcher.group("leet").toString();
 switch (string1) {
 case "$":
 matcher.appendReplacement(stringBuffer, "S");
 break;
 case "4":
 case "@":
 matcher.appendReplacement(stringBuffer, "A");
 break;
 case "3":
 matcher.appendReplacement(stringBuffer, "E");
 break;
 case "7":
 matcher.appendReplacement(stringBuffer, "T");
 break;
 case "0":
 matcher.appendReplacement(stringBuffer, "O");
 break;
 case "1":
 matcher.appendReplacement(stringBuffer, "I");
 }
 } else if (matcher.group("nonWord") != nullptr) {
 matcher.appendReplacement(stringBuffer, "");
 }
 }

 matcher.appendTail(stringBuffer);
 matcher = this->preProcessDoubles.matcher(stringBuffer.toString());
 stringBuffer.delete(0, stringBuffer.capacity());

 while (matcher.find()) {
 if (matcher.group("doublechar") != nullptr) {
 matcher.appendReplacement(stringBuffer, "${doublechar}");
 }
 }

 matcher.appendTail(stringBuffer);
 matcher = this->preProcessVowels.matcher(stringBuffer.toString());
 stringBuffer.delete(0, stringBuffer.capacity());
 int int0 = 0;

 while (matcher.find()) {
 if (matcher.group("vowel") != nullptr) {
 if (int0 < this->storeVowelsAmount) {
 matcher.appendReplacement(stringBuffer, "${vowel}");
 int0++;
 } else {
 matcher.appendReplacement(stringBuffer, "");
 }
 }
 }

 matcher.appendTail(stringBuffer);
 return stringBuffer.toString();
 }

 void addPhonizer(Phonizer phonizer) {
 if (phonizer != nullptr && !this->phonizers.containsKey(phonizer.getName())) {
 this->phonizers.put(phonizer.getName(), phonizer);
 }
 }

 void finalizeData() {
 this->phoneticRules = "";
 int int0 = this->phonizers.size();
 int int1 = 0;

 for (Phonizer phonizer : this->phonizers.values()) {
 this->phoneticRules = this->phoneticRules + phonizer.getRegex();
 if (++int1 < int0) {
 this->phoneticRules = this->phoneticRules + "|";
 }
 }

 ProfanityFilter.printDebug("PhoneticRules: " + this->phoneticRules);
 this->pattern = Pattern.compile(this->phoneticRules);
 }

 void loadFilterWords() {
 try {
 std::string string0 = ZomboidFileSystem.instance.getString(ProfanityFilter.LOCALES_DIR + "blacklist_" + this->id + ".txt");
 File file = new File(string0);
 FileReader fileReader = new FileReader(file);
 BufferedReader bufferedReader = new BufferedReader(fileReader);

 std::string string1;
 int int0;
 for (int0 = 0; (string1 = bufferedReader.readLine()) != nullptr; int0++) {
 this->addFilterWord(string1);
 }

 fileReader.close();
 ProfanityFilter.printDebug("BlackList, " + int0 + " added.");
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 void loadFilterContains() {
 try {
 std::string string0 = ZomboidFileSystem.instance.getString(ProfanityFilter.LOCALES_DIR + "blacklist_contains_" + this->id + ".txt");
 File file = new File(string0);
 FileReader fileReader = new FileReader(file);
 BufferedReader bufferedReader = new BufferedReader(fileReader);
 int int0 = 0;

 std::string string1;
 while ((string1 = bufferedReader.readLine()) != nullptr) {
 if (!string1.startsWith("//")) {
 this->addFilterContains(string1);
 int0++;
 }
 }

 fileReader.close();
 ProfanityFilter.printDebug("BlackList contains, " + int0 + " added.");
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 void loadWhiteListWords() {
 try {
 std::string string0 = ZomboidFileSystem.instance.getString(ProfanityFilter.LOCALES_DIR + "whitelist_" + this->id + ".txt");
 File file = new File(string0);
 FileReader fileReader = new FileReader(file);
 BufferedReader bufferedReader = new BufferedReader(fileReader);

 std::string string1;
 int int0;
 for (int0 = 0; (string1 = bufferedReader.readLine()) != nullptr; int0++) {
 this->addWhiteListWord(string1);
 }

 fileReader.close();
 ProfanityFilter.printDebug("WhiteList, " + int0 + " added.");
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }
}
} // namespace locales
} // namespace profanity
} // namespace zombie
