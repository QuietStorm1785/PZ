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


class WinReqistry {
public:
    InputStream is;
    StringWriter sw = std::make_shared<StringWriter>();

   public WinReqistry$StreamReader(InputStream var1) {
      this.is = var1;
   }

    void run() {
    int var1;
      try {
         while ((var1 = this.is.read()) != -1) {
            this.sw.write(var1);
         }
      } catch (IOException var2) {
      }
   }

    std::string getResult() {
      return this.sw;
   }
}
} // namespace core
} // namespace zombie
