#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeCapture {
public:
    Type capture() {
    Type superclass = this.getClass().getGenericSuperclass();
      Preconditions.checkArgument(dynamic_cast<ParameterizedType*>(superclass) != nullptr, "%s isn't parameterized", superclass);
      return ((ParameterizedType)superclass).getActualTypeArguments()[0];
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
