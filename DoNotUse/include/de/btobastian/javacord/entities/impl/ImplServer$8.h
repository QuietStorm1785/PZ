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
#include "de/btobastian/javacord/entities/impl/ImplServer/8/1.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$8(ImplServer var1, std::string var2) {
      this.this$0 = var1;
      this.val$userId = var2;
   }

    Void call() {
      ImplServer.access$000().debug("Trying to unban an user from server {} (user id: {})", this.this$0, this.val$userId);
      HttpResponse<JsonNode> response = Unirest.delete("https://discordapp.com/api/v6/guilds/" + this.this$0.getId() + "/bans/" + this.val$userId)
         .header("authorization", ImplServer.access$100(this.this$0).getToken())
         .asJson();
      ImplServer.access$100(this.this$0).checkResponse(response);
      ImplServer.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, this.this$0, nullptr);
      ImplServer.access$000().info("Unbanned an user from server {} (user id: {})", this.this$0, this.val$userId);
      ImplServer.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this));
    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
