#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/listener/user/UserRoleRemoveListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildMemberUpdateHandler {
public:
   GuildMemberUpdateHandler$2(GuildMemberUpdateHandler var1, User var2, Role var3) {
      this.this$0 = var1;
      this.val$user = var2;
      this.val$role = var3;
   }

    void run() {
      List<UserRoleRemoveListener> listeners = GuildMemberUpdateHandler.access$300(this.this$0).getListeners(UserRoleRemoveListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onUserRoleRemove(GuildMemberUpdateHandler.access$400(this.this$0), this.val$user, this.val$role);
            } catch (Throwable var7) {
               GuildMemberUpdateHandler.access$200().warn("Uncaught exception in UserRoleRemoveListenerListener!", var7);
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
