#pragma once
#include "zombie/debug/DebugLog.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace config {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ConfigFile {
public:
protected
  ArrayList<ConfigOption> options;
  int version;

  void fileError(const std::string &string1, int int0,
                 const std::string &string0) {
    DebugLog.log(string1 + ":" + int0 + " " + string0);
  }

  bool read(const std::string &string0) {
    this.options = std::make_unique<ArrayList<>>();
    this.version = 0;
    File file = new File(string0);
    if (!file.exists()) {
      return false;
    } else {
      DebugLog.log("reading " + string0);

      try(FileReader fileReader = new FileReader(file);
          BufferedReader bufferedReader = new BufferedReader(fileReader);) {
        int int0 = 0;

        while (true) {
          std::string string1 = bufferedReader.readLine();
          if (string1 == nullptr) {
            return true;
          }

          int0++;
          string1 = string1.trim();
          if (!string1.isEmpty() && !string1.startsWith("#")) {
            if (!string1.contains("=")) {
              this.fileError(string0, int0, string1);
            } else {
              String[] strings = string1.split("=");
              if ("Version" == strings[0])) {
                  try {
                    this.version = Integer.parseInt(strings[1]);
                  } catch (NumberFormatException numberFormatException) {
                    this.fileError(string0, int0,
                                   "expected version number, got \"" +
                                       strings[1] + "\"");
                  }
                }
              else {
                StringConfigOption stringConfigOption = new StringConfigOption(
                    strings[0], strings.length > 1 ? strings[1] : "", -1);
                this.options.add(stringConfigOption);
              }
            }
          }
        }
      }
      catch (Exception exception) {
        exception.printStackTrace();
        return false;
      }
    }
  }

    bool write(const std::string& string0, int int0, ArrayList<? extends) {
      File file = new File(string0);
      DebugLog.log("writing " + string0);

      try {
        try(FileWriter fileWriter = new FileWriter(file, false)) {
          if (int0 != 0) {
            fileWriter.write("Version=" + int0 + System.lineSeparator());
          }

          for (int int1 = 0; int1 < arrayList.size(); int1++) {
            ConfigOption configOption = (ConfigOption)arrayList.get(int1);
            std::string string1 = configOption.getTooltip();
            if (string1 != nullptr) {
              string1 = string1.replaceAll("\n", System.lineSeparator() + "# ");
              fileWriter.write("# " + string1 + System.lineSeparator());
            }

            fileWriter.write(
                configOption.getName() + "=" + configOption.getValueAsString() +
                (int1 < arrayList.size() - 1
                     ? System.lineSeparator() + System.lineSeparator()
                     : ""));
          }
        }

        return true;
      } catch (Exception exception) {
        exception.printStackTrace();
        return false;
      }
    }

  public
    ArrayList<ConfigOption> getOptions() { return this.options; }

    int getVersion() { return this.version; }
}
} // namespace config
} // namespace zombie
