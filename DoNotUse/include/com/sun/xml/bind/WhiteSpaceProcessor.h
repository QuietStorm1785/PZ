#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {

class WhiteSpaceProcessor {
public:
    static std::string replace(const std::string& text) {
    return replace();
   }

    static CharSequence replace(CharSequence text) {
    int i = text.length() - 1;

      while (i >= 0 && !isWhiteSpaceExceptSpace(text.charAt(i))) {
         i--;
      }

      if (i < 0) {
    return text;
      } else {
    std::stringstream buf = new std::stringstream(text);
         buf.setCharAt(i--, ' ');

         for (; i >= 0; i--) {
            if (isWhiteSpaceExceptSpace(buf.charAt(i))) {
               buf.setCharAt(i, ' ');
            }
         }

         return new std::string(buf);
      }
   }

    static CharSequence trim(CharSequence text) {
    int len = text.length();
    int start = 0;

      while (start < len && isWhiteSpace(text.charAt(start))) {
         start++;
      }

    int end = len - 1;

      while (end > start && isWhiteSpace(text.charAt(end))) {
         end--;
      }

    return start = = 0 && end == len - 1 ? text : text.subSequence(start, end + 1);
   }

    static std::string collapse(const std::string& text) {
    return collapse();
   }

    static CharSequence collapse(CharSequence text) {
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

    static bool isWhiteSpace(CharSequence s) {
      for (int i = s.length() - 1; i >= 0; i--) {
         if (!isWhiteSpace(s.charAt(i))) {
    return false;
         }
      }

    return true;
   }

    static bool isWhiteSpace(char ch) {
      return ch > ' ' ? false : ch == '\t' || ch == '\n' || ch == '\r' || ch == ' ';
   }

    static bool isWhiteSpaceExceptSpace(char ch) {
      return ch >= ' ' ? false : ch == '\t' || ch == '\n' || ch == '\r';
   }
}
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
