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


class Utils {
public:
   Utils$1(Class var1) {
      this.val$refNav = var1;
   }

    Method run() {
      try {
    Method getInstance = this.val$refNav.getDeclaredMethod("getInstance");
         getInstance.setAccessible(true);
    return getInstance;
      } catch (NoSuchMethodException var2) {
         throw IllegalStateException("ReflectionNavigator.getInstance can't be found");
      }
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
