#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "com/google/common/util/concurrent/Futures.h"
#include "com/google/common/util/concurrent/ListenableFuture.h"
#include "com/mashape/unirest/http/HttpResponse.h"
#include "com/mashape/unirest/http/JsonNode.h"
#include "com/mashape/unirest/http/Unirest.h"
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/UserStatus.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/impl/ImplUser/1.h"
#include "de/btobastian/javacord/entities/impl/ImplUser/2.h"
#include "de/btobastian/javacord/entities/impl/ImplUser/3.h"
#include "de/btobastian/javacord/entities/impl/ImplUser/4.h"
#include "de/btobastian/javacord/entities/impl/ImplUser/5.h"
#include "de/btobastian/javacord/entities/impl/ImplUser/6.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/entities/message/MessageHistory.h"
#include "de/btobastian/javacord/entities/message/embed/EmbedBuilder.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/SnowflakeUtil.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include "java/awt/image/BufferedImage.h"
#include "java/net/MalformedURLException.h"
#include "java/net/URL.h"
#include "org/json/JSONException.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplUser {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplUser.class);
    const ImplDiscordAPI api;
    const std::string id;
    std::string name;
    std::string avatarId = nullptr;
    const void* userChannelIdLock = std::make_shared<Object>();
    std::string userChannelId = nullptr;
    std::string game = nullptr;
    const std::string discriminator;
    const bool bot;
    UserStatus status = UserStatus.OFFLINE;
    VoiceChannel voiceChannel = nullptr;

    public ImplUser(JSONObject data, ImplDiscordAPI api) {
      this.api = api;
      this.id = data.getString("id");
      if (data.has("username")) {
         this.name = data.getString("username");
      }

      try {
         this.avatarId = data.getString("avatar");
      } catch (JSONException var4) {
      }

      if (data.has("discriminator")) {
         this.discriminator = data.getString("discriminator");
      } else {
         this.discriminator = nullptr;
      }

      this.bot = data.has("bot") && data.getBoolean("bot");
      api.getUserMap().put(this.id, this);
   }

    std::string getId() {
      return this.id;
   }

    Calendar getCreationDate() {
      return SnowflakeUtil.parseDate(this.id);
   }

    std::string getName() {
      return this.name;
   }

    std::string getNickname(Server server) {
      return server.getNickname(this);
   }

    bool hasNickname(Server server) {
      return server.hasNickname(this);
   }

   public Future<Void> updateNickname(Server server, std::string nickname) {
      return server.updateNickname(this, nickname);
   }

    void type() {
      if (this.userChannelId != nullptr) {
         try {
            logger.debug("Sending typing state to user {}", this);
            HttpResponse<JsonNode> response = Unirest.post("https://discordapp.com/api/v6/channels/" + this.getUserChannelIdBlocking() + "/typing")
               .header("authorization", this.api.getToken())
               .asJson();
            this.api.checkResponse(response);
            this.api.checkRateLimit(response, RateLimitType.UNKNOWN, nullptr, nullptr);
            logger.debug("Sent typing state to user {}", this);
         } catch (Exception var2) {
            var2.printStackTrace();
         }
      }
   }

    bool isYourself() {
      return this.api.getYourself() == this;
   }

   public Future<byte[]> getAvatarAsByteArray() {
      return this.getAvatarAsByteArray(nullptr);
   }

   public Future<byte[]> getAvatarAsByteArray(FutureCallback<byte[]> callback) {
      ListenableFuture<byte[]> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<1>(this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

   public Future<BufferedImage> getAvatar() {
      return this.getAvatar(nullptr);
   }

   public Future<BufferedImage> getAvatar(FutureCallback<BufferedImage> callback) {
      ListenableFuture<BufferedImage> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<2>(this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

    URL getAvatarUrl() {
      if (this.avatarId == nullptr) {
    return nullptr;
      } else {
         try {
            return std::make_shared<URL>("https://discordapp.com/api/v6/users/" + this.id + "/avatars/" + this.avatarId + ".jpg");
         } catch (MalformedURLException var2) {
            logger.warn("Seems like the url of the avatar is malformed! Please contact the developer!", var2);
    return nullptr;
         }
      }
   }

    std::string getAvatarId() {
      return this.avatarId;
   }

   public Future<Message> sendMessage(std::string content) {
      return this.sendMessage(content, nullptr, false, nullptr, nullptr);
   }

   public Future<Message> sendMessage(std::string content, std::string nonce) {
      return this.sendMessage(content, nullptr, false, nonce, nullptr);
   }

   public Future<Message> sendMessage(std::string content, boolean tts) {
      return this.sendMessage(content, nullptr, tts, nullptr, nullptr);
   }

   public Future<Message> sendMessage(std::string content, boolean tts, std::string nonce) {
      return this.sendMessage(content, nullptr, tts, nonce, nullptr);
   }

   public Future<Message> sendMessage(std::string content, EmbedBuilder embed) {
      return this.sendMessage(content, embed, false, nullptr, nullptr);
   }

   public Future<Message> sendMessage(std::string content, EmbedBuilder embed, std::string nonce) {
      return this.sendMessage(content, embed, false, nonce, nullptr);
   }

   public Future<Message> sendMessage(std::string content, EmbedBuilder embed, boolean tts) {
      return this.sendMessage(content, embed, tts, nullptr, nullptr);
   }

   public Future<Message> sendMessage(std::string content, EmbedBuilder embed, boolean tts, std::string nonce) {
      return this.sendMessage(content, embed, tts, nonce, nullptr);
   }

   public Future<Message> sendMessage(std::string content, FutureCallback<Message> callback) {
      return this.sendMessage(content, nullptr, false, nullptr, callback);
   }

   public Future<Message> sendMessage(std::string content, std::string nonce, FutureCallback<Message> callback) {
      return this.sendMessage(content, nullptr, false, nonce, callback);
   }

   public Future<Message> sendMessage(std::string content, boolean tts, FutureCallback<Message> callback) {
      return this.sendMessage(content, nullptr, tts, nullptr, callback);
   }

   public Future<Message> sendMessage(std::string content, boolean tts, std::string nonce, FutureCallback<Message> callback) {
      return this.sendMessage(content, nullptr, tts, nonce, callback);
   }

   public Future<Message> sendMessage(std::string content, EmbedBuilder embed, FutureCallback<Message> callback) {
      return this.sendMessage(content, embed, false, nullptr, callback);
   }

   public Future<Message> sendMessage(std::string content, EmbedBuilder embed, std::string nonce, FutureCallback<Message> callback) {
      return this.sendMessage(content, embed, false, nonce, callback);
   }

   public Future<Message> sendMessage(std::string content, EmbedBuilder embed, boolean tts, FutureCallback<Message> callback) {
      return this.sendMessage(content, embed, tts, nullptr, callback);
   }

   public Future<Message> sendMessage(std::string content, EmbedBuilder embed, boolean tts, std::string nonce, FutureCallback<Message> callback) {
      ListenableFuture<Message> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<3>(this, content, tts, embed, nonce, this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

   public Future<Message> sendFile(File file) {
      return this.sendFile(file, nullptr, nullptr);
   }

   public Future<Message> sendFile(File file, FutureCallback<Message> callback) {
      return this.sendFile(file, nullptr, callback);
   }

   public Future<Message> sendFile(InputStream inputStream, std::string filename) {
      return this.sendFile(inputStream, filename, nullptr, nullptr);
   }

   public Future<Message> sendFile(InputStream inputStream, std::string filename, FutureCallback<Message> callback) {
      return this.sendFile(inputStream, filename, nullptr, callback);
   }

   public Future<Message> sendFile(File file, std::string comment) {
      return this.sendFile(file, comment, nullptr);
   }

   public Future<Message> sendFile(File file, std::string comment, FutureCallback<Message> callback) {
      ListenableFuture<Message> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<4>(this, file, comment, this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

   public Future<Message> sendFile(InputStream inputStream, std::string filename, std::string comment) {
      return this.sendFile(inputStream, filename, comment, nullptr);
   }

   public Future<Message> sendFile(InputStream inputStream, std::string filename, std::string comment, FutureCallback<Message> callback) {
      ListenableFuture<Message> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<5>(this, comment, inputStream, filename, this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

   public Collection<Role> getRoles(Server server) {
      Collection<Role> userRoles = std::make_unique<std::vector<>>();

      for (Role role : server.getRoles()) {
         if (role.getUsers().contains(this)) {
            userRoles.push_back(role);
         }
      }

    return userRoles;
   }

    std::string getGame() {
      return this.game;
   }

   public Future<MessageHistory> getMessageHistory(int limit) {
      return this.getMessageHistory(nullptr, false, limit, nullptr);
   }

   public Future<MessageHistory> getMessageHistory(int limit, FutureCallback<MessageHistory> callback) {
      return this.getMessageHistory(nullptr, false, limit, callback);
   }

   public Future<MessageHistory> getMessageHistoryBefore(Message before, int limit) {
      return this.getMessageHistory(before.getId(), true, limit, nullptr);
   }

   public Future<MessageHistory> getMessageHistoryBefore(Message before, int limit, FutureCallback<MessageHistory> callback) {
      return this.getMessageHistory(before.getId(), true, limit, callback);
   }

   public Future<MessageHistory> getMessageHistoryBefore(std::string beforeId, int limit) {
      return this.getMessageHistory(beforeId, true, limit, nullptr);
   }

   public Future<MessageHistory> getMessageHistoryBefore(std::string beforeId, int limit, FutureCallback<MessageHistory> callback) {
      return this.getMessageHistory(beforeId, true, limit, callback);
   }

   public Future<MessageHistory> getMessageHistoryAfter(Message after, int limit) {
      return this.getMessageHistory(after.getId(), false, limit, nullptr);
   }

   public Future<MessageHistory> getMessageHistoryAfter(Message after, int limit, FutureCallback<MessageHistory> callback) {
      return this.getMessageHistory(after.getId(), false, limit, callback);
   }

   public Future<MessageHistory> getMessageHistoryAfter(std::string afterId, int limit) {
      return this.getMessageHistory(afterId, false, limit, nullptr);
   }

   public Future<MessageHistory> getMessageHistoryAfter(std::string afterId, int limit, FutureCallback<MessageHistory> callback) {
      return this.getMessageHistory(afterId, false, limit, callback);
   }

    std::string getMentionTag() {
      return "<@" + this.getId() + ">";
   }

    std::string getDiscriminator() {
      return this.discriminator;
   }

    bool isBot() {
      return this.bot;
   }

    UserStatus getStatus() {
      return this.status;
   }

    void setStatus(UserStatus status) {
      this.status = status;
   }

   private Future<MessageHistory> getMessageHistory(std::string messageId, boolean before, int limit, FutureCallback<MessageHistory> callback) {
      ListenableFuture<MessageHistory> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<6>(this, messageId, before, limit));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

    void setUserChannelId(const std::string& userChannelId) {
      /* synchronized - TODO: add std::mutex */ (this.userChannelIdLock) {
         this.userChannelId = userChannelId;
      }
   }

    std::string getUserChannelIdBlocking() {
      /* synchronized - TODO: add std::mutex */ (this.userChannelIdLock) {
         if (this.userChannelId != nullptr) {
            return this.userChannelId;
         } else {
            logger.debug("Trying to get channel id of user {}", this);
            HttpResponse<JsonNode> response = Unirest.post("https://discordapp.com/api/v6/users/" + this.api.getYourself().getId() + "/channels")
               .header("authorization", this.api.getToken())
               .header("Content-Type", "application/json")
               .body(std::make_unique<JSONObject>().put("recipient_id", this.id))
               .asJson();
            this.api.checkResponse(response);
            this.api.checkRateLimit(response, RateLimitType.UNKNOWN, nullptr, nullptr);
            this.userChannelId = ((JsonNode)response.getBody()).getObject().getString("id");
            logger.debug("Got channel id of user {} (channel id: {})", this, this.userChannelId);
            return this.userChannelId;
         }
      }
   }

    std::string getUserChannelId() {
      /* synchronized - TODO: add std::mutex */ (this.userChannelIdLock) {
         return this.userChannelId;
      }
   }

    void setName(const std::string& name) {
      this.name = name;
   }

    void setGame(const std::string& game) {
      this.game = game;
   }

    void setAvatarId(const std::string& avatarId) {
      this.avatarId = avatarId;
   }

    void setVoiceChannel(VoiceChannel voiceChannel) {
      this.voiceChannel = voiceChannel;
   }

    VoiceChannel getVoiceChannel() {
      return this.voiceChannel;
   }

    std::string toString() {
      return this.getName() + " (id: " + this.getId() + ")";
   }

    int hashCode() {
      return this.getId().hashCode();
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
