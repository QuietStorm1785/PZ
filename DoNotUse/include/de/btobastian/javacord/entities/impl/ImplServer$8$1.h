#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/impl/ImplServer/8.h"
#include "de/btobastian/javacord/listener/server/ServerMemberUnbanListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$8$1(8 var1) {
      this.this$1 = var1;
   }

    void run() {
      List<ServerMemberUnbanListener> listeners = ImplServer.access$100(this.this$1.this$0).getListeners(ServerMemberUnbanListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onServerMemberUnban(ImplServer.access$100(this.this$1.this$0), this.this$1.val$userId, this.this$1.this$0);
            } catch (Throwable var7) {
               ImplServer.access$000().warn("Uncaught exception in ServerMemberUnbanListener!", var7);
            }
         }
      }
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
