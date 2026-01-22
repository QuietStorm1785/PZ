#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildDeleteHandler/1.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildDeleteHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(GuildDeleteHandler.class);

    public GuildDeleteHandler(ImplDiscordAPI api) {
      super(api, true, "GUILD_DELETE");
   }

    void handle(JSONObject packet) {
    Server server = this.api.getServerById(packet.getString("id"));
      if (server != nullptr) {
         this.api.getServerMap().remove(server.getId());
         this.listenerExecutorService.submit(std::make_shared<1>(this, server));
      }
   }
}
} // namespace server
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
