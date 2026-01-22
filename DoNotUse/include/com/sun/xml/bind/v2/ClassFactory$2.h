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


class ClassFactory {
public:
   ClassFactory$2(Class var1) {
      this.val$clazz = var1;
   }

   public Constructor<T> run() {
      return ClassFactory.access$000(this.val$clazz);
   }
}
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
