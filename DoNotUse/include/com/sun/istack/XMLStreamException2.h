#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/stream/Location.h"
#include "javax/xml/stream/XMLStreamException.h"

namespace com {
namespace sun {
namespace istack {


class XMLStreamException2 : public XMLStreamException {
public:
    public XMLStreamException2(const std::string& msg) {
      super(msg);
   }

    public XMLStreamException2(std::exception th) {
      super(th);
   }

    public XMLStreamException2(const std::string& msg, std::exception th) {
      super(msg, th);
   }

    public XMLStreamException2(const std::string& msg, Location location) {
      super(msg, location);
   }

    public XMLStreamException2(const std::string& msg, Location location, std::exception th) {
      super(msg, location, th);
   }

    std::exception getCause() {
      return this.getNestedException();
   }
}
} // namespace istack
} // namespace sun
} // namespace com
