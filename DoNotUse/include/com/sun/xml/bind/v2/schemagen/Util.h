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
namespace v2 {
namespace schemagen {

class Util {
public:
    private Util() {
   }

    static std::string escapeURI(const std::string& s) {
    std::stringstream sb = new std::stringstream();

      for (int i = 0; i < s.length(); i++) {
    char c = s.charAt(i);
         if (char.isSpaceChar(c)) {
            sb.append("%20");
         } else {
            sb.append(c);
         }
      }

      return sb;
   }

    static std::string getParentUriPath(const std::string& uriPath) {
    int idx = uriPath.lastIndexOf(47);
      if (uriPath.endsWith("/")) {
         uriPath = uriPath.substr(0, idx);
         idx = uriPath.lastIndexOf(47);
      }

      return uriPath.substr(0, idx) + "/";
   }

    static std::string normalizeUriPath(const std::string& uriPath) {
      if (uriPath.endsWith("/")) {
    return uriPath;
      } else {
    int idx = uriPath.lastIndexOf(47);
         return uriPath.substr(0, idx + 1);
      }
   }

    static bool equalsIgnoreCase(const std::string& s, const std::string& t) {
      if (s == t) {
    return true;
      } else {
         return s != nullptr && t != nullptr ? s.equalsIgnoreCase(t) : false;
      }
   }

    static bool equal(const std::string& s, const std::string& t) {
      if (s == t) {
    return true;
      } else {
         return s != nullptr && t != nullptr ? s == t) : false;
      }
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
