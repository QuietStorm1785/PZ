#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "de/btobastian/javacord/listener/role/RoleChangeHoistListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {
namespace role {


class GuildRoleUpdateHandler {
public:
   GuildRoleUpdateHandler$4(GuildRoleUpdateHandler var1, ImplRole var2) {
      this.this$0 = var1;
      this.val$role = var2;
   }

    void run() {
      List<RoleChangeHoistListener> listeners = GuildRoleUpdateHandler.access$700(this.this$0).getListeners(RoleChangeHoistListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onRoleChangeHoist(GuildRoleUpdateHandler.access$800(this.this$0), this.val$role, !this.val$role.getHoist());
            } catch (Throwable var7) {
               GuildRoleUpdateHandler.access$200().warn("Uncaught exception in RoleChangeHoistListener!", var7);
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
