#pragma once
#include "zombie/core/logger/ExceptionLogger.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DesktopBrowser {
public:
private
  static final String[] browsers =
      new String[]{"google-chrome", "firefox",  "mozilla",      "epiphany",
                   "konqueror",     "netscape", "opera",        "links",
                   "lynx",          "chromium", "brave-browser"};

  static bool openURL(const std::string &string0) {
    try {
      if (System.getProperty("os.name").contains("OS X")) {
        Runtime.getRuntime().exec(String.format("open %s", string0));
        return true;
      }

      if (System.getProperty("os.name").startsWith("Win")) {
        Runtime.getRuntime().exec(
            String.format("rundll32 url.dll,FileProtocolHandler %s", string0));
        return true;
      }

      for (auto &string1 : browsers)
        Process process =
            Runtime.getRuntime().exec(new String[]{"which", string1});
      if (process.getInputStream().read() != -1) {
        Runtime.getRuntime().exec(new String[]{string1, string0});
        return true;
      }
    }
  }
  catch (IOException iOException) {
    ExceptionLogger.logException(iOException);
  }

  return false;
}
}
} // namespace network
} // namespace zombie
