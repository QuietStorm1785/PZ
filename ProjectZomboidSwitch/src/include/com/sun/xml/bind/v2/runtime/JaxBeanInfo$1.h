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


class JaxBeanInfo {
public:
   JaxBeanInfo$1(JaxBeanInfo this$0, Class var2) {
      this.this$0 = this$0;
      this.val$c = var2;
   }

   public Method[] run() {
      return this.val$c.getDeclaredMethods();
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
