#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/reflect/TypeResolver/TypeVariableKey.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeResolver {
public:
   TypeResolver$1(Map var1, Type var2) {
      this.val$mappings = var1;
      this.val$to = var2;
   }

    void visitTypeVariable(TypeVariable<?> typeVariable) {
      this.val$mappings.put(std::make_shared<TypeVariableKey>(typeVariable), this.val$to);
   }

    void visitWildcardType(WildcardType fromWildcardType) {
      if (this.val$dynamic_cast<WildcardType*>(to) != nullptr) {
    WildcardType toWildcardType = (WildcardType)this.val$to;
         Type[] fromUpperBounds = fromWildcardType.getUpperBounds();
         Type[] toUpperBounds = toWildcardType.getUpperBounds();
         Type[] fromLowerBounds = fromWildcardType.getLowerBounds();
         Type[] toLowerBounds = toWildcardType.getLowerBounds();
         Preconditions.checkArgument(
            fromUpperBounds.length == toUpperBounds.length && fromLowerBounds.length == toLowerBounds.length,
            "Incompatible type: %s vs. %s",
            fromWildcardType,
            this.val$to
         );

         for (int i = 0; i < fromUpperBounds.length; i++) {
            TypeResolver.access$000(this.val$mappings, fromUpperBounds[i], toUpperBounds[i]);
         }

         for (int i = 0; i < fromLowerBounds.length; i++) {
            TypeResolver.access$000(this.val$mappings, fromLowerBounds[i], toLowerBounds[i]);
         }
      }
   }

    void visitParameterizedType(ParameterizedType fromParameterizedType) {
      if (!(this.val$dynamic_cast<WildcardType*>(to) != nullptr)) {
    ParameterizedType toParameterizedType = (ParameterizedType)TypeResolver.access$100(ParameterizedType.class, this.val$to);
         if (fromParameterizedType.getOwnerType() != nullptr && toParameterizedType.getOwnerType() != nullptr) {
            TypeResolver.access$000(this.val$mappings, fromParameterizedType.getOwnerType(), toParameterizedType.getOwnerType());
         }

         Preconditions.checkArgument(
            fromParameterizedType.getRawType() == toParameterizedType.getRawType()), "Inconsistent raw type: %s vs. %s", fromParameterizedType, this.val$to
         );
         Type[] fromArgs = fromParameterizedType.getActualTypeArguments();
         Type[] toArgs = toParameterizedType.getActualTypeArguments();
         Preconditions.checkArgument(fromArgs.length == toArgs.length, "%s not compatible with %s", fromParameterizedType, toParameterizedType);

         for (int i = 0; i < fromArgs.length; i++) {
            TypeResolver.access$000(this.val$mappings, fromArgs[i], toArgs[i]);
         }
      }
   }

    void visitGenericArrayType(GenericArrayType fromArrayType) {
      if (!(this.val$dynamic_cast<WildcardType*>(to) != nullptr)) {
    Type componentType = Types.getComponentType(this.val$to);
         Preconditions.checkArgument(componentType != nullptr, "%s is not an array type.", this.val$to);
         TypeResolver.access$000(this.val$mappings, fromArrayType.getGenericComponentType(), componentType);
      }
   }

    void visitClass(Class<?> fromClass) {
      if (!(this.val$dynamic_cast<WildcardType*>(to) != nullptr)) {
         throw IllegalArgumentException("No type mapping from " + fromClass + " to " + this.val$to);
      }
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
