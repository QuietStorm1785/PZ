#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/listener/user/UserChangeNameListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace user {


class PresenceUpdateHandler {
public:
   PresenceUpdateHandler$2(PresenceUpdateHandler var1, User var2, std::string var3) {
      this.this$0 = var1;
      this.val$user = var2;
      this.val$oldName = var3;
   }

    void run() {
      List<UserChangeNameListener> listeners = PresenceUpdateHandler.access$300(this.this$0).getListeners(UserChangeNameListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onUserChangeName(PresenceUpdateHandler.access$400(this.this$0), this.val$user, this.val$oldName);
            } catch (Throwable var7) {
               PresenceUpdateHandler.access$200().warn("Uncaught exception in UserChangeNameListener!", var7);
            }
         }
      }
   }
}
} // namespace user
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
