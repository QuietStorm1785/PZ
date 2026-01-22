#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/listener/role/RoleCreateListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {
namespace role {


class GuildRoleCreateHandler {
public:
   GuildRoleCreateHandler$1(GuildRoleCreateHandler var1, Role var2) {
      this.this$0 = var1;
      this.val$role = var2;
   }

    void run() {
      List<RoleCreateListener> listeners = GuildRoleCreateHandler.access$000(this.this$0).getListeners(RoleCreateListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onRoleCreate(GuildRoleCreateHandler.access$100(this.this$0), this.val$role);
            } catch (Throwable var7) {
               GuildRoleCreateHandler.access$200().warn("Uncaught exception in RoleCreateListener!", var7);
            }
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
