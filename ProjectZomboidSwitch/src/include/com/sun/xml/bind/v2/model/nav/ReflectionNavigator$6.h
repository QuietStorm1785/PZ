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
    Class onClass(Class c, Void v) {
    return c;
   }

    Class onParameterizdType(ParameterizedType p, Void v) {
      return (Class)this.visit(p.getRawType(), nullptr);
   }

    Class onGenericArray(GenericArrayType g, Void v) {
      return Array.newInstance((Class<?>)this.visit(g.getGenericComponentType(), nullptr), 0).getClass();
   }

    Class onVariable(TypeVariable tv, Void v) {
      return (Class)this.visit(tv.getBounds()[0], nullptr);
   }

    Class onWildcard(WildcardType w, Void v) {
      return (Class)this.visit(w.getUpperBounds()[0], nullptr);
   }
}
} // namespace nav
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
