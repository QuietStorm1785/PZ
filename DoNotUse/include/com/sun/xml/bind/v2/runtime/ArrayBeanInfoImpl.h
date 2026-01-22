#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/runtime/RuntimeArrayInfo.h"
#include "com/sun/xml/bind/v2/runtime/ArrayBeanInfoImpl/ArrayLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "javax/xml/bind/helpers/ValidationEventImpl.h"
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


class ArrayBeanInfoImpl : public JaxBeanInfo {
public:
    const Class itemType = this.jaxbType.getComponentType();
    const JaxBeanInfo itemBeanInfo;
    Loader loader;

    public ArrayBeanInfoImpl(JAXBContextImpl owner, RuntimeArrayInfo rai) {
      super(owner, rai, rai.getType(), rai.getTypeName(), false, true, false);
      this.itemBeanInfo = owner.getOrCreate(rai.getItemType());
   }

    void link(JAXBContextImpl grammar) {
      this.getLoader(grammar, false);
      super.link(grammar);
   }

    void* toArray(const std::vector& list) {
    int len = list.size();
    void* array = Array.newInstance(this.itemType, len);

      for (int i = 0; i < len; i++) {
         Array.set(array, i, list.get(i));
      }

    return array;
   }

    void serializeBody(void* array, XMLSerializer target) {
    int len = Array.getLength(array);

      for (int i = 0; i < len; i++) {
    void* item = Array.get(array, i);
         target.startElement("", "item", nullptr, nullptr);
         if (item == nullptr) {
            target.writeXsiNilTrue();
         } else {
            target.childAsXsiType(item, "arrayItem", this.itemBeanInfo, false);
         }

         target.endElement();
      }
   }

    std::string getElementNamespaceURI(void* array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    std::string getElementLocalName(void* array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void* createInstance(UnmarshallingContext context) {
      return std::make_unique<std::vector>();
   }

    bool reset(void* array, UnmarshallingContext context) {
    return false;
   }

    std::string getId(void* array, XMLSerializer target) {
    return nullptr;
   }

    void serializeAttributes(void* array, XMLSerializer target) {
   }

    void serializeRoot(void* array, XMLSerializer target) {
      target.reportError(std::make_shared<ValidationEventImpl>(1, Messages.UNABLE_TO_MARSHAL_NON_ELEMENT.format(new Object[]{array.getClass().getName()}), nullptr, nullptr));
   }

    void serializeURIs(void* array, XMLSerializer target) {
   }

    Transducer getTransducer() {
    return nullptr;
   }

    Loader getLoader(JAXBContextImpl context, bool typeSubstitutionCapable) {
      if (this.loader == nullptr) {
         this.loader = std::make_shared<ArrayLoader>(this, context);
      }

      return this.loader;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
