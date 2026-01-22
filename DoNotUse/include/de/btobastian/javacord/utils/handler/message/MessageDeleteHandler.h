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
#include "de/btobastian/javacord/utils/handler/message/MessageDeleteHandler/1.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace message {


class MessageDeleteHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(MessageDeleteHandler.class);

    public MessageDeleteHandler(ImplDiscordAPI api) {
      super(api, true, "MESSAGE_DELETE");
   }

    void handle(JSONObject packet) {
    std::string messageId = packet.getString("id");
    Message message = this.api.getMessageById(messageId);
      if (message != nullptr) {
         /* synchronized - TODO: add std::mutex */ (message) {
            if (message.isDeleted()) {
               return;
            }

            ((ImplMessage)message).setDeleted(true);
         }

         this.listenerExecutorService.submit(std::make_shared<1>(this, message));
      }
   }
}
} // namespace message
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
