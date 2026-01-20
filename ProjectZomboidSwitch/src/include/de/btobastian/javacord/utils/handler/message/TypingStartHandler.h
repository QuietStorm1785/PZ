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
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/message/TypingStartHandler/1.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>
#include <iterator>

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace message {


class TypingStartHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(TypingStartHandler.class);

    public TypingStartHandler(ImplDiscordAPI api) {
      super(api, true, "TYPING_START");
   }

    void handle(JSONObject packet) {
    Channel channelTemp = nullptr;
    std::string channelId = packet.getString("channel_id");
      Iterator<Server> serverIterator = this.api.getServers().iterator();

      while (serverIterator.hasNext()) {
         channelTemp = serverIterator.next().getChannelById(channelId);
         if (channelTemp != nullptr) {
            break;
         }
      }

    std::string userId = packet.getString("user_id");

    User user;
      try {
         user = (User)this.api.getUserById(userId).get();
      } catch (ExecutionException | InterruptedException var9) {
         return;
      }

      this.listenerExecutorService.submit(std::make_shared<1>(this, user, channelTemp));
   }
}
} // namespace message
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
