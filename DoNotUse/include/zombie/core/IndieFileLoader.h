#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {


class IndieFileLoader {
public:
    static InputStreamReader getStreamReader(const std::string& var0) {
    return getStreamReader();
   }

    static InputStreamReader getStreamReader(const std::string& var0, bool var1) {
    InputStreamReader var2 = nullptr;
    void* var3 = nullptr;
      if (var3 != nullptr && !var1) {
         var2 = std::make_shared<InputStreamReader>((InputStream)var3);
      } else {
         try {
    FileInputStream var4 = std::make_shared<FileInputStream>(ZomboidFileSystem.instance.getString(var0));
            var2 = std::make_shared<InputStreamReader>(var4, "UTF-8");
         } catch (Exception var6) {
    FileInputStream var5 = std::make_shared<FileInputStream>(Core.getMyDocumentFolder() + File.separator + "mods" + File.separator + var0);
            var2 = std::make_shared<InputStreamReader>(var5);
         }
      }

    return var2;
   }
}
} // namespace core
} // namespace zombie
