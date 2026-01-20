#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/Locator.h"
#include "org/xml/sax/SAXParseException.h"

namespace com {
namespace sun {
namespace istack {


class SAXParseException2 : public SAXParseException {
public:
    public SAXParseException2(const std::string& message, Locator locator) {
      super(message, locator);
   }

    public SAXParseException2(const std::string& message, Locator locator, std::exception e) {
      super(message, locator, e);
   }

    public SAXParseException2(const std::string& message, const std::string& publicId, const std::string& systemId, int lineNumber, int columnNumber) {
      super(message, publicId, systemId, lineNumber, columnNumber);
   }

    public SAXParseException2(const std::string& message, const std::string& publicId, const std::string& systemId, int lineNumber, int columnNumber, std::exception e) {
      super(message, publicId, systemId, lineNumber, columnNumber, e);
   }

    std::exception getCause() {
      return this.getException();
   }
}
} // namespace istack
} // namespace sun
} // namespace com
