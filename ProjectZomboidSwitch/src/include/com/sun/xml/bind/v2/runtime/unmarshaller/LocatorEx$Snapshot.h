#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"
#include "javax/xml/bind/ValidationEventLocator.h"
#include "org/w3c/dom/Node.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class LocatorEx {
public:
    const int columnNumber;
    const int lineNumber;
    const int offset;
    const std::string systemId;
    const std::string publicId;
    const URL url;
    const void* object;
    const Node node;

   public LocatorEx$Snapshot(LocatorEx loc) {
      this.columnNumber = loc.getColumnNumber();
      this.lineNumber = loc.getLineNumber();
      this.systemId = loc.getSystemId();
      this.publicId = loc.getPublicId();
    ValidationEventLocator vel = loc.getLocation();
      this.offset = vel.getOffset();
      this.url = vel.getURL();
      this.object = vel.getObject();
      this.node = vel.getNode();
   }

    void* getObject() {
      return this.object;
   }

    Node getNode() {
      return this.node;
   }

    int getOffset() {
      return this.offset;
   }

    URL getURL() {
      return this.url;
   }

    int getColumnNumber() {
      return this.columnNumber;
   }

    int getLineNumber() {
      return this.lineNumber;
   }

    std::string getSystemId() {
      return this.systemId;
   }

    std::string getPublicId() {
      return this.publicId;
   }

    ValidationEventLocator getLocation() {
    return this;
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
