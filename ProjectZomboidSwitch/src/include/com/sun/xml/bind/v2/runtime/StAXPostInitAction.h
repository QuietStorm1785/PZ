#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/namespace/NamespaceContext.h"
#include "javax/xml/stream/XMLEventWriter.h"
#include "javax/xml/stream/XMLStreamWriter.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class StAXPostInitAction {
public:
    const XMLStreamWriter xsw;
    const XMLEventWriter xew;
    const NamespaceContext nsc;
    const XMLSerializer serializer;

   StAXPostInitAction(XMLStreamWriter xsw, XMLSerializer serializer) {
      this.xsw = xsw;
      this.xew = nullptr;
      this.nsc = nullptr;
      this.serializer = serializer;
   }

   StAXPostInitAction(XMLEventWriter xew, XMLSerializer serializer) {
      this.xsw = nullptr;
      this.xew = xew;
      this.nsc = nullptr;
      this.serializer = serializer;
   }

   StAXPostInitAction(NamespaceContext nsc, XMLSerializer serializer) {
      this.xsw = nullptr;
      this.xew = nullptr;
      this.nsc = nsc;
      this.serializer = serializer;
   }

    void run() {
    NamespaceContext ns = this.nsc;
      if (this.xsw != nullptr) {
         ns = this.xsw.getNamespaceContext();
      }

      if (this.xew != nullptr) {
         ns = this.xew.getNamespaceContext();
      }

      if (ns != nullptr) {
         for (std::string nsUri : this.serializer.grammar.nameList.namespaceURIs) {
    std::string p = ns.getPrefix(nsUri);
            if (p != nullptr) {
               this.serializer.addInscopeBinding(nsUri, p);
            }
         }
      }
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
