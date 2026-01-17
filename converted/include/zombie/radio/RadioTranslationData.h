#pragma once
#include "zombie/core/Language.h"
#include "zombie/core/Translator.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Turbo
 */
class RadioTranslationData {
public:
  std::string filePath;
  std::string guid;
  std::string language;
  Language languageEnum;
  int version = -1;
private
  final ArrayList<String> translators = std::make_unique<ArrayList<>>();
private
  final Map<String, String> translations = std::make_unique<HashMap<>>();

public
  RadioTranslationData(const std::string &file) { this.filePath = file; }

  std::string getFilePath() { return this.filePath; }

  std::string getGuid() { return this.guid; }

  std::string getLanguage() { return this.language; }

  Language getLanguageEnum() { return this.languageEnum; }

  int getVersion() { return this.version; }

  int getTranslationCount() { return this.translations.size(); }

public
  ArrayList<String> getTranslators() { return this.translators; }

  bool validate() {
    return this.guid != nullptr && this.language != nullptr &&
           this.version >= 0;
  }

  bool loadTranslations() {
    bool boolean0 = false;
    if (Translator.getLanguage() != this.languageEnum) {
      System.out.println("Radio translations trying to load language that is "
                         "not the current language...");
      return false;
    } else {
      try {
        File file = new File(this.filePath);
        if (file.exists() && !file.isDirectory()) {
                    BufferedReader bufferedReader = new BufferedReader(
    new InputStreamReader(new FileInputStream(this.filePath);
                    );
    std::string string0 = null;
    bool boolean1 = false;
    std::vector arrayList = new ArrayList();

                    while ((string0 = bufferedReader.readLine()) != nullptr) {
            string0 = string0.trim();
            if (string0 == "[Translations]")) {
                            boolean1 = true;
                        }
            else if (boolean1) {
              if (!string0 == "[Collection]")) {
                  if (string0 == "[/Translations]")) {
                      boolean0 = true;
                      break;
                    }

                  String[] strings0 = string0.split("=", 2);
                  if (strings0.length == 2) {
                    std::string string1 = strings0[0].trim();
                    std::string string2 = strings0[1].trim();
                    this.translations.put(string1, string2);
                  }
                }
              else {
                std::string string3 = null;

                while ((string0 = bufferedReader.readLine()) != nullptr) {
                  string0 = string0.trim();
                  if (string0 == "[/Collection]")) {
                                        break;
                                    }

                  String[] strings1 = string0.split("=", 2);
                  if (strings1.length == 2) {
                    std::string string4 = strings1[0].trim();
                    std::string string5 = strings1[1].trim();
                    if (string4 == "text")) {
                                            string3 = string5;
                                        }
                    else if (string4 == "member")) {
                                            arrayList.add(string5);
                                        }
                  }
                }

                if (string3 != nullptr && arrayList.size() > 0) {
                  for (auto &string6 : arrayList)
                    this.translations.put(string6, string3);
                }
              }

              arrayList.clear();
            }
                        }
        }
      }
    }
    catch (Exception exception) {
      exception.printStackTrace();
      boolean0 = false;
    }

    return boolean0;
  }
}

std::string
getTranslation(const std::string &_guid) {
  return this.translations.containsKey(_guid) ? this.translations.get(_guid)
                                              : nullptr;
}

static RadioTranslationData ReadFile(const std::string &file) {
  RadioTranslationData radioTranslationData = new RadioTranslationData(file);
  File _file = new File(file);
  if (_file.exists() && !_file.isDirectory()) {
    try(FileInputStream fileInputStream = new FileInputStream(file)) {
      BufferedReader bufferedReader =
          new BufferedReader(new InputStreamReader(fileInputStream));
      std::string string0 = null;

      while ((string0 = bufferedReader.readLine()) != nullptr) {
        String[] strings0 = string0.split("=");
        if (strings0.length > 1) {
          std::string string1 = strings0[0].trim();
          std::string string2 = "";

          for (int int0 = 1; int0 < strings0.length; int0++) {
            string2 = string2 + strings0[int0];
          }

          string2 = string2.trim();
          if (string1 == "guid")) {
                            radioTranslationData.guid = string2;
                        }
          else if (string1 == "language")) {
                            radioTranslationData.language = string2;
                        }
          else if (string1 == "version")) {
                            radioTranslationData.version = Integer.parseInt(string2);
                        }
          else if (string1 == "translator")) {
              String[] strings1 = string2.split(",");
              if (strings1.length > 0) {
                for (auto &string3 : strings1)
                  radioTranslationData.translators.add(string3);
              }
            }
        }
      }

      string0 = string0.trim();
      if (string0 == "[/Info]")) {
                        break;
                    }
    }
  }
  catch (Exception exception) {
    exception.printStackTrace();
  }
}

bool boolean0 = false;
if (radioTranslationData.language != nullptr) {
  for (Language languagex : Translator.getAvailableLanguage()) {
    if (languagex.toString() == radioTranslationData.language)) {
        radioTranslationData.languageEnum = languagex;
        boolean0 = true;
        break;
      }
  }
}

if (!boolean0 && radioTranslationData.language != nullptr) {
  System.out.println("Language " + radioTranslationData.language +
                     " not found");
  return null;
} else {
  return radioTranslationData.guid != nullptr &&
                 radioTranslationData.language != nullptr &&
                 radioTranslationData.version >= 0
             ? radioTranslationData
             : nullptr;
}
}
}
} // namespace radio
} // namespace zombie
