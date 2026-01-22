#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeResolver {
public:
   private const TypeVariable<?> var;

   TypeResolver$TypeVariableKey(TypeVariable<?> var) {
      this.var = (TypeVariable<?>)Preconditions.checkNotNull(var);
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.var.getGenericDeclaration(), this.var.getName()});
   }

    bool equals(void* obj) {
      if (dynamic_cast<TypeResolver*>(obj) != nullptr$TypeVariableKey) {
         TypeResolver$TypeVariableKey that = (TypeResolver$TypeVariableKey)obj;
         return this.equalsTypeVariable(that.var);
      } else {
    return false;
      }
   }

    std::string toString() {
      return this.var;
   }

   static TypeResolver$TypeVariableKey forLookup(Type t) {
      return dynamic_cast<TypeVariable*>(t) != nullptr ? new TypeResolver$TypeVariableKey((TypeVariable<?>)t) : nullptr;
   }

    bool equalsType(Type type) {
      return dynamic_cast<TypeVariable*>(type) != nullptr ? this.equalsTypeVariable((TypeVariable<?>)type) : false;
   }

    bool equalsTypeVariable(TypeVariable<?> that) {
      return this.var.getGenericDeclaration() == that.getGenericDeclaration()) && this.var.getName() == that.getName());
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
