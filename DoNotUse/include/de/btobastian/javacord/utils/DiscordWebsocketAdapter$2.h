#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/neovisionaries/ws/client/WebSocket.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {


class DiscordWebsocketAdapter {
public:
   DiscordWebsocketAdapter$2(DiscordWebsocketAdapter var1, WebSocket var2, int var3) {
      this.this$0 = var1;
      this.val$websocket = var2;
      this.val$heartbeatInterval = var3;
   }

    void run() {
      DiscordWebsocketAdapter.access$302(this.this$0, false);
      DiscordWebsocketAdapter.access$400(this.this$0, this.val$websocket);
      DiscordWebsocketAdapter.access$500().debug("Sent heartbeat (interval: {})", this.val$heartbeatInterval);
   }
}
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
