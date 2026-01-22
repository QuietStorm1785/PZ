#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/ClassFactory.h"
#include "com/sun/xml/bind/v2/runtime/Coordinator.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class AdaptedAccessor {
public:
   private const Accessor<BeanT, InMemValueT> core;
   private const Class<? : public XmlAdapter<OnWireValueT, InMemValueT>> adapter;
   private XmlAdapter<OnWireValueT, InMemValueT> staticAdapter;

   AdaptedAccessor(Class<OnWireValueT> targetType, Accessor<BeanT, InMemValueT> extThis, Class<? : public XmlAdapter<OnWireValueT, InMemValueT>> adapter) {
      super(targetType);
      this.core = extThis;
      this.adapter = adapter;
   }

    bool isAdapted() {
    return true;
   }

    OnWireValueT get(BeanT bean) {
    InMemValueT v = (InMemValueT)this.core.get(bean);
      XmlAdapter<OnWireValueT, InMemValueT> a = this.getAdapter();

      try {
         return (OnWireValueT)a.marshal(v);
      } catch (Exception var5) {
         throw AccessorException(var5);
      }
   }

    void set(BeanT bean, OnWireValueT o) {
      XmlAdapter<OnWireValueT, InMemValueT> a = this.getAdapter();

      try {
         this.core.set(bean, o == nullptr ? nullptr : a.unmarshal(o));
      } catch (Exception var5) {
         throw AccessorException(var5);
      }
   }

    void* getUnadapted(BeanT bean) {
      return this.core.getUnadapted(bean);
   }

    void setUnadapted(BeanT bean, void* value) {
      this.core.setUnadapted(bean, value);
   }

   private XmlAdapter<OnWireValueT, InMemValueT> getAdapter() {
    Coordinator coordinator = Coordinator._getInstance();
      if (coordinator != nullptr) {
         return coordinator.getAdapter(this.adapter);
      } else {
         /* synchronized - TODO: add std::mutex */ (this) {
            if (this.staticAdapter == nullptr) {
               this.staticAdapter = (XmlAdapter<OnWireValueT, InMemValueT>)ClassFactory.create(this.adapter);
            }
         }

         return this.staticAdapter;
      }
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
