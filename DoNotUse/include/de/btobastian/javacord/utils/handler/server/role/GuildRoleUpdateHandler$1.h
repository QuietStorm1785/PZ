#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "de/btobastian/javacord/listener/role/RoleChangeNameListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {
namespace role {


class GuildRoleUpdateHandler {
public:
   GuildRoleUpdateHandler$1(GuildRoleUpdateHandler var1, ImplRole var2, std::string var3) {
      this.this$0 = var1;
      this.val$role = var2;
      this.val$oldName = var3;
   }

    void run() {
      List<RoleChangeNameListener> listeners = GuildRoleUpdateHandler.access$000(this.this$0).getListeners(RoleChangeNameListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onRoleChangeName(GuildRoleUpdateHandler.access$100(this.this$0), this.val$role, this.val$oldName);
            } catch (Throwable var7) {
               GuildRoleUpdateHandler.access$200().warn("Uncaught exception in RoleChangeNameListener!", var7);
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
