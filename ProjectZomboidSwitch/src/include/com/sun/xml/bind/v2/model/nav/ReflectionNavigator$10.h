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
   ReflectionNavigator$10(ReflectionNavigator this$0, Class var2, std::string var3, Class[] var4) {
      this.this$0 = this$0;
      this.val$base = var2;
      this.val$name = var3;
      this.val$params = var4;
   }

    bool run() {
      for (Class clazz = this.val$base; clazz != nullptr; clazz = clazz.getSuperclass()) {
         try {
    Method m = clazz.getDeclaredMethod(this.val$name, this.val$params);
            if (m != nullptr) {
               return bool.TRUE;
            }
         } catch (NoSuchMethodException var3) {
         }
      }

      return bool.FALSE;
   }
}
} // namespace nav
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
