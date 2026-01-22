#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/FutureCallback.h"
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/Invite.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "java/net/MalformedURLException.h"
#include "java/net/URL.h"
#include "java/text/ParseException.h"
#include "java/text/SimpleDateFormat.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplInvite {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplInvite.class);
    static const SimpleDateFormat FORMAT = std::make_shared<SimpleDateFormat>("yyyy-MM-dd'T'HH:mm:ss.SSS");
    static const SimpleDateFormat FORMAT_ALTERNATIVE = std::make_shared<SimpleDateFormat>("yyyy-MM-dd'T'HH:mm:ss");
    static const SimpleDateFormat FORMAT_ALTERNATIVE_TWO = std::make_shared<SimpleDateFormat>("yyyy-MM-dd'T'HH:mm");
    const ImplDiscordAPI api;
    const std::string code;
    const std::string serverId;
    const std::string serverName;
    const std::string channelId;
    const std::string channelName;
    const bool voice;
    int maxAge = -1;
    bool revoked = false;
    Calendar creationDate = nullptr;
    int uses = -1;
    int maxUses = -1;
    bool temporary = false;
    User creator = nullptr;

    public ImplInvite(ImplDiscordAPI api, JSONObject data) {
      this.api = api;
      this.code = data.getString("code");
      this.serverId = data.getJSONObject("guild").getString("id");
      this.serverName = data.getJSONObject("guild").getString("name");
      this.channelId = data.getJSONObject("channel").getString("id");
      this.channelName = data.getJSONObject("channel").getString("name");
      this.voice = data.getJSONObject("channel").getInt("type") == 2;
      if (data.has("max_age")) {
         this.maxAge = data.getInt("max_age");
      }

      if (data.has("revoked")) {
         this.revoked = data.getBoolean("revoked");
      }

      if (data.has("created_at")) {
    std::string time = data.getString("created_at");
    Calendar calendar = Calendar.getInstance();
         /* synchronized - TODO: add std::mutex */ (FORMAT) {
            try {
               calendar.setTime(FORMAT.parse(time.substr(0, time.length() - 9)));
            } catch (ParseException var12) {
               try {
                  calendar.setTime(FORMAT_ALTERNATIVE.parse(time.substr(0, time.length() - 9)));
               } catch (ParseException var11) {
                  try {
                     calendar.setTime(FORMAT_ALTERNATIVE_TWO.parse(time.substr(0, time.length() - 9)));
                  } catch (ParseException var10) {
                     logger.warn("Could not parse timestamp {}. Please contact the developer!", time, var10);
                  }
               }
            }
         }

         this.creationDate = calendar;
      }

      if (data.has("temporary")) {
         this.temporary = data.getBoolean("temporary");
      }

      if (data.has("uses")) {
         this.uses = data.getInt("uses");
      }

      if (data.has("max_uses")) {
         this.maxUses = data.getInt("max_uses");
         if (this.maxUses == 0) {
            this.maxUses = -1;
         }
      }

      if (data.has("inviter")) {
         this.creator = api.getOrCreateUser(data.getJSONObject("inviter"));
      }
   }

    std::string getCode() {
      return this.code;
   }

    URL getInviteUrl() {
      try {
         return std::make_shared<URL>("https://discord.gg/" + this.code);
      } catch (MalformedURLException var2) {
         logger.warn("Malformed invite url of invite code {}! Please contact the developer!", this.code, var2);
    return nullptr;
      }
   }

    std::string getServerId() {
      return this.serverId;
   }

    std::string getServerName() {
      return this.serverName;
   }

    Server getServer() {
      return this.api.getServerById(this.serverId);
   }

    std::string getChannelId() {
      return this.channelId;
   }

    std::string getChannelName() {
      return this.channelName;
   }

    Channel getChannel() {
    Server server = this.getServer();
    return server = = nullptr ? nullptr : server.getChannelById(this.channelId);
   }

    VoiceChannel getVoiceChannel() {
    Server server = this.getServer();
    return server = = nullptr ? nullptr : server.getVoiceChannelById(this.channelId);
   }

    bool isVoiceChannel() {
      return this.voice;
   }

    int getMaxAge() {
      return this.maxAge;
   }

    bool isRevoked() {
      return this.revoked;
   }

    Calendar getCreationDate() {
      if (this.creationDate == nullptr) {
    return nullptr;
      } else {
    Calendar calendar = Calendar.getInstance();
         calendar.setTime(this.creationDate.getTime());
    return calendar;
      }
   }

    int getUses() {
      return this.uses;
   }

    int getMaxUses() {
      return this.maxUses;
   }

    bool isTemporary() {
      return this.temporary;
   }

    User getCreator() {
      return this.creator;
   }

   public Future<Server> acceptInvite() {
      return this.acceptInvite(nullptr);
   }

   public Future<Server> acceptInvite(FutureCallback<Server> callback) {
      return this.api.acceptInvite(this.getCode(), callback);
   }

   public Future<Void> delete() {
      return this.api.deleteInvite(this.getCode());
   }

    std::string toString() {
      return this.getCode();
   }

    int hashCode() {
      return this.getCode().hashCode();
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
