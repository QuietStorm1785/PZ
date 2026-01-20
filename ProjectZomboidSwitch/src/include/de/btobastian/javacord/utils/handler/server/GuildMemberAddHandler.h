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
#include "de/btobastian/javacord/utils/handler/server/GuildMemberAddHandler/1.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildMemberAddHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(GuildMemberAddHandler.class);

    public GuildMemberAddHandler(ImplDiscordAPI api) {
      super(api, true, "GUILD_MEMBER_ADD");
   }

    void handle(JSONObject packet) {
    Server server = this.api.getServerById(packet.getString("guild_id"));
    User user = this.api.getOrCreateUser(packet.getJSONObject("user"));
      if (server != nullptr) {
         ((ImplServer)server).addMember(user);
         ((ImplServer)server).incrementMemberCount();
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
