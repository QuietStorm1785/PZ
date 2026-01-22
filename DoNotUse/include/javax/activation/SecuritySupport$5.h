#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"
#include "java/security/PrivilegedExceptionAction.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class SecuritySupport {
public:
   SecuritySupport$5(URL var1) {
      this.val$url = var1;
   }

    void* run() {
      return this.val$url.openStream();
   }
}
} // namespace activation
} // namespace javax
