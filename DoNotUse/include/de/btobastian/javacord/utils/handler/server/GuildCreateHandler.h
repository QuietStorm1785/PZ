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
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildCreateHandler/1.h"
#include "de/btobastian/javacord/utils/handler/server/GuildCreateHandler/2.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildCreateHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(GuildCreateHandler.class);

    public GuildCreateHandler(ImplDiscordAPI api) {
      super(api, true, "GUILD_CREATE");
   }

    void handle(JSONObject packet) {
      if (!packet.has("unavailable") || !packet.getBoolean("unavailable")) {
    std::string id = packet.getString("id");
         if (this.api.getUnavailableServers().contains(id)) {
            this.api.getUnavailableServers().remove(id);
    std::make_shared<ImplServer>();
         } else if (this.api.getServerById(id) == nullptr) {
    Server server = std::make_shared<ImplServer>(packet, this.api);
            this.listenerExecutorService.submit(std::make_shared<1>(this, server));
            this.api.getThreadPool().getExecutorService().submit(std::make_shared<2>(this, server));
         }
      }
   }
}
} // namespace server
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
