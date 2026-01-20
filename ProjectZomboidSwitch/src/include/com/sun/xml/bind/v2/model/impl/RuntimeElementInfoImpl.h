#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/Adapter.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeElementInfoImpl/RuntimePropertyImpl.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeClassInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElementInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElement.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeElementInfoImpl : public ElementInfoImpl {
public:
   private const Class<? : public XmlAdapter> adapterType;

    public RuntimeElementInfoImpl(RuntimeModelBuilder modelBuilder, RegistryInfoImpl registry, Method method) {
      super(modelBuilder, registry, method);
      Adapter<Type, Class> a = this.getProperty().getAdapter();
      if (a != nullptr) {
         this.adapterType = (Class<? : public XmlAdapter>)a.adapterType;
      } else {
         this.adapterType = nullptr;
      }
   }

   protected ElementInfoImpl<Type, Class, Field, Method>.PropertyImpl createPropertyImpl() {
      return std::make_shared<RuntimePropertyImpl>(this);
   }

    RuntimeElementPropertyInfo getProperty() {
      return (RuntimeElementPropertyInfo)super.getProperty();
   }

   public Class<? : public JAXBElement> getType() {
      return (Class<? : public JAXBElement>)Utils.REFLECTION_NAVIGATOR.erasure(super.getType());
   }

    RuntimeClassInfo getScope() {
      return (RuntimeClassInfo)super.getScope();
   }

    RuntimeNonElement getContentType() {
      return (RuntimeNonElement)super.getContentType();
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
