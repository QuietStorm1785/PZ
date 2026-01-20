#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/SAXException2.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/TODO.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/IDREFS.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/LocatorEx.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/LocatorEx/Snapshot.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Patcher.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "org/xml/sax/SAXException.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Lister {
public:
    const BeanT bean;
   private const List<std::string> idrefs;
    const UnmarshallingContext context;
   private const Accessor<BeanT, PropT> acc;
    const LocatorEx location;

   public Lister$IDREFS$Pack(BeanT var1, Accessor<BeanT, PropT> bean, Accessor acc) {
      this.this$0 = var1;
      this.idrefs = std::make_unique<std::vector<>>();
      this.bean = bean;
      this.acc = acc;
      this.context = UnmarshallingContext.getInstance();
      this.location = std::make_shared<Snapshot>(this.context.getLocator());
      this.context.addPatcher(this);
   }

    void add(const std::string& item) {
      this.idrefs.push_back(item);
   }

    void run() {
      try {
    void* pack = IDREFS.access$100(this.this$0).startPacking(this.bean, this.acc);

         for (std::string id : this.idrefs) {
    Callable callable = this.context.getObjectFromId(id, IDREFS.access$200(this.this$0));

    void* t;
            try {
               t = callable != nullptr ? callable.call() : nullptr;
            } catch (SAXException var7) {
    throw var7;
            } catch (Exception var8) {
               throw SAXException2(var8);
            }

            if (t == nullptr) {
               this.context.errorUnresolvedIDREF(this.bean, id, this.location);
            } else {
               TODO.prototype();
               IDREFS.access$100(this.this$0).addToPack(pack, t);
            }
         }

         IDREFS.access$100(this.this$0).endPacking(pack, this.bean, this.acc);
      } catch (AccessorException var9) {
         this.context.handleError(var9);
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
