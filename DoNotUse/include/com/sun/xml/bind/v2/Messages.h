#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/MessageFormat.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {


enum class Messages {
   ILLEGAL_ENTRY,
   ERROR_LOADING_CLASS,
   INVALID_PROPERTY_VALUE,
   UNSUPPORTED_PROPERTY,
   BROKEN_CONTEXTPATH,
   NO_DEFAULT_CONSTRUCTOR_IN_INNER_CLASS,
   INVALID_TYPE_IN_MAP,
   INVALID_JAXP_IMPLEMENTATION,
   JAXP_SUPPORTED_PROPERTY,
   JAXP_UNSUPPORTED_PROPERTY,
   JAXP_XML_SECURITY_DISABLED,
   JAXP_EXTERNAL_ACCESS_CONFIGURED;

    static const ResourceBundle rb = ResourceBundle.getBundle(Messages.class.getName());

    std::string toString() {
      return this.format();
   }

    std::string format(Object... args) {
      return MessageFormat.format(rb.getString(this.name()), args);
   }
}
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
