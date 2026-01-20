#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Joiner.h"
#include "com/mashape/unirest/http/HttpResponse.h"
#include "com/mashape/unirest/http/JsonNode.h"
#include "com/mashape/unirest/http/Unirest.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include "org/json/JSONObject.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplChannel {
public:
   ImplChannel$10(ImplChannel var1, std::string[] var2) {
      this.this$0 = var1;
      this.val$messages = var2;
   }

    Void call() {
      ImplChannel.access$000().debug("Bulk deleting messages in channel {} (ids: [{}])", this, Joiner.on(",").join(this.val$messages));
      ImplChannel.access$100(this.this$0).checkRateLimit(nullptr, RateLimitType.SERVER_MESSAGE, nullptr, this.this$0);
      HttpResponse<JsonNode> response = Unirest.post("https://discordapp.com/api/v6/channels/" + this.this$0.getId() + "/messages/bulk-delete")
         .header("authorization", ImplChannel.access$100(this.this$0).getToken())
         .header("Content-Type", "application/json")
         .body(std::make_unique<JSONObject>().put("messages", this.val$messages))
         .asJson();
      ImplChannel.access$100(this.this$0).checkRateLimit(response, RateLimitType.SERVER_MESSAGE, nullptr, this.this$0);
      ImplChannel.access$000().debug("Bulk deleted messages in channel {} (ids: [{}])", this, Joiner.on(",").join(this.val$messages));
    return nullptr;
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
