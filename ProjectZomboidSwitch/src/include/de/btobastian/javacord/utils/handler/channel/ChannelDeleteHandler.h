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
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelDeleteHandler/1.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelDeleteHandler/2.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace channel {


class ChannelDeleteHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(ChannelDeleteHandler.class);

    public ChannelDeleteHandler(ImplDiscordAPI api) {
      super(api, true, "CHANNEL_DELETE");
   }

    void handle(JSONObject packet) {
    int type = packet.getInt("type");
      if (type == 0) {
         this.handleServerTextChannel(packet, this.api.getServerById(packet.getString("guild_id")));
      } else if (type == 2) {
         this.handleServerVoiceChannel(packet, this.api.getServerById(packet.getString("guild_id")));
      }
   }

    void handleServerTextChannel(JSONObject packet, Server server) {
    Channel channel = server.getChannelById(packet.getString("id"));
      if (channel != nullptr) {
         ((ImplServer)server).removeChannel(channel);
         this.listenerExecutorService.submit(std::make_shared<1>(this, channel));
      }
   }

    void handleServerVoiceChannel(JSONObject packet, Server server) {
    VoiceChannel channel = server.getVoiceChannelById(packet.getString("id"));
      if (channel != nullptr) {
         ((ImplServer)server).removeVoiceChannel(channel);
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
