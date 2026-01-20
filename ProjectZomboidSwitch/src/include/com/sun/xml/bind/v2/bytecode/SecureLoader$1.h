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
namespace bytecode {


class SecureLoader {
public:
    void* run() {
      return Thread.currentThread().getContextClassLoader();
   }
}
} // namespace bytecode
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
