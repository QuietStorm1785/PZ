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


class ImplChannel {
public:
   ImplChannel$12(ImplChannel var1, std::string var2, boolean var3, int var4) {
      this.this$0 = var1;
      this.val$messageId = var2;
      this.val$before = var3;
      this.val$limit = var4;
   }

    MessageHistory call() {
      MessageHistory history = std::make_shared<ImplMessageHistory>(
         ImplChannel.access$100(this.this$0), ImplChannel.access$200(this.this$0), this.val$messageId, this.val$before, this.val$limit
      );
      ImplChannel.access$100(this.this$0).addHistory(history);
    return history;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
