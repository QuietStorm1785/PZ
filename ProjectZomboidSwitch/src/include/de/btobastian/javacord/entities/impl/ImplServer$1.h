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
#include "de/btobastian/javacord/entities/impl/ImplServer/1/1.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplServer {
public:
   ImplServer$1(ImplServer var1) {
      this.this$0 = var1;
   }

    Void call() {
      ImplServer.access$000().debug("Trying to delete server {}", this.this$0);
      HttpResponse<JsonNode> response = Unirest.delete("https://discordapp.com/api/v6/guilds/" + ImplServer.access$200(this.this$0))
         .header("authorization", ImplServer.access$100(this.this$0).getToken())
         .asJson();
      ImplServer.access$100(this.this$0).checkResponse(response);
      ImplServer.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, this.this$0, nullptr);
      ImplServer.access$100(this.this$0).getServerMap().remove(ImplServer.access$200(this.this$0));
      ImplServer.access$000().info("Deleted server {}", this.this$0);
      ImplServer.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this));
    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
