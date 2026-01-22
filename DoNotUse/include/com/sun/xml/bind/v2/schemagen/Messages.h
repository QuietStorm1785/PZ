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
namespace schemagen {


enum class Messages {
   ANONYMOUS_TYPE_CYCLE;

    static const ResourceBundle rb = ResourceBundle.getBundle(Messages.class.getName());

    std::string toString() {
      return this.format();
   }

    std::string format(Object... args) {
      return MessageFormat.format(rb.getString(this.name()), args);
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
