#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/ErrorHandler.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/SAXParseException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace util {


class FatalAdapter {
public:
    const ErrorHandler core;

    public FatalAdapter(ErrorHandler handler) {
      this.core = handler;
   }

    void warning(SAXParseException exception) {
      this.core.warning(exception);
   }

    void error(SAXParseException exception) {
      this.core.fatalError(exception);
   }

    void fatalError(SAXParseException exception) {
      this.core.fatalError(exception);
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
