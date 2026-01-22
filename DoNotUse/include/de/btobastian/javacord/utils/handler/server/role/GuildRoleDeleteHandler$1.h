#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/listener/role/RoleDeleteListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {
namespace role {


class GuildRoleDeleteHandler {
public:
   GuildRoleDeleteHandler$1(GuildRoleDeleteHandler var1, Role var2) {
      this.this$0 = var1;
      this.val$role = var2;
   }

    void run() {
      List<RoleDeleteListener> listeners = GuildRoleDeleteHandler.access$000(this.this$0).getListeners(RoleDeleteListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onRoleDelete(GuildRoleDeleteHandler.access$100(this.this$0), this.val$role);
            } catch (Throwable var7) {
               GuildRoleDeleteHandler.access$200().warn("Uncaught exception in RoleDeleteListener!", var7);
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
