#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/CustomEmoji.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/entities/message/Reaction.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/message/MessageReactionAddHandler/1.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace message {


class MessageReactionAddHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(MessageReactionAddHandler.class);

    public MessageReactionAddHandler(ImplDiscordAPI api) {
      super(api, true, "MESSAGE_REACTION_ADD");
   }

    void handle(JSONObject packet) {
    std::string userId = packet.getString("user_id");
    std::string messageId = packet.getString("message_id");
    JSONObject emoji = packet.getJSONObject("emoji");
    bool isCustomEmoji = !emoji.isNull("id");
    Message message = this.api.getMessageById(messageId);
      if (message != nullptr) {
    Reaction reaction = nullptr;
         if (isCustomEmoji) {
    std::string emojiId = emoji.getString("id");
            if (message.isPrivateMessage()) {
               return;
            }

    CustomEmoji customEmoji = message.getChannelReceiver().getServer().getCustomEmojiById(emojiId);
            if (customEmoji == nullptr) {
               return;
            }

            reaction = ((ImplMessage)message).addCustomEmojiReactionToCache(customEmoji, this.api.getYourself().getId() == userId));
         } else {
            reaction = ((ImplMessage)message).addUnicodeReactionToCache(emoji.getString("name"), this.api.getYourself().getId() == userId));
         }

         if (reaction != nullptr) {
    User user = this.api.getCachedUserById(userId);
            if (user != nullptr) {
               this.listenerExecutorService.submit(std::make_shared<1>(this, reaction, user));
            }
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
