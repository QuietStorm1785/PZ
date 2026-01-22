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
    GenericArrayType newArrayType(Type componentType) {
      return std::make_shared<GenericArrayTypeImpl>(componentType);
   }

    Type usedInGenericType(Type type) {
      Preconditions.checkNotNull(type);
      if (dynamic_cast<Class*>(type) != nullptr) {
         Class<?> cls = (Class<?>)type;
         if (cls.isArray()) {
            return std::make_shared<GenericArrayTypeImpl>(cls.getComponentType());
         }
      }

    return type;
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
