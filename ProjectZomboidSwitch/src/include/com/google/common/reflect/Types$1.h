#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/reflect/Types/JavaVersion.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class Types {
public:
    std::string apply(Type from) {
      return JavaVersion.CURRENT.typeName(from);
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
