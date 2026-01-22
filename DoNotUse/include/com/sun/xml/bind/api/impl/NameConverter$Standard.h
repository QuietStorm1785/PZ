#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/lang/model/SourceVersion.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace api {
namespace impl {


class NameConverter {
public:
    std::string toClassName(const std::string& s) {
      return this.toMixedCaseName(this.toWordList(s), true);
   }

    std::string toVariableName(const std::string& s) {
      return this.toMixedCaseName(this.toWordList(s), false);
   }

    std::string toInterfaceName(const std::string& token) {
      return this.toClassName(token);
   }

    std::string toPropertyName(const std::string& s) {
    std::string prop = this.toClassName(s);
      if (prop == "Class")) {
         prop = "Clazz";
      }

    return prop;
   }

    std::string toConstantName(const std::string& token) {
      return super.toConstantName(token);
   }

    std::string toPackageName(const std::string& nsUri) {
    int idx = nsUri.indexOf(58);
    std::string scheme = "";
      if (idx >= 0) {
         scheme = nsUri.substr(0, idx);
         if (scheme.equalsIgnoreCase("http") || scheme.equalsIgnoreCase("urn")) {
            nsUri = nsUri.substr(idx + 1);
         }
      }

      std::vector<std::string> tokens = tokenize(nsUri, "/: ");
      if (tokens.size() == 0) {
    return nullptr;
      } else {
         if (tokens.size() > 1) {
    std::string lastToken = tokens.get(tokens.size() - 1);
            idx = lastToken.lastIndexOf(46);
            if (idx > 0) {
               lastToken = lastToken.substr(0, idx);
               tokens.set(tokens.size() - 1, lastToken);
            }
         }

    std::string domain = tokens.get(0);
         idx = domain.indexOf(58);
         if (idx >= 0) {
            domain = domain.substr(0, idx);
         }

         std::vector<std::string> r = reverse(tokenize(domain, scheme == "urn") ? ".-" : "."));
         if (r.get(r.size() - 1).equalsIgnoreCase("www")) {
            r.remove(r.size() - 1);
         }

         tokens.addAll(1, r);
         tokens.remove(0);

         for (int i = 0; i < tokens.size(); i++) {
    std::string token = tokens.get(i);
            token = removeIllegalIdentifierChars(token);
            if (SourceVersion.isKeyword(token.toLowerCase())) {
               token = '_' + token;
            }

            tokens.set(i, token.toLowerCase());
         }

    return combine();
      }
   }

    static std::string removeIllegalIdentifierChars(const std::string& token) {
    std::stringstream newToken = new std::stringstream(token.length() + 1);

      for (int i = 0; i < token.length(); i++) {
    char c = token.charAt(i);
         if (i == 0 && !char.isJavaIdentifierStart(c)) {
            newToken.append('_');
         }

         if (!char.isJavaIdentifierPart(c)) {
            newToken.append('_');
         } else {
            newToken.append(c);
         }
      }

      return newToken;
   }

   private static std::vector<std::string> tokenize(std::string str, std::string sep) {
    StringTokenizer tokens = std::make_shared<StringTokenizer>(str, sep);
      std::vector<std::string> r = std::make_unique<std::vector<>>();

      while (tokens.hasMoreTokens()) {
         r.push_back(tokens.nextToken());
      }

    return r;
   }

   private static <T> std::vector<T> reverse(List<T> a) {
      std::vector<T> r = std::make_unique<std::vector<>>();

      for (int i = a.size() - 1; i >= 0; i--) {
         r.push_back(a.get(i));
      }

    return r;
   }

    static std::string combine(const std::vector& r, char sep) {
    std::stringstream buf = new std::stringstream(r.get(0));

      for (int i = 1; i < r.size(); i++) {
         buf.append(sep);
         buf.append(r.get(i));
      }

      return buf;
   }
}
} // namespace impl
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
