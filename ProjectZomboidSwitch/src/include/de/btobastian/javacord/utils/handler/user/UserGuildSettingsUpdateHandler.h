#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "org/json/JSONObject.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace user {


class UserGuildSettingsUpdateHandler : public PacketHandler {
public:
    public UserGuildSettingsUpdateHandler(ImplDiscordAPI api) {
      super(api, true, "USER_GUILD_SETTINGS_UPDATE");
   }

    void handle(JSONObject packet) {
   }
}
} // namespace user
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
