#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/VoiceChannel.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/listener/user/UserChangeOverwrittenPermissionsListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace channel {


class ChannelUpdateHandler {
public:
   ChannelUpdateHandler$8(ChannelUpdateHandler var1, User var2, VoiceChannel var3, Permissions var4) {
      this.this$0 = var1;
      this.val$user = var2;
      this.val$channel = var3;
      this.val$oldPermissions = var4;
   }

    void run() {
      List<UserChangeOverwrittenPermissionsListener> listeners = ChannelUpdateHandler.access$1500(this.this$0)
         .getListeners(UserChangeOverwrittenPermissionsListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onUserChangeOverwrittenPermissions(
                  ChannelUpdateHandler.access$1600(this.this$0), this.val$user, this.val$channel, this.val$oldPermissions
               );
            } catch (Throwable var7) {
               ChannelUpdateHandler.access$200().warn("Uncaught exception in UserChangeOverwrittenPermissionsListener!", var7);
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
