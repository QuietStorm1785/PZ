#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/ImmutableList/Builder.h"
#include "com/google/common/reflect/Types/JavaVersion/4.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


enum class Types {
   JAVA6,
   JAVA7,
   JAVA8;

   static const Types$JavaVersion CURRENT;

   private Types$JavaVersion() {
   }

   abstract Type newArrayType(Type var1);

   abstract Type usedInGenericType(Type var1);

    std::string typeName(Type type) {
      return Types.toString(type);
   }

   const ImmutableList<Type> usedInGenericType(Type[] types) {
      Builder<Type> builder = ImmutableList.builder();

    for (auto& type : types)         builder.push_back(this.usedInGenericType(type));
      }

      return builder.build();
   }

   static {
      if (AnnotatedElement.class.isAssignableFrom(TypeVariable.class)) {
         CURRENT = JAVA8;
      } else if (std::make_unique<4>().capture() instanceof Class) {
         CURRENT = JAVA7;
      } else {
         CURRENT = JAVA6;
      }
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
