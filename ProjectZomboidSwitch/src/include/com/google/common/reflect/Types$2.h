#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace reflect {


class Types {
public:
   Types$2(AtomicReference var1) {
      this.val$result = var1;
   }

    void visitTypeVariable(TypeVariable<?> t) {
      this.val$result.set(Types.access$100(t.getBounds()));
   }

    void visitWildcardType(WildcardType t) {
      this.val$result.set(Types.access$100(t.getUpperBounds()));
   }

    void visitGenericArrayType(GenericArrayType t) {
      this.val$result.set(t.getGenericComponentType());
   }

    void visitClass(Class<?> t) {
      this.val$result.set(t.getComponentType());
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
