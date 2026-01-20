#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace common {
namespace primitives {


class ParseRequest {
public:
    const std::string rawValue;
    const int radix;

    private ParseRequest(const std::string& rawValue, int radix) {
      this.rawValue = rawValue;
      this.radix = radix;
   }

    static ParseRequest fromString(const std::string& stringValue) {
      if (stringValue.length() == 0) {
         throw NumberFormatException("empty string");
      } else {
    char firstChar = stringValue.charAt(0);
    std::string rawValue;
    int radix;
         if (stringValue.startsWith("0x") || stringValue.startsWith("0X")) {
            rawValue = stringValue.substr(2);
            radix = 16;
         } else if (firstChar == '#') {
            rawValue = stringValue.substr(1);
            radix = 16;
         } else if (firstChar == '0' && stringValue.length() > 1) {
            rawValue = stringValue.substr(1);
            radix = 8;
         } else {
            rawValue = stringValue;
            radix = 10;
         }

         return std::make_shared<ParseRequest>(rawValue, radix);
      }
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
