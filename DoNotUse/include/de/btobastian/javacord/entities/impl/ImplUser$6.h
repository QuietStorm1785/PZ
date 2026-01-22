#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/btobastian/javacord/entities/message/MessageHistory.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessageHistory.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplUser {
public:
   ImplUser$6(ImplUser var1, std::string var2, boolean var3, int var4) {
      this.this$0 = var1;
      this.val$messageId = var2;
      this.val$before = var3;
      this.val$limit = var4;
   }

    MessageHistory call() {
      MessageHistory history = std::make_shared<ImplMessageHistory>(
         ImplUser.access$300(this.this$0), this.this$0.getUserChannelIdBlocking(), this.val$messageId, this.val$before, this.val$limit
      );
      ImplUser.access$300(this.this$0).addHistory(history);
    return history;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
