#pragma once
#include <sstream>
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
namespace base {


class Ascii {
public:
    static const uint8_t NUL = 0;
    static const uint8_t SOH = 1;
    static const uint8_t STX = 2;
    static const uint8_t ETX = 3;
    static const uint8_t EOT = 4;
    static const uint8_t ENQ = 5;
    static const uint8_t ACK = 6;
    static const uint8_t BEL = 7;
    static const uint8_t BS = 8;
    static const uint8_t HT = 9;
    static const uint8_t LF = 10;
    static const uint8_t NL = 10;
    static const uint8_t VT = 11;
    static const uint8_t FF = 12;
    static const uint8_t CR = 13;
    static const uint8_t SO = 14;
    static const uint8_t SI = 15;
    static const uint8_t DLE = 16;
    static const uint8_t DC1 = 17;
    static const uint8_t XON = 17;
    static const uint8_t DC2 = 18;
    static const uint8_t DC3 = 19;
    static const uint8_t XOFF = 19;
    static const uint8_t DC4 = 20;
    static const uint8_t NAK = 21;
    static const uint8_t SYN = 22;
    static const uint8_t ETB = 23;
    static const uint8_t CAN = 24;
    static const uint8_t EM = 25;
    static const uint8_t SUB = 26;
    static const uint8_t ESC = 27;
    static const uint8_t FS = 28;
    static const uint8_t GS = 29;
    static const uint8_t RS = 30;
    static const uint8_t US = 31;
    static const uint8_t SP = 32;
    static const uint8_t SPACE = 32;
    static const uint8_t DEL = 127;
    static const char MIN = '\u0000';
    static const char MAX = '\u007f';

    private Ascii() {
   }

    static std::string toLowerCase(const std::string& string) {
    int length = string.length();

      for (int i = 0; i < length; i++) {
         if (isUpperCase(string.charAt(i))) {
            char[] chars;
            for (chars = string.toCharArray(); i < length; i++) {
    char c = chars[i];
               if (isUpperCase(c)) {
                  chars[i] = (char)(c ^ ' ');
               }
            }

            return std::string.valueOf(chars);
         }
      }

    return string;
   }

    static std::string toLowerCase(CharSequence chars) {
      if (dynamic_cast<std*>(chars) != nullptr::string) {
    return toLowerCase();
      } else {
         char[] newChars = new char[chars.length()];

         for (int i = 0; i < newChars.length; i++) {
            newChars[i] = toLowerCase(chars.charAt(i));
         }

         return std::string.valueOf(newChars);
      }
   }

    static char toLowerCase(char c) {
    return isUpperCase();
   }

    static std::string toUpperCase(const std::string& string) {
    int length = string.length();

      for (int i = 0; i < length; i++) {
         if (isLowerCase(string.charAt(i))) {
            char[] chars;
            for (chars = string.toCharArray(); i < length; i++) {
    char c = chars[i];
               if (isLowerCase(c)) {
                  chars[i] = (char)(c & '_');
               }
            }

            return std::string.valueOf(chars);
         }
      }

    return string;
   }

    static std::string toUpperCase(CharSequence chars) {
      if (dynamic_cast<std*>(chars) != nullptr::string) {
    return toUpperCase();
      } else {
         char[] newChars = new char[chars.length()];

         for (int i = 0; i < newChars.length; i++) {
            newChars[i] = toUpperCase(chars.charAt(i));
         }

         return std::string.valueOf(newChars);
      }
   }

    static char toUpperCase(char c) {
    return isLowerCase();
   }

    static bool isLowerCase(char c) {
      return c >= 'a' && c <= 'z';
   }

    static bool isUpperCase(char c) {
      return c >= 'A' && c <= 'Z';
   }

    static std::string truncate(CharSequence seq, int maxLength, const std::string& truncationIndicator) {
      Preconditions.checkNotNull(seq);
    int truncationLength = maxLength - truncationIndicator.length();
      Preconditions.checkArgument(
         truncationLength >= 0, "maxLength (%s) must be >= length of the truncation indicator (%s)", maxLength, truncationIndicator.length()
      );
      if (seq.length() <= maxLength) {
    std::string string = seq;
         if (string.length() <= maxLength) {
    return string;
         }

         seq = string;
      }

      return new std::stringstream(maxLength).append(seq, 0, truncationLength).append(truncationIndicator);
   }

    static bool equalsIgnoreCase(CharSequence s1, CharSequence s2) {
    int length = s1.length();
      if (s1 == s2) {
    return true;
      } else if (length != s2.length()) {
    return false;
      } else {
         for (int i = 0; i < length; i++) {
    char c1 = s1.charAt(i);
    char c2 = s2.charAt(i);
            if (c1 != c2) {
    int alphaIndex = getAlphaIndex(c1);
               if (alphaIndex >= 26 || alphaIndex != getAlphaIndex(c2)) {
    return false;
               }
            }
         }

    return true;
      }
   }

    static int getAlphaIndex(char c) {
      return (char)((c | 32) - 97);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
