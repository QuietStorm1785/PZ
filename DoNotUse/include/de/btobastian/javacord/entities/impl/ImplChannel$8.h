#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/Unirest.h"
#include "de/btobastian/javacord/entities/User.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplChannel {
public:
   ImplChannel$8(ImplChannel var1, User var2) {
      this.this$0 = var1;
      this.val$user = var2;
   }

    Void call() {
      ImplChannel.access$000().debug("Deleting permissions in channel {} for user {}", this, this.val$user);
      Unirest.delete("https://discordapp.com/api/v6/channels/" + this.this$0.getId() + "/permissions/" + this.val$user.getId())
         .header("authorization", ImplChannel.access$100(this.this$0).getToken())
         .asJson();
      ImplChannel.access$000().debug("Deleted permissions in channel {} for user {}", this, this.val$user);
    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
