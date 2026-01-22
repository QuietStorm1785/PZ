#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/listener/server/ServerJoinListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildCreateHandler {
public:
   GuildCreateHandler$1(GuildCreateHandler var1, Server var2) {
      this.this$0 = var1;
      this.val$server = var2;
   }

    void run() {
      List<ServerJoinListener> listeners = GuildCreateHandler.access$000(this.this$0).getListeners(ServerJoinListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onServerJoin(GuildCreateHandler.access$100(this.this$0), this.val$server);
            } catch (Throwable var7) {
               GuildCreateHandler.access$200().warn("Uncaught exception in ServerJoinListener!", var7);
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
