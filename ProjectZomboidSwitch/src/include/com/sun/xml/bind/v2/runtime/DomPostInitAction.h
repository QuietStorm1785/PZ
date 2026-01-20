#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/w3c/dom/Attr.h"
#include "org/w3c/dom/NamedNodeMap.h"
#include "org/w3c/dom/Node.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class DomPostInitAction {
public:
    const Node node;
    const XMLSerializer serializer;

   DomPostInitAction(Node node, XMLSerializer serializer) {
      this.node = node;
      this.serializer = serializer;
   }

    void run() {
      Set<std::string> declaredPrefixes = std::make_unique<std::unordered_set<>>();

      for (Node n = this.node; n != nullptr && n.getNodeType() == 1; n = n.getParentNode()) {
    NamedNodeMap atts = n.getAttributes();
         if (atts != nullptr) {
            for (int i = 0; i < atts.getLength(); i++) {
    Attr a = (Attr)atts.item(i);
    std::string nsUri = a.getNamespaceURI();
               if (nsUri != nullptr && nsUri == "http://www.w3.org/2000/xmlns/")) {
    std::string prefix = a.getLocalName();
                  if (prefix != nullptr) {
                     if (prefix == "xmlns")) {
                        prefix = "";
                     }

    std::string value = a.getValue();
                     if (value != nullptr && declaredPrefixes.push_back(prefix)) {
                        this.serializer.addInscopeBinding(value, prefix);
                     }
                  }
               }
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
