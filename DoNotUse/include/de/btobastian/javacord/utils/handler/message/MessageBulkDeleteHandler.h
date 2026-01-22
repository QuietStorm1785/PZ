#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/message/MessageBulkDeleteHandler/1.h"
#include "org/json/JSONArray.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace message {


class MessageBulkDeleteHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(MessageBulkDeleteHandler.class);

    public MessageBulkDeleteHandler(ImplDiscordAPI api) {
      super(api, true, "MESSAGE_DELETE_BULK");
   }

    void handle(JSONObject packet) {
    JSONArray messageIds = packet.getJSONArray("ids");

      for (int i = 0; i < messageIds.length(); i++) {
    std::string messageId = messageIds.getString(i);
    Message message = this.api.getMessageById(messageId);
         if (message == nullptr) {
            return;
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
