#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/message/MessageCreateHandler/1.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace message {


class MessageCreateHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(MessageCreateHandler.class);

    public MessageCreateHandler(ImplDiscordAPI api) {
      super(api, true, "MESSAGE_CREATE");
   }

    void handle(JSONObject packet) {
    std::string messageId = packet.getString("id");
    Message messageTemp = this.api.getMessageById(messageId);
      if (messageTemp == nullptr) {
         messageTemp = std::make_shared<ImplMessage>(packet, this.api, nullptr);
      }

      this.listenerExecutorService.submit(std::make_shared<1>(this, messageTemp));
   }
}
} // namespace message
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
