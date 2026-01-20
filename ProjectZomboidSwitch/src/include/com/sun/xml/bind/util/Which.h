#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace util {


class Which {
public:
    static std::string which(Class clazz) {
    return which();
   }

    static std::string which(const std::string& classname, ClassLoader loader) {
    std::string classnameAsResource = classname.replace('.', '/') + ".class";
      if (loader == nullptr) {
         loader = SecureLoader.getSystemClassLoader();
      }

    URL it = loader.getResource(classnameAsResource);
      return it != nullptr ? it : nullptr;
   }
}
} // namespace util
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
