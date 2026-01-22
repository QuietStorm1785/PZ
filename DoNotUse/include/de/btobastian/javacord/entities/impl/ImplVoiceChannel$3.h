#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/Unirest.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/permissions/Permissions.h"
#include "de/btobastian/javacord/entities/permissions/impl/ImplPermissions.h"
#include "org/json/JSONObject.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplVoiceChannel {
public:
   ImplVoiceChannel$3(ImplVoiceChannel var1, User var2, Permissions var3) {
      this.this$0 = var1;
      this.val$user = var2;
      this.val$permissions = var3;
   }

    Void call() {
      ImplVoiceChannel.access$000()
         .debug(
            "Updating permissions in channel {} for user {} (allow: {}, deny: {})",
            new Object[]{this, this.val$user, ((ImplPermissions)this.val$permissions).getAllowed(), ((ImplPermissions)this.val$permissions).getDenied()}
         );
      Unirest.put("https://discordapp.com/api/v6/channels/" + this.this$0.getId() + "/permissions/" + this.val$user.getId())
         .header("authorization", ImplVoiceChannel.access$100(this.this$0).getToken())
         .header("Content-Type", "application/json")
         .body(
    std::make_shared<JSONObject>();
               .put("allow", ((ImplPermissions)this.val$permissions).getAllowed())
               .put("deny", ((ImplPermissions)this.val$permissions).getDenied())
               .put("type", "member")
               
         )
         .asJson();
      ImplVoiceChannel.access$000()
         .debug(
            "Updated permissions in channel {} for user {} (allow: {}, deny: {})",
            new Object[]{this, this.val$user, ((ImplPermissions)this.val$permissions).getAllowed(), ((ImplPermissions)this.val$permissions).getDenied()}
         );
    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
