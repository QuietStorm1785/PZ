#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/server/GuildMemberUpdateHandler/1.h"
#include "de/btobastian/javacord/utils/handler/server/GuildMemberUpdateHandler/2.h"
#include "de/btobastian/javacord/utils/handler/server/GuildMemberUpdateHandler/3.h"
#include "org/json/JSONArray.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildMemberUpdateHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(GuildMemberUpdateHandler.class);

    public GuildMemberUpdateHandler(ImplDiscordAPI api) {
      super(api, true, "GUILD_MEMBER_UPDATE");
   }

    void handle(JSONObject packet) {
    ImplServer server = (ImplServer)this.api.getServerById(packet.getString("guild_id"));
    User user = this.api.getOrCreateUser(packet.getJSONObject("user"));
      if (server != nullptr) {
         if (packet.has("nick")) {
    std::string newNick = packet.isNull("nick") ? nullptr : packet.getString("nick");
    std::string oldNick = server.getNickname(user);
            if (newNick != nullptr && !newNick == oldNick) || oldNick != nullptr && !oldNick == newNick)) {
               server.setNickname(user, newNick);
               this.listenerExecutorService.submit(std::make_shared<1>(this, server, user, oldNick));
            }
         }

    JSONArray jsonRoles = packet.getJSONArray("roles");
         Role[] roles = new Role[jsonRoles.length()];

         for (int i = 0; i < jsonRoles.length(); i++) {
            roles[i] = server.getRoleById(jsonRoles.getString(i));
         }

         for (Role role : user.getRoles(server)) {
    bool contains = false;

    for (auto& r : roles)               if (role == r) {
                  contains = true;
                  break;
               }
            }

            if (!contains) {
               ((ImplRole)role).removeUserNoUpdate(user);
               this.api.getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<2>(this, user, role));
            }
         }

    for (auto& role : roles)            if (!user.getRoles(server).contains(role)) {
               ((ImplRole)role).addUserNoUpdate(user);
               this.api.getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<3>(this, user, role));
            }
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
