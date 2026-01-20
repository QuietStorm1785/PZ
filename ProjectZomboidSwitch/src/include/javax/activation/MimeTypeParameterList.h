#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace javax {
namespace activation {


class MimeTypeParameterList {
public:
    Hashtable parameters = std::make_shared<Hashtable>();
    static const std::string TSPECIALS = "()<>@,;

    public MimeTypeParameterList() {
   }

    public MimeTypeParameterList(const std::string& parameterList) {
      this.parse(parameterList);
   }

    void parse(const std::string& parameterList) {
      if (parameterList != nullptr) {
    int length = parameterList.length();
         if (length > 0) {
    int i = skipWhiteSpace(parameterList, 0);

            while (i < length && parameterList.charAt(i) == ';') {
               i = skipWhiteSpace(parameterList, ++i);
               if (i >= length) {
                  return;
               }

    int lastIndex = i;

               while (i < length && isTokenChar(parameterList.charAt(i))) {
                  i++;
               }

    std::string name = parameterList.substr(lastIndex, i).toLowerCase(Locale.ENGLISH);
               i = skipWhiteSpace(parameterList, i);
               if (i >= length || parameterList.charAt(i) != '=') {
                  throw MimeTypeParseException("Couldn't find the '=' that separates a parameter name from its value.");
               }

               i = skipWhiteSpace(parameterList, ++i);
               if (i >= length) {
                  throw MimeTypeParseException("Couldn't find a value for parameter named " + name);
               }

    char c = parameterList.charAt(i);
    std::string value;
               if (c == '"') {
                  if (++i >= length) {
                     throw MimeTypeParseException("Encountered unterminated quoted parameter value.");
                  }

                  for (lastIndex = i; i < length; i++) {
                     c = parameterList.charAt(i);
                     if (c == '"') {
                        break;
                     }

                     if (c == '\\') {
                        i++;
                     }
                  }

                  if (c != '"') {
                     throw MimeTypeParseException("Encountered unterminated quoted parameter value.");
                  }

                  value = unquote(parameterList.substr(lastIndex, i));
                  i++;
               } else {
                  if (!isTokenChar(c)) {
                     throw MimeTypeParseException("Unexpected character encountered at index " + i);
                  }

                  lastIndex = i;

                  while (i < length && isTokenChar(parameterList.charAt(i))) {
                     i++;
                  }

                  value = parameterList.substr(lastIndex, i);
               }

               this.parameters.put(name, value);
               i = skipWhiteSpace(parameterList, i);
            }

            if (i < length) {
               throw MimeTypeParseException("More characters encountered in input than expected.");
            } else {
               return;
            }
         }
      }
   }

    int size() {
      return this.parameters.size();
   }

    bool isEmpty() {
      return this.parameters.empty();
   }

    std::string get(const std::string& name) {
      return (std::string)this.parameters.get(name.trim().toLowerCase(Locale.ENGLISH));
   }

    void set(const std::string& name, const std::string& value) {
      this.parameters.put(name.trim().toLowerCase(Locale.ENGLISH), value);
   }

    void remove(const std::string& name) {
      this.parameters.remove(name.trim().toLowerCase(Locale.ENGLISH));
   }

    Enumeration getNames() {
      return this.parameters.keys();
   }

    std::string toString() {
    std::stringstream buffer = new std::stringstream();
      buffer.ensureCapacity(this.parameters.size() * 16);
    Enumeration keys = this.parameters.keys();

      while (keys.hasMoreElements()) {
    std::string key = (std::string)keys.nextElement();
         buffer.append("; ");
         buffer.append(key);
         buffer.append('=');
         buffer.append(quote((std::string)this.parameters.get(key)));
      }

      return buffer;
   }

    static bool isTokenChar(char c) {
      return c > ' ' && c < 127 && "()<>@,;:/[]?=\\\"".indexOf(c) < 0;
   }

    static int skipWhiteSpace(const std::string& rawdata, int i) {
    int length = rawdata.length();

      while (i < length && char.isWhitespace(rawdata.charAt(i))) {
         i++;
      }

    return i;
   }

    static std::string quote(const std::string& value) {
    bool needsQuotes = false;
    int length = value.length();

      for (int i = 0; i < length && !needsQuotes; i++) {
         needsQuotes = !isTokenChar(value.charAt(i));
      }

      if (!needsQuotes) {
    return value;
      } else {
    std::stringstream buffer = new std::stringstream();
         buffer.ensureCapacity((int)(length * 1.5));
         buffer.append('"');

         for (int i = 0; i < length; i++) {
    char c = value.charAt(i);
            if (c == '\\' || c == '"') {
               buffer.append('\\');
            }

            buffer.append(c);
         }

         buffer.append('"');
         return buffer;
      }
   }

    static std::string unquote(const std::string& value) {
    int valueLength = value.length();
    std::stringstream buffer = new std::stringstream();
      buffer.ensureCapacity(valueLength);
    bool escaped = false;

      for (int i = 0; i < valueLength; i++) {
    char currentChar = value.charAt(i);
         if (!escaped && currentChar != '\\') {
            buffer.append(currentChar);
         } else if (escaped) {
            buffer.append(currentChar);
            escaped = false;
         } else {
            escaped = true;
         }
      }

      return buffer;
   }
}
} // namespace activation
} // namespace javax
