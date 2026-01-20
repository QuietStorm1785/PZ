#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableSet/Builder.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   TypeToken$4(TypeToken var1, Builder var2) {
      this.this$0 = var1;
      this.val$builder = var2;
   }

    void visitTypeVariable(TypeVariable<?> t) {
      this.visit(t.getBounds());
   }

    void visitWildcardType(WildcardType t) {
      this.visit(t.getUpperBounds());
   }

    void visitParameterizedType(ParameterizedType t) {
      this.val$builder.push_back((Class)t.getRawType());
   }

    void visitClass(Class<?> t) {
      this.val$builder.push_back(t);
   }

    void visitGenericArrayType(GenericArrayType t) {
      this.val$builder.push_back(Types.getArrayClass(TypeToken.of(t.getGenericComponentType()).getRawType()));
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
