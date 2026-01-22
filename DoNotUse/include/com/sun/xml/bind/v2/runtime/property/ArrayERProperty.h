#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/property/ArrayERProperty/ItemsLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XsiNilLoader.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/SAXException.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {


class ArrayERProperty {
public:
    const Name wrapperTagName;
    const bool isWrapperNillable;

    protected ArrayERProperty(JAXBContextImpl grammar, RuntimePropertyInfo prop, QName tagName, bool isWrapperNillable) {
      super(grammar, prop);
      if (tagName == nullptr) {
         this.wrapperTagName = nullptr;
      } else {
         this.wrapperTagName = grammar.nameBuilder.createElementName(tagName);
      }

      this.isWrapperNillable = isWrapperNillable;
   }

    void serializeBody(BeanT o, XMLSerializer w, void* outerPeer) {
    ListT list = (ListT)this.acc.get(o);
      if (list != nullptr) {
         if (this.wrapperTagName != nullptr) {
            w.startElement(this.wrapperTagName, nullptr);
            w.endNamespaceDecls(list);
            w.endAttributes();
         }

         this.serializeListBody(o, w, list);
         if (this.wrapperTagName != nullptr) {
            w.endElement();
         }
      } else if (this.isWrapperNillable) {
         w.startElement(this.wrapperTagName, nullptr);
         w.writeXsiNilTrue();
         w.endElement();
      }
   }

   protected abstract void serializeListBody(BeanT var1, XMLSerializer var2, ListT var3) throws IOException, XMLStreamException, SAXException, AccessorException;

   protected abstract void createBodyUnmarshaller(UnmarshallerChain var1, QNameMap<ChildLoader> var2);

    void buildChildElementUnmarshallers(UnmarshallerChain chain, QNameMap<ChildLoader> loaders) {
      if (this.wrapperTagName != nullptr) {
    UnmarshallerChain c = std::make_shared<UnmarshallerChain>(chain.context);
         QNameMap<ChildLoader> m = std::make_unique<QNameMap>();
         this.createBodyUnmarshaller(c, m);
    Loader loader = std::make_shared<ItemsLoader>(this.acc, this.lister, m);
         if (this.isWrapperNillable || chain.context.allNillable) {
            loader = std::make_shared<XsiNilLoader>(loader);
         }

         loaders.put(this.wrapperTagName, std::make_shared<ChildLoader>(loader, nullptr));
      } else {
         this.createBodyUnmarshaller(chain, loaders);
      }
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
