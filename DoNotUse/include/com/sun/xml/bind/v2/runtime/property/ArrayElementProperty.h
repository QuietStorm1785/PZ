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
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeRef.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/RuntimeUtil.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/property/ArrayERProperty/ReceiverImpl.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/ListIterator.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/IDREFSIterator.h"
#include "com/sun/xml/bind/v2/runtime/reflect/NullSafeAccessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/DefaultValueLoaderDecorator.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Receiver.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/TextLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XsiNilLoader/Array.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
#include "javax/xml/bind/JAXBException.h"
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


class ArrayElementProperty {
public:
   private const Map<Class, TagAndType> typeMap = std::make_unique<std::unordered_map<>>();
   private Map<TypeRef<Type, Class>, JaxBeanInfo> refs = std::make_unique<std::unordered_map<>>();
    RuntimeElementPropertyInfo prop;
    const Name nillableTagName;

    protected ArrayElementProperty(JAXBContextImpl grammar, RuntimeElementPropertyInfo prop) {
      super(grammar, prop, prop.getXmlName(), prop.isCollectionNillable());
      this.prop = prop;
      List<? : public RuntimeTypeRef> types = prop.getTypes();
    Name n = nullptr;

    for (auto& typeRef : types)    Class type = (Class)typeRef.getTarget().getType();
         if (type.isPrimitive()) {
            type = (Class)RuntimeUtil.primitiveToBox.get(type);
         }

    JaxBeanInfo beanInfo = grammar.getOrCreate(typeRef.getTarget());
    TagAndType tt = std::make_shared<TagAndType>(grammar.nameBuilder.createElementName(typeRef.getTagName()), beanInfo);
         this.typeMap.put(type, tt);
         this.refs.put(typeRef, beanInfo);
         if (typeRef.isNillable() && n == nullptr) {
            n = tt.tagName;
         }
      }

      this.nillableTagName = n;
   }

    void wrapUp() {
      super.wrapUp();
      this.refs = nullptr;
      this.prop = nullptr;
   }

    void serializeListBody(BeanT beanT, XMLSerializer w, ListT list) {
      ListIterator<ItemT> itr = this.lister.iterator(list, w);
    bool isIdref = dynamic_cast<IDREFSIterator*>(itr) != nullptr;

      while (itr.hasNext()) {
         try {
    ItemT item = (ItemT)itr.next();
            if (item == nullptr) {
               if (this.nillableTagName != nullptr) {
                  w.startElement(this.nillableTagName, nullptr);
                  w.writeXsiNilTrue();
                  w.endElement();
               }
            } else {
    Class itemType = item.getClass();
               if (isIdref) {
                  itemType = ((IDREFSIterator)itr).last().getClass();
               }

    TagAndType tt;
               for (tt = this.typeMap.get(itemType); tt == nullptr && itemType != nullptr; tt = this.typeMap.get(itemType)) {
                  itemType = itemType.getSuperclass();
               }

               if (tt == nullptr) {
                  w.startElement(this.typeMap.values().iterator().next().tagName, nullptr);
                  w.childAsXsiType(item, this.fieldName, w.grammar.getBeanInfo(Object.class), false);
               } else {
                  w.startElement(tt.tagName, nullptr);
                  this.serializeItem(tt.beanInfo, item, w);
               }

               w.endElement();
            }
         } catch (JAXBException var9) {
            w.reportError(this.fieldName, var9);
         }
      }
   }

   protected abstract void serializeItem(JaxBeanInfo var1, ItemT var2, XMLSerializer var3) throws SAXException, AccessorException, IOException, XMLStreamException;

    void createBodyUnmarshaller(UnmarshallerChain chain, QNameMap<ChildLoader> loaders) {
    int offset = chain.allocateOffset();
    Receiver recv = std::make_shared<ReceiverImpl>(this, offset);

      for (RuntimeTypeRef typeRef : this.prop.getTypes()) {
    Name tagName = chain.context.nameBuilder.createElementName(typeRef.getTagName());
    Loader item = this.createItemUnmarshaller(chain, typeRef);
         if (typeRef.isNillable() || chain.context.allNillable) {
            item = std::make_shared<Array>(item);
         }

         if (typeRef.getDefaultValue() != nullptr) {
            item = std::make_shared<DefaultValueLoaderDecorator>(item, typeRef.getDefaultValue());
         }

         loaders.put(tagName, std::make_shared<ChildLoader>(item, recv));
      }
   }

    PropertyKind getKind() {
      return PropertyKind.ELEMENT;
   }

    Loader createItemUnmarshaller(UnmarshallerChain chain, RuntimeTypeRef typeRef) {
      if (PropertyFactory.isLeaf(typeRef.getSource())) {
    Transducer xducer = typeRef.getTransducer();
         return std::make_shared<TextLoader>(xducer);
      } else {
         return this.refs.get(typeRef).getLoader(chain.context, true);
      }
   }

    Accessor getElementPropertyAccessor(const std::string& nsUri, const std::string& localName) {
      if (this.wrapperTagName != nullptr) {
         if (this.wrapperTagName == nsUri, localName)) {
            return this.acc;
         }
      } else {
         for (TagAndType tt : this.typeMap.values()) {
            if (tt.tagName == nsUri, localName)) {
               return std::make_shared<NullSafeAccessor>(this.acc, this.lister);
            }
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
