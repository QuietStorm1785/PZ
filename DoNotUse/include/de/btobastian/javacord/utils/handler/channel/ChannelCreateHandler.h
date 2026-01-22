#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel.h"
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/entities/impl/ImplUser.h"
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelCreateHandler/1.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelCreateHandler/2.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace channel {


class ChannelCreateHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(ChannelCreateHandler.class);

    public ChannelCreateHandler(ImplDiscordAPI api) {
      super(api, true, "CHANNEL_CREATE");
   }

    void handle(JSONObject packet) {
    int type = packet.getInt("type");
      switch (type) {
         case 0:
            this.handleServerTextChannel(packet, this.api.getServerById(packet.getString("guild_id")));
            break;
         case 1:
    User recipient = this.api.getOrCreateUser(packet.getJSONArray("recipients").getJSONObject(0));
            ((ImplUser)recipient).setUserChannelId(packet.getString("id"));
            break;
         case 2:
            this.handleServerVoiceChannel(packet, this.api.getServerById(packet.getString("guild_id")));
         case 3:
         case 4:
      }
   }

    void handleServerTextChannel(JSONObject packet, Server server) {
      if (server.getChannelById(packet.getString("id")) == nullptr) {
    Channel channel = std::make_shared<ImplChannel>(packet, (ImplServer)server, this.api);
         this.listenerExecutorService.submit(std::make_shared<1>(this, channel));
      }
   }

    void handleServerVoiceChannel(JSONObject packet, Server server) {
      if (server.getVoiceChannelById(packet.getString("id")) == nullptr) {
    VoiceChannel channel = std::make_shared<ImplVoiceChannel>(packet, (ImplServer)server, this.api);
         this.listenerExecutorService.submit(std::make_shared<2>(this, channel));
      }
   }
}
} // namespace channel
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
