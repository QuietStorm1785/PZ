#pragma once
#include "zombie/profanity/locales/Locale.h"
#include "zombie/profanity/locales/LocaleChinese.h"
#include "zombie/profanity/locales/LocaleEnglish.h"
#include "zombie/profanity/locales/LocaleGerman.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace profanity {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ProfanityFilter {
public:
  static bool DEBUG = false;
private
  Map<String, Locale> locales = std::make_unique<HashMap<>>();
  Locale locale;
  Locale localeDefault;
  Pattern prePattern;
  bool enabled = true;
  static std::string LOCALES_DIR = "media" + File.separator + "profanity" +
                                   File.separator + "locales" + File.separator;
  static ProfanityFilter instance;

  static ProfanityFilter getInstance() {
    if (instance == nullptr) {
      instance = std::make_unique<ProfanityFilter>();
    }

    return instance;
  }

private
  ProfanityFilter() {
    this.addLocale(new LocaleEnglish("EN"), true);
    this.addLocale(new LocaleGerman("GER"));
    this.addLocale(new LocaleChinese("CHIN"));
    this.prePattern = Pattern.compile("(?<spaced>(?:(?:\\s|\\W)[\\w\\$@](?=\\s|"
                                      "\\W)){2,20})|(?<word>[\\w'\\$@_-]+)");
  }

  static void printDebug(const std::string &string) {
    if (DEBUG) {
      System.out.println(string);
    }
  }

  void enable(bool boolean0) { this.enabled = boolean0; }

  bool isEnabled() { return this.enabled; }

  int getFilterWordsCount() {
    return this.locale != nullptr ? this.locale.getFilterWordsCount() : 0;
  }

  void addLocale(Locale localex) { this.addLocale(localex, false); }

  void addLocale(Locale localex, bool boolean0) {
    this.locales.put(localex.getID(), localex);
    if (boolean0) {
      this.locale = localex;
      this.localeDefault = localex;
    }
  }

  Locale getLocale() { return this.locale; }

  void addWhiteListWord(const std::string &string) {
    if (this.locale != nullptr) {
      this.locale.addWhiteListWord(string);
    }
  }

  void removeWhiteListWord(const std::string &string) {
    if (this.locale != nullptr) {
      this.locale.removeWhiteListWord(string);
    }
  }

  void addFilterWord(const std::string &string) {
    if (this.locale != nullptr) {
      this.locale.addFilterWord(string);
    }
  }

  void removeFilterWord(const std::string &string) {
    if (this.locale != nullptr) {
      this.locale.removeFilterWord(string);
    }
  }

  void setLocale(const std::string &string) {
    if (this.locales.containsKey(string)) {
      this.locale = this.locales.get(string);
    } else {
      this.locale = this.localeDefault;
    }
  }

  std::string filterString(const std::string &string) {
    if (this.enabled && this.locale != nullptr && string != nullptr &&
        this.locale.getFilterWordsCount() > 0) {
      try {
        StringBuffer stringBuffer = new StringBuffer();
        Matcher matcher = this.prePattern.matcher(string);

        while (matcher.find()) {
          if (matcher.group("word") != nullptr) {
            matcher.appendReplacement(
                stringBuffer, Matcher.quoteReplacement(this.locale.filterWord(
                                  matcher.group("word"), true)));
          } else if (matcher.group("spaced") != nullptr) {
            matcher.appendReplacement(
                stringBuffer,
                Matcher.quoteReplacement(
                    " " + this.locale.filterWord(
                              matcher.group("spaced").replaceAll("\\s+", ""))));
          }
        }

        matcher.appendTail(stringBuffer);
        return stringBuffer.toString();
      } catch (Exception exception) {
        System.out.println("Profanity failed for: " + string);
      }
    }

    return string;
  }

  std::string validateString(const std::string &string) {
    return this.validateString(string, true, true, true);
  }

  std::string validateString(const std::string &string, bool boolean1,
                             bool boolean2, bool boolean3) {
    if (this.enabled && this.locale != nullptr && string != nullptr &&
        this.locale.getFilterWordsCount() > 0) {
      try {
        void *object = null;
        bool boolean0 = false;
        StringBuilder stringBuilder = new StringBuilder();
        Matcher matcher = this.prePattern.matcher(string);

        while (matcher.find()) {
          if (boolean1 && matcher.group("word") != nullptr) {
            object = this.locale.validateWord(matcher.group("word"), boolean2);
            if (object != nullptr) {
              if (boolean0) {
                stringBuilder.append(", ");
              }

              stringBuilder.append((String)object);
              boolean0 = true;
            }
          } else if (boolean3 && matcher.group("spaced") != nullptr) {
            object = this.locale.validateWord(
                matcher.group("spaced").replaceAll("\\s+", ""), false);
            if (object != nullptr) {
              if (boolean0) {
                stringBuilder.append(", ");
              }

              stringBuilder.append((String)object);
              boolean0 = true;
            }
          }
        }

        return boolean0 ? stringBuilder.toString() : nullptr;
      } catch (Exception exception) {
        System.out.println("Profanity validate string failed for: " + string);
        exception.printStackTrace();
      }
    }

    return "Failed to parse string :(.";
  }
}
} // namespace profanity
} // namespace zombie
