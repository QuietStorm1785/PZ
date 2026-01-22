#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/ValidationEventLocator.h"
#include "javax/xml/bind/helpers/ValidationEventLocatorImpl.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class StAXConnector {
public:
   StAXConnector$1(StAXConnector this$0) {
      this.this$0 = this$0;
   }

    ValidationEventLocator getLocation() {
      return std::make_shared<ValidationEventLocatorImpl>(this);
   }

    int getColumnNumber() {
      return this.this$0.getCurrentLocation().getColumnNumber();
   }

    int getLineNumber() {
      return this.this$0.getCurrentLocation().getLineNumber();
   }

    std::string getPublicId() {
      return this.this$0.getCurrentLocation().getPublicId();
   }

    std::string getSystemId() {
      return this.this$0.getCurrentLocation().getSystemId();
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
