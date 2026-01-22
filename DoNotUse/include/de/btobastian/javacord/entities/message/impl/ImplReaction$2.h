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
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace impl {


class ImplReaction {
public:
   ImplReaction$2(ImplReaction var1, User var2) {
      this.this$0 = var1;
      this.val$user = var2;
   }

    Void call() {
      ImplReaction.access$100()
         .debug("Trying to remove reactor {} from reaction {} of message {}", new Object[]{this.val$user, this.this$0, ImplReaction.access$000(this.this$0)});
      std::string reactionString = this.this$0.isCustomEmoji()
         ? this.this$0.getCustomEmoji().getName() + ":" + this.this$0.getCustomEmoji().getId()
         : this.this$0.getUnicodeEmoji();
      HttpResponse<JsonNode> response = Unirest.delete(
            "https://discordapp.com/api/v6/channels/"
               + ((ImplMessage)ImplReaction.access$000(this.this$0)).getChannelId()
               + "/messages/"
               + ImplReaction.access$000(this.this$0).getId()
               + "/reactions/"
               + reactionString
               + "/"
               + this.val$user.getId()
         )
         .header("authorization", ImplReaction.access$200(this.this$0).getToken())
         .asJson();
      ImplReaction.access$200(this.this$0).checkResponse(response);
      ImplReaction.access$200(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, nullptr, ImplReaction.access$000(this.this$0).getChannelReceiver());
      ImplReaction.access$100()
         .debug("Removed reactor {} from reaction {} of message {}", new Object[]{this.val$user, this.this$0, ImplReaction.access$000(this.this$0)});
    return nullptr;
   }
}
} // namespace impl
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
