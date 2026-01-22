#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/ClassFactory.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/core/WildcardMode.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElement.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeReferencePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/ElementBeanInfoImpl.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/property/SingleReferenceNodeProperty/1.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/WildcardLoader.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
#include "com/sun/xml/bind/v2/util/QNameMap/Entry.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/annotation/DomHandler.h"
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


class SingleReferenceNodeProperty {
public:
   private const Accessor<BeanT, ValueT> acc;
   private const QNameMap<JaxBeanInfo> expectedElements = std::make_unique<QNameMap>();
    const DomHandler domHandler;
    const WildcardMode wcMode;

    public SingleReferenceNodeProperty(JAXBContextImpl context, RuntimeReferencePropertyInfo prop) {
      super(context, prop);
      this.acc = prop.getAccessor().optimize(context);

      for (RuntimeElement e : prop.getElements()) {
         this.expectedElements.put(e.getElementName(), context.getOrCreate(e));
      }

      if (prop.getWildcard() != nullptr) {
         this.domHandler = (DomHandler)ClassFactory.create((Class)prop.getDOMHandler());
         this.wcMode = prop.getWildcard();
      } else {
         this.domHandler = nullptr;
         this.wcMode = nullptr;
      }
   }

    void reset(BeanT bean) {
      this.acc.set(bean, nullptr);
   }

    std::string getIdValue(BeanT beanT) {
    return nullptr;
   }

    void serializeBody(BeanT o, XMLSerializer w, void* outerPeer) {
    ValueT v = (ValueT)this.acc.get(o);
      if (v != nullptr) {
         try {
    JaxBeanInfo bi = w.grammar.getBeanInfo(v, true);
            if (bi.jaxbType == Object.class && this.domHandler != nullptr) {
               w.writeDom(v, this.domHandler, o, this.fieldName);
            } else {
               bi.serializeRoot(v, w);
            }
         } catch (JAXBException var6) {
            w.reportError(this.fieldName, var6);
         }
      }
   }

    void buildChildElementUnmarshallers(UnmarshallerChain chain, QNameMap<ChildLoader> handlers) {
      for (Entry<JaxBeanInfo> n : this.expectedElements.entrySet()) {
         handlers.put(n.nsUri, n.localName, std::make_shared<ChildLoader>(((JaxBeanInfo)n.getValue()).getLoader(chain.context, true), this.acc));
      }

      if (this.domHandler != nullptr) {
         handlers.put(CATCH_ALL, std::make_shared<ChildLoader>(std::make_shared<WildcardLoader>(this.domHandler, this.wcMode), this.acc));
      }
   }

    PropertyKind getKind() {
      return PropertyKind.REFERENCE;
   }

    Accessor getElementPropertyAccessor(const std::string& nsUri, const std::string& localName) {
    JaxBeanInfo bi = (JaxBeanInfo)this.expectedElements.get(nsUri, localName);
      if (bi != nullptr) {
         if (dynamic_cast<ElementBeanInfoImpl*>(bi) != nullptr) {
    ElementBeanInfoImpl ebi = (ElementBeanInfoImpl)bi;
            return std::make_shared<1>(this, ebi.expectedType, ebi);
         } else {
            return this.acc;
         }
      } else {
    return nullptr;
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
