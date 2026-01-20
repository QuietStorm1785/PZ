#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace javax {
namespace xml {
namespace bind {
namespace annotation {
namespace adapters {

class NormalizedStringAdapter : public XmlAdapter {
public:
    std::string unmarshal(const std::string& text) {
      if (text == nullptr) {
    return nullptr;
      } else {
    int i = text.length() - 1;

         while (i >= 0 && !isWhiteSpaceExceptSpace(text.charAt(i))) {
            i--;
         }

         if (i < 0) {
    return text;
         } else {
            char[] buf = text.toCharArray();

            for (buf[i--] = ' '; i >= 0; i--) {
               if (isWhiteSpaceExceptSpace(buf[i])) {
                  buf[i] = ' ';
               }
            }

            return new std::string(buf);
         }
      }
   }

    std::string marshal(const std::string& s) {
    return s;
   }

    static bool isWhiteSpaceExceptSpace(char ch) {
      return ch >= ' ' ? false : ch == '\t' || ch == '\n' || ch == '\r';
   }
}
} // namespace adapters
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
