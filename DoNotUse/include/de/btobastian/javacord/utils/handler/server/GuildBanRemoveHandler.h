#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildBanRemoveHandler/1.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildBanRemoveHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(GuildBanRemoveHandler.class);

    public GuildBanRemoveHandler(ImplDiscordAPI api) {
      super(api, true, "GUILD_BAN_REMOVE");
   }

    void handle(JSONObject packet) {
    Server server = this.api.getServerById(packet.getString("guild_id"));
    User user = this.api.getOrCreateUser(packet.getJSONObject("user"));
      if (server != nullptr) {
         ((ImplServer)server).removeMember(user);
         this.listenerExecutorService.submit(std::make_shared<1>(this, user, server));
      }
   }
}
} // namespace server
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
