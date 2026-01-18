#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace fileSystem {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FileOpenMode {
public:
  static const int NONE = 0;
  static const int READ = 1;
  static const int WRITE = 2;
  static const int OPEN = 4;
  static const int CREATE = 8;
  static const int STREAM = 16;
  static const int CREATE_AND_WRITE = 10;
  static const int OPEN_AND_READ = 5;

  static std::string toStringMode(int int0) {
    StringBuilder stringBuilder = new StringBuilder();
    if ((int0 & 1) != 0) {
      stringBuilder.append('r');
    }

    if ((int0 & 2) != 0) {
      stringBuilder.append('w');
    }

    return stringBuilder.toString();
  }
}
} // namespace fileSystem
} // namespace zombie
