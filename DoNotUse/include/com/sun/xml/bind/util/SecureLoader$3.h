#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/PrivilegedAction.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace util {


class SecureLoader {
public:
    ClassLoader run() {
      return ClassLoader.getSystemClassLoader();
   }
}
} // namespace util
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
