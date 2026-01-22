#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/logger/ExceptionLogger.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class DesktopBrowser {
public:
   private static const std::string[] browsers = new std::string[]{
      "google-chrome", "firefox", "mozilla", "epiphany", "konqueror", "netscape", "opera", "links", "lynx", "chromium", "brave-browser"
   };

    static bool openURL(const std::string& var0) {
      try {
         if (System.getProperty("os.name").contains("OS X")) {
            Runtime.getRuntime().exec(std::string.format("open %s", var0));
    return true;
         }

         if (System.getProperty("os.name").startsWith("Win")) {
            Runtime.getRuntime().exec(std::string.format("rundll32 url.dll,FileProtocolHandler %s", var0));
    return true;
         }

    for (auto& var4 : browsers)    Process var5 = Runtime.getRuntime().exec(new std::string[]{"which", var4});
            if (var5.getInputStream().read() != -1) {
               Runtime.getRuntime().exec(new std::string[]{var4, var0});
    return true;
            }
         }
      } catch (IOException var6) {
         ExceptionLogger.logException(var6);
      }

    return false;
   }
}
} // namespace network
} // namespace zombie
