#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/ImplDiscordAPI.h"
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/entities/permissions/Ban.h"
#include "org/json/JSONObject.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {


class ImplBan {
public:
    const ImplServer server;
    const User user;
    const std::string reason;

    public ImplBan(ImplDiscordAPI api, ImplServer server, JSONObject data) {
      this.server = server;
      this.user = api.getOrCreateUser(data.getJSONObject("user"));
      this.reason = data.isNull("reason") ? nullptr : data.getString("reason");
   }

    User getUser() {
      return this.user;
   }

    Server getServer() {
      return this.server;
   }

    std::string getReason() {
      return this.reason;
   }
}
} // namespace impl
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
