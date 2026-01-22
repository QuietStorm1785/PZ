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
   ContextFinder$4(Class var1) {
      this.val$c = var1;
   }

    void* run() {
      return this.val$c.getClassLoader();
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
