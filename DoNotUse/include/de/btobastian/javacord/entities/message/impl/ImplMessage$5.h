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
   ImplMessage$5(ImplMessage var1, ImplMessage var2) {
      this.this$0 = var1;
      this.val$message = var2;
   }

    Void call() {
      ImplMessage.access$000()
         .debug(
            "Trying to pin message (id: {}, author: {}, content: \"{}\")", new Object[]{this.this$0.getId(), this.this$0.getAuthor(), this.this$0.getContent()}
         );
      if (this.this$0.isPrivateMessage()) {
         ImplMessage.access$100(this.this$0).checkRateLimit(nullptr, RateLimitType.PRIVATE_MESSAGE, nullptr, nullptr);
      } else {
         ImplMessage.access$100(this.this$0).checkRateLimit(nullptr, RateLimitType.SERVER_MESSAGE, nullptr, this.this$0.getChannelReceiver());
      }

      HttpResponse<JsonNode> response = Unirest.put(
            "https://discordapp.com/api/v6/channels/" + ImplMessage.access$200(this.this$0) + "/pins/" + this.this$0.getId()
         )
         .header("authorization", ImplMessage.access$100(this.this$0).getToken())
         .asJson();
      ImplMessage.access$100(this.this$0).checkResponse(response);
      if (this.this$0.isPrivateMessage()) {
         ImplMessage.access$100(this.this$0).checkRateLimit(response, RateLimitType.PRIVATE_MESSAGE, nullptr, nullptr);
      } else {
         ImplMessage.access$100(this.this$0).checkRateLimit(response, RateLimitType.SERVER_MESSAGE, nullptr, this.this$0.getChannelReceiver());
      }

      ImplMessage.access$000()
         .debug("Pinned message (id: {}, author: {}, content: \"{}\")", new Object[]{this.this$0.getId(), this.this$0.getAuthor(), this.this$0.getContent()});
      /* synchronized - TODO: add std::mutex */ (this) {
         if (this.val$message.isPinned()) {
    return nullptr;
         } else {
            ImplMessage.access$302(this.this$0, true);
    return nullptr;
         }
      }
   }
}
} // namespace impl
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
