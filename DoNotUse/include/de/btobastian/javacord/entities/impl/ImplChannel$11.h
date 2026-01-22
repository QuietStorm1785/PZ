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
#include "de/btobastian/javacord/entities/message/Message.h"
#include "de/btobastian/javacord/entities/message/impl/ImplMessage.h"
#include "de/btobastian/javacord/utils/ratelimits/RateLimitType.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace impl {


class ImplChannel {
public:
   ImplChannel$11(ImplChannel var1, std::string var2) {
      this.this$0 = var1;
      this.val$messageId = var2;
   }

    Message call() {
      ImplChannel.access$000().debug("Requesting message (channel id: {}, message id: {})", ImplChannel.access$200(this.this$0), this.val$messageId);
      HttpResponse<JsonNode> response = Unirest.get(
            "https://discordapp.com/api/v6/channels/" + ImplChannel.access$200(this.this$0) + "/messages/" + this.val$messageId
         )
         .header("authorization", ImplChannel.access$100(this.this$0).getToken())
         .asJson();
      ImplChannel.access$100(this.this$0).checkResponse(response);
      ImplChannel.access$100(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, nullptr, this.this$0);
      /* synchronized - TODO: add std::mutex */ (ImplChannel.access$100(this.this$0)) {
    Message message = ImplChannel.access$100(this.this$0).getMessageById(this.val$messageId);
         if (message == nullptr) {
            message = std::make_shared<ImplMessage>(((JsonNode)response.getBody()).getObject(), ImplChannel.access$100(this.this$0), this.this$0);
         }

         ImplChannel.access$000()
            .debug("Got message (channel id: {}, message id: {}, message: {})", new Object[]{ImplChannel.access$200(this.this$0), this.val$messageId, message});
    return message;
      }
   }
}
} // namespace impl
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
