#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/CompositeStructure.h"
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


class CompositeStructureBeanInfo : public JaxBeanInfo {
public:
    public CompositeStructureBeanInfo(JAXBContextImpl context) {
      super(context, nullptr, CompositeStructure.class, false, true, false);
   }

    std::string getElementNamespaceURI(CompositeStructure o) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    std::string getElementLocalName(CompositeStructure o) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    CompositeStructure createInstance(UnmarshallingContext context) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool reset(CompositeStructure o, UnmarshallingContext context) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    std::string getId(CompositeStructure o, XMLSerializer target) {
    return nullptr;
   }

    Loader getLoader(JAXBContextImpl context, bool typeSubstitutionCapable) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void serializeRoot(CompositeStructure o, XMLSerializer target) {
      target.reportError(std::make_shared<ValidationEventImpl>(1, Messages.UNABLE_TO_MARSHAL_NON_ELEMENT.format(new Object[]{o.getClass().getName()}), nullptr, nullptr));
   }

    void serializeURIs(CompositeStructure o, XMLSerializer target) {
   }

    void serializeAttributes(CompositeStructure o, XMLSerializer target) {
   }

    void serializeBody(CompositeStructure o, XMLSerializer target) {
    int len = o.bridges.length;

      for (int i = 0; i < len; i++) {
    void* value = o.values[i];
    InternalBridge bi = (InternalBridge)o.bridges[i];
         bi.marshal(value, target);
      }
   }

   public Transducer<CompositeStructure> getTransducer() {
    return nullptr;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
