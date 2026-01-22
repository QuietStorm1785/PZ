#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/Server.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace handler {
namespace server {


class GuildCreateHandler {
public:
   GuildCreateHandler$2(GuildCreateHandler var1, Server var2) {
      this.this$0 = var1;
      this.val$server = var2;
   }

    void run() {
      GuildCreateHandler.access$400(this.this$0).getInternalServerJoinListener().onServerJoin(GuildCreateHandler.access$300(this.this$0), this.val$server);
   }
}
} // namespace server
} // namespace handler
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
