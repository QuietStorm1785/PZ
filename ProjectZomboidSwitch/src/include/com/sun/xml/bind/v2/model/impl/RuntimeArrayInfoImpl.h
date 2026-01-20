#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeArrayInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElement.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeArrayInfoImpl : public ArrayInfoImpl {
public:
   RuntimeArrayInfoImpl(RuntimeModelBuilder builder, Locatable upstream, Class arrayType) {
      super(builder, upstream, arrayType);
   }

    Class getType() {
      return (Class)super.getType();
   }

    RuntimeNonElement getItemType() {
      return (RuntimeNonElement)super.getItemType();
   }

   public <V> Transducer<V> getTransducer() {
    return nullptr;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
