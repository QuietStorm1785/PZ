#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Marshaller.h"
#include "javax/xml/bind/util/JAXBSource/1.h"
#include "javax/xml/transform/sax/SAXSource.h"
#include "org/xml/sax/InputSource.h"
#include "org/xml/sax/XMLReader.h"

namespace javax {
namespace xml {
namespace bind {
namespace util {


class JAXBSource : public SAXSource {
public:
    const Marshaller marshaller;
    const void* contentObject;
    const XMLReader pseudoParser = std::make_shared<1>(this);

    public JAXBSource(JAXBContext context, void* contentObject) {
      this(
         context == nullptr ? assertionFailed(Messages.format("JAXBSource.NullContext")) : context.createMarshaller(),
         contentObject == nullptr ? assertionFailed(Messages.format("JAXBSource.NullContent")) : contentObject
      );
   }

    public JAXBSource(Marshaller marshaller, void* contentObject) {
      if (marshaller == nullptr) {
         throw JAXBException(Messages.format("JAXBSource.NullMarshaller"));
      } else if (contentObject == nullptr) {
         throw JAXBException(Messages.format("JAXBSource.NullContent"));
      } else {
         this.marshaller = marshaller;
         this.contentObject = contentObject;
         super.setXMLReader(this.pseudoParser);
         super.setInputSource(std::make_unique<InputSource>());
      }
   }

    static Marshaller assertionFailed(const std::string& message) {
      throw JAXBException(message);
   }
}
} // namespace util
} // namespace bind
} // namespace xml
} // namespace javax
