#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/1.h"
#include "de/btobastian/javacord/listener/role/RoleChangeHoistListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {


class ImplRole {
public:
   ImplRole$1$4(1 var1) {
      this.this$1 = var1;
   }

    void run() {
      List<RoleChangeHoistListener> listeners = ImplRole.access$200(this.this$1.this$0).getListeners(RoleChangeHoistListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onRoleChangeHoist(ImplRole.access$200(this.this$1.this$0), this.this$1.this$0, !ImplRole.access$700(this.this$1.this$0));
            } catch (Throwable var7) {
               ImplRole.access$100().warn("Uncaught exception in RoleChangeHoistListener!", var7);
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
