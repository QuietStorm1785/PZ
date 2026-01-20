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
#include "de/btobastian/javacord/utils/handler/message/MessageUpdateHandler/1.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace message {


class MessageUpdateHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(MessageUpdateHandler.class);

    public MessageUpdateHandler(ImplDiscordAPI api) {
      super(api, true, "MESSAGE_UPDATE");
   }

    void handle(JSONObject packet) {
    std::string messageId = packet.getString("id");
    Message message = this.api.getMessageById(messageId);
      if (message != nullptr) {
    std::string oldContent = message.getContent();
         if (packet.has("content")) {
            ((ImplMessage)message).setContent(packet.getString("content"));
            this.listenerExecutorService.submit(std::make_shared<1>(this, message, oldContent));
         }
      }
   }
}
} // namespace message
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
