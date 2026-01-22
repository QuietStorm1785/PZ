#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/listener/server/ServerMemberUnbanListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildBanRemoveHandler {
public:
   GuildBanRemoveHandler$1(GuildBanRemoveHandler var1, User var2, Server var3) {
      this.this$0 = var1;
      this.val$user = var2;
      this.val$server = var3;
   }

    void run() {
      List<ServerMemberUnbanListener> listeners = GuildBanRemoveHandler.access$000(this.this$0).getListeners(ServerMemberUnbanListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onServerMemberUnban(GuildBanRemoveHandler.access$100(this.this$0), this.val$user.getId(), this.val$server);
            } catch (Throwable var7) {
               GuildBanRemoveHandler.access$200().warn("Uncaught exception in ServerMemberUnbanListener!", var7);
            }
         }
      }
   }
}
} // namespace server
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
