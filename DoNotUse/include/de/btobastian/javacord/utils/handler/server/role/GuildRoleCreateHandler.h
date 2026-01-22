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
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/server/role/GuildRoleCreateHandler/1.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {
namespace role {


class GuildRoleCreateHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(GuildRoleCreateHandler.class);

    public GuildRoleCreateHandler(ImplDiscordAPI api) {
      super(api, true, "GUILD_ROLE_CREATE");
   }

    void handle(JSONObject packet) {
    std::string guildId = packet.getString("guild_id");
    JSONObject roleJson = packet.getJSONObject("role");
    Server server = this.api.getServerById(guildId);
    Role role = std::make_shared<ImplRole>(roleJson, (ImplServer)server, this.api);
      this.listenerExecutorService.submit(std::make_shared<1>(this, role));
   }
}
} // namespace role
} // namespace server
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
