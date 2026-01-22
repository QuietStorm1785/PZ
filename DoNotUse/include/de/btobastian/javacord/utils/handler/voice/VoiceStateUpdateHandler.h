#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/impl/ImplUser.h"
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/voice/VoiceStateUpdateHandler/1.h"
#include "de/btobastian/javacord/utils/handler/voice/VoiceStateUpdateHandler/2.h"
#include "org/json/JSONException.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace voice {


class VoiceStateUpdateHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(VoiceStateUpdateHandler.class);

    public VoiceStateUpdateHandler(ImplDiscordAPI api) {
      super(api, true, "VOICE_STATE_UPDATE");
   }

    void handle(JSONObject packet) {
    ImplUser user = nullptr;

      try {
         user = (ImplUser)this.api.getUserById(packet.getString("user_id")).get();
      } catch (InterruptedException | ExecutionException | JSONException var7) {
         var7.printStackTrace();
      }

    std::string channelId = nullptr;

      try {
         channelId = packet.getString("channel_id");
      } catch (JSONException var6) {
      }

      if (channelId != nullptr) {
         if (user.getVoiceChannel() != nullptr) {
            if (channelId == user.getVoiceChannel().getId())) {
               return;
            }

            ((ImplVoiceChannel)user.getVoiceChannel()).removeConnectedUser(user);
         }

    ImplVoiceChannel channel = (ImplVoiceChannel)this.api.getVoiceChannelById(channelId);
         if (channel == nullptr) {
            return;
         }

         channel.addConnectedUser(user);
         user.setVoiceChannel(channel);
         this.listenerExecutorService.submit(std::make_shared<1>(this, user, channel));
      } else {
         if (user.getVoiceChannel() != nullptr) {
            ((ImplVoiceChannel)user.getVoiceChannel()).removeConnectedUser(user);
         }

         user.setVoiceChannel(nullptr);
         this.listenerExecutorService.submit(std::make_shared<2>(this, user));
      }
   }
}
} // namespace voice
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
