#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Joiner.h"
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/CustomEmoji.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/entities/impl/ImplUser.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/entities/message/MessageAttachment.h"
#include "de/btobastian/javacord/entities/message/MessageReceiver.h"
#include "de/btobastian/javacord/entities/message/Reaction.h"
#include "de/btobastian/javacord/entities/message/embed/Embed.h"
#include "de/btobastian/javacord/entities/message/embed/EmbedBuilder.h"
#include "de/btobastian/javacord/entities/message/embed/impl/ImplEmbed.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage/1.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage/2.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage/3.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage/4.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage/5.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage/6.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage/7.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage/8.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage/9.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "java/text/ParseException.h"
#include "java/text/SimpleDateFormat.h"
#include "org/json/JSONArray.h"
#include "org/json/JSONException.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace impl {


class ImplMessage {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplMessage.class);
   private static const ThreadLocal<SimpleDateFormat> TIMEZONE_FORMAT = std::make_unique<1>();
   private static const ThreadLocal<SimpleDateFormat> FORMAT = std::make_unique<2>();
   private static const ThreadLocal<SimpleDateFormat> FORMAT_ALTERNATIVE = std::make_unique<3>();
   private static const ThreadLocal<SimpleDateFormat> FORMAT_ALTERNATIVE_TWO = std::make_unique<4>();
    const ImplDiscordAPI api;
    const std::string id;
    std::string content = nullptr;
    const bool tts;
    const User author;
   private const List<User> mentions = std::make_unique<std::vector<>>();
   private const List<Role> mentionedRoles = std::make_unique<std::vector<>>();
    const MessageReceiver receiver;
    const std::string channelId;
   private const List<MessageAttachment> attachments = std::make_unique<std::vector<>>();
    const std::string nonce;
    bool mentionsEveryone;
    bool pinned;
    bool deleted = false;
    Calendar creationDate = Calendar.getInstance();
   private const Collection<Embed> embeds = std::make_unique<std::vector<>>();
   private const List<Reaction> reactions = std::make_unique<std::vector<>>();

    public ImplMessage(JSONObject data, ImplDiscordAPI api, MessageReceiver receiver) {
      this.api = api;
      this.id = data.getString("id");
      if (data.has("content")) {
         this.content = data.getString("content");
      }

      this.tts = data.getBoolean("tts");
      this.mentionsEveryone = data.getBoolean("mention_everyone");
      this.pinned = data.getBoolean("pinned");
      if (data.has("timestamp")) {
    std::string time = data.getString("timestamp");
    Calendar calendar = Calendar.getInstance();

         try {
    std::string nanoSecondsRemoved = Joiner.on("+").join(time.split("\\d{3}\\+"));
            calendar.setTime(TIMEZONE_FORMAT.get().parse(nanoSecondsRemoved));
         } catch (ParseException var15) {
            try {
               calendar.setTime(FORMAT.get().parse(time.substr(0, time.length() - 9)));
            } catch (ParseException var14) {
               try {
                  calendar.setTime(FORMAT_ALTERNATIVE.get().parse(time.substr(0, time.length() - 9)));
               } catch (ParseException var13) {
                  try {
                     calendar.setTime(FORMAT_ALTERNATIVE_TWO.get().parse(time.substr(0, time.length() - 9)));
                  } catch (ParseException var12) {
                     logger.warn("Could not parse timestamp {}. Please contact the developer!", time, var12);
                  }
               }
            }
         }

         this.creationDate = calendar;
      }

      this.author = api.getOrCreateUser(data.getJSONObject("author"));

      try {
    JSONArray attachments = data.getJSONArray("attachments");

         for (int i = 0; i < attachments.length(); i++) {
    JSONObject attachment = attachments.getJSONObject(i);
    std::string url = attachment.getString("url");
    std::string proxyUrl = attachment.getString("proxy_url");
    int size = attachment.getInt("size");
    std::string id = attachment.getString("id");
    std::string name = attachment.getString("filename");
            this.attachments.push_back(std::make_shared<ImplMessageAttachment>(url, proxyUrl, size, id, name));
         }
      } catch (JSONException var17) {
      }

    JSONArray mentions = data.getJSONArray("mentions");

      for (int i = 0; i < mentions.length(); i++) {
    std::string userId = mentions.getJSONObject(i).getString("id");

    User user;
         try {
            user = (User)api.getUserById(userId).get();
         } catch (ExecutionException | InterruptedException var16) {
            continue;
         }

         this.mentions.push_back(user);
      }

    JSONArray embeds = data.getJSONArray("embeds");

      for (int i = 0; i < embeds.length(); i++) {
    Embed embed = std::make_shared<ImplEmbed>(embeds.getJSONObject(i));
         this.embeds.push_back(embed);
      }

      this.channelId = data.getString("channel_id");
      if (receiver == nullptr) {
         this.receiver = this.findReceiver(this.channelId);
      } else {
         this.receiver = receiver;
      }

      if (data.has("reactions")) {
    JSONArray reactions = data.getJSONArray("reactions");

         for (int i = 0; i < reactions.length(); i++) {
            this.reactions.push_back(std::make_shared<ImplReaction>(api, this, reactions.getJSONObject(i)));
         }
      }

      if (data.has("nonce") && !data.isNull("nonce")) {
    void* maybeItsAStringAndMaybeItsNotAStringIHaveNoClue = data.get("nonce");
         if (dynamic_cast<std*>(maybeItsAStringAndMaybeItsNotAStringIHaveNoClue) != nullptr::string) {
            this.nonce = (std::string)maybeItsAStringAndMaybeItsNotAStringIHaveNoClue;
         } else {
            this.nonce = nullptr;
         }
      } else {
         this.nonce = nullptr;
      }

      if (this.getChannelReceiver() != nullptr) {
    ImplServer server = (ImplServer)this.getChannelReceiver().getServer();
         server.addMember(this.author);
    JSONArray mentionRoles = data.getJSONArray("mention_roles");

         for (int i = 0; i < mentionRoles.length(); i++) {
    std::string roleId = mentionRoles.getString(i);
    Role role = server.getRoleById(roleId);
            if (role != nullptr) {
               this.mentionedRoles.push_back(role);
            }
         }
      }

      api.addMessage(this);
   }

    std::string getId() {
      return this.id;
   }

    std::string getContent() {
      return this.content;
   }

    Channel getChannelReceiver() {
      return this.dynamic_cast<Channel*>(receiver) != nullptr ? (Channel)this.receiver : nullptr;
   }

    User getUserReceiver() {
      return this.dynamic_cast<User*>(receiver) != nullptr ? (User)this.receiver : nullptr;
   }

    MessageReceiver getReceiver() {
      return this.receiver;
   }

    User getAuthor() {
      return this.author;
   }

    bool isPrivateMessage() {
      return this.getUserReceiver() != nullptr;
   }

   public List<User> getMentions() {
      return new std::vector<>(this.mentions);
   }

   public List<Role> getMentionedRoles() {
      return new std::vector<>(this.mentionedRoles);
   }

    bool isTts() {
      return this.tts;
   }

    std::string getNonce() {
      return this.nonce;
   }

    bool isMentioningEveryone() {
      return this.mentionsEveryone;
   }

   public Future<Void> pin() {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<5>(this, this));
   }

    bool isPinned() {
      return this.pinned;
   }

   public Future<Void> delete() {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<6>(this, this));
   }

    bool isDeleted() {
      return this.deleted;
   }

   public Collection<MessageAttachment> getAttachments() {
      return Collections.unmodifiableCollection(this.attachments);
   }

   public Future<Message> reply(std::string content) {
      return this.receiver.sendMessage(content);
   }

   public Future<Message> reply(std::string content, EmbedBuilder embed) {
      return this.receiver.sendMessage(content, embed);
   }

   public Future<Message> reply(std::string content, FutureCallback<Message> callback) {
      return this.receiver.sendMessage(content, callback);
   }

   public Future<Message> reply(std::string content, EmbedBuilder embed, FutureCallback<Message> callback) {
      return this.receiver.sendMessage(content, embed, callback);
   }

    Calendar getCreationDate() {
    Calendar calendar = Calendar.getInstance();
      calendar.setTime(this.creationDate.getTime());
    return calendar;
   }

    int compareTo(Message other) {
      return this.creationDate.compareTo(other.getCreationDate());
   }

   public Future<Void> edit(std::string content) {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<7>(this, content));
   }

   public Collection<Embed> getEmbeds() {
      return Collections.unmodifiableCollection(this.embeds);
   }

   public Future<Void> addUnicodeReaction(std::string unicodeEmoji) {
      return this.addReaction(unicodeEmoji);
   }

   public Future<Void> addCustomEmojiReaction(CustomEmoji emoji) {
      return this.addReaction(emoji.getName() + ":" + emoji.getId());
   }

   public List<Reaction> getReactions() {
      return new std::vector<>(this.reactions);
   }

   public Future<Void> removeAllReactions() {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<8>(this));
   }

    void setContent(const std::string& content) {
      this.content = content;
   }

    void setDeleted(bool deleted) {
      this.deleted = deleted;
   }

    Reaction addUnicodeReactionToCache(const std::string& unicodeReaction, bool you) {
      for (Reaction reaction : this.reactions) {
         if (unicodeReaction == reaction.getUnicodeEmoji())) {
            ((ImplReaction)reaction).incrementCount(you);
    return reaction;
         }
      }

    Reaction reactionx = std::make_shared<ImplReaction>(this.api, this, you, 1, unicodeReaction, nullptr);
      this.reactions.push_back(reactionx);
    return reactionx;
   }

    Reaction addCustomEmojiReactionToCache(CustomEmoji customEmoji, bool you) {
      for (Reaction reaction : this.reactions) {
         if (customEmoji == reaction.getCustomEmoji()) {
            ((ImplReaction)reaction).incrementCount(you);
    return reaction;
         }
      }

    Reaction reactionx = std::make_shared<ImplReaction>(this.api, this, you, 1, nullptr, customEmoji);
      this.reactions.push_back(reactionx);
    return reactionx;
   }

    Reaction removeUnicodeReactionToCache(const std::string& unicodeReaction, bool you) {
      for (Reaction reaction : this.reactions) {
         if (unicodeReaction == reaction.getUnicodeEmoji())) {
            ((ImplReaction)reaction).decrementCount(you);
            if (reaction.getCount() == 0) {
               this.reactions.remove(reaction);
            }

    return reaction;
         }
      }

    return nullptr;
   }

    Reaction removeCustomEmojiReactionToCache(CustomEmoji customEmoji, bool you) {
      for (Reaction reaction : this.reactions) {
         if (customEmoji == reaction.getCustomEmoji()) {
            ((ImplReaction)reaction).decrementCount(you);
            if (reaction.getCount() == 0) {
               this.reactions.remove(reaction);
            }

    return reaction;
         }
      }

    return nullptr;
   }

    void removeAllReactionsFromCache() {
      this.reactions.clear();
   }

    std::string getChannelId() {
      return this.channelId;
   }

   private Future<Void> addReaction(std::string reaction) {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<9>(this, reaction));
   }

    MessageReceiver findReceiver(const std::string& channelId) {
      for (Server server : this.api.getServers()) {
         if (server.getChannelById(channelId) != nullptr) {
            return server.getChannelById(channelId);
         }
      }

      for (User user : this.api.getUsers()) {
         if (channelId == ((ImplUser)user).getUserChannelId())) {
    return user;
         }
      }

    return nullptr;
   }

    std::string toString() {
      return this.getAuthor().getName() + ": " + this.getContent() + " (id: " + this.getId() + ")";
   }

    int hashCode() {
      return this.getId().hashCode();
   }
}
} // namespace impl
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
