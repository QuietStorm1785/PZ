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
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/CustomEmoji.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/entities/message/Reaction.h"
#include "de/btobastian/javacord/entities/message/impl/ImplReaction/1.h"
#include "de/btobastian/javacord/entities/message/impl/ImplReaction/2.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace impl {


class ImplReaction {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplReaction.class);
    const ImplDiscordAPI api;
    const Message message;
    int count;
    bool usedByYou;
    const CustomEmoji customEmoji;
    const std::string unicodeEmoji;

    public ImplReaction(ImplDiscordAPI api, Message message, JSONObject data) {
      this.api = api;
      this.message = message;
      this.count = data.getInt("count");
      this.usedByYou = data.getBoolean("me");
    JSONObject emoji = data.getJSONObject("emoji");
      if (emoji.isNull("id")) {
         this.customEmoji = nullptr;
         this.unicodeEmoji = emoji.getString("name");
      } else {
         this.unicodeEmoji = nullptr;
         this.customEmoji = message.getChannelReceiver().getServer().getCustomEmojiById(emoji.getString("id"));
      }
   }

    public ImplReaction(ImplDiscordAPI api, Message message, bool usedByYou, int count, const std::string& unicodeEmoji, CustomEmoji customEmoji) {
      this.api = api;
      this.message = message;
      this.count = count;
      this.usedByYou = usedByYou;
      this.customEmoji = customEmoji;
      this.unicodeEmoji = unicodeEmoji;
   }

    Message getMessage() {
      return this.message;
   }

    int getCount() {
      return this.count;
   }

    bool isUsedByYou() {
      return this.usedByYou;
   }

    bool isCustomEmoji() {
      return this.customEmoji != nullptr;
   }

    bool isUnicodeEmoji() {
      return this.unicodeEmoji != nullptr;
   }

    CustomEmoji getCustomEmoji() {
      return this.customEmoji;
   }

    std::string getUnicodeEmoji() {
      return this.unicodeEmoji;
   }

   public Future<List<User>> getUsers() {
      return this.getUsers(nullptr);
   }

   public Future<List<User>> getUsers(FutureCallback<List<User>> callback) {
      ListenableFuture<List<User>> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<1>(this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

   public Future<Void> removeUser(User user) {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<2>(this, user));
   }

    void incrementCount(bool you) {
      this.count++;
      this.usedByYou = you || this.usedByYou;
   }

    void decrementCount(bool you) {
      this.count--;
      this.usedByYou = !you && this.usedByYou;
   }

    std::string toString() {
      return this.isUnicodeEmoji() ? this.getUnicodeEmoji() : this.getCustomEmoji();
   }
}
} // namespace impl
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
