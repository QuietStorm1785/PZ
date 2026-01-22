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
#include "com/mashape/unirest/http/HttpResponse.h"
#include "com/mashape/unirest/http/JsonNode.h"
#include "com/mashape/unirest/http/Unirest.h"
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/CustomEmoji.h"
#include "de/btobastian/javacord/entities/Invite.h"
#include "de/btobastian/javacord/entities/Region.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/UserStatus.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/1.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/10.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/11.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/12.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/13.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/14.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/15.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/2.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/3.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/4.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/5.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/6.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/7.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/8.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/9.h"
#include "de/btobastian/javacord/entities/permissions/Ban.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/SnowflakeUtil.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include "java/awt/image/BufferedImage.h"
#include "java/net/MalformedURLException.h"
#include "java/net/URL.h"
#include "org/json/JSONArray.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplServer.class);
    const ImplDiscordAPI api;
   private const ConcurrentHashMap<std::string, Channel> channels = std::make_unique<ConcurrentHashMap<>>();
   private const ConcurrentHashMap<std::string, VoiceChannel> voiceChannels = std::make_unique<ConcurrentHashMap<>>();
   private const ConcurrentHashMap<std::string, User> members = std::make_unique<ConcurrentHashMap<>>();
   private const ConcurrentHashMap<std::string, Role> roles = std::make_unique<ConcurrentHashMap<>>();
   private const ConcurrentHashMap<std::string, CustomEmoji> customEmojis = std::make_unique<ConcurrentHashMap<>>();
   private const ConcurrentHashMap<std::string, std::string> nicknames = std::make_unique<ConcurrentHashMap<>>();
    const std::string id;
    std::string name;
    Region region;
    int memberCount;
    const bool large;
    std::string ownerId;
    std::string iconHash;

    public ImplServer(JSONObject data, ImplDiscordAPI api) {
      this.api = api;
      this.name = data.getString("name");
      this.id = data.getString("id");
      this.region = Region.getRegionByKey(data.getString("region"));
      this.memberCount = data.getInt("member_count");
      this.large = data.getBoolean("large");
      this.ownerId = data.getString("owner_id");
    JSONArray roles = data.getJSONArray("roles");

      for (int i = 0; i < roles.length(); i++) {
    std::make_shared<ImplRole>();
      }

    JSONArray emojis = data.getJSONArray("emojis");

      for (int i = 0; i < emojis.length(); i++) {
    std::make_shared<ImplCustomEmoji>();
      }

    JSONArray channels = data.getJSONArray("channels");

      for (int i = 0; i < channels.length(); i++) {
    JSONObject channelJson = channels.getJSONObject(i);
    int type = channelJson.getInt("type");
         if (type == 0) {
    std::make_shared<ImplChannel>();
         }

         if (type == 2) {
    std::make_shared<ImplVoiceChannel>();
         }
      }

    JSONArray members = std::make_shared<JSONArray>();
      if (data.has("members")) {
         members = data.getJSONArray("members");
      }

      this.addMembers(members);
      if (!api.isLazyLoading() && this.isLarge() && this.getMembers().size() < this.getMemberCount()) {
         JSONObject requestGuildMembersPacket = std::make_unique<JSONObject>()
            .put("op", 8)
            .put("d", std::make_unique<JSONObject>().put("guild_id", this.getId()).put("query", "").put("limit", 0));
         logger.debug("Sending request guild members packet for server {}", this);
         api.getSocketAdapter().getWebSocket().sendText(requestGuildMembersPacket);
      }

    JSONArray voiceStates = std::make_shared<JSONArray>();
      if (data.has("voice_states")) {
         voiceStates = data.getJSONArray("voice_states");
      }

      for (int i = 0; i < voiceStates.length(); i++) {
    JSONObject voiceState = voiceStates.getJSONObject(i);
         if (voiceState.has("user_id") && !voiceState.isNull("user_id")) {
    User user = api.getCachedUserById(voiceState.getString("user_id"));
            if (user != nullptr && voiceState.has("channel_id") && !voiceState.isNull("channel_id")) {
    VoiceChannel channel = this.getVoiceChannelById(voiceState.getString("channel_id"));
               if (channel != nullptr) {
                  ((ImplVoiceChannel)channel).addConnectedUser(user);
                  ((ImplUser)user).setVoiceChannel(channel);
               }
            }
         }
      }

    JSONArray presences = std::make_shared<JSONArray>();
      if (data.has("presences")) {
         presences = data.getJSONArray("presences");
      }

      for (int ix = 0; ix < presences.length(); ix++) {
    JSONObject presence = presences.getJSONObject(ix);
    User user = api.getOrCreateUser(presence.getJSONObject("user"));
         if (user != nullptr
            && presence.has("game")
            && !presence.isNull("game")
            && presence.getJSONObject("game").has("name")
            && !presence.getJSONObject("game").isNull("name")) {
            ((ImplUser)user).setGame(presence.getJSONObject("game").getString("name"));
         }

         if (user != nullptr && presence.has("status") && !presence.isNull("status")) {
    UserStatus status = UserStatus.fromString(presence.getString("status"));
            ((ImplUser)user).setStatus(status);
         }
      }

      this.iconHash = data.isNull("icon") ? nullptr : data.getString("icon");
      api.getServerMap().put(this.id, this);
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

   public Future<Void> delete() {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<1>(this));
   }

   public Future<Void> leave() {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<2>(this));
   }

    Channel getChannelById(const std::string& id) {
      return this.channels.get(id);
   }

   public Collection<Channel> getChannels() {
      return Collections.unmodifiableCollection(this.channels.values());
   }

    VoiceChannel getVoiceChannelById(const std::string& id) {
      return this.voiceChannels.get(id);
   }

   public Collection<VoiceChannel> getVoiceChannels() {
      return Collections.unmodifiableCollection(this.voiceChannels.values());
   }

    User getMemberById(const std::string& id) {
      return this.members.get(id);
   }

   public Collection<User> getMembers() {
      return Collections.unmodifiableCollection(this.members.values());
   }

    bool isMember(User user) {
      return this.isMember(user.getId());
   }

    bool isMember(const std::string& userId) {
      return this.members.containsKey(userId);
   }

   public Collection<Role> getRoles() {
      return Collections.unmodifiableCollection(this.roles.values());
   }

    Role getRoleById(const std::string& id) {
      return this.roles.get(id);
   }

   public Future<Channel> createChannel(std::string name) {
      return this.createChannel(name, nullptr);
   }

   public Future<Channel> createChannel(std::string name, FutureCallback<Channel> callback) {
      ListenableFuture<Channel> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<3>(this, name));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

   public Future<VoiceChannel> createVoiceChannel(std::string name) {
      return this.createVoiceChannel(name, nullptr);
   }

   public Future<VoiceChannel> createVoiceChannel(std::string name, FutureCallback<VoiceChannel> callback) {
      ListenableFuture<VoiceChannel> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<4>(this, name));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

   public Future<Invite[]> getInvites() {
      return this.getInvites(nullptr);
   }

   public Future<Invite[]> getInvites(FutureCallback<Invite[]> callback) {
      ListenableFuture<Invite[]> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<5>(this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

   public Future<Void> updateRoles(User user, Role[] roles) {
      std::string[] roleIds = new std::string[roles.length];

      for (int i = 0; i < roles.length; i++) {
         roleIds[i] = roles[i].getId();
      }

      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<6>(this, roles, user, roleIds));
   }

   public Future<Void> banUser(User user) {
      return this.banUser(user.getId(), 0);
   }

   public Future<Void> banUser(std::string userId) {
      return this.banUser(userId, 0);
   }

   public Future<Void> banUser(User user, int deleteDays) {
      return this.banUser(user.getId(), deleteDays);
   }

   public Future<Void> banUser(std::string userId, int deleteDays) {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<7>(this, userId, deleteDays));
   }

   public Future<Void> unbanUser(std::string userId) {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<8>(this, userId));
   }

   public Future<Ban[]> getBans() {
      return this.getBans(nullptr);
   }

   public Future<Ban[]> getBans(FutureCallback<Ban[]> callback) {
      ListenableFuture<Ban[]> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<9>(this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

   public Future<Void> kickUser(User user) {
      return this.kickUser(user.getId());
   }

   public Future<Void> kickUser(std::string userId) {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<10>(this, userId));
   }

   public Future<Role> createRole() {
      return this.createRole(nullptr);
   }

   public Future<Role> createRole(FutureCallback<Role> callback) {
      ListenableFuture<Role> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<11>(this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

   public Future<Void> updateName(std::string newName) {
      return this.update(newName, nullptr, nullptr);
   }

   public Future<Void> updateRegion(Region newRegion) {
      return this.update(nullptr, newRegion, nullptr);
   }

   public Future<Void> updateIcon(BufferedImage newIcon) {
      return this.update(nullptr, nullptr, newIcon);
   }

   public Future<Void> update(std::string newName, Region newRegion, BufferedImage newIcon) {
    JSONObject params = std::make_shared<JSONObject>();
      if (newName == nullptr) {
         params.put("name", this.getName());
      } else {
         params.put("name", newName);
      }

      if (newRegion != nullptr) {
         params.put("region", newRegion.getKey());
      }

      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<12>(this, newName, newRegion, params));
   }

    Region getRegion() {
      return this.region;
   }

    int getMemberCount() {
      return this.memberCount;
   }

    bool isLarge() {
      return this.large;
   }

    std::string getOwnerId() {
      return this.ownerId;
   }

   public Future<User> getOwner() {
      return this.api.getUserById(this.ownerId);
   }

   public Collection<CustomEmoji> getCustomEmojis() {
      return this.customEmojis.values();
   }

    CustomEmoji getCustomEmojiById(const std::string& id) {
      return this.customEmojis.get(id);
   }

    CustomEmoji getCustomEmojiByName(const std::string& name) {
      for (CustomEmoji emoji : this.customEmojis.values()) {
         if (emoji.getName() == name)) {
    return emoji;
         }
      }

    return nullptr;
   }

    std::string getNickname(User user) {
      return this.nicknames.get(user.getId());
   }

    bool hasNickname(User user) {
      return this.nicknames.contains(user.getId());
   }

   public Future<Void> updateNickname(User user, std::string nickname) {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<13>(this, user, nickname));
   }

    URL getIconUrl() {
      if (this.iconHash == nullptr) {
    return nullptr;
      } else {
         try {
            return std::make_shared<URL>("https://cdn.discordapp.com/icons/" + this.id + "/" + this.iconHash + ".png");
         } catch (MalformedURLException var2) {
            logger.warn("Seems like the url of the icon is malformed! Please contact the developer!", var2);
    return nullptr;
         }
      }
   }

   public Future<byte[]> getIconAsByteArray() {
      return this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<14>(this));
   }

   public Future<byte[]> getIcon() {
      return this.getIcon(nullptr);
   }

   public Future<byte[]> getIcon(FutureCallback<byte[]> callback) {
      ListenableFuture<byte[]> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<15>(this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

    void setName(const std::string& name) {
      this.name = name;
   }

    void setRegion(Region region) {
      this.region = region;
   }

    void addMember(User user) {
      this.members.put(user.getId(), user);
   }

    void addMembers(JSONArray members) {
      for (int i = 0; i < members.length(); i++) {
    User member = this.api.getOrCreateUser(members.getJSONObject(i).getJSONObject("user"));
         if (members.getJSONObject(i).has("nick") && !members.getJSONObject(i).isNull("nick")) {
            this.nicknames.put(member.getId(), members.getJSONObject(i).getString("nick"));
         }

         this.members.put(member.getId(), member);
    JSONArray memberRoles = members.getJSONObject(i).getJSONArray("roles");

         for (int j = 0; j < memberRoles.length(); j++) {
    Role role = this.getRoleById(memberRoles.getString(j));
            if (role != nullptr) {
               ((ImplRole)role).addUserNoUpdate(member);
            }
         }
      }
   }

    void removeMember(User user) {
      this.members.remove(user.getId());

      for (Role role : this.getRoles()) {
         ((ImplRole)role).removeUserNoUpdate(user);
      }

      for (Channel channel : this.getChannels()) {
         ((ImplChannel)channel).removeOverwrittenPermissions(user);
      }

      for (VoiceChannel channel : this.getVoiceChannels()) {
         ((ImplVoiceChannel)channel).removeOverwrittenPermissions(user);
      }
   }

    void incrementMemberCount() {
      this.memberCount++;
   }

    void decrementMemberCount() {
      this.memberCount--;
   }

    void setMemberCount(int memberCount) {
      this.memberCount = memberCount;
   }

    void addChannel(Channel channel) {
      this.channels.put(channel.getId(), channel);
   }

    void addVoiceChannel(VoiceChannel channel) {
      this.voiceChannels.put(channel.getId(), channel);
   }

    void addRole(Role role) {
      this.roles.put(role.getId(), role);
   }

    void removeRole(Role role) {
      this.roles.remove(role.getId());
   }

    void removeChannel(Channel channel) {
      this.channels.remove(channel.getId());
   }

    void removeVoiceChannel(VoiceChannel channel) {
      this.voiceChannels.remove(channel.getId());
   }

    void addCustomEmoji(CustomEmoji emoji) {
      this.customEmojis.put(emoji.getId(), emoji);
   }

    void removeCustomEmoji(CustomEmoji emoji) {
      this.customEmojis.remove(emoji.getId());
   }

    void setOwnerId(const std::string& ownerId) {
      this.ownerId = ownerId;
   }

    void setNickname(User user, const std::string& nickname) {
      if (nickname == nullptr) {
         this.nicknames.remove(user.getId());
      } else {
         this.nicknames.put(user.getId(), nickname);
      }
   }

    std::string getIconHash() {
      return this.iconHash;
   }

    void setIconHash(const std::string& hash) {
      this.iconHash = hash;
   }

    void* createChannelBlocking(const std::string& name, bool voice) {
      logger.debug("Trying to create channel in server {} (name: {}, voice: {})", new Object[]{this, name, voice});
    JSONObject param = std::make_shared<JSONObject>().put("name", name).put("type", voice ? "voice" : "text");
      HttpResponse<JsonNode> response = Unirest.post("https://discordapp.com/api/v6/guilds/" + this.id + "/channels")
         .header("authorization", this.api.getToken())
         .header("Content-Type", "application/json")
         .body(param)
         .asJson();
      this.api.checkResponse(response);
      this.api.checkRateLimit(response, RateLimitType.UNKNOWN, this, nullptr);
      return voice
         ? std::make_shared<ImplVoiceChannel>(((JsonNode)response.getBody()).getObject(), this, this.api)
         : std::make_shared<ImplChannel>(((JsonNode)response.getBody()).getObject(), this, this.api);
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
