#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/Location.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace nav {


class ReflectionNavigator {
public:
   ReflectionNavigator$7(ReflectionNavigator this$0, Class var2) {
      this.this$0 = this$0;
      this.val$clazz = var2;
   }

    std::string toString() {
      return this.val$clazz.getName();
   }
}
} // namespace nav
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
