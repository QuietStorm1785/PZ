#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/output/NamespaceContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/output/SAXOutput.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/ContentHandler.h"
#include "org/xml/sax/SAXException.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class MarshallerImpl {
public:
   MarshallerImpl$2(MarshallerImpl this$0, ContentHandler out) {
      super(out);
      this.this$0 = this$0;
   }

    void startDocument(XMLSerializer serializer, bool fragment, int[] nsUriIndex2prefixIndex, NamespaceContextImpl nsContext) {
      super.startDocument(serializer, false, nsUriIndex2prefixIndex, nsContext);
   }

    void endDocument(bool fragment) {
      super.endDocument(false);
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
