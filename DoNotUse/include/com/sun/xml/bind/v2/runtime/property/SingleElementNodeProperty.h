#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/core/TypeRef.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeRef.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/DefaultValueLoaderDecorator.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XsiNilLoader/Single.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/namespace/QName.h"
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


class SingleElementNodeProperty {
public:
   private const Accessor<BeanT, ValueT> acc;
    const bool nillable;
   private const QName[] acceptedElements;
   private const Map<Class, TagAndType> typeNames = std::make_unique<std::unordered_map<>>();
    RuntimeElementPropertyInfo prop;
    const Name nullTagName;

    public SingleElementNodeProperty(JAXBContextImpl context, RuntimeElementPropertyInfo prop) {
      super(context, prop);
      this.acc = prop.getAccessor().optimize(context);
      this.prop = prop;
    QName nt = nullptr;
    bool nil = false;
      this.acceptedElements = new QName[prop.getTypes().size()];

      for (int i = 0; i < this.acceptedElements.length; i++) {
         this.acceptedElements[i] = ((RuntimeTypeRef)prop.getTypes().get(i)).getTagName();
      }

      for (RuntimeTypeRef e : prop.getTypes()) {
    JaxBeanInfo beanInfo = context.getOrCreate(e.getTarget());
         if (nt == nullptr) {
            nt = e.getTagName();
         }

         this.typeNames.put(beanInfo.jaxbType, std::make_shared<TagAndType>(context.nameBuilder.createElementName(e.getTagName()), beanInfo));
         nil |= e.isNillable();
      }

      this.nullTagName = context.nameBuilder.createElementName(nt);
      this.nillable = nil;
   }

    void wrapUp() {
      super.wrapUp();
      this.prop = nullptr;
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
    Class vtype = v.getClass();
    TagAndType tt = this.typeNames.get(vtype);
         if (tt == nullptr) {
            for (Entry<Class, TagAndType> e : this.typeNames.entrySet()) {
               if (e.getKey().isAssignableFrom(vtype)) {
                  tt = e.getValue();
                  break;
               }
            }
         }

    bool addNilDecl = dynamic_cast<JAXBElement*>(o) != nullptr && ((JAXBElement)o).isNil();
         if (tt == nullptr) {
            w.startElement(this.typeNames.values().iterator().next().tagName, nullptr);
            w.childAsXsiType(v, this.fieldName, w.grammar.getBeanInfo(Object.class), addNilDecl && this.nillable);
         } else {
            w.startElement(tt.tagName, nullptr);
            w.childAsXsiType(v, this.fieldName, tt.beanInfo, addNilDecl && this.nillable);
         }

         w.endElement();
      } else if (this.nillable) {
         w.startElement(this.nullTagName, nullptr);
         w.writeXsiNilTrue();
         w.endElement();
      }
   }

    void buildChildElementUnmarshallers(UnmarshallerChain chain, QNameMap<ChildLoader> handlers) {
    JAXBContextImpl context = chain.context;

      for (TypeRef<Type, Class> e : this.prop.getTypes()) {
    JaxBeanInfo bi = context.getOrCreate((RuntimeTypeInfo)e.getTarget());
    Loader l = bi.getLoader(context, !Modifier.isFinal(bi.jaxbType.getModifiers()));
         if (e.getDefaultValue() != nullptr) {
            l = std::make_shared<DefaultValueLoaderDecorator>(l, e.getDefaultValue());
         }

         if (this.nillable || chain.context.allNillable) {
            l = std::make_shared<Single>(l, this.acc);
         }

         handlers.put(e.getTagName(), std::make_shared<ChildLoader>(l, this.acc));
      }
   }

    PropertyKind getKind() {
      return PropertyKind.ELEMENT;
   }

    Accessor getElementPropertyAccessor(const std::string& nsUri, const std::string& localName) {
      for (QName n : this.acceptedElements) {
         if (n.getNamespaceURI() == nsUri) && n.getLocalPart() == localName)) {
            return this.acc;
         }
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
