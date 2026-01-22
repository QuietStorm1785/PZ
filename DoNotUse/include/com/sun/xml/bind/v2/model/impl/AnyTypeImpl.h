#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "com/sun/xml/bind/v2/runtime/Location.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class AnyTypeImpl {
public:
    const T type;
   private const Navigator<T, C, ?, ?> nav;

    public AnyTypeImpl(?> nav) {
      this.type = (T)nav.ref(Object.class);
      this.nav = nav;
   }

    QName getTypeName() {
    return ANYTYPE_NAME;
   }

    T getType() {
      return this.type;
   }

    Locatable getUpstream() {
    return nullptr;
   }

    bool isSimpleType() {
    return false;
   }

    Location getLocation() {
      return this.nav.getClassLocation(this.nav.asDecl(Object.class));
   }

   /** @deprecated */
    bool canBeReferencedByIDREF() {
    return true;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
