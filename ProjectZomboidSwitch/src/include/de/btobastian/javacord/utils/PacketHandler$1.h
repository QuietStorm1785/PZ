#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/json/JSONObject.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {


class PacketHandler {
public:
   PacketHandler$1(PacketHandler var1, JSONObject var2) {
      this.this$0 = var1;
      this.val$packet = var2;
   }

    void run() {
      try {
         this.this$0.handle(this.val$packet);
      } catch (Exception var2) {
         PacketHandler.access$000()
            .warn(
               "Couldn't handle packet of type {}. Please contact the developer! (packet: {})",
               new Object[]{this.this$0.getType(), this.val$packet, var2}
            );
      }
   }
}
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
