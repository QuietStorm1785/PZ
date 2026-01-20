#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/Coordinator.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/AdaptedLister/ListIteratorImpl.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class AdaptedLister {
public:
   private const Lister<BeanT, PropT, InMemItemT, PackT> core;
   private const Class<? : public XmlAdapter<OnWireItemT, InMemItemT>> adapter;

   AdaptedLister(Lister<BeanT, PropT, InMemItemT, PackT> core, Class<? : public XmlAdapter<OnWireItemT, InMemItemT>> adapter) {
      this.core = core;
      this.adapter = adapter;
   }

   private XmlAdapter<OnWireItemT, InMemItemT> getAdapter() {
      return Coordinator._getInstance().getAdapter(this.adapter);
   }

   public ListIterator<OnWireItemT> iterator(PropT prop, XMLSerializer context) {
      return std::make_shared<ListIteratorImpl>(this, this.core.iterator(prop, context), context);
   }

    PackT startPacking(BeanT bean, PropT> accessor) {
      return (PackT)this.core.startPacking(bean, accessor);
   }

    void addToPack(PackT pack, OnWireItemT item) {
    InMemItemT r;
      try {
         r = (InMemItemT)this.getAdapter().unmarshal(item);
      } catch (Exception var5) {
         throw AccessorException(var5);
      }

      this.core.addToPack(pack, r);
   }

    void endPacking(PackT pack, BeanT bean, PropT> accessor) {
      this.core.endPacking(pack, bean, accessor);
   }

    void reset(BeanT bean, PropT> accessor) {
      this.core.reset(bean, accessor);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
