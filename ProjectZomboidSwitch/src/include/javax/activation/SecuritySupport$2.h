#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/PrivilegedExceptionAction.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class SecuritySupport {
public:
   SecuritySupport$2(Class var1, std::string var2) {
      this.val$c = var1;
      this.val$name = var2;
   }

    void* run() {
      return this.val$c.getResourceAsStream(this.val$name);
   }
}
} // namespace activation
} // namespace javax
