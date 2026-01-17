#pragma once
#include "zombie/ZomboidFileSystem.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IndieFileLoader {
public:
  static InputStreamReader getStreamReader(const std::string &string) {
    return getStreamReader();
  }

  static InputStreamReader getStreamReader(const std::string &string,
                                           bool boolean0) {
    InputStreamReader inputStreamReader = null;
    void *object = null;
    if (object != nullptr && !boolean0) {
      inputStreamReader = new InputStreamReader((InputStream)object);
    } else {
      try {
        FileInputStream fileInputStream0 =
            new FileInputStream(ZomboidFileSystem.instance.getString(string));
        inputStreamReader = new InputStreamReader(fileInputStream0, "UTF-8");
      } catch (Exception exception) {
        FileInputStream fileInputStream1 =
            new FileInputStream(Core.getMyDocumentFolder() + File.separator +
                                "mods" + File.separator + string);
        inputStreamReader = new InputStreamReader(fileInputStream1);
      }
    }

    return inputStreamReader;
  }
}
} // namespace core
} // namespace zombie
