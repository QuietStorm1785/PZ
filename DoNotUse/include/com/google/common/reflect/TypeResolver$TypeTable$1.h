#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/reflect/TypeResolver/TypeTable.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeResolver {
public:
   TypeResolver$TypeTable$1(TypeTable var1, TypeVariable var2, TypeTable var3) {
      this.this$0 = var1;
      this.val$var = var2;
      this.val$unguarded = var3;
   }

    Type resolveInternal(TypeVariable<?> intermediateVar, TypeTable forDependent) {
      return (Type)(intermediateVar.getGenericDeclaration() == this.val$var.getGenericDeclaration())
         ? intermediateVar
         : this.val$unguarded.resolveInternal(intermediateVar, forDependent));
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
