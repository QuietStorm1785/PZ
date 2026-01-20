#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElement.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeRef.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeElementInfoImpl {
public:
   : public ElementInfoImpl<Type, Class, Field, Method>.PropertyImpl
   , public RuntimeElementPropertyInfo,
   RuntimeTypeRef {
   RuntimeElementInfoImpl$RuntimePropertyImpl(RuntimeElementInfoImpl this$0) {
      super(this$0);
      this.this$0 = this$0;
   }

    Accessor getAccessor() {
      return RuntimeElementInfoImpl.access$000(this.this$0) == nullptr
         ? Accessor.JAXB_ELEMENT_VALUE
         : Accessor.JAXB_ELEMENT_VALUE.adapt((Class)this.getAdapter().defaultType, RuntimeElementInfoImpl.access$000(this.this$0));
   }

    Type getRawType() {
      return Collection.class;
   }

    Type getIndividualType() {
      return (Type)this.this$0.getContentType().getType();
   }

    bool elementOnlyContent() {
    return false;
   }

   public List<? : public RuntimeTypeRef> getTypes() {
      return Collections.singletonList(this);
   }

   public List<? : public RuntimeNonElement> ref() {
      return super.ref();
   }

    RuntimeNonElement getTarget() {
      return (RuntimeNonElement)super.getTarget();
   }

    RuntimePropertyInfo getSource() {
    return this;
   }

    Transducer getTransducer() {
      return RuntimeModelBuilder.createTransducer(this);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
