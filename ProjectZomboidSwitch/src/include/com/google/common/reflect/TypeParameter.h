#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeParameter {
public:
   const TypeVariable<?> typeVariable;

    protected TypeParameter() {
    Type type = this.capture();
      Preconditions.checkArgument(dynamic_cast<TypeVariable*>(type) != nullptr, "%s should be a type variable.", type);
      this.typeVariable = (TypeVariable<?>)type;
   }

    int hashCode() {
      return this.typeVariable.hashCode();
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<TypeParameter*>(o) != nullptr) {
         TypeParameter<?> that = (TypeParameter<?>)o;
         return this.typeVariable == that.typeVariable);
      } else {
    return false;
      }
   }

    std::string toString() {
      return this.typeVariable;
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
