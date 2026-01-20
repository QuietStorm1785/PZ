#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "com/google/common/util/concurrent/Futures.h"
#include "com/google/common/util/concurrent/ListenableFuture.h"
#include "com/mashape/unirest/http/Unirest.h"
#include "com/mashape/unirest/http/exceptions/UnirestException.h"
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/InviteBuilder.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/1.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/10.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/11.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/12.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/2.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/3.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/4.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/5.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/6.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/7.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/8.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel/9.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/entities/message/MessageHistory.h"
#include "de/btobastian/javacord/entities/message/embed/EmbedBuilder.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplPermissions.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/SnowflakeUtil.h"
#include "org/json/JSONArray.h"
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


class ImplChannel {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplChannel.class);
    static const Permissions emptyPermissions = std::make_shared<ImplPermissions>(0, 0);
    const ImplDiscordAPI api;
    const std::string id;
    std::string name;
    std::string topic = nullptr;
    std::string parentId = nullptr;
    int position;
    const ImplServer server;
   private const ConcurrentHashMap<std::string, Permissions> overwrittenPermissions = std::make_unique<ConcurrentHashMap<>>();

    public ImplChannel(JSONObject data, ImplServer server, ImplDiscordAPI api) {
      this.api = api;
      this.server = server;
      this.id = data.getString("id");
      this.name = data.getString("name");

      try {
         this.topic = data.getString("topic");
      } catch (JSONException var12) {
      }

      this.position = data.getInt("position");
      if (data.has("parent_id") && !data.isNull("parent_id")) {
         this.parentId = data.getString("parent_id");
      }

    JSONArray permissionOverwrites = data.getJSONArray("permission_overwrites");

      for (int i = 0; i < permissionOverwrites.length(); i++) {
    JSONObject permissionOverwrite = permissionOverwrites.getJSONObject(i);
    std::string id = permissionOverwrite.getString("id");
    int allow = permissionOverwrite.getInt("allow");
    int deny = permissionOverwrite.getInt("deny");
    std::string type = permissionOverwrite.getString("type");
         if (type == "role")) {
    Role role = server.getRoleById(id);
            if (role != nullptr) {
               ((ImplRole)role).setOverwrittenPermissions(this, std::make_shared<ImplPermissions>(allow, deny));
            }
         }

         if (type == "member")) {
            this.overwrittenPermissions.put(id, std::make_shared<ImplPermissions>(allow, deny));
         }
      }

      server.addChannel(this);
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

    std::string getTopic() {
      return this.topic;
   }

    int getPosition() {
      return this.position;
   }

    Server getServer() {
      return this.server;
   }

   public Future<Void> delete() {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<1>(this));
   }

    void type() {
      try {
         logger.debug("Sending typing state in channel {}", this);
         Unirest.post("https://discordapp.com/api/v6/channels/" + this.id + "/typing").header("authorization", this.api.getToken()).asJson();
         logger.debug("Sent typing state in channel {}", this);
      } catch (UnirestException var2) {
         logger.warn("Couldn't send typing state in channel {}. Please contact the developer!", this, var2);
      }
   }

    InviteBuilder getInviteBuilder() {
      return std::make_shared<ImplInviteBuilder>(this, this.api);
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
      ListenableFuture<Message> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<2>(this, content, tts, embed, nonce, this));
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
      ListenableFuture<Message> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<3>(this, file, comment, this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

   public Future<Message> sendFile(InputStream inputStream, std::string filename, std::string comment) {
      return this.sendFile(inputStream, filename, comment, nullptr);
   }

   public Future<Message> sendFile(InputStream inputStream, std::string filename, std::string comment, FutureCallback<Message> callback) {
      ListenableFuture<Message> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<4>(this, comment, inputStream, filename, this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

    Permissions getOverwrittenPermissions(User user) {
    Permissions permissions = this.overwrittenPermissions.get(user.getId());
    return permissions = = nullptr ? emptyPermissions : permissions;
   }

    Permissions getOverwrittenPermissions(Role role) {
      return role.getOverwrittenPermissions(this);
   }

   public Future<Void> updateOverwrittenPermissions(Role role, Permissions permissions) {
      return this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<5>(this, role, permissions));
   }

   public Future<Void> updateOverwrittenPermissions(User user, Permissions permissions) {
      return this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<6>(this, user, permissions));
   }

   public Future<Void> deleteOverwrittenPermissions(Role role) {
      return this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<7>(this, role));
   }

   public Future<Void> deleteOverwrittenPermissions(User user) {
      return this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<8>(this, user));
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

   public Future<Void> updateName(std::string newName) {
      return this.update(newName, this.getTopic(), this.getPosition());
   }

   public Future<Void> updateTopic(std::string newTopic) {
      return this.update(this.getName(), newTopic, this.getPosition());
   }

   public Future<Void> updatePosition(int newPosition) {
      return this.update(this.getName(), this.getTopic(), newPosition);
   }

   public Future<Void> update(std::string newName, std::string newTopic, int newPosition) {
    JSONObject params = std::make_shared<JSONObject>().put("name", newName).put("topic", newTopic).put("position", newPosition);
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<9>(this, newName, newTopic, newPosition, params));
   }

    std::string getMentionTag() {
      return "<#" + this.getId() + ">";
   }

   public Future<Void> bulkDelete(std::string... messages) {
      return this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<10>(this, messages));
   }

   public Future<Void> bulkDelete(Message... messages) {
      std::string[] messageIds = new std::string[messages.length];

      for (int i = 0; i < messages.length; i++) {
         messageIds[i] = messages[i].getId();
      }

      return this.bulkDelete(messageIds);
   }

   public Future<Message> getMessageById(std::string messageId) {
    Message message = this.api.getMessageById(messageId);
      return message != nullptr ? Futures.immediateFuture(message) : this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<11>(this, messageId));
   }

   private Future<MessageHistory> getMessageHistory(std::string messageId, boolean before, int limit, FutureCallback<MessageHistory> callback) {
      ListenableFuture<MessageHistory> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<12>(this, messageId, before, limit));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

    void setName(const std::string& name) {
      this.name = name;
   }

    void setTopic(const std::string& topic) {
      this.topic = topic;
   }

    void setPosition(int position) {
      this.position = position;
   }

    void setOverwrittenPermissions(User user, Permissions permissions) {
      this.overwrittenPermissions.put(user.getId(), permissions);
   }

    void removeOverwrittenPermissions(User user) {
      this.overwrittenPermissions.remove(user.getId());
   }

    std::string getParentId() {
      return this.parentId;
   }

    void setParentId(const std::string& parentId) {
      this.parentId = parentId;
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
