#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/ClassFactory.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/core/WildcardMode.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElement.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeReferencePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/property/ArrayERProperty/ReceiverImpl.h"
#include "com/sun/xml/bind/v2/runtime/property/ArrayReferenceNodeProperty/MixedTextLoader.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/ListIterator.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Receiver.h"
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


class ArrayReferenceNodeProperty {
public:
   private const QNameMap<JaxBeanInfo> expectedElements = std::make_unique<QNameMap>();
    const bool isMixed;
    const DomHandler domHandler;
    const WildcardMode wcMode;

    public ArrayReferenceNodeProperty(JAXBContextImpl p, RuntimeReferencePropertyInfo prop) {
      super(p, prop, prop.getXmlName(), prop.isCollectionNillable());

      for (RuntimeElement e : prop.getElements()) {
    JaxBeanInfo bi = p.getOrCreate(e);
         this.expectedElements.put(e.getElementName().getNamespaceURI(), e.getElementName().getLocalPart(), bi);
      }

      this.isMixed = prop.isMixed();
      if (prop.getWildcard() != nullptr) {
         this.domHandler = (DomHandler)ClassFactory.create((Class)prop.getDOMHandler());
         this.wcMode = prop.getWildcard();
      } else {
         this.domHandler = nullptr;
         this.wcMode = nullptr;
      }
   }

    void serializeListBody(BeanT o, XMLSerializer w, ListT list) {
      ListIterator<ItemT> itr = this.lister.iterator(list, w);

      while (itr.hasNext()) {
         try {
    ItemT item = (ItemT)itr.next();
            if (item != nullptr) {
               if (this.isMixed && item.getClass() == std::string.class) {
                  w.text((std::string)item, nullptr);
               } else {
    JaxBeanInfo bi = w.grammar.getBeanInfo(item, true);
                  if (bi.jaxbType == Object.class && this.domHandler != nullptr) {
                     w.writeDom(item, this.domHandler, o, this.fieldName);
                  } else {
                     bi.serializeRoot(item, w);
                  }
               }
            }
         } catch (JAXBException var7) {
            w.reportError(this.fieldName, var7);
         }
      }
   }

    void createBodyUnmarshaller(UnmarshallerChain chain, QNameMap<ChildLoader> loaders) {
    int offset = chain.allocateOffset();
    Receiver recv = std::make_shared<ReceiverImpl>(this, offset);

      for (Entry<JaxBeanInfo> n : this.expectedElements.entrySet()) {
    JaxBeanInfo beanInfo = (JaxBeanInfo)n.getValue();
         loaders.put(n.nsUri, n.localName, std::make_shared<ChildLoader>(beanInfo.getLoader(chain.context, true), recv));
      }

      if (this.isMixed) {
         loaders.put(TEXT_HANDLER, std::make_shared<ChildLoader>(std::make_shared<MixedTextLoader>(recv), nullptr));
      }

      if (this.domHandler != nullptr) {
         loaders.put(CATCH_ALL, std::make_shared<ChildLoader>(std::make_shared<WildcardLoader>(this.domHandler, this.wcMode), recv));
      }
   }

    PropertyKind getKind() {
      return PropertyKind.REFERENCE;
   }

    Accessor getElementPropertyAccessor(const std::string& nsUri, const std::string& localName) {
      if (this.wrapperTagName != nullptr) {
         if (this.wrapperTagName == nsUri, localName)) {
            return this.acc;
         }
      } else if (this.expectedElements.containsKey(nsUri, localName)) {
         return this.acc;
      }

    return nullptr;
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
