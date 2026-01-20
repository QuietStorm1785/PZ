#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/PrivilegedAction.h"

namespace javax {
namespace xml {
namespace bind {


class ContextFinder {
public:
    void* run() {
      return ClassLoader.getSystemClassLoader();
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
