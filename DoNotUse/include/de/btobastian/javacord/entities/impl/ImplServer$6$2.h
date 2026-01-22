#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/impl/ImplServer/6.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include "de/btobastian/javacord/listener/user/UserRoleAddListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$6$2(6 var1, Role var2) {
      this.this$1 = var1;
      this.val$role = var2;
   }

    void run() {
      List<UserRoleAddListener> listeners = ImplServer.access$100(this.this$1.this$0).getListeners(UserRoleAddListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onUserRoleAdd(ImplServer.access$100(this.this$1.this$0), this.this$1.val$user, this.val$role);
            } catch (Throwable var7) {
               ImplServer.access$000().warn("Uncaught exception in UserRoleAddListener!", var7);
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
