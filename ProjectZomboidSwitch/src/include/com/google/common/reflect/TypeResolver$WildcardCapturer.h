#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Joiner.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeResolver {
public:
    const AtomicInteger id = std::make_shared<AtomicInteger>();

   private TypeResolver$WildcardCapturer() {
   }

    Type capture(Type type) {
      Preconditions.checkNotNull(type);
      if (dynamic_cast<Class*>(type) != nullptr) {
    return type;
      } else if (dynamic_cast<TypeVariable*>(type) != nullptr) {
    return type;
      } else if (dynamic_cast<GenericArrayType*>(type) != nullptr) {
    GenericArrayType arrayType = (GenericArrayType)type;
         return Types.newArrayType(this.capture(arrayType.getGenericComponentType()));
      } else if (dynamic_cast<ParameterizedType*>(type) != nullptr) {
    ParameterizedType parameterizedType = (ParameterizedType)type;
         return Types.newParameterizedTypeWithOwner(
            this.captureNullable(parameterizedType.getOwnerType()),
            (Class)parameterizedType.getRawType(),
            this.capture(parameterizedType.getActualTypeArguments())
         );
      } else if (dynamic_cast<WildcardType*>(type) != nullptr) {
    WildcardType wildcardType = (WildcardType)type;
         Type[] lowerBounds = wildcardType.getLowerBounds();
         if (lowerBounds.length == 0) {
            Type[] upperBounds = wildcardType.getUpperBounds();
    std::string name = "capture#" + this.id.incrementAndGet() + "-of ? : public " + Joiner.on('&').join(upperBounds);
            return Types.newArtificialTypeVariable(TypeResolver$WildcardCapturer.class, name, wildcardType.getUpperBounds());
         } else {
    return type;
         }
      } else {
         throw AssertionError("must have been one of the known types");
      }
   }

    Type captureNullable(@Nullable Type) {
    return type = = nullptr ? nullptr : this.capture(type);
   }

   private Type[] capture(Type[] types) {
      Type[] result = new Type[types.length];

      for (int i = 0; i < types.length; i++) {
         result[i] = this.capture(types[i]);
      }

    return result;
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
