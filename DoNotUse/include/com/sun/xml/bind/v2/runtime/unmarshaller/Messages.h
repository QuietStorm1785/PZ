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
namespace unmarshaller {


enum class Messages {
   UNRESOLVED_IDREF,
   UNEXPECTED_ELEMENT,
   UNEXPECTED_TEXT,
   NOT_A_QNAME,
   UNRECOGNIZED_TYPE_NAME,
   UNRECOGNIZED_TYPE_NAME_MAYBE,
   UNABLE_TO_CREATE_MAP,
   UNINTERNED_STRINGS,
   ERRORS_LIMIT_EXCEEDED;

    static const ResourceBundle rb = ResourceBundle.getBundle(Messages.class.getName());

    std::string toString() {
      return this.format();
   }

    std::string format(Object... args) {
      return MessageFormat.format(rb.getString(this.name()), args);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
