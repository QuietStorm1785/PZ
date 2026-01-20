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
namespace model {
namespace nav {


class ReflectionNavigator {
public:
   ReflectionNavigator$4(ReflectionNavigator this$0, Class var2, std::string var3) {
      this.this$0 = this$0;
      this.val$clazz = var2;
      this.val$fieldName = var3;
   }

    Field run() {
      try {
         return this.val$clazz.getDeclaredField(this.val$fieldName);
      } catch (NoSuchFieldException var2) {
    return nullptr;
      }
   }
}
} // namespace nav
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
