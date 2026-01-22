#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace istack {


class SAXException2 : public SAXException {
public:
    public SAXException2(const std::string& message) {
      super(message);
   }

    public SAXException2(std::exception e) {
      super(e);
   }

    public SAXException2(const std::string& message, std::exception e) {
      super(message, e);
   }

    std::exception getCause() {
      return this.getException();
   }
}
} // namespace istack
} // namespace sun
} // namespace com
