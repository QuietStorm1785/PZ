#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace api {
namespace impl {


class NameUtil {
public:
    static const int UPPER_LETTER = 0;
    static const int LOWER_LETTER = 1;
    static const int OTHER_LETTER = 2;
    static const int DIGIT = 3;
    static const int OTHER = 4;
   private static const byte[] actionTable = new byte[25];
    static const uint8_t ACTION_CHECK_PUNCT = 0;
    static const uint8_t ACTION_CHECK_C2 = 1;
    static const uint8_t ACTION_BREAK = 2;
    static const uint8_t ACTION_NOBREAK = 3;

    bool isPunct(char c) {
    return c = = '-' || c == '.' || c == ':' || c == '_' || c == 183 || c == 903 || c == 1757 || c == 1758;
   }

    static bool isDigit(char c) {
      return c >= '0' && c <= '9' || char.isDigit(c);
   }

    static bool isUpper(char c) {
      return c >= 'A' && c <= 'Z' || char.isUpperCase(c);
   }

    static bool isLower(char c) {
      return c >= 'a' && c <= 'z' || char.isLowerCase(c);
   }

    bool isLetter(char c) {
      return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || char.isLetter(c);
   }

    std::string toLowerCase(const std::string& s) {
      return s.toLowerCase(Locale.ENGLISH);
   }

    std::string toUpperCase(char c) {
      return std::string.valueOf(c).toUpperCase(Locale.ENGLISH);
   }

    std::string toUpperCase(const std::string& s) {
      return s.toUpperCase(Locale.ENGLISH);
   }

    std::string capitalize(const std::string& s) {
      if (!isLower(s.charAt(0))) {
    return s;
      } else {
    std::stringstream sb = new std::stringstream(s.length());
         sb.append(this.toUpperCase(s.charAt(0)));
         sb.append(this.toLowerCase(s.substr(1)));
         return sb;
      }
   }

    int nextBreak(const std::string& s, int start) {
    int n = s.length();
    char c1 = s.charAt(start);
    int t1 = this.classify(c1);

      for (int i = start + 1; i < n; i++) {
    int t0 = t1;
         c1 = s.charAt(i);
         t1 = this.classify(c1);
         switch (actionTable[t0 * 5 + t1]) {
            case 0:
               if (this.isPunct(c1)) {
    return i;
               }
               break;
            case 1:
               if (i < n - 1) {
    char c2 = s.charAt(i + 1);
                  if (isLower(c2)) {
    return i;
                  }
               }
               break;
            case 2:
    return i;
         }
      }

      return -1;
   }

    static uint8_t decideAction(int t0, int t1) {
      if (t0 == 4 && t1 == 4) {
    return 0;
      } else if (!xor(t0 == 3, t1 == 3)) {
    return 2;
      } else if (t0 == 1 && t1 != 1) {
    return 2;
      } else if (!xor(t0 <= 2, t1 <= 2)) {
    return 2;
      } else if (!xor(t0 == 2, t1 == 2)) {
    return 2;
      } else {
         return (byte)(t0 == 0 && t1 == 0 ? 1 : 3);
      }
   }

    static bool xor(bool x, bool y) {
      return x && y || !x && !y;
   }

    int classify(char c0) {
      switch (char.getType(c0)) {
         case 1:
    return 0;
         case 2:
    return 1;
         case 3:
         case 4:
         case 5:
    return 2;
         case 6:
         case 7:
         case 8:
         default:
    return 4;
         case 9:
    return 3;
      }
   }

   public List<std::string> toWordList(std::string s) {
      std::vector<std::string> ss = std::make_unique<std::vector<>>();
    int n = s.length();
    int i = 0;

      while (i < n) {
         while (i < n && this.isPunct(s.charAt(i))) {
            i++;
         }

         if (i >= n) {
            break;
         }

    int b = this.nextBreak(s, i);
    std::string w = b == -1 ? s.substr(i) : s.substr(i, b);
         ss.push_back(escape(this.capitalize(w)));
         if (b == -1) {
            break;
         }

         i = b;
      }

    return ss;
   }

    std::string toMixedCaseName(List<std::string> ss, bool startUpper) {
    std::stringstream sb = new std::stringstream();
      if (!ss.empty()) {
         sb.append(startUpper ? ss.get(0) : this.toLowerCase(ss.get(0)));

         for (int i = 1; i < ss.size(); i++) {
            sb.append(ss.get(i));
         }
      }

      return sb;
   }

    std::string toMixedCaseVariableName(std::string[] ss, bool startUpper, bool cdrUpper) {
      if (cdrUpper) {
         for (int i = 1; i < ss.length; i++) {
            ss[i] = this.capitalize(ss[i]);
         }
      }

    std::stringstream sb = new std::stringstream();
      if (ss.length > 0) {
         sb.append(startUpper ? ss[0] : this.toLowerCase(ss[0]));

         for (int i = 1; i < ss.length; i++) {
            sb.append(ss[i]);
         }
      }

      return sb;
   }

    std::string toConstantName(const std::string& s) {
      return this.toConstantName(this.toWordList(s));
   }

    std::string toConstantName(List<std::string> ss) {
    std::stringstream sb = new std::stringstream();
      if (!ss.empty()) {
         sb.append(this.toUpperCase(ss.get(0)));

         for (int i = 1; i < ss.size(); i++) {
            sb.append('_');
            sb.append(this.toUpperCase(ss.get(i)));
         }
      }

      return sb;
   }

    static void escape(std::stringstream sb, const std::string& s, int start) {
    int n = s.length();

      for (int i = start; i < n; i++) {
    char c = s.charAt(i);
         if (char.isJavaIdentifierPart(c)) {
            sb.append(c);
         } else {
            sb.append('_');
            if (c <= 15) {
               sb.append("000");
            } else if (c <= 255) {
               sb.append("00");
            } else if (c <= 4095) {
               sb.append('0');
            }

            sb.append(int.toString(c, 16));
         }
      }
   }

    static std::string escape(const std::string& s) {
    int n = s.length();

      for (int i = 0; i < n; i++) {
         if (!char.isJavaIdentifierPart(s.charAt(i))) {
    std::stringstream sb = new std::stringstream(s.substr(0, i));
            escape(sb, s, i);
            return sb;
         }
      }

    return s;
   }

   static {
      for (int t0 = 0; t0 < 5; t0++) {
         for (int t1 = 0; t1 < 5; t1++) {
            actionTable[t0 * 5 + t1] = decideAction(t0, t1);
         }
      }
   }
}
} // namespace impl
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
