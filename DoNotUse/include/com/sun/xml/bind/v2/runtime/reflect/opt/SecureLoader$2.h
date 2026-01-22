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
namespace v2 {
namespace runtime {
namespace reflect {
namespace opt {


class SecureLoader {
public:
   SecureLoader$2(Class var1) {
      this.val$c = var1;
   }

    void* run() {
      return this.val$c.getClassLoader();
   }
}
} // namespace opt
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
