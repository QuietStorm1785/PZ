#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/server/role/GuildRoleDeleteHandler/1.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {
namespace role {


class GuildRoleDeleteHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(GuildRoleDeleteHandler.class);

    public GuildRoleDeleteHandler(ImplDiscordAPI api) {
      super(api, true, "GUILD_ROLE_DELETE");
   }

    void handle(JSONObject packet) {
    std::string guildId = packet.getString("guild_id");
    std::string roleId = packet.getString("role_id");
    Server server = this.api.getServerById(guildId);
    Role role = server.getRoleById(roleId);
      if (role != nullptr) {
         ((ImplServer)server).removeRole(role);
         this.listenerExecutorService.submit(std::make_shared<1>(this, role));
      }
   }
}
} // namespace role
} // namespace server
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
