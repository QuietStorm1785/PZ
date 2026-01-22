#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/core/LeafInfo.h"
#include "com/sun/xml/bind/v2/runtime/Location.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class LeafInfoImpl {
public:
    const TypeT type;
    const QName typeName;

    protected LeafInfoImpl(TypeT type, QName typeName) {
      assert type != nullptr;

      this.type = type;
      this.typeName = typeName;
   }

    TypeT getType() {
      return this.type;
   }

   /** @deprecated */
    bool canBeReferencedByIDREF() {
    return false;
   }

    QName getTypeName() {
      return this.typeName;
   }

    Locatable getUpstream() {
    return nullptr;
   }

    Location getLocation() {
    return this;
   }

    bool isSimpleType() {
    return true;
   }

    std::string toString() {
      return this.type;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
