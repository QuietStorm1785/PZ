#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/1.h"
#include "de/btobastian/javacord/listener/role/RoleChangePermissionsListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {


class ImplRole {
public:
   ImplRole$1$1(1 var1, ImplPermissions var2) {
      this.this$1 = var1;
      this.val$oldPermissions = var2;
   }

    void run() {
      List<RoleChangePermissionsListener> listeners = ImplRole.access$200(this.this$1.this$0).getListeners(RoleChangePermissionsListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onRoleChangePermissions(ImplRole.access$200(this.this$1.this$0), this.this$1.this$0, this.val$oldPermissions);
            } catch (Throwable var7) {
               ImplRole.access$100().warn("Uncaught exception in RoleChangePermissionsListener!", var7);
            }
         }
      }
   }
}
} // namespace impl
} // namespace permissions
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
