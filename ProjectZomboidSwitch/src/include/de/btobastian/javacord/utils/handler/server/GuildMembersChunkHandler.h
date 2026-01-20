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
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildMembersChunkHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(GuildMembersChunkHandler.class);

    public GuildMembersChunkHandler(ImplDiscordAPI api) {
      super(api, true, "GUILD_MEMBERS_CHUNK");
   }

    void handle(JSONObject packet) {
    Server server = this.api.getServerById(packet.getString("guild_id"));
      if (server != nullptr) {
         ((ImplServer)server).addMembers(packet.getJSONArray("members"));
      }
   }
}
} // namespace server
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
