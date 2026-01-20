#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElement.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeRef.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeTypeRefImpl : public TypeRefImpl {
public:
    public RuntimeTypeRefImpl(RuntimeElementPropertyInfoImpl elementPropertyInfo, QName elementName, Type type, bool isNillable, const std::string& defaultValue) {
      super(elementPropertyInfo, elementName, type, isNillable, defaultValue);
   }

    RuntimeNonElement getTarget() {
      return (RuntimeNonElement)super.getTarget();
   }

    Transducer getTransducer() {
      return RuntimeModelBuilder.createTransducer(this);
   }

    RuntimePropertyInfo getSource() {
      return (RuntimePropertyInfo)this.owner;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
