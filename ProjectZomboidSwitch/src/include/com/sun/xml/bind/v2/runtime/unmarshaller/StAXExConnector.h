#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/stream/XMLStreamException.h"
#include "org/jvnet/staxex/Base64Data.h"
#include "org/jvnet/staxex/XMLStreamReaderEx.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class StAXExConnector : public StAXStreamConnector {
public:
    const XMLStreamReaderEx in;

    public StAXExConnector(XMLStreamReaderEx in, XmlVisitor visitor) {
      super(in, visitor);
      this.in = in;
   }

    void handleCharacters() {
      if (this.predictor.expectText()) {
    CharSequence pcdata = this.in.getPCDATA();
         if (dynamic_cast<Base64Data*>(pcdata) != nullptr) {
    Base64Data bd = (Base64Data)pcdata;
            com.sun.xml.bind.v2.runtime.unmarshaller.Base64Data binary = new com.sun.xml.bind.v2.runtime.unmarshaller.Base64Data();
            if (!bd.hasData()) {
               binary.set(bd.getDataHandler());
            } else {
               binary.set(bd.get(), bd.getDataLen(), bd.getMimeType());
            }

            this.visitor.text(binary);
            this.textReported = true;
         } else {
            this.buffer.append(pcdata);
         }
      }
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
