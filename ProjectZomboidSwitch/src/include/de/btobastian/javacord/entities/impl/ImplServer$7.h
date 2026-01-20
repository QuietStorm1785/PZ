#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/mashape/unirest/http/HttpResponse.h"
#include "com/mashape/unirest/http/JsonNode.h"
#include "com/mashape/unirest/http/Unirest.h"
#include "de/btobastian/javacord/entities/User.h"
#include "de/btobastian/javacord/entities/impl/ImplServer/7/1.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$7(ImplServer var1, std::string var2, int var3) {
      this.this$0 = var1;
      this.val$userId = var2;
      this.val$deleteDays = var3;
   }

    Void call() {
      ImplServer.access$000()
         .debug("Trying to ban an user from server {} (user id: {}, delete days: {})", new Object[]{this.this$0, this.val$userId, this.val$deleteDays});
      HttpResponse<JsonNode> response = Unirest.put(
            "https://discordapp.com/api/v6/guilds/" + this.this$0.getId() + "/bans/" + this.val$userId + "?delete-message-days=" + this.val$deleteDays
         )
         .header("authorization", ImplServer.access$100(this.this$0).getToken())
         .asJson();
      ImplServer.access$100(this.this$0).checkResponse(response);
      ImplServer.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, this.this$0, nullptr);
    User user = (User)ImplServer.access$100(this.this$0).getUserById(this.val$userId).get();
      if (user != nullptr) {
         this.this$0.removeMember(user);
      }

      ImplServer.access$000()
         .info("Banned an user from server {} (user id: {}, delete days: {})", new Object[]{this.this$0, this.val$userId, this.val$deleteDays});
      ImplServer.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this, user));
    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
