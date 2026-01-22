#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/WinReqistry/StreamReader.h"

namespace zombie {
namespace core {


class WinReqistry {
public:
    static std::string getSteamDirectory() {
    return readRegistry();
   }

    static std::string readRegistry(const std::string& var0, const std::string& var1) {
      try {
    Process var2 = Runtime.getRuntime().exec("reg query \"" + var0 + "\" /v " + var1);
    StreamReader var3 = std::make_shared<StreamReader>(var2.getInputStream());
         var3.start();
         var2.waitFor();
         var3.join();
    std::string var4 = var3.getResult();
         if (var4 != nullptr && !var4 == "")) {
            var4 = var4.substr(var4.indexOf("REG_SZ") + 7).trim();
            std::string[] var5 = var4.split("\t");
            return var5[var5.length - 1];
         } else {
    return nullptr;
         }
      } catch (Exception var6) {
    return nullptr;
      }
   }
}
} // namespace core
} // namespace zombie
