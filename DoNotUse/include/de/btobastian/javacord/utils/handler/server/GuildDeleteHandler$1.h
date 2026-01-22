#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Server.h"
#include "de/btobastian/javacord/listener/server/ServerLeaveListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildDeleteHandler {
public:
   GuildDeleteHandler$1(GuildDeleteHandler var1, Server var2) {
      this.this$0 = var1;
      this.val$server = var2;
   }

    void run() {
      List<ServerLeaveListener> listeners = GuildDeleteHandler.access$000(this.this$0).getListeners(ServerLeaveListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onServerLeave(GuildDeleteHandler.access$100(this.this$0), this.val$server);
            } catch (Throwable var7) {
               GuildDeleteHandler.access$200().warn("Uncaught exception in ServerLeaveListener!", var7);
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
