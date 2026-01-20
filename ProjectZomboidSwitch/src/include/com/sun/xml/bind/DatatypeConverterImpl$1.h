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


class DatatypeConverterImpl {
public:
    ClassLoader run() {
      return Thread.currentThread().getContextClassLoader();
   }
}
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
