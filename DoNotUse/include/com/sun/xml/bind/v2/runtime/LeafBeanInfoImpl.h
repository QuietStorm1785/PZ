#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeLeafInfo.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/TextLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XsiTypeLoader.h"
#include "javax/xml/bind/helpers/ValidationEventImpl.h"
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


class LeafBeanInfoImpl {
public:
    const Loader loader;
    const Loader loaderWithSubst;
   private const Transducer<BeanT> xducer;
    const Name tagName;

    public LeafBeanInfoImpl(JAXBContextImpl grammar, RuntimeLeafInfo li) {
      super(grammar, li, li.getClazz(), li.getTypeNames(), li.isElement(), true, false);
      this.xducer = li.getTransducer();
      this.loader = std::make_shared<TextLoader>(this.xducer);
      this.loaderWithSubst = std::make_shared<XsiTypeLoader>(this);
      if (this.isElement()) {
         this.tagName = grammar.nameBuilder.createElementName(li.getElementName());
      } else {
         this.tagName = nullptr;
      }
   }

    QName getTypeName(BeanT instance) {
    QName tn = this.xducer.getTypeName(instance);
      return tn != nullptr ? tn : super.getTypeName(instance);
   }

    std::string getElementNamespaceURI(BeanT t) {
      return this.tagName.nsUri;
   }

    std::string getElementLocalName(BeanT t) {
      return this.tagName.localName;
   }

    BeanT createInstance(UnmarshallingContext context) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool reset(BeanT bean, UnmarshallingContext context) {
    return false;
   }

    std::string getId(BeanT bean, XMLSerializer target) {
    return nullptr;
   }

    void serializeBody(BeanT bean, XMLSerializer w) {
      try {
         this.xducer.writeText(w, bean, nullptr);
      } catch (AccessorException var4) {
         w.reportError(nullptr, var4);
      }
   }

    void serializeAttributes(BeanT bean, XMLSerializer target) {
   }

    void serializeRoot(BeanT bean, XMLSerializer target) {
      if (this.tagName == nullptr) {
         target.reportError(std::make_shared<ValidationEventImpl>(1, Messages.UNABLE_TO_MARSHAL_NON_ELEMENT.format(new Object[]{bean.getClass().getName()}), nullptr, nullptr));
      } else {
         target.startElement(this.tagName, bean);
         target.childAsSoleContent(bean, nullptr);
         target.endElement();
      }
   }

    void serializeURIs(BeanT bean, XMLSerializer target) {
      if (this.xducer.useNamespace()) {
         try {
            this.xducer.declareNamespace(bean, target);
         } catch (AccessorException var4) {
            target.reportError(nullptr, var4);
         }
      }
   }

    Loader getLoader(JAXBContextImpl context, bool typeSubstitutionCapable) {
      return typeSubstitutionCapable ? this.loaderWithSubst : this.loader;
   }

   public Transducer<BeanT> getTransducer() {
      return this.xducer;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
