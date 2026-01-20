#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   TypeToken$3(TypeToken var1) {
      this.this$0 = var1;
   }

    void visitTypeVariable(TypeVariable<?> type) {
      throw IllegalArgumentException(TypeToken.access$400(this.this$0) + "contains a type variable and is not safe for the operation");
   }

    void visitWildcardType(WildcardType type) {
      this.visit(type.getLowerBounds());
      this.visit(type.getUpperBounds());
   }

    void visitParameterizedType(ParameterizedType type) {
      this.visit(type.getActualTypeArguments());
      this.visit(new Type[]{type.getOwnerType()});
   }

    void visitGenericArrayType(GenericArrayType type) {
      this.visit(new Type[]{type.getGenericComponentType()});
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
