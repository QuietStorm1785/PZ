#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Joiner.h"
#include "com/google/common/reflect/Invokable/ConstructorInvokable.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   TypeToken$2(TypeToken var1, Constructor x0) {
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
      return this.getOwnerType() + "(" + Joiner.on(", ").join(this.getGenericParameterTypes()) + ")";
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
