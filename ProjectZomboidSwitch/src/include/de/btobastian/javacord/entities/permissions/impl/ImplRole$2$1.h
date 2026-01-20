#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/2.h"
#include "de/btobastian/javacord/listener/role/RoleDeleteListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {


class ImplRole {
public:
   ImplRole$2$1(2 var1) {
      this.this$1 = var1;
   }

    void run() {
      List<RoleDeleteListener> listeners = ImplRole.access$200(this.this$1.this$0).getListeners(RoleDeleteListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onRoleDelete(ImplRole.access$200(this.this$1.this$0), this.this$1.this$0);
            } catch (Throwable var7) {
               ImplRole.access$100().warn("Uncaught exception in RoleDeleteListener!", var7);
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
