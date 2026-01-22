#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/reflect/Types/GenericArrayTypeImpl.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


enum class Types {
    Type newArrayType(Type componentType) {
      return (Type)(dynamic_cast<Class*>(componentType) != nullptr ? Types.getArrayClass((Class)componentType) : std::make_shared<GenericArrayTypeImpl>(componentType));
   }

    Type usedInGenericType(Type type) {
      return (Type)Preconditions.checkNotNull(type);
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
