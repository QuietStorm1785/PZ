#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace mashape {
namespace unirest {
namespace http {
namespace utils {

class URLParamEncoder {
public:
    static std::string encode(const std::string& input) {
    std::stringstream resultStr = new std::stringstream();

      for (char ch : input.toCharArray()) {
         if (isUnsafe(ch)) {
            resultStr.append('%');
            resultStr.append(toHex(ch / 16));
            resultStr.append(toHex(ch % 16));
         } else {
            resultStr.append(ch);
         }
      }

      return resultStr;
   }

    static char toHex(int ch) {
      return (char)(ch < 10 ? 48 + ch : 65 + ch - 10);
   }

    static bool isUnsafe(char ch) {
      return ch <= 128 && ch >= 0 ? " %$&+,/:;=?@<>#%".indexOf(ch) >= 0 : true;
   }
}
} // namespace utils
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
