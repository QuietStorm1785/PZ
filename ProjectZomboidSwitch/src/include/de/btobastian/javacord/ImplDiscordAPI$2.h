#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <nlohmann/json.hpp>

namespace de {
namespace btobastian {
namespace javacord {


class ImplDiscordAPI {
public:
   ImplDiscordAPI$2(ImplDiscordAPI& parent, DiscordAPI& api) : parent_(parent), api_(api) {}

   DiscordAPI& call() {
      parent_.connectBlocking();
      // Optionally handle JSON config or state here
      return api_;
   }
private:
   ImplDiscordAPI& parent_;
   DiscordAPI& api_;
}
} // namespace javacord
} // namespace btobastian
} // namespace de
