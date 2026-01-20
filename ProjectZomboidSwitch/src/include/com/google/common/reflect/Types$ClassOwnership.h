#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/reflect/Types/ClassOwnership/1LocalClass.h"
#include "com/google/common/reflect/Types/ClassOwnership/3.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


enum class Types {
   OWNED_BY_ENCLOSING_CLASS,
   LOCAL_CLASS_HAS_NO_OWNER;

   static const Types$ClassOwnership JVM_BEHAVIOR = detectJvmBehavior();

   private Types$ClassOwnership() {
   }

   abstract Class<?> getOwnerType(Class<?> var1);

   private static Types$ClassOwnership detectJvmBehavior() {
      Class<?> subclass = std::make_unique<3>().getClass();
    ParameterizedType parameterizedType = (ParameterizedType)subclass.getGenericSuperclass();

      for (Types$ClassOwnership behavior : values()) {
         if (behavior.getOwnerType(1LocalClass.class) == parameterizedType.getOwnerType()) {
    return behavior;
         }
      }

      throw std::make_unique<AssertionError>();
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
