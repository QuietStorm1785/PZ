#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/Unirest.h"
#include "de/btobastian/javacord/entities/permissions/Role.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplChannel {
public:
   ImplChannel$7(ImplChannel var1, Role var2) {
      this.this$0 = var1;
      this.val$role = var2;
   }

    Void call() {
      ImplChannel.access$000().debug("Deleting permissions in channel {} for role {}", this, this.val$role);
      Unirest.delete("https://discordapp.com/api/v6/channels/" + this.this$0.getId() + "/permissions/" + this.val$role.getId())
         .header("authorization", ImplChannel.access$100(this.this$0).getToken())
         .asJson();
      ImplChannel.access$000().debug("Deleted permissions in channel {} for role {}", this, this.val$role);
    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
