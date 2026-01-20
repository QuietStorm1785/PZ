#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace de {
namespace btobastian {
namespace javacord {
namespace exceptions {

class PermissionsException : public Exception {
public:
    public PermissionsException(const std::string& message) {
      super(message);
   }
}
} // namespace exceptions
} // namespace javacord
} // namespace btobastian
} // namespace de
