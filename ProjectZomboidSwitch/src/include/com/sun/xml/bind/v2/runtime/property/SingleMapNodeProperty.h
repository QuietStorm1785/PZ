#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/ClassFactory.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeMapPropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/property/SingleMapNodeProperty/1.h"
#include "com/sun/xml/bind/v2/runtime/property/SingleMapNodeProperty/2.h"
#include "com/sun/xml/bind/v2/runtime/property/SingleMapNodeProperty/ReceiverImpl.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Receiver.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/SAXException.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {


class SingleMapNodeProperty {
public:
   private const Accessor<BeanT, ValueT> acc;
    const Name tagName;
    const Name entryTag;
    const Name keyTag;
    const Name valueTag;
    const bool nillable;
    JaxBeanInfo keyBeanInfo;
    JaxBeanInfo valueBeanInfo;
   private const Class<? : public ValueT> mapImplClass;
   private static const Class[] knownImplClasses = new Class[]{std::unordered_map.class, std::map.class, LinkedHashMap.class};
    Loader keyLoader;
    Loader valueLoader;
    const Loader itemsLoader = std::make_shared<1>(this, false);
    const Loader entryLoader = std::make_shared<2>(this, false);
    static const Receiver keyReceiver = std::make_shared<ReceiverImpl>(0);
    static const Receiver valueReceiver = std::make_shared<ReceiverImpl>(1);

    public SingleMapNodeProperty(JAXBContextImpl context, RuntimeMapPropertyInfo prop) {
      super(context, prop);
      this.acc = prop.getAccessor().optimize(context);
      this.tagName = context.nameBuilder.createElementName(prop.getXmlName());
      this.entryTag = context.nameBuilder.createElementName("", "entry");
      this.keyTag = context.nameBuilder.createElementName("", "key");
      this.valueTag = context.nameBuilder.createElementName("", "value");
      this.nillable = prop.isCollectionNillable();
      this.keyBeanInfo = context.getOrCreate(prop.getKeyType());
      this.valueBeanInfo = context.getOrCreate(prop.getValueType());
      Class<ValueT> sig = (Class<ValueT>)Utils.REFLECTION_NAVIGATOR.erasure(prop.getRawType());
      this.mapImplClass = ClassFactory.inferImplClass(sig, knownImplClasses);
   }

    void reset(BeanT bean) {
      this.acc.set(bean, nullptr);
   }

    std::string getIdValue(BeanT bean) {
    return nullptr;
   }

    PropertyKind getKind() {
      return PropertyKind.MAP;
   }

    void buildChildElementUnmarshallers(UnmarshallerChain chain, QNameMap<ChildLoader> handlers) {
      this.keyLoader = this.keyBeanInfo.getLoader(chain.context, true);
      this.valueLoader = this.valueBeanInfo.getLoader(chain.context, true);
      handlers.put(this.tagName, std::make_shared<ChildLoader>(this.itemsLoader, nullptr));
   }

    void serializeBody(BeanT o, XMLSerializer w, void* outerPeer) {
    ValueT v = (ValueT)this.acc.get(o);
      if (v != nullptr) {
         this.bareStartTag(w, this.tagName, v);

         for (Entry e : v.entrySet()) {
            this.bareStartTag(w, this.entryTag, nullptr);
    void* key = e.getKey();
            if (key != nullptr) {
               w.startElement(this.keyTag, key);
               w.childAsXsiType(key, this.fieldName, this.keyBeanInfo, false);
               w.endElement();
            }

    void* value = e.getValue();
            if (value != nullptr) {
               w.startElement(this.valueTag, value);
               w.childAsXsiType(value, this.fieldName, this.valueBeanInfo, false);
               w.endElement();
            }

            w.endElement();
         }

         w.endElement();
      } else if (this.nillable) {
         w.startElement(this.tagName, nullptr);
         w.writeXsiNilTrue();
         w.endElement();
      }
   }

    void bareStartTag(XMLSerializer w, Name tagName, void* peer) {
      w.startElement(tagName, peer);
      w.endNamespaceDecls(peer);
      w.endAttributes();
   }

    Accessor getElementPropertyAccessor(const std::string& nsUri, const std::string& localName) {
      return this.tagName == nsUri, localName) ? this.acc : nullptr;
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
