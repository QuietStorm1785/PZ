#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplPermissions.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "de/btobastian/javacord/utils/PacketHandler.h"
#include "de/btobastian/javacord/utils/handler/server/role/GuildRoleUpdateHandler/1.h"
#include "de/btobastian/javacord/utils/handler/server/role/GuildRoleUpdateHandler/2.h"
#include "de/btobastian/javacord/utils/handler/server/role/GuildRoleUpdateHandler/3.h"
#include "de/btobastian/javacord/utils/handler/server/role/GuildRoleUpdateHandler/4.h"
#include "de/btobastian/javacord/utils/handler/server/role/GuildRoleUpdateHandler/5.h"
#include "java/awt/Color.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {
namespace role {


class GuildRoleUpdateHandler : public PacketHandler {
public:
    static const Logger logger = LoggerUtil.getLogger(GuildRoleUpdateHandler.class);

    public GuildRoleUpdateHandler(ImplDiscordAPI api) {
      super(api, true, "GUILD_ROLE_UPDATE");
   }

    void handle(JSONObject packet) {
    std::string guildId = packet.getString("guild_id");
    JSONObject roleJson = packet.getJSONObject("role");
    Server server = this.api.getServerById(guildId);
    ImplRole role = (ImplRole)server.getRoleById(roleJson.getString("id"));
    std::string name = roleJson.getString("name");
      if (!role.getName() == name)) {
    std::string oldName = role.getName();
         role.setName(name);
         this.listenerExecutorService.submit(std::make_shared<1>(this, role, oldName));
      }

    Permissions permissions = std::make_shared<ImplPermissions>(roleJson.getInt("permissions"));
      if (!role.getPermissions() == permissions)) {
    Permissions oldPermissions = role.getPermissions();
         role.setPermissions((ImplPermissions)permissions);
         this.listenerExecutorService.submit(std::make_shared<2>(this, role, oldPermissions));
      }

    Color color = std::make_shared<Color>(roleJson.getInt("color"));
      if (role.getColor().getRGB() != color.getRGB()) {
    Color oldColor = role.getColor();
         role.setColor(color);
         this.listenerExecutorService.submit(std::make_shared<3>(this, role, oldColor));
      }

      if (role.getHoist() != roleJson.getBoolean("hoist")) {
         role.setHoist(!role.getHoist());
         this.listenerExecutorService.submit(std::make_shared<4>(this, role));
      }

      /* synchronized - TODO: add std::mutex */ (Role.class) {
    int position = roleJson.getInt("position");
         if (role.getPosition() != position) {
    int oldPosition = role.getPosition();
            role.setPosition(position);
            this.listenerExecutorService.submit(std::make_shared<5>(this, role, oldPosition));
         }
      }
   }
}
} // namespace role
} // namespace server
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
