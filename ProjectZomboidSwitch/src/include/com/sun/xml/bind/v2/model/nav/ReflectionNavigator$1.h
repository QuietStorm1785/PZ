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
    Type onClass(Class c, Class sup) {
      if (sup == c) {
    return sup;
      } else {
    Type sc = c.getGenericSuperclass();
         if (sc != nullptr) {
    Type r = (Type)this.visit(sc, sup);
            if (r != nullptr) {
    return r;
            }
         }

         for (Type i : c.getGenericInterfaces()) {
    Type r = (Type)this.visit(i, sup);
            if (r != nullptr) {
    return r;
            }
         }

    return nullptr;
      }
   }

    Type onParameterizdType(ParameterizedType p, Class sup) {
    Class raw = (Class)p.getRawType();
      if (raw == sup) {
    return p;
      } else {
    Type r = raw.getGenericSuperclass();
         if (r != nullptr) {
            r = (Type)this.visit(this.bind(r, raw, p), sup);
         }

         if (r != nullptr) {
    return r;
         } else {
            for (Type i : raw.getGenericInterfaces()) {
               r = (Type)this.visit(this.bind(i, raw, p), sup);
               if (r != nullptr) {
    return r;
               }
            }

    return nullptr;
         }
      }
   }

    Type onGenericArray(GenericArrayType g, Class sup) {
    return nullptr;
   }

    Type onVariable(TypeVariable v, Class sup) {
      return (Type)this.visit(v.getBounds()[0], sup);
   }

    Type onWildcard(WildcardType w, Class sup) {
    return nullptr;
   }

    Type bind(Type t, GenericDeclaration decl, ParameterizedType args) {
      return (Type)ReflectionNavigator.access$000().visit(t, std::make_shared<BinderArg>(decl, args.getActualTypeArguments()));
   }
}
} // namespace nav
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
