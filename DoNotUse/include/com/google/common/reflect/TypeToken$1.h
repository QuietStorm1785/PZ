#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/reflect/Invokable/MethodInvokable.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   TypeToken$1(TypeToken var1, Method x0) {
      super(x0);
      this.this$0 = var1;
   }

    Type getGenericReturnType() {
      return this.this$0.resolveType(super.getGenericReturnType()).getType();
   }

   Type[] getGenericParameterTypes() {
      return TypeToken.access$000(this.this$0, super.getGenericParameterTypes());
   }

   Type[] getGenericExceptionTypes() {
      return TypeToken.access$000(this.this$0, super.getGenericExceptionTypes());
   }

   public TypeToken<T> getOwnerType() {
      return this.this$0;
   }

    std::string toString() {
      return this.getOwnerType() + "." + super;
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
