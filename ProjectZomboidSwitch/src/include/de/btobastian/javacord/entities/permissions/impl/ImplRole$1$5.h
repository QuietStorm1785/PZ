#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/1.h"
#include "de/btobastian/javacord/listener/role/RoleChangeManagedListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {


class ImplRole {
public:
   ImplRole$1$5(1 var1) {
      this.this$1 = var1;
   }

    void run() {
      List<RoleChangeManagedListener> listeners = ImplRole.access$200(this.this$1.this$0).getListeners(RoleChangeManagedListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onRoleChangeManaged(ImplRole.access$200(this.this$1.this$0), this.this$1.this$0, !ImplRole.access$800(this.this$1.this$0));
            } catch (Throwable var7) {
               ImplRole.access$100().warn("Uncaught exception in RoleChangeManagedListener!", var7);
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
