#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/ValidationEventLocator.h"
#include "javax/xml/bind/helpers/ValidationEventLocatorImpl.h"
#include "org/xml/sax/Locator.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class LocatorExWrapper {
public:
    const Locator locator;

    public LocatorExWrapper(Locator locator) {
      this.locator = locator;
   }

    ValidationEventLocator getLocation() {
      return std::make_shared<ValidationEventLocatorImpl>(this.locator);
   }

    std::string getPublicId() {
      return this.locator.getPublicId();
   }

    std::string getSystemId() {
      return this.locator.getSystemId();
   }

    int getLineNumber() {
      return this.locator.getLineNumber();
   }

    int getColumnNumber() {
      return this.locator.getColumnNumber();
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
