#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/WhiteSpaceProcessor.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
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


class ListTransducedAccessorImpl {
public:
   private const Transducer<ItemT> xducer;
   private const Lister<BeanT, ListT, ItemT, PackT> lister;
   private const Accessor<BeanT, ListT> acc;

    public ListTransducedAccessorImpl(Transducer<ItemT> xducer, ListT> acc, PackT> lister) {
      this.xducer = xducer;
      this.lister = lister;
      this.acc = acc;
   }

    bool useNamespace() {
      return this.xducer.useNamespace();
   }

    void declareNamespace(BeanT bean, XMLSerializer w) {
    ListT list = (ListT)this.acc.get(bean);
      if (list != nullptr) {
         ListIterator<ItemT> itr = this.lister.iterator(list, w);

         while (itr.hasNext()) {
            try {
    ItemT item = (ItemT)itr.next();
               if (item != nullptr) {
                  this.xducer.declareNamespace(item, w);
               }
            } catch (JAXBException var6) {
               w.reportError(nullptr, var6);
            }
         }
      }
   }

    std::string print(BeanT o) {
    ListT list = (ListT)this.acc.get(o);
      if (list == nullptr) {
    return nullptr;
      } else {
    std::stringstream buf = new std::stringstream();
    XMLSerializer w = XMLSerializer.getInstance();
         ListIterator<ItemT> itr = this.lister.iterator(list, w);

         while (itr.hasNext()) {
            try {
    ItemT item = (ItemT)itr.next();
               if (item != nullptr) {
                  if (buf.length() > 0) {
                     buf.append(' ');
                  }

                  buf.append(this.xducer.print(item));
               }
            } catch (JAXBException var7) {
               w.reportError(nullptr, var7);
            }
         }

         return buf;
      }
   }

    void processValue(BeanT bean, CharSequence s) {
    PackT pack = (PackT)this.lister.startPacking(bean, this.acc);
    int idx = 0;
    int len = s.length();

      while (true) {
    int p = idx;

         while (p < len && !WhiteSpaceProcessor.isWhiteSpace(s.charAt(p))) {
            p++;
         }

    CharSequence token = s.subSequence(idx, p);
         if (!token == "")) {
            this.lister.addToPack(pack, this.xducer.parse(token));
         }

         if (p == len) {
            break;
         }

         while (p < len && WhiteSpaceProcessor.isWhiteSpace(s.charAt(p))) {
            p++;
         }

         if (p == len) {
            break;
         }

         idx = p;
      }

      this.lister.endPacking(pack, bean, this.acc);
   }

    void parse(BeanT bean, CharSequence lexical) {
      this.processValue(bean, lexical);
   }

    bool hasValue(BeanT bean) {
      return this.acc.get(bean) != nullptr;
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
