#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace api {

class AccessorException : public Exception {
public:
    public AccessorException() {
   }

    public AccessorException(const std::string& message) {
      super(message);
   }

    public AccessorException(const std::string& message, std::exception cause) {
      super(message, cause);
   }

    public AccessorException(std::exception cause) {
      super(cause);
   }
}
} // namespace api
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
