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


class Lister {
public:
    const ListIterator i;
    const XMLSerializer context;
    void* last;

   private Lister$IDREFSIterator(ListIterator i, XMLSerializer context) {
      this.i = i;
      this.context = context;
   }

    bool hasNext() {
      return this.i.hasNext();
   }

    void* last() {
      return this.last;
   }

    std::string next() {
      this.last = this.i.next();
    std::string id = this.context.grammar.getBeanInfo(this.last, true).getId(this.last, this.context);
      if (id == nullptr) {
         this.context.errorMissingId(this.last);
      }

    return id;
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
