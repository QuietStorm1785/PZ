#pragma once
#include <sstream>
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

class CollapsedStringAdapter : public XmlAdapter {
public:
    std::string unmarshal(const std::string& text) {
      if (text == nullptr) {
    return nullptr;
      } else {
    int len = text.length();
    int s = 0;

         while (s < len && !isWhiteSpace(text.charAt(s))) {
            s++;
         }

         if (s == len) {
    return text;
         } else {
    std::stringstream result = new std::stringstream(len);
            if (s != 0) {
               for (int i = 0; i < s; i++) {
                  result.append(text.charAt(i));
               }

               result.append(' ');
            }

    bool inStripMode = true;

            for (int i = s + 1; i < len; i++) {
    char ch = text.charAt(i);
    bool b = isWhiteSpace(ch);
               if (!inStripMode || !b) {
                  inStripMode = b;
                  if (b) {
                     result.append(' ');
                  } else {
                     result.append(ch);
                  }
               }
            }

            len = result.length();
            if (len > 0 && result.charAt(len - 1) == ' ') {
               result.setLength(len - 1);
            }

            return result;
         }
      }
   }

    std::string marshal(const std::string& s) {
    return s;
   }

    static bool isWhiteSpace(char ch) {
      return ch > ' ' ? false : ch == '\t' || ch == '\n' || ch == '\r' || ch == ' ';
   }
}
} // namespace adapters
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
