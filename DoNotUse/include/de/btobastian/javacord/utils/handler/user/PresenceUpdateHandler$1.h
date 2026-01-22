#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/UserStatus.h"
#include "de/btobastian/javacord/listener/user/UserChangeStatusListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace user {


class PresenceUpdateHandler {
public:
   PresenceUpdateHandler$1(PresenceUpdateHandler var1, User var2, UserStatus var3) {
      this.this$0 = var1;
      this.val$user = var2;
      this.val$oldStatus = var3;
   }

    void run() {
      List<UserChangeStatusListener> listeners = PresenceUpdateHandler.access$000(this.this$0).getListeners(UserChangeStatusListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onUserChangeStatus(PresenceUpdateHandler.access$100(this.this$0), this.val$user, this.val$oldStatus);
            } catch (Throwable var7) {
               PresenceUpdateHandler.access$200().warn("Uncaught exception in UserChangeStatusListener!", var7);
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
