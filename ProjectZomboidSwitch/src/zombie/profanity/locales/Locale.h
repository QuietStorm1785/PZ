#pragma once
#include <sstream>
#include <stack>
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


class Locale {
public:
    std::string id;
    int storeVowelsAmount = 3;
    std::string phoneticRules = "";
   protected Map<std::string, Phonizer> phonizers = std::make_unique<std::unordered_map<>>();
   protected Map<std::string, std::string> filterWords = std::make_unique<std::unordered_map<>>();
   protected List<std::string> filterWordsRaw = std::make_unique<std::vector<>>();
   protected List<std::string> filterContains = std::make_unique<std::vector<>>();
   protected std::vector<std::string> whitelistWords = std::make_unique<std::vector<>>();
    Pattern pattern;
    Pattern preProcessLeet = Pattern.compile("(?<leet>[\\$@34701])\\k<leet>*|(?<nonWord>[^A-Z\\s\\$@34701]+)");
    Pattern preProcessDoubles = Pattern.compile("(?<doublechar>[A-Z])\\k<doublechar>+");
    Pattern preProcessVowels = Pattern.compile("(?<vowel>[AOUIE])");

    protected Locale(const std::string& var1) {
      this.id = var1;
      this.Init();
      this.finalizeData();
      this.loadFilterWords();
      this.loadFilterContains();
      this.loadWhiteListWords();
      ProfanityFilter.printDebug("Done init locale: " + this.id);
   }

    std::string getID() {
      return this.id;
   }

    std::string getPhoneticRules() {
      return this.phoneticRules;
   }

    int getFilterWordsCount() {
      return this.filterWords.size();
   }

   protected abstract void Init();

    void addWhiteListWord(const std::string& var1) {
      var1 = var1.toUpperCase().trim();
      if (!this.whitelistWords.contains(var1)) {
         this.whitelistWords.push_back(var1);
      }
   }

    void removeWhiteListWord(const std::string& var1) {
      var1 = var1.toUpperCase().trim();
      if (this.whitelistWords.contains(var1)) {
         this.whitelistWords.remove(var1);
      }
   }

    bool isWhiteListedWord(const std::string& var1) {
      return this.whitelistWords.contains(var1.toUpperCase().trim());
   }

    void addFilterWord(const std::string& var1) {
    std::string var2 = this.phonizeWord(var1);
      if (var2.length() > 2) {
    std::string var3 = "";
         if (this.filterWords.containsKey(var2)) {
            var3 = var3 + this.filterWords.get(var2) + ",";
         }

         ProfanityFilter.printDebug("Adding word: " + var1 + ", Phonized: " + var2);
         this.filterWords.put(var2, var3 + var1.toLowerCase());
      } else {
         ProfanityFilter.printDebug("Refusing word: " + var1 + ", Phonized: " + var2 + ", nullptr or phonized < 2 characters");
      }
   }

    void removeFilterWord(const std::string& var1) {
    std::string var2 = this.phonizeWord(var1);
      if (this.filterWords.containsKey(var2)) {
         this.filterWords.remove(var2);
      }
   }

    void addFilterContains(const std::string& var1) {
      if (var1 != nullptr && !var1.empty() && !this.filterContains.contains(var1.toUpperCase())) {
         this.filterContains.push_back(var1.toUpperCase());
      }
   }

    void removeFilterContains(const std::string& var1) {
      this.filterContains.remove(var1.toUpperCase());
   }

    void addFilterRawWord(const std::string& var1) {
      if (var1 != nullptr && !var1.empty() && !this.filterWordsRaw.contains(var1.toUpperCase())) {
         this.filterWordsRaw.push_back(var1.toUpperCase());
      }
   }

    void removeFilterWordRaw(const std::string& var1) {
      this.filterWordsRaw.remove(var1.toUpperCase());
   }

    std::string repeatString(int var1, char var2) {
      char[] var3 = new char[var1];
      Arrays.fill(var3, var2);
      return new std::string(var3);
   }

    bool containsIgnoreCase(const std::string& var1, const std::string& var2) {
      if (var1 != nullptr && var2 != nullptr) {
    int var3 = var2.length();
         if (var3 == 0) {
    return true;
         } else {
            for (int var4 = var1.length() - var3; var4 >= 0; var4--) {
               if (var1.regionMatches(true, var4, var2, 0, var3)) {
    return true;
               }
            }

    return false;
         }
      } else {
    return false;
      }
   }

    std::string filterWord(const std::string& var1) {
      return this.filterWord(var1, false);
   }

    std::string filterWord(const std::string& var1, bool var2) {
      if (this.isWhiteListedWord(var1)) {
    return var1;
      } else {
    std::string var3 = this.phonizeWord(var1);
         if (this.filterWords.containsKey(var3)) {
            return new std::string(new char[var1.length()]).replace('\u0000', '*');
         } else {
            if (this.filterWordsRaw.size() > 0) {
               for (int var4 = 0; var4 < this.filterWordsRaw.size(); var4++) {
                  if (var1.equalsIgnoreCase(this.filterWordsRaw.get(var4))) {
                     return new std::string(new char[var1.length()]).replace('\u0000', '*');
                  }
               }
            }

            if (var2) {
               for (int var5 = 0; var5 < this.filterContains.size(); var5++) {
    std::string var6 = this.filterContains.get(var5);
                  if (this.containsIgnoreCase(var1, var6)) {
                     var1 = var1.replaceAll("(?i)" + Pattern.quote(var6), this.repeatString(var6.length(), '*'));
                  }
               }
            }

    return var1;
         }
      }
   }

    std::string validateWord(const std::string& var1, bool var2) {
      if (this.isWhiteListedWord(var1)) {
    return nullptr;
      } else {
    std::string var3 = this.phonizeWord(var1);
         if (this.filterWords.containsKey(var3)) {
    return var1;
         } else {
            if (this.filterWordsRaw.size() > 0) {
               for (int var4 = 0; var4 < this.filterWordsRaw.size(); var4++) {
                  if (var1.equalsIgnoreCase(this.filterWordsRaw.get(var4))) {
    return var1;
                  }
               }
            }

            if (var2) {
               for (int var5 = 0; var5 < this.filterContains.size(); var5++) {
    std::string var6 = this.filterContains.get(var5);
                  if (this.containsIgnoreCase(var1, var6)) {
                     return var6.toLowerCase();
                  }
               }
            }

    return nullptr;
         }
      }
   }

    std::string returnMatchSetForWord(const std::string& var1) {
    std::string var2 = this.phonizeWord(var1);
      return this.filterWords.containsKey(var2) ? this.filterWords.get(var2) : nullptr;
   }

    std::string returnPhonizedWord(const std::string& var1) {
      return this.phonizeWord(var1);
   }

    std::string phonizeWord(const std::string& var1) {
      var1 = var1.toUpperCase().trim();
      if (this.whitelistWords.contains(var1)) {
    return var1;
      } else {
         var1 = this.preProcessWord(var1);
         if (this.phonizers.size() <= 0) {
    return var1;
         } else {
    Matcher var2 = this.pattern.matcher(var1);
    std::stringstream var3 = new std::stringstream();

            while (var2.find()) {
               for (Entry var5 : this.phonizers.entrySet()) {
                  if (var2.group((std::string)var5.getKey()) != nullptr) {
                     ((Phonizer)var5.getValue()).execute(var2, var3);
                     break;
                  }
               }
            }

            var2.appendTail(var3);
            return var3;
         }
      }
   }

    std::string preProcessWord(const std::string& var1) {
    Matcher var2 = this.preProcessLeet.matcher(var1);
    std::stringstream var3 = new std::stringstream();

      while (var2.find()) {
         if (var2.group("leet") != nullptr) {
    std::string var4 = var2.group("leet");
            switch (var4) {
               case "$":
                  var2.appendReplacement(var3, "S");
                  break;
               case "4":
               case "@":
                  var2.appendReplacement(var3, "A");
                  break;
               case "3":
                  var2.appendReplacement(var3, "E");
                  break;
               case "7":
                  var2.appendReplacement(var3, "T");
                  break;
               case "0":
                  var2.appendReplacement(var3, "O");
                  break;
               case "1":
                  var2.appendReplacement(var3, "I");
            }
         } else if (var2.group("nonWord") != nullptr) {
            var2.appendReplacement(var3, "");
         }
      }

      var2.appendTail(var3);
      var2 = this.preProcessDoubles.matcher(var3);
      var3.delete(0, var3.capacity());

      while (var2.find()) {
         if (var2.group("doublechar") != nullptr) {
            var2.appendReplacement(var3, "${doublechar}");
         }
      }

      var2.appendTail(var3);
      var2 = this.preProcessVowels.matcher(var3);
      var3.delete(0, var3.capacity());
    int var8 = 0;

      while (var2.find()) {
         if (var2.group("vowel") != nullptr) {
            if (var8 < this.storeVowelsAmount) {
               var2.appendReplacement(var3, "${vowel}");
               var8++;
            } else {
               var2.appendReplacement(var3, "");
            }
         }
      }

      var2.appendTail(var3);
      return var3;
   }

    void addPhonizer(Phonizer var1) {
      if (var1 != nullptr && !this.phonizers.containsKey(var1.getName())) {
         this.phonizers.put(var1.getName(), var1);
      }
   }

    void finalizeData() {
      this.phoneticRules = "";
    int var1 = this.phonizers.size();
    int var2 = 0;

      for (Phonizer var4 : this.phonizers.values()) {
         this.phoneticRules = this.phoneticRules + var4.getRegex();
         if (++var2 < var1) {
            this.phoneticRules = this.phoneticRules + "|";
         }
      }

      ProfanityFilter.printDebug("PhoneticRules: " + this.phoneticRules);
      this.pattern = Pattern.compile(this.phoneticRules);
   }

    void loadFilterWords() {
      try {
    std::string var1 = ZomboidFileSystem.instance.getString(ProfanityFilter.LOCALES_DIR + "blacklist_" + this.id + ".txt");
    File var2 = std::make_shared<File>(var1);
    FileReader var3 = std::make_shared<FileReader>(var2);
    BufferedReader var4 = std::make_shared<BufferedReader>(var3);

    std::string var5;
    int var6;
         for (var6 = 0; (var5 = var4.readLine()) != nullptr; var6++) {
            this.addFilterWord(var5);
         }

         var3.close();
         ProfanityFilter.printDebug("BlackList, " + var6 + " added.");
      } catch (IOException var7) {
         var7.printStackTrace();
      }
   }

    void loadFilterContains() {
      try {
    std::string var1 = ZomboidFileSystem.instance.getString(ProfanityFilter.LOCALES_DIR + "blacklist_contains_" + this.id + ".txt");
    File var2 = std::make_shared<File>(var1);
    FileReader var3 = std::make_shared<FileReader>(var2);
    BufferedReader var4 = std::make_shared<BufferedReader>(var3);
    int var6 = 0;

    std::string var5;
         while ((var5 = var4.readLine()) != nullptr) {
            if (!var5.startsWith("//")) {
               this.addFilterContains(var5);
               var6++;
            }
         }

         var3.close();
         ProfanityFilter.printDebug("BlackList contains, " + var6 + " added.");
      } catch (IOException var7) {
         var7.printStackTrace();
      }
   }

    void loadWhiteListWords() {
      try {
    std::string var1 = ZomboidFileSystem.instance.getString(ProfanityFilter.LOCALES_DIR + "whitelist_" + this.id + ".txt");
    File var2 = std::make_shared<File>(var1);
    FileReader var3 = std::make_shared<FileReader>(var2);
    BufferedReader var4 = std::make_shared<BufferedReader>(var3);

    std::string var5;
    int var6;
         for (var6 = 0; (var5 = var4.readLine()) != nullptr; var6++) {
            this.addWhiteListWord(var5);
         }

         var3.close();
         ProfanityFilter.printDebug("WhiteList, " + var6 + " added.");
      } catch (IOException var7) {
         var7.printStackTrace();
      }
   }
}
} // namespace locales
} // namespace profanity
} // namespace zombie
