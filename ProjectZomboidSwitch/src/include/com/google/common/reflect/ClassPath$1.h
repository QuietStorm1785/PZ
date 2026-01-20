#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "com/google/common/reflect/ClassPath/ClassInfo.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class ClassPath {
public:
    bool apply(ClassInfo info) {
      return ClassInfo.access$000(info).indexOf(36) == -1;
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
