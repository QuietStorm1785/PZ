#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole.h"
#include "de/btobastian/javacord/listener/role/RoleChangeColorListener.h"
#include "java/awt/Color.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {
namespace role {


class GuildRoleUpdateHandler {
public:
   GuildRoleUpdateHandler$3(GuildRoleUpdateHandler var1, ImplRole var2, Color var3) {
      this.this$0 = var1;
      this.val$role = var2;
      this.val$oldColor = var3;
   }

    void run() {
      List<RoleChangeColorListener> listeners = GuildRoleUpdateHandler.access$500(this.this$0).getListeners(RoleChangeColorListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onRoleChangeColor(GuildRoleUpdateHandler.access$600(this.this$0), this.val$role, this.val$oldColor);
            } catch (Throwable var7) {
               GuildRoleUpdateHandler.access$200().warn("Uncaught exception in RoleChangeColorListener!", var7);
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
