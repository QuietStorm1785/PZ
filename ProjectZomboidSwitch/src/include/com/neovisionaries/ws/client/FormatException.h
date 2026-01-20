#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

class FormatException : public Exception {
public:
    static const long serialVersionUID = 1L;

    public FormatException(const std::string& message) {
      super(message);
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
