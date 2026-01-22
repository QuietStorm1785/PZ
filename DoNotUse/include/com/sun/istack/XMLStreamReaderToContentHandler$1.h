#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/Locator.h"

namespace com {
namespace sun {
namespace istack {


class XMLStreamReaderToContentHandler {
public:
   XMLStreamReaderToContentHandler$1(XMLStreamReaderToContentHandler this$0) {
      this.this$0 = this$0;
   }

    int getColumnNumber() {
      return XMLStreamReaderToContentHandler.access$000(this.this$0).getLocation().getColumnNumber();
   }

    int getLineNumber() {
      return XMLStreamReaderToContentHandler.access$000(this.this$0).getLocation().getLineNumber();
   }

    std::string getPublicId() {
      return XMLStreamReaderToContentHandler.access$000(this.this$0).getLocation().getPublicId();
   }

    std::string getSystemId() {
      return XMLStreamReaderToContentHandler.access$000(this.this$0).getLocation().getSystemId();
   }
}
} // namespace istack
} // namespace sun
} // namespace com
