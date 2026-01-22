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
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace impl {


class ImplMessage {
public:
   ImplMessage$8(ImplMessage var1) {
      this.this$0 = var1;
   }

    Void call() {
      ImplMessage.access$000().debug("Trying to remove all reactions from message {}", this.this$0);
      HttpResponse<JsonNode> response = Unirest.delete(
            "https://discordapp.com/api/v6/channels/" + ImplMessage.access$200(this.this$0) + "/messages/" + this.this$0.getId() + "/reactions"
         )
         .header("authorization", ImplMessage.access$100(this.this$0).getToken())
         .asJson();
      ImplMessage.access$100(this.this$0).checkResponse(response);
      if (this.this$0.isPrivateMessage()) {
         ImplMessage.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, nullptr, nullptr);
      } else {
         ImplMessage.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, nullptr, this.this$0.getChannelReceiver());
      }

      ImplMessage.access$000().debug("Removed all reactions from message {}", this.this$0);
    return nullptr;
   }
}
} // namespace impl
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
