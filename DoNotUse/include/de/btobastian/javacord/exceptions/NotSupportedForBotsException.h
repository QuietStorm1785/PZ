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

class NotSupportedForBotsException : public IllegalStateException {
public:
    public NotSupportedForBotsException() {
      super("Bots are not able to use this method!");
   }

    public NotSupportedForBotsException(const std::string& message) {
      super(message);
   }
}
} // namespace exceptions
} // namespace javacord
} // namespace btobastian
} // namespace de
