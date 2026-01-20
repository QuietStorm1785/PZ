#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/impl/ImplServer.h"
#include "de/btobastian/javacord/listener/user/UserChangeNicknameListener.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildMemberUpdateHandler {
public:
   GuildMemberUpdateHandler$1(GuildMemberUpdateHandler var1, ImplServer var2, User var3, std::string var4) {
      this.this$0 = var1;
      this.val$server = var2;
      this.val$user = var3;
      this.val$oldNick = var4;
   }

    void run() {
      List<UserChangeNicknameListener> listeners = GuildMemberUpdateHandler.access$000(this.this$0).getListeners(UserChangeNicknameListener.class);
      /* synchronized - TODO: add std::mutex */ (listeners) {
    for (auto& listener : listeners)            try {
               listener.onUserChangeNickname(GuildMemberUpdateHandler.access$100(this.this$0), this.val$server, this.val$user, this.val$oldNick);
            } catch (Throwable var7) {
               GuildMemberUpdateHandler.access$200().warn("Uncaught exception in UserChangeNicknameListener!", var7);
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
