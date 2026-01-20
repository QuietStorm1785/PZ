#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace logger {


class ZLogger {
public:
    PrintStream file;
    PrintStream console;

   private ZLogger$OutputStreams() {
   }

    void println(const std::string& var1) {
      if (this.file != nullptr) {
         this.file.println(var1);
         this.file.flush();
      }

      if (this.console != nullptr) {
         this.console.println(var1);
      }
   }
}
} // namespace logger
} // namespace core
} // namespace zombie
