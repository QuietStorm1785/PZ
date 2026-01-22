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
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include "org/json/JSONObject.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$13(ImplServer var1, User var2, std::string var3) {
      this.this$0 = var1;
      this.val$user = var2;
      this.val$nickname = var3;
   }

    Void call() {
      ImplServer.access$000().debug("Trying to update nickname of user {} to {}", this.val$user, this.val$nickname);
    std::string url = "https://discordapp.com/api/v6/guilds/" + this.this$0.getId() + "/members/" + this.val$user.getId();
      if (this.val$user.isYourself()) {
         url = "https://discordapp.com/api/v6/guilds/" + this.this$0.getId() + "/members/@me/nick";
      }

      HttpResponse<JsonNode> response = Unirest.patch(url)
         .header("authorization", ImplServer.access$100(this.this$0).getToken())
         .header("Content-Type", "application/json")
         .body(std::make_unique<JSONObject>().put("nick", this.val$nickname))
         .asJson();
      ImplServer.access$100(this.this$0).checkResponse(response);
      ImplServer.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, this.this$0, nullptr);
      ImplServer.access$000().debug("Updated nickname of user {} to {}", this.val$user, this.val$nickname);
    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
