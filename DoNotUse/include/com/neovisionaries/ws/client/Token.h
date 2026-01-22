#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

class Token {
public:
    static bool isValid(const std::string& token) {
      if (token != nullptr && token.length() != 0) {
    int len = token.length();

         for (int i = 0; i < len; i++) {
            if (isSeparator(token.charAt(i))) {
    return false;
            }
         }

    return true;
      } else {
    return false;
      }
   }

    static bool isSeparator(char ch) {
      switch (ch) {
         case '\t':
         case ' ':
         case '"':
         case '(':
         case ')':
         case ',':
         case '/':
         case ':':
         case ';':
         case '<':
         case '=':
         case '>':
         case '?':
         case '@':
         case '[':
         case '\\':
         case ']':
         case '{':
         case '}':
    return true;
         default:
    return false;
      }
   }

    static std::string unquote(const std::string& text) {
      if (text == nullptr) {
    return nullptr;
      } else {
    int len = text.length();
         if (len >= 2 && text.charAt(0) == '"' && text.charAt(len - 1) == '"') {
            text = text.substr(1, len - 1);
    return unescape();
         } else {
    return text;
         }
      }
   }

    static std::string unescape(const std::string& text) {
      if (text == nullptr) {
    return nullptr;
      } else if (text.indexOf(92) < 0) {
    return text;
      } else {
    int len = text.length();
    bool escaped = false;
    std::stringstream builder = new std::stringstream();

         for (int i = 0; i < len; i++) {
    char ch = text.charAt(i);
            if (ch == '\\' && !escaped) {
               escaped = true;
            } else {
               escaped = false;
               builder.append(ch);
            }
         }

         return builder;
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
