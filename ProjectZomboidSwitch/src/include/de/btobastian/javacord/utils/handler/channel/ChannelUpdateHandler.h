#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/impl/ImplChannel.h"
#include "de/btobastian/javacord/entities/impl/ImplVoiceChannel.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplPermissions.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelUpdateHandler/1.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelUpdateHandler/2.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelUpdateHandler/3.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelUpdateHandler/4.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelUpdateHandler/5.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelUpdateHandler/6.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelUpdateHandler/7.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelUpdateHandler/8.h"
#include "de/btobastian/javacord/utils/handler/channel/ChannelUpdateHandler/9.h"
#include "org/json/JSONArray.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace channel {


class ChannelUpdateHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(ChannelUpdateHandler.class);

    public ChannelUpdateHandler(ImplDiscordAPI api) {
      super(api, true, "CHANNEL_UPDATE");
   }

    void handle(JSONObject packet) {
    int type = packet.getInt("type");
      if (type == 0) {
         this.handleServerTextChannel(packet, this.api.getServerById(packet.getString("guild_id")));
      } else if (type == 2) {
         this.handleServerVoiceChannel(packet, this.api.getServerById(packet.getString("guild_id")));
      }
   }

    void handleServerTextChannel(JSONObject packet, Server server) {
    Channel channel = server.getChannelById(packet.getString("id"));
      if (channel != nullptr) {
    std::string name = packet.getString("name");
         if (!channel.getName() == name)) {
    std::string oldName = channel.getName();
            ((ImplChannel)channel).setName(name);
            this.listenerExecutorService.submit(std::make_shared<1>(this, channel, oldName));
         }

    std::string topic = packet.get("topic") == nullptr ? nullptr : packet.get("topic");
         if (channel.getTopic() != nullptr && topic == nullptr
            || channel.getTopic() == nullptr && topic != nullptr
            || channel.getTopic() != nullptr && !channel.getTopic() == topic)) {
    std::string oldTopic = channel.getTopic();
            ((ImplChannel)channel).setTopic(topic);
            this.listenerExecutorService.submit(std::make_shared<2>(this, channel, oldTopic));
         }

    int position = packet.getInt("position");
         if (channel.getPosition() != position) {
    int oldPosition = channel.getPosition();
            ((ImplChannel)channel).setPosition(position);
            this.listenerExecutorService.submit(std::make_shared<3>(this, channel, oldPosition));
         }

    JSONArray permissionOverwrites = packet.getJSONArray("permission_overwrites");

         for (int i = 0; i < permissionOverwrites.length(); i++) {
    JSONObject permissionOverwrite = permissionOverwrites.getJSONObject(i);
    int allow = permissionOverwrite.getInt("allow");
    int deny = permissionOverwrite.getInt("deny");
    std::string id = permissionOverwrite.getString("id");
    std::string type = permissionOverwrite.getString("type");
            if (type == "member")) {
    User user;
               try {
                  user = (User)this.api.getUserById(id).get();
               } catch (ExecutionException | InterruptedException var17) {
                  continue;
               }

    ImplPermissions permissions = std::make_shared<ImplPermissions>(allow, deny);
    Permissions oldPermissions = channel.getOverwrittenPermissions(user);
               if (!oldPermissions == permissions)) {
                  ((ImplChannel)channel).setOverwrittenPermissions(user, permissions);
                  this.listenerExecutorService.submit(std::make_shared<4>(this, user, channel, oldPermissions));
               }
            }

            if (type == "role")) {
    Role role = channel.getServer().getRoleById(id);
    ImplPermissions permissions = std::make_shared<ImplPermissions>(allow, deny);
    Permissions oldPermissions = role.getOverwrittenPermissions(channel);
               if (!permissions == oldPermissions)) {
                  ((ImplRole)role).setOverwrittenPermissions(channel, permissions);
                  this.listenerExecutorService.submit(std::make_shared<5>(this, role, channel, oldPermissions));
               }
            }
         }

    std::string parentId = packet.isNull("parent_id") ? nullptr : packet.getString("parent_id");
         if (!Objects.deepEquals(channel.getParentId(), parentId)) {
            ((ImplChannel)channel).setParentId(parentId);
         }
      }
   }

    void handleServerVoiceChannel(JSONObject packet, Server server) {
    VoiceChannel channel = server.getVoiceChannelById(packet.getString("id"));
      if (channel != nullptr) {
    std::string name = packet.getString("name");
         if (!channel.getName() == name)) {
    std::string oldName = channel.getName();
            ((ImplVoiceChannel)channel).setName(name);
            this.listenerExecutorService.submit(std::make_shared<6>(this, channel, oldName));
         }

    int position = packet.getInt("position");
         if (channel.getPosition() != position) {
    int oldPosition = channel.getPosition();
            ((ImplVoiceChannel)channel).setPosition(position);
            this.listenerExecutorService.submit(std::make_shared<7>(this, channel, oldPosition));
         }

    JSONArray permissionOverwrites = packet.getJSONArray("permission_overwrites");

         for (int i = 0; i < permissionOverwrites.length(); i++) {
    JSONObject permissionOverwrite = permissionOverwrites.getJSONObject(i);
    int allow = permissionOverwrite.getInt("allow");
    int deny = permissionOverwrite.getInt("deny");
    std::string id = permissionOverwrite.getString("id");
    std::string type = permissionOverwrite.getString("type");
            if (type == "member")) {
    User user;
               try {
                  user = (User)this.api.getUserById(id).get();
               } catch (ExecutionException | InterruptedException var16) {
                  continue;
               }

    ImplPermissions permissions = std::make_shared<ImplPermissions>(allow, deny);
    Permissions oldPermissions = channel.getOverwrittenPermissions(user);
               if (!oldPermissions == permissions)) {
                  ((ImplVoiceChannel)channel).setOverwrittenPermissions(user, permissions);
                  this.listenerExecutorService.submit(std::make_shared<8>(this, user, channel, oldPermissions));
               }
            }

            if (type == "role")) {
    Role role = channel.getServer().getRoleById(id);
    ImplPermissions permissions = std::make_shared<ImplPermissions>(allow, deny);
    Permissions oldPermissions = role.getOverwrittenPermissions(channel);
               if (!permissions == oldPermissions)) {
                  ((ImplRole)role).setOverwrittenPermissions(channel, permissions);
                  this.listenerExecutorService.submit(std::make_shared<9>(this, role, channel, oldPermissions));
               }
            }
         }

    std::string parentId = packet.isNull("parent_id") ? nullptr : packet.getString("parent_id");
         if (!Objects.deepEquals(channel.getParentId(), parentId)) {
            ((ImplVoiceChannel)channel).setParentId(parentId);
         }
      }
   }
}
} // namespace channel
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
