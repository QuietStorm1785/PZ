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
namespace Lua {


class LuaManager {
public:
    const PrintWriter writer;

   public LuaManager$GlobalObject$LuaFileWriter(PrintWriter var1) {
      this.writer = var1;
   }

    void write(const std::string& var1) {
      this.writer.write(var1);
   }

    void writeln(const std::string& var1) {
      this.writer.write(var1);
      this.writer.write(System.lineSeparator());
   }

    void close() {
      this.writer.close();
   }
}
} // namespace Lua
} // namespace zombie
