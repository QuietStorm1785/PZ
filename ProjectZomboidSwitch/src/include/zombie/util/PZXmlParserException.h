#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {

class PZXmlParserException : public Exception {
public:
    public PZXmlParserException() {
   }

    public PZXmlParserException(const std::string& var1) {
      super(var1);
   }

    public PZXmlParserException(const std::string& var1, std::exception var2) {
      super(var1, var2);
   }

    public PZXmlParserException(std::exception var1) {
      super(var1);
   }

    std::string toString() {
    std::string var1 = super;
    std::string var2 = var1;
    std::exception var3 = this.getCause();
      if (var3 != nullptr) {
         var2 = var1 + System.lineSeparator() + "  Caused by:" + System.lineSeparator() + "    " + var3;
      }

    return var2;
   }
}
} // namespace util
} // namespace zombie
