#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "de/btobastian/javacord/listener/role/RoleChangePermissionsListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {
namespace role {


class GuildRoleUpdateHandler {
public:
   GuildRoleUpdateHandler$2(GuildRoleUpdateHandler var1, ImplRole var2, Permissions var3) {
      this.this$0 = var1;
      this.val$role = var2;
      this.val$oldPermissions = var3;
   }

    void run() {
      List<RoleChangePermissionsListener> listeners = GuildRoleUpdateHandler.access$300(this.this$0).getListeners(RoleChangePermissionsListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onRoleChangePermissions(GuildRoleUpdateHandler.access$400(this.this$0), this.val$role, this.val$oldPermissions);
            } catch (Throwable var7) {
               GuildRoleUpdateHandler.access$200().warn("Uncaught exception in RoleChangePermissionsListener!", var7);
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
