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
namespace runtime {


enum class Messages {
   ILLEGAL_PARAMETER,
   UNABLE_TO_FIND_CONVERSION_METHOD,
   MISSING_ID,
   NOT_IMPLEMENTED_IN_2_0,
   UNRECOGNIZED_ELEMENT_NAME,
   TYPE_MISMATCH,
   MISSING_OBJECT,
   NOT_IDENTIFIABLE,
   DANGLING_IDREF,
   NULL_OUTPUT_RESOLVER,
   UNABLE_TO_MARSHAL_NON_ELEMENT,
   UNABLE_TO_MARSHAL_UNBOUND_CLASS,
   UNSUPPORTED_PROPERTY,
   NULL_PROPERTY_NAME,
   MUST_BE_X,
   NOT_MARSHALLABLE,
   UNSUPPORTED_RESULT,
   UNSUPPORTED_ENCODING,
   SUBSTITUTED_BY_ANONYMOUS_TYPE,
   CYCLE_IN_MARSHALLER,
   UNABLE_TO_DISCOVER_EVENTHANDLER,
   ELEMENT_NEEDED_BUT_FOUND_DOCUMENT,
   UNKNOWN_CLASS,
   FAILED_TO_GENERATE_SCHEMA,
   ERROR_PROCESSING_SCHEMA,
   ILLEGAL_CONTENT;

    static const ResourceBundle rb = ResourceBundle.getBundle(Messages.class.getName());

    std::string toString() {
      return this.format();
   }

    std::string format(Object... args) {
      return MessageFormat.format(rb.getString(this.name()), args);
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
