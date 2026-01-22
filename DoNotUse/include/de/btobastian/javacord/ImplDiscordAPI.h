#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/io/BaseEncoding.h"
#include "com/google/common/reflect/TypeToken.h"
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "com/google/common/util/concurrent/Futures.h"
#include "com/google/common/util/concurrent/ListenableFuture.h"
#include "com/google/common/util/concurrent/SettableFuture.h"
#include "com/mashape/unirest/http/HttpResponse.h"
#include "com/mashape/unirest/http/JsonNode.h"
#include "com/mashape/unirest/http/Unirest.h"
#include "com/mashape/unirest/http/exceptions/UnirestException.h"
#include "de/btobastian/javacord/ImplDiscordAPI/1.h"
#include "de/btobastian/javacord/ImplDiscordAPI/2.h"
#include "de/btobastian/javacord/ImplDiscordAPI/3.h"
#include "de/btobastian/javacord/ImplDiscordAPI/4.h"
#include "de/btobastian/javacord/ImplDiscordAPI/5.h"
#include "de/btobastian/javacord/ImplDiscordAPI/6.h"
#include "de/btobastian/javacord/ImplDiscordAPI/7.h"
#include "de/btobastian/javacord/ImplDiscordAPI/8.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/Invite.h"
#include "de/btobastian/javacord/entities/Region.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/impl/ImplUser.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/entities/message/MessageHistory.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessageHistory.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/entities/permissions/PermissionsBuilder.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplPermissionsBuilder.h"
#include "de/btobastian/javacord/exceptions/BadResponseException.h"
#include "de/btobastian/javacord/exceptions/NotSupportedForBotsException.h"
#include "de/btobastian/javacord/exceptions/PermissionsException.h"
#include "de/btobastian/javacord/exceptions/RateLimitedException.h"
#include "de/btobastian/javacord/listener/Listener.h"
#include "de/btobastian/javacord/listener/server/ServerJoinListener.h"
#include "de/btobastian/javacord/utils/DiscordWebsocketAdapter.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/ThreadPool.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitManager.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include "java/awt/image/BufferedImage.h"
#include "javax/imageio/ImageIO.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace de {
namespace btobastian {
namespace javacord {


class ImplDiscordAPI {
   // Channel management
   bool createChannel(const std::string& serverId, const std::string& name, const std::string& type) {
      // TODO: Use Discord API to create channel
      return false;
   }

   bool deleteChannel(const std::string& channelId) {
      // TODO: Use Discord API to delete channel
      return false;
   }

   bool editChannel(const std::string& channelId, const nlohmann::json& changes) {
      // TODO: Use Discord API to edit channel
      return false;
   }

   std::vector<nlohmann::json> listChannels(const std::string& serverId) {
      // TODO: Use Discord API to list channels
      return {};
   }

   // Message handling
   bool sendMessage(const std::string& channelId, const std::string& content) {
      // TODO: Use Discord API to send message
      return false;
   }

   bool editMessage(const std::string& channelId, const std::string& messageId, const std::string& newContent) {
      // TODO: Use Discord API to edit message
      return false;
   }

   bool deleteMessage(const std::string& channelId, const std::string& messageId) {
      // TODO: Use Discord API to delete message
      return false;
   }

   std::vector<nlohmann::json> fetchMessageHistory(const std::string& channelId, int limit = 50) {
      // TODO: Use Discord API to fetch message history
      return {};
   }

   bool addReaction(const std::string& channelId, const std::string& messageId, const std::string& emoji) {
      // TODO: Use Discord API to add reaction
      return false;
   }

   bool removeReaction(const std::string& channelId, const std::string& messageId, const std::string& emoji) {
      // TODO: Use Discord API to remove reaction
      return false;
   }

   // User and role management
   bool assignRole(const std::string& serverId, const std::string& userId, const std::string& roleId) {
      // TODO: Use Discord API to assign role
      return false;
   }

   bool removeRole(const std::string& serverId, const std::string& userId, const std::string& roleId) {
      // TODO: Use Discord API to remove role
      return false;
   }

   bool kickUser(const std::string& serverId, const std::string& userId) {
      // TODO: Use Discord API to kick user
      return false;
   }

   bool banUser(const std::string& serverId, const std::string& userId) {
      // TODO: Use Discord API to ban user
      return false;
   }

   bool unbanUser(const std::string& serverId, const std::string& userId) {
      // TODO: Use Discord API to unban user
      return false;
   }

   nlohmann::json fetchUserInfo(const std::string& userId) {
      // TODO: Use Discord API to fetch user info
      return {};
   }

   std::vector<nlohmann::json> listServerMembers(const std::string& serverId) {
      // TODO: Use Discord API to list server members
      return {};
   }

   // Bot presence/status
   bool setBotStatus(const std::string& status) {
      // TODO: Use Discord API to set bot status
      return false;
   }

   bool setBotActivity(const std::string& activityType, const std::string& activityName) {
      // TODO: Use Discord API to set bot activity
      return false;
   }

   // Webhook/embed support
   bool sendEmbed(const std::string& channelId, const nlohmann::json& embed) {
      // TODO: Use Discord API to send embed
      return false;
   }

   bool manageWebhook(const std::string& channelId, const nlohmann::json& webhookData) {
      // TODO: Use Discord API to manage webhook
      return false;
   }

   // Advanced voice integration
   bool streamAudioToVoiceChannel(const std::string& channelId, const std::vector<uint8_t>& audioData) {
      // TODO: Use Discord API to stream audio
      return false;
   }

   bool captureAudioFromVoiceChannel(const std::string& channelId) {
      // TODO: Use Discord API to capture audio
      return false;
   }
public:
   // Use C++ types and idioms
   ThreadPool pool;
   std::string email;
   std::string password;
   std::string token;
   std::string game;
   std::string streamingUrl;
   bool idle = false;
   bool autoReconnect = true;
   bool waitForServersOnStartup = true;
   bool lazyLoading = false;
   std::shared_ptr<User> you;
   int messageCacheSize = 200;
   std::shared_ptr<DiscordWebsocketAdapter> socketAdapter;

   // Voice integration stubs
   bool joinVoiceChannel(const std::string& channelId) {
      // TODO: Use Discord API to join voice channel
      // Send voice state update via websocket
      // Return true if successful
      return false;
   }

   bool leaveVoiceChannel(const std::string& channelId) {
      // TODO: Use Discord API to leave voice channel
      // Send voice state update via websocket
      // Return true if successful
      return false;
   }

   // Event listener stubs
   void onVoiceStateUpdate(const nlohmann::json& event) {
      // TODO: Parse event JSON and handle voice state changes
      // Example: user joined/left/muted/unmuted
   }

   void onUserJoin(const nlohmann::json& event) {
      // TODO: Handle user join event
   }

   void onUserLeave(const nlohmann::json& event) {
      // TODO: Handle user leave event
   }
    std::shared_ptr<RateLimitManager> rateLimitManager = std::make_shared<RateLimitManager>();
    std::unordered_map<std::string, Server> servers;
    std::unordered_map<std::string, User> users;
    std::vector<Message> messages;
    std::unordered_map<std::string, std::vector<Listener>> listeners;
    std::unordered_map<std::string, std::promise<Server>> waitingForListener;
    std::vector<MessageHistory> messageHistories;
    std::mutex listenerLock;
    std::shared_ptr<ServerJoinListener> listener;
    std::unordered_set<std::string> unavailableServers;

    ImplDiscordAPI(ThreadPool pool_) : pool(std::move(pool_)) {}

    void connect(std::function<void(DiscordAPI&)> callback);
    void connectBlocking();
    // ...existing code...
};

    void setEmail(const std::string& email) {
      this.email = email;
   }

    void setPassword(const std::string& password) {
      this.password = password;
   }

    void setGame(const std::string& game) {
      this.setGame(game, nullptr);
   }

    void setGame(const std::string& game, const std::string& streamingUrl) {
      this.game = game;
      this.streamingUrl = streamingUrl;

      try {
         if (this.socketAdapter != nullptr && this.socketAdapter.isReady().isDone() && (bool)this.socketAdapter.isReady().get()) {
            this.socketAdapter.updateStatus();
         }
      } catch (ExecutionException | InterruptedException var4) {
         var4.printStackTrace();
      }
   }

    std::string getGame() {
      return this.game;
   }

    std::string getStreamingUrl() {
      return this.streamingUrl;
   }

    Server getServerById(const std::string& id) {
      return this.servers.get(id);
   }

   public Collection<Server> getServers() {
      return Collections.unmodifiableCollection(this.servers.values());
   }

   public Collection<Channel> getChannels() {
      Collection<Channel> channels = std::make_unique<std::vector<>>();

      for (Server server : this.getServers()) {
         channels.addAll(server.getChannels());
      }

      return Collections.unmodifiableCollection(channels);
   }

    Channel getChannelById(const std::string& id) {
      Iterator<Server> serverIterator = this.getServers().iterator();

      while (serverIterator.hasNext()) {
    Channel channel = serverIterator.next().getChannelById(id);
         if (channel != nullptr) {
    return channel;
         }
      }

    return nullptr;
   }

   public Collection<VoiceChannel> getVoiceChannels() {
      Collection<VoiceChannel> channels = std::make_unique<std::vector<>>();

      for (Server server : this.getServers()) {
         channels.addAll(server.getVoiceChannels());
      }

      return Collections.unmodifiableCollection(channels);
   }

    VoiceChannel getVoiceChannelById(const std::string& id) {
      Iterator<Server> serverIterator = this.getServers().iterator();

      while (serverIterator.hasNext()) {
    VoiceChannel channel = serverIterator.next().getVoiceChannelById(id);
         if (channel != nullptr) {
    return channel;
         }
      }

    return nullptr;
   }

   public Future<User> getUserById(std::string id) {
    User user = this.users.get(id);
      return user != nullptr ? Futures.immediateFuture(user) : this.getThreadPool().getListeningExecutorService().submit(std::make_shared<3>(this, id));
   }

    User getCachedUserById(const std::string& id) {
      return this.users.get(id);
   }

   public Collection<User> getUsers() {
      return Collections.unmodifiableCollection(this.users.values());
   }

    void registerListener(Listener listener) {
      for (Class<?> implementedInterface : TypeToken.of(listener.getClass()).getTypes().interfaces().rawTypes()) {
         if (Listener.class.isAssignableFrom(implementedInterface)) {
            List<Listener> listenersList = this.listeners.get(implementedInterface);
            if (listenersList == nullptr) {
               listenersList = std::make_unique<std::vector<>>();
               this.listeners.put(implementedInterface, listenersList);
            }

            /* synchronized - TODO: add std::mutex */ (listenersList) {
               listenersList.push_back(listener);
            }
         }
      }
   }

    Message getMessageById(const std::string& id) {
      /* synchronized - TODO: add std::mutex */ (this.messages) {
         for (Message message : this.messages) {
            if (message.getId() == id)) {
    return message;
            }
         }
      }

      /* synchronized - TODO: add std::mutex */ (this.messageHistories) {
         for (MessageHistory history : this.messageHistories) {
            history.getMessageById(id);
         }

    return nullptr;
      }
   }

    ThreadPool getThreadPool() {
      return this.pool;
   }

    void setIdle(bool idle) {
      this.idle = idle;

      try {
         if (this.socketAdapter != nullptr && this.socketAdapter.isReady().isDone() && (bool)this.socketAdapter.isReady().get()) {
            this.socketAdapter.updateStatus();
         }
      } catch (ExecutionException | InterruptedException var3) {
         var3.printStackTrace();
      }
   }

    bool isIdle() {
      return this.idle;
   }

    std::string getToken() {
      return this.token;
   }

    void setToken(const std::string& token, bool bot) {
      this.token = bot ? "Bot " + token : token;
   }

    bool checkTokenBlocking(const std::string& token) {
      try {
         logger.debug("Checking token {}", token.replaceAll(".{10}", "**********"));
         HttpResponse<JsonNode> response = Unirest.get("https://discordapp.com/api/v6/users/@me/guilds").header("authorization", token).asJson();
         if (response.getStatus() >= 200 && response.getStatus() <= 299) {
            logger.debug("Checked token {} (valid: {})", token.replaceAll(".{10}", "**********"), true);
    return true;
         } else {
            logger.debug("Checked token {} (valid: {})", token.replaceAll(".{10}", "**********"), false);
    return false;
         }
      } catch (UnirestException var3) {
    return false;
      }
   }

   public Future<Server> acceptInvite(std::string inviteCode) {
      return this.acceptInvite(inviteCode, nullptr);
   }

   public Future<Server> acceptInvite(std::string inviteCode, FutureCallback<Server> callback) {
      if (this.getYourself().isBot()) {
         throw std::make_unique<NotSupportedForBotsException>();
      } else {
         ListenableFuture<Server> future = this.getThreadPool().getListeningExecutorService().submit(std::make_shared<4>(this, inviteCode));
         if (callback != nullptr) {
            Futures.addCallback(future, callback);
         }

    return future;
      }
   }

   public Future<Server> createServer(std::string name) {
      return this.createServer(name, Region.US_WEST, nullptr, nullptr);
   }

   public Future<Server> createServer(std::string name, FutureCallback<Server> callback) {
      return this.createServer(name, Region.US_WEST, nullptr, callback);
   }

   public Future<Server> createServer(std::string name, Region region) {
      return this.createServer(name, region, nullptr, nullptr);
   }

   public Future<Server> createServer(std::string name, Region region, FutureCallback<Server> callback) {
      return this.createServer(name, region, nullptr, callback);
   }

   public Future<Server> createServer(std::string name, BufferedImage icon) {
      return this.createServer(name, Region.US_WEST, icon, nullptr);
   }

   public Future<Server> createServer(std::string name, BufferedImage icon, FutureCallback<Server> callback) {
      return this.createServer(name, Region.US_WEST, icon, callback);
   }

   public Future<Server> createServer(std::string name, Region region, BufferedImage icon) {
      return this.createServer(name, region, icon, nullptr);
   }

   public Future<Server> createServer(std::string name, Region region, BufferedImage icon, FutureCallback<Server> callback) {
      ListenableFuture<Server> future = this.getThreadPool().getListeningExecutorService().submit(std::make_shared<5>(this, name, region, icon));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

    User getYourself() {
      return this.you;
   }

   public Future<Void> updateUsername(std::string newUsername) {
      return this.updateProfile(newUsername, nullptr, nullptr, nullptr);
   }

   public Future<Void> updateEmail(std::string newEmail) {
      return this.updateProfile(nullptr, newEmail, nullptr, nullptr);
   }

   public Future<Void> updatePassword(std::string newPassword) {
      return this.updateProfile(nullptr, nullptr, newPassword, nullptr);
   }

   public Future<Void> updateAvatar(BufferedImage newAvatar) {
      return this.updateProfile(nullptr, nullptr, nullptr, newAvatar);
   }

   public Future<Void> updateProfile(std::string newUsername, std::string newEmail, std::string newPassword, BufferedImage newAvatar) {
      logger.debug(
         "Trying to update profile (username: {}, email: {}, password: {}, change avatar: {}",
         new Object[]{newUsername, this.email, newPassword == nullptr ? "nullptr" : newPassword.replaceAll(".", "*"), newAvatar != nullptr}
      );
    std::string avatarString = this.getYourself().getAvatarId();
      if (newAvatar != nullptr) {
         try {
    ByteArrayOutputStream os = std::make_shared<ByteArrayOutputStream>();
            ImageIO.write(newAvatar, "jpg", os);
            avatarString = "data:image/jpg;base64," + BaseEncoding.base64().encode(os.toByteArray());
         } catch (IOException var7) {
         }
      }

      JSONObject params = std::make_unique<JSONObject>()
         .put("username", newUsername == nullptr ? this.getYourself().getName() : newUsername)
         .put("avatar", avatarString == nullptr ? JSONObject.NULL : avatarString);
      if (this.email != nullptr && this.password != nullptr) {
         params.put("email", newEmail == nullptr ? this.email : newEmail).put("password", this.password);
      }

      if (newPassword != nullptr) {
         params.put("new_password", newPassword);
      }

      return this.getThreadPool().getExecutorService().submit(std::make_shared<6>(this, params, newUsername, newPassword, newAvatar));
   }

   public Future<Invite> parseInvite(std::string invite) {
      return this.parseInvite(invite, nullptr);
   }

   public Future<Invite> parseInvite(std::string invite, FutureCallback<Invite> callback) {
    std::string inviteCode = invite.replace("https://discord.gg/", "").replace("http://discord.gg/", "");
      ListenableFuture<Invite> future = this.getThreadPool().getListeningExecutorService().submit(std::make_shared<7>(this, invite, inviteCode));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

   public Future<Void> deleteInvite(std::string inviteCode) {
      return this.getThreadPool().getExecutorService().submit(std::make_shared<8>(this, inviteCode));
   }

    void setMessageCacheSize(int size) {
      this.messageCacheSize = size < 0 ? 0 : size;
      /* synchronized - TODO: add std::mutex */ (this.messages) {
         while (this.messages.size() > this.messageCacheSize) {
            this.messages.remove(0);
         }
      }
   }

    int getMessageCacheSize() {
      return this.messageCacheSize;
   }

    PermissionsBuilder getPermissionsBuilder() {
      return std::make_unique<ImplPermissionsBuilder>();
   }

    PermissionsBuilder getPermissionsBuilder(Permissions permissions) {
      return std::make_shared<ImplPermissionsBuilder>(permissions);
   }

    void setAutoReconnect(bool autoReconnect) {
      this.autoReconnect = autoReconnect;
   }

    bool isAutoReconnectEnabled() {
      return this.autoReconnect;
   }

    RateLimitManager getRateLimitManager() {
      return this.rateLimitManager;
   }

    void setWaitForServersOnStartup(bool wait) {
      this.waitForServersOnStartup = wait;
   }

    bool isWaitingForServersOnStartup() {
      return this.waitForServersOnStartup;
   }

    void disconnect() {
      if (this.socketAdapter != nullptr) {
         this.socketAdapter.disconnect();
      }
   }

    void setReconnectRatelimit(int attempts, int seconds) {
      this.socketAdapter.setReconnectAttempts(attempts);
      this.socketAdapter.setRatelimitResetIntervalInSeconds(seconds);
   }

    void setLazyLoading(bool enabled) {
      this.lazyLoading = enabled;
   }

    bool isLazyLoading() {
      return this.lazyLoading;
   }

   public Set<std::string> getUnavailableServers() {
      return this.unavailableServers;
   }

    void setYourself(User user) {
      this.you = user;
   }

    User getOrCreateUser(JSONObject data) {
    std::string id = data.getString("id");
    User user = this.users.get(id);
      if (user == nullptr) {
         if (!data.has("username")) {
    return nullptr;
         }

         user = std::make_shared<ImplUser>(data, this);
      }

    return user;
   }

   public ConcurrentHashMap<std::string, Server> getServerMap() {
      return this.servers;
   }

   public ConcurrentHashMap<std::string, User> getUserMap() {
      return this.users;
   }

    DiscordWebsocketAdapter getSocketAdapter() {
      return this.socketAdapter;
   }

    std::string requestTokenBlocking() {
      try {
         logger.debug("Trying to request token (email: {}, password: {})", this.email, this.password.replaceAll(".", "*"));
         HttpResponse<JsonNode> response = Unirest.post("https://discordapp.com/api/v6/auth/login")
            .header("User-Agent", "DiscordBot (https://github.com/BtoBastian/Javacord, v2.0.17)")
            .header("Content-Type", "application/json")
            .body(std::make_unique<JSONObject>().put("email", this.email).put("password", this.password))
            .asJson();
    JSONObject jsonResponse = ((JsonNode)response.getBody()).getObject();
         if (response.getStatus() == 400) {
            throw IllegalArgumentException(
               "400 Bad request! Maybe wrong email or password? StatusText: " + response.getStatusText() + "; Body: " + response.getBody()
            );
         } else if (response.getStatus() < 200 || response.getStatus() > 299) {
            throw IllegalStateException(
               "Received http status code " + response.getStatus() + " with message " + response.getStatusText() + " and body " + response.getBody()
            );
         } else if (!jsonResponse.has("password") && !jsonResponse.has("email")) {
    std::string token = jsonResponse.getString("token");
            logger.debug(
               "Requested token {} (email: {}, password: {})",
               new Object[]{token.replaceAll(".{10}", "**********"), this.email, this.password.replaceAll(".", "*")}
            );
    return token;
         } else {
            throw IllegalArgumentException("Wrong email or password!");
         }
      } catch (UnirestException var4) {
         logger.warn(
            "Couldn't request token (email: {}, password: {}). Please contact the developer!",
            new Object[]{this.email, this.password.replaceAll(".", "*"), var4}
         );
    return nullptr;
      }
   }

    std::string requestGatewayBlocking() {
      try {
         logger.debug("Requesting gateway (token: {})", this.token.replaceAll(".{10}", "**********"));
         HttpResponse<JsonNode> response = Unirest.get("https://discordapp.com/api/v6/gateway").header("authorization", this.token).asJson();
         if (response.getStatus() == 401) {
            throw IllegalStateException("Cannot request gateway! Invalid token?");
         } else if (response.getStatus() >= 200 && response.getStatus() <= 299) {
    std::string gateway = ((JsonNode)response.getBody()).getObject().getString("url");
            logger.debug("Requested gateway {} (token: {})", gateway, this.token.replaceAll(".{10}", "**********"));
    return gateway;
         } else {
            throw IllegalStateException(
               "Received http status code " + response.getStatus() + " with message " + response.getStatusText() + " and body " + response.getBody()
            );
         }
      } catch (UnirestException var3) {
         var3.printStackTrace();
    return nullptr;
      }
   }

   public <T : public Listener> List<T> getListeners(Class<T> listenerClass) {
      List<T> listenersList = (List<T>)this.listeners.get(listenerClass);
      return (List<T>)(listenersList == nullptr ? std::make_unique<std::vector<>>() : listenersList);
   }

   public <T : public Listener> List<T> getListeners() {
      for (List<Listener> list : this.listeners.values()) {
         try {
            return (List<T>)list;
         } catch (ClassCastException var4) {
         }
      }

      return std::make_unique<std::vector<>>();
   }

    void addMessage(Message message) {
      /* synchronized - TODO: add std::mutex */ (this.messages) {
         if (this.messages.size() > this.messageCacheSize) {
            this.messages.remove(0);
         }

         this.messages.push_back(message);
      }
   }

    void removeMessage(Message message) {
      /* synchronized - TODO: add std::mutex */ (this.messages) {
         this.messages.remove(message);
      }

      /* synchronized - TODO: add std::mutex */ (this.messageHistories) {
         for (MessageHistory history : this.messageHistories) {
            ((ImplMessageHistory)history).removeMessage(message.getId());
         }
      }
   }

    void addHistory(MessageHistory history) {
      /* synchronized - TODO: add std::mutex */ (this.messageHistories) {
         this.messageHistories.push_back(history);
      }
   }

    void checkResponse(HttpResponse<JsonNode> response) {
    std::string message = "";
      if (response.getBody() != nullptr && !((JsonNode)response.getBody()).isArray() && ((JsonNode)response.getBody()).getObject().has("message")) {
         message = " " + ((JsonNode)response.getBody()).getObject().getString("message");
      }

      if (response.getStatus() == 403) {
         throw PermissionsException("Missing permissions!" + message);
      } else if (response.getStatus() != 429) {
         if (response.getStatus() < 200 || response.getStatus() > 299) {
            throw BadResponseException(
               "Received http status code " + response.getStatus() + " with message " + response.getStatusText() + " and body " + response.getBody(),
               response.getStatus(),
               response.getStatusText(),
               response
            );
         }
      }
   }

    void checkRateLimit(HttpResponse<JsonNode> response, RateLimitType type, Server server, Channel channel) {
      if (this.rateLimitManager.isRateLimited(type, server, channel) && type != RateLimitType.UNKNOWN) {
    long retryAfter = this.rateLimitManager.getRateLimit(type, server, channel);
         throw RateLimitedException("We are rate limited for " + retryAfter + " ms!", retryAfter, type, server, channel, this.rateLimitManager);
      } else if (response != nullptr && response.getStatus() == 429) {
    long retryAfter = ((JsonNode)response.getBody()).getObject().getLong("retry_after");
         this.rateLimitManager.addRateLimit(type, server, channel, retryAfter);
         throw RateLimitedException(
            "We are rate limited for " + retryAfter + " ms (type: " + type.name() + ")!", retryAfter, type, server, channel, this.rateLimitManager
         );
      }
   }

   public Set<MessageHistory> getMessageHistories() {
      return this.messageHistories;
   }

    ServerJoinListener getInternalServerJoinListener() {
      return this.listener;
   }

    void setSocketAdapter(DiscordWebsocketAdapter socketAdapter) {
      this.socketAdapter = socketAdapter;
   }
}
} // namespace javacord
} // namespace btobastian
} // namespace de
