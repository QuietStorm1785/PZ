#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "javax/xml/bind/UnmarshallerHandler.h"
#include "javax/xml/transform/sax/SAXResult.h"

namespace javax {
namespace xml {
namespace bind {
namespace util {


class JAXBResult : public SAXResult {
public:
    const UnmarshallerHandler unmarshallerHandler;

    public JAXBResult(JAXBContext context) {
      this(context == nullptr ? assertionFailed() : context.createUnmarshaller());
   }

    public JAXBResult(Unmarshaller _unmarshaller) {
      if (_unmarshaller == nullptr) {
         throw JAXBException(Messages.format("JAXBResult.NullUnmarshaller"));
      } else {
         this.unmarshallerHandler = _unmarshaller.getUnmarshallerHandler();
         super.setHandler(this.unmarshallerHandler);
      }
   }

    void* getResult() {
      return this.unmarshallerHandler.getResult();
   }

    static Unmarshaller assertionFailed() {
      throw JAXBException(Messages.format("JAXBResult.NullContext"));
   }
}
} // namespace util
} // namespace bind
} // namespace xml
} // namespace javax
