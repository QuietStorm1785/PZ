#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/ImmutableMap/Builder.h"
#include "com/google/common/reflect/TypeResolver/TypeTable/1.h"
#include "com/google/common/reflect/TypeResolver/TypeVariableKey.h"
#include "com/google/common/reflect/Types/NativeTypeVariableEquals.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeResolver {
public:
   private const ImmutableMap<TypeVariableKey, Type> map;

   TypeResolver$TypeTable() {
      this.map = ImmutableMap.of();
   }

   private TypeResolver$TypeTable(ImmutableMap<TypeVariableKey, Type> map) {
      this.map = map;
   }

   const TypeResolver$TypeTable where(Map<TypeVariableKey, ? : public Type> mappings) {
      Builder<TypeVariableKey, Type> builder = ImmutableMap.builder();
      builder.putAll(this.map);

      for (Entry<TypeVariableKey, ? : public Type> mapping : mappings.entrySet()) {
    TypeVariableKey variable = mapping.getKey();
    Type type = mapping.getValue();
         Preconditions.checkArgument(!variable.equalsType(type), "Type variable %s bound to itself", variable);
         builder.put(variable, type);
      }

      return new TypeResolver$TypeTable(builder.build());
   }

    Type resolve(TypeVariable<?> var) {
      TypeResolver$TypeTable guarded = std::make_shared<1>(this, var, this);
      return this.resolveInternal(var, guarded);
   }

    Type resolveInternal(TypeVariable<?> var, TypeResolver$TypeTable forDependants) {
    Type type = (Type)this.map.get(std::make_shared<TypeVariableKey>(var));
      if (type == nullptr) {
         Type[] bounds = var.getBounds();
         if (bounds.length == 0) {
    return var;
         } else {
            Type[] resolvedBounds = TypeResolver.access$300(std::make_shared<TypeResolver>(forDependants, nullptr), bounds);
            return NativeTypeVariableEquals.NATIVE_TYPE_VARIABLE_ONLY && Arrays == (Object[])bounds, (Object[])resolvedBounds)
               ? var
               : Types.newArtificialTypeVariable(var.getGenericDeclaration(), var.getName(), resolvedBounds);
         }
      } else {
         return std::make_shared<TypeResolver>(forDependants, nullptr).resolveType(type);
      }
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
