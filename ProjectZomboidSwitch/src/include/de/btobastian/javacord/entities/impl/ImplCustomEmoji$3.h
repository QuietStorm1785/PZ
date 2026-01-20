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
#include "de/btobastian/javacord/entities/impl/ImplCustomEmoji/3/1.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplCustomEmoji {
public:
   ImplCustomEmoji$3(ImplCustomEmoji var1) {
      this.this$0 = var1;
   }

    Void call() {
      ImplCustomEmoji.access$100().debug("Trying to delete emoji {}", this.this$0);
      HttpResponse<JsonNode> response = Unirest.delete(
            "https://discordapp.com/api/v6/guilds/" + ImplCustomEmoji.access$000(this.this$0).getId() + "/emojis/" + ImplCustomEmoji.access$300(this.this$0)
         )
         .header("authorization", ImplCustomEmoji.access$200(this.this$0).getToken())
         .asJson();
      ImplCustomEmoji.access$200(this.this$0).checkResponse(response);
      ImplCustomEmoji.access$200(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, ImplCustomEmoji.access$000(this.this$0), nullptr);
      ImplCustomEmoji.access$000(this.this$0).removeCustomEmoji(this.this$0);
      ImplCustomEmoji.access$100().info("Deleted emoji {}", this.this$0);
      ImplCustomEmoji.access$200(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this));
    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
