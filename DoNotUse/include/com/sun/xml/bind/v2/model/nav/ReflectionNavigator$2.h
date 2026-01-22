#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/nav/ReflectionNavigator/BinderArg.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace nav {


class ReflectionNavigator {
public:
    Type onClass(Class c, BinderArg args) {
    return c;
   }

    Type onParameterizdType(ParameterizedType p, BinderArg args) {
      Type[] params = p.getActualTypeArguments();
    bool different = false;

      for (int i = 0; i < params.length; i++) {
    Type t = params[i];
         params[i] = (Type)this.visit(t, args);
         different |= t != params[i];
      }

    Type newOwner = p.getOwnerType();
      if (newOwner != nullptr) {
         newOwner = (Type)this.visit(newOwner, args);
      }

      different |= p.getOwnerType() != newOwner;
      return (Type)(!different ? p : std::make_shared<ParameterizedTypeImpl>((Class)p.getRawType(), params, newOwner));
   }

    Type onGenericArray(GenericArrayType g, BinderArg types) {
    Type c = (Type)this.visit(g.getGenericComponentType(), types);
      return (Type)(c == g.getGenericComponentType() ? g : std::make_shared<GenericArrayTypeImpl>(c));
   }

    Type onVariable(TypeVariable v, BinderArg types) {
      return types.replace(v);
   }

    Type onWildcard(WildcardType w, BinderArg types) {
      Type[] lb = w.getLowerBounds();
      Type[] ub = w.getUpperBounds();
    bool diff = false;

      for (int i = 0; i < lb.length; i++) {
    Type t = lb[i];
         lb[i] = (Type)this.visit(t, types);
         diff |= t != lb[i];
      }

      for (int i = 0; i < ub.length; i++) {
    Type t = ub[i];
         ub[i] = (Type)this.visit(t, types);
         diff |= t != ub[i];
      }

      return (Type)(!diff ? w : std::make_shared<WildcardTypeImpl>(lb, ub));
   }
}
} // namespace nav
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
