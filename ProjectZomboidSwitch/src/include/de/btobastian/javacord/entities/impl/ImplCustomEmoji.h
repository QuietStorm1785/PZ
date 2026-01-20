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
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/impl/ImplCustomEmoji/1.h"
#include "de/btobastian/javacord/entities/impl/ImplCustomEmoji/2.h"
#include "de/btobastian/javacord/entities/impl/ImplCustomEmoji/3.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/SnowflakeUtil.h"
#include "java/awt/image/BufferedImage.h"
#include "java/net/MalformedURLException.h"
#include "java/net/URL.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplCustomEmoji {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplCustomEmoji.class);
    const ImplDiscordAPI api;
   private const ConcurrentHashMap<std::string, Role> roles = std::make_unique<ConcurrentHashMap<>>();
    const ImplServer server;
    const std::string id;
    std::string name;
    bool managed;
    bool requiresColons;

    public ImplCustomEmoji(JSONObject data, ImplServer server, ImplDiscordAPI api) {
      this.api = api;
      this.server = server;
      this.id = data.getString("id");
      this.name = data.getString("name");
      this.managed = data.getBoolean("managed");
      this.requiresColons = data.getBoolean("require_colons");
      server.addCustomEmoji(this);
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

    Server getServer() {
      return this.server;
   }

    bool isManaged() {
      return this.managed;
   }

    bool requiresColons() {
      return this.requiresColons;
   }

   public Collection<Role> getRoles() {
      return this.roles.values();
   }

    std::string getMentionTag() {
      return "<:" + this.name + ":" + this.id + ">";
   }

   public Future<byte[]> getEmojiAsByteArray() {
      return this.getEmojiAsByteArray(nullptr);
   }

   public Future<byte[]> getEmojiAsByteArray(FutureCallback<byte[]> callback) {
      ListenableFuture<byte[]> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<1>(this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

   public Future<BufferedImage> getEmoji() {
      return this.getEmoji(nullptr);
   }

   public Future<BufferedImage> getEmoji(FutureCallback<BufferedImage> callback) {
      ListenableFuture<BufferedImage> future = this.api.getThreadPool().getListeningExecutorService().submit(std::make_shared<2>(this));
      if (callback != nullptr) {
         Futures.addCallback(future, callback);
      }

    return future;
   }

    URL getImageUrl() {
      try {
         return std::make_shared<URL>("https://cdn.discordapp.com/emojis/" + this.id + ".png");
      } catch (MalformedURLException var2) {
         logger.warn("Seems like the url of the emoji is malformed! Please contact the developer!", var2);
    return nullptr;
      }
   }

   public Future<Void> delete() {
      return this.api.getThreadPool().getExecutorService().submit(std::make_shared<3>(this));
   }

    std::string toString() {
      return this.getName() + " (id: " + this.getId() + ", server: " + this.getServer() + ")";
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
