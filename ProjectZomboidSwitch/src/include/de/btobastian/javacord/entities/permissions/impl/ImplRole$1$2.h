#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/permissions/impl/ImplRole/1.h"
#include "de/btobastian/javacord/listener/role/RoleChangeNameListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace permissions {
namespace impl {


class ImplRole {
public:
   ImplRole$1$2(1 var1, std::string var2) {
      this.this$1 = var1;
      this.val$oldName = var2;
   }

    void run() {
      List<RoleChangeNameListener> listeners = ImplRole.access$200(this.this$1.this$0).getListeners(RoleChangeNameListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onRoleChangeName(ImplRole.access$200(this.this$1.this$0), this.this$1.this$0, this.val$oldName);
            } catch (Throwable var7) {
               ImplRole.access$100().warn("Uncaught exception in RoleChangeNameListener!", var7);
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
