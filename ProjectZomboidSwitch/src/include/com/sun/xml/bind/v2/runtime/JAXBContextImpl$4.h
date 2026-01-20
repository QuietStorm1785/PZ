#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/ErrorListener.h"
#include "org/xml/sax/SAXParseException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class JAXBContextImpl {
public:
   JAXBContextImpl$4(JAXBContextImpl this$0, SAXParseException[] var2, SAXParseException[] var3) {
      this.this$0 = this$0;
      this.val$e = var2;
      this.val$w = var3;
   }

    void error(SAXParseException exception) {
      this.val$e[0] = exception;
   }

    void fatalError(SAXParseException exception) {
      this.val$e[0] = exception;
   }

    void warning(SAXParseException exception) {
      this.val$w[0] = exception;
   }

    void info(SAXParseException exception) {
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
