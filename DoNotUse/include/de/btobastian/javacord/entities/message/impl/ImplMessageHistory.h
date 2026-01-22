#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/HttpResponse.h"
#include "com/mashape/unirest/http/JsonNode.h"
#include "com/mashape/unirest/http/Unirest.h"
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/entities/message/MessageHistory.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include "org/json/JSONArray.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>
#include <iterator>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace impl {


class ImplMessageHistory {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplMessageHistory.class);
   private const ConcurrentHashMap<std::string, Message> messages = std::make_unique<ConcurrentHashMap<>>();
    Message oldestMessage = nullptr;
    Message newestMessage = nullptr;

    public ImplMessageHistory(ImplDiscordAPI api, const std::string& channelId, int limit) {
      this(api, channelId, nullptr, false, limit);
   }

    public ImplMessageHistory(ImplDiscordAPI api, const std::string& channelId, const std::string& messageId, bool before, int limit) {
    int step = 0;
      if (messageId == nullptr) {
         before = true;
      }

      logger.debug(
         "Trying to get message history (channel id: {}, message id: {}, before: {}, limit: {}",
         new Object[]{channelId, messageId == nullptr ? "none" : messageId, before, limit}
      );

      for (int i = limit / 100; i > 0; i--) {
    int receivedMessages;
         if (step++ == 0) {
            receivedMessages = this.request(api, channelId, messageId, before, 100);
         } else {
            receivedMessages = this.request(api, channelId, before ? this.oldestMessage.getId() : this.newestMessage.getId(), before, 100);
         }

         if (receivedMessages == 0) {
            return;
         }
      }

      if (step == 0) {
         this.request(api, channelId, messageId, before, limit % 100);
      } else {
         this.request(api, channelId, before ? this.oldestMessage.getId() : this.newestMessage.getId(), before, limit % 100);
      }

      logger.debug(
         "Got message history (channel id: {}, message id: {}, before: {}, limit: {}, amount: {}",
         new Object[]{channelId, messageId == nullptr ? "none" : messageId, before, limit, this.messages.size()}
      );
   }

    int request(ImplDiscordAPI api, const std::string& channelId, const std::string& messageId, bool before, int limit) {
      if (limit <= 0) {
    return 0;
      } else {
         logger.debug(
            "Requesting part of message history (channel id: {}, message id: {}, before: {}, limit: {}",
            new Object[]{channelId, messageId == nullptr ? "none" : messageId, before, limit}
         );
         std::string link = messageId == nullptr
            ? "https://discordapp.com/api/v6/channels/" + channelId + "/messages?&limit=" + limit
            : "https://discordapp.com/api/v6/channels/" + channelId + "/messages?&" + (before ? "before" : "after") + "=" + messageId + "&limit=" + limit;
         HttpResponse<JsonNode> response = Unirest.get(link).header("authorization", api.getToken()).asJson();
         api.checkResponse(response);
         api.checkRateLimit(response, RateLimitType.UNKNOWN, nullptr, nullptr);
    JSONArray messages = ((JsonNode)response.getBody()).getArray();

         for (int i = 0; i < messages.length(); i++) {
    JSONObject messageJson = messages.getJSONObject(i);
    std::string id = messageJson.getString("id");
    Message message = api.getMessageById(id);
            if (message == nullptr) {
               message = std::make_shared<ImplMessage>(messageJson, api, nullptr);
            }

            if (this.newestMessage == nullptr || message.compareTo(this.newestMessage) > 0) {
               this.newestMessage = message;
            }

            if (this.oldestMessage == nullptr || message.compareTo(this.oldestMessage) < 0) {
               this.oldestMessage = message;
            }

            this.messages.put(id, message);
         }

         return messages.length();
      }
   }

    Message getMessageById(const std::string& id) {
      return this.messages.get(id);
   }

   public Iterator<Message> iterator() {
      return this.getMessages().iterator();
   }

   public Collection<Message> getMessages() {
      return Collections.unmodifiableCollection(this.messages.values());
   }

    Message getNewestMessage() {
      if (this.newestMessage != nullptr) {
         return this.newestMessage;
      } else {
    Message newestMessage = nullptr;

         for (Message message : this.messages.values()) {
            if (newestMessage == nullptr) {
               newestMessage = message;
            } else if (message.compareTo(newestMessage) > 0) {
               newestMessage = message;
            }
         }

    return newestMessage;
      }
   }

    Message getOldestMessage() {
      if (this.oldestMessage != nullptr) {
         return this.oldestMessage;
      } else {
    Message oldestMessage = nullptr;

         for (Message message : this.messages.values()) {
            if (oldestMessage == nullptr) {
               oldestMessage = message;
            } else if (message.compareTo(oldestMessage) < 0) {
               oldestMessage = message;
            }
         }

    return oldestMessage;
      }
   }

   public List<Message> getMessagesSorted() {
      List<Message> messages = new std::vector<>(this.messages.values());
      Collections.sort(messages);
    return messages;
   }

    void removeMessage(const std::string& id) {
      this.messages.remove(id);
      if (this.newestMessage != nullptr && this.newestMessage.getId() == id)) {
         this.newestMessage = nullptr;
      }

      if (this.oldestMessage != nullptr && this.oldestMessage.getId() == id)) {
         this.oldestMessage = nullptr;
      }
   }
}
} // namespace impl
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
