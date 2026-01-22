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
#include "de/btobastian/javacord/entities/message/impl/ImplMessage/7/1.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include "org/json/JSONObject.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace impl {


class ImplMessage {
public:
   ImplMessage$7(ImplMessage var1, std::string var2) {
      this.this$0 = var1;
      this.val$content = var2;
   }

    Void call() {
      if (this.this$0.isPrivateMessage()) {
         ImplMessage.access$100(this.this$0).checkRateLimit(nullptr, RateLimitType.PRIVATE_MESSAGE, nullptr, nullptr);
      } else {
         ImplMessage.access$100(this.this$0).checkRateLimit(nullptr, RateLimitType.SERVER_MESSAGE, nullptr, this.this$0.getChannelReceiver());
      }

      HttpResponse<JsonNode> response = Unirest.patch(
            "https://discordapp.com/api/v6/channels/" + ImplMessage.access$200(this.this$0) + "/messages/" + this.this$0.getId()
         )
         .header("authorization", ImplMessage.access$100(this.this$0).getToken())
         .header("content-type", "application/json")
         .body(std::make_unique<JSONObject>().put("content", this.val$content))
         .asJson();
      ImplMessage.access$100(this.this$0).checkResponse(response);
      if (this.this$0.isPrivateMessage()) {
         ImplMessage.access$100(this.this$0).checkRateLimit(response, RateLimitType.PRIVATE_MESSAGE, nullptr, nullptr);
      } else {
         ImplMessage.access$100(this.this$0).checkRateLimit(response, RateLimitType.SERVER_MESSAGE, nullptr, this.this$0.getChannelReceiver());
      }

    std::string oldContent = this.this$0.getContent();
      this.this$0.setContent(this.val$content);
      if (!oldContent == this.val$content)) {
         ImplMessage.access$100(this.this$0).getThreadPool().getSingleThreadExecutorService("listeners").submit(std::make_shared<1>(this, oldContent));
      }

    return nullptr;
   }
}
} // namespace impl
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
