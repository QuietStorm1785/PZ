#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace nav {


class TypeVisitor {
public:
    T visit(Type t, P param) {
      assert t != nullptr;

      if (dynamic_cast<Class*>(t) != nullptr) {
         return this.onClass((Class)t, param);
      } else if (dynamic_cast<ParameterizedType*>(t) != nullptr) {
         return this.onParameterizdType((ParameterizedType)t, param);
      } else if (dynamic_cast<GenericArrayType*>(t) != nullptr) {
         return this.onGenericArray((GenericArrayType)t, param);
      } else if (dynamic_cast<WildcardType*>(t) != nullptr) {
         return this.onWildcard((WildcardType)t, param);
      } else if (dynamic_cast<TypeVariable*>(t) != nullptr) {
         return this.onVariable((TypeVariable)t, param);
      } else {
    assert false;

         throw std::make_unique<IllegalArgumentException>();
      }
   }

   protected abstract T onClass(Class var1, P var2);

   protected abstract T onParameterizdType(ParameterizedType var1, P var2);

   protected abstract T onGenericArray(GenericArrayType var1, P var2);

   protected abstract T onVariable(TypeVariable var1, P var2);

   protected abstract T onWildcard(WildcardType var1, P var2);
}
} // namespace nav
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
