#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Region.h"
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/listener/server/ServerChangeRegionListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildUpdateHandler {
public:
   GuildUpdateHandler$2(GuildUpdateHandler var1, ImplServer var2, Region var3) {
      this.this$0 = var1;
      this.val$server = var2;
      this.val$oldRegion = var3;
   }

    void run() {
      List<ServerChangeRegionListener> listeners = GuildUpdateHandler.access$300(this.this$0).getListeners(ServerChangeRegionListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onServerChangeRegion(GuildUpdateHandler.access$400(this.this$0), this.val$server, this.val$oldRegion);
            } catch (Throwable var7) {
               GuildUpdateHandler.access$200().warn("Uncaught exception in ServerChangeRegionListener!", var7);
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
