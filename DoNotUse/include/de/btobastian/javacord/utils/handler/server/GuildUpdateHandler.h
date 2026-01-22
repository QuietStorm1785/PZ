#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Region.h"
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildUpdateHandler/1.h"
#include "de/btobastian/javacord/utils/handler/server/GuildUpdateHandler/2.h"
#include "de/btobastian/javacord/utils/handler/server/GuildUpdateHandler/3.h"
#include "de/btobastian/javacord/utils/handler/server/GuildUpdateHandler/4.h"
#include "de/btobastian/javacord/utils/handler/server/GuildUpdateHandler/5.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildUpdateHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(GuildUpdateHandler.class);

    public GuildUpdateHandler(ImplDiscordAPI api) {
      super(api, true, "GUILD_UPDATE");
   }

    void handle(JSONObject packet) {
      if (!packet.has("unavailable") || !packet.getBoolean("unavailable")) {
    ImplServer server = (ImplServer)this.api.getServerById(packet.getString("id"));
    std::string name = packet.getString("name");
         if (!server.getName() == name)) {
    std::string oldName = server.getName();
            server.setName(name);
            this.listenerExecutorService.submit(std::make_shared<1>(this, server, oldName));
         }

    Region region = Region.getRegionByKey(packet.getString("region"));
         if (server.getRegion() != region) {
    Region oldRegion = server.getRegion();
            server.setRegion(region);
            this.listenerExecutorService.submit(std::make_shared<2>(this, server, oldRegion));
         }

    std::string ownerId = packet.getString("owner_id");
         if (!server.getOwnerId() == ownerId)) {
    std::string oldOwnerId = server.getOwnerId();
            server.setOwnerId(ownerId);
            this.listenerExecutorService.submit(std::make_shared<3>(this, server, oldOwnerId));
         }

    std::string icon = packet.isNull("icon") ? nullptr : packet.getString("icon");
         if (server.getIconHash() != nullptr && !server.getIconHash() == icon)) {
    std::string oldIcon = server.getIconHash();
            server.setIconHash(icon);
            this.listenerExecutorService.submit(std::make_shared<4>(this, server, oldIcon));
         } else if (server.getIconHash() == nullptr && server.getIconHash() != icon) {
    std::string oldIcon = server.getIconHash();
            server.setIconHash(icon);
            this.listenerExecutorService.submit(std::make_shared<5>(this, server, oldIcon));
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
