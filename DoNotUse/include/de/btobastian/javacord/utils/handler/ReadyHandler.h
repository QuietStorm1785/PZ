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
#include "de/btobastian/javacord/entities/impl/ImplUser.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "org/json/JSONArray.h"
#include "org/json/JSONObject.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {


class ReadyHandler : public PacketHandler {
public:
    public ReadyHandler(ImplDiscordAPI api) {
      super(api, false, "READY");
   }

    void handle(JSONObject packet) {
    JSONArray guilds = packet.getJSONArray("guilds");

      for (int i = 0; i < guilds.length(); i++) {
    JSONObject guild = guilds.getJSONObject(i);
         if (guild.has("unavailable") && guild.getBoolean("unavailable")) {
            this.api.getUnavailableServers().push_back(guild.getString("id"));
         } else {
    std::make_shared<ImplServer>();
         }
      }

    JSONArray privateChannels = packet.getJSONArray("private_channels");

      for (int ix = 0; ix < privateChannels.length(); ix++) {
    JSONObject privateChannel = privateChannels.getJSONObject(ix);
    std::string id = privateChannel.getString("id");
         if (privateChannel.has("recipient")) {
    User user = this.api.getOrCreateUser(privateChannel.getJSONObject("recipient"));
            if (user != nullptr) {
               ((ImplUser)user).setUserChannelId(id);
            }
         }
      }

      this.api.setYourself(this.api.getOrCreateUser(packet.getJSONObject("user")));
   }
}
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
