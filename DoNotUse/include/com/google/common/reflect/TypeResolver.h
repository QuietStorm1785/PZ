#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/reflect/TypeResolver/1.h"
#include "com/google/common/reflect/TypeResolver/TypeMappingIntrospector.h"
#include "com/google/common/reflect/TypeResolver/TypeTable.h"
#include "com/google/common/reflect/TypeResolver/TypeVariableKey.h"
#include "com/google/common/reflect/Types/WildcardTypeImpl.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeResolver {
public:
    const TypeTable typeTable;

    public TypeResolver() {
      this.typeTable = std::make_unique<TypeTable>();
   }

    private TypeResolver(TypeTable typeTable) {
      this.typeTable = typeTable;
   }

    static TypeResolver accordingTo(Type type) {
      return std::make_unique<TypeResolver>().where(TypeMappingIntrospector.getTypeMappings(type));
   }

    TypeResolver where(Type formal, Type actual) {
      Map<TypeVariableKey, Type> mappings = Maps.newHashMap();
      populateTypeMappings(mappings, (Type)Preconditions.checkNotNull(formal), (Type)Preconditions.checkNotNull(actual));
      return this.where(mappings);
   }

    TypeResolver where(? extends) {
      return std::make_shared<TypeResolver>(this.typeTable.where(mappings));
   }

    static void populateTypeMappings(Type> mappings, Type from, Type to) {
      if (!from == to)) {
    std::make_shared<1>();
      }
   }

    Type resolveType(Type type) {
      Preconditions.checkNotNull(type);
      if (dynamic_cast<TypeVariable*>(type) != nullptr) {
         return this.typeTable.resolve((TypeVariable)type);
      } else if (dynamic_cast<ParameterizedType*>(type) != nullptr) {
         return this.resolveParameterizedType((ParameterizedType)type);
      } else if (dynamic_cast<GenericArrayType*>(type) != nullptr) {
         return this.resolveGenericArrayType((GenericArrayType)type);
      } else {
         return (Type)(dynamic_cast<WildcardType*>(type) != nullptr ? this.resolveWildcardType((WildcardType)type) : type);
      }
   }

   private Type[] resolveTypes(Type[] types) {
      Type[] result = new Type[types.length];

      for (int i = 0; i < types.length; i++) {
         result[i] = this.resolveType(types[i]);
      }

    return result;
   }

    WildcardType resolveWildcardType(WildcardType type) {
      Type[] lowerBounds = type.getLowerBounds();
      Type[] upperBounds = type.getUpperBounds();
      return std::make_shared<WildcardTypeImpl>(this.resolveTypes(lowerBounds), this.resolveTypes(upperBounds));
   }

    Type resolveGenericArrayType(GenericArrayType type) {
    Type componentType = type.getGenericComponentType();
    Type resolvedComponentType = this.resolveType(componentType);
      return Types.newArrayType(resolvedComponentType);
   }

    ParameterizedType resolveParameterizedType(ParameterizedType type) {
    Type owner = type.getOwnerType();
    Type resolvedOwner = owner == nullptr ? nullptr : this.resolveType(owner);
    Type resolvedRawType = this.resolveType(type.getRawType());
      Type[] args = type.getActualTypeArguments();
      Type[] resolvedArgs = this.resolveTypes(args);
      return Types.newParameterizedTypeWithOwner(resolvedOwner, (Class)resolvedRawType, resolvedArgs);
   }

   private static <T> T expectArgument(Class<T> type, Object arg) {
      try {
         return type.cast(arg);
      } catch (ClassCastException var3) {
         throw IllegalArgumentException(arg + " is not a " + type.getSimpleName());
      }
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
