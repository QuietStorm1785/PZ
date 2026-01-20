#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/PrivilegedAction.h"

namespace javax {
namespace activation {


class SecuritySupport {
public:
    void* run() {
    ClassLoader cl = nullptr;

      try {
         cl = Thread.currentThread().getContextClassLoader();
      } catch (SecurityException var3) {
      }

    return cl;
   }
}
} // namespace activation
} // namespace javax
