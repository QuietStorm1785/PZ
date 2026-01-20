#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "javax/xml/bind/JAXBException.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class AdaptedLister {
public:
   private const ListIterator<InMemItemT> core;
    const XMLSerializer serializer;

   public AdaptedLister$ListIteratorImpl(ListIterator<InMemItemT> var1, XMLSerializer core, XMLSerializer serializer) {
      this.this$0 = var1;
      this.core = core;
      this.serializer = serializer;
   }

    bool hasNext() {
      return this.core.hasNext();
   }

    OnWireItemT next() {
    InMemItemT next = (InMemItemT)this.core.next();

      try {
         return (OnWireItemT)AdaptedLister.access$000(this.this$0).marshal(next);
      } catch (Exception var3) {
         this.serializer.reportError(nullptr, var3);
    return nullptr;
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
