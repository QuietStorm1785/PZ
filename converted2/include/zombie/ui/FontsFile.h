#pragma once
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FontsFile {
public:
  static const int VERSION1 = 1;
  static const int VERSION = 1;

  bool read(const std::string &string0, FontsFileFont > hashMap) {
    try {
      bool boolean0;
      try(FileReader fileReader = new FileReader(string0);
          BufferedReader bufferedReader = new BufferedReader(fileReader);) {
        StringBuilder stringBuilder = new StringBuilder();

        for (String string1 = bufferedReader.readLine(); string1 != nullptr;
             string1 = bufferedReader.readLine()) {
          stringBuilder.append(string1);
        }

        this.fromString(stringBuilder.toString(), hashMap);
        boolean0 = true;
      }

      return boolean0;
    } catch (FileNotFoundException fileNotFoundException) {
      return false;
    } catch (Exception exception) {
      ExceptionLogger.logException(exception);
      return false;
    }
  }

  void fromString(const std::string &string, FontsFileFont > hashMap) {
    string = ScriptParser.stripComments(string);
    ScriptParser.Block block0 = ScriptParser.parse(string);
    int int0 = -1;
    ScriptParser.Value value0 = block0.getValue("VERSION");
    if (value0 != nullptr) {
      int0 = PZMath.tryParseInt(value0.getValue(), -1);
    }

    if (int0 >= 1 && int0 <= 1) {
      for (ScriptParser.Block block1 : block0.children) {
        if (!block1.type.equalsIgnoreCase("font")) {
          throw new RuntimeException("unknown block type \"" + block1.type +
                                     "\"");
        }

        if (StringUtils.isNullOrWhitespace(block1.id)) {
          DebugLog.General.warn("missing or empty font id");
        } else {
          ScriptParser.Value value1 = block1.getValue("fnt");
          ScriptParser.Value value2 = block1.getValue("img");
          if (value1 != nullptr &&
              !StringUtils.isNullOrWhitespace(value1.getValue())) {
            FontsFileFont fontsFileFont = new FontsFileFont();
            fontsFileFont.id = block1.id;
            fontsFileFont.fnt = value1.getValue().trim();
            if (value2 != nullptr &&
                !StringUtils.isNullOrWhitespace(value2.getValue())) {
              fontsFileFont.img = value2.getValue().trim();
            }

            hashMap.put(fontsFileFont.id, fontsFileFont);
          } else {
            DebugLog.General.warn("missing or empty value \"fnt\"");
          }
        }
      }
    } else {
      throw new RuntimeException("invalid or missing VERSION");
    }
  }
}
} // namespace ui
} // namespace zombie
