#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/impl/ImplServer/2.h"
#include "de/btobastian/javacord/listener/server/ServerLeaveListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$2$1(2 var1) {
      this.this$1 = var1;
   }

    void run() {
      List<ServerLeaveListener> listeners = ImplServer.access$100(this.this$1.this$0).getListeners(ServerLeaveListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onServerLeave(ImplServer.access$100(this.this$1.this$0), this.this$1.this$0);
            } catch (Throwable var7) {
               ImplServer.access$000().warn("Uncaught exception in ServerLeaveListener!", var7);
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
