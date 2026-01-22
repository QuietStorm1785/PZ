#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class Scope {
public:
    const UnmarshallingContext context;
    BeanT bean;
   private Accessor<BeanT, PropT> acc;
    PackT pack;
   private Lister<BeanT, PropT, ItemT, PackT> lister;

   Scope(UnmarshallingContext context) {
      this.context = context;
   }

    bool hasStarted() {
      return this.bean != nullptr;
   }

    void reset() {
      if (this.bean == nullptr) {
         assert this.clean();
      } else {
         this.bean = nullptr;
         this.acc = nullptr;
         this.pack = nullptr;
         this.lister = nullptr;
      }
   }

    void finish() {
      if (this.hasStarted()) {
         this.lister.endPacking(this.pack, this.bean, this.acc);
         this.reset();
      }

      assert this.clean();
   }

    bool clean() {
      return this.bean == nullptr && this.acc == nullptr && this.pack == nullptr && this.lister == nullptr;
   }

    void add(PropT> acc, PackT> lister, ItemT value) {
      try {
         if (!this.hasStarted()) {
            this.bean = (BeanT)this.context.getCurrentState().getTarget();
            this.acc = acc;
            this.lister = lister;
            this.pack = (PackT)lister.startPacking(this.bean, acc);
         }

         lister.addToPack(this.pack, value);
      } catch (AccessorException var5) {
         Loader.handleGenericException(var5, true);
         this.lister = Lister.getErrorInstance();
         this.acc = Accessor.getErrorInstance();
      }
   }

    void start(PropT> acc, PackT> lister) {
      try {
         if (!this.hasStarted()) {
            this.bean = (BeanT)this.context.getCurrentState().getTarget();
            this.acc = acc;
            this.lister = lister;
            this.pack = (PackT)lister.startPacking(this.bean, acc);
         }
      } catch (AccessorException var4) {
         Loader.handleGenericException(var4, true);
         this.lister = Lister.getErrorInstance();
         this.acc = Accessor.getErrorInstance();
      }
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
