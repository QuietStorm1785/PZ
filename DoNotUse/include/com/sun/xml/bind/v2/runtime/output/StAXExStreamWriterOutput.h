#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/marshaller/NoEscapeHandler.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Base64Data.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/jvnet/staxex/XMLStreamWriterEx.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class StAXExStreamWriterOutput : public XMLStreamWriterOutput {
public:
    const XMLStreamWriterEx out;

    public StAXExStreamWriterOutput(XMLStreamWriterEx out) {
      super(out, NoEscapeHandler.theInstance);
      this.out = out;
   }

    void text(Pcdata value, bool needsSeparatingWhitespace) {
      if (needsSeparatingWhitespace) {
         this.out.writeCharacters(" ");
      }

      if (!(dynamic_cast<Base64Data*>(value) != nullptr)) {
         this.out.writeCharacters(value);
      } else {
    Base64Data v = (Base64Data)value;
         this.out.writeBinary(v.getDataHandler());
      }
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
