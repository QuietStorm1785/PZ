#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {

class DiscordWebsocketAdapter {
public:
   DiscordWebsocketAdapter$1(DiscordWebsocketAdapter var1) {
      this.this$0 = var1;
   }

    void run() {
    int amount = DiscordWebsocketAdapter.access$000(this.this$0).getServers().size();

      while (true) {
         try {
            Thread.sleep(1500L);
         } catch (InterruptedException var3) {
         }

         if (DiscordWebsocketAdapter.access$000(this.this$0).getServers().size() <= amount
            && DiscordWebsocketAdapter.access$100(this.this$0) + 1500L < System.currentTimeMillis()) {
            DiscordWebsocketAdapter.access$200(this.this$0).set(true);
            return;
         }

         amount = DiscordWebsocketAdapter.access$000(this.this$0).getServers().size();
      }
   }
}
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
