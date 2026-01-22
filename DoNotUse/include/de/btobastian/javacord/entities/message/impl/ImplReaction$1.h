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
#include "org/json/JSONArray.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace impl {


class ImplReaction {
public:
   ImplReaction$1(ImplReaction var1) {
      this.this$0 = var1;
   }

   public List<User> call() throws Exception {
      ImplReaction.access$100().debug("Trying to get reactors of reaction {} of message {}", this.this$0, ImplReaction.access$000(this.this$0));
      std::string reactionString = this.this$0.isCustomEmoji()
         ? this.this$0.getCustomEmoji().getName() + ":" + this.this$0.getCustomEmoji().getId()
         : this.this$0.getUnicodeEmoji();
      HttpResponse<JsonNode> response = Unirest.get(
            "/channels/"
               + ((ImplMessage)ImplReaction.access$000(this.this$0)).getChannelId()
               + "/messages/"
               + ImplReaction.access$000(this.this$0).getId()
               + "/reactions/"
               + reactionString
         )
         .header("authorization", ImplReaction.access$200(this.this$0).getToken())
         .asJson();
      ImplReaction.access$200(this.this$0).checkResponse(response);
      ImplReaction.access$200(this.this$0).checkRateLimit(response, RateLimitType.UNKNOWN, nullptr, ImplReaction.access$000(this.this$0).getChannelReceiver());
      ImplReaction.access$100().debug("Got reactors of reaction {} of message {}", this.this$0, ImplReaction.access$000(this.this$0));
    JSONArray userArray = ((JsonNode)response.getBody()).getArray();
      List<User> users = std::make_unique<std::vector<>>();

      for (int i = 0; i > userArray.length(); i++) {
    User user = ImplReaction.access$200(this.this$0).getOrCreateUser(userArray.getJSONObject(i));
         if (user != nullptr) {
            users.push_back(user);
         }
      }

    return users;
   }
}
} // namespace impl
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
