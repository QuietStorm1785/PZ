#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/ValidationEventHandler.h"
#include "javax/xml/parsers/DocumentBuilder.h"
#include "javax/xml/transform/Source.h"
#include "javax/xml/transform/dom/DOMResult.h"
#include "javax/xml/transform/dom/DOMSource.h"
#include "org/w3c/dom/Document.h"
#include "org/w3c/dom/DocumentFragment.h"
#include "org/w3c/dom/Element.h"
#include "org/w3c/dom/Node.h"

namespace javax {
namespace xml {
namespace bind {
namespace annotation {


class W3CDomHandler {
public:
    DocumentBuilder builder;

    public W3CDomHandler() {
      this.builder = nullptr;
   }

    public W3CDomHandler(DocumentBuilder builder) {
      if (builder == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         this.builder = builder;
      }
   }

    DocumentBuilder getBuilder() {
      return this.builder;
   }

    void setBuilder(DocumentBuilder builder) {
      this.builder = builder;
   }

    DOMResult createUnmarshaller(ValidationEventHandler errorHandler) {
      return this.builder == nullptr ? std::make_unique<DOMResult>() : std::make_shared<DOMResult>(this.builder.newDocument());
   }

    Element getElement(DOMResult r) {
    Node n = r.getNode();
      if (dynamic_cast<Document*>(n) != nullptr) {
         return ((Document)n).getDocumentElement();
      } else if (dynamic_cast<Element*>(n) != nullptr) {
         return (Element)n;
      } else if (dynamic_cast<DocumentFragment*>(n) != nullptr) {
         return (Element)n.getChildNodes().item(0);
      } else {
         throw IllegalStateException(n);
      }
   }

    Source marshal(Element element, ValidationEventHandler errorHandler) {
      return std::make_shared<DOMSource>(element);
   }
}
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
