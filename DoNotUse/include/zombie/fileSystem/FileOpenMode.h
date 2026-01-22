#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace fileSystem {

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

    static std::string toStringMode(int var0) {
    std::stringstream var1 = new std::stringstream();
      if ((var0 & 1) != 0) {
         var1.append('r');
      }

      if ((var0 & 2) != 0) {
         var1.append('w');
      }

      return var1;
   }
}
} // namespace fileSystem
} // namespace zombie
