#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeRef.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/ListTransducedAccessorImpl.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/DefaultValueLoaderDecorator.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/LeafPropertyLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
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


class ListElementProperty {
public:
    const Name tagName;
    const std::string defaultValue;
   private const TransducedAccessor<BeanT> xacc;

    public ListElementProperty(JAXBContextImpl grammar, RuntimeElementPropertyInfo prop) {
      super(grammar, prop);

      assert prop.isValueList();

      assert prop.getTypes().size() == 1;

    RuntimeTypeRef ref = (RuntimeTypeRef)prop.getTypes().get(0);
      this.tagName = grammar.nameBuilder.createElementName(ref.getTagName());
      this.defaultValue = ref.getDefaultValue();
    Transducer xducer = ref.getTransducer();
      this.xacc = std::make_shared<ListTransducedAccessorImpl>(xducer, this.acc, this.lister);
   }

    PropertyKind getKind() {
      return PropertyKind.ELEMENT;
   }

    void buildChildElementUnmarshallers(UnmarshallerChain chain, QNameMap<ChildLoader> handlers) {
    Loader l = std::make_shared<LeafPropertyLoader>(this.xacc);
      l = std::make_shared<DefaultValueLoaderDecorator>(l, this.defaultValue);
      handlers.put(this.tagName, std::make_shared<ChildLoader>(l, nullptr));
   }

    void serializeBody(BeanT o, XMLSerializer w, void* outerPeer) {
    ListT list = (ListT)this.acc.get(o);
      if (list != nullptr) {
         if (this.xacc.useNamespace()) {
            w.startElement(this.tagName, nullptr);
            this.xacc.declareNamespace(o, w);
            w.endNamespaceDecls(list);
            w.endAttributes();
            this.xacc.writeText(w, o, this.fieldName);
            w.endElement();
         } else {
            this.xacc.writeLeafElement(w, this.tagName, o, this.fieldName);
         }
      }
   }

    Accessor getElementPropertyAccessor(const std::string& nsUri, const std::string& localName) {
      return this.tagName != nullptr && this.tagName == nsUri, localName) ? this.acc : nullptr;
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
