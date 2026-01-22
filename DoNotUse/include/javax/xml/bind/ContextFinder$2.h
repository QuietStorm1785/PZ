#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/PrivilegedExceptionAction.h"

namespace javax {
namespace xml {
namespace bind {


class ContextFinder {
public:
   ContextFinder$2(Class var1) {
      this.val$implClass = var1;
   }

    void* run() {
      return this.val$implClass.newInstance();
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
