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
#include "de/btobastian/javacord/entities/UserStatus.h"
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/entities/impl/ImplUser.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "de/btobastian/javacord/listener/user/UserChangeGameListener.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/user/PresenceUpdateHandler/1.h"
#include "de/btobastian/javacord/utils/handler/user/PresenceUpdateHandler/2.h"
#include "org/json/JSONArray.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace user {


class PresenceUpdateHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(PresenceUpdateHandler.class);

    public PresenceUpdateHandler(ImplDiscordAPI api) {
      super(api, true, "PRESENCE_UPDATE");
   }

    void handle(JSONObject packet) {
    User user = this.api.getOrCreateUser(packet.getJSONObject("user"));
      if (user != nullptr) {
    Server server = nullptr;
         if (packet.has("guild_id")) {
            server = this.api.getServerById(packet.getString("guild_id"));
         }

         if (server != nullptr) {
            ((ImplServer)server).addMember(user);
         }

         if (server != nullptr && packet.has("roles")) {
    JSONArray roleIds = packet.getJSONArray("roles");

            for (int i = 0; i < roleIds.length(); i++) {
               ((ImplRole)server.getRoleById(roleIds.getString(i))).addUserNoUpdate(user);
            }
         }

         if (packet.has("status")) {
    UserStatus status = UserStatus.fromString(packet.getString("status"));
    UserStatus oldStatus = user.getStatus();
            ((ImplUser)user).setStatus(status);
            this.listenerExecutorService.submit(std::make_shared<1>(this, user, oldStatus));
         }

         if (packet.getJSONObject("user").has("username")) {
    std::string name = packet.getJSONObject("user").getString("username");
            if (!user.getName() == name)) {
    std::string oldName = user.getName();
               ((ImplUser)user).setName(name);
               this.listenerExecutorService.submit(std::make_shared<2>(this, user, oldName));
            }
         }

         if (packet.has("game")) {
    std::string game;
            if (!packet.isNull("game") && packet.getJSONObject("game").has("name") && !packet.getJSONObject("game").isNull("name")) {
               game = packet.getJSONObject("game").get("name");
            } else {
               game = nullptr;
            }

    std::string oldGame = user.getGame();
            if (game == nullptr && oldGame != nullptr || game != nullptr && oldGame == nullptr || game != nullptr && !game == oldGame)) {
               ((ImplUser)user).setGame(game);
               List<UserChangeGameListener> listeners = this.api.getListeners(UserChangeGameListener.class);
               /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)                     try {
                        listener.onUserChangeGame(this.api, user, oldGame);
                     } catch (Throwable var12) {
                        logger.warn("Uncaught exception in UserChangeGameListener!", var12);
                     }
                  }
               }
            }
         }
      }
   }
}
} // namespace user
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
