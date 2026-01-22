#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "javax/xml/transform/sax/TransformerHandler.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class DomLoader {
public:
    TransformerHandler handler;
    const ResultT result;
    int depth;

   public DomLoader$State(DomLoader var1, UnmarshallingContext context) throws SAXException {
      this.this$0 = var1;
      this.handler = nullptr;
      this.depth = 1;
      this.handler = JAXBContextImpl.createTransformerHandler(context.getJAXBContext().disableSecurityProcessing);
      this.result = (ResultT)DomLoader.access$000(var1).createUnmarshaller(context);
      this.handler.setResult(this.result);

      try {
         this.handler.setDocumentLocator(context.getLocator());
         this.handler.startDocument();
         this.declarePrefixes(context, context.getAllDeclaredPrefixes());
      } catch (SAXException var4) {
         context.handleError(var4);
    throw var4;
      }
   }

    void* getElement() {
      return DomLoader.access$000(this.this$0).getElement(this.result);
   }

    void declarePrefixes(UnmarshallingContext context, std::string[] prefixes) {
      for (int i = prefixes.length - 1; i >= 0; i--) {
    std::string nsUri = context.getNamespaceURI(prefixes[i]);
         if (nsUri == nullptr) {
            throw IllegalStateException("prefix '" + prefixes[i] + "' isn't bound");
         }

         this.handler.startPrefixMapping(prefixes[i], nsUri);
      }
   }

    void undeclarePrefixes(std::string[] prefixes) {
      for (int i = prefixes.length - 1; i >= 0; i--) {
         this.handler.endPrefixMapping(prefixes[i]);
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
