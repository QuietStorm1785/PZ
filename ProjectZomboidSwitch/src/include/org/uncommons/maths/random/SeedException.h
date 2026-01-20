#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace org {
namespace uncommons {
namespace maths {
namespace random {

class SeedException : public Exception {
public:
    public SeedException(const std::string& message) {
      super(message);
   }

    public SeedException(const std::string& message, std::exception cause) {
      super(message, cause);
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
