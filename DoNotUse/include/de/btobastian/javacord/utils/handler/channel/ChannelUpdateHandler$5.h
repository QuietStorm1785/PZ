#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Channel.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/listener/role/RoleChangeOverwrittenPermissionsListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace channel {


class ChannelUpdateHandler {
public:
   ChannelUpdateHandler$5(ChannelUpdateHandler var1, Role var2, Channel var3, Permissions var4) {
      this.this$0 = var1;
      this.val$role = var2;
      this.val$channel = var3;
      this.val$oldPermissions = var4;
   }

    void run() {
      List<RoleChangeOverwrittenPermissionsListener> listeners = ChannelUpdateHandler.access$900(this.this$0)
         .getListeners(RoleChangeOverwrittenPermissionsListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onRoleChangeOverwrittenPermissions(
                  ChannelUpdateHandler.access$1000(this.this$0), this.val$role, this.val$channel, this.val$oldPermissions
               );
            } catch (Throwable var7) {
               ChannelUpdateHandler.access$200().warn("Uncaught exception in RoleChangeOverwrittenPermissionsListener!", var7);
            }
         }
      }
   }
}
} // namespace channel
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
