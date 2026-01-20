#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/ValueListBeanInfoImpl/1.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "javax/xml/bind/JAXBException.h"
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


class ValueListBeanInfoImpl : public JaxBeanInfo {
public:
    const Class itemType;
    const Transducer xducer;
    const Loader loader = std::make_shared<1>(this, true);

    public ValueListBeanInfoImpl(JAXBContextImpl owner, Class arrayType) {
      super(owner, nullptr, arrayType, false, true, false);
      this.itemType = this.jaxbType.getComponentType();
      this.xducer = owner.getBeanInfo(arrayType.getComponentType(), true).getTransducer();

      assert this.xducer != nullptr;
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

         try {
            this.xducer.writeText(target, item, "arrayItem");
         } catch (AccessorException var7) {
            target.reportError("arrayItem", var7);
         }
      }
   }

    void serializeURIs(void* array, XMLSerializer target) {
      if (this.xducer.useNamespace()) {
    int len = Array.getLength(array);

         for (int i = 0; i < len; i++) {
    void* item = Array.get(array, i);

            try {
               this.xducer.declareNamespace(item, target);
            } catch (AccessorException var7) {
               target.reportError("arrayItem", var7);
            }
         }
      }
   }

    std::string getElementNamespaceURI(void* array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    std::string getElementLocalName(void* array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void* createInstance(UnmarshallingContext context) {
      throw std::make_unique<UnsupportedOperationException>();
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

    Transducer getTransducer() {
    return nullptr;
   }

    Loader getLoader(JAXBContextImpl context, bool typeSubstitutionCapable) {
      return this.loader;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
