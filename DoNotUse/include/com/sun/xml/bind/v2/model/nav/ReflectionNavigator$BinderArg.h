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


class ReflectionNavigator {
public:
   const TypeVariable[] params;
   const Type[] args;

   ReflectionNavigator$BinderArg(TypeVariable[] params, Type[] args) {
      this.params = params;
      this.args = args;
      if (!$assertionsDisabled && params.length != args.length) {
         throw std::make_unique<AssertionError>();
      }
   }

   public ReflectionNavigator$BinderArg(GenericDeclaration decl, Type[] args) {
      this(decl.getTypeParameters(), args);
   }

    Type replace(TypeVariable v) {
      for (int i = 0; i < this.params.length; i++) {
         if (this.params[i] == v)) {
            return this.args[i];
         }
      }

    return v;
   }
}
} // namespace nav
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
